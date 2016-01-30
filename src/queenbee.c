#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "common.h"
#include "unix_toolkit.h"

#define OPTSTR "vh"

void init_args() {
  ARGUMENTS.verbose = 0;
  ARGUMENTS.mock_execution = 0;
  ARGUMENTS.executable_path = NULL;
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
  puts( "-h, --help             displays this message" );
  puts( "-v, --version          displays the version number" );
  puts( "-m, --mock-execution       do not run the specified file (profiling only)" );
}

int main(int argc, char *argv[]) {
  extern int optind;
  int long_index = 0;
  int opt = 0;

  struct option long_opts[] = {
    { "help", no_argument, NULL, 'h' },
    { "version", no_argument, NULL, 'V' },
    { "verbose", no_argument, NULL, 'v' },
    { "mock-execution", no_argument, NULL, 'm' },
    { NULL, 0, NULL, 0 }
  };

  init_args();

  opt = getopt_long( argc, argv, OPTSTR, long_opts, &long_index  );
  while ( opt != -1 ) {
    switch ( opt ) {
      case 'v':
        ARGUMENTS.verbose = 1;
        break;
      case 'V':
        display_version();
        return EXIT_SUCCESS;
      case 'h':
        display_usage();
        return EXIT_SUCCESS;
      case 'm':
        ARGUMENTS.mock_execution = 1;
        break;
      case 0:
        fprintf(stderr, "Invalid argument\n");
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
    ARGUMENTS.executable_path = argv[optind];
  }

  char * exec_argv[] = { ARGUMENTS.executable_path, (char *)0 };
  exec_wrapper(ARGUMENTS.executable_path, exec_argv);

  return EXIT_SUCCESS;
}
