
import vitis
import os

cwd = os.getcwd()+'/'

# Initialize session
client = vitis.create_client()
client.set_workspace(path='./w')

# Delete the component if it already exists
if os.path.exists('./w/convolution_accelerator'):
	client.delete_component(name='convolution_accelerator')

# Create component. Create new config file in the component folder of the workspace
comp = client.create_hls_component(name='convolution_accelerator', cfg_file = ['hls_config.cfg'], template = 'empty_hls_component')

# Get handle of config file, then programmatically set desired options
cfg_file = client.get_config_file(path = './w/convolution_accelerator/hls_config.cfg')
cfg_file.set_value (                 key = 'part',                  value = 'xcvu440_CIV-flgb2377-1-i') 
cfg_file.set_value (section = 'hls', key = 'syn.file',              value = cwd+'winograd.cpp')
cfg_file.set_values(section = 'hls', key = 'tb.file',               values = [cwd+'winograd_test.cpp'])
cfg_file.set_value (section = 'hls', key = 'syn.top',               value = 'winograd')
cfg_file.set_value (section = 'hls', key = 'clock',                 value = '10') # 250MHz
cfg_file.set_value (section = 'hls', key = 'flow_target',           value = 'vivado')
cfg_file.set_value (section = 'hls', key = 'package.output.syn',    value = '0')
cfg_file.set_value (section = 'hls', key = 'package.output.format', value = 'ip_catalog')
cfg_file.set_value (section = 'hls', key = 'csim.code_analyzer',    value = '0')

# Run flow steps
comp = client.get_component(name='convolution_accelerator')
comp.run(operation='C_SIMULATION')
comp.run(operation='SYNTHESIS')
comp.run(operation='CO_SIMULATION')