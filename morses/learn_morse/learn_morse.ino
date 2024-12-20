#include <LiquidCrystal.h>

// pin to which the button is connected
int buttonPin = 6;
// pin to which the buzzer is connected
int buzzerPin = 9;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);

  // lcd.begin(16, 2);

  pinMode(buttonPin, INPUT_PULLUP);

  state = UP;
  characterIndex = 0;
  downDuration = 0;
  lastChange = 0;
  action = START;
}

// reset the dash-dot-sequence of the current character
void clearCharacter() {
  characterIndex = 0;
  for (int i = 0; i < 5; ++i) {
    character[i] = CLEAR;
  }
}

// determine the next dash or dot in the dash-dot sequence of the current character
void readDashDot() {
  Serial.print("Down duration was: ");
  Serial.println(downDuration);

  if (downDuration >= dashDuration - tolerance && downDuration < dashDuration + tolerance) {
    character[characterIndex] = DASH;
    Serial.println("DASH");
    characterIndex++;
  } else if (downDuration >= dotDuration - tolerance && downDuration < dotDuration + tolerance) {
    character[characterIndex] = DOT;
    Serial.println("DOT");
    characterIndex++;
  } else {
    Serial.println("Down duration unrecognized");
  }
}

// interpret the current dash-dot-sequence as a character
char readCharacter() {
  bool found;
  for (int i = 0; i < 26; ++i) {
    found = true;
    for (int j = 0; found && j < 5; ++j) {
      if (character[j] != alphabet[i][j + 1]) {
        found = false;
      }
    }
    if (found) {
      return alphabet[i][0];
    }
  }
  return 0;
}

void loop() {
  State newState = digitalRead(buttonPin) ? UP : DOWN;

  // if the button is pressed, play a tone
  if (newState == DOWN) {
    tone(buzzerPin, 800);
  } else {
    noTone(buzzerPin);
  }

  if (newState == state) {
    if (newState == UP) {
      // calculate the the time the button has been in UP state
      unsigned long upDuration = (millis() - lastChange);

      if (action == READ_DASHDOT && upDuration >= shortGap - tolerance && upDuration < shortGap + tolerance) {
        readDashDot();
        action = READ_CHARACTER;
      } else if (action == READ_CHARACTER && upDuration >= mediumGap - tolerance && upDuration < mediumGap + tolerance) {
        char c = readCharacter();
        if (c != 0) {
          // a valid character has been recognized
          Serial.print("Read character: ");
          Serial.println(c);
          lcd.print(c);
        } else {
          Serial.println("Unrecognized character");
        }
        clearCharacter();
        action = READ_WORD;
      } else if (action == READ_WORD && upDuration >= longGap - tolerance && upDuration < longGap + tolerance) {
        Serial.println("Read next word");
        lcd.print(' ');
        action = READ_DASHDOT;
      }
    } else {
      downDuration = (millis() - lastChange);
    }
  } else {
    if (state == UP && newState == DOWN) {
      downDuration = 0;
    }
    lastChange = millis();
    state = newState;
    action = READ_DASHDOT;
  }
}
