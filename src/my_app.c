/*
 * =====================================================================================
 *
 *       Filename:  my_app.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/11/14 14:46:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <pthread.h>

void * my_handler1(void* data )
{
    printf("my_halder1\n");
}

void * my_handler2(void* data )
{
    printf("my_halder1\n");
}

int main()
{
    pthread_t tid1, tid2;

    pthread_create(&tid1, 0, my_handler1, 0);
    pthread_create(&tid2, 0, my_handler2, 0);

    pthread_join( tid1, 0 );
    pthread_join( tid2, 0 );
    return 0;
}

