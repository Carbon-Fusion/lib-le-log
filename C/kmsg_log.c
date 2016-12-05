#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define ALT_LOG "/sdcard/lible.log"

int klog(__attribute__((unused)) int level,__attribute__((unused)) char * a )
{

 char *buf = malloc(sizeof(char) * 256);
 int ret = -1; 

  // Write to kmsg if possibe.
 int kmsg = open("/dev/kmsg", O_WRONLY);
  if (kmsg > 0) // Trying to open KMSG, if it doesn't return any error, continue executing the code.
  {
    strcpy(buf,"Test\n");

    ret = write(kmsg, buf, strlen(buf) ); // Write "Test" to KMSG
    close(kmsg); // CLOSE THE FILE DISCRIPTOR TO AVOID LEAK ;
  } else {
    /*
      Now if the file doesn't exists
      we would open another the file
      on sdcard to transmit our msg
    */

	int sdkmsg; 

    if (access(ALT_LOG, F_OK ) == -1) {  // Check if the file exists
      sdkmsg = open(ALT_LOG, O_CREAT | O_WRONLY); // If it doesn't exist, create it and open to write

    } else {
		/*
		* TODO: Make better file checks
		*/
	  sdkmsg = open(ALT_LOG, O_APPEND); // Else, assume file already exist: Open to append. 
	}

    /*
      Checking is done, now we will write to the KMSG
    */

      strcpy(buf,"ERROR: COULD NOT OPEN KMSG PLEASE FIX");

      ret = write(sdkmsg, buf, strlen(buf) );// write errors

      close(sdkmsg); // CLOSE THE FILE DISCRIPTOR TO AVOID LEAK ;

    }

	free(buf); //empty buf memory
	return ret;
}
