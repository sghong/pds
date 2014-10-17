/*
 * =====================================================================================
 *
 *       Filename:  tst.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/28/12 09:45:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

static int a=0;

#define MSEC_TO_HZ(ms)     (1000.0/(ms))

int main( int argc, char * const argv[]) 
{

#if 0
    pid_t wpid;
    int a=0;
    if(a)
        ;//break;
    wpid = wait(NULL);
    printf("%d\n", wpid);
    open
    dlopen

    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
    //printf("%d\n", sizeof(int));
#endif

#if 1
    printf("%f hz\n", MSEC_TO_HZ( atoi(argv[1]) ));
#endif

    return 0;
}
