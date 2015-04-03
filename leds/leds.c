
#define LED_UPPER_LEFT (10)
#define LED_UPPER_RIGHT (3)
#define LED_LOWER_LEFT (13)
#define LED_LOWER_RIGHT (5)

#define BUTTON_UPPER_LEFT (9)
#define BUTTON_UPPER_RIGHT (2)
#define BUTTON_LOWER_LEFT (12)
#define BUTTON_LOWER_RIGHT (6)

void setup()
{
    pinMode(LED_UPPER_LEFT, OUTPUT);
    pinMode(LED_UPPER_RIGHT, OUTPUT);
    pinMode(LED_LOWER_LEFT, OUTPUT);
    pinMode(LED_LOWER_RIGHT, OUTPUT);
    pinMode(BUTTON_UPPER_LEFT, INPUT_PULLUP);
    pinMode(BUTTON_UPPER_RIGHT, INPUT_PULLUP);
    pinMode(BUTTON_LOWER_LEFT, INPUT_PULLUP);
    pinMode(BUTTON_LOWER_RIGHT, INPUT_PULLUP);
}

void loop()
{
      int value;
      value = digitalRead(BUTTON_UPPER_RIGHT);
      digitalWrite(LED_UPPER_RIGHT, !value);

      value = digitalRead(BUTTON_UPPER_LEFT);
      digitalWrite(LED_UPPER_LEFT, !value);

      value = digitalRead(BUTTON_LOWER_RIGHT);
      digitalWrite(LED_LOWER_RIGHT, !value);

      value = digitalRead(BUTTON_LOWER_LEFT);
      digitalWrite(LED_LOWER_LEFT, !value);
}

