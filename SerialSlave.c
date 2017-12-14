#ifndef F_CPU
#define F_CPU 16000000UL
#endif
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/myInputOutput.h>
 
#define ACK 0x7E
 
void spi_init_slave (void)
{
    DDRB=(1<<4);                                  //MISO as OUTPUT
    SPCR = (1<<SPE);                                //Enable SPI
}
 
//Function to send and receive data
unsigned char spi_tranceiver (unsigned char data)
{
    SPDR = data;                                  //Load data into buffer
    while(!(SPSR & (1<<SPIF) ));                  //Wait until transmission complete
    return(SPDR);                                 //Return received data
}
 
int main(void)
{
    spi_init_slave();                             //Initialize slave SPI
    unsigned char data, buffer[10];
    //DDRA  = 0x00;                                 //Initialize PORTA as INPUT
    //PORTA = 0xFF;
	pinMode('C',5,1);                                 //Enable Pull-Up Resistors
    while(1)
    {
		/*digitalWrite('C',5,0);
		_delay_ms(100);
		digitalWrite('C',5,1);
		_delay_ms(100);*/
        data = spi_tranceiver(ACK);
		/*digitalWrite('C',5,1);
		_delay_ms(500);
		digitalWrite('C',5,0);*/
		if(data == 3) {
			digitalWrite('C',5,1);
			_delay_ms(500);
			digitalWrite('C',5,0);
		}
		//_delay_ms(100);

		//itoa(data, buffer, 10);               //Receive data, send ACK
                                  //Wait
    }
}
