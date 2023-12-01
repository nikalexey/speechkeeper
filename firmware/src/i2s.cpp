#include "i2s.h"

void I2S_Init(i2s_mode_t MODE, i2s_bits_per_sample_t BPS)
{
  i2s_config_t i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN | I2S_MODE_ADC_BUILT_IN),
      .sample_rate = SAMPLE_RATE,
      .bits_per_sample = BPS,
      .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
      .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_STAND_I2S | I2S_COMM_FORMAT_STAND_MSB),
      .intr_alloc_flags = 0,
      .dma_buf_count = 16,
      .dma_buf_len = 60
    };
  if (MODE == I2S_MODE_DAC_BUILT_IN || MODE == I2S_MODE_ADC_BUILT_IN) {
    Serial.println("using ADC_builtin");
    i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    // GPIO36, VP
    i2s_set_adc_mode(ADC_UNIT_1, ADC1_CHANNEL_0);  
  }
}

size_t I2S_Read(char *data, int numData)
{
  size_t bytes_read;
  i2s_read(I2S_NUM_0, (char *)data, numData, &bytes_read, portMAX_DELAY);
  return bytes_read;
}

size_t I2S_Write(char *data, int numData)
{
  size_t bytes_written;
  i2s_write(I2S_NUM_0, (const char *)data, numData, &bytes_written, portMAX_DELAY);
  return bytes_written;
}
