


#define MAX_WRITE 16

byte tempStore[MAX_WRITE];

void writePage(long eeAddress)
{
  for (byte x = 0 ; x < MAX_WRITE ; x++)
    Serial.write(tempStore[x]);
}

void setup()
{

  //Start the serial port
  Serial.begin(19200);

  //Here is where we'll keep track of where in the memory we're writing
  long currentSpot = 0;
  long timerReset = 0;
  byte counter = 0;

  delay(30000);

  //Here we listen for bytes on the serial port and increment
  //the counter as we store them in our tempStore variable
  while (1)
  {
    while (Serial.available())
    {
      tempStore[counter++] = Serial.read(); //Read this byte into the array

      if (counter == MAX_WRITE)
      {
        //Once we've collected a page worth, go ahead and do
        //a page write operation
        writePage(currentSpot);
        counter = 0; //Reset
        currentSpot += MAX_WRITE;
      }

      timerReset = millis();
    }


    if (millis() - timerReset > 2000)
    {
      Serial.println(currentSpot);
      timerReset = millis();
    }
  }
}

void loop()
{
  // Don't do anything here
}
