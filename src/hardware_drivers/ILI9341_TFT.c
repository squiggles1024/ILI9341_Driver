#include "ILI9341_TFT.h"
#include "ILI9341_hardware.h"

#define CAST_AND_DEREFERENCE_32bitPtr(x) *((const uint32_t*)(&x))

typedef struct{
    uint8_t S_MSB;
    uint8_t S_LSB;
    uint8_t E_MSB;
    uint8_t E_LSB;
}ILI9341_DrawBounds_t;

typedef enum{
    DimensionsInvalid = 0,
    DimensionsValid = 1,
}ImageDimensionValidity_t;

static void ILI9341_SetCoordinates(ILI9341_Coordinate_t StartCorner, ILI9341_Coordinate_t EndCorner);
static ImageDimensionValidity_t ValidateCoordinates(ILI9341_Coordinate_t StartCorner, ILI9341_Coordinate_t EndCorner);
static int16_t SCREEN_HEIGHT;
static int16_t SCREEN_WIDTH;

/******************************************************************
 *@brief: Initializes the LCD Hardware and prepares it to receive image data
 * See https://cdn-shop.adafruit.com/datasheets/ILI9341.pdf for details regarding commands and data
 * Credit to ST Micro ILI9341.c Driver for initilization sequence
 ******************************************************************/

void ILI9341_Init(void){
    ILI9341_HardwareInit();

    ILI9341_SendCommand(ILI9341_SWRESET);
    ILI9341_Delay(1000);
    
    //Power Control A - Page 195
    ILI9341_SendCommand(ILI9341_PWRCONTROLA);
    ILI9341_SendByte(0x39);
    ILI9341_SendByte(0x2C);
    ILI9341_SendByte(0x00);
    ILI9341_SendByte(0x34);
    ILI9341_SendByte(0x02); 

    //Power Control B - Page 196
    ILI9341_SendCommand(ILI9341_PWRCONTROLB);
    ILI9341_SendByte(0x00);
    ILI9341_SendByte(0xC1);
    ILI9341_SendByte(0x30); 

    //Driver Timing Control A - Page 197
    ILI9341_SendCommand(ILI9341_TIMINGCONTROLA);
    ILI9341_SendByte(0x85); 
    ILI9341_SendByte(0x00);
    ILI9341_SendByte(0x78);

    //Driver Timing Control B - Page 199
    ILI9341_SendCommand(ILI9341_TIMINGCONTROLB);
    ILI9341_SendByte(0x00);
    ILI9341_SendByte(0x00);

    //Power on Sequence Control - Page 200
    ILI9341_SendCommand(ILI9341_Pwr_on_sequence_control);
    ILI9341_SendByte(0x64);
    ILI9341_SendByte(0x03);
    ILI9341_SendByte(0x12);
    ILI9341_SendByte(0x81);

    //Pump Ratio Control - Page 202
    ILI9341_SendCommand(ILI9341_Pump_ratio_control);
    ILI9341_SendByte(0x20);

    //Power Control 1 - Page 178
    ILI9341_SendCommand(ILI9341_PWCTRL_1);
    ILI9341_SendByte(0x10);

    //Power Control 2 - Page 179
    ILI9341_SendCommand(ILI9341_PWCTRL_2);
    ILI9341_SendByte(0x10);

    //VCOM Control 1 - Page 180
    ILI9341_SendCommand(ILI9341_VMCTRL1);
    ILI9341_SendByte(0x45);
    ILI9341_SendByte(0x15);

    //VCOM Control 2 - Page 182
    ILI9341_SendCommand(ILI9341_VMCTRL2);
    ILI9341_SendByte(0x90);

    //Memory Access Control - Page 127
    ILI9341_SendCommand(ILI9341_MADCTL);
    ILI9341_SendByte(0x30);

    //Pixel Format Set - Page 134
    ILI9341_SendCommand(ILI9341_PIXSET);
    ILI9341_SendByte(0x66);

    //Frame Rate Control (In Normal Mode/Full Colors) - Page 155
    ILI9341_SendCommand(ILI9341_FRMCTR1);
    ILI9341_SendByte(0x00);
    ILI9341_SendByte(0x18);

    // Display Function Control - Page 164
    ILI9341_SendCommand(ILI9341_DISCTRL);
    ILI9341_SendByte(0x08);
    ILI9341_SendByte(0x82);
    ILI9341_SendByte(0x27);

    //Enable 3G - Page 201
    ILI9341_SendCommand(ILI9341_Enable_3G);
    ILI9341_SendByte(0x00);

    //Gamma Set - Page 107
    ILI9341_SendCommand(ILI9341_GAMSET);
    ILI9341_SendByte(0x01);

    //Positive Gamma Correction - Page 188
    ILI9341_SendCommand(ILI9341_PGAMCTRL);
    ILI9341_SendByte(0x0F);
    ILI9341_SendByte(0x29);
    ILI9341_SendByte(0x24);
    ILI9341_SendByte(0x0C);
    ILI9341_SendByte(0x0E);
    ILI9341_SendByte(0x09);
    ILI9341_SendByte(0x4E);
    ILI9341_SendByte(0x78);
    ILI9341_SendByte(0x3C);
    ILI9341_SendByte(0x09);
    ILI9341_SendByte(0x13);
    ILI9341_SendByte(0x05);
    ILI9341_SendByte(0x17);
    ILI9341_SendByte(0x11);
    ILI9341_SendByte(0x00);

    //Negative Gamma Correction - Page 189
    ILI9341_SendCommand(ILI9341_NGAMCTRL);
    ILI9341_SendByte(0x00);
    ILI9341_SendByte(0x16);
    ILI9341_SendByte(0x1B);
    ILI9341_SendByte(0x04);
    ILI9341_SendByte(0x11);
    ILI9341_SendByte(0x07);
    ILI9341_SendByte(0x31);
    ILI9341_SendByte(0x33);
    ILI9341_SendByte(0x42);
    ILI9341_SendByte(0x05);
    ILI9341_SendByte(0x0C);
    ILI9341_SendByte(0x0A);
    ILI9341_SendByte(0x28);
    ILI9341_SendByte(0x2F);
    ILI9341_SendByte(0x0F);

    //Sleep Out - Page 101
    ILI9341_SendCommand(ILI9341_SLPOUT);
    ILI9341_Delay(150);

    //Display ON - Page 109
    ILI9341_SendCommand(0x29);

    //Screen Orientation - Page 209
    ILI9341_SetScreenOrientation(SCREEN_DEFAULT_ORIENTATION);
}

