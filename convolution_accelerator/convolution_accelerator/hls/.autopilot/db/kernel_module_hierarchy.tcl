set ModuleHierarchy {[{
"Name" : "winograd", "RefName" : "winograd","ID" : "0","Type" : "sequential",
"SubInsts" : [
	{"Name" : "grp_winograd_Pipeline_read_g_fu_234", "RefName" : "winograd_Pipeline_read_g","ID" : "1","Type" : "sequential",
		"SubLoops" : [
		{"Name" : "read_g","RefName" : "read_g","ID" : "2","Type" : "pipeline"},]},
	{"Name" : "grp_winograd_Pipeline_read_d_fu_250", "RefName" : "winograd_Pipeline_read_d","ID" : "3","Type" : "sequential",
		"SubLoops" : [
		{"Name" : "read_d","RefName" : "read_d","ID" : "4","Type" : "pipeline"},]},
	{"Name" : "grp_winograd_Pipeline_compute_Y_fu_269", "RefName" : "winograd_Pipeline_compute_Y","ID" : "5","Type" : "sequential",
		"SubLoops" : [
		{"Name" : "compute_Y","RefName" : "compute_Y","ID" : "6","Type" : "pipeline"},]},]
}]}