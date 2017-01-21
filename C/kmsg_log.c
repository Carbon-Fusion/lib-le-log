#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#ifndef LOG_LOC
 #define LOG_LOC "/cache/lible.log"
#endif


int klog(char *msg)
{

 char *buf = malloc(sizeof(char) * 256);
 int ret = -1;

  // Write to kmsg if possibe.
 int outbuf = open("/dev/kmsg", O_WRONLY);
  if (outbuf > 0) // Trying to open KMSG,
  {
    strcpy(buf,*msg);
  } else { //If kmesg don't open write to sd
    /*
      Now if the file doesn't exists, we would open another file on the sdcard to transmit our KMSG.
    */
    if (access(LOG_LOC, F_OK ) == -1) {  // Check if the file exists.
      outbuf = open(LOG_LOC, O_CREAT | O_WRONLY); // If it doesn't exist, create it and open it to write to it.

    } else {
		/*
		* TODO: Make better file checks.
		*/
	  outbuf = open(LOG_LOC, O_APPEND); // Else, assume file already exist: Open to append.
	}

    /*
      Checking is done, now we will write to the KMSG.
    */

      strcpy(buf,"COULD NOT OPEN KMSG PLEASE FIX");

    }

	ret = write(outbuf, buf, strlen(buf) ); // Write "Test" to KMSG

	close(outbuf); // CLOSE THE FILE DISCRIPTOR TO AVOID LEAK ;

	free(buf); // Empty buf memory.
	return ret;
}

	int logwarn(char *warning)
	{
		char *warn ="Warning! : "  ;
		strcat(*warn,*warning);
		int ret = klog(*warn);
		return(ret);
	}

	int logerror(char *error)
	{
		char *error_tag ="Error! : "  ;
		strcat(*error_tag,error);
		int ret = klog(*error_tag);
		return(ret);
	}
	int logdebug (char *debug_msg)
	{
		char *debug_tag = "Debug : ";
		strcat(*debug_tag,debug_msg);
		int ret = klog(*debug_tag);
		return(ret);
	}
	int loginfo (char *info)
	{
		char *info_tag = "Info : ";
		strcat(*info_tag,info);
		int ret = klog(*info_tag);
		return(ret);
	}
