/*ReceiveData patter
  ------------------
  xPos>int;yPos:int</
  ------------------
*/


// OLED Definitions and imports
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
#define DELAY
Adafruit_SSD1306 display(OLED_RESET);

//----------- Incoming data setup
char chByte = 0;  // incoming serial byte
String strInput = "xPos>int;yPos:int</";    // buffer for incoming packet
String xVal = "0";
String yVal = "0";

void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);

  //----------------- OLED Setup
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);     // initialize with the I2C addr 0x3C (for the 128x64)
  display.clearDisplay();   // clears the screen and buffer
  display.setTextColor(WHITE);
}

void loop()
{

  //--------------------------------Reading from Phone section
  while (Serial.available() > 0)
  {
    //get incoming bytes
    chByte = Serial.read();
    if (chByte == '/') {
      //means one stream end received

      posSegmenter(strInput);
      //reset strInput
      strInput = "";
    } else {
      strInput += chByte;
    }
  }


  

}

void posSegmenter(String incomingBufferString) {

  //data parsing
  int indexOfAr = incomingBufferString.indexOf(">");
  int indexOfCol = incomingBufferString.indexOf(":");
  int indexOfSlash = incomingBufferString.indexOf("/");
  int indexOfSemiCol = incomingBufferString.indexOf(";");
  int indexOfBckAr = incomingBufferString.indexOf("<");


  xVal = incomingBufferString.substring(indexOfAr + 1, indexOfSemiCol);
  yVal = incomingBufferString.substring(indexOfCol + 1, indexOfBckAr);


  //data displaying
  display.setTextSize(1);

  display.setCursor(2, 2);
  display.println("X Pos: ");
  display.setCursor(40, 2);
  display.println(xVal);
  display.setCursor(2, 16);
  display.println("Y Pos: ");
  display.setCursor(40, 16);
  display.println(yVal);
  display.display();
  display.clearDisplay();
}
