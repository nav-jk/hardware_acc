set SynModuleInfo {
  {SRCNAME winograd_Pipeline_read_g MODELNAME winograd_Pipeline_read_g RTLNAME winograd_winograd_Pipeline_read_g
    SUBMODULES {
      {MODELNAME winograd_flow_control_loop_pipe_sequential_init RTLNAME winograd_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME winograd_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME winograd_Pipeline_read_d MODELNAME winograd_Pipeline_read_d RTLNAME winograd_winograd_Pipeline_read_d}
  {SRCNAME winograd_Pipeline_compute_Y MODELNAME winograd_Pipeline_compute_Y RTLNAME winograd_winograd_Pipeline_compute_Y}
  {SRCNAME winograd MODELNAME winograd RTLNAME winograd IS_TOP 1
    SUBMODULES {
      {MODELNAME winograd_faddfsub_32ns_32ns_32_5_full_dsp_1 RTLNAME winograd_faddfsub_32ns_32ns_32_5_full_dsp_1 BINDTYPE op TYPE fadd IMPL fulldsp LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME winograd_fsub_32ns_32ns_32_5_full_dsp_1 RTLNAME winograd_fsub_32ns_32ns_32_5_full_dsp_1 BINDTYPE op TYPE fsub IMPL fulldsp LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME winograd_fadd_32ns_32ns_32_5_full_dsp_1 RTLNAME winograd_fadd_32ns_32ns_32_5_full_dsp_1 BINDTYPE op TYPE fadd IMPL fulldsp LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME winograd_fmul_32ns_32ns_32_4_max_dsp_1 RTLNAME winograd_fmul_32ns_32ns_32_4_max_dsp_1 BINDTYPE op TYPE fmul IMPL maxdsp LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME winograd_gmem_m_axi RTLNAME winograd_gmem_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME winograd_CTRL_s_axi RTLNAME winograd_CTRL_s_axi BINDTYPE interface TYPE interface_s_axilite}
    }
  }
}
