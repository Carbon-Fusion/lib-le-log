#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#ifndef LOG_LOC
 #define LOG_LOC "/cache/lible.log"
#endif
/*
  This is the main function "klog"
  it takes the the log level
  ==================================== \
   label  | loglevel | message         /
  ==================================== \
  | Info  | 0        |  Info :         /
  | Warn  | 1        |  Warn :         \
  | Error | 2        |  Error :        /
  | Debug | 3        |  Debug :        \
  ==================================== /
  then opens the /dev/kmsg or LOG_LOC
  if it cant acces the location
  it tries to open the LOG_LOC
  and print COULD NOT OPEN KMSG PLEASE FIX
*/
int klog(int level, char *msg)
{

 int ret = -1;
 char buf [256];

 int outbuf = open("/dev/kmsg", O_WRONLY);
  if (outbuf > 0)
  {
    switch (level)
     {
      case 0 : buf = "Info :" ;
                strcat(buf,msg);
                break ;

      case 1 : buf = "Warn :";
                strcat(buf,msg);
              break ;
      case 2 : buf = "Error :"
                strcat(buf,msg);
              break ;
      case 3 : buf = "Debug :"
                strcat(buf,msg);
              break ;
      default : buf = "Error : Unknown log level "
                break;
    }


  } else {
    if (access(LOG_LOC, F_OK ) == -1) {
      outbuf = open(LOG_LOC, O_CREAT | O_WRONLY);
    } else {
		/*
		* TODO: Make better file checks.
		*/
	  outbuf = open(LOG_LOC, O_APPEND);
      strcpy(buf,"COULD NOT OPEN KMSG PLEASE FIX");
    }
  }
	ret = write(outbuf, buf, strlen(buf) );
	close(outbuf);

	return ret;
}
