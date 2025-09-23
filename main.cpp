#include <iostream>
using namespace std;

int main() {
    // ---- Input ----
    float g[3][3] = { {1, 0, -1},
                      {0, 1, 0},
                      {-1, 0, 1} };

    float d[4][4] = { {1, 2, 0, 1},
                      {0, 1, 3, 2},
                      {1,0,2,1},
                      {2,1,0,1} };

    // ---- Step 1a: Gg ----
    float Gg[4][3];
    Gg[0][0] = g[0][0];                     Gg[0][1] = g[0][1];                     Gg[0][2] = g[0][2];
    Gg[1][0] = 0.5*(g[0][0]+g[1][0]+g[2][0]); Gg[1][1] = 0.5*(g[0][1]+g[1][1]+g[2][1]); Gg[1][2] = 0.5*(g[0][2]+g[1][2]+g[2][2]);
    Gg[2][0] = 0.5*(g[0][0]-g[1][0]+g[2][0]); Gg[2][1] = 0.5*(g[0][1]-g[1][1]+g[2][1]); Gg[2][2] = 0.5*(g[0][2]-g[1][2]+g[2][2]);
    Gg[3][0] = g[2][0];                     Gg[3][1] = g[2][1];                     Gg[3][2] = g[2][2];

    cout << "Gg (4x3):" << endl;
    for(int i=0;i<4;i++){
        for(int j=0;j<3;j++) cout << Gg[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    // ---- Step 1b: U = Gg * G^T ----
    float U[4][4];
    for(int i=0;i<4;i++){
        U[i][0] = Gg[i][0];
        U[i][1] = 0.5*Gg[i][0] + 0.5*Gg[i][1] + 0.5*Gg[i][2];
        U[i][2] = 0.5*Gg[i][0] - 0.5*Gg[i][1] + 0.5*Gg[i][2];
        U[i][3] = Gg[i][2];
    }

    cout << "U (4x4):" << endl;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++) cout << U[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    // ---- Step 2a: Bd = B^T * d ----
    float Bd[4][4];
    for(int j=0;j<4;j++){
        Bd[0][j] = d[0][j]-d[2][j];
        Bd[1][j] = d[1][j]+d[2][j];
        Bd[2][j] = -d[1][j]+d[2][j];
        Bd[3][j] = d[1][j]-d[3][j];
    }

    cout << "Bd (4x4):" << endl;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++) cout << Bd[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    // ---- Step 2b: V = Bd * B ----
    float V[4][4];
    for(int i=0;i<4;i++){
        V[i][0] = Bd[i][0]-Bd[i][2];
        V[i][1] = Bd[i][1]+Bd[i][2];
        V[i][2] = -Bd[i][1]+Bd[i][2];
        V[i][3] = Bd[i][1]-Bd[i][3];
    }

    cout << "V (4x4):" << endl;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++) cout << V[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    // ---- Step 3: Elementwise multiply M = U .* V ----
    float M[4][4];
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            M[i][j] = U[i][j] * V[i][j];
        }
    }

    cout << "M (4x4):" << endl;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++) cout << M[i][j] << " ";
        cout << endl;
    }
    cout << endl;


    float At[2][4];
    for(int i=0;i<4;i++){
        At[0][i] = M[0][i]+M[1][i]+M[2][i];
        At[1][i] = M[1][i]-M[2][i]-M[3][i];
    }
    // ---- Step 4: Output Y = A^T * M * A ----
    float Y[2][2];
    Y[0][0] = At[0][0]+At[0][1]+At[0][2];
    Y[0][1] = At[0][1]-At[0][2]-At[0][3];
    Y[1][0] = At[1][0]+At[1][1]+At[1][2];
    Y[1][1] = At[1][1]-At[1][2]-At[1][3];

    cout << "Output Y (2x2):" << endl;
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            cout << Y[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
