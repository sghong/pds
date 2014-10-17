/*
 * =====================================================================================
 *
 *       Filename:  sleep_poll.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/01/12 09:15:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <poll.h>

void sleep_us(unsigned int nusecs)
{
    struct pollfd dummy;

    int timeout;

    if( (timeout = nusecs / 1000) <= 0)
        timeout = 1;
    poll(&dummy, 0, timeout);
}
