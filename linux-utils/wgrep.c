#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int searchSubstring(char subStr[], char line[]) {
  int subStrLen = strlen(subStr);
  int lineLen = strlen(line);
  int fast = 0; int slow = 0; int match = 0;

  while (subStrLen <= lineLen - slow) {
    if (subStr[fast] == line[slow+fast]) {
      match++;
      fast++;
    } else {
      match = 0;
      fast = 0;
      slow++;
    }

    if (match == subStrLen) {
      return 0;
    }
  }
  return 1;
}

int main(int argc, char *argv[]) {

  char *line = NULL;
  size_t len = 0;
  
  if (argc == 1) {
    printf("wgrep: searchterm [file ...]\n");
    exit(1);
  } else if (argc == 2) { // Takes from stdin
    while (getline(&line, &len, stdin) != -1) {
      if (searchSubstring(argv[1], line) == 0) {
        printf("%s", line);
      }
    }
  } else { // Reads from file
    for (int i = 2; i < argc; i++) {
      FILE *fp = fopen(argv[i], "r");
      if (fp == NULL) {
        printf("wgrep: cannot open file\n");
        exit(1);
      }
      while (getline(&line, &len, fp) != -1) {
        if (searchSubstring(argv[1], line) == 0) {
          printf("%s", line);
        }
      }
    }
  }

  exit(0);
}
