#ifndef _rc522_h_
#define _rc522_h_
/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
//������󳤶�
#define MAX_LEN 16
#define  SPI_DUMMY_BYTE                  (0xFF)                                 // ��������
//NRSTPD���Ŷ��壬Not Reset and Power-down
//sbit NRSTPD = P1^4; 
#define RFID_CS_PORT (GPIOE)
#define RFID_CS_PIN  (GPIO_PIN_5)

#define RFID_RST_PORT (GPIOC)
#define RFID_RST_PIN  (GPIO_PIN_2)



//4�ֽڿ����кţ���5�ֽ�ΪУ���ֽ�
extern unsigned char  serNum[5];

//MF522������
#define PCD_IDLE              0x00               //NO action;ȡ����ǰ����
#define PCD_AUTHENT           0x0E               //��֤��Կ
#define PCD_RECEIVE           0x08               //��������
#define PCD_TRANSMIT          0x04               //��������
#define PCD_TRANSCEIVE        0x0C               //���Ͳ���������
#define PCD_RESETPHASE        0x0F               //��λ
#define PCD_CALCCRC           0x03               //CRC����

//Mifare_One��Ƭ������
#define PICC_REQIDL           0x26               //Ѱ��������δ��������״̬
#define PICC_REQALL           0x52               //Ѱ��������ȫ����
#define PICC_ANTICOLL         0x93               //����ײ
#define PICC_SElECTTAG        0x93               //ѡ��
#define PICC_AUTHENT1A        0x60               //��֤A��Կ
#define PICC_AUTHENT1B        0x61               //��֤B��Կ
#define PICC_READ             0x30               //����
#define PICC_WRITE            0xA0               //д��
#define PICC_DECREMENT        0xC0               //�ۿ�
#define PICC_INCREMENT        0xC1               //��ֵ
#define PICC_RESTORE          0xC2               //�������ݵ�������
#define PICC_TRANSFER         0xB0               //���滺����������
#define PICC_HALT             0x50               //����


//��MF522ͨѶʱ���صĴ������
#define MI_OK                 0
#define MI_NOTAGERR           1
#define MI_ERR                2


//------------------MFRC522�Ĵ���---------------
//Page 0:Command and Status
#define     Reserved00            0x00    
#define     CommandReg            0x01    
#define     CommIEnReg            0x02    
#define     DivlEnReg             0x03    
#define     CommIrqReg            0x04    
#define     DivIrqReg             0x05
#define     ErrorReg              0x06    
#define     Status1Reg            0x07    
#define     Status2Reg            0x08    
#define     FIFODataReg           0x09
#define     FIFOLevelReg          0x0A
#define     WaterLevelReg         0x0B
#define     ControlReg            0x0C
#define     BitFramingReg         0x0D
#define     CollReg               0x0E
#define     Reserved01            0x0F
//Page 1:Command     
#define     Reserved10            0x10
#define     ModeReg               0x11
#define     TxModeReg             0x12
#define     RxModeReg             0x13
#define     TxControlReg          0x14
#define     TxAutoReg             0x15
#define     TxSelReg              0x16
#define     RxSelReg              0x17
#define     RxThresholdReg        0x18
#define     DemodReg              0x19
#define     Reserved11            0x1A
#define     Reserved12            0x1B
#define     MifareReg             0x1C
#define     Reserved13            0x1D
#define     Reserved14            0x1E
#define     SerialSpeedReg        0x1F
//Page 2:CFG    
#define     Reserved20            0x20  
#define     CRCResultRegM         0x21
#define     CRCResultRegL         0x22
#define     Reserved21            0x23
#define     ModWidthReg           0x24
#define     Reserved22            0x25
#define     RFCfgReg              0x26
#define     GsNReg                0x27
#define     CWGsPReg	          0x28
#define     ModGsPReg             0x29
#define     TModeReg              0x2A
#define     TPrescalerReg         0x2B
#define     TReloadRegH           0x2C
#define     TReloadRegL           0x2D
#define     TCounterValueRegH     0x2E
#define     TCounterValueRegL     0x2F
//Page 3:TestRegister     
#define     Reserved30            0x30
#define     TestSel1Reg           0x31
#define     TestSel2Reg           0x32
#define     TestPinEnReg          0x33
#define     TestPinValueReg       0x34
#define     TestBusReg            0x35
#define     AutoTestReg           0x36
#define     VersionReg            0x37
#define     AnalogTestReg         0x38
#define     TestDAC1Reg           0x39  
#define     TestDAC2Reg           0x3A   
#define     TestADCReg            0x3B   
#define     Reserved31            0x3C   
#define     Reserved32            0x3D   
#define     Reserved33            0x3E   
#define     Reserved34			  0x3F
//-----------------------------------------------
extern unsigned char    SPIWriteByte(unsigned char  dat);                                               // SPIд
extern unsigned char    SPIReadByte(void);                                                  // SPI��
extern unsigned char    SPIReadWriteByte(unsigned char  dat);                                           // SPI��д
extern void Delay(unsigned short  nCount);
/*
 * �� �� ����Write_MFRC522
 * ��    �ã�Write_MFRC522(0x11, 0x3F);
 * ������������Ĵ���ModeReg(��ַ11h)д0x3F
 */
