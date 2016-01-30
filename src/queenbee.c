#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common.h"

#define OPTSTR "vh"

typedef struct {
} args_t;

void init_args( args_t * arguments ) {
}

void display_version( void ) {
  char str[32];
  sprintf(str, NAME " version %d.%d.%d", MAJOR_VERSION, MINOR_VERSION, REVISION);
  puts(str);
}

void display_usage( void ) {
  puts( "Usage: " NAME " [executable]");
  puts(  NAME " is an application wrapper which automatically detects \n"
        "integrated / dedicated GPU setups and executes application \n"
        "against best GPU" );
  puts( "" );
  puts( "-h      displays this help section" );
  puts( "-v      displays the version number");
}

int main(int argc, char *argv[]) {
  args_t arguments;
  int opt = 0;

  init_args(&arguments);

  opt = getopt( argc, argv, OPTSTR );
  while ( opt != -1 ) {
    switch ( opt ) {
      case 'v':
        display_version();
        return EXIT_SUCCESS;
      case 'h':
        display_usage();
        return EXIT_SUCCESS;
      default:
        display_usage();
        return EXIT_SUCCESS;
    }
  }

  return EXIT_SUCCESS;
}
