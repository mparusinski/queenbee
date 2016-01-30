#include "usage.h"
#include "common.h"

#include <stdio.h>

void display_usage( void ) {
  puts( "Usage: " NAME " [executable]");
  puts(  NAME " is an application wrapper which automatically detects \n"
        "integrated / dedicated GPU setups and executes application \n"
        "against best GPU" );
  puts( "" );
  puts( "-h, --help     displays this help section" );
  puts( "--version      displays the version number");
}