unsigned char  Write_MFRC522(unsigned char  addr, unsigned char  val);


/*
 * �� �� ����Read_MFRC522
 * ��    �ã�val = Read_MFRC522(0x11);
 * �������������Ĵ���ModeReg(��ַ11h)������
 */
unsigned char  Read_MFRC522(unsigned char  addr);


/*
 * �� �� ����MFRC522_Reset
 * ��    �ã�MFRC522_Reset();
 * ����������MFRC522��λ
 */
void MFRC522_Reset(void);


/*
 * �� �� ����MFRC522_Init
 * ��    �ã�MFRC522_Init();
 * ����������MFRC522��ʼ��
 */
void MFRC522_Init(void);


/*
 * �� �� ����MFRC522_Request
 * ��    �ã�status = MFRC522_Request(PICC_REQIDL, str);
 * ����������Ѱ���߷�Χ��δ���ߵĿ����ɹ�����MI_OK��ͬʱstr�н��տ�2Byte�����ʹ���
 */
unsigned char  MFRC522_Request(unsigned char  reqMode, unsigned char  *cardType);


/*
 * �� �� ����MFRC522_ToCard
 * ��    �ã�status = MFRC522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);
 * �����������������뿨ͨ��
 */
unsigned char  MFRC522_ToCard(unsigned char  command,unsigned char *sendData, unsigned char  sendLen, unsigned char *backData, unsigned short *backLen);


/*
 * �� �� ����MFRC522_Anticoll
 * ��    �ã�status = MFRC522_Anticoll(str);
 * ��������������ײ���ɹ�����MI_OK��ͬʱstr�н��տ�4Byte�����к�
 */
unsigned char  MFRC522_Anticoll(unsigned char  *serNum);


/*
 * �� �� ����MFRC522_SelectTag
 * ��    �ã�size = MFRC522_SelectTag(serNum);
 * ����������ѡ��������Ϊ�����кţ����ؿ�����������
 */
unsigned char  MFRC522_SelectTag(unsigned char  *serNum);


/*
 * �� �� ����MFRC522_Auth
 * ��    �ã�status = MFRC522_Auth(PICC_AUTHENT1A, blockAddr, sectorKeyA[blockAddr/4], serNum);
 * ������������֤���ɹ�����MI_OK
 */
unsigned char  MFRC522_Auth(unsigned char  authMode, unsigned char  BlockAddr, unsigned char  *Sectorkey, unsigned char  *serNum);


/*
 * �� �� ����MFRC522_Read
 * ��    �ã�status = MFRC522_Read(blockAddr, str);
 * �������������������ݣ��ɹ�����MI_OK��ͬʱ��ȡ����16Byte���ݱ��浽str�У�����blockAddrΪ���ַ
 */
unsigned char  MFRC522_Read(unsigned char  blockAddr,unsigned char  *recvData);


/*
 * �� �� ����MFRC522_Write
 * ��    �ã�status = MFRC522_Write(blockAddr, writeData);
 * ����������д�������ݣ���writeData������д��blockAddr��
 */
unsigned char  MFRC522_Write(unsigned char  blockAddr,unsigned char  *writeData);


/*
 * �� �� ����MFRC522_Halt
 * ��    �ã�MFRC522_Halt();
 * �������������Ƭ��������״̬����ֹ�ظ���
 */
unsigned char MFRC522_Halt(void);

#endif