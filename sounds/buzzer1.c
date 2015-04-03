#define BUZZER1 (4)
#define BUZZER2 (7)

void write_buzz_and_delay(int buzzer1, int buzzer2, int delay) {
    digitalWrite(BUZZER1, buzzer1);
    digitalWrite(BUZZER2, buzzer2);
    delayMicroseconds(delay);
}

void buzz_sound(long duration, int delay) {
    while (duration > 0) {
        write_buzz_and_delay(0,1,delay);
        write_buzz_and_delay(1,0,delay);
        duration -= (long)delay*2;
    }
}

void setup() {
    pinMode(BUZZER1, OUTPUT);
    pinMode(BUZZER2, OUTPUT);
}

void loop() {
    buzz_sound(1000L*1000L, 3333);
    buzz_sound(1000000, 1111);
}

