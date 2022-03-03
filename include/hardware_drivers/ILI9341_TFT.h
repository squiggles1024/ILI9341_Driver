#ifndef ILI9341_TFT_H_
#define ILI9341_TFT_H_

/****************************************************************
 * Includes
 ****************************************************************/
#include <stdint.h>
#include <fonts.h>
/****************************************************************
 * Defines
 ****************************************************************/
#define ILI9341_DUMMYBYTE (0xFF)

/****************************************************************
 * @defgroup: Screen Size Parameters
 ****************************************************************/
//#define SCREEN_WIDTH  (320)
//#define SCREEN_HEIGHT (240)
#define TOTAL_SCREEN_PIXELS  (320U*240U)
#define TOTAL_SCREEN_BYTES   (TOTAL_SCREEN_PIXELS*3)

/****************************************************************
 * @defgroup: D/CX Line States
 ****************************************************************/
#define ILI9341_SEND_DATA     (1U)
#define ILI9341_SEND_COMMAND  (0U)

/****************************************************************
 * Command List, See Pg 83 of https://cdn-shop.adafruit.com/datasheets/ILI9341.pdf
 * @defgroup: Level 1 Command
 ****************************************************************/
#define ILI9341_NOP         (0x00)  // No Operations
#define ILI9341_SWRESET     (0x01)  // Software Reset
#define ILI9341_RDDIDIF     (0x04)  // Read display ID
#define ILI9341_RDDST       (0x09)  // Read display Status
#define ILI9341_RDDPM       (0x0A)  // Read display power mode
#define ILI9341_RDDMADCTL   (0x0B)  // Read display MADCTL
#define ILI9341_RDDCOLMOD   (0x0C)  // Read display pixel format
#define ILI9341_RDDIM       (0x0D)  // Read Display Image Format
#define ILI9341_RDDSM       (0x0E)  // Read Display Signal Mode 
#define ILI9341_RDDSDR      (0x0F)  // Read Display Self-Diagnostic Result
#define ILI9341_SPLIN       (0x10)  // Enter Sleep Mode
#define ILI9341_SLPOUT      (0x11)  // Sleep Out
#define ILI9341_PTLON       (0x12)  // Partial Mode ON 
#define ILI9341_NORON       (0x13)  // Normal Display Mode ON
#define ILI9341_DINVOFF     (0x20)  // Display Inversion OFF
#define ILI9341_DINVON      (0x21)  // Display Inversion ON 
#define ILI9341_GAMSET      (0x26)  // Gamma Set 
#define ILI9341_DISPOFF     (0x28)  // Display OFF
#define ILI9341_DISPON      (0x29)  // Display ON
#define ILI9341_CASET       (0x2A)  // Column Address Set
#define ILI9341_PASET       (0x2B)  // Page Address Set
#define ILI9341_RAMWR       (0x2C)  // Memory Write
#define ILI9341_RGBSET      (0x2D)  // Color Set
#define ILI9341_RAMRD       (0x2E)  // Memory Read
#define ILI9341_PLTAR       (0x30)  // Partial Area
#define ILI9341_VSCRDEF     (0x33)  // Vertical Scrolling Definition
#define ILI9341_TEOFF       (0x34)  // Tearing Effect Line OFF
#define ILI9341_TEON        (0x35)  // Tearing Effect Line ON
#define ILI9341_MADCTL      (0x36)  // Memory Access Control
#define ILI9341_VSCRSADD    (0x37)  // Vertical Scrolling Start Address 
#define ILI9341_IDMOFF      (0x38)  // Idle Mode OFF
#define ILI9341_IDMON       (0x39)  // Idle Mode ON 
#define ILI9341_PIXSET      (0x3A)  // COLMOD: Pixel Format Set
#define ILI9341_Write_Memory_Continue (0x3C)  // Write_Memory_Continue
#define ILI9341_Read_Memory_Continue  (0x3E)  // Read_Memory_Continue
#define ILI9341_Set_Tear_Scanline     (0x44)  // Set_Tear_Scanline 
#define ILI9341_Get_Scanline          (0x45)  // Get_Scanline
#define ILI9341_WRDISBV     (0x51)  // Write Display Brightness
#define ILI9341_RDDISBV     (0x52)  // Read Display Brightness
#define ILI9341_WRCTRLD     (0x53)  // Write CTRL Display
#define ILI9341_RDCTRLD     (0x54)  // Read CTRL Display
#define ILI9341_WRCABC      (0x55)  // Write Content Adaptive Brightness Control 
#define ILI9341_RDCABC      (0x56)  // Read Content Adaptive Brightness Control
#define ILI9341_WCABCMIN    (0x5E)  // Write CABC Minimum Brightness
#define ILI9341_RCABCMIN    (0x5F)  // Read CABC Minimum Brightness
#define ILI9341_RDID1       (0xDA)  // Read ID1
#define ILI9341_RDID2       (0xDB)  // Read ID2
#define ILI9341_RDID3       (0xDC)  // Read ID3

/****************************************************************
 * @defgroup: Level 2 Commands
 ****************************************************************/
