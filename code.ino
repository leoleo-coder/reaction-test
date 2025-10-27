#define BUTTON_REACT 0
#define BUTTON_HARD  1
#define BUTTON_EASY  2
#define LED_GO       3
#define LED_FAIL     4
#define LED_PASS     5
#define BUTTON_MED   6

#define TIME_EASY 700
#define TIME_MED  350
#define TIME_HARD 150

int difficulty = TIME_EASY;

void setup() {
  pinMode(BUTTON_REACT, INPUT_PULLUP);
  pinMode(BUTTON_HARD, INPUT_PULLUP);
  pinMode(BUTTON_EASY, INPUT_PULLUP);
  pinMode(BUTTON_MED, INPUT_PULLUP);
  pinMode(LED_GO, OUTPUT);
  pinMode(LED_FAIL, OUTPUT);
  pinMode(LED_PASS, OUTPUT);
  digitalWrite(LED_GO, LOW);
  digitalWrite(LED_FAIL, LOW);
  digitalWrite(LED_PASS, LOW);
}

void loop() {
  if (digitalRead(BUTTON_HARD) == LOW) {
    difficulty = TIME_HARD;
    flashLED(LED_GO, 2);
    delay(200);
  } else if (digitalRead(BUTTON_MED) == LOW) {
    difficulty = TIME_MED;
    flashLED(LED_GO, 1);
    delay(200);
  } else if (digitalRead(BUTTON_EASY) == LOW) {
    difficulty = TIME_EASY;
    flashLED(LED_GO, 3);
    delay(200);
  }
  delay(1000 + random(1000, 2000));
  digitalWrite(LED_FAIL, LOW);
  digitalWrite(LED_PASS, LOW);
  digitalWrite(LED_GO, HIGH);
  unsigned long startTime = millis();
  bool reacted = false;
  while (millis() - startTime < difficulty) {
    if (digitalRead(BUTTON_REACT) == LOW) {
      reacted = true;
      break;
    }
  }
  digitalWrite(LED_GO, LOW);
  if (reacted) {
    digitalWrite(LED_PASS, HIGH);
    delay(800);
    digitalWrite(LED_PASS, LOW);
  } else {
    digitalWrite(LED_FAIL, HIGH);
    delay(800);
    digitalWrite(LED_FAIL, LOW);
  }
}

void flashLED(int pin, int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
    delay(100);
  }
}
