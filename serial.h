#ifndef serial_h
#define serial_h

#define FOSC 12000000L //
#define BAUD 2400

extern unsigned char pc_com[9];

extern void init_serial();
extern void SendData();
extern void SendString(char *s);

#endif
