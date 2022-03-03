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

int main_fill_screen_test(void)
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

int main_test_image(){
  HAL_Init();
  SystemClock_Config();
  ILI9341_Init();
  ILI9341_Image_t MyPic;
  ILI9341_ImageOpen(Kawaii_senpai_img_lol, &MyPic);
  ILI9341_DisplayImage(MyPic);
  while(1){
  }
}

int main_test_lines(){
  HAL_Init();
  SystemClock_Config();
  ILI9341_Init();

  uint16_t Width = ILI9341_GetScreenWidth() - 1;
  uint16_t Height = ILI9341_GetScreenHeight() - 1;

  ILI9341_Color_t Color1 = {0,255,0};
  ILI9341_Coordinate_t Start1 = {0,Height/2};
  ILI9341_Coordinate_t End1 = {Width, Height};
  ILI9341_DrawLine(Color1, Start1, End1);
  
  ILI9341_Color_t Color2 = {255,0,0};
  ILI9341_Coordinate_t Start2 = {0,0};
  ILI9341_Coordinate_t End2 = {Width / 2, Height / 2};
  ILI9341_DrawLine(Color2, Start2, End2);

  ILI9341_Color_t Color3 = {0,0,255};
  ILI9341_Coordinate_t Start3 = {0,Height};
  ILI9341_Coordinate_t End3 = {Width,0};
  ILI9341_DrawLine(Color3, Start3, End3);

  ILI9341_Color_t Color4 = {255,0,0};
  ILI9341_Coordinate_t Start4 = {0,Height/2};
  ILI9341_Coordinate_t End4 = {Width,Height/2};
  ILI9341_DrawLine(Color4, Start4, End4);

  ILI9341_Color_t Color5 = {0,255,0};
  ILI9341_DrawVLine(Color5, Width/2, Height);

  while(1);
}

int main(){
  HAL_Init();
  SystemClock_Config();
  ILI9341_Init();
  ILI9341_Color_t Color = {0,255,0};
  uint8_t *MyMsg = "Hello, World, Repeat , Repeat , Repeat , Repeat , Repeat , Repeat , Repeat , Repeat , Repeat , Repeat , Repeat , Repeat , Repeat , Repeat , Repeat , Repeat , Repeat , Repeat ,";
  ILI9341_PrintText(MyMsg,Font12,Color);
  while(1);
}