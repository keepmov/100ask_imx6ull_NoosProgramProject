#include "mmc.h"
#include "my_printf.h"

#define USDHC2_BASE                              (0x2194000u)

static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_NAND_RE_B;
static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_NAND_WE_B;
static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_NAND_DATA0;
static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_NAND_DATA1;
static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_NAND_DATA2;
static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_NAND_DATA3;
static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_NAND_DATA4;
static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_NAND_DATA5;
static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_NAND_DATA6;
static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_NAND_DATA7;
static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_NAND_ALE;

static volatile unsigned int *IOMUXC_USDHC2_CLK_SELECT_INPUT;
static volatile unsigned int *IOMUXC_USDHC2_CMD_SELECT_INPUT;
static volatile unsigned int *IOMUXC_USDHC2_DATA0_SELECT_INPUT;
static volatile unsigned int *IOMUXC_USDHC2_DATA1_SELECT_INPUT;
static volatile unsigned int *IOMUXC_USDHC2_DATA2_SELECT_INPUT;
static volatile unsigned int *IOMUXC_USDHC2_DATA3_SELECT_INPUT;
static volatile unsigned int *IOMUXC_USDHC2_DATA4_SELECT_INPUT;
static volatile unsigned int *IOMUXC_USDHC2_DATA5_SELECT_INPUT;
static volatile unsigned int *IOMUXC_USDHC2_DATA6_SELECT_INPUT;
static volatile unsigned int *IOMUXC_USDHC2_DATA7_SELECT_INPUT;

static volatile unsigned int *IOMUXC_SW_PAD_CTL_PAD_NAND_RE_B;   
static volatile unsigned int *IOMUXC_SW_PAD_CTL_PAD_NAND_WE_B;  
static volatile unsigned int *IOMUXC_SW_PAD_CTL_PAD_NAND_DATA00; 
static volatile unsigned int *IOMUXC_SW_PAD_CTL_PAD_NAND_DATA01;
static volatile unsigned int *IOMUXC_SW_PAD_CTL_PAD_NAND_DATA02;
static volatile unsigned int *IOMUXC_SW_PAD_CTL_PAD_NAND_DATA03;
static volatile unsigned int *IOMUXC_SW_PAD_CTL_PAD_NAND_DATA04;
static volatile unsigned int *IOMUXC_SW_PAD_CTL_PAD_NAND_DATA05;
static volatile unsigned int *IOMUXC_SW_PAD_CTL_PAD_NAND_DATA06;
static volatile unsigned int *IOMUXC_SW_PAD_CTL_PAD_NAND_DATA07;

static volatile unsigned int *CCM_CCGR6;


USDHC_Type *usdhc2_reg = ((USDHC_Type *)USDHC2_BASE);


static unsigned char USDHC_Reset(unsigned int mask, unsigned int timeout);


/**********************************************************************
 * 函数名称： Emmc_PinConfig
 * 功能描述： 配置引脚
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2020/02/28	     V1.0	  LJZ	           创建
 ***********************************************************************/
