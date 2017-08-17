#ifndef _tf_h_
#define _tf_h_
/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
//����TF���ӿ�
#define TF_CS_PORT              GPIOE
#define TF_CS_PIN               GPIO_PIN_5

#define Set_TF_CS  GPIO_WriteHigh(TF_CS_PORT,TF_CS_PIN)		/* ��ֹSD�� */
#define Clr_TF_CS  GPIO_WriteLow(TF_CS_PORT,TF_CS_PIN)		/* ʹ��SD�� */ 

/* �Զ��������� */
typedef enum
{
	TF_OK      = (u8)0x00,
	TF_ERROR   = (u8)0x01
} TF_Status_TypeDef;		/* SD�������ɹ�ʧ�ܷ���ֵ */

typedef struct
{
	u8  ManufacturerID;       // ������ʶID
	u16 OEM_AppliID;          // OEM/Ӧ�� ID
	u32 ProdName1;            // ��Ʒ����1
	u8  ProdName2;            // ��Ʒ����2
	u8  ProdRev;              // ��Ʒ�汾
	u32 ProdSN;               // ��Ʒ���
	u8  Reserved1;            // ����
	u16 ManufactDate;         // ��������
	u8  CID_CRC;              // CID CRC
	u8  Reserved2;            // always 1
} TF_CID;	/* CID�Ĵ��� */

/* �Զ���� */
//SD�������ݽ������Ƿ��ͷ����ߺ궨��  
#define NO_RELEASE      0
#define RELEASE         1	

/* 
 * SD��ָ��� 
 */
#define CMD0    0       //����λ
#define CMD1    1
#define CMD9    9       //����9 ����CSD����
#define CMD10   10      //����10����CID����
#define CMD12   12      //����12��ֹͣ���ݴ���
#define CMD16   16      //����16������SectorSize Ӧ����0x00
#define CMD17   17      //����17����sector
#define CMD18   18      //����18����Multi sector
#define ACMD23  23      //����23�����ö�sectorд��ǰԤ�Ȳ���N��block
#define CMD24   24      //����24��дsector
#define CMD25   25      //����25��дMulti sector
#define ACMD41  41      //����41��Ӧ����0x00
#define CMD55   55      //����55��Ӧ����0x01
#define CMD58   58      //����58����OCR��Ϣ
#define CMD59   59      //����59��ʹ��/��ֹCRC��Ӧ����0x00
//����д���Ӧ������
#define MSD_DATA_OK                0x05
#define MSD_DATA_CRC_ERROR         0x0B
#define MSD_DATA_WRITE_ERROR       0x0D
#define MSD_DATA_OTHER_ERROR       0xFF
//SD����Ӧ�����
#define MSD_RESPONSE_NO_ERROR      0x00
#define MSD_IN_IDLE_STATE          0x01
#define MSD_ERASE_RESET            0x02
#define MSD_ILLEGAL_COMMAND        0x04
#define MSD_COM_CRC_ERROR          0x08
#define MSD_ERASE_SEQUENCE_ERROR   0x10
#define MSD_ADDRESS_ERROR          0x20
#define MSD_PARAMETER_ERROR        0x40
#define MSD_RESPONSE_FAILURE       0xFF




extern void TF_Init(void);
extern unsigned char TF_Idle_Sta(void);
extern unsigned char TF_WaitDataReady(void);
extern unsigned char TF_SendCommand(unsigned char cmd, unsigned int arg, unsigned char crc);
extern unsigned char TF_SendCommand_NoDeassert(unsigned char cmd, unsigned int arg, unsigned char crc);
extern unsigned char TF_ReceiveData(unsigned char *data, unsigned short len, unsigned char release);
extern unsigned char TF_GetCID(TF_CID *cid);
extern unsigned char TF_GetCSD(unsigned char * csd);
extern unsigned int  TF_GetCapacity(void);
extern unsigned char TF_ReadSingleBlock(unsigned int sector, unsigned char *buffer);
extern unsigned char TF_ReadMultiBlock(unsigned int sector, unsigned char *buffer, unsigned char count);
extern unsigned char TF_Read_Bytes(unsigned long address,unsigned char *buf,unsigned int offset,unsigned int bytes);
extern unsigned char TF_WriteSingleBlock(unsigned int sector, unsigned char * buffer);
extern unsigned char TF_WriteMultiBlock(unsigned int sector, const unsigned char *data, unsigned char count);
#endif
/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/