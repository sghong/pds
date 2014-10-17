#include <unistd.h>   
#include <stdlib.h>   
#include <stdio.h>   
#include <fcntl.h>   
#include <sys/types.h>   
#include <sys/stat.h>   

int main()   
{   
    int fd;   
    int val;   
    fd = open("exec_copy.txt", O_CREAT);   
        printf("fd %d\n",fd);   

    val = fcntl(fd, F_GETFD, 0);   
    if (val & FD_CLOEXEC)   
        printf("close-on-exec bit on\n");   
    else   
        printf("close-on-exec bit off\n");   


    val |= FD_CLOEXEC;   
    //val &= ~FD_CLOEXEC;   

    if (val & FD_CLOEXEC)   
        printf("close-on-exec bit on\n");   
    else   
        printf("close-on-exec bit off\n");   
    fcntl(fd, F_SETFD, val);   

    // loop 프로그램을 exec 시킨다.     
    execl("/home/p12791/tmp/loop", "./loop", NULL);
}  
