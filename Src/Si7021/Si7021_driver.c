#include <Si7021/Si7021_driver.h>

static float get_temp_code(uint16_t temp_code);
static float get_humi_code(uint16_t humi_code);
static uint16_t to_uint16(uint8_t bytes[]);

static float get_temp_code(uint16_t temp_code)
{
  return (float)(((175.72 * temp_code) / 65536.0) - 46.85);
}

static float get_humi_code(uint16_t humi_code)
{
  float value = (float)(((125.0 * humi_code) / 65536.0) - 6.0);

  if(value < 0)
    return 0;
  else if(value > 100)
    return 100;
  else
    return (float)value;
}

static uint16_t to_uint16(uint8_t bytes[])
{
  return (uint16_t)((bytes[0]<<8) | bytes[1]);
}

bool Si7021_read_single_param(Si7021_Handle_t* device, float* data, Si7021_measurement_type_t type)
{
  uint8_t cmd;
  uint8_t buffer[2];
  uint16_t code;

  if(type == Humidity)
    cmd = Humi_HM;
  else if(type == Temperature)
    cmd = Temp_HM;
  else
    return false;

  if(HAL_OK != HAL_I2C_Master_Transmit(device->i2c, Si7021_I2C_ADDR, &cmd, 1, 10000))
    return false;

  if(HAL_OK != HAL_I2C_Master_Receive(device->i2c, Si7021_I2C_ADDR, buffer, 2, 10000))
    return false;

  code = to_uint16(buffer);

  if(type == Humidity)
    *data = get_humi_code(code);
  else if(type == Temperature)
    *data = get_temp_code(code);

  return true;
}

bool Si7021_read_all_params(Si7021_Handle_t* device, float* humidity, float* temperature)
{
  uint8_t cmd = Humi_HM;
  uint8_t buffer[2];
  uint16_t code;

  if(HAL_OK != HAL_I2C_Master_Transmit(device->i2c, Si7021_I2C_ADDR, &cmd, 1, 10000))
    return false;

  if(HAL_OK != HAL_I2C_Master_Receive(device->i2c, Si7021_I2C_ADDR, buffer, 2, 10000))
    return false;

  code = to_uint16(buffer);
  *humidity = get_humi_code(code);

  /* There is a temperature measurement with each RH measurement */
  cmd = Temp_AH;

  if(HAL_OK != HAL_I2C_Master_Transmit(device->i2c, Si7021_I2C_ADDR, &cmd, 1, 10000))
    return false;

  if(HAL_OK != HAL_I2C_Master_Receive(device->i2c, Si7021_I2C_ADDR, buffer, 2, 10000))
    return false;

  code = to_uint16(buffer);
  *temperature = get_temp_code(code);

  return true;
}

