/***************************************************
 *         Author: yi                              *
 *         Date  : 2017/9/3                        *
 *         Last  : 2017/9/3                        *
 *         Notes : 8位数码管显示                    *
 *           P2 | P0                               *
 **************************************************/

#include <REGX52.h>
#include "shumaguan.h"

unsigned char code NUM_TAB[11]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x86};//共阳数码管段码
unsigned char X_tab[4];
unsigned char Y_tab[4];

void shumaguan()
{
  static unsigned char i;
  LED_DATA=0xff;  //消除残影
  switch (i) {
    case 0:
    LED_WEIXUAN=0xfe;//11111110
    LED_DATA=NUM_TAB[X_tab[0]];break;
    case 1:
    LED_WEIXUAN = 0xfd;//11111101
    LED_DATA=NUM_TAB[X_tab[1]];break;
    case 2:
    LED_WEIXUAN=0xfb;//11111011
    LED_DATA=NUM_TAB[X_tab[2]];break;
    case 3:
    LED_WEIXUAN=0xf7;//11110111
    LED_DATA=NUM_TAB[X_tab[3]];break;
    case 4:
    LED_WEIXUAN=0xef;//11101111
    LED_DATA=NUM_TAB[Y_tab[0]];break;
    case 5:
    LED_WEIXUAN=0xdf;//11011111
    LED_DATA=NUM_TAB[Y_tab[1]];break;
    case 6:
    LED_WEIXUAN=0xbf;//10111111
    LED_DATA=NUM_TAB[Y_tab[2]];break;
    case 7:
    LED_WEIXUAN=0x7f;//01111111
    LED_DATA=NUM_TAB[Y_tab[3]];break;
  }
  /*---------------------------------
  可以写一些延时语句 费时计算
  ---------------------------------*/
  LED_DATA=0xff;
  if (i<7) {
    i++;
  } else {
    i=0;
  }
}
