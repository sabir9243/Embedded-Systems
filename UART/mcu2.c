#include<reg51.h>

sbit RS = P0^0;		//command/data config pin
sbit RW = P0^1;		//read/write config pin
sbit E = P0^2;		//clk for display

sbit d0=P0^4;		//data/command pins 
sbit d1=P0^5;
sbit d2=P0^6;
sbit d3=P0^7;

char r_data[20],*r_ptr=r_data;  //the r_ptr points a memory location where we are going to store our received r_data

// a union is defined, two members, one is char, another is a structure
//the structure inside of union is defined to use individual bits using bitfields to send data to LCD display
union 
{
   char charMem;
   struct
   {
		  int b  : 8;//this field is empty because character is of 8bit but union is 16bit
      int b0 : 1; //bitwidth(lsb)
			int b1 : 1;
      int b2 : 1;
      int b3 : 1;
      int b4 : 1;
      int b5 : 1;
      int b6 : 1;
      int b7 : 1;//(msb)
   }Bit;
}charUnion;

void init_uart(){
	TMOD = 0x20;
	TH1 = 0xFC;
	SCON = 0x50;                //select one of 4 modes(mode-1) of UART
	TR1 = 1;
}


void serial() interrupt 4     //this is a serial interrupt subroutine 
{
	if(RI==1){
		*r_ptr=SBUF;
		r_ptr++;
		RI=0;
			
	}
	else if(TI==1){
		TI=0;
	}
}


void write_disp(char c,int cD){
	//this function writes either command or data to display
	//for command use cD=0
	//for data use cD=1
	
	if(cD==0)
		RS=0;
	else
		RS=1;
	charUnion.charMem=c;
	RW=0;                  
	E=1;
	d3=charUnion.Bit.b7;				//accessing the MSB of ascii character received using unions of structure of bitfields
	d2=charUnion.Bit.b6;
	d1=charUnion.Bit.b5;
	d0=charUnion.Bit.b4;
	E=0;
	
	E=1;
	d3=charUnion.Bit.b3;
  d2=charUnion.Bit.b2;
	d1=charUnion.Bit.b1;
	d0=charUnion.Bit.b0;
	E=0;
	
}

void write_string(char *ch){	//this function writes a character of display
	while((*ch)!='\0')
		write_disp(*(ch++),1);
}

void e_interrupt0() interrupt 0
{
  EX0=0;
	write_string(&r_data);              //this is active low hardware interrupt 0 subroutine which calls a function to display received data on LCD display	
}


void init_display(){									//function for initializing the display
	write_disp(0x02,0);									//set 4 bit mod
	write_disp(0x01,0); 								//clear display
	write_disp(0x0F,0);									//turn on display
	
}


void main()
{  
	init_display();			//initialize display
	init_uart();				//initialize UART
	EA=1;               //this enables all the interrupts
	ES=1;								//this enables serial interrupts 
	EX0=1;			        //this enables external active low hardware interruts
	while(1);						//this loop continues until the external interrupt pin becomes low
	
}
		
	