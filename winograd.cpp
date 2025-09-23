#include "matmul_partition.h"

// HLS tripcount (optional)
const unsigned int c_dim = 4;

void winograd_conv(float* in_g, float* in_d, float* out_y) {
#pragma HLS INTERFACE m_axi port=in_g depth=9
#pragma HLS INTERFACE m_axi port=in_d depth=16
#pragma HLS INTERFACE m_axi port=out_y depth=4
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL

    // ---- Local buffers ----
    float g[3][3];
    float d[4][4];
    float Gg[4][3];
    float U[4][4];
    float Bd[4][4];
    float V[4][4];
    float M[4][4];
    float Y[2][2];

    // ---- Array partitioning for maximum parallelism ----
#pragma HLS ARRAY_PARTITION variable=g dim=2 complete
#pragma HLS ARRAY_PARTITION variable=Gg dim=2 complete
#pragma HLS ARRAY_PARTITION variable=U dim=1 complete
#pragma HLS ARRAY_PARTITION variable=U dim=2 complete
#pragma HLS ARRAY_PARTITION variable=d dim=1 complete
#pragma HLS ARRAY_PARTITION variable=Bd dim=1 complete
#pragma HLS ARRAY_PARTITION variable=V dim=1 complete
#pragma HLS ARRAY_PARTITION variable=V dim=2 complete
#pragma HLS ARRAY_PARTITION variable=M dim=1 complete
#pragma HLS ARRAY_PARTITION variable=M dim=2 complete
#pragma HLS ARRAY_PARTITION variable=Y dim=1 complete
#pragma HLS ARRAY_PARTITION variable=Y dim=2 complete

    // ---- Read filter g ----
read_g:
    for (int i = 0, idx = 0; i < 3; i++)
        for (int j = 0; j < 3; j++, idx++)
#pragma HLS LOOP_TRIPCOUNT min=9 max=9
            g[i][j] = in_g[idx];

    // ---- Read input d ----
read_d:
    for (int i = 0, idx = 0; i < 4; i++)
        for (int j = 0; j < 4; j++, idx++)
#pragma HLS LOOP_TRIPCOUNT min=16 max=16
            d[i][j] = in_d[idx];

    // ---- Step 1a: Gg = G * g ----
compute_Gg:
    for (int i = 0; i < 4; i++) {
#pragma HLS UNROLL
        for (int j = 0; j < 3; j++) {
#pragma HLS UNROLL
            if (i == 0)       Gg[i][j] = g[0][j];
            else if (i == 1)  Gg[i][j] = 0.5f * (g[0][j] + g[1][j] + g[2][j]);
            else if (i == 2)  Gg[i][j] = 0.5f * (g[0][j] - g[1][j] + g[2][j]);
            else               Gg[i][j] = g[2][j];
        }
    }

    // ---- Step 1b: U = Gg * G^T ----
compute_U:
    for(int i=0;i<4;i++){
#pragma HLS UNROLL
        U[i][0] = Gg[i][0];
        U[i][1] = 0.5f*(Gg[i][0] + Gg[i][1] + Gg[i][2]);
        U[i][2] = 0.5f*(Gg[i][0] - Gg[i][1] + Gg[i][2]);
        U[i][3] = Gg[i][2];
    }

    // ---- Step 2a: Bd = B^T * d ----
compute_Bd:
    for(int j=0;j<4;j++){
#pragma HLS UNROLL
        Bd[0][j] = d[0][j]-d[2][j];
        Bd[1][j] = d[1][j]+d[2][j];
        Bd[2][j] = -d[1][j]+d[2][j];
        Bd[3][j] = d[1][j]-d[3][j];
    }

    // ---- Step 2b: V = Bd * B ----
compute_V:
    for(int i=0;i<4;i++){
#pragma HLS UNROLL
        V[i][0] = Bd[i][0]-Bd[i][2];
        V[i][1] = Bd[i][1]+Bd[i][2];
        V[i][2] = -Bd[i][0]+Bd[i][1]+Bd[i][2];
        V[i][3] = -Bd[i][3];
    }

    // ---- Step 3: Elementwise multiply M = U .* V ----
compute_M:
    for(int i=0;i<4;i++){
#pragma HLS UNROLL
        for(int j=0;j<4;j++){
#pragma HLS UNROLL
            M[i][j] = U[i][j] * V[i][j];
        }
    }

    // ---- Step 4: Compute output Y ----
Y[0][0] = M[0][0]+M[0][1]+M[0][2];
Y[0][1] = M[0][1]-M[0][2]-M[0][3];
Y[1][0] = M[1][0]+M[1][1]+M[1][2];
Y[1][1] = M[1][1]-M[1][2]-M[1][3];

    // ---- Write results back ----
write_y:
    for(int i=0;i<2;i++){
#pragma HLS UNROLL
        for(int j=0;j<2;j++){
#pragma HLS UNROLL
            out_y[i*2+j] = Y[i][j];
        }
    }
}
