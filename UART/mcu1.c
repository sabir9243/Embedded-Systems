#include<reg51.h>

void init_uart(){
	TMOD = 0x20;
	TH1 = 0xFC;
	SCON = 0x50;                //select one of 4 modes(mode-1) of UART
	TR1 = 1;
}

void delay(unsigned char msecond){
	TMOD=0x01;
	while(msecond!=0)
	{
	TH1=0xfc;
	TL1=0x6b;
	TR1=1;
	while(TF1==0);
	TR1=0;
	TF1=0;
	msecond-=1;
	}
}

void transmit_byte(char c){
	SBUF = c;
	while(TI==0);
	TI=0;
}


void transmit_string(char st[]){
	char *ch =st;
	while(*ch!='\0'){
		transmit_byte(*(ch++));
	}
}

void main(){
	
	char name[]="Sabir";
	delay(2);
	init_uart();
	transmit_string(name);
	while(1);
  
	//transmit_string(d);
	
}