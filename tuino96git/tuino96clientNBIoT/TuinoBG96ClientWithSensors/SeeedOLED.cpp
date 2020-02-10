/**
 * @file SeeedOLED.cpp
 * @description Functions to drive the Seeed OLED display
 * @author FrankieChu
 * @reworker htemizel
 * @licence MIT licence
 *
 * Find out more about WIOTS:
 * Company: https://wireless-iot-solutions.com/wp/
 * GitHub:  https://github.com/WirelessIoTSolutions/
 */
#include "Wire.h"
#include "SeeedOLED.h"

#include <avr/pgmspace.h>

// funtion to setup the oled display with the necessary configs for easy use
void SeeedOLED::setupOLED(void)
{
    init();               //initialze SEEED OLED display
    clearDisplay();       //clear the screen and set start position to top left corner
    setNormalDisplay();   //Set display to normal mode (i.e non-inverse mode)
    setHorizontalMode();  //Set addressing mode to Page Mode
}

// use this function to print on the OLED Screen
//second and third parameters are Row and Column of where to print it
void SeeedOLED::printOLED(int value, unsigned char Row, unsigned char Column)
{
    setTextXY(Row, Column);
    String printString = String(value);
    this->putString(printString.c_str());
}

// use this function to print on the OLED Screen
//second and third parameters are Row and Column of where to print it
void SeeedOLED::printOLED(float value, unsigned char Row, unsigned char Column)
{
    setTextXY(Row, Column);
    String printString = String(value);
    this->putString(printString.c_str());
}

// use this function to print on the OLED Screen
//second and third parameters are Row and Column of where to print it
void SeeedOLED::printOLED(String value, unsigned char Row, unsigned char Column)
{
    setTextXY(Row, Column);
    String printString = value;
    this->putString(printString.c_str());
}

// use this function to print on the OLED Screen
//second and third parameters are Row and Column of where to print it
void SeeedOLED::printOLED(char value[], unsigned char Row, unsigned char Column)
{
    setTextXY(Row, Column);
    String printString = String(value);
    this->putString(printString.c_str());
}

// use this function to print on the OLED Screen
//second and third parameters are Row and Column of where to print it
void SeeedOLED::printOLED(double value, unsigned char Row, unsigned char Column)
{
    setTextXY(Row, Column);
    String printString = String(value);
    this->putString(printString.c_str());
}

// use this function to print on the OLED Screen
//second and third parameters are Row and Column of where to print it
void SeeedOLED::clearLine(unsigned char Row)
{
    unsigned char Column = 0;
    setTextXY(Row, Column);
    String printString = "                ";
    this->putString(printString.c_str());
    delay(500);
}


