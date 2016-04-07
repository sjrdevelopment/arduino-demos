int ledPin = 9;    // LED connected to digital pin 9

int lastInputValue;
int currentInputValue;

void setup() {
  Serial.begin(9600);
}

void loop() {
    // check if data has been sent from the computer:
    if (Serial.available()) {
      // read the most recent byte (which will be from 0 to 255):
     
      currentInputValue = Serial.parseInt();
    
      // set the brightness of the LED:
      if(currentInputValue != lastInputValue && currentInputValue > 0) {
        analogWrite(ledPin, currentInputValue);
        lastInputValue = currentInputValue;
      }
    }
}


