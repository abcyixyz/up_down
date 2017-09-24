#include <REGX52.h>
#include "serial.h"

bit busy;
bit pc_com_success;
unsigned char pc_com[9];
//零位a开始、一位0读取or1移动目标or2停止移动、二0管子or1前级、三0同时or1分别、四数字千、五数字百、六数字十、七数字个、八结束b

/*-------------------------串口中断初始化---------------------------*/
void init_serial()
{
    SCON = 0x50;                                          //8-bit variable UART
    TMOD |= 0x20;                        //Set Timer1 as 8-bit auto reload mode
    TH1 = TL1 = -(FOSC/12/32/BAUD);                     //Set auto-reload vaule
    TR1 = 1;                                                 //Timer1 start run
    ES = 1;                                             //Enable UART interrupt
    EA = 1;                                      //Open master interrupt switch
}

/*----------------------------
Send a byte data to UART
Input: dat (data to be sent)
Output:None
----------------------------*/
void SendData(unsigned char dat)
{
    while (busy)
	{
		/*---------------------*/
	}                       //Wait for the completion of the previous data is sent
    ACC = dat;                        //Calculate the even parity bit P (PSW.0)
    busy = 1;
    SBUF = ACC;                                      //Send data to UART buffer
}

/*----------------------------
Send a string to UART
Input: s (address of string)
Output:None
----------------------------*/
void SendString(char *s)
{
    while (*s)                                    //Check the end of the string
    {
        SendData(*s++);            //Send current char and increment string ptr
    }
}

/*---------------------------------串口中断-----------------------------------*/
void Uart_Isr() interrupt 4 //using 1
{
    if (RI)
    {
      static unsigned char count;                            //串口接收计数的变量
  		RI=0;                                                   //手动清零RI寄存器
  		pc_com[count]=SBUF;
  		if(count==0 && pc_com[count]=='a')        //同时判断count跟收到的起始字符‘a’
  		{
       		count++;
  		}
 		 else if(count>=1 && count<8)
  		{
          count++;
  		}
  		else if(count==8&&pc_com[count]=='b')      //判断校验和，数据多的话是求//和，或者其他的校验方法，也可能是固定的帧尾
  		{
    		count=0;
     		pc_com_success = 1;         //串口接收成功标志，为1时在主程序中回复，然后清零
  		}
  		else
  		{
     		count=0;                                    //判断不满足条件就将计数值清零
 		  }
    }
    if (TI)
    {
        TI = 0;                                 //Clear transmit interrupt flag
        busy = 0;                                    //Clear transmit busy flag
    }
}
