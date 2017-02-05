int klog(int level, char *msg);

#define MAX_MESSAGE_LEN 256

#ifndef ALT_LOG_LOC
 #define ALT_LOG_LOC "/cache/lible.log"
#endif

#ifndef DEFAULT_LOG_LOC
  #define  DEFAULT_LOG_LOC "/dev/kmsg"
#endif

#ifdef LOG_WRAP_TAGS
  #define INFO "I:"
  #define WARN "W:"
  #define ERROR "E:"
  #define DEBUG "D:"
#else
  #define INFO "Info :"
  #define WARN "Warn :"
  #define ERROR "Error :"
  #define DEBUG "Debug :"
#endif 
