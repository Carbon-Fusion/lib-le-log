/*   This file is part of lib-le-log.

   lib-le-log is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   lib-le-log is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with lib-le-log.  If not, see <http://www.gnu.org/licenses/>
*/

/*
Copyright © of Carbon-Fusion (www.github.com/Carbon-Fusion)
*/

/*
* Written / Contributed by
* DevUt (www.github.com/DevUt)
* naiylk (www.github.com/nailyk-fr)
*/
#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#ifndef LOG_LOC
#define LOG_LOC "/cache/lible.log"
#endif


int klog(char *msg, ...)
{
 // Combine all the arguments into a string
 va_list arg; // Declare the arg as the list
 va_start(arg,msg); // start reading
 char *var_combined ; // This variable contains string when it has been "stiched" or combined or strcat'd together
 vasprintf(&var_combined , msg, arg); // Magic HAppens ! vasprintf returns the strcat'd string and stores into var_combined
 va_end(arg); // End the list

char *buf = malloc(sizeof(char) * 256); // Allocate buf variable
int ret = -1; // The return value to have a default error

 // Write to kmsg if possibe.
int outbuf = open("/dev/kmsg", O_WRONLY);
 if (outbuf > 0) // Trying to open KMSG,
 {
   strcpy(buf,msg);
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

 int logwarn(char *warning, ...)
 {
   // Combine all the arguments into a string
   va_list arg; // Declare the arg as the list
   va_start(arg,warning); // start reading
   char *var_combined  ; // This variable contains string when it has been "stiched" or combined or strcat'd together
   vasprintf(&var_combined , warning, arg); // Magic HAppens ! vasprintf returns the strcat'd string and stores into var_combined
   va_end(arg); // End the list

   char warn[256] ="Warning! : "  ;
   strcat(warn,var_combined);
   int ret = klog(warn);
   return(ret);

 }

 int logerror(char *error, ...)
 {
   // Combine all the arguments into a string
   va_list arg; // Declare the arg as the list
   va_start(arg,error); // start reading
   char *var_combined ; // This variable contains string when it has been "stiched" or combined or strcat'd together
   vasprintf(&var_combined , error, arg); // Magic HAppens ! vasprintf returns the strcat'd string and stores into var_combined
   va_end(arg); // End the list

   char error_tag[256] ="Error! : "  ;
   strcat(error_tag,var_combined);
   int ret = klog(error_tag);
   return(ret);
 }
 int logdebug (char *debug_msg, ...)
 {
   // Combine all the arguments into a string
   va_list arg; // Declare the arg as the list
   va_start(arg,debug_msg); // start reading
   char *var_combined ; // This variable contains string when it has been "stiched" or combined or strcat'd together
   vasprintf(&var_combined , debug_msg, arg); // Magic HAppens ! vasprintf returns the strcat'd string and stores into var_combined
   va_end(arg); // End the list

   char debug_tag[256] = "Debug : ";
   strcat(debug_tag,var_combined);
   int ret = klog(debug_tag);
   return(ret);
 }
 int loginfo (char *info, ...)
 {
   // Combine all the arguments into a string
   va_list arg; // Declare the arg as the list
   va_start(arg,info); // start reading
   char *var_combined ; // This variable contains string when it has been "stiched" or combined or strcat'd together
   vasprintf(&var_combined , info, arg); // Magic HAppens ! vasprintf returns the strcat'd string and stores into var_combined
   va_end(arg); // End the list

   char info_tag[256] = "Info : ";
   strcat(info_tag,var_combined);
   int ret = klog(info_tag);
   return(ret);
 }
