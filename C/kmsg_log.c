#include <stdio.h>
#include <unistd.h>

int klog(int level,char a [ ] )
{
  // Open KMSG to write ;
 int kmsg = open("/dev/kmsg", O_WRONLY);
  if (kmsg > 0) // CHECK IF OPENING KMSG DIDNT RETURN ANY ERRORS ;
  {
  write(kmsg, "Test"); // WRITE TO IT
  } else {

    close(kmsg); // CLOSE THE FILE DISCRIPTOR TO AVOID LEAK ;

    /*
      Now if the file doesnt exists
      we would open another the file
      on sdcard to transmit our msg
    */
    int skmsg = access(fname, F_OK ) ;  // CHECK IF THE FILE EXISTS
    if (skmsg == "-1") {  // IF IT DOESNT EXISTS THEN
      sdkmsg = open("/sdcard/liblelog", O_CREAT); // CREATE IT
      close(sdkmsg); // CLOSE THE DISCRIPTOR WITH O_CREAT VALUE
    }

    /*
      CHECKING STAGE DONE
      NOW WE WWOULD WRITE TO IT
    */
      sdkmsg = open("/sdcard/liblelog",O_WRONLY) // OPEN TO WRITE
      write(sdkmsg, "ERROR: COULD NOT OPEN KMSG PLEASE FIX ");// WRITE THE ERRORS
      close(sdkmsg); // CLOSE THE FILE DISCRIPTOR TO AVOID LEAK ; 



}
