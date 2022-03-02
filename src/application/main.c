/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "rcc.h"
#include "stm32f4xx_hal.h"
#include "ILI9341_TFT.h"
#include "image.h"

int main_test_DrawPixel(void)
{

  HAL_Init();
  SystemClock_Config();
  ILI9341_Init();
  ILI9341_Color_t color = {255,0,0};
  ILI9341_Coordinate_t position = {0,0};
  while (1)
  {
    ILI9341_DrawPixel(color, position);
    if(position.X == 319){
      position.Y = (position.Y + 1) % 240;
    }
    position.X = (position.X + 1) % 320;
    if(position.Y == 239){
      if(color.red == 255){
        color.red = 0;
        color.green = 255;
        color.blue = 0;
      } else if (color.green == 255){
        color.red = 0;
        color.green = 0;
        color.blue = 255;   
      } else {
        color.red = 255;
        color.green = 0;
        color.blue = 0;      
      }
    }
  }
 
}

int main_test_FillScreen(void)
{
  HAL_Init();
  SystemClock_Config();
  ILI9341_Init();
  ILI9341_Color_t color = {255,0,0};

  while (1)
  {
    ILI9341_FillSceen(color);
      if(color.red == 255){
        color.red = 0;
        color.green = 255;
        color.blue = 0;
      } else if (color.green == 255){
        color.red = 0;
        color.green = 0;
        color.blue = 255;   
      } else {
        color.red = 255;
        color.green = 0;
        color.blue = 0;
    }
  }
 
}

int main_DrawRectangleMiddleOut(void)
{
  HAL_Init();
  SystemClock_Config();
  ILI9341_Init();
  ILI9341_Color_t color = {255,0,0};
  ILI9341_Coordinate_t middle = {.X = ILI9341_GetScreenWidth() / 2, .Y = ILI9341_GetScreenHeight() / 2};
  uint16_t width = 0;
  uint16_t height = 0;
  while (1)
  {
    ILI9341_DrawRectangle(width,height,middle,color);
      if(width >= ILI9341_GetScreenWidth() && height >= ILI9341_GetScreenHeight()){
          if(color.red == 255){
            color.red = 0;
            color.green = 255;
            color.blue = 0;
          } else if (color.green == 255){
            color.red = 0;
            color.green = 0;
            color.blue = 255;   
          } else {
            color.red = 255;
            color.green = 0;
            color.blue = 0;
        }
        width = 0;
        height = 0;
      }
      width = width + 16;
      height = height + 12;
  }
}

int main_testRectangleOffScreen(void)
{
  HAL_Init();
  SystemClock_Config();
  ILI9341_Init();
  ILI9341_Color_t color = {255,0,0};
  ILI9341_Coordinate_t middle = {.X = ILI9341_GetScreenWidth() / 2, .Y = ILI9341_GetScreenHeight() / 2};
  uint16_t width = 50;
  uint16_t height = 50;
  while (1)
  {
    ILI9341_DrawRectangle(width,height,middle,color);
    if(color.red == 255){
      color.red = 0;
      color.green = 255;
      color.blue = 0;
    } else if (color.green == 255){
      color.red = 0;
      color.green = 0;
      color.blue = 255;   
    } else {
      color.red = 255;
      color.green = 0;
      color.blue = 0;
    }
    middle.X = middle.X + 4;
    middle.Y = middle.Y + 3;
  }
}

int main(){
  HAL_Init();
  SystemClock_Config();
  ILI9341_Init();
  ILI9341_Image_t MyPic;
  ILI9341_ImageOpen(Kawaii_senpai_img_lol, &MyPic);
  ILI9341_DisplayImage(MyPic);
  while(1){
  }
}