#define ILI9341_IFMODE      (0xB0)  // RGB Interface Signal Control
#define ILI9341_FRMCTR1     (0xB1)  // Frame Rate Control (In Normal Mode/Full Colors) 
#define ILI9341_FRMCTR2     (0xB2)  // Frame Rate Control (In Idle Mode/8 colors)
#define ILI9341_FRMCTR3     (0xB3)  // Frame Rate control (In Partial Mode/Full Colors)
#define ILI9341_INVTR       (0xB4)  // Display Inversion Control
#define ILI9341_PRCTR       (0xB5)  // Blanking Porch Control
#define ILI9341_DISCTRL     (0xB6)  // Display Function Control
#define ILI9341_ETMOD       (0xB7)  // Entry Mode Set
#define ILI9341_Backlight_Control_1 (0xB8)  // Backlight Control 1
#define ILI9341_Backlight_Control_2 (0xB9)  // Backlight Control 2
#define ILI9341_Backlight_Control_3 (0xBA)  // Backlight Control 3
#define ILI9341_Backlight_Control_4 (0xBB)  // Backlight Control 4
#define ILI9341_Backlight_Control_5 (0xBC)  // Backlight Control 5
#define ILI9341_Backlight_Control_6 (0xBD)  // Backlight Control 6
#define ILI9341_Backlight_Control_7 (0xBE)  // Backlight Control 7
#define ILI9341_Backlight_Control_8 (0xBF)  // Backlight Control 8
#define ILI9341_PWCTRL_1    (0xC0)  // Power Control 1 
#define ILI9341_PWCTRL_2    (0xC1)  // Power Control 2
#define ILI9341_VMCTRL1     (0xC5)  // VCOM Control 1
#define ILI9341_VMCTRL2     (0xC7)  // VCOM Control 2
#define ILI9341_NVMWR       (0xD0)  // NV Memory Write
#define ILI9341_NVMPKEY     (0xD1)  // NV Memory Protection Key
#define ILI9341_RDNVM       (0xD2)  // NV Memory Status Read 
#define ILI9341_RDID4       (0xD3)  // Read ID4
#define ILI9341_PGAMCTRL    (0xE0)  // Positive Gamma Correction
#define ILI9341_NGAMCTRL    (0xE1)  // Negative Gamma Correction
#define ILI9341_DGAMCTRL1   (0xE2)  // Digital Gamma Control 1 
#define ILI9341_DGAMCTRL2   (0xE3)  // Digital Gamma Control 2
#define ILI9341_IFCTL       (0xF6)  // Interface Control

/****************************************************************
 * @defgroup: Level 2 Commands
 ****************************************************************/
#define ILI9341_PWRCONTROLA        (0xCB)  //
#define ILI9341_PWRCONTROLB        (0xCF)  //
#define ILI9341_TIMINGCONTROLA     (0xE8)  //
#define ILI9341_TIMINGCONTROLB     (0xEA)  //
#define ILI9341_Pwr_on_sequence_control (0xED)  //
#define ILI9341_Enable_3G          (0xF2)  //
#define ILI9341_Pump_ratio_control (0xF7)  //

/****************************************************************
 * Typedefs
 ****************************************************************/

typedef uint8_t ILI9341_Command_t;

//See ILI9341 Manual Page 209
typedef enum{
    Normal = 0x08,
    YMirror = 0x28,
    XMirror = 0x48,
    XYMirror = 0x68,
    XYExchange = 0x88,
    XYExchangeYMirror = 0xA8,
    XYExchangeXMirror = 0xC8,
    XYExchangeXYMirror = 0xE8
}ILI9341_ScreenOrientation_t;

#define SCREEN_DEFAULT_ORIENTATION (XYExchangeXYMirror)

typedef enum{
    small = 0,
    smedium = 1,
    medium = 2,
    large = 3
}ILI9341_FontSize_t;

typedef struct{
    int16_t X;
    int16_t Y;
}ILI9341_Coordinate_t;

typedef struct{
    uint32_t Width;
    uint32_t Height;
    uint32_t ImageLength;
    const uint8_t *ImageData;
}ILI9341_Image_t;

typedef struct{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}ILI9341_Color_t;


/****************************************************************
 * Public Function Declarations
 ****************************************************************/
void ILI9341_Init(void);
void ILI9341_DeInit(void);
void ILI9341_Reset(void);

void ILI9341_SendCommand(ILI9341_Command_t command);
void ILI9341_SendData(const uint8_t *buffer, uint32_t length);
void ILI9341_GetData(uint8_t *OutBuffer, uint32_t length);
void ILI9341_SendByte(const uint8_t byte);
void ILI9341_SetScreenOrientation(ILI9341_ScreenOrientation_t Orientation);
int16_t ILI9341_GetScreenWidth();
int16_t ILI9341_GetScreenHeight();

void ILI9341_DrawPixel(ILI9341_Color_t Color, ILI9341_Coordinate_t Position);
void ILI9341_PrintText(uint8_t *text, sFONT font, ILI9341_Color_t Color);
void ILI9341_DisplayImage(ILI9341_Image_t Image);
void ILI9341_DrawRectangle(uint16_t width, uint16_t height, ILI9341_Coordinate_t Middle, ILI9341_Color_t Color);
void ILI9341_FillSceen(ILI9341_Color_t Color);
void ILI9341_ImageOpen(const uint8_t *BitmapFile, ILI9341_Image_t *Image);
void ILI9341_DrawLine(ILI9341_Color_t Color, ILI9341_Coordinate_t Start, ILI9341_Coordinate_t End);
void ILI9341_DrawVLine(ILI9341_Color_t Color, int16_t StartX, int16_t EndY);
void ILI9341_SetCursor(ILI9341_Coordinate_t Position);
ILI9341_Coordinate_t ILI9341_GetCursor(void);

#endif
