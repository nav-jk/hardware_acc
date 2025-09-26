# 2025-09-26T18:00:56.279202
import vitis

client = vitis.create_client()
client.set_workspace(path="hardware_acc")

comp = client.get_component(name="convolution_accelerator")
comp.run(operation="IMPLEMENTATION")

vitis.dispose()

