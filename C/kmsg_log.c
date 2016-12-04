#include <stdio.h>
#include <unistd.h>

int klog(int level,char a [ ] )
{
  // Write to kmsg if possibe.
 int kmsg = open("/dev/kmsg", O_WRONLY);
  if (kmsg > 0) // Trying to open KMSG, if it doesn't return any error, continue executing the code.
  {
  write(kmsg, "Test"); // Write "Test" to KMSG
  } else {

    close(kmsg); // CLOSE THE FILE DISCRIPTOR TO AVOID LEAK ;

    /*
      Now if the file doesn't exists
      we would open another the file
      on sdcard to transmit our msg
    */
    int skmsg = access(fname, F_OK ) ;  // Check if the file exists
    if (skmsg == "-1") {  // If it doesn't exist, create it
      sdkmsg = open("/sdcard/liblelog", O_CREAT); 
      close(sdkmsg); // Close the discriptor with the value of "O_CREAT"
    }

    /*
      Checking is done, now we will write to the KMSG
    */
      sdkmsg = open("/sdcard/liblelog",O_WRONLY) // OPEN TO WRITE
      write(sdkmsg, "ERROR: COULD NOT OPEN KMSG PLEASE FIX ");// write errors
      close(sdkmsg); // CLOSE THE FILE DISCRIPTOR TO AVOID LEAK ; 



}
