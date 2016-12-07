#########################################################################
# Copyright (C) of Carbon Fusion org @ github.com/Carbon-Fusion
#
# License:
#
#    This file is part of lib-le-log.
#
#
##########################################################################
#
# include this lib with:
#       source kmsg_log
#       or
#       . kmsg_log
#
# usage:
#       loginfo "This lib-le-log is too great for you"
#       logwarn "This lib-le-log is too great for you"
#       logerror "This lib-le-log is too great for you"
#       logdebug "This lib-le-log is too great for you"
#
#########################################################################

# check if we are sourced or directly called
[ "$0" = "$BASH_SOURCE" ] && SOURCED=no || SOURCED=yes
# debug only:
# echo "process $$ is $SOURCED ($0, $BASH_SOURCE)"

loglevel="$1"

# define the max possible log message length
MAXLENGTH=256

# log destination
LOG=/dev/kmsg

# print error
F_PRINTERR(){
    echo "ERROR: This message cannot be logged because it's either too long or invalid!"
}

# debug output
logdebug(){
    unset LEVEL MSG
    LEVEL="DEBUG:"
    MSG="$(F_CHKMSG "$1")"
    if [ "$MSG" == "invalid" ];then
        F_PRINTERR  >> $LOG
    else
        echo "$LEVEL $MSG" >> $LOG
    fi
}

# print info message
loginfo(){
    unset LEVEL MSG
    #logdebug "calling $FUNCNAME"
    LEVEL="INFO:"
    MSG="$(F_CHKMSG "$1")"
    if [ "$MSG" == "invalid" ];then
        F_PRINTERR 
    else
        echo "$LEVEL $MSG" >> $LOG
    fi
}

# print warning message
logwarn(){
    unset LEVEL MSG
    #logdebug "calling $FUNCNAME"
    LEVEL="WARNING:"
    MSG="$(F_CHKMSG "$1")"
    if [ "$MSG" == "invalid" ];then
        F_PRINTERR  >> $LOG
    else
        echo "$LEVEL $MSG" >> $LOG
    fi
}

# print error message
logerror(){
    unset LEVEL MSG
    #logdebug "calling $FUNCNAME"
    LEVEL="ERROR:"
    MSG="$(F_CHKMSG "$1")"
    if [ "$MSG" == "invalid" ];then
        F_PRINTERR >> $LOG
    else
        echo "$LEVEL $MSG" >> $LOG
    fi
}

# check message string to avoid misusage
F_CHKMSG(){
    unset CMSG
    CMSG="$1"
    #echo "checkin $CMSG"
    if [ "${#CMSG}" -gt $MAXLENGTH ];then
        echo "invalid"
    else
        # TODO: check for unusual chars?!

        # return log message to the calling function
        echo "$CMSG"
    fi
}
