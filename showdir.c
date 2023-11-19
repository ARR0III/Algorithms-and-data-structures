#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>
#include <sys/types.h>

void list_dir (const char * dir_name) {
  DIR * directory = opendir(dir_name);

  if (!directory) {
    fprintf(stderr, "Cannot open directory \"%s\": %s\n", dir_name, strerror(errno));
    return;
  }
    
  while (1) {
    struct dirent * entry = readdir(directory);
    const char * d_name;

    if (!entry) {
      break;
    }

    d_name = entry->d_name;

    if (entry->d_type & DT_DIR) {
      if (strcmp (d_name, "..") == 0 || strcmp(d_name, ".") == 0) {
        continue;
      }
      
      int    path_length;
      char * path = (char *)calloc(1, PATH_MAX + 1);
        
      if (!path) {
        break;
      }
 
      path_length = snprintf(path, PATH_MAX, "%s/%s", dir_name, d_name);
        
      if (path_length >= PATH_MAX) {
        fprintf (stderr, "Path length has got too long.\n");
        free(path);
        break;
      }
        
      list_dir(path);
        
      memset(path, 0x00, path_length);
      free(path);
      path = NULL;
    }

    printf ("%s/%s\n", dir_name, d_name); /* print path file and filename */
    /* !!! call encrypt file function !!! */
  }

  if (closedir(directory)) {
    fprintf (stderr, "Could not close '%s': %s\n", dir_name, strerror(errno));
    return;
  }
}

int main (int argc, char * argv[]) {
  int i;

  if (argc > 1) {
    for (i = 1; i < argc; i++) {
      list_dir(argv[i]);
    }
  }

  return 0;
}
