#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAX_MESSAGE_LEN 256

#ifndef ALT_LOG_LOC
 #define ALT_LOG_LOC "/cache/lible.log"
#endif

#ifndef DEFAULT_LOG_LOC
  #define  DEFAULT_LOG_LOC "/dev/kmsg"
#endif

/*
  This is the main function "klog"
  it takes the the log level
  ======================================\
   label  | loglevel | message          /
  ======================================\
  | Info  | 0        |  Info :    || I: /
  | Warn  | 1        |  Warn :    || W: \
  | Error | 2        |  Error :   || E: /
  | Debug | 3        |  Debug :   || D: \
  ===================================== /
  then opens the /dev/kmsg or DEFAULT_LOG_LOC (if defined) ,
  if it cant acces the location ,
  it tries to open the ALT_LOG_LOC ,
  and writes "COULD NOT OPEN KMSG PLEASE FIX".
*/
int klog(int level, char *msg)
{

 int ret = -1;
 char buf [256];

 int outbuf = open(DEFAULT_LOG_LOC, O_WRONLY);
  if (outbuf > 0) // [1] Open the DEFAULT_LOG_LOC
      ;
   else { // IF we cant open the DEFAULT_LOG_LOC
    if (access(ALT_LOG_LOC, F_OK ) == -1) { //Check for ALT_LOG_LOC
      outbuf = open(ALT_LOG_LOC, O_CREAT | O_WRONLY); //IF not create one and open it for reading
    } else { // if ALT_LOG_LOC exists then open it to O_APPEND
		/*
		* TODO: Make better file checks.
		*/
	  outbuf = open(ALT_LOG_LOC, O_APPEND);
      strcpy(buf,"COULD NOT OPEN KMSG PLEASE FIX");
    }
  }
  switch (level)
   {
    case 0 :
            #ifdef LOG_WRAP_TAGS
                snprintf(buf,MAX_MESSAGE_LEN, "%s%s","I:",msg);
            #else
                snprintf(buf,MAX_MESSAGE_LEN, "%s%s","Info :",msg);
            #endif

    case 1 :
            #ifdef LOG_WRAP_TAGS
                snprintf(buf,MAX_MESSAGE_LEN, "%s%s","W:",msg);
            #else
                snprintf(buf,MAX_MESSAGE_LEN, "%s%s","Warn :",msg);
            #endif

    case 2 :
            #ifdef LOG_WRAP_TAGS
                snprintf(buf,MAX_MESSAGE_LEN, "%s%s","E:",msg);
            #else
                snprintf(buf,MAX_MESSAGE_LEN, "%s%s","Error :",msg);
            #endif

    case 3 :
            #ifdef LOG_WRAP_TAGS
                snprintf(buf,MAX_MESSAGE_LEN, "%s%s","D:",msg);
            #else
                snprintf(buf,MAX_MESSAGE_LEN, "%s%s","Debug :",msg);;
            #endif
            break ;
    default : snprintf(buf,MAX_MESSAGE_LEN, "%s","Error : Unknown log level");
              break;
          }
	ret = write(outbuf, buf, strlen(buf) );
	close(outbuf);

	return ret;
}
