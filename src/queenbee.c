#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "common.h"

#define OPTSTR "vh"

typedef struct {
  char * executable_path;
} args_t;

void init_args( args_t * arguments ) {
  arguments->executable_path = NULL;
}

struct option long_opts[] = {
  { "help", no_argument, NULL, 'h' },
  { "version", no_argument, NULL, 'v' },
  { NULL, required_argument, NULL, 0 }
};

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
  args_t arguments;
  int long_index = 0;
  int opt = 0;

  init_args(&arguments);

  opt = getopt_long( argc, argv, OPTSTR, long_opts, &long_index  );
  while ( opt != -1 ) {
    switch ( opt ) {
      case 'v':
        display_version();
        return EXIT_SUCCESS;
      case 'h':
        display_usage();
        return EXIT_SUCCESS;
      case 0:
        return EXIT_FAILURE;
      default: // Should not get here
        return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
