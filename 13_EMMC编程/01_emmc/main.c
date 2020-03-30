#include "my_printf.h"
#include "uart.h"
#include "mmc.h"

int main()
{
	unsigned int i;
	
	USDHC_Command command;
	Uart_Init();	
    USDHC_Init();
	
	command.index = 0;
	command.arg = 0;
	command.mix_ctrl = 0;
	command.xfr_typ = 0;
	command.response_type = ResponseTypeNone;
	
	//发送CMD0
	USDHC_SendCommand(&command);

	for( i = 0; i < 10; i++ )
	{
		//发送CMD1
		//设置响应类型 R3
		//答复长度为48bit，RSPTYP[1:0] = 0b10 = 2
		command.index = 1;
		command.arg = 0;
		command.mix_ctrl = 0;
		command.xfr_typ = 2 << 16;
		command.response_type = ResponseTypeR3;
		
		USDHC_SendCommand(&command);
		
		// 等待EMMC复位完成
		// 在OCR中第31为表示EMMC设备是否准备好处理数据，1为准备好，0为忙
		if ( command.response[0] & (1U << 31U) )
		{
			printf("MMC is Ready ok \n\r");
			break;
		}
		else
		{
			printf("MMC is Busy.\n\r");
		}
	}
	return 0;
}