// 8x8 Font ASCII 32 - 127 Implemented
// Users can modify this to support more characters(glyphs)
// BasicFont is placed in code memory.
// This font be freely used without any restriction(It is placed in public domain)
const unsigned char BasicFont[][8] PROGMEM=
{
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x5F,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x07,0x00,0x07,0x00,0x00,0x00},
  {0x00,0x14,0x7F,0x14,0x7F,0x14,0x00,0x00},
  {0x00,0x24,0x2A,0x7F,0x2A,0x12,0x00,0x00},
  {0x00,0x23,0x13,0x08,0x64,0x62,0x00,0x00},
  {0x00,0x36,0x49,0x55,0x22,0x50,0x00,0x00},
  {0x00,0x00,0x05,0x03,0x00,0x00,0x00,0x00},
  {0x00,0x1C,0x22,0x41,0x00,0x00,0x00,0x00},
  {0x00,0x41,0x22,0x1C,0x00,0x00,0x00,0x00},
  {0x00,0x08,0x2A,0x1C,0x2A,0x08,0x00,0x00},
  {0x00,0x08,0x08,0x3E,0x08,0x08,0x00,0x00},
  {0x00,0xA0,0x60,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x08,0x08,0x08,0x08,0x08,0x00,0x00},
  {0x00,0x60,0x60,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x20,0x10,0x08,0x04,0x02,0x00,0x00},
  {0x00,0x3E,0x51,0x49,0x45,0x3E,0x00,0x00},
  {0x00,0x00,0x42,0x7F,0x40,0x00,0x00,0x00},
  {0x00,0x62,0x51,0x49,0x49,0x46,0x00,0x00},
  {0x00,0x22,0x41,0x49,0x49,0x36,0x00,0x00},
  {0x00,0x18,0x14,0x12,0x7F,0x10,0x00,0x00},
  {0x00,0x27,0x45,0x45,0x45,0x39,0x00,0x00},
  {0x00,0x3C,0x4A,0x49,0x49,0x30,0x00,0x00},
  {0x00,0x01,0x71,0x09,0x05,0x03,0x00,0x00},
  {0x00,0x36,0x49,0x49,0x49,0x36,0x00,0x00},
  {0x00,0x06,0x49,0x49,0x29,0x1E,0x00,0x00},
  {0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00},
  {0x00,0x00,0xAC,0x6C,0x00,0x00,0x00,0x00},
  {0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00},
  {0x00,0x14,0x14,0x14,0x14,0x14,0x00,0x00},
  {0x00,0x41,0x22,0x14,0x08,0x00,0x00,0x00},
  {0x00,0x02,0x01,0x51,0x09,0x06,0x00,0x00},
  {0x00,0x32,0x49,0x79,0x41,0x3E,0x00,0x00},
  {0x00,0x7E,0x09,0x09,0x09,0x7E,0x00,0x00},
  {0x00,0x7F,0x49,0x49,0x49,0x36,0x00,0x00},
  {0x00,0x3E,0x41,0x41,0x41,0x22,0x00,0x00},
  {0x00,0x7F,0x41,0x41,0x22,0x1C,0x00,0x00},
  {0x00,0x7F,0x49,0x49,0x49,0x41,0x00,0x00},
  {0x00,0x7F,0x09,0x09,0x09,0x01,0x00,0x00},
  {0x00,0x3E,0x41,0x41,0x51,0x72,0x00,0x00},
  {0x00,0x7F,0x08,0x08,0x08,0x7F,0x00,0x00},
  {0x00,0x41,0x7F,0x41,0x00,0x00,0x00,0x00},
  {0x00,0x20,0x40,0x41,0x3F,0x01,0x00,0x00},
  {0x00,0x7F,0x08,0x14,0x22,0x41,0x00,0x00},
  {0x00,0x7F,0x40,0x40,0x40,0x40,0x00,0x00},
  {0x00,0x7F,0x02,0x0C,0x02,0x7F,0x00,0x00},
  {0x00,0x7F,0x04,0x08,0x10,0x7F,0x00,0x00},
  {0x00,0x3E,0x41,0x41,0x41,0x3E,0x00,0x00},
  {0x00,0x7F,0x09,0x09,0x09,0x06,0x00,0x00},
  {0x00,0x3E,0x41,0x51,0x21,0x5E,0x00,0x00},
  {0x00,0x7F,0x09,0x19,0x29,0x46,0x00,0x00},
  {0x00,0x26,0x49,0x49,0x49,0x32,0x00,0x00},
  {0x00,0x01,0x01,0x7F,0x01,0x01,0x00,0x00},
  {0x00,0x3F,0x40,0x40,0x40,0x3F,0x00,0x00},
  {0x00,0x1F,0x20,0x40,0x20,0x1F,0x00,0x00},
  {0x00,0x3F,0x40,0x38,0x40,0x3F,0x00,0x00},
  {0x00,0x63,0x14,0x08,0x14,0x63,0x00,0x00},
  {0x00,0x03,0x04,0x78,0x04,0x03,0x00,0x00},
  {0x00,0x61,0x51,0x49,0x45,0x43,0x00,0x00},
  {0x00,0x7F,0x41,0x41,0x00,0x00,0x00,0x00},
  {0x00,0x02,0x04,0x08,0x10,0x20,0x00,0x00},
  {0x00,0x41,0x41,0x7F,0x00,0x00,0x00,0x00},
  {0x00,0x04,0x02,0x01,0x02,0x04,0x00,0x00},
  {0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00},
  {0x00,0x01,0x02,0x04,0x00,0x00,0x00,0x00},
  {0x00,0x20,0x54,0x54,0x54,0x78,0x00,0x00},
  {0x00,0x7F,0x48,0x44,0x44,0x38,0x00,0x00},
  {0x00,0x38,0x44,0x44,0x28,0x00,0x00,0x00},
  {0x00,0x38,0x44,0x44,0x48,0x7F,0x00,0x00},
  {0x00,0x38,0x54,0x54,0x54,0x18,0x00,0x00},
  {0x00,0x08,0x7E,0x09,0x02,0x00,0x00,0x00},
  {0x00,0x18,0xA4,0xA4,0xA4,0x7C,0x00,0x00},
  {0x00,0x7F,0x08,0x04,0x04,0x78,0x00,0x00},
  {0x00,0x00,0x7D,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x80,0x84,0x7D,0x00,0x00,0x00,0x00},
  {0x00,0x7F,0x10,0x28,0x44,0x00,0x00,0x00},
  {0x00,0x41,0x7F,0x40,0x00,0x00,0x00,0x00},
  {0x00,0x7C,0x04,0x18,0x04,0x78,0x00,0x00},
  {0x00,0x7C,0x08,0x04,0x7C,0x00,0x00,0x00},
  {0x00,0x38,0x44,0x44,0x38,0x00,0x00,0x00},
  {0x00,0xFC,0x24,0x24,0x18,0x00,0x00,0x00},
  {0x00,0x18,0x24,0x24,0xFC,0x00,0x00,0x00},
  {0x00,0x00,0x7C,0x08,0x04,0x00,0x00,0x00},
  {0x00,0x48,0x54,0x54,0x24,0x00,0x00,0x00},
  {0x00,0x04,0x7F,0x44,0x00,0x00,0x00,0x00},
  {0x00,0x3C,0x40,0x40,0x7C,0x00,0x00,0x00},
  {0x00,0x1C,0x20,0x40,0x20,0x1C,0x00,0x00},
  {0x00,0x3C,0x40,0x30,0x40,0x3C,0x00,0x00},
  {0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00},
  {0x00,0x1C,0xA0,0xA0,0x7C,0x00,0x00,0x00},
  {0x00,0x44,0x64,0x54,0x4C,0x44,0x00,0x00},
  {0x00,0x08,0x36,0x41,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x41,0x36,0x08,0x00,0x00,0x00,0x00},
  {0x00,0x02,0x01,0x01,0x02,0x01,0x00,0x00},
  {0x00,0x02,0x05,0x05,0x02,0x00,0x00,0x00} 
};

