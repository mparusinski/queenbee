#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "common.h"
#include "unix_toolkit.h"

#define OPTSTR "mvVh"

#define ARGS_PARSE_EXIT_SUCCESS 0
#define ARGS_PARSE_EXIT_FAILURE 1
#define ARGS_PARSE_CONTINUE 2

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
  puts( "-V, --version          displays the version number" );
  puts( "-v, --verbose          verbose output");
  puts( "-m, --mock-execution       do not run the specified file (profiling only)" );
}

int matches_option(char * argument, struct option long_opts[], int opts_num,
  int * opt_index) {
  // returns 1 if matches
  if (strlen(argument) >= 2 && argument[0] == '-') {
    if (argument[1] != '-') {
      char optch = argument[1];
      for (int i = 0; i < opts_num; i++) {
        struct option opt = long_opts[i];
        char val = (char) opt.val;
        if (optch == val) {
          *opt_index = i;
          return 1;
        }
      }
    } else {
      char * substr = (char *) &(argument[2]);
      for (int i = 0; i < opts_num; i++) {
        struct option opt = long_opts[i];
        if (strcmp(substr, opt.name) == 0) {
          *opt_index = i;
          return 1;
        }
      }
    }
  }
  return 0;
}

/*
 * The first part of the arguments constitute queenbee options,
 * the second part is the executable and its arguments
 * [queenbee_executable] [queenbee_options] [application_commnand]
 * The whole idea of this script is to discover this smartly and do the split
 * returns 1 is succeesful
 */
int split_arguments(int argc, char* argv[],
    struct option long_opts[], int opts_num,
    int* qb_argc, char*** qb_argv,
    int* app_argc, char*** app_argv) {
  int option_index = 0;
  int skip_option = 0;
  int _qb_argc, _app_argc, i;

  // It is safe to assume the application receives at least two arguments
  if (argc >= 2) {
    for (i = 1; i < argc; i++) { // skipping program
      // Check if it is one of my arguments
      if (skip_option) { // argument to one of the options
        skip_option = 0;
        continue;
      }
      char * curr_arg = argv[i];
      if (curr_arg != NULL) {
        if (matches_option(curr_arg, long_opts, opts_num, &option_index)) {
          struct option opt = long_opts[option_index];
          if (opt.has_arg) {
            skip_option = 1;
          }
        } else {
          // found splitting point
          break;
        }
      }
    }
    _qb_argc = i;
    _app_argc = argc - _qb_argc;

    *qb_argc = _qb_argc;
    *app_argc = _app_argc;

    *qb_argv = (char **) malloc(sizeof(char*) * (_qb_argc + 1));
    *app_argv = (char **) malloc(sizeof(char*) * (_app_argc + 1));

    for (int i = 0; i < _qb_argc; i++) {
      (*qb_argv)[i] = argv[i];
    }
    (*qb_argv)[_qb_argc] = NULL;

    for (int i = 0; i < _app_argc; i++) {
      (*app_argv)[i] = argv[_qb_argc + i];
    }
    (*app_argv)[_app_argc] = NULL;

    return 1;
  } else {
    display_usage();
    return 0;
  }
}

int parse_arguments(int argc, char* argv[]) {
  extern int optind;
  int long_index = 0;
  int opt = 0;
  int qb_argc, app_argc;
  char ** qb_argv, ** app_argv;

  qb_argc = app_argc = -1;
  qb_argv = app_argv = NULL;

  struct option long_opts[] = {
    { "help", no_argument, NULL, 'h' },
    { "version", no_argument, NULL, 'V' },
    { "verbose", no_argument, NULL, 'v' },
    { "mock-execution", no_argument, NULL, 'm' },
    { NULL, 0, NULL, 0 }
  };

  if (!split_arguments(argc, argv, long_opts, 4, &qb_argc, &qb_argv,
      &app_argc, &app_argv)) {
    return ARGS_PARSE_EXIT_FAILURE;
  }

  init_args();

  opt = getopt_long( qb_argc, qb_argv, OPTSTR, long_opts, &long_index  );
  while ( opt != -1 ) {
    switch ( opt ) {
      case 'v':
        ARGUMENTS.verbose = 1;
        break;
      case 'V':
        display_version();
        return ARGS_PARSE_EXIT_SUCCESS;
      case 'h':
        display_usage();
        return ARGS_PARSE_EXIT_SUCCESS;
      case 'm':
        ARGUMENTS.mock_execution = 1;
        break;
      case 0:
        fprintf(stderr, "Invalid argument\n");
        display_usage();
        return ARGS_PARSE_EXIT_FAILURE;
      default: // Should not get here
        return ARGS_PARSE_EXIT_FAILURE;
      }

      opt = getopt_long( qb_argc, qb_argv, OPTSTR, long_opts, &long_index );
  }

  if (app_argc == 0) {
    fprintf(stderr, "Missing executable \n");
    display_usage();
    return ARGS_PARSE_EXIT_FAILURE;
  } else {
    ARGUMENTS.executable_path = app_argv[0];
    ARGUMENTS.executable_arguments = app_argv;
  }

  if (qb_argv != NULL)
    free(qb_argv);

  return ARGS_PARSE_CONTINUE;
}

int main(int argc, char *argv[]) {
  int args_parse_ret_value = parse_arguments(argc, argv);

  switch (args_parse_ret_value) {
    case ARGS_PARSE_EXIT_SUCCESS:
      return EXIT_SUCCESS;
    case ARGS_PARSE_EXIT_FAILURE:
      return EXIT_FAILURE;
    case ARGS_PARSE_CONTINUE:
      break;
  }

  char * exec_argv[] = { ARGUMENTS.executable_path, (char *)0 };
  exec_wrapper(ARGUMENTS.executable_path, exec_argv);

  return EXIT_SUCCESS;
}
