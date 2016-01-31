#ifndef _QUEENBEE_COMMON_H_
#define _QUEENBEE_COMMON_H_

#define NAME "queenbee"
#define MAJOR_VERSION 0
#define MINOR_VERSION 2
#define REVISION 2

struct args_t {
  int verbose;
  int mock_execution;
  char * executable_path;
  char ** executable_arguments;
} ARGUMENTS;

#define IS_VERBOSE (ARGUMENTS.verbose >= 1)
#define MOCK_EXECUTE (ARGUMENTS.mock_execution >= 1)

#endif // _QUEENBEE_COMMON_H_