void SeeedOLED::init(void)
{
    sendCommand(SeeedOLED_Display_Off_Cmd); 	//display off
    delay(5); 
    sendCommand(SeeedOLED_Display_On_Cmd); 	//display on
    delay(5); 
    sendCommand(SeeedOLED_Normal_Display_Cmd);  //Set Normal Display (default)
}

void SeeedOLED::sendCommand(unsigned char command)
{
  Wire.beginTransmission(SeeedOLED_Address); // begin I2C communication
#if defined(ARDUINO) && ARDUINO >= 100
  Wire.write(SeeedOLED_Command_Mode);	     // Set OLED Command mode
  Wire.write(command);
#else
  Wire.send(SeeedOLED_Command_Mode);	     // Set OLED Command mode
  Wire.send(command);
#endif
  Wire.endTransmission();    		     // End I2C communication
}

void SeeedOLED::setBrightness(unsigned char Brightness)
{
   sendCommand(SeeedOLED_Set_Brightness_Cmd);
   sendCommand(Brightness);
}

void SeeedOLED::setHorizontalMode()
{
    addressingMode = HORIZONTAL_MODE;
    sendCommand(0x20); 			//set addressing mode
    sendCommand(0x00); 			//set horizontal addressing mode
}

void SeeedOLED::setPageMode()
{
    addressingMode = PAGE_MODE;
    sendCommand(0x20); 			//set addressing mode
    sendCommand(0x02); 			//set page addressing mode
}

void SeeedOLED::setTextXY(unsigned char Row, unsigned char Column)
{
    sendCommand(0xB0 + Row); 			//set page address
    sendCommand(0x00 + (8*Column & 0x0F)); 	//set column lower address
    sendCommand(0x10 + ((8*Column>>4)&0x0F)); 	//set column higher address
}

void SeeedOLED::clearDisplay()
{
  unsigned char i,j;
  sendCommand(SeeedOLED_Display_Off_Cmd); 	//display off
  for(j=0;j<8;j++)
  {	
    setTextXY(j,0);    
    {
      for(i=0;i<16;i++)  //clear all columns
      {
        putChar(' ');    
      }
    }
  }
  sendCommand(SeeedOLED_Display_On_Cmd); 	//display on
  setTextXY(0,0);    
}

