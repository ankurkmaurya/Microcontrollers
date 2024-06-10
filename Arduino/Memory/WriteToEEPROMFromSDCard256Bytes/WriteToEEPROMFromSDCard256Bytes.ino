
#include <SPI.h>
#include <SD.h>
#include <Wire.h>


#define EEPROM_ADDRESS 0x50  //Address of 24LC02 eeprom chip is 1010100
#define MEMORY_SIZE 256     // 256 Bytes Memory
#define PAGE_SIZE 8     // 8 Bytes
#define MEMORY_PAGES 32     // 32 Pages


void writeByte(int deviceAddress, unsigned int memoryAddress, byte data) {
  Wire.beginTransmission(deviceAddress);
  //Write 1 Byte Memory Address
  Wire.write(memoryAddress);
  Wire.write(data); //Write the data
  Wire.endTransmission(); //Send stop condition
  delay(20);
}

void writePage(int deviceAddress, unsigned int memoryAddress, byte data[]) {
  /*
     The Arduino Wire library only has a 32 character buffer, so that is the maximun we can send using Arduino.
     This buffer includes the two address bytes which limits our data payload to 30 bytes.
     Since our page size is 8 bytes there is no need to divide the write operation
  */
  Serial.print("Writing to Memory Addrress - ");
  Serial.println(memoryAddress, DEC);

  Wire.beginTransmission(deviceAddress);
  //Write 1 Byte Memory Address
  Wire.write(memoryAddress);
  for (int i = 0; i < PAGE_SIZE; i++) {
    Wire.write(data[i]); //Write the data
  }
  Wire.endTransmission(); //Send stop condition
  delay(30);

  Serial.println("Done");
}

byte readByte(int deviceAddress, unsigned int memoryAddress) {
  byte rdata = 0xFF;

  Wire.beginTransmission(deviceAddress);
  //Write 1 Byte Memory Address
  Wire.write(memoryAddress);
  Wire.endTransmission();

  Wire.requestFrom(deviceAddress, 1);
  delay(10);

  if (Wire.available())
    rdata = Wire.read();
  return rdata;
}

boolean verifyDataInPage(int deviceAddress, unsigned int pageOffset, byte dataToVerify[]) {
  byte rdata = 0xFF;
  byte pageBuffer[PAGE_SIZE];

  Wire.beginTransmission(deviceAddress);
  //Write 1 Byte Memory Address
  Wire.write(pageOffset);
  Wire.endTransmission();

  Wire.requestFrom(deviceAddress, PAGE_SIZE);
  delay(10);

  int dataCounter = 0;
  while (Wire.available()) {
    pageBuffer[dataCounter] = Wire.read();
    dataCounter++;
  }

  for (int i = 0; i < PAGE_SIZE; i++) {
    if (pageBuffer[i] != dataToVerify[i]) {
      return false;
    }
  }
  return true;
}

void printAllMemoryPages(int deviceAddress) {
  //Print Data
  for (uint16_t i = 0; i < MEMORY_SIZE; i++) {
    Serial.write(readByte(deviceAddress, i)); //Print statement
  }

  //  int lineCntr = 0;
  //  for (uint16_t i = 0; i < MEMORY_SIZE; i++) {
  //    if (lineCntr == 8) {
  //      Serial.println("");
  //      lineCntr = 0;
  //    }
  //
  //    Serial.print(readByte(EEPROM1_ADDRESS, i), BIN); //Print statement
  //    Serial.print(" ");
  //    lineCntr++;
  //  }
  //  Serial.println("");
}

boolean verifyDataAtMemAddress(int deviceAddress, unsigned int memoryAddress, byte dataToVerify) {
  if (readByte(deviceAddress, memoryAddress) == dataToVerify) {
    return true;
  } else {
    return false;
  }
}


boolean saveToMemoryFromSDCard(int deviceAddress, String fileName) {
  boolean allWriteVerifiedSuccess = true;
  uint16_t pageCounter = 0;
  unsigned int memoryAddress = 0;
  byte pageBuffer[PAGE_SIZE];
  uint16_t bufferCounter = 0;
  byte data = 0;

  File myFile = SD.open(fileName); //open the file for reading
  if (myFile) {
    Serial.print("Success Opening - ");
    Serial.println(fileName);

    Serial.println("Writing File Data to Memory - ");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      if (bufferCounter == PAGE_SIZE) {
        pageCounter++;
        Serial.print("Writing to Page - ");
        Serial.println(pageCounter, DEC);
        writePage(deviceAddress, memoryAddress, pageBuffer); //Write data buffer to memory page
        //Verify data written to memory page
        if (!verifyDataInPage(deviceAddress, memoryAddress, pageBuffer)) {
          allWriteVerifiedSuccess = false;
          Serial.println("Verify Failed.");
        }
        bufferCounter = 0;
        memoryAddress = memoryAddress + PAGE_SIZE;
        data++;
      }
      pageBuffer[bufferCounter] = myFile.read(); //Read data byte from file
      bufferCounter++;


      if (pageCounter == MEMORY_PAGES) {
        break; //Memory is Full all the Memory Pages has been filled
      }
    }
    myFile.close(); // close the file:
    Serial.println("Data Written to Memory.");
  } else {
    // if the file didn't open, print an error
    Serial.print("Error Opening - ");
    Serial.println(fileName);
    allWriteVerifiedSuccess = false;
  }
  return allWriteVerifiedSuccess;
}


void setup() {
  Wire.begin();

  Serial.begin(19200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }

//  Serial.println("Initializing SD card...");
//
//  if (!SD.begin(10)) {
//    Serial.println("Initialization Failed!");
//    while (1);
//  }
//  Serial.println("Initialization Done.");

//  delay(20000);
//
//    boolean dataWritten = saveToMemoryFromSDCard(EEPROM_ADDRESS, "b.txt");
//    if (dataWritten) {
//      Serial.println("Data Write to Memory - Success");
//    } else {
//      Serial.println("Data Write to Memory - Failed");
//    }

  delay(10000);
  printAllMemoryPages(EEPROM_ADDRESS);


}

void loop() {
  // put your main code here, to run repeatedly:

}
