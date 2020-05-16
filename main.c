//This program runs motors in different directions per second
#include <reg51.h>
sbit r1 = P1^0;
sbit r2 = P1^7;
sbit r3 = P1^2;
sbit r4 = P1^3;
sbit c1 = P1^4;
sbit c2 = P1^5;
sbit c3 = P1^6;
//4x3 keypad connections//

sbit m1p = P3^3;
sbit m1n = P3^4;
sbit m2p = P3^5;
sbit m2n = P3^6;
//Motor input line connections//

sbit rs = P3^0;
sbit rw = P3^1;
sbit en = P3^2;
//LCD Control lines

void lcdcmd(unsigned char);
void lcddat(unsigned char);
void lcddis(unsigned char *, unsigned char);
void check();
void delay();
unsigned char pwd[4], x;

void main()
{
lcdcmd(0x38);  //0x38, to configure the LCD for 2-line, 5×7 font and 8-bit operation mode
lcdcmd(0x01);  //clear screen
lcdcmd(0x10);  //display on, cursor blinking
lcdcmd(0x0c);  //shift cursor position to right (display on & cursor off)
lcdcmd(0x80);	 // to set cursor position at first block of the first line of LCD
lcddis(" PASSWORD PROTECTION", 20);
lcdcmd(0xc0);  //To pass to next line
lcddis("       SYSTEM       ", 20);
delay(); delay(); delay();
lcdcmd(0x01);  //clear screen'
lcddis("ENTER PASSWORD:  ", 19);
lcdcmd(0xc0);
	while(1)
		{
			r1 = 0;
			if(c1 == 0)
			{
				pwd[x] = '1';
				delay(); delay(); delay(); delay(); delay(); delay();  delay(); 
				lcddat('*');
				x = x+1;
			}
			if(c2 == 0)
			{
				pwd[x] = '2';
				delay(); delay(); delay(); delay(); delay(); delay(); delay();
				lcddat('*');
				x = x+1;
			}
			if(c3 == 0)
			{
				pwd[x] = '3';
				delay(); delay(); delay(); delay(); delay(); delay(); delay();
				lcddat('*');
				x = x+1;
			}
			r2 = 0; 
			r1 = 1;
			if(c1 == 0)
			{
				pwd[x] = '4';
				delay(); delay(); delay(); delay(); delay(); delay(); delay();
				lcddat('*');
				x = x+1;
			}
			if(c2 == 0)
			{
				pwd[x] = '5';
				delay(); delay(); delay(); delay(); delay(); delay(); delay();
				lcddat('*');
				x = x+1;
			}
			if(c3 == 0)
			{
				pwd[x] = '6';
				delay(); delay(); delay(); delay(); delay(); delay(); delay();
				lcddat('*');
				x = x+1;
			}
			r3 = 0; 
			r2 = 1;
			if(c1 == 0)
			{
				pwd[x] = '7';
				delay(); delay(); delay(); delay(); delay(); delay(); delay();
				lcddat('*');
				x = x+1;
			}
			if(c2 == 0)
			{
				pwd[x] = '8';
				delay(); delay(); delay(); delay(); delay(); delay(); delay();
				lcddat('*');
				x = x+1;
			}
			if(c3 == 0)
			{
				pwd[x] = '9';
				delay(); delay(); delay(); delay(); delay(); delay(); delay();
				lcddat('*');
				x = x+1;
			}
			r4 = 0; r3 = 1;
			if(c1 == 0)
			{
				pwd[x] = '*';
				delay(); delay(); delay(); delay(); delay(); delay(); delay();
				lcddat('*');
				x = x+1;
			}
			if(c2 == 0)
			{
				pwd[x] = '0';
				delay(); delay(); delay(); delay(); delay(); delay(); delay();
				lcddat('*');
				x = x+1;
			}
			if(c3 == 0)
			{
				check();
				delay();
				delay(); 
				delay(); 
			}
			r4 = 1;
		}
}

void check()
{
	unsigned int i;
	if(pwd[0]=='4'&&pwd[1]=='5'&&pwd[2]=='6'&&pwd[3]=='7')
	{
			
			lcdcmd(0x01);
			lcddis("  ACCESS GRANTED   ", 19);
			lcdcmd(0xc0);  //To pass to next line
			lcddis("   WELCOME HOME!   ", 20);
			i = 50;
			while(i--)
			{
			m1p = 1; m1n = 0;  //Opens doors
			m2p = 1; m2n = 0;  //Opens doors	
			delay();
			}
			i = 60;
			while(i--)
			{
			m1p = 0; m1n = 0;  //Stops for a while
			m2p = 0; m2n = 0;  //Stops for a while
			delay();
			}
			lcdcmd(0x01);
			lcddis("  DOORS CLOSING..   ", 20);
			i = 50;
			while(i--)
			{
			m1p = 0; m1n = 1;  //Closes the door
			m2p = 0; m2n = 1;  //Closes the door
			delay();
			}	
			lcdcmd(0x01);
			i = 40;
			while(i--)
			{
			m1p = 0; m1n = 0;  //Stops 
			m2p = 0; m2n = 0;  
			delay();
			}
	}
	else
	{
		lcdcmd(0x01);
		lcddis("   ACCESS DENIED!   ", 20);
	}
}

void lcdcmd(unsigned char val)
{
	P2 = val;
	rs = 0;
	rw = 0;
	en = 1;
	delay();
	en = 0;
}

void lcddat(unsigned char dat)
{
P2 = dat;
rs = 1 ;
rw = 0;
en = 1;
delay();
en = 0;	
}	

void lcddis(unsigned char *s, unsigned char r)
{
	unsigned char w;
	for(w = 0; w<r; w++)
	{
		lcddat(s[w]);
		delay();
	}
}

void delay()
{	
unsigned int i, j;
for(i = 0; i<8000; i++);
for(j = 0; j<100; j++);

}