void SeeedOLED::sendData(unsigned char Data)
{
     Wire.beginTransmission(SeeedOLED_Address); // begin I2C transmission
#if defined(ARDUINO) && ARDUINO >= 100
     Wire.write(SeeedOLED_Data_Mode);            // data mode
     Wire.write(Data);
#else
     Wire.send(SeeedOLED_Data_Mode);            // data mode
     Wire.send(Data);
#endif
     Wire.endTransmission();                    // stop I2C transmission
}

void SeeedOLED::putChar(unsigned char C)
{
    if(C < 32 || C > 127) //Ignore non-printable ASCII characters. This can be modified for multilingual font.
    {
    C=' '; //Space
    }	
    unsigned char i=0;
    for(i=0;i<8;i++)
    {
       //read bytes from code memory
       sendData(pgm_read_byte(&BasicFont[C-32][i])); //font array starts at 0, ASCII starts at 32. Hence the translation
    }
}

void SeeedOLED::putString(const char *String)
{
    unsigned char i=0;
    while(String[i])
    {
        putChar(String[i]);     
        i++;
    }
}

unsigned char SeeedOLED::putNumber(long long_num)
{
  unsigned char char_buffer[10]="";
  unsigned char i = 0;
  unsigned char f = 0;

  if (long_num < 0) 
  {
    f=1;
    putChar('-');
    long_num = -long_num;
  } 
  else if (long_num == 0) 
  {
    f=1;
    putChar('0');
    return f;
  } 

  while (long_num > 0) 
  {
    char_buffer[i++] = long_num % 10;
    long_num /= 10;
  }

  f=f+i;
  for(; i > 0; i--)
  {
    putChar('0'+ char_buffer[i - 1]);
  }
  return f;
}

unsigned char SeeedOLED::putFloat(float floatNumber,unsigned char decimal)
{
  unsigned int temp=0;
  float decy=0.0;
  float rounding = 0.5;
  unsigned char f=0;
  if(floatNumber<0.0)
  {
    putString("-");
    floatNumber = -floatNumber;
    f +=1;
  }
  for (unsigned char i=0; i<decimal; ++i)
  {
    rounding /= 10.0;
  }
    floatNumber += rounding;
  
  temp = floatNumber;
  f += putNumber(temp);
  if(decimal>0)
  {
    putChar('.');
    f +=1;
 }
  decy = floatNumber-temp;//decimal part, 
  for(unsigned char i=0;i<decimal;i++)//4 
  {
    decy *=10;// for the next decimal
    temp = decy;//get the decimal
    putNumber(temp);
    decy -= temp;
  }
  f +=decimal;
  return f;
}
unsigned char SeeedOLED::putFloat(float floatNumber)
{
  unsigned char decimal=2;
  unsigned int temp=0;
  float decy=0.0;
  float rounding = 0.5;
  unsigned char f=0;
  if(floatNumber<0.0)
  {
    putString("-");
    floatNumber = -floatNumber;
    f +=1;
  }
  for (unsigned char i=0; i<decimal; ++i)
  {
    rounding /= 10.0;
  }
    floatNumber += rounding;
  
  temp = floatNumber;
  f += putNumber(temp);
  if(decimal>0)
  {
    putChar('.');
    f +=1;
 }
  decy = floatNumber-temp;//decimal part, 
  for(unsigned char i=0;i<decimal;i++)//4 
  {
    decy *=10;// for the next decimal
    temp = decy;//get the decimal
    putNumber(temp);
    decy -= temp;
  }
  f +=decimal;
  return f;
}

void SeeedOLED::drawBitmap(unsigned char *bitmaparray,int bytes)
{
  char localAddressMode = addressingMode;
  if(addressingMode != HORIZONTAL_MODE)
  {
      //Bitmap is drawn in horizontal mode 	
      setHorizontalMode();
  }

  for(int i=0;i<bytes;i++)
  {
      sendData(pgm_read_byte(&bitmaparray[i]));
  }

  if(localAddressMode == PAGE_MODE)
  {
     //If pageMode was used earlier, restore it.
     setPageMode(); 
  }
  
}

