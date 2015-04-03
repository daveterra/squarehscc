/*
 Started: 6-19-2007
 Spark Fun Electronics
 Nathan Seidle
*/

#include "pitches.h"
#include "simon_board.h"

// Define game parameters
byte ROUNDS_TO_WIN = 13; //Number of rounds to succesfully remember before you win.
byte ENTRY_TIME_LIMIT = 3; //Amount of time to press a button before game times out.

byte gameBoard[13]; //Contains the combination of buttons as we advance
byte gameRound = 0; //Counts the number of succesful rounds the player has made it through

void setup() {
  boardSetup();
  playWinner(); // After setup is complete, say hello to the world
}

void loop() {
  attractMode(); // Blink lights while waiting for user to press a button

  // Indicate the start of game play
  setLEDs(CHOICE_ALL); // Turn all LEDs on
  delay(1000);
  setLEDs(CHOICE_NONE); // Turn off LEDs
  delay(250);

  // Play memory game and handle result
  if (playMemory() == true) {
    playWinner(); // Player won, play winner tones
  } else {
    playLoser(); // Player lost, play loser tones
  }
}

// Play the regular memory game
// Returns false if player loses, or true if player wins
boolean playMemory() {
  randomSeed(millis()); // Seed the random generator with random amount of millis()
  gameRound = 0; // Reset the game to the beginning

  while (gameRound < ROUNDS_TO_WIN) {
    addToMoves(); // Add a button to the current moves, then play them back
    playMoves(); // Play back the current game board

    // Then require the player to repeat the sequence.
    for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++) {
      byte choice = waitForButton(ENTRY_TIME_LIMIT); // See what button the user presses
      if (choice == CHOICE_NONE) {
        return false; // If wait timed out, player loses
      }
      if (choice != gameBoard[currentMove]) {
        return false; // If the choice is incorect, player loses
      }
    }
    delay(1000); // Player was correct, delay before playing moves
  }
  return true; // Player made it through all the rounds to win!
}

// Plays the current contents of the game moves
void playMoves() {
  for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++) {
    toner(gameBoard[currentMove], 150);
    // Wait some amount of time between button playback
    delay(150); // Shorten this to make game harder: 150 works well. 75 gets fast.
  }
}

// Adds a new random button to the game sequence
void addToMoves() {
  byte newButton = randomChoice();
  gameBoard[gameRound++] = newButton; // Add this new button to the game array
}

// Play the winner sound and lights
void playWinner() {
  setLEDs(CHOICE_GREEN | CHOICE_BLUE);
  winnerSound();
  setLEDs(CHOICE_RED | CHOICE_YELLOW);
  winnerSound();
  setLEDs(CHOICE_GREEN | CHOICE_BLUE);
  winnerSound();
  setLEDs(CHOICE_RED | CHOICE_YELLOW);
  winnerSound();
}

// Play the winner sound
// This is just a unique (annoying) sound we came up with, there is no magic to it
void winnerSound() {
  // Toggle the buzzer at various speeds
  for (byte i = 10; i > 1; i--) {
    buzzSound(i*10, i)
  }
}

// Play the loser sound/lights
void playLoser() {
  setLEDs(CHOICE_RED | CHOICE_GREEN);
  buzzSound(255, 1500);
  setLEDs(CHOICE_BLUE | CHOICE_YELLOW);
  buzzSound(255, 1500);
  setLEDs(CHOICE_RED | CHOICE_GREEN);
  buzzSound(255, 1500);
  setLEDs(CHOICE_BLUE | CHOICE_YELLOW);
  buzzSound(255, 1500);
}

// Show an "attract mode" display while waiting for user to press button.
void attractMode() {
  while(1) {
    setLEDs(CHOICE_RED);
    delay(100);
    if (checkButtons() != CHOICE_NONE) return;
    setLEDs(CHOICE_BLUE);
    delay(100);
    if (checkButtons() != CHOICE_NONE) return;
    setLEDs(CHOICE_GREEN);
    delay(100);
    if (checkButtons() != CHOICE_NONE) return;
    setLEDs(CHOICE_YELLOW);
    delay(100);
    if (checkButtons() != CHOICE_NONE) return;
  }
}
