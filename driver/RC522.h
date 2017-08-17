#ifndef _rc522_h_
#define _rc522_h_
/*******************************************************************************
****蓝旗嵌入式系统 STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****版本:V1.0
****日期:14-2-2014
****说明:主芯片STM8S105C4T6
********************************************************************************/
//数组最大长度
#define MAX_LEN 16
#define  SPI_DUMMY_BYTE                  (0xFF)                                 // 空闲数据
//NRSTPD引脚定义，Not Reset and Power-down
//sbit NRSTPD = P1^4; 
#define RFID_CS_PORT (GPIOE)
#define RFID_CS_PIN  (GPIO_PIN_5)

#define RFID_RST_PORT (GPIOC)
#define RFID_RST_PIN  (GPIO_PIN_2)



//4字节卡序列号，第5字节为校验字节
extern unsigned char  serNum[5];

//MF522命令字
#define PCD_IDLE              0x00               //NO action;取消当前命令
#define PCD_AUTHENT           0x0E               //验证密钥
#define PCD_RECEIVE           0x08               //接收数据
#define PCD_TRANSMIT          0x04               //发送数据
#define PCD_TRANSCEIVE        0x0C               //发送并接收数据
#define PCD_RESETPHASE        0x0F               //复位
#define PCD_CALCCRC           0x03               //CRC计算

//Mifare_One卡片命令字
#define PICC_REQIDL           0x26               //寻天线区内未进入休眠状态
#define PICC_REQALL           0x52               //寻天线区内全部卡
#define PICC_ANTICOLL         0x93               //防冲撞
#define PICC_SElECTTAG        0x93               //选卡
#define PICC_AUTHENT1A        0x60               //验证A密钥
#define PICC_AUTHENT1B        0x61               //验证B密钥
#define PICC_READ             0x30               //读块
#define PICC_WRITE            0xA0               //写块
#define PICC_DECREMENT        0xC0               //扣款
#define PICC_INCREMENT        0xC1               //充值
#define PICC_RESTORE          0xC2               //调块数据到缓冲区
#define PICC_TRANSFER         0xB0               //保存缓冲区中数据
#define PICC_HALT             0x50               //休眠


//和MF522通讯时返回的错误代码
#define MI_OK                 0
#define MI_NOTAGERR           1
#define MI_ERR                2


//------------------MFRC522寄存器---------------
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
extern unsigned char    SPIWriteByte(unsigned char  dat);                                               // SPI写
extern unsigned char    SPIReadByte(void);                                                  // SPI读
extern unsigned char    SPIReadWriteByte(unsigned char  dat);                                           // SPI读写
extern void Delay(unsigned short  nCount);
/*
 * 函 数 名：Write_MFRC522
 * 调    用：Write_MFRC522(0x11, 0x3F);
 * 功能描述：向寄存器ModeReg(地址11h)写0x3F
 */
unsigned char  Write_MFRC522(unsigned char  addr, unsigned char  val);


/*
 * 函 数 名：Read_MFRC522
 * 调    用：val = Read_MFRC522(0x11);
 * 功能描述：读寄存器ModeReg(地址11h)的数据
 */
unsigned char  Read_MFRC522(unsigned char  addr);


/*
 * 函 数 名：MFRC522_Reset
 * 调    用：MFRC522_Reset();
 * 功能描述：MFRC522复位
 */
void MFRC522_Reset(void);


/*
 * 函 数 名：MFRC522_Init
 * 调    用：MFRC522_Init();
 * 功能描述：MFRC522初始化
 */
void MFRC522_Init(void);


/*
 * 函 数 名：MFRC522_Request
 * 调    用：status = MFRC522_Request(PICC_REQIDL, str);
 * 功能描述：寻天线范围内未休眠的卡，成功返回MI_OK，同时str中接收卡2Byte的类型代码
 */
unsigned char  MFRC522_Request(unsigned char  reqMode, unsigned char  *cardType);


/*
 * 函 数 名：MFRC522_ToCard
 * 调    用：status = MFRC522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);
 * 功能描述：读卡器与卡通信
 */
unsigned char  MFRC522_ToCard(unsigned char  command,unsigned char *sendData, unsigned char  sendLen, unsigned char *backData, unsigned short *backLen);


/*
 * 函 数 名：MFRC522_Anticoll
 * 调    用：status = MFRC522_Anticoll(str);
 * 功能描述：防冲撞，成功返回MI_OK，同时str中接收卡4Byte卡序列号
 */
unsigned char  MFRC522_Anticoll(unsigned char  *serNum);


/*
 * 函 数 名：MFRC522_SelectTag
 * 调    用：size = MFRC522_SelectTag(serNum);
 * 功能描述：选卡，参数为卡序列号，返回卡储蓄器容量
 */
unsigned char  MFRC522_SelectTag(unsigned char  *serNum);


/*
 * 函 数 名：MFRC522_Auth
 * 调    用：status = MFRC522_Auth(PICC_AUTHENT1A, blockAddr, sectorKeyA[blockAddr/4], serNum);
 * 功能描述：认证，成功返回MI_OK
 */
unsigned char  MFRC522_Auth(unsigned char  authMode, unsigned char  BlockAddr, unsigned char  *Sectorkey, unsigned char  *serNum);


/*
 * 函 数 名：MFRC522_Read
 * 调    用：status = MFRC522_Read(blockAddr, str);
 * 功能描述：读卡块数据，成功返回MI_OK，同时读取到的16Byte数据保存到str中，参数blockAddr为块地址
 */
unsigned char  MFRC522_Read(unsigned char  blockAddr,unsigned char  *recvData);


/*
 * 函 数 名：MFRC522_Write
 * 调    用：status = MFRC522_Write(blockAddr, writeData);
 * 功能描述：写卡块数据，将writeData中数据写入blockAddr中
 */
unsigned char  MFRC522_Write(unsigned char  blockAddr,unsigned char  *writeData);


/*
 * 函 数 名：MFRC522_Halt
 * 调    用：MFRC522_Halt();
 * 功能描述：命令卡片进入休眠状态，防止重复读
 */
unsigned char MFRC522_Halt(void);

#endif