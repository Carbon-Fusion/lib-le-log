#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int klog(int level,char a [ ] )
{
  // Write to kmsg if possibe.
 int kmsg = open("/dev/kmsg", O_WRONLY);
  if (kmsg > 0) // Trying to open KMSG, if it doesn't return any error, continue executing the code.
  {
    char **buf_kmsg;

    strcpy(buf_kmsg,"Test");
    int size_in_buf = strlen(buf_kmsg) ;

    write(kmsg,buf_kmsg,size_in_buf); // Write "Test" to KMSG
  } else {

    close(kmsg); // CLOSE THE FILE DISCRIPTOR TO AVOID LEAK ;

    /*
      Now if the file doesn't exists
      we would open another the file
      on sdcard to transmit our msg
    */
    int sdkmsg = access("/sdcard/lible.log", F_OK ) ;  // Check if the file exists
    if (sdkmsg == "-1") {  // If it doesn't exist, create it
      sdkmsg = open("/sdcard/lible.log", O_CREAT);
      close(sdkmsg); // Close the discriptor with the value of "O_CREAT"
    }

    /*
      Checking is done, now we will write to the KMSG
    */
        char **buf_sd;
      sdkmsg = open("/sdcard/lible.log",O_WRONLY); // OPEN TO WRITE

      strcpy(buf_sd,"ERROR: COULD NOT OPEN KMSG PLEASE FIX");
      int size_in_buf = strlen(buf_sd);

      write(sdkmsg,buf_sd,size_in_buf);// write errors
      close(sdkmsg); // CLOSE THE FILE DISCRIPTOR TO AVOID LEAK ;



    }
}
