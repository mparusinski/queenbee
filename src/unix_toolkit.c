#include "unix_toolkit.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "common.h"

int exec_wrapper(char *file, char * argv[]) {
  // argv[] ends with a null pointer
  extern int errno;
  char * whole_cmd_str = NULL;
  int whole_cmd_str_size = 0;
  int argc = 0;

  while (argv[argc] != NULL) {
    argc++;
  }

  if (argc > 0) {
    for (int i = 0; i < argc; i++) {
      whole_cmd_str_size += strlen(argv[i]) + 1; // + 1 for _/\0 in betweeen
    }
  }

  whole_cmd_str = (char *) malloc(sizeof(char) * whole_cmd_str_size);
  memset(whole_cmd_str, 0, whole_cmd_str_size);

  if (argc > 0) {
    for (int i = 0; i < (argc - 1); i++) {
      strcat(whole_cmd_str, argv[i]);
      strcat(whole_cmd_str, " ");
    }
    strcat(whole_cmd_str, argv[argc - 1]);
  }

  if (MOCK_EXECUTE) {
    fprintf(stdout, "%s\n", whole_cmd_str);
  } else {
    int return_value = execvp(file, argv);
    if (return_value == -1) {
      switch (errno) {
        // TODO: Implement a handler for each different error message
        case EACCES:
        default:
          fprintf(stderr, "An unknown error occurred when executing \"%s\"\n",
            whole_cmd_str);
      }
    }
  }
  free(whole_cmd_str);
}
