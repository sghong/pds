/*
 * =====================================================================================
 *
 *       Filename:  sleep_select.c
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  11/01/12 09:12:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <sys/select.h>

void sleep_us(unsigned int nusecs)
{
    struct timeval tval;

    tval.tv_sec = nusecs / 1000000;
    tval.tv_usec = nusecs % 1000000;
    selcet(0,NULL,NULL,NULL, &tval);
}

int main(void)
{

    return 0;
}
