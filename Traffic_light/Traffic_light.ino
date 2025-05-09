const int greenPin = 2;
const int yellowPin = 3;
const int redPin = 4;
const int buttonPin = 5;
const int speakerPin = 6; // Speaker connected to pin 6

// Segment pins for 7-segment display (A to G)
const int segmentPins[7] = {7, 8, 9, 10, 11, 12, 13};  // A, B, C, D, E, F, G

bool inTransition = false;

// Digit segment patterns for common cathode display (0–9)
const byte digit[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

// Display a number on 7-segment
void displayDigit(int num) {
  if (num >= 0 && num <= 9) {
    for (int i = 0; i < 7; i++) {
      digitalWrite(segmentPins[i], digit[num][i]);
    }
  } else {
    // Turn OFF all segments if invalid number
    for (int i = 0; i < 7; i++) {
      digitalWrite(segmentPins[i], LOW);
    }
  }
}

void setup() {
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(speakerPin, OUTPUT); // Speaker pin

  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

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

    // Start 7-segment countdown from 9 to 0
    for (int i = 9; i >= 0; i--) {
      displayDigit(i);

      // Beep speaker for 200ms each second
      tone(speakerPin, 1000);   // 1kHz tone
      delay(200);
      noTone(speakerPin);

      delay(800); // Remaining part of the second
    }

    digitalWrite(redPin, LOW);       // Red OFF
    digitalWrite(yellowPin, HIGH);   // Yellow ON
    delay(3000);                     // Yellow for 3 seconds
    digitalWrite(yellowPin, LOW);    // Yellow OFF
    digitalWrite(greenPin, HIGH);    // Green ON

    displayDigit(-1);                // Clear display

    inTransition = false;
  }
}
