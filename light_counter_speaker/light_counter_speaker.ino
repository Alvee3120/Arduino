const int greenPin = 2;
const int yellowPin = 3;
const int redPin = 4;
const int buttonPin = 5;
const int speakerPin = 6;

// 7-segment segment pins A–G (connected to Arduino 7–13)
const int segmentPins[7] = {7, 8, 9, 10, 11, 12, 13};

bool inTransition = false;

// Digit patterns for 0–9 on common cathode display
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

void displayDigit(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digit[num][i]);
  }
}

void clearDisplay() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], LOW);
  }
}

void setup() {
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(speakerPin, OUTPUT);

  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  digitalWrite(greenPin, HIGH);  // Start with green ON
}

void loop() {
  if (digitalRead(buttonPin) == LOW && !inTransition) {
    inTransition = true;

    delay(3000); // Wait 3 seconds

    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, HIGH);
    delay(5000);

    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, HIGH);

    // 🔊 + 🧮 Red light active: countdown + beep for 10 seconds
    for (int i = 9; i >= 0; i--) {
      displayDigit(i);
      
      tone(speakerPin, 1000);   // Beep
      delay(200);
      noTone(speakerPin);
      delay(800);               // Total 1 second per digit
    }

    clearDisplay();             // Optional: turn off display
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);

    inTransition = false;
  }
}
