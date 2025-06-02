#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  int currentChar;
  int previousChar = -2;
  int count = 0;

  for (int i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    if (fp == NULL) {
      printf("wzip: file1 [file2 ...]\n");
      exit(1);
    }

    while ((currentChar = fgetc(fp)) != EOF) {
      if (currentChar == previousChar || previousChar == -2) {
        count++;
      } else {
        fwrite(&count, 4, 1, stdout);
        printf("%c", previousChar);
        count = 1;
      }
      previousChar = currentChar;

    }
    fwrite(&count, 4, 1, stdout);
    printf("%c", previousChar);
  }
  
  exit(0);
}
