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

    // GREEN OFF, YELLOW ON (Before RED)
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, HIGH);

    // Countdown 5 seconds (yellow before red)
    for (int i = 5; i > 0; i--) {
      displayDigit(i);
      delay(1000);
    }

    // YELLOW OFF, RED ON
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, HIGH);

    // Countdown 10 seconds with beep
    for (int i = 9; i >= 0; i--) {
      displayDigit(i);
      tone(speakerPin, 1000);   // 1kHz tone
      delay(200);
      noTone(speakerPin);
      delay(800);
    }

    // RED OFF, YELLOW ON (Before GREEN)
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, HIGH);

    // Countdown 3 seconds (yellow before green)
    for (int i = 3; i > 0; i--) {
      displayDigit(i);
      delay(1000);
    }

    // YELLOW OFF, GREEN ON
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, HIGH);

    // Clear display
    displayDigit(-1);

    inTransition = false;
  }
}