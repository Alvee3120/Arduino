const int greenPin = 2;
const int yellowPin = 3;
const int redPin = 4;
const int buttonPin = 5;

// Segment pins for 7-segment display (a to g)
const int segmentPins[7] = {6, 7, 8, 9, 10, 11, 12};  // Adjust if needed

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
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digit[num][i]);
  }
}

void setup() {
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

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
      delay(1000); // Show each number for 1 second
    }

    // Turn off red and go back to green
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);

    // Optionally clear display
    displayDigit(10); // Invalid index; all segments OFF if you code it

    inTransition = false;
  }
}
