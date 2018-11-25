#ifndef _BMP280_H_
#define _BMP280_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"

#include <stdint.h>
#include <stdbool.h>

#define BMP280_I2C_ADDR_0  0x76			// if SDO pin is low
#define BMP280_I2C_ADDR_1  0x77			// if SDO pin is high

#define BMP280_CHIP_ID  0x58				// BMP280 has chip-id 0x58
#define BME280_CHIP_ID  0x60				// BME280 has chip-id 0x60

typedef enum {
    BMP280_MODE_SLEEP = 0,
    BMP280_MODE_FORCED = 1,
    BMP280_MODE_NORMAL = 3
}BMP280_Mode;

typedef enum {
    BMP280_FILTER_OFF = 0,
    BMP280_FILTER_2 = 1,
    BMP280_FILTER_4 = 2,
    BMP280_FILTER_8 = 3,
    BMP280_FILTER_16 = 4
}BMP280_Filter;

typedef enum {
    BMP280_SKIPPED = 0,          // no measurement
    BMP280_ULTRA_LOW_POWER = 1,  // oversampling x1
    BMP280_LOW_POWER = 2,        // oversampling x2
    BMP280_STANDARD = 3,         // oversampling x4
    BMP280_HIGH_RES = 4,         // oversampling x8
    BMP280_ULTRA_HIGH_RES = 5    // oversampling x16
}BMP280_Oversampling;

typedef enum {
    BMP280_STANDBY_05 = 0,      // stand by time 0.5ms
    BMP280_STANDBY_62 = 1,      // stand by time 62.5ms
    BMP280_STANDBY_125 = 2,     // stand by time 125ms
    BMP280_STANDBY_250 = 3,     // stand by time 250ms
    BMP280_STANDBY_500 = 4,     // stand by time 500ms
    BMP280_STANDBY_1000 = 5,    // stand by time 1s
    BMP280_STANDBY_2000 = 6,    // stand by time 2s BMP280, 10ms BME280
    BMP280_STANDBY_4000 = 7,    // stand by time 4s BMP280, 20ms BME280
}BMP280_StandbyTime;

typedef struct {
    BMP280_Mode mode;
    BMP280_Filter filter;
    BMP280_Oversampling oversampling_pressure;
    BMP280_Oversampling oversampling_temperature;
    BMP280_Oversampling oversampling_humidity;
    BMP280_StandbyTime standby;
}BMP280_params_t;

typedef struct {
    uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;
    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;

    // Humidity compensation for BME280
    uint8_t  dig_H1;
    int16_t  dig_H2;
    uint8_t  dig_H3;
    int16_t  dig_H4;
    int16_t  dig_H5;
    int8_t   dig_H6;

    uint16_t addr;

    I2C_HandleTypeDef* i2c;

    BMP280_params_t params;

    uint8_t  id;

}BMP280_Handle_t;

void BMP280_init_default_params(BMP280_params_t *params);

bool BMP280_init(BMP280_Handle_t *dev, BMP280_params_t *params);

bool BMP280_read_all_params_fixed(BMP280_Handle_t *dev, int32_t *temperature, uint32_t *pressure, uint32_t *humidity);

bool BMP280_read_all_params_float(BMP280_Handle_t *dev, float *temperature, float *pressure, float *humidity);					   

#ifdef __cplusplus
}
#endif

#endif  // _BMP280_H_
