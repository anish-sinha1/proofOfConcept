#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define RAW_DATA "./data/raw_data.csv" // Defines file to process
#define PROCESSED_DATA "./data/processed_data.csv"
int getBufferSize(void);
int writeCharactersToFile(int);

int main() {
  int bufferSize = getBufferSize();

  int numChars = writeCharactersToFile(bufferSize);

  return 0;
}

// Open and read file

int getBufferSize() {
  FILE *dataFile = fopen(RAW_DATA, "r+");
  int ch;
  int count;
  while (1) {
    ch = fgetc(dataFile);
    if (ch != EOF) {
      ++count;
    }
    if (ch == EOF) {
      ++count;
      break;
    }
  }
  fclose(dataFile);
  return count;
}

// Read all characters that are not spaces into the buffer then write them into
// a file

int writeCharactersToFile(int bufferSize) {
  char buffer[bufferSize];
  FILE *dataFile = fopen(RAW_DATA, "rw");
  FILE *outFile = fopen(PROCESSED_DATA, "w");
  int ch;
  int cursor = 0;
  while (1) {
    ch = fgetc(dataFile);
    if (ch == EOF) {
      break;
    }
    if (ch != ' ' && ch != '\0') {
      buffer[cursor] = ch;
      ++cursor;
    }
  }
  for (int i = 0; i < cursor; i++) {
    printf("%c", buffer[i]);
  }
  fwrite(buffer, sizeof(char), cursor, outFile);
  fclose(dataFile);
  return 0;
}