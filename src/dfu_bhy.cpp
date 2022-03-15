#include "inc/app_config.h"

#if APP_CONFIG_DFU_BHY
#include "Arduino.h"


#include "SPIFBlockDevice.h"
#include "LittleFileSystem.h"



#include "inc/fw.h" //echo const > fw.h && xxd -i BHI260AP_NiclaSenseME-flash.fw >> fw.h

#define BHY_DFU_FW_PATH "/fs/BHY_UPDATE.BIN"
#define BHY_DFU_FW_INFO_PATH "/fs/BHY_FW.INFO"

SPIFBlockDevice spif(SPI_PSELMOSI0, SPI_PSELMISO0, SPI_PSELSCK0, CS_FLASH);
mbed::LittleFileSystem fs("fs");
FILE *file;

#define fw_bin BHI260AP_NiclaSenseME_flash_fw
#define fw_bin_len BHI260AP_NiclaSenseME_flash_fw_len

void *nicla_dbg_info_ptr;

void dfubhy() {
  char crc = 0;
  FILE *file_info;
  int info_len = 0;     //FW len read from info file
  char info_crc = 0;    //CRC read from info file
  int size;
  int err;

  for (int i = 0; i < fw_bin_len; i++) {
    crc = crc ^ fw_bin[i];
  }

  Serial.print("The computed CRC is 0x");
  Serial.println(crc, HEX);


  err = fs.mount(&spif);
  if (err) {
    err = fs.reformat(&spif);
    Serial.print("Error mounting file system: ");
    Serial.println(err);
    return;
  }


  file_info = fopen(BHY_DFU_FW_INFO_PATH, "r+");
  if (NULL != file_info) {
      Serial.println("FW info found");
      size = fread(&info_crc, sizeof(info_crc), 1, file_info);
      size = fread(&info_len, sizeof(info_len), 1, file_info);
      fseek(file_info, 0, SEEK_SET);
  } else {
      Serial.println("FW info does not exist, created");
      file_info = fopen(BHY_DFU_FW_INFO_PATH, "wb");
  }

  if ((fw_bin_len != info_len) || (crc != info_crc)) {
      Serial.println("BHY FW outdated or unknown version previously, will be updated!");
      file = fopen(BHY_DFU_FW_PATH, "wb");
      if (NULL != file) {
          int ret;
          Serial.println("Writing BHY FW binary into SPIFlash...");
          ret = fwrite(fw_bin, fw_bin_len, 1, file);
          fwrite(&crc, 1, 1, file);
          delay(100);
          fclose(file);
      } else {
          Serial.println("error writing to the BHY FW bin");
      }

      if (NULL != file_info) {
          size = fwrite(&crc, sizeof(crc), 1, file_info);
          size = fwrite(&fw_bin_len, sizeof(fw_bin_len), 1, file_info);
          fclose(file_info);
          file_info = NULL;
      }

      Serial.println("BHY FW Upload Done!");

      NVIC_SystemReset();
  } else {
      Serial.println("BHY FW already up-to-date!");
  }

  if (NULL != file_info) {
      fclose(file_info);
  }
}

#endif
