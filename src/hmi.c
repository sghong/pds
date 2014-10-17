/*
 * =====================================================================================
 *
 *       Filename:  hmi.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/08/14 16:17:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>

#define MAKE_TAG_CONSTANT(A,B,C,D) (((A) << 24) | ((B) << 16) | ((C) << 8) | (D))

#define HARDWARE_MODULE_TAG MAKE_TAG_CONSTANT('H', 'W', 'M', 'T')
#define HARDWARE_DEVICE_TAG MAKE_TAG_CONSTANT('H', 'W', 'D', 'T')  


int main(void)
{
    printf("%x\n",'H' << 24 );

}
