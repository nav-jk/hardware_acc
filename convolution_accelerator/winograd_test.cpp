#include "winograd.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>


int main() {

    float g[9] = {1, 0, -1, 0, 1, 0, -1, 0, 1};
    float d[16] = {1, 2, 0, 1, 0, 1, 3, 2, 1, 0, 2, 1, 2, 1, 0, 1};
    float out[4] = {0};

    winograd(g, d, out);

    for (int i = 0;i < 4;i++) {
        std::cout << out[i] << std::endl;
    }
    
    return EXIT_SUCCESS;   
}