/*
 * =====================================================================================
 *
 *       Filename:  do_while.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/12/14 18:09:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>

//#define error(code,text) do{ fprintf(stderr,"%s\n", "ddd"); } while(0)
#define error(code,text) fprintf(stderr,"%s\n", "ddd");  fprintf(stderr,"%s\n", "ddd");

int main(void)
{
    //{error(a1,a2)}
    if(0)
      error(a1,a2);
    else
       printf("here\n");

    return 0;
}