void ILI9341_DeInit(void){
    ILI9341_SendCommand(ILI9341_SWRESET);
    ILI9341_HardwareDeInit();
}

void ILI9341_Reset(void){
    ILI9341_SendCommand(ILI9341_SWRESET);
}

void ILI9341_SendCommand(ILI9341_Command_t Command){
    ILI9341_DCRSState(ILI9341_SEND_COMMAND);
    ILI9341_CSState(0);
    ILI9341_WriteData(&Command,1);
    ILI9341_CSState(1);
}

void ILI9341_SendData(const uint8_t *OutDataBuffer, uint32_t length){
    ILI9341_DCRSState(ILI9341_SEND_DATA);
    ILI9341_CSState(0);
    ILI9341_WriteData(OutDataBuffer,length);
    ILI9341_CSState(1);
}

void ILI9341_SendByte(const uint8_t byte){
    ILI9341_DCRSState(ILI9341_SEND_DATA);
    ILI9341_CSState(0);
    ILI9341_WriteData(&byte,1);
    ILI9341_CSState(1);
}

void ILI9341_GetData(uint8_t *InDataBuffer, uint32_t length){
    ILI9341_DCRSState(ILI9341_SEND_DATA);
    ILI9341_CSState(0);
    ILI9341_ReadData(InDataBuffer,length);
    ILI9341_CSState(1);
}

/************************************************
* Fix Later: Change screen height/width based upon orientation
************************************************/
void ILI9341_SetScreenOrientation(ILI9341_ScreenOrientation_t Orientation){
    ILI9341_SendCommand(ILI9341_MADCTL);
    ILI9341_SendByte(Orientation);
    SCREEN_HEIGHT = 240;
    SCREEN_WIDTH = 320;
}

void ILI9341_DrawPixel(ILI9341_Color_t Color, ILI9341_Coordinate_t Position){
    ILI9341_SetCoordinates(Position,Position);
    ILI9341_SendCommand(ILI9341_RAMWR);
    ILI9341_SendData((uint8_t*)&Color, 3);
}

void ILI9341_FillSceen(ILI9341_Color_t Color){
    ILI9341_Coordinate_t CoordinateStart = {.X = 0, .Y = 0};
    ILI9341_Coordinate_t CoordinateEnd = {.X = SCREEN_WIDTH-1, .Y = SCREEN_HEIGHT-1};
    ILI9341_SetCoordinates(CoordinateStart, CoordinateEnd);
    ILI9341_SendCommand(ILI9341_RAMWR);
    for(uint32_t i = 0; i < TOTAL_SCREEN_BYTES; i++){
        ILI9341_SendData((uint8_t*)&Color, 3);
    }
}

