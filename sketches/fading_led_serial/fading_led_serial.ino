int ledPin = 9;    // LED connected to digital pin 9
int inputPin = A0; // Potentiometer connected to A0 pin

int changeThreshold = 5;
int lastInputValue;

void setup() {
  Serial.begin(9600);
  Serial.println("hello world");
}

void loop() {
    int inputValue = analogRead(inputPin); // 0 - 1024
    
    if (inputValue > lastInputValue + changeThreshold
        || inputValue < lastInputValue - changeThreshold) {
      Serial.println(map(inputValue, 0, 1023, 0, 255));
      lastInputValue = inputValue;
     
    }

}


