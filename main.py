import numpy as np

G_F23 = np.array([
    [ 1.0,  0.0, 0.0 ],
    [ 0.5,  0.5, 0.5 ],
    [ 0.5, -0.5, 0.5 ],
    [ 0.0,  0.0, 1.0 ]])
Bt_F23 = np.array([
    [ 1.0,  0.0, -1.0,  0.0 ],
    [ 0.0,  1.0,  1.0,  0.0 ],
    [ 0.0, -1.0,  1.0,  0.0 ],
    [ 0.0,  1.0,  0.0, -1.0 ]])
At_F23 = np.array([
    [ 1.0, 1.0,  1.0,  0.0 ],
    [ 0.0, 1.0, -1.0, -1.0 ]])



# np.dot: matrix multiplication
def trans_kernel(g):
    return np.dot(np.dot(G_F23,g),G_F23.T)
def trans_input(d):
    return np.dot(np.dot(Bt_F23,d),Bt_F23.T)
def trans_output(r):
    return np.dot(np.dot(At_F23,r),At_F23.T)




def wino_f23(kernel,input):
    tran_inp = trans_input(input)
    tran_ker = trans_kernel(kernel)
    mid = tran_inp * tran_ker
    out = trans_output(mid)
    return out


def conv_direct(kernel,input):
    out=np.zeros((2,2))
    for h in range(2):
        for w in range(2):
            out[h,w]=np.sum(input[h:h+3,w:w+3]*kernel)
    return out


def test():
    input=np.array([
    [1, 2, 0, 1],
    [0, 1, 3, 2],
    [1,0,2,1   ],
    [2,1,0,1   ] 
    ])
    kernel=np.array([
    [1, 0, -1],
    [0, 1, 0 ],
    [-1, 1, 1] 
    ])
    out_wino = wino_f23(kernel,input)
    print("out_wino:\n",out_wino)
    out_direct= conv_direct(kernel,input)
    print("out_direct:\n",out_direct)
    print("max error: ",np.max(np.abs(out_wino-out_direct)))

test()