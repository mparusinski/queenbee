#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "common.h"

#define OPTSTR "vh"

typedef struct {
  int verbose;
  char * executable_path;
} args_t;

void init_args( args_t * arguments ) {
  arguments->verbose = 0;
  arguments->executable_path = NULL;
}

void display_version( void ) {
  char str[32];
  sprintf(str, NAME " version %d.%d.%d", MAJOR_VERSION, MINOR_VERSION, REVISION);
  puts(str);
}

void display_usage( void ) {
  puts( "Usage: " NAME " [FILE]");
  puts(  NAME " is an application wrapper which automatically detects \n"
        "integrated / dedicated GPU setups and executes application \n"
        "against best GPU" );
  puts( "" );
  puts( "-h, --help         displays this message" );
  puts( "-v, --version      displays the version number");
}

int main(int argc, char *argv[]) {
  extern int optind;
  args_t arguments;
  int long_index = 0;
  int opt = 0;

  struct option long_opts[] = {
    { "help", no_argument, NULL, 'h' },
    { "version", no_argument, NULL, 'V' },
    { "verbose", no_argument, NULL, 'v' },
    { NULL, 0, NULL, 0 }
  };

  init_args(&arguments);

  opt = getopt_long( argc, argv, OPTSTR, long_opts, &long_index  );
  while ( opt != -1 ) {
    switch ( opt ) {
      case 'v':
        arguments.verbose = 1;
      case 'V':
        display_version();
        return EXIT_SUCCESS;
      case 'h':
        display_usage();
        return EXIT_SUCCESS;
      case 0:
        display_usage();
        return EXIT_FAILURE;
      default: // Should not get here
        return EXIT_FAILURE;
    }
  }

  if ((optind + 1) > argc) {
    fprintf(stderr, "Missing executable \n");
    display_usage();
    return EXIT_FAILURE;
  } else if (argc > (optind + 1)) {
    fprintf(stderr, "Too many arguments\n");
    display_usage();
    return EXIT_FAILURE;
  } else {
    arguments.executable_path = argv[optind];
  }

  return EXIT_SUCCESS;
}
