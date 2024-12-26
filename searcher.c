#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_LINE_LEN 2048

int contains_line(const char *filename, const char *search_line) {
  FILE *file_ptr = fopen(filename, "r");
  if (file_ptr == NULL) {
    perror("ERROR: Invalid file");
    return -1;
  }

  char curr_line[MAX_LINE_LEN];
  while (fgets(curr_line, sizeof(curr_line), file_ptr)) {
    if (strstr(curr_line, search_line)) {
      fclose(file_ptr);
      return 1;
    }
  }

  fclose(file_ptr);
  return -1;
}

int main() {
  DIR *dir = NULL;
  struct dirent *entry;
  char search_line[MAX_LINE_LEN];

  /* ENTER DIRECTORY/FOLDER CONTAINING FILES */
  char dir_path[] = "./memories-off-2nd-main";
  dir = opendir(dir_path);

  if (!dir) {
    perror("ERROR: Invalid directory");
    return -1;
  }

  printf("Enter text to search: ");
  scanf("%s", search_line);

  int found = 0;

  while ((entry = readdir(dir)) != NULL) {
    /* Check if is of a certain file type (this case .txt) */
    if (strstr(entry->d_name, ".txt")) {
      char file_path[MAX_LINE_LEN];
      snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entry->d_name);

      if (contains_line(file_path, search_line) == 1) {
        found++;
      }
    }
  }

  if (found == 0) {
    printf("No files contain the line \"%s\".\n", search_line);
  } else {
    printf("%d instances of the line \"%s\".\n", found, search_line);
  }

  closedir(dir);
  return 0;
}
