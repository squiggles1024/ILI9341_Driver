#ifndef ILI9341_HARDWARE_H_
#define ILI9341_HARDWARE_H_
#include "stm32f4xx_hal.h"

#define LCD_CSN_Pin                  GPIO_PIN_12
#define LCD_CSN_GPIO_Port            GPIOB
#define LCD_CSN_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()
#define LCD_CSN_GPIO_CLK_DISABLE()   __HAL_RCC_GPIOB_CLK_DISABLE()

#define LCD_SCK_Pin                  GPIO_PIN_13
#define LCD_MISO_Pin                 GPIO_PIN_14
#define LCD_MOSI_Pin                 GPIO_PIN_15
#define LCD_SPI_Port                 GPIOB
#define LCD_SPI_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()
#define LCD_SPI_GPIO_CLK_DISABLE()   __HAL_RCC_GPIOB_CLK_DISABLE()
#define SPI_CLK_ENABLE()             __HAL_RCC_SPI2_CLK_ENABLE()
#define SPI_CLK_DISABLE()            __HAL_RCC_SPI2_CLK_DISABLE()


#define LCD_DCRS_Pin                  GPIO_PIN_8
#define LCD_DCRS_GPIO_Port            GPIOA
#define LCD_DCRS_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOA_CLK_ENABLE()
#define LCD_DCRS_GPIO_CLK_DISABLE()   __HAL_RCC_GPIOA_CLK_DISABLE()

#define LCD_SPI_HANDLE_INSTANCE       SPI2
#define LCD_SPI_BAUD_PRESCALER        SPI_BAUDRATEPRESCALER_4
#define LCD_ALT_FN                    GPIO_AF5_SPI2

#define LCD_SPI_TIMEOUT              (1000U)

extern SPI_HandleTypeDef lcdspi;

void    ILI9341_HardwareInit(void);
void    ILI9341_Delay(uint32_t Delay);
void    ILI9341_CSState(uint8_t state);
void    ILI9341_DCRSState(uint8_t state);
void    ILI9341_WriteData(const uint8_t *DataIn, uint32_t DataLength);
void    ILI9341_ReadData(uint8_t *DataOut, uint32_t DataLength);
void    ILI9341_HardwareDeInit(void);

#endif