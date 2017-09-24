/***************************************************
 *         Author: yi                              *
 *         Date  : 2017/9/23                       *
 *         Last  : 2017/9/24                       *
 *         Notes : ad采样 并将结果送至 X_int和Y_int  *
 *         使用用外部中断0 定时器0                   *
 **************************************************/
#include <REGX52.h>
#include "ad_ICL7135.h"

bit turn; //用于控制交替采样
unsigned int X_int; //ad 采样结果
unsigned int Y_int; //ad 采样结果

/************************ad初始化**************************/
void init_ad() {
  IT   = 1; //外部中断-下降沿触发，停止计数。进入中断程序。
  TH   = 0; //T0 计数清零
  TL   = 0; //T0 计数清零
  TMOD = 0x0d|TMOD; //T0 16位计算模式  TR0和/INT0同为 1 时计数
  EX0  = 1; //开放外部中断0
  TR0  = 1; //启动计数器
  EA   = 1; //开放外部总中断
  X_run= 1; //开启一芯片采样
  Y_run= 0; //另一芯片等待
}

 /**********************中断计数程序***********************/
void timer0() interrupt 1  { //把ad转换所需脉冲数放置到 X_int
  if (0 == turn) {
    X_run = 0;  //X ad停止转换,进入自动调零阶段
    X_int = (TH0*256+TL0-10000);  //X 反向积分阶段完成开始计算
    TH0   = 0;
    TL0   = 0;
    Y_run = 1;
  }
  else{
    Y_run = 0;
    Y_int = (TH0*256+TL0-10000);
    TH0   = 0;
    TL0   = 0;
    X_run = 1;
  }
  turn = !turn;
}