static void Emmc_PinConfig(void)
{
	// 配置引脚复用功能
	IOMUXC_SW_MUX_CTL_PAD_NAND_RE_B  = (volatile unsigned int *)(0x20E0178);		
	IOMUXC_SW_MUX_CTL_PAD_NAND_WE_B  = (volatile unsigned int *)(0x20E017C);		
	IOMUXC_SW_MUX_CTL_PAD_NAND_DATA0 = (volatile unsigned int *)(0x20E0180);
	IOMUXC_SW_MUX_CTL_PAD_NAND_DATA1 = (volatile unsigned int *)(0x20E0184);
	IOMUXC_SW_MUX_CTL_PAD_NAND_DATA2 = (volatile unsigned int *)(0x20E0188);
	IOMUXC_SW_MUX_CTL_PAD_NAND_DATA3 = (volatile unsigned int *)(0x20E018C);
	IOMUXC_SW_MUX_CTL_PAD_NAND_DATA4 = (volatile unsigned int *)(0x20E0190);
	IOMUXC_SW_MUX_CTL_PAD_NAND_DATA5 = (volatile unsigned int *)(0x20E0194);
	IOMUXC_SW_MUX_CTL_PAD_NAND_DATA6 = (volatile unsigned int *)(0x20E0198);
	IOMUXC_SW_MUX_CTL_PAD_NAND_DATA7 = (volatile unsigned int *)(0x20E019C);
	IOMUXC_SW_MUX_CTL_PAD_NAND_ALE   = (volatile unsigned int *)(0x20E01A0);		
	
	*IOMUXC_SW_MUX_CTL_PAD_NAND_RE_B  = 0x1U;
	*IOMUXC_SW_MUX_CTL_PAD_NAND_WE_B  = 0x1U;
	*IOMUXC_SW_MUX_CTL_PAD_NAND_DATA0 = 0x1U;
	*IOMUXC_SW_MUX_CTL_PAD_NAND_DATA1 = 0x1U;
	*IOMUXC_SW_MUX_CTL_PAD_NAND_DATA2 = 0x1U;
	*IOMUXC_SW_MUX_CTL_PAD_NAND_DATA3 = 0x1U;
	*IOMUXC_SW_MUX_CTL_PAD_NAND_DATA4 = 0x1U;
	*IOMUXC_SW_MUX_CTL_PAD_NAND_DATA5 = 0x1U;
	*IOMUXC_SW_MUX_CTL_PAD_NAND_DATA6 = 0x1U;
	*IOMUXC_SW_MUX_CTL_PAD_NAND_DATA7 = 0x1U;
	*IOMUXC_SW_MUX_CTL_PAD_NAND_ALE   = 0x5U;
	
	// 配置引脚的输入源
	IOMUXC_USDHC2_CLK_SELECT_INPUT    = (volatile unsigned int *)(0x020E0670);
	IOMUXC_USDHC2_CMD_SELECT_INPUT    = (volatile unsigned int *)(0x020E0678);
	IOMUXC_USDHC2_DATA0_SELECT_INPUT  = (volatile unsigned int *)(0x020E067C);
	IOMUXC_USDHC2_DATA1_SELECT_INPUT  = (volatile unsigned int *)(0x020E0680);
	IOMUXC_USDHC2_DATA2_SELECT_INPUT  = (volatile unsigned int *)(0x020E0684);
	IOMUXC_USDHC2_DATA3_SELECT_INPUT  = (volatile unsigned int *)(0x020E0688);
	IOMUXC_USDHC2_DATA4_SELECT_INPUT  = (volatile unsigned int *)(0x020E068C);
	IOMUXC_USDHC2_DATA5_SELECT_INPUT  = (volatile unsigned int *)(0x020E0690);
	IOMUXC_USDHC2_DATA6_SELECT_INPUT  = (volatile unsigned int *)(0x020E0694);
	IOMUXC_USDHC2_DATA7_SELECT_INPUT  = (volatile unsigned int *)(0x020E0698);
	
	*IOMUXC_USDHC2_CLK_SELECT_INPUT    = 0x2U;
	*IOMUXC_USDHC2_CMD_SELECT_INPUT    = 0x2U;
	*IOMUXC_USDHC2_DATA0_SELECT_INPUT  = 0x2U;
	*IOMUXC_USDHC2_DATA1_SELECT_INPUT  = 0x2U;
	*IOMUXC_USDHC2_DATA2_SELECT_INPUT  = 0x1U;
	*IOMUXC_USDHC2_DATA3_SELECT_INPUT  = 0x2U;
	*IOMUXC_USDHC2_DATA4_SELECT_INPUT  = 0x1U;
	*IOMUXC_USDHC2_DATA5_SELECT_INPUT  = 0x1U;
	*IOMUXC_USDHC2_DATA6_SELECT_INPUT  = 0x1U;
	*IOMUXC_USDHC2_DATA7_SELECT_INPUT  = 0x1U;
		
	// 配置引脚的输入输出参数
	IOMUXC_SW_PAD_CTL_PAD_NAND_RE_B   = (volatile unsigned int *)(0x020E0404U);
	IOMUXC_SW_PAD_CTL_PAD_NAND_WE_B   = (volatile unsigned int *)(0x020E0408U);
	IOMUXC_SW_PAD_CTL_PAD_NAND_DATA00 = (volatile unsigned int *)(0x020E040CU);
	IOMUXC_SW_PAD_CTL_PAD_NAND_DATA01 = (volatile unsigned int *)(0x020E0410U);
	IOMUXC_SW_PAD_CTL_PAD_NAND_DATA02 = (volatile unsigned int *)(0x020E0414U);
	IOMUXC_SW_PAD_CTL_PAD_NAND_DATA03 = (volatile unsigned int *)(0x020E0418U);
	IOMUXC_SW_PAD_CTL_PAD_NAND_DATA04 = (volatile unsigned int *)(0x020E041CU);
	IOMUXC_SW_PAD_CTL_PAD_NAND_DATA05 = (volatile unsigned int *)(0x020E0420U);
	IOMUXC_SW_PAD_CTL_PAD_NAND_DATA06 = (volatile unsigned int *)(0x020E0424U);
	IOMUXC_SW_PAD_CTL_PAD_NAND_DATA07 = (volatile unsigned int *)(0x020E0428U);
	
	*IOMUXC_SW_PAD_CTL_PAD_NAND_RE_B   = 0x17059; 
	*IOMUXC_SW_PAD_CTL_PAD_NAND_WE_B   = 0x17059; 
	*IOMUXC_SW_PAD_CTL_PAD_NAND_DATA00 = 0x17059; 
	*IOMUXC_SW_PAD_CTL_PAD_NAND_DATA01 = 0x17059; 
	*IOMUXC_SW_PAD_CTL_PAD_NAND_DATA02 = 0x17059; 
	*IOMUXC_SW_PAD_CTL_PAD_NAND_DATA03 = 0x17059; 
	*IOMUXC_SW_PAD_CTL_PAD_NAND_DATA04 = 0x17059; 
	*IOMUXC_SW_PAD_CTL_PAD_NAND_DATA05 = 0x17059; 
	*IOMUXC_SW_PAD_CTL_PAD_NAND_DATA06 = 0x17059; 
	*IOMUXC_SW_PAD_CTL_PAD_NAND_DATA07 = 0x17059; 	
	
}

/**********************************************************************
 * 函数名称： USDHC_Init
 * 功能描述： usdhc初始化
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2020/02/28	     V1.0	  LJZ	           创建
 ***********************************************************************/
void USDHC_Init(void)
{
	CCM_CCGR6            = (volatile unsigned int *)(0x20C4080);
	
	Emmc_PinConfig();
	
	/* 使能USDHC时钟 */
	*CCM_CCGR6 = ((*CCM_CCGR6) & ~(3U << 0x04)) | (((unsigned int)3U) << 0x04);
	
	/* 复位 USDHC   */
	if( USDHC_Reset(0x1000000U, 100U) == 1 )
	{
		/* 复位成功 */
		printf("Reset Success\n\r");
	}
	else
	{
		/* 复位失败 */
		printf("Reset false\n\r");
		return;
	}
	
	/* 设置为小端模式，关闭DMA */
	usdhc2_reg->PROT_CTRL &= ~(0x30U | 0x300U);
   
    usdhc2_reg->PROT_CTRL |= 2U << 4U;

    /* 设置读写缓存的水位线 */
    usdhc2_reg->WTMK_LVL &= ~(0xFFU | 0xFF0000U | 0x1F00U | 0x1F000000U);
    usdhc2_reg->WTMK_LVL |= 128 | 128 << 16U | 8 << 8 | 8U << 24U;
	
    /* 配置数据超时时间 */
    usdhc2_reg->SYS_CTRL &= ~0xF0000U;
    usdhc2_reg->SYS_CTRL |= USDHC_DATA_TIMEOUT << 16;   
	
	
	usdhc2_reg->MIX_CTRL &= ~(0x01U);
    /* 使能中断状态 */
	//CCSEN : 0x01
	//TCSEN : 0x02
	//BRRSEN : 0x20
	usdhc2_reg->INT_STATUS_EN |= (0x01 | 0x02 |0x20);
	
	
	
	/* 设置数据总线位宽，默认设为1位 */
	usdhc2_reg->PROT_CTRL |= 0U << 1;
	
    /* 设置时钟为400KHz. */
    //Single Data Rate mode,默认使用PLL2_PFD2 = 396Mhz, usdhc2_clk_root = 396Mhz / 2 =  198Mhz
    //usdhc2_clk = 	usdhc2_clk_root / (prescaler * divisor)
	//SDCLKFS = 0x40 = 128分频
	//DVS = 0x03 = 4分频
	//usdhc2_clk = 198Mhz/(128*4) = 0.387Mhz
	usdhc2_reg->SYS_CTRL &= ~((0xFF00) | (0xF0));
	usdhc2_reg->SYS_CTRL |= (0x0040U << 8) | (0x0003U << 4);
	
	/* 等待时钟稳定 */
	while (!(usdhc2_reg->PRES_STATE & 0x8U))
    {
		
    }
	
}

/**********************************************************************
 * 函数名称： USDHC_Reset
 * 功能描述： usdhc复位
 * 输入参数： unsigned int mask    ：
 *            unsigned int timeout ：超时时间
 * 输出参数： unsigned char
 * 返 回 值： 0为复位成功，1为复位失败。
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2020/02/28	     V1.0	  LJZ	           创建
 ***********************************************************************/
static unsigned char USDHC_Reset(unsigned int mask, unsigned int timeout)
{
    usdhc2_reg->SYS_CTRL |= mask;
	
    while ((usdhc2_reg->SYS_CTRL & mask) != 0U)
    {
        if (timeout == 0U)
        {
            break;
        }
        timeout--;
    }

    return ((!timeout) ? 0 : 1);
}

/**********************************************************************
 * 函数名称： USDHC_SendCommand
 * 功能描述： 向EMMC发送命令
 * 输入参数： USDHC_Command* command ：USDHC命令结构体
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2020/02/28	     V1.0	  LJZ	           创建
 ***********************************************************************/
void USDHC_SendCommand(USDHC_Command *command)
{
	/* 等待命令发送完成 */
	// CIHB掩码：0x01
	while( usdhc2_reg->PRES_STATE & 0x01U )
	{
	}
	
	/* 等待数据完成 */
	// CDIHB掩码：0x02
	while( usdhc2_reg->PRES_STATE & 0x02U )
	{
	}
	
	printf("Send CMD%d \n\r", command->index);
	
	/* 配置传输方式 */
	// BCEN掩码: 0x02U
	// DDR_EN掩码：0x08U
	// DTDSEL掩码：0x10U
	// MSBSEL掩码：0x20U
	usdhc2_reg->MIX_CTRL &= ~(0x20U | 0x2U | 0x10U | 0x8U );
    usdhc2_reg->MIX_CTRL |= ((command->mix_ctrl) & (0x20U | 0x2U | 0x10U | 0x8U ));	
	
    usdhc2_reg->CMD_ARG = command->arg;
	
	/* 配置命令参数 */
	// CDMINX掩码：0x3F000000U
	// DPSEL掩码：0x200000U
	// CICEN掩码：0x100000U
	// CCCEN掩码：0x80000U
	// PSPTYP[1:0]掩码：0x30000U
	usdhc2_reg->CMD_XFR_TYP &= ~(0x3F000000U | 0x200000U | 0x100000U | 0x80000U | 0x30000U);

    usdhc2_reg->CMD_XFR_TYP = (((command->index << 24U) & 0x3F000000U) | 
	                           ((command->xfr_typ) &(0x3F000000U | 0x200000U | 0x100000U | 0x80000U | 0x30000U)));
    /* 等待命令发送 */
	// CC位掩码：0x01
	while( !(usdhc2_reg->INT_STATUS & 0x1U ) )
	{
	}
	
	/* 清中断标记位 */
	// CC位掩码：0x01
	usdhc2_reg->INT_STATUS &= 0x01U ;
	
	USDHC_ReadResponse(command);
}

/**********************************************************************
 * 函数名称： USDHC_ReadResponse
 * 功能描述： 读取Response
 * 输入参数： USDHC_Command* command ：USDHC命令结构体
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2020/02/28	     V1.0	  LJZ	           创建
 ***********************************************************************/
void USDHC_ReadResponse(USDHC_Command *command)
{
	unsigned int i;
	
	if( command->response_type != ResponseTypeNone )
	{
		command->response[0] = usdhc2_reg->CMD_RSP0;
		
		if( command->response_type == ResponseTypeR2 )
		{
			command->response[1] = usdhc2_reg->CMD_RSP1;
			command->response[2] = usdhc2_reg->CMD_RSP2;
			command->response[3] = usdhc2_reg->CMD_RSP3;

			i = 4;
		
			do
			{
				command->response[i - 1] <<= 8;
				if (i > 1)
				{
					command->response[i - 1] |= ((command->response[i - 2] & 0xFF000000U) >> 24U);
				}
			} while (i--);
		}
	}
}