#ifndef _chipeeprom_h_
#define _chipeeprom_h_
/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/

/* �Զ���� */
extern void WriteMultiBlockByte(u8 BlockStartAddress,FLASH_MemType_TypeDef FLASH_MemType, 
                FLASH_ProgramMode_TypeDef FLASH_ProgMode, uint8_t *Buffer,uint8_t BlockNum);
extern void ReadMultiBlockByte(u8 BlockStartAddress,uint8_t BlockNum,
                        uint8_t ReadBlockByte[]);
#endif
/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/