// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
// Tool Version Limit: 2025.05
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#ifdef SDT
#include "xparameters.h"
#endif
#include "xwinograd.h"

extern XWinograd_Config XWinograd_ConfigTable[];

#ifdef SDT
XWinograd_Config *XWinograd_LookupConfig(UINTPTR BaseAddress) {
	XWinograd_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XWinograd_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XWinograd_ConfigTable[Index].Ctrl_BaseAddress == BaseAddress) {
			ConfigPtr = &XWinograd_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XWinograd_Initialize(XWinograd *InstancePtr, UINTPTR BaseAddress) {
	XWinograd_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XWinograd_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XWinograd_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XWinograd_Config *XWinograd_LookupConfig(u16 DeviceId) {
	XWinograd_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XWINOGRAD_NUM_INSTANCES; Index++) {
		if (XWinograd_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XWinograd_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XWinograd_Initialize(XWinograd *InstancePtr, u16 DeviceId) {
	XWinograd_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XWinograd_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XWinograd_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

