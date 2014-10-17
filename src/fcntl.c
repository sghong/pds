/*
 * =====================================================================================
 *
 *       Filename:  fcntl.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/26/14 15:42:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <fcntl.h>   
#include <unistd.h>   
#include <sys/types.h>   
#include <sys/stat.h>   
#include <stdio.h>   
#include <string.h>   
 
#define STDIN 0   
int main()   
{   
    int mode, fd, value;   
    char buf[255];   

    memset(buf, 0x00, 255);   

    // 처음 입력은 봉쇄모드로   
    read (STDIN, buf, 255);   
    printf("-> %s\n", buf);   
    memset(buf, 0x00, 255);   

    // NONBLOCKING 모드로 변경한다.   
    value = fcntl(STDIN, F_GETFL, 0);   
    value |= O_NONBLOCK;   
    fcntl(STDIN, F_SETFL, value);   
    printf("NON BLOCKING MODE 로 변경 \n");   

    // 2초후 비봉쇄 모드로 들어간다.   
    sleep(2);   

    // 바쁜대기(busy wait) 시작   
//    while(1)   
 //   {   
        read (STDIN, buf, 255);   
        printf("-> %s\n", buf);   
  //  }   
        return 0;
}  
