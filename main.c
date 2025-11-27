#include <ctype.h>
#include <stdio.h>
#include <string.h>

const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const char rotorI[] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
const char rotorII[] = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
const char rotorIII[] = "BDFHJLCPRTXVZNYEIWGAKMUSQO";

const char notchI = 'Q';
const char notchII = 'E';
const char notchIII = 'V';

const char reflector[] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";

int posRotorI = 0;
int posRotorII = 0;
int posRotorIII = 0;

int letterToIndex(char letter) { return toupper(letter - 'A'); }

char indexToLetter(int idx) { return alphabet[idx % 26]; }

void rotateRotors() {
  posRotorI = (posRotorI + 1) % 26;

  if (alphabet[posRotorI] == notchI) {
    posRotorII = (posRotorII + 1) % 26;
  }

  if (alphabet[posRotorII] == notchII) {
    posRotorIII = (posRotorIII + 1) % 26;
  }
}

int main() {
  printf("Hello, Enigma Machine!");
  printf("\n");

  return 0;
}
