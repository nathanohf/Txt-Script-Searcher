#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_LINE_LEN 2048

int contains_line(const char *filename, const char *search_line) {
  int count = 0;
  FILE *file_ptr = fopen(filename, "r");
  if (file_ptr == NULL) {
    perror("ERROR: Invalid file\n");
    return 0;
  }

  char curr_line[MAX_LINE_LEN];
  while (fgets(curr_line, sizeof(curr_line), file_ptr)) {
    if (strstr(curr_line, search_line)) {
      printf("%sfound in file %s\n", curr_line, filename);
      count++;
    }
  }

  fclose(file_ptr);
  return count;
}

int main() {
  /* Temporary true loop for now, ctrl + c to exit */
  /* REMOVE LATER */
  while(1) {
    DIR *dir = NULL;
    struct dirent *entry;
    char search_line[MAX_LINE_LEN];

    /* ENTER DIRECTORY/FOLDER CONTAINING FILES */
    char dir_path[] = "./memories-off-2nd-main";
    dir = opendir(dir_path);

    if (!dir) {
      perror("ERROR: Invalid directory\n");
      return -1;
    }
    printf("Enter text to search: ");
    scanf("%s", search_line);
    
    printf("CTRL + C to exit.");
    printf("\n---=-=- LINES FOUND -=-=---\n");

    int found = 0;
    int count = 0;

    while ((entry = readdir(dir)) != NULL) {
      /* Check if is of a certain file type (this case .txt) */
      if (strstr(entry->d_name, ".txt")) {
        char file_path[MAX_LINE_LEN];
        snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entry->d_name);

        int contains_status = contains_line(file_path, search_line);
        if (contains_status != 0) {
          found++;
          count += contains_status;
        }
      }
    }

    if (found == 0) {
      printf("No files contain the line \"%s\"\n", search_line);
    } else {
      printf("%d files containing line\n", found);
      printf("%d total instances\n", count);
    }

    closedir(dir);
  }
  return 0;
}
