# ==============================================================
# Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
# Tool Version Limit: 2025.05
# Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
# Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
# 
# ==============================================================
source -notrace "/tools/Xilinx/2025.1/Vitis/common/scripts/ipxhls.tcl"
set ip_out_dir "/home/nirmal-thomas/Documents/dev/hls_dev/hardware_acc/convolution_accelerator/convolution_accelerator/hls/impl/ip"
set data_file "/home/nirmal-thomas/Documents/dev/hls_dev/hardware_acc/convolution_accelerator/convolution_accelerator/hls/hls_data.json"
set src_dir [file dir $data_file]
set ip_types {vitis sysgen}
set ippack_opts_dict {}
if { [catch {::ipx::utils::package_hls_ip $ip_out_dir $data_file $ip_types $src_dir $ippack_opts_dict} res] } {
  puts "Caught error:\n$::errorInfo"
  error $res
}
