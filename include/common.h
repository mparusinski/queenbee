#ifndef _QUEENBEE_COMMON_H_
#define _QUEENBEE_COMMON_H_

#define NAME "queenbee"
#define MAJOR_VERSION 0
#define MINOR_VERSION 2
#define REVISION 2

struct args_t {
  int verbose;
  char * executable_path;
} ARGUMENTS;

#define IS_VERBOSE (ARGUMENTS.verbose > 1)

#endif // _QUEENBEE_COMMON_H_
