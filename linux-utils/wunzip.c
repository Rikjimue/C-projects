#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  if (argc == 1) {
      printf("wunzip: file1 [file2 ...]\n");
      exit(1);
  }

  int count;
  char character;

  for (int i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "rb");
    if (fp == NULL) {
      printf("wunzip: error opening file\n");
      exit(1);
    }
    while(fread(&count, 4, 1, fp) == 1) {
      if (fread(&character, 1, 1, fp) == 1) {
        for (int j = 0; j < count; j++) {
          printf("%c", character);
        }
      } else {
        printf("wunzip: error format unexpected\n");
        exit(1);
      }
    }
  }
  exit(0);
}
