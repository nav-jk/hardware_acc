// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XWINOGRAD_H
#define XWINOGRAD_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xwinograd_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Ctrl_BaseAddress;
} XWinograd_Config;
#endif

typedef struct {
    u64 Ctrl_BaseAddress;
    u32 IsReady;
} XWinograd;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XWinograd_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XWinograd_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XWinograd_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XWinograd_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
#ifdef SDT
int XWinograd_Initialize(XWinograd *InstancePtr, UINTPTR BaseAddress);
XWinograd_Config* XWinograd_LookupConfig(UINTPTR BaseAddress);
#else
int XWinograd_Initialize(XWinograd *InstancePtr, u16 DeviceId);
XWinograd_Config* XWinograd_LookupConfig(u16 DeviceId);
#endif
int XWinograd_CfgInitialize(XWinograd *InstancePtr, XWinograd_Config *ConfigPtr);
#else
int XWinograd_Initialize(XWinograd *InstancePtr, const char* InstanceName);
int XWinograd_Release(XWinograd *InstancePtr);
#endif

void XWinograd_Start(XWinograd *InstancePtr);
u32 XWinograd_IsDone(XWinograd *InstancePtr);
u32 XWinograd_IsIdle(XWinograd *InstancePtr);
u32 XWinograd_IsReady(XWinograd *InstancePtr);
void XWinograd_EnableAutoRestart(XWinograd *InstancePtr);
void XWinograd_DisableAutoRestart(XWinograd *InstancePtr);

void XWinograd_Set_in_g(XWinograd *InstancePtr, u64 Data);
u64 XWinograd_Get_in_g(XWinograd *InstancePtr);
void XWinograd_Set_in_d(XWinograd *InstancePtr, u64 Data);
u64 XWinograd_Get_in_d(XWinograd *InstancePtr);
void XWinograd_Set_out_y(XWinograd *InstancePtr, u64 Data);
u64 XWinograd_Get_out_y(XWinograd *InstancePtr);

void XWinograd_InterruptGlobalEnable(XWinograd *InstancePtr);
void XWinograd_InterruptGlobalDisable(XWinograd *InstancePtr);
void XWinograd_InterruptEnable(XWinograd *InstancePtr, u32 Mask);
void XWinograd_InterruptDisable(XWinograd *InstancePtr, u32 Mask);
void XWinograd_InterruptClear(XWinograd *InstancePtr, u32 Mask);
u32 XWinograd_InterruptGetEnabled(XWinograd *InstancePtr);
u32 XWinograd_InterruptGetStatus(XWinograd *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
