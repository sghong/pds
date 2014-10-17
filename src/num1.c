/*
 * =====================================================================================
 *
 *       Filename:  num1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/11/14 10:16:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(void)
{
    int num1 = 10;
    int num2 = (num1--)+2;

    printf("num1 %d\n",num1);
    printf("num2 %d\n",num2);

    return 0;
}
