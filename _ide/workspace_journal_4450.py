# 2025-09-25T20:53:17.626341
import vitis

client = vitis.create_client()
client.set_workspace(path="hardware_acc")

comp = client.get_component(name="convolution_accelerator")
comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

vitis.dispose()

