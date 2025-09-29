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
    float At[2][4];
    float Y[2][2];

    // ---- Array partitioning for maximum parallelism ----
#pragma HLS ARRAY_PARTITION variable=g   dim=2 complete
#pragma HLS ARRAY_PARTITION variable=Gg  dim=2 complete
#pragma HLS ARRAY_PARTITION variable=U   complete
#pragma HLS ARRAY_PARTITION variable=d   dim=1 complete
#pragma HLS ARRAY_PARTITION variable=Bd  dim=1 complete
#pragma HLS ARRAY_PARTITION variable=V   complete
#pragma HLS ARRAY_PARTITION variable=M   complete
#pragma HLS ARRAY_PARTITION variable=Y   complete
#pragma HLS ARRAY_PARTITION variable=At complete


// ---- Read filter g (3x3) ----
read_g:
for (int itr = 0, i = 0, j = 0; itr < 9; itr++, j++) {
#pragma HLS LOOP_TRIPCOUNT min=9 max=9
    if (j == 3) { 
        j = 0; 
        i++; }
    g[i][j] = in_g[itr];
}

// ---- Read input d (4x4) ----
read_d:
for (int itr = 0, i = 0, j = 0; itr < 16; itr++, j++) {
#pragma HLS LOOP_TRIPCOUNT min=16 max=16
    if (j == 4) { 
        j = 0; 
        i++; }
    d[i][j] = in_d[itr];
}

    // ---- Step 1a: Gg = G * g ----
compute_Gg:
    for (int i = 0; i < 4; i++) {
#pragma HLS UNROLL
        for (int j = 0; j < 3; j++) {
#pragma HLS UNROLL
            if (i == 0)       Gg[i][j] = g[0][j];
            else if (i == 1)  Gg[i][j] = (g[0][j] + g[1][j] + g[2][j]) / 2;
            else if (i == 2)  Gg[i][j] = (g[0][j] - g[1][j] + g[2][j]) / 2;
            else               Gg[i][j] = g[2][j];
        }
    }

    // ---- Step 1b: U = Gg * G^T ----
compute_U:
    for(int i=0;i<4;i++){
#pragma HLS UNROLL
        U[i][0] = Gg[i][0];
        U[i][1] = (Gg[i][0] + Gg[i][1] + Gg[i][2])/2;
        U[i][2] = (Gg[i][0] - Gg[i][1] + Gg[i][2])/2;
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
        V[i][0] = Bd[i][0] - Bd[i][2];
        V[i][1] = Bd[i][1] + Bd[i][2];
        V[i][2] = -Bd[i][1] + Bd[i][2];     // <-- fixed
        V[i][3] = Bd[i][1] - Bd[i][3];      // <-- fixed
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

    // ---- Step 4a: Compute output AT * M ----
compute_AT:
        for(int i=0;i<4;i++){
#pragma HLS UNROLL
        At[0][i] = M[0][i]+M[1][i]+M[2][i];
        At[1][i] = M[1][i]-M[2][i]-M[3][i];
    }

    // ---- Step 4b: Compute output Y ----
compute_Y:
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
#pragma HLS UNROLL
            if(i==0 && j==0)      Y[i][j] = At[0][0] + At[0][1] + At[0][2];
            else if(i==0 && j==1) Y[i][j] = At[0][1] - At[0][2] - At[0][3];
            else if(i==1 && j==0) Y[i][j] = At[1][0] + At[1][1] + At[1][2];
            else                   Y[i][j] = At[1][1] - At[1][2] - At[1][3];
        }
    }

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
