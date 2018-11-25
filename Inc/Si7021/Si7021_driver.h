#ifndef _SI7021_H_
#define _SI7021_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"

#include <stdbool.h>

static const uint16_t Si7021_I2C_ADDR = (0x40<<1);           // Si7021 I2C address

#define RES0 0
#define RES1 7
#define VDDS 6
#define HTRE 2

typedef enum Si7021_commands
{
  Humi_HM        = 0xE5, // Measure Relative Humidity, Hold Master Mode
  Humi_NHM       = 0xF5, // Measure Relative Humidity, No Hold Master Mode
  Temp_HM        = 0xE3, // Measure Temperature, Hold Master Mode
  Temp_NHM       = 0xF3, // Measure Temperature, No Hold Master Mode
  Temp_AH        = 0xE0, // Read Temperature Value from Previous RH Measurement
  Si7021_Reset   = 0xFE, // Reset
  W_RHT_U_reg    = 0xE6, // Write RH/T User Register 1
  R_RHT_U_reg    = 0xE7, // Read RH/T User Register 1
  W_Heater_C_reg = 0x51, // Write Heater Control Register
  R_Heater_C_reg = 0x11, // Read Heater Control Register
  R_ID_Byte11    = 0xFA, // Read Electronic ID 1st Byte, first part
  R_ID_Byte12    = 0x0F, // Read Electronic ID 1st Byte, second part
  R_ID_Byte21    = 0xFC, // Read Electronic ID 2nd Byte, first part
  R_ID_Byte22    = 0xC9, // Read Electronic ID 2nd Byte, second part
  R_Firm_rev1    = 0x84, // Read Firmware Revision, first part
  R_Firm_rev2    = 0xB8  // Read Firmware Revision, second part
}Si7021_commands_t;

typedef enum Si7021_measurement_type
{
  Humidity,
  Temperature
}Si7021_measurement_type_t;

typedef struct
{	
	I2C_HandleTypeDef* i2c;

}Si7021_Handle_t;

bool Si7021_read_single_param(Si7021_Handle_t* device, float* data, Si7021_measurement_type_t type);

bool Si7021_read_all_params(Si7021_Handle_t* device, float* humidity, float* temperature);

#ifdef __cplusplus
}
#endif

#endif /* _SI7021_H_ */
