#ifndef _MMC_H_
#define _MMC_H_

#define USDHC_READ_WATERMARK_LEVEL (0x80U)
#define USDHC_WRITE_WATERMARK_LEVEL (0x80U)

#define USDHC_READ_BURST_LEN (8U)   
#define USDHC_WRITE_BURST_LEN (8U)  
#define USDHC_DATA_TIMEOUT (0xFU)   


typedef struct {
  volatile unsigned int DS_ADDR;                           /**< DMA System Address, offset: 0x0 */
  volatile unsigned int BLK_ATT;                           /**< Block Attributes, offset: 0x4 */
  volatile unsigned int CMD_ARG;                           /**< Command Argument, offset: 0x8 */
  volatile unsigned int CMD_XFR_TYP;                       /**< Command Transfer Type, offset: 0xC */
  volatile unsigned int CMD_RSP0;                          /**< Command Response0, offset: 0x10 */
  volatile unsigned int CMD_RSP1;                          /**< Command Response1, offset: 0x14 */
  volatile unsigned int CMD_RSP2;                          /**< Command Response2, offset: 0x18 */
  volatile unsigned int CMD_RSP3;                          /**< Command Response3, offset: 0x1C */
  volatile unsigned int DATA_BUFF_ACC_PORT;                /**< Data Buffer Access Port, offset: 0x20 */
  volatile unsigned int PRES_STATE;                        /**< Present State, offset: 0x24 */
  volatile unsigned int PROT_CTRL;                         /**< Protocol Control, offset: 0x28 */
  volatile unsigned int SYS_CTRL;                          /**< System Control, offset: 0x2C */
  volatile unsigned int INT_STATUS;                        /**< Interrupt Status, offset: 0x30 */
  volatile unsigned int INT_STATUS_EN;                     /**< Interrupt Status Enable, offset: 0x34 */
  volatile unsigned int INT_SIGNAL_EN;                     /**< Interrupt Signal Enable, offset: 0x38 */
  volatile unsigned int AUTOCMD12_ERR_STATUS;              /**< Auto CMD12 Error Status, offset: 0x3C */
  volatile unsigned int HOST_CTRL_CAP;                     /**< Host Controller Capabilities, offset: 0x40 */
  volatile unsigned int WTMK_LVL;                          /**< Watermark Level, offset: 0x44 */
  volatile unsigned int MIX_CTRL;                          /**< Mixer Control, offset: 0x48 */
          unsigned char RESERVED_0[4];
  volatile unsigned int FORCE_EVENT;                       /**< Force Event, offset: 0x50 */
  volatile unsigned int ADMA_ERR_STATUS;                   /**< ADMA Error Status Register, offset: 0x54 */
  volatile unsigned int ADMA_SYS_ADDR;                     /**< ADMA System Address, offset: 0x58 */
          unsigned char RESERVED_1[4];
  volatile unsigned int DLL_CTRL;                          /**< DLL (Delay Line) Control, offset: 0x60 */
  volatile unsigned int DLL_STATUS;                        /**< DLL Status, offset: 0x64 */
  volatile unsigned int CLK_TUNE_CTRL_STATUS;              /**< CLK Tuning Control and Status, offset: 0x68 */
          unsigned char RESERVED_2[84];
  volatile unsigned int VEND_SPEC;                         /**< Vendor Specific Register, offset: 0xC0 */
  volatile unsigned int MMC_BOOT;                          /**< MMC Boot Register, offset: 0xC4 */
  volatile unsigned int VEND_SPEC2;                        /**< Vendor Specific 2 Register, offset: 0xC8 */
  volatile unsigned int TUNING_CTRL;                       /**< Tuning Control Register, offset: 0xCC */
} USDHC_Type;

typedef enum 
{
	ResponseTypeNone = 0U,
	ResponseTypeR1   = 1U,
	ResponseTypeR1b  = 2U,
	ResponseTypeR2   = 3U,
	ResponseTypeR3   = 4U,
	ResponseTypeR4	 = 5U,
	ResponseTypeR5   = 6U,
	ResponseTypeR5b  = 7U,
	ResponseTypeR6   = 8U,
	ResponseTypeR7   = 9U
}USDHC_Respones_Type;

typedef struct
{
	unsigned int  index;
	unsigned int  arg;
	unsigned int  response[4];
	USDHC_Respones_Type response_type;
	unsigned int  mix_ctrl;
	unsigned int  xfr_typ;
}USDHC_Command;

void USDHC_Init(void);
void USDHC_SendCommand(USDHC_Command *command);
void USDHC_ReadResponse(USDHC_Command *command);
#endif