#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_LINE_LEN 1024

int contains_line(const char *filename, const char *search_line) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Error opening file");
    return 0;
  }

  char line[MAX_LINE_LEN];
  while (fgets(line, sizeof(line), file)) {
    if (strstr(line, search_line)) {
      fclose(file);
      return 1;
    }
  }

  fclose(file);
  return 0;
}

int main() {
  DIR *dir;
  struct dirent *entry;
  char search_line[MAX_LINE_LEN];
  /* ENTER DIRECTORY/FOLDER CONTAINING FILES */
  dir = opendir("./memories-off-2nd-main");

  if (!dir) {
    perror("ERROR: Invalid directory");
    return -1;
  }

  printf("Enter text to search: ");
  scanf("%s", search_line);

  printf("CURR SEARCHLINE: %s\n", search_line);

  int found = 0;

  while ((entry = readdir(dir)) != NULL) {
    if (strstr(entry->d_name, ".msb.txt")) {
      printf("openable file \n");
    }
  }

  if (!found) {
    printf("No files contain the line \"%s\".\n", search_line);
  }

  closedir(dir);
  return 0;
}
