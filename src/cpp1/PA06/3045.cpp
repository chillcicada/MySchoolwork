#include <stdio.h>
#include <string.h>

char convertMorseToAscii(const char *morse) {
  const char *morseCode[] = {
      ".-",   "-...", "-.-.", "-..",  ".",   "..-.", "--.",  "....", "..",
      ".---", "-.-",  ".-..", "--",   "-.",  "---",  ".--.", "--.-", ".-.",
      "...",  "-",    "..-",  "...-", ".--", "-..-", "-.--", "--.."};
  const char asciiMap[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  for (int i = 0; i < 26; ++i) {
    if (strcmp(morse, morseCode[i]) == 0)
      return asciiMap[i];
  }
  return ' ';
}

void morseToEnglish(const char *morse, char *english) {
  char morseChar[5];
  int morseCharIndex{0}, englishIndex{0}, spaceCount{0};

  for (int i = 0; morse[i] != '\0'; ++i) {
    if (morse[i] == ' ') {
      spaceCount++;
      if (morseCharIndex) {
        morseChar[morseCharIndex] = '\0';
        english[englishIndex++] = convertMorseToAscii(morseChar);
        morseCharIndex = 0;
      }
      if (spaceCount == 2) {
        english[englishIndex++] = ' ';
        spaceCount = 0;
      }
    } else {
      spaceCount = 0;
      morseChar[morseCharIndex++] = morse[i];
    }
  }
  if (morseCharIndex) {
    morseChar[morseCharIndex] = '\0';
    english[englishIndex++] = convertMorseToAscii(morseChar);
  }
  english[englishIndex] = '\0';
}

int main() {
  char morseSentence[10240];
  fgets(morseSentence, sizeof(morseSentence), stdin);
  size_t len = strlen(morseSentence);
  if (len > 0 && morseSentence[len - 1] == '\n') {
    morseSentence[len - 1] = '\0';
  }
  char englishSentence[10240];
  morseToEnglish(morseSentence, englishSentence);
  printf("%s\n", englishSentence);
  return 0;
}
