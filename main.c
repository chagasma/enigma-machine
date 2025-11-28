#include <ctype.h>
#include <stdio.h>
#include <string.h>

const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const char rotorI[] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
const char rotorII[] = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
const char rotorIII[] = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
const char rotorIV[] = "ESOVPZJAYQUIRHXLNFTGKDCMWB";
const char rotorV[] = "VZBRGITYUPSDNHLXAWMJQOFECK";

int rotorIInverse[26];
int rotorIIInverse[26];
int rotorIIIInverse[26];

const char notchI = 'Q';
const char notchII = 'E';
const char notchIII = 'V';
const char notchIV = 'J';
const char notchV = 'Z';

// nunca gira, inverte sinal em pares, garante a simetria
const char reflectorB[] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
const char reflectorC[] = "FVPJIAOYEDRZXWGCTKUQSBNMHL";

int posRotorI = 0;
int posRotorII = 0;
int posRotorIII = 0;

int letterToIndex(char letter) { return toupper(letter) - 'A'; }

char indexToLetter(int idx) { return alphabet[idx % 26]; }

// ex: pos 0 == 'E' portanto inverse[4] = 0 | input: 'E' output: 'A'
void buildInverseWiring(const char *rotor, int *inverse) {
  for (int i = 0; i < 26; i++) {
    int output = letterToIndex(rotor[i]);
    inverse[output] = i;
  }
}

void rotateRotors() {
  // double stepping: quando o do meio e o da direita atingem o notch giram os 3
  int middleAtNotch = (alphabet[posRotorII] == notchII);
  int rightAtNotch = (alphabet[posRotorI] == notchI);

  if (middleAtNotch) {
    posRotorIII = (posRotorIII + 1) % 26;
    posRotorII = (posRotorII + 1) % 26;
  } else if (rightAtNotch) {
    posRotorII = (posRotorII + 1) % 26;
  }

  // rotação a cada step
  posRotorI = (posRotorI + 1) % 26;
}

// fluxo indo - update na position para atualizar o posticionamento
// ex: gira 3 vezes 'A' fica fisicamente aonde deveria estar 'D'
// retorno da letra de saída
int forward(int signal, const char *rotor, int position) {
  int entry = (signal + position + 26) % 26;
  int encoded = letterToIndex(rotor[entry]);
  return (encoded - position + 26) % 26;
}

// basicamente o mesmo fluxo só que reverso
int backward(int signal, const int *inverseRotor, int position) {
  int entry = (signal + position + 26) % 26;
  int encoded = inverseRotor[entry];
  return (encoded - position + 26) % 26;
}

char encodeCharacter(char letter) {
  // gira
  rotateRotors();

  // codifica
  int signal = letterToIndex(letter);

  // sinal atravessa os rotores direta pra esquerda
  signal = forward(signal, rotorIII, posRotorI);
  signal = forward(signal, rotorII, posRotorII);
  signal = forward(signal, rotorI, posRotorIII);

  signal = letterToIndex(reflectorB[signal]);

  signal = backward(signal, rotorIInverse, posRotorIII);
  signal = backward(signal, rotorIIInverse, posRotorII);
  signal = backward(signal, rotorIIIInverse, posRotorI);

  return indexToLetter(signal);
}

int main() {
  buildInverseWiring(rotorI, rotorIInverse);
  buildInverseWiring(rotorII, rotorIIInverse);
  buildInverseWiring(rotorIII, rotorIIIInverse);

  char input[256];

  printf("Enigma Machine\n");
  printf("Enter text: ");

  if (fgets(input, sizeof(input), stdin) == NULL) {
    return 1;
  }

  printf("Output: ");

  for (int i = 0; input[i] != '\0'; i++) {
    if (isalpha(input[i])) {
      printf("%c", encodeCharacter(input[i]));
    } else {
      printf("%c", input[i]);
    }
  }

  return 0;
}
