/*
  Listfiles

  This example shows how print out the files in a
  directory on a SD card

  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10

*/
#include <SPI.h>
#include <SD.h>


void printRootDir() {
  File root = SD.open("/");
  printDirectory(root, 0);
  Serial.println("done!");
}

void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void readFile(String fileName){
  File myFile = SD.open(fileName); //open the file for reading
  if (myFile) {
    Serial.println(fileName);

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close(); // close the file:
  } else {
    // if the file didn't open, print an error:
    Serial.print("Error Opening - ");
    Serial.println(fileName);
  }
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("Initialization Failed!");
    while (1);
  }
  Serial.println("Initialization Done.");

  delay(10000);
  
  //printRootDir();
  readFile("b.txt");

}

void loop() {
  // nothing happens after setup finishes.
}
