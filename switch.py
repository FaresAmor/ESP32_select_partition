import sys
import os

# Get the IDF_PATH environment variable
idf_path = os.environ.get("IDF_PATH")
if not idf_path:
    raise EnvironmentError("IDF_PATH environment variable is not set.")

# Construct the path to the otatool.py script
otatool_dir = os.path.join(idf_path, "components", "app_update")

# Add the directory containing otatool.py to the Python path
sys.path.append(otatool_dir)

# Import all functions and classes from otatool
from otatool import OtatoolTarget

# Initialize the OtatoolTarget with the target device's serial port
target = OtatoolTarget("COM4")  # Use the correct COM port

# Switch the boot partition to the one corresponding to app slot 1
target.switch_ota_partition(0)

#python run_otatool.py     this is the cmd ligne to run this code in terminal
