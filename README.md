## Overview
  
- Input: 3x3 filter (`g`) and 4x4 input tile (`d`)  
- Output: 2x2 tile (`Y`)  


## Matrix Overview

| Matrix | Size | Role |
|--------|------|------|
| `g`    | 3x3  | Filter |
| `d`    | 4x4  | Input tile |
| `Gg`   | 4x3  | Filter transform (G * g) |
| `U`    | 4x4  | Intermediate filter |
| `Bd`   | 4x4  | Input transform (B^T * d) |
| `V`    | 4x4  | Transformed input (Bd * B) |
| `M`    | 4x4  | Elementwise multiplication U .* V |
| `Y`    | 2x2  | Final output |

---

## Array Partitioning (Parallel Access)

Array partitioning splits arrays into separate hardware registers or memory blocks so **all elements can be accessed simultaneously**.

```cpp
#pragma HLS ARRAY_PARTITION variable=g dim=2 complete   // Each column separate
#pragma HLS ARRAY_PARTITION variable=Gg dim=2 complete  // Parallel compute per column
#pragma HLS ARRAY_PARTITION variable=U dim=1 complete   // Each row separate
#pragma HLS ARRAY_PARTITION variable=U dim=2 complete   // Each column separate → fully parallel
#pragma HLS ARRAY_PARTITION variable=d dim=1 complete
#pragma HLS ARRAY_PARTITION variable=Bd dim=1 complete
#pragma HLS ARRAY_PARTITION variable=V dim=1 complete
#pragma HLS ARRAY_PARTITION variable=V dim=2 complete   // Fully parallel
#pragma HLS ARRAY_PARTITION variable=M dim=1 complete
#pragma HLS ARRAY_PARTITION variable=M dim=2 complete
#pragma HLS ARRAY_PARTITION variable=Y dim=1 complete
#pragma HLS ARRAY_PARTITION variable=Y dim=2 complete
```