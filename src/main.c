#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <estia-image.h>
#include <getopt.h>

#include "features.h"
#include "utils.h"
#include "argsparse.h"

int main(int argc, char **argv) {
  /*To use debug mode: 
   - add --debug: freud.exe --debug -f images/input/image.jpeg
   or 
   - Simply run your compiled project with start button on the blue menu bar at the bottom of the VS Code window.
   */

  /*DO NOT EDIT THIS PART*/
  Config configuration ;
  parse_arguments( argc, argv, &configuration ) ;
  check_debug_mode(configuration);
  check_file();
  /* END */

  /* Use "if ( strncmp( command, <commandname>, 9 ) == 0 )" to check if your <commandname> is called by program.*/
  /* Example with helloworld command
   * If helloworld is a called command: freud.exe -f images/input/image.jpeg -c helloworld 
   */
  if ( strncmp( configuration.command, "helloworld", 10 ) == 0 ) {
    /* helloworld() function is defined in feature.h and implemented in feature.c */
    helloWorld();
  }
  /*
   * TO COMPLETE
   */
  
  return 0;
}
else if (strncmp(configuration.command, "dimension", 9) == 0) {
    if (configuration.filenames_count < 1) {
        fputs("error: aucun fichier spécifié pour « dimension »\n", stderr);
        return 1;
    }
    dimension(configuration.filenames[0]);
}


else if ( strncmp( configuration.command, "first_pixel", 11 ) == 0 ) {
    first_pixel(configuration.filenames[0]);
    return 0;
}

else if ( strncmp( configuration.command, "tenth_pixel", 11 ) == 0 ) {
    tenth_pixel(configuration.filenames[0]);
}

else if (strncmp(configuration.command, "second_line", 11) == 0) {
        if (configuration.filenames_count < 1) return 1;
        second_line(configuration.filenames[0]);
    }

else if (strncmp(configuration.command, "max_pixel", 9) == 0) {
    if (configuration.filenames_count < 1) return 1;
    max_pixel(configuration.filenames[0]);
}

else if (strncmp(configuration.command, "min_pixel", 9) == 0) {
    if (configuration.filenames_count < 1) return 1;
    min_pixel(configuration.filenames[0]);
}

else if ( strncmp( configuration.command, "print_pixel", 11 ) == 0 ) {
    print_pixel(configuration.filenames[0]);
    return 0;
}

else if ( strncmp( configuration.command, "color_red", 9 ) == 0 ) {
    color_red(configuration.filenames[0]);
    return 0;
}

else if (strncmp(configuration.command, "max_component", 13) == 0) {
    if (configuration.filenames_count < 1) return 1;
    if (configuration.argc_extra < 1) return 1;
    char comp = configuration.extra_args[0][0];
    max_component(configuration.filenames[0], comp);
}

else if (strncmp(configuration.command, "min_component", 13) == 0) {
    if (configuration.filenames_count < 1 || configuration.argc_extra < 1) return 1;
    char comp = configuration.extra_args[0][0];
    min_component(configuration.filenames[0], comp);
}

else if (strncmp(configuration.command, "stat_report", 11) == 0) {
    if (configuration.filenames_count < 1) return 1;
    stat_report(configuration.filenames[0]);
}