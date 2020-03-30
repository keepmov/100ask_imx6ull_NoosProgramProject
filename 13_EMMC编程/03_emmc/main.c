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
	
	if( i >= 10 )
	{
		printf("Reset MMC fail.\n\r");
	}
	else
	{
		//发送CMD2
		//设置响应类型 R2
		//答复长度为136bit，RSPTYP[1:0] = 0b01 = 1
		command.index = 2;
		command.arg = 0;
		command.mix_ctrl = 0;
		command.xfr_typ = 1 << 16 | 1 << 19;
		command.response_type = ResponseTypeR2;
		
		USDHC_SendCommand(&command);
		
		printf("ManufacturerID: 0x%x \n\r", (unsigned char)((command.response[3U] & 0xFF000000U) >> 24U));
		printf("CBX: 0x%x \n\r", (unsigned char)((command.response[3U] & 0x00FF0000U) >> 16U));
		printf("ApplicationID: 0x%x \n\r", (unsigned char)((command.response[3U] & 0x0000FF00U) >> 8U));
		printf("Product version: 0x%x \n\r", (unsigned char)((command.response[1U] & 0xFF000000U) >> 24U));
		
		// Send CMD3 设置设备相对地址
		command.index = 3;
		command.arg = 1 << 16;
		command.mix_ctrl = 0;
		command.xfr_typ = 2 << 16 | 0x80000U | 0x100000U;
		command.response_type = ResponseTypeR1;
		
		USDHC_SendCommand(&command);
		
		// COM_CRC_ERROR:(1U << 23U)
		// ILLEGAL_COMMAND:(1U << 22U)
		if (!(command.response[0] & ((1U << 23U) | (1U << 22U))))
		{
			printf("Emmc in Stand-by State\n\r");
		}
		else
		{
			printf("SDMMC_R1 Error\n\r");
			return 0;
		}
		
		// Send CMD9 读取CSD信息
		command.index = 9;
		command.arg = 1 << 16;
		command.mix_ctrl = 0;
		command.xfr_typ = 1 << 16 | 1 << 19;
		command.response_type = ResponseTypeR2;
		
		USDHC_SendCommand(&command);
		
		printf("CSD structure: %x \n\r", (unsigned char)((command.response[3U] & 0xC0000000U) >> 30U));
		
		// Send CMD7 进入tranfaer状态
		command.index = 7;
		command.arg = 1 << 16;
		command.mix_ctrl = 0;
		command.xfr_typ = 2 << 16 | 1 << 19 | 1 << 20;
		command.response_type = ResponseTypeR1;
		
		USDHC_SendCommand(&command);
		
		if (!(command.response[0] & ((1U << 23U) | (1U << 22U))))
		{
			printf("Emmc in Transfer State\n\r");
		}
		else
		{
			printf("SDMMC_R1Error\n\r");
			return 0;
		}
		
		//读EXCSD
		MMC_ReadExCsd();
		
		//设置EMMC的数据总线位宽为8
		MMC_SetBusWidth();
		
		//设置USDHC的数据总线位宽为8
		USDHC_SetBusWidth();
	}
	
	return 0;
}

