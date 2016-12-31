#Lib-le-Log 

This Library is licensed under LGPL v3

This Library is a clear way of logging to /dev/kmsg easily from any point of the "Android Source Code" 

    It supports mulitple-languages 
    Currently supported : C and SH/bash 

##C usage :  

 To use for writing a Simple Message into the kmsg without any tags use 
  
     klog("YOUR MSG IS HERE") ;
     // result in /dev/kmsg
     // [2.56] YOUR MSG IS HERE
     
*Note : You __cant__ use the "%s" deceleration for passing strings to klog functions* **THIS A BUG AND WOULD BE FIXED IN THE NEXT RELEASE**

E.G 

      char *a = "YOUR MESSAGE IS HERE" ; 
      klog("%s",*a); // This is not valid 
      
      /* The error message would be 
       * error: too many arguments to function call, expected single argument 'msg', have 2 arguments
       * klog("%s",*a);
       */
    
 Using the warning tag 
    
      logwarn("YOUR MESG IS HERE "); 
      // result in /dev/kmsg
      // [2.43] Warning! : YOUR MSG HERE 
      // Warning function uses klog as parent function 
 
Using the Info tag 
    
      loginfo("YOUR MESG IS HERE "); 
      // result in /dev/kmsg
      // [2.49] Info : YOUR MSG HERE 
      // Info function uses klog as parent function 
      
 
Using the Error tag 
    
      logerror("YOUR MESG IS HERE "); 
      // result in /dev/kmsg
      // [2.53] Error! : YOUR MSG HERE 
      // Error function uses klog as parent function  
   

Using the Debug tag 
    
      logdebug("YOUR MESG IS HERE "); 
      // result in /dev/kmsg
      // [2.68] Debug : YOUR MSG HERE 
      // Debug function uses klog as parent function    

     
     
    //TODO ADD SH README
