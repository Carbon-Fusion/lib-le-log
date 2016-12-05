#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define LOG_LOC "/sdcard/lible.log"

int klog(__attribute__((unused)) int level,__attribute__((unused)) char * a )
{

 char *buf = malloc(sizeof(char) * 256);
 int ret = -1; 

  // Write to kmsg if possibe.
 int kmsg = open("/dev/kmsg", O_WRONLY);
  if (kmsg > 0) // Trying to open KMSG, if it doesn't return any error, continue executing the code.
  {
    strcpy(buf,"Test\n");

    ret = write(kmsg, buf, strlen(buf) ); // Write to KMSG.
    close(kmsg); // Close the file discriptor to avoid any leaks.
  } else {
    /*
      Now if the file doesn't exists, we would open another file on the sdcard to transmit our KMSG.
    */
	int sdkmsg; 

    if (access(LOG_LOC, F_OK ) == -1) {  // Check if the file exists.
      sdkmsg = open(LOG_LOC, O_CREAT | O_WRONLY); // If it doesn't exist, create it and open it to write to it.

    } else {
		/*
		* TODO: Make better file checks.
		*/
	  sdkmsg = open(LOG_LOC, O_APPEND); // Else, assume file already exist: Open to append. 
	}

    /*
      Checking is done, now we will write to the KMSG.
    */

      strcpy(buf,"ERROR: COULD NOT OPEN KMSG PLEASE FIX");

      ret = write(sdkmsg, buf, strlen(buf) );// Write any errors.

      close(sdkmsg); // Close the file discriptor to avoid any leaks.

    }

	free(buf); // Empty buf memory.
	return ret;
}