void ILI9341_DrawRectangle(uint16_t width, uint16_t height, ILI9341_Coordinate_t Middle, ILI9341_Color_t Color){

    ILI9341_Coordinate_t CoordinateStart = {.X = Middle.X - width/2, .Y = Middle.Y - height/2};
    ILI9341_Coordinate_t CoordinateEnd = {.X = Middle.X + width/2, .Y = Middle.Y + height/2};

    if(ValidateCoordinates(CoordinateStart,CoordinateEnd) == DimensionsInvalid){
        return;
    }

    if(CoordinateStart.X < 0){
        CoordinateStart.X = 0; //One pixel off screen
    }

    if(CoordinateStart.Y < 0){
        CoordinateStart.Y = 0;
    }


    if(CoordinateEnd.X > SCREEN_WIDTH - 1){
        CoordinateEnd.X = SCREEN_WIDTH - 1; //One pixel off screen
    }

    if(CoordinateStart.Y > SCREEN_HEIGHT - 1){
        CoordinateStart.Y = SCREEN_HEIGHT - 1;
    }

    ILI9341_SetCoordinates(CoordinateStart, CoordinateEnd);
    uint32_t TotalBytes = width*height*3;
    ILI9341_SendCommand(ILI9341_RAMWR);
    for(uint32_t i = 0; i < TotalBytes; i++){
        ILI9341_SendData((uint8_t*)&Color, 3);
    }
}

static void ILI9341_SetCoordinates(ILI9341_Coordinate_t StartCorner, ILI9341_Coordinate_t EndCorner){
    ILI9341_DrawBounds_t Coordinate = {.S_MSB = StartCorner.X >> 8, .S_LSB = StartCorner.X, .E_MSB = EndCorner.X >> 8, .E_LSB = EndCorner.X};

    ILI9341_SendCommand(ILI9341_CASET);
    ILI9341_SendData((uint8_t*)&Coordinate,4);
    Coordinate.S_MSB = StartCorner.Y >> 8;
    Coordinate.S_LSB = StartCorner.Y;
    Coordinate.E_MSB = EndCorner.Y >> 8;
    Coordinate.E_LSB = EndCorner.Y;
    ILI9341_SendCommand(ILI9341_PASET);
    ILI9341_SendData((uint8_t*)&Coordinate,4);
}

static ImageDimensionValidity_t ValidateCoordinates(ILI9341_Coordinate_t StartCorner, ILI9341_Coordinate_t EndCorner){
    //Entire Image off screen
    if(EndCorner.X < 0 || EndCorner.Y < 0){
        return DimensionsInvalid;
    }

    //Entire Image off screen
    if(StartCorner.X >= SCREEN_WIDTH || StartCorner.Y >= SCREEN_HEIGHT){
        return DimensionsInvalid;
    }

    //Start corner exceeds end corner
    if(StartCorner.X > EndCorner.X || StartCorner.Y > EndCorner.Y){
        return DimensionsInvalid;
    }
    return DimensionsValid;
}

void ILI9341_DisplayImage(ILI9341_Image_t Image){
    ILI9341_Coordinate_t CoordinateStart = {.0, .Y = 0};
    ILI9341_Coordinate_t CoordinateEnd = {.X = 319, .Y = 179};
    ILI9341_SetCoordinates(CoordinateStart,CoordinateEnd);
    ILI9341_SendCommand(ILI9341_RAMWR);
    for(uint32_t i = Image.ImageLength - 1; i > 0x36; i--){
        ILI9341_SendByte(Image.ImageData[i]);
    }
}

inline int16_t ILI9341_GetScreenWidth(){
    return SCREEN_WIDTH;
}

inline int16_t ILI9341_GetScreenHeight(){
   return SCREEN_HEIGHT;
}

void ILI9341_ImageOpen(const uint8_t *BitmapFile, ILI9341_Image_t *Image){
  Image->ImageLength = CAST_AND_DEREFERENCE_32bitPtr(BitmapFile[0x02]);
  Image->Width = CAST_AND_DEREFERENCE_32bitPtr(BitmapFile[0x12]);
  Image->Height = CAST_AND_DEREFERENCE_32bitPtr(BitmapFile[0x16]);
  Image->ImageData = (&BitmapFile[0x36]);
}