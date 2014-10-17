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
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "fixed_point.h"

#include "CUST_PANTECH_SENSOR.h"

static int a=0;

#define MSEC_TO_HZ(ms)     (1000.0/(ms))
#define HZ_TO_NSEC(hz)     (1000000000LL/(hz))
#define NSEC_TO_MSEC(nsec) ((nsec)/1000000LL)


//#define FX_FLTTOFIX_Q16(f) ((int32)((f)*(1<<(16)))) 5
//#define FX_FIXTOFLT_Q16(i) (((double)(i))/((double)(1<<(16))))


typedef enum {
LOG_LEVEL_ALL,
LOG_LEVEL_VERBOSE,
LOG_LEVEL_DEBUG,
LOG_LEVEL_INFO,
LOG_LEVEL_WARN,
LOG_LEVEL_ERROR,
LOG_LEVEL_DISABLED                                                                                               
} log_level_e;

static log_level_e g_log_level = LOG_LEVEL_WARN;

unsigned char init_sensor_register_array[][2] = {   // initial                                                     
    {0xEF,0x00},
    {0x37,0x07},
    {0x38,0x17},
    {0x39,0x06},
    {0x46,0x2D},
    {0x47,0x0F},
    {0x4A,0x50},
};

#define INIT_SENSOR_REG_ARRAY_SIZE (sizeof(init_sensor_register_array)/sizeof(init_sensor_register_array[0]))


int main( int argc, char * const argv[]) 
{
#if 0
    printf("argc %d\n", argc);
    printf("argv %s\n", argv[0]);
    printf("argv %c\n", argv[0][0]);
    printf("argv %c\n", argv[0][1]);
    printf("argv %c\n", argv[0][2]);
    printf("argv %c\n", argv[0][3]);
    printf("argv %c\n", argv[0][4]);
    printf("argv %c\n", argv[0][5]);
#endif
#if 0
    int i;
    for(i = 0; i < INIT_SENSOR_REG_ARRAY_SIZE;i++){
        printf("%x %x\n", init_sensor_register_array[i][0], init_sensor_register_array[i][1]);
    }
#endif
#if 0

    int fd;

    fd = open("/dev/ddd",O_RDWR | O_APPEND);

    printf("fd %d\n",fd);
#endif

#if 0
    pid_t wpid;
    int a=0;
    if(a)
        ;//break;
    wpid = wait(NULL);
    printf("%d\n", wpid);
    //printf("%d\n", sizeof(int));
#endif

#if 0
//    printf("%f hz\n",  NSEC_TO_MSEC( HZ_TO_NSEC( atoi(argv[1])) ) );
    printf("%f\n", 0.4f );
#endif

#if 0
    unsigned char data1 = 0x0;
    unsigned char data2 = 0x0;
    int ret;

    printf("%x\n", ( data1 & 0x10 ) >> 4);
    printf( "%x\n", ((data1&~0x01)|((1<<0)&0x01)) );

    ret = closedir(NULL);
    printf("ret = [%d]\n",ret);
#endif
#if 0 
    char a = 4;
    static char read_buf[4096];

    char* pc;

    pc = a;
#if 0
#error code present
#endif

    printf("%x\n",FX_FLTTOFIX_Q16(0.02));
    printf("%x\n", FX_FLTTOFIX_Q16(0.02));
    printf("%x\n",FX_FLTTOFIX_Q16(2));
    printf("%x\n",FX_G_Q16);
    printf("%f\n",G);
    //printf("===%d\n",sizeof(read_buf));


    printf("]]]%d\n",++a);

#endif
#if 1
    int ch;
    do{
        ch = getchar();
        printf("%c %d\n", ch, ch);
    }while(ch != 13);
#endif

    return 0;
}