void SeeedOLED::setHorizontalScrollProperties(bool direction,unsigned char startPage, unsigned char endPage, unsigned char scrollSpeed)
{
/*
Use the following defines for 'direction' :

 Scroll_Left			
 Scroll_Right			

Use the following defines for 'scrollSpeed' :

 Scroll_2Frames		
 Scroll_3Frames
 Scroll_4Frames
 Scroll_5Frames	
 Scroll_25Frames
 Scroll_64Frames
 Scroll_128Frames
 Scroll_256Frames

*/

   if(Scroll_Right == direction)
   {
        //Scroll Right
        sendCommand(0x26);
   }
   else
   {
        //Scroll Left  
        sendCommand(0x27);

   }
    sendCommand(0x00);
    sendCommand(startPage);
    sendCommand(scrollSpeed);
    sendCommand(endPage);
    sendCommand(0x00);
    sendCommand(0xFF);
}

void SeeedOLED::activateScroll()
{
    sendCommand(SeeedOLED_Activate_Scroll_Cmd);
}

void SeeedOLED::deactivateScroll()
{
    sendCommand(SeeedOLED_Dectivate_Scroll_Cmd);
}

void SeeedOLED::setNormalDisplay()
{
    sendCommand(SeeedOLED_Normal_Display_Cmd);
}

void SeeedOLED::setInverseDisplay()
{
    sendCommand(SeeedOLED_Inverse_Display_Cmd);
}

