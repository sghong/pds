/*
 * =====================================================================================
 *
 *       Filename:  ctrl-c-signal.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/20/14 13:57:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <signal.h>
#include <stdio.h>

static int keepRunning = 1;

void intHandler(int dummy)
{
    printf("Done\n");
    keepRunning = 0;
}

int main(void)
{
    signal(SIGINT, intHandler);

    while(keepRunning)
    {
        printf(".");
    }

    return 0;

}
