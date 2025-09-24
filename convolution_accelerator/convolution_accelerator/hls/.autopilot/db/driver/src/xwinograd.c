// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xwinograd.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XWinograd_CfgInitialize(XWinograd *InstancePtr, XWinograd_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Ctrl_BaseAddress = ConfigPtr->Ctrl_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XWinograd_Start(XWinograd *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XWinograd_ReadReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_AP_CTRL) & 0x80;
    XWinograd_WriteReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XWinograd_IsDone(XWinograd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XWinograd_ReadReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XWinograd_IsIdle(XWinograd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XWinograd_ReadReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XWinograd_IsReady(XWinograd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XWinograd_ReadReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XWinograd_EnableAutoRestart(XWinograd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XWinograd_WriteReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_AP_CTRL, 0x80);
}

void XWinograd_DisableAutoRestart(XWinograd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XWinograd_WriteReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_AP_CTRL, 0);
}

void XWinograd_Set_in_g(XWinograd *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XWinograd_WriteReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_IN_G_DATA, (u32)(Data));
    XWinograd_WriteReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_IN_G_DATA + 4, (u32)(Data >> 32));
}

u64 XWinograd_Get_in_g(XWinograd *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XWinograd_ReadReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_IN_G_DATA);
    Data += (u64)XWinograd_ReadReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_IN_G_DATA + 4) << 32;
    return Data;
}

void XWinograd_Set_in_d(XWinograd *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XWinograd_WriteReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_IN_D_DATA, (u32)(Data));
    XWinograd_WriteReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_IN_D_DATA + 4, (u32)(Data >> 32));
}

u64 XWinograd_Get_in_d(XWinograd *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XWinograd_ReadReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_IN_D_DATA);
    Data += (u64)XWinograd_ReadReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_IN_D_DATA + 4) << 32;
    return Data;
}

void XWinograd_Set_out_y(XWinograd *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XWinograd_WriteReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_OUT_Y_DATA, (u32)(Data));
    XWinograd_WriteReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_OUT_Y_DATA + 4, (u32)(Data >> 32));
}

u64 XWinograd_Get_out_y(XWinograd *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XWinograd_ReadReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_OUT_Y_DATA);
    Data += (u64)XWinograd_ReadReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_OUT_Y_DATA + 4) << 32;
    return Data;
}

void XWinograd_InterruptGlobalEnable(XWinograd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XWinograd_WriteReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_GIE, 1);
}

void XWinograd_InterruptGlobalDisable(XWinograd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XWinograd_WriteReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_GIE, 0);
}

void XWinograd_InterruptEnable(XWinograd *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XWinograd_ReadReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_IER);
    XWinograd_WriteReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_IER, Register | Mask);
}

void XWinograd_InterruptDisable(XWinograd *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XWinograd_ReadReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_IER);
    XWinograd_WriteReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_IER, Register & (~Mask));
}

void XWinograd_InterruptClear(XWinograd *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XWinograd_WriteReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_ISR, Mask);
}

u32 XWinograd_InterruptGetEnabled(XWinograd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XWinograd_ReadReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_IER);
}

u32 XWinograd_InterruptGetStatus(XWinograd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XWinograd_ReadReg(InstancePtr->Ctrl_BaseAddress, XWINOGRAD_CTRL_ADDR_ISR);
}

