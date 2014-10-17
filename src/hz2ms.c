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
#define HZ_TO_NSEC(hz)     (1000000000LL/(hz))
#define NSEC_TO_MSEC(nsec) ((nsec)/1000000LL)

int main( int argc, char * const argv[]) 
{
   float seconds;
#if 0
    pid_t wpid;
    int a=0;
    if(a)
        ;//break;
    wpid = wait(NULL);
    printf("%d\n", wpid);
    //printf("%d\n", sizeof(int));
#endif

#if 1
    seconds = HZ_TO_NSEC( atoi(argv[1]));
    printf("%f ms\n",  (float)seconds/1000000);
#endif

    return 0;
}
