#include "ILI9341_hardware.h"
#include "common.h"
#include "stm32f4xx_hal.h"

SPI_HandleTypeDef lcdspi;

static void ILI9341_GPIO_Init(void);
static void ILI9341_SPI_Init(void);
static void ILI9341_GPIO_DeInit(void);
static void ILI9341_SPI_DeInit(void);
static void ILI9341_Error(void);

void ILI9341_HardwareInit(void){
  ILI9341_GPIO_Init();
  ILI9341_SPI_Init();
}

void ILI9341_HardwareDeInit(void){
    ILI9341_GPIO_DeInit();
    ILI9341_SPI_DeInit();
}

void ILI9341_CSState(uint8_t state){
  if(state){
    HAL_GPIO_WritePin(LCD_CSN_GPIO_Port, LCD_CSN_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(LCD_CSN_GPIO_Port, LCD_CSN_Pin, GPIO_PIN_RESET);
  }
}

void ILI9341_DCRSState(uint8_t state){
  if(state){
    HAL_GPIO_WritePin(LCD_DCRS_GPIO_Port, LCD_DCRS_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(LCD_DCRS_GPIO_Port, LCD_DCRS_Pin, GPIO_PIN_RESET);
  }
}

void ILI9341_WriteData(const uint8_t *DataIn, uint32_t DataLength){
  if(HAL_SPI_Transmit(&lcdspi,  (uint8_t*) DataIn, DataLength, LCD_SPI_TIMEOUT) != HAL_OK){
    ILI9341_CSState(GPIO_PIN_SET);
    ILI9341_Error();
  }
}

void ILI9341_ReadData(uint8_t *DataOut, uint32_t DataLength){
  ILI9341_CSState(GPIO_PIN_RESET);
  if(HAL_SPI_Receive(&lcdspi,  (uint8_t*) DataOut, DataLength, LCD_SPI_TIMEOUT) != HAL_OK){
    ILI9341_CSState(GPIO_PIN_SET);
    ILI9341_Error();
  }

}

void ILI9341_Delay(uint32_t Delay){
  HAL_Delay(Delay);
}

static void ILI9341_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */

  LCD_CSN_GPIO_CLK_ENABLE();
  LCD_DCRS_GPIO_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_CSN_GPIO_Port, LCD_CSN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_DCRS_GPIO_Port, LCD_DCRS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LCD_CSN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(LCD_CSN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LCD_DCRS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(LCD_DCRS_GPIO_Port, &GPIO_InitStruct);

}

static void ILI9341_SPI_Init(void)
{
  lcdspi.Instance = LCD_SPI_HANDLE_INSTANCE;
  lcdspi.Init.Mode = SPI_MODE_MASTER;
  lcdspi.Init.Direction = SPI_DIRECTION_2LINES;
  lcdspi.Init.DataSize = SPI_DATASIZE_8BIT;
  lcdspi.Init.CLKPolarity = SPI_POLARITY_LOW;
  lcdspi.Init.CLKPhase = SPI_PHASE_1EDGE;
  lcdspi.Init.NSS = SPI_NSS_SOFT;
  lcdspi.Init.BaudRatePrescaler = LCD_SPI_BAUD_PRESCALER;
  lcdspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
  lcdspi.Init.TIMode = SPI_TIMODE_DISABLE;
  lcdspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  lcdspi.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&lcdspi) != HAL_OK)
  {
    Error_Handler();
  }

}

static void ILI9341_GPIO_DeInit(void){
  HAL_GPIO_DeInit(LCD_CSN_GPIO_Port,LCD_CSN_Pin);
  HAL_GPIO_DeInit(LCD_DCRS_GPIO_Port,LCD_DCRS_Pin);

}

static void ILI9341_SPI_DeInit(void){
  HAL_SPI_DeInit(&lcdspi);
}

static void ILI9341_Error(void)
{
  /* De-initialize the SPI communication BUS */
  ILI9341_HardwareDeInit();
  
  /* Re-Initiaize the SPI communication BUS */
  ILI9341_HardwareInit();
}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==LCD_SPI_HANDLE_INSTANCE)
  {

    SPI_CLK_ENABLE();

    LCD_SPI_GPIO_CLK_ENABLE();

    GPIO_InitStruct.Pin = LCD_SCK_Pin|LCD_MISO_Pin|LCD_MOSI_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = LCD_ALT_FN;
    HAL_GPIO_Init(LCD_SPI_Port, &GPIO_InitStruct);

  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==LCD_SPI_HANDLE_INSTANCE)
  {

    SPI_CLK_DISABLE();


    HAL_GPIO_DeInit(LCD_SPI_Port, LCD_SCK_Pin|LCD_MISO_Pin|LCD_MOSI_Pin);


  }
}
