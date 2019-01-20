/*myprintf.h*/

#ifndef __MY_PRINTF_H_
#define __MY_PRINTF_H_


//移植需要考虑的地方
#define print(...)  printf(__VA_ARGS__)


//全局有效


//打印控制地方
#define __DEBUG


#ifdef __DEBUG

    #define PRINT_BARE(...) printf(__VA_ARGS__)
    #define PRINT_ENTER(format,...) print(""format"\n",##__VA_ARGS__)

    #ifdef __SIMPLEDBG
        //#define PRINT_1(format,...) print(""format"\n",##__VA_ARGS__)
        #define PRINT(format,...) print(""format"",##__VA_ARGS__)
    #else
        #define PRINT(format,...) print("File: %s, Line: %05d: %-30s"format"",__FILE__, __LINE__,"debug1", ##__VA_ARGS__)
    #endif
#else
    #define PRINT(format,...)
#endif


#ifdef __DEBUG_2
    #ifdef __SIMPLEDBG
        #define PRINT_2(format,...) print(""format"",##__VA_ARGS__)
    #else
        #define PRINT_2(format,...) print("File: %s, Line: %05d: %-30s"format"",__FILE__, __LINE__,"debug2", ##__VA_ARGS__)
    #endif
#else
    #define PRINT_2(format,...)
#endif










#endif
