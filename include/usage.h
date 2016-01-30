#ifndef _QUEENBEE_USAGE_H_
#define _QUEENBEE_USAGE_H_

#include <unistd.h>

struct globalargs_t {
  int version;
} globalargs;

static char * optstr = "vh?";

void display_usage( void );

#endif  // _QUEENBEE_USAGE_H_
