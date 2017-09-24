#ifndef shumaguan_h
#define shumaguan_h

#define LED_DATA    P2  //LED段选IO abcdefg dp
#define LED_WEIXUAN P0  //LED位选IO 8765 4321

extern unsigned char X_tab[4];
extern unsigned char Y_tab[4];
extern void shumaguan();  //8位数码管用于显示 X_tab Y_tab 中的字符

#endif
