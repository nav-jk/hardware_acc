#include <iostream>
#include <vector>
using namespace std;

int main() {
    // ---- Input ----
    float g[3][3] = { {1, 2, 3},
                      {4, 5, 6},
                      {7, 8, 9} };

    float d[4][4] = { {1, 2, 3, 4},
                      {5, 6, 7, 8},
                      {9,10,11,12},
                      {13,14,15,16} };

    // ---- Step 1a: Gg ----
    float Gg[4][3];
    Gg[0][0] = g[0][0];                     Gg[0][1] = g[0][1];                     Gg[0][2] = g[0][2];
    Gg[1][0] = 0.5*(g[0][0]+g[1][0]+g[2][0]); Gg[1][1] = 0.5*(g[0][1]+g[1][1]+g[2][1]); Gg[1][2] = 0.5*(g[0][2]+g[1][2]+g[2][2]);
    Gg[2][0] = 0.5*(g[0][0]-g[1][0]+g[2][0]); Gg[2][1] = 0.5*(g[0][1]-g[1][1]+g[2][1]); Gg[2][2] = 0.5*(g[0][2]-g[1][2]+g[2][2]);
    Gg[3][0] = g[2][0];                     Gg[3][1] = g[2][1];                     Gg[3][2] = g[2][2];

    // ---- Step 1b: U = Gg * G^T ----
    float U[4][4];
    for(int i=0;i<4;i++){
        U[i][0] = Gg[i][0];
        U[i][1] = 0.5*Gg[i][0] + 0.5*Gg[i][1] + 0.5*Gg[i][2];
        U[i][2] = 0.5*Gg[i][0] - 0.5*Gg[i][1] + 0.5*Gg[i][2];
        U[i][3] = Gg[i][2];
    }

    // ---- Step 2a: Bd = B^T * d ----
    float Bd[4][4];
    for(int j=0;j<4;j++){
        Bd[0][j] = d[0][j]-d[2][j];
        Bd[1][j] = d[1][j]+d[2][j];
        Bd[2][j] = -d[1][j]+d[2][j];
        Bd[3][j] = d[1][j]-d[3][j];
    }

    // ---- Step 2b: V = Bd * B ----
    float V[4][4];
    for(int i=0;i<4;i++){
        V[i][0] = Bd[i][0]-Bd[i][2];
        V[i][1] = Bd[i][1]+Bd[i][2];
        V[i][2] = -Bd[i][0]+Bd[i][1]+Bd[i][2];
        V[i][3] = -Bd[i][3];
    }

    // ---- Step 3: Elementwise multiply M = U .* V ----
    float M[4][4];
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            M[i][j] = U[i][j] * V[i][j];
        }
    }

    // ---- Step 4: Output Y = A^T * M * A ----
    float Y[2][2];
    Y[0][0] = M[0][0]+M[0][1]+M[0][2]+0; // A^T row0 * M col0
    Y[0][1] = M[0][1]-M[0][2]-M[0][3];
    Y[1][0] = M[1][0]+M[1][1]+M[1][2];
    Y[1][1] = M[1][1]-M[1][2]-M[1][3];

    // ---- Print Output ----
    cout << "Output Y (2x2):" << endl;
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            cout << Y[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
