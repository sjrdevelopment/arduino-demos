int ledPin = 9;    // LED connected to digital pin 9
int inputPin = A0; // Potentiometer connected to A0 pin

int lastInputValue;

void setup() {
  // nothing happens in setup
}

void loop() {
    int inputValue = analogRead(inputPin); // 0 - 1024
    
    if (inputValue != lastInputValue) {

      analogWrite(ledPin, map(inputValue, 0, 1023, 0, 255));
      // wait for 30 milliseconds to see the dimming effect
    }
    delay(30);
}


