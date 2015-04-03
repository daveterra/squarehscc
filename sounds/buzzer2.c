#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
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


#define NUM_MARY_NOTES 26
int const mary_had_a_little_lamb[NUM_MARY_NOTES] = {
    NOTE_B4,NOTE_A4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_B4,NOTE_B4,
    NOTE_A4,NOTE_A4,NOTE_A4,NOTE_B4,NOTE_D4,NOTE_D4,
    NOTE_B4,NOTE_A4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_B4,NOTE_B4,
    NOTE_B4,NOTE_A4,NOTE_A4,NOTE_B4,NOTE_A4,NOTE_G4, };

void mary_had_a_little_lamb()
{
    for(int i = 0; i< NUM_MARY_NOTES; i++) {
        buzz_sound(1000L*1000L, mary_had_a_little_lamb[i]);
    }
}

void rodion_for_loop()
{
    for(int i = 100; i < 10000; i += 10) {
        buzz_sound(1000, i);
    }
}

void double_for_loop()
{
    for(int i = 1000; i > 0; i -= 10) {
        for(int j = 100; j < 10000; j += 10) {
            buzz_sound(i, j);
        }
    }
}

void loop() {
    mary_had_a_little_lamb();
    rodion_for_loop();
    double_for_loop();
}

