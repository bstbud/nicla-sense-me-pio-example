# PlatformIO Template project for Nicla Sense ME

This project serves as a [PlatformIO](https://platformio.org/) template project to build and upload firmware for the Arduino Nicla Sense ME


## Requirements for building the Firmware
- PlatformIO Core (CLI) or PlatformIO IDE

## Steps to Upload the app firmware to the Nicla Sense ME board
This firmware is the referring to the example sketch "App.ino" from the Arduino library "Arduino_BHY2"

## Steps to Upload the Application Firmware to the Nicla Sense ME board
```
pio run -v -e nicla_sense_me_app -t clean
pio run -v -e nicla_sense_me_app -t upload
```

## Steps to Update the BHY firmware for the BHI260AP chip on the Nicla Sense ME board

### Step 1
This step uploads an stepstone FW which carries the BHY firmware which is written to the on-board flash and then picked up by the bootloader of the Nicla Sense ME board
```
pio run -v -e nicla_sense_me_dfu_bhi260 -t clean
pio run -v -e nicla_sense_me_dfu_bhi260 -t upload
```
### Step 2
This step will restore the app application firmware for the main MCU of the Nicla Sense Board
```
pio run -v -e nicla_sense_me_app -t upload
```


# Arduino IDE Support
This project is also compatible with Arduino IDE, simply open the sketch nicla-sense-me-pio-example.ino by the IDE and upload
## Steps to Upload the Application Firmware to the Nicla Sense ME board
- Build Configuration Change
locate the file, ./src/inc/app_config.h
make sure the APP_CONFIG_DFU_BHY is defined as 0
```
#define APP_CONFIG_DFU_BHY 0
```
- Build
Use the Arduino IDE to upload the sketch

## Steps to Update the BHY firmware for the BHI260AP chip on the Nicla Sense ME board

- Build Configuration Change
locate the file, ./src/inc/app_config.h
make sure the APP_CONFIG_DFU_BHY is defined as 1
```
#define APP_CONFIG_DFU_BHY 1
```
- Build
Use the Arduino IDE to upload the sketch

_Note:
This step uploads an stepstone FW which carries the BHY firmware which is written to the on-board flash and then picked up by the bootloader of the Nicla Sense ME board_


- Restore
Follow the steps (above) to restore the regular application firmware

