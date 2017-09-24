#ifndef ad_ICL7135_h
#define ad_ICL7135_h

/*-----------------------------------------
    由于需要采样2路模拟信号故使用了2片7135
------------------------------------------*/

sbit X_run=P1^6;  //ad芯片转换启动控制io-run
sbit Y_run=P1^7;  //ad芯片转换启动控制io-run

extern unsigned int X_int; //ad 采样结果
extern unsigned int Y_int; //ad 采样结果

extern void init_ad();  //ad初始化

#endif
