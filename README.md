# PlatformIO Template project for Nicla Sense ME

This project serves as a [PlatformIO](https://platformio.org/) template project to build and upload firmware for the Arduino Nicla Sense ME 


## Requirements for building the Firmware
- PlatformIO Core (CLI) or PlatformIO IDE


## Steps to Upload the Application Firmware to the Nicla Sense ME board
```
pio run -v -e nicla_sense_me_default -t clean
pio run -v -e nicla_sense_me_default -t upload
```

## Steps to Update the BHY firmware for the BHI260AP chip

### Step 1
This step uploads an stepstone FW which carries the BHY firmware which is written to the on-board flash and then picked up by the bootloader of the Nicla Sense ME board
```
pio run -v -e nicla_sense_me_dfu_bhy -t clean
pio run -v -e nicla_sense_me_dfu_bhy -t upload
```
### Step 2
This step will restore the default application firmware for the main MCU of the Nicla Sense Board
```
pio run -v -e nicla_sense_me_default -t upload
```

