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

/*
  This function just basically takes the input
  arg and prints it to /dev/kmsg.
  Its final printing point can be changed from
  /dev/kmsg to any other location
  using the Header LOG_LOC
  currently if it cant open kmsg it logs it
  in the /cache/lible.log
  */
int klog(char *msg)
{

 char *buf = malloc(256);
 int ret = -1;


 int outbuf = open("/dev/kmsg", O_WRONLY);
  if (outbuf > 0)
  {
    strcpy(buf,msg);
  } else { //If kmesg don't open write to sd
    /*
      Now if the file doesn't exists, we would open another file on the sdcard to transmit our KMSG.
    */
    if (access(LOG_LOC, F_OK ) == -1){ // Check if the file exists.
      outbuf = open(LOG_LOC, O_CREAT | O_WRONLY); // If it doesn't exist, create it and open it to write to it.
    } else {
		/*
		* TODO: Make better file checks.
		*/
	  outbuf = open(LOG_LOC, O_APPEND); // Else, assume file already exist: Open to append.
	}
      strcpy(buf,"COULD NOT OPEN KMSG PLEASE FIX");
    }

	ret = write(outbuf, buf, strlen(buf) );

	close(outbuf);
	free(buf);
	return ret;
}

/*
  This functions prefixes the Warning label
  to the real message and sends it to klog
  for real "printing" to kmsg (IF LOG_LOC not defined or used)
*/
int logwarn(char *warning)
{
  char *warn = malloc(256);
   strcpy(warn ,"Warning!: ");
   strcat(warn ,warning);
	int ret = klog(warn) ;
   free(warn);
   return(ret);

}
  /*
    This functions prefixes the Error label
    to the real message and sends it to klog
    for real "printing" to kmsg (IF LOG_LOC not defined or used)
  */
int logerror(char *error_msg)
{
 char *error = malloc(256);
  strcpy(error,"Error!: ");
  strcat(error,error_msg);
 int ret = klog(error);
  free(error);
  return(ret);
}
  /*
    This functions prefixes the debug label
    to the real message and sends it to klog
    for real "printing" to kmsg (IF LOG_LOC not defined or used)
  */
int logdebug (char *debug_msg)
{
  char *debug = malloc(256);
   strcpy(debug,"Error!: ");
   strcat(debug,debug_msg);
  int ret = klog(debug);
   free(debug);
   return(ret);
}
  /*
    This functions prefixes the Info label
    to the real message and sends it to klog
    for real "printing" to kmsg (IF LOG_LOC not defined or used)
  */
int loginfo (char *info_msg)
{
 char *info = malloc(256);
  strcpy(info,"Error!: ");
  strcat(info,info_msg);
 int ret = klog(info);
  free(info);
  return(ret);
}
