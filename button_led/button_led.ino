#define LED_PIN 10
#define BTN_PIN 7

void setup()
{
  pinMode(BTN_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  bool isButtonPressed = digitalRead(BTN_PIN) == HIGH;

  if (isButtonPressed)
  {
    digitalWrite(LED_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
  }
}