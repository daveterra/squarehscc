#define CHOICE_NONE     0 //Used to check buttons
#define CHOICE_RED	(1 << 0)
#define CHOICE_GREEN	(1 << 1)
#define CHOICE_BLUE	(1 << 2)
#define CHOICE_YELLOW	(1 << 3)
#define CHOICE_ALL (CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_YELLOW)

// LED pin definitions, these are Arduino pins, not ATmega pins
#define LED_RED     10
#define LED_GREEN   3
#define LED_BLUE    13
#define LED_YELLOW  5

// Button pin definitions
#define BUTTON_RED    9
#define BUTTON_GREEN  2
#define BUTTON_BLUE   12
#define BUTTON_YELLOW 6

// Buzzer pin definitions
#define BUZZER1  4
#define BUZZER2  7
