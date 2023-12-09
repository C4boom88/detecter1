#include "MS5803.h"
#include "i2c.h"


void MS5803_Init(I2C_HandleTypeDef *hi2c1)
{
  uint8_t cmd = 0x1E; // Reset command
  HAL_I2C_Master_Transmit(hi2c1, MS5803_ADDR, &cmd, 1, HAL_MAX_DELAY);
  HAL_Delay(10);
}

uint32_t MS5803_ReadRawPressure(I2C_HandleTypeDef *hi2c1)
{
  uint8_t cmd = 0x48; // Pressure conversion command
  HAL_I2C_Master_Transmit(hi2c1, MS5803_ADDR, &cmd, 1, HAL_MAX_DELAY);
  HAL_Delay(10);

  uint8_t buf[3];
  HAL_I2C_Master_Receive(hi2c1, MS5803_ADDR, buf, 3, HAL_MAX_DELAY);

  return ((uint32_t)buf[0] << 16) | ((uint32_t)buf[1] << 8) | buf[2];
}

float MS5803_GetPressure(I2C_HandleTypeDef *hi2c1)
{
  uint32_t D1 = MS5803_ReadRawPressure(hi2c1);

  uint8_t cmd = 0x58; // Temperature conversion command
  HAL_I2C_Master_Transmit(hi2c1, MS5803_ADDR, &cmd, 1, HAL_MAX_DELAY);
  HAL_Delay(10);

  uint8_t buf[3];
  HAL_I2C_Master_Receive(hi2c1, MS5803_ADDR, buf, 3, HAL_MAX_DELAY);

  uint32_t D2 = ((uint32_t)buf[0] << 16) | ((uint32_t)buf[1] << 8) | buf[2];

  int32_t dT = D2 - ((uint32_t)0x800000); // Calculate temperature difference
  int32_t TEMP = 2000 + ((int64_t)dT * 1000 / 8388608); // Calculate temperature

  int64_t OFF = ((int64_t)24576 * 2048) + ((int64_t)dT * 45 / 1024); // Calculate offset
  int64_t SENS = ((int64_t)24576 * 32768) + ((int64_t)dT * 45 / 1024); // Calculate sensitivity

  int32_t P = ((D1 * SENS / 2097152) - OFF) * 10000 / 32768; // Calculate pressure

  return (float)P / 100.0f;
}