void SeeedOLED::printMM1Logo()
{
  printOLED("/", 0, 0);
  printOLED("\\", 1, 0);
  printOLED("/", 2, 0);
  printOLED("\\", 3, 0);
  printOLED("/", 4, 0);
  printOLED("\\", 5, 0);
  printOLED("/", 6, 0);
  printOLED("\\", 7, 0);
  delay(100);

  printOLED(" \\", 0, 0);
  printOLED(" /", 1, 0);
  printOLED(" \\", 2, 0);
  printOLED(" /", 3, 0);
  printOLED(" \\", 4, 0);
  printOLED(" /", 5, 0);
  printOLED(" \\", 6, 0);
  printOLED(" /", 7, 0);
  delay(100);

  printOLED("  /", 0, 0);
  printOLED("  \\", 1, 0);
  printOLED(" O/", 2, 0);
  printOLED(" O\\", 3, 0);
  printOLED(" O/", 4, 0);
  printOLED(" O\\", 5, 0);
  printOLED("  /", 6, 0);
  printOLED("  \\", 7, 0);
  delay(100);

  printOLED("   \\", 0, 0);
  printOLED("   /", 1, 0);
  printOLED(" O \\", 2, 0);
  printOLED(" O /", 3, 0);
  printOLED(" O \\", 4, 0);
  printOLED(" OO/", 5, 0);
  printOLED("   \\", 6, 0);
  printOLED("   /", 7, 0);
  delay(100);

  printOLED("    /", 0, 0);
  printOLED("    \\", 1, 0);
  printOLED(" O O/", 2, 0);
  printOLED(" O O\\", 3, 0);
  printOLED(" O O/", 4, 0);
  printOLED(" OOO\\", 5, 0);
  printOLED("    /", 6, 0);
  printOLED("    \\", 7, 0);
  delay(100);

  printOLED("     \\", 0, 0);
  printOLED("     /", 1, 0);
  printOLED(" O O \\", 2, 0);
  printOLED(" O O /", 3, 0);
  printOLED(" O O \\", 4, 0);
  printOLED(" OOOO/", 5, 0);
  printOLED("     \\", 6, 0);
  printOLED("     /", 7, 0);
  delay(100);

  printOLED("     /", 0, 0);
  printOLED("     \\", 1, 0);
  printOLED(" O O /", 2, 0);
  printOLED(" O O \\", 3, 0);
  printOLED(" O O /", 4, 0);
  printOLED(" OOOO\\", 5, 0);
  printOLED("     /", 6, 0);
  printOLED("     \\", 7, 0);
  delay(100);

  printOLED("      \\", 0, 0);
  printOLED("      /", 1, 0);
  printOLED(" O O O\\", 2, 0);
  printOLED(" O O O/", 3, 0);
  printOLED(" O O O\\", 4, 0);
  printOLED(" OOOOO/", 5, 0);
  printOLED("      \\", 6, 0);
  printOLED("      /", 7, 0);
  delay(100);

  printOLED("       /", 0, 0);
  printOLED("       \\", 1, 0);
  printOLED(" O O O /", 2, 0);
  printOLED(" O O O \\", 3, 0);
  printOLED(" O O O /", 4, 0);
  printOLED(" OOOOO \\", 5, 0);
  printOLED("       /", 6, 0);
  printOLED("       \\", 7, 0);
  delay(100);

  printOLED("        \\", 0, 0);
  printOLED("        /", 1, 0);
  printOLED(" O O O  \\", 2, 0);
  printOLED(" O O O  /", 3, 0);
  printOLED(" O O O  \\", 4, 0);
  printOLED(" OOOOO  /", 5, 0);
  printOLED("        \\", 6, 0);
  printOLED("        /", 7, 0);
  delay(100);

  printOLED("         /", 0, 0);
  printOLED("         \\", 1, 0);
  printOLED(" O O O   /", 2, 0);
  printOLED(" O O O   \\", 3, 0);
  printOLED(" O O O   /", 4, 0);
  printOLED(" OOOOO   \\", 5, 0);
  printOLED("         /", 6, 0);
  printOLED("         \\", 7, 0);
  delay(100);

  printOLED("          \\", 0, 0);
  printOLED("          /", 1, 0);
  printOLED(" O O O   O\\", 2, 0);
  printOLED(" O O O   O/", 3, 0);
  printOLED(" O O O   O\\", 4, 0);
  printOLED(" OOOOO   O/", 5, 0);
  printOLED("          \\", 6, 0);
  printOLED("          /", 7, 0);
  delay(100);

  printOLED("           /", 0, 0);
  printOLED("           \\", 1, 0);
  printOLED(" O O O   O /", 2, 0);
  printOLED(" O O O   O \\", 3, 0);
  printOLED(" O O O   O /", 4, 0);
  printOLED(" OOOOO   O \\", 5, 0);
  printOLED("           /", 6, 0);
  printOLED("           \\", 7, 0);
  delay(100);

  printOLED("            \\", 0, 0);
  printOLED("            /", 1, 0);
  printOLED(" O O O   O  \\", 2, 0);
  printOLED(" O O O   O  /", 3, 0);
  printOLED(" O O O   O  \\", 4, 0);
  printOLED(" OOOOO   O  /", 5, 0);
  printOLED("            \\", 6, 0);
  printOLED("            /", 7, 0);
  delay(100);

  printOLED("             /", 0, 0);
  printOLED("             \\", 1, 0);
  printOLED(" O O O   O   /", 2, 0);
  printOLED(" O O O   O   \\", 3, 0);
  printOLED(" O O O   O   /", 4, 0);
  printOLED(" OOOOO   O   \\", 5, 0);
  printOLED("             /", 6, 0);
  printOLED("             \\", 7, 0);
  delay(100);

  printOLED("              \\", 0, 0);
  printOLED("              /", 1, 0);
  printOLED(" O O O   O   O\\", 2, 0);
  printOLED(" O O O   O    /", 3, 0);
  printOLED(" O O O   O    \\", 4, 0);
  printOLED(" OOOOO   O    /", 5, 0);
  printOLED("              \\", 6, 0);
  printOLED("              /", 7, 0);
  delay(100);

  printOLED("               /", 0, 0);
  printOLED("               \\", 1, 0);
  printOLED(" O O O   O   OO/", 2, 0);
  printOLED(" O O O   O    O\\", 3, 0);
  printOLED(" O O O   O    O/", 4, 0);
  printOLED(" OOOOO   O    O\\", 5, 0);
  printOLED("               /", 6, 0);
  printOLED("               \\", 7, 0);
  delay(100);
  
  printOLED("                ", 0, 0);
  printOLED("                ", 1, 0);
  printOLED(" O O O   O  OOOO", 2, 0);
  printOLED(" O O O   O  O   ", 3, 0);
  printOLED(" O O O   O  OOOO", 4, 0);
  printOLED(" O O O   O     O", 5, 0);
  printOLED(" OOOOO   O  OOOO", 6, 0);
  printOLED("                ", 7, 0);
  delay(100);
}
