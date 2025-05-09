const int greenPin = 2;
const int yellowPin = 3;
const int redPin = 4;
const int buttonPin = 5;
const int speakerPin = 6;  // Speaker pin

bool inTransition = false;

void setup() {
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(speakerPin, OUTPUT);  // Speaker output

  digitalWrite(greenPin, HIGH);  // Start with green ON
}

void loop() {
  if (digitalRead(buttonPin) == LOW && !inTransition) {
    inTransition = true;

    delay(3000); // Wait 3 seconds after button press

    digitalWrite(greenPin, LOW);   // Green OFF
    digitalWrite(yellowPin, HIGH); // Yellow ON
    delay(5000);                   // Yellow for 5 seconds

    digitalWrite(yellowPin, LOW);  // Yellow OFF
    digitalWrite(redPin, HIGH);    // Red ON

    tone(speakerPin, 1000);        // Sound speaker at 1kHz
    delay(10000);                  // Red for 10 seconds
    noTone(speakerPin);            // Stop sound

    digitalWrite(redPin, LOW);     // Red OFF
    digitalWrite(greenPin, HIGH);  // Green ON again

    inTransition = false;
  }
}