/*******************************************************************************
****蓝旗嵌入式系统 STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****版本:V1.0
****日期:14-2-2014
****说明:主芯片STM8S105C4T6
********************************************************************************/
#include "include.h"

/*******************************************************************************
****函数名称:
****函数功能:初始化ADC
****版本:V1.0
****日期:14-2-2014
****入口参数:无
****出口参数:无
****说明:
********************************************************************************/

//4字节卡序列号，第5字节为校验字节
unsigned char serNum[5];


//函数原型申明
void SetBitMask(unsigned char reg, unsigned char mask);
void ClearBitMask(unsigned char reg, unsigned char mask);
void AntennaOn(void);
void AntennaOff(void);
/*******************************************************************************
****函数名称:
****函数功能:延时函数
****版本:V1.0
****日期:14-2-2014
****入口参数:需要延时的数目
****出口参数:无
****说明:
********************************************************************************/
void Delay(unsigned short nCount)
{
  while (nCount != 0)
  {   
    nCount--;
  }
}
/**************************************************************************************
* FunctionName   : SPIReadWriteByte()
* Description    : SPI读写函数
* EntryParameter : dat - 要写入的数据
* ReturnValue    : 返回操作结果
**************************************************************************************/
u8 SPIReadWriteByte(unsigned char dat)
{
    while (SPI_GetFlagStatus(SPI_FLAG_TXE) == RESET);
  
    SPI_SendData(dat);                                                          // Send the byte

    while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET) ;
  
    return SPI_ReceiveData();                                                   // Return the byte read from the SPI bus
}

/**************************************************************************************
* FunctionName   : SPIWriteByte()
* Description    : SPI写函数
* EntryParameter : dat - 要写入的数据
* ReturnValue    : 返回操作结果
**************************************************************************************/
unsigned char SPIWriteByte(unsigned char dat)
{
    unsigned char tmp;
    
    while (SPI_GetFlagStatus(SPI_FLAG_TXE) == RESET);
    SPI_SendData(dat);                                                          // Send the byte

    while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
  
    tmp = SPI_ReceiveData();                                                   // Return the byte read from the SPI bus
    return tmp;
}

/**************************************************************************************
* FunctionName   : SPIReadByte()
* Description    : SPI读函数
* EntryParameter : None
* ReturnValue    : 返回读取数据
**************************************************************************************/
unsigned char SPIReadByte(void)
{
    unsigned char dat;
    while (SPI_GetFlagStatus(SPI_FLAG_TXE) == RESET);
  
    SPI_SendData(SPI_DUMMY_BYTE);                                               // Send the byte

    while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
  
    dat = SPI_ReceiveData();                                                    // Return the byte read from the SPI bus
    return dat;
}
/*
 * 函 数 名：Write_MFRC5200
 * 功能描述：向MFRC522的某一寄存器写一个字节数据
 * 输入参数：addr--寄存器地址；val--要写入的值
 * 返 回 值：无
 */
unsigned char Write_MFRC522(unsigned char addr, unsigned char val)
{
	unsigned char status;
       GPIO_WriteLow(RFID_CS_PORT, RFID_CS_PIN);

	//地址格式：0XXXXXX0
	SPIWriteByte((addr<<1)&0x7E);	

	status=SPIWriteByte(val);
	
	GPIO_WriteHigh(RFID_CS_PORT, RFID_CS_PIN);
        return status;
}


/*
 * 函 数 名：Read_MFRC522
 * 功能描述：从MFRC522的某一寄存器读一个字节数据
 * 输入参数：addr--寄存器地址
 * 返 回 值：返回读取到的一个字节数据
 */
unsigned char Read_MFRC522(unsigned char addr)
{
	unsigned char val;

	GPIO_WriteLow(RFID_CS_PORT, RFID_CS_PIN);

	//地址格式：1XXXXXX0
	SPIWriteByte(((addr<<1)&0x7E) | 0x80);	
        //SPIWriteByte(((addr & 0x3F) << 1) | 0x80);	
	val = SPIReadByte();
	
	GPIO_WriteHigh(RFID_CS_PORT, RFID_CS_PIN);
	
	return val;	
}

/*
 * 函 数 名：SetBitMask
 * 功能描述：置RC522寄存器位
 * 输入参数：reg--寄存器地址;mask--置位值
 * 返 回 值：无
 */
void SetBitMask(unsigned char reg, unsigned char mask)  
{
    unsigned char tmp;
    tmp = Read_MFRC522(reg);
    Write_MFRC522(reg, tmp | mask);  // set bit mask
}


/*
 * 函 数 名：ClearBitMask
 * 功能描述：清RC522寄存器位
 * 输入参数：reg--寄存器地址;mask--清位值
 * 返 回 值：无
 */
void ClearBitMask(unsigned char reg,unsigned char mask)  
{
    unsigned char tmp;
    tmp = Read_MFRC522(reg);
    Write_MFRC522(reg, tmp & (~mask));  // clear bit mask
} 


/*
 * 函 数 名：AntennaOn
 * 功能描述：开启天线,每次启动或关闭天险发射之间应至少有1ms的间隔
 * 输入参数：无
 * 返 回 值：无
 */
void AntennaOn(void)
{
	unsigned char temp;

	temp = Read_MFRC522(TxControlReg);
	if (!(temp & 0x03))
	{
		SetBitMask(TxControlReg, 0x03);
	}
}


/*
 * 函 数 名：AntennaOff
 * 功能描述：关闭天线,每次启动或关闭天险发射之间应至少有1ms的间隔
 * 输入参数：无
 * 返 回 值：无
 */
void AntennaOff(void)
{
	ClearBitMask(TxControlReg, 0x03);
}


/*
 * 函 数 名：ResetMFRC522
 * 功能描述：复位RC522
 * 输入参数：无
 * 返 回 值：无
 */
void MFRC522_Reset(void)
{
    Write_MFRC522(CommandReg, PCD_RESETPHASE);
}


/*
 * 函 数 名：InitMFRC522
 * 功能描述：初始化RC522
 * 输入参数：无
 * 返 回 值：无
 */
void MFRC522_Init(void)
{ 
   SPI_DeInit();
   SPI_Init(SPI_FIRSTBIT_MSB, 
           SPI_BAUDRATEPRESCALER_16, 
           SPI_MODE_MASTER, 
           SPI_CLOCKPOLARITY_HIGH, 
           SPI_CLOCKPHASE_2EDGE, 
           SPI_DATADIRECTION_2LINES_FULLDUPLEX, 
           SPI_NSS_SOFT, 
           0x07);
   
   GPIO_Init(RFID_CS_PORT, (GPIO_Pin_TypeDef)RFID_CS_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
   GPIO_Init(RFID_RST_PORT, (GPIO_Pin_TypeDef)RFID_RST_PIN, GPIO_MODE_OUT_PP_LOW_FAST); 
   GPIO_WriteHigh(RFID_RST_PORT, RFID_RST_PIN);
   
   SPI_Cmd(ENABLE);
   MFRC522_Reset();
 	
	//Timer: TPrescaler*TreloadVal/6.78MHz = 24ms
    Write_MFRC522(TModeReg, 0x8D);		//Tauto=1; f(Timer) = 6.78MHz/TPreScaler
    Read_MFRC522(TModeReg);
    Write_MFRC522(TPrescalerReg, 0x3E);	//TModeReg[3..0] + TPrescalerReg
    Write_MFRC522(TReloadRegL, 30);           
    Write_MFRC522(TReloadRegH, 0);
	
    Write_MFRC522(TxAutoReg, 0x40);		//100%ASK
    Write_MFRC522(ModeReg, 0x3D);		//CRC初始值0x6363	???
    
    AntennaOn();		//打开天线
}


/*
 * 函 数 名：MFRC522_Request
 * 功能描述：寻卡，读取卡类型号
 * 输入参数：reqMode--寻卡方式，
 *			 TagType--返回卡片类型
 *			 	0x4400 = Mifare_UltraLight
 *				0x0400 = Mifare_One(S50)
 *				0x0200 = Mifare_One(S70)
 *				0x0800 = Mifare_Pro(X)
 *				0x4403 = Mifare_DESFire
 * 返 回 值：成功返回MI_OK
 */
unsigned char MFRC522_Request(unsigned char reqMode, unsigned char *TagType)
{
	unsigned char status;  
	unsigned short backBits;			//接收到的数据位数

	//ClearBitMask(Status2Reg, 0x08);			
        
        Write_MFRC522(BitFramingReg, 0x07);		//TxLastBists = BitFramingReg[2..0]	???
	//SetBitMask(TxControlReg, 0x03);			
        
	TagType[0] = reqMode;
	status = MFRC522_ToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);
        //Send_Hex(status);
	if ((status != MI_OK) || (backBits != 0x10))
	{    
		status = MI_ERR;
	}
   
	return status;
}


/*
 * 函 数 名：MFRC522_ToCard
 * 功能描述：RC522和ISO14443卡通讯
 * 输入参数：command--MF522命令字，
 *			 sendData--通过RC522发送到卡片的数据, 
 *			 sendLen--发送的数据长度		 
 *			 backData--接收到的卡片返回数据，
 *			 backLen--返回数据的位长度
 * 返 回 值：成功返回MI_OK
 */
unsigned char MFRC522_ToCard(unsigned char command, unsigned char *sendData, unsigned char sendLen, unsigned char *backData, unsigned short *backLen)
{
    unsigned char status = MI_ERR;
    unsigned char irqEn = 0x00;
    unsigned char waitIRq = 0x00;
    unsigned char lastBits;
    unsigned char n;
    unsigned short i;

    switch (command)
    {
        case PCD_AUTHENT:		//认证卡密
		{
			irqEn = 0x12;
			waitIRq = 0x10;
			break;
		}
		case PCD_TRANSCEIVE:	//发送FIFO中数据
		{
			irqEn = 0x77;
			waitIRq = 0x30;
			break;
		}
		default:
			break;
    }
   
    Write_MFRC522(CommIEnReg, irqEn|0x80);	//允许中断请求
    ClearBitMask(CommIrqReg, 0x80);			//清除所有中断请求位
    SetBitMask(FIFOLevelReg, 0x80);			//FlushBuffer=1, FIFO初始化
    
    Write_MFRC522(CommandReg, PCD_IDLE);	//NO action;取消当前命令	???

	//向FIFO中写入数据
    for (i=0; i<sendLen; i++)
    {   
	n=Write_MFRC522(FIFODataReg, sendData[i]);    
    }

	//执行命令
    Write_MFRC522(CommandReg, command);
    n = Read_MFRC522(CommandReg);
    if (command == PCD_TRANSCEIVE)
    {    
	SetBitMask(BitFramingReg, 0x80);		//StartSend=1,transmission of data starts  
    }   
    
	//等待接收数据完成
    i = 2000;	//i根据时钟频率调整，操作M1卡最大等待时间25ms	???
    do 
    {
		//CommIrqReg[7..0]
		//Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
        n = Read_MFRC522(CommIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x01) && !(n&waitIRq));

    ClearBitMask(BitFramingReg, 0x80);			//StartSend=0
	
    if (i != 0)
    {    
        if(!(Read_MFRC522(ErrorReg) & 0x1B))	//BufferOvfl Collerr CRCErr ProtecolErr
        {
            status = MI_OK;
            if (n & irqEn & 0x01)
            {   
				status = MI_NOTAGERR;			//??   
	    }

            if (command == PCD_TRANSCEIVE)
            {
               	n = Read_MFRC522(FIFOLevelReg);
              	lastBits = Read_MFRC522(ControlReg) & 0x07;
                if (lastBits)
                {   
		    *backLen = (n-1)*8 + lastBits;   
		}
                else
                {   
		    *backLen = n*8;   
		}

                if (n == 0)
                {   
		    n = 1;    
	        }
                if (n > MAX_LEN)
                {   
		    n = MAX_LEN;   
		}
				
				//读取FIFO中接收到的数据
                for (i=0; i<n; i++)
                {   
		    backData[i] = Read_MFRC522(FIFODataReg);    
		}
            }
        }
        else
        {   
		status = MI_ERR;  
	}
        
    }
	
    //SetBitMask(ControlReg,0x80);           //timer stops
    //Write_MFRC522(CommandReg, PCD_IDLE); 

    return status;
}


/*
 * 函 数 名：MFRC522_Anticoll
 * 功能描述：防冲突检测，读取选中卡片的卡序列号
 * 输入参数：serNum--返回4字节卡序列号,第5字节为校验字节
 * 返 回 值：成功返回MI_OK
 */
unsigned char MFRC522_Anticoll(unsigned char *serNum)
{
    unsigned char  status;
    unsigned char  i;
    unsigned char serNumCheck=0;
    unsigned short unLen;
    

    //ClearBitMask(Status2Reg, 0x08);		//TempSensclear
    //ClearBitMask(CollReg,0x80);			//ValuesAfterColl
    Write_MFRC522(BitFramingReg, 0x00);		//TxLastBists = BitFramingReg[2..0]
 
    serNum[0] = PICC_ANTICOLL;
    serNum[1] = 0x20;
    status = MFRC522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);

    if (status == MI_OK)
	{
		//校验卡序列号
		for (i=0; i<4; i++)
		{   
		 	serNumCheck ^= serNum[i];
		}
		if (serNumCheck != serNum[i])
		{   
			status = MI_ERR;    
		}
    }

    //SetBitMask(CollReg, 0x80);		//ValuesAfterColl=1

    return status;
} 


/*
 * 函 数 名：CalulateCRC
 * 功能描述：用MF522计算CRC
 * 输入参数：pIndata--要读数CRC的数据，len--数据长度，pOutData--计算的CRC结果
 * 返 回 值：无
 */
void CalulateCRC(unsigned char  *pIndata, unsigned char  len, unsigned char  *pOutData)
{
    unsigned char  i, n;

    ClearBitMask(DivIrqReg, 0x04);			//CRCIrq = 0
    SetBitMask(FIFOLevelReg, 0x80);			//清FIFO指针
    //Write_MFRC522(CommandReg, PCD_IDLE);

	//向FIFO中写入数据	
    for (i=0; i<len; i++)
    {   
	Write_MFRC522(FIFODataReg, *(pIndata+i));   
    }
    Write_MFRC522(CommandReg, PCD_CALCCRC);

	//等待CRC计算完成
    i = 0xFF;
    do 
    {
        n = Read_MFRC522(DivIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x04));			//CRCIrq = 1

	//读取CRC计算结果
    pOutData[0] = Read_MFRC522(CRCResultRegL);
    pOutData[1] = Read_MFRC522(CRCResultRegM);
}


/*
 * 函 数 名：MFRC522_SelectTag
 * 功能描述：选卡，读取卡存储器容量
 * 输入参数：serNum--传入卡序列号
 * 返 回 值：成功返回卡容量
 */
unsigned char  MFRC522_SelectTag(unsigned char  *serNum)
{
    unsigned char  i;
    unsigned char  status;
    unsigned char  size;
    unsigned short recvBits;
    unsigned char  buffer[9]; 

	//ClearBitMask(Status2Reg, 0x08);			//MFCrypto1On=0

    buffer[0] = PICC_SElECTTAG;
    buffer[1] = 0x70;
    for (i=0; i<5; i++)
    {
    	buffer[i+2] = *(serNum+i);
    }
    CalulateCRC(buffer, 7, &buffer[7]);		//??
    status = MFRC522_ToCard(PCD_TRANSCEIVE, buffer, 9, buffer, &recvBits);
    
    if ((status == MI_OK) && (recvBits == 0x18))
    {   
	size = buffer[0]; 
    }
    else
    {   
	size = 0;    
    }

    return size;
}


/*
 * 函 数 名：MFRC522_Auth
 * 功能描述：验证卡片密码
 * 输入参数：authMode--密码验证模式
                 0x60 = 验证A密钥
                 0x61 = 验证B密钥 
             BlockAddr--块地址
             Sectorkey--扇区密码
             serNum--卡片序列号，4字节
 * 返 回 值：成功返回MI_OK
 */
unsigned char  MFRC522_Auth(unsigned char  authMode, unsigned char  BlockAddr, unsigned char  *Sectorkey, unsigned char  *serNum)
{
    unsigned char  status;
    unsigned short  recvBits;
    unsigned char  i;
    unsigned char  buff[12]; 

	//验证指令+块地址＋扇区密码＋卡序列号
    buff[0] = authMode;
    buff[1] = BlockAddr;
    for (i=0; i<6; i++)
    {    
	buff[i+2] = *(Sectorkey+i);   
    }
    for (i=0; i<4; i++)
    {    
	buff[i+8] = *(serNum+i);   
    }
    status = MFRC522_ToCard(PCD_AUTHENT, buff, 12, buff, &recvBits);

    if ((status != MI_OK) || (!(Read_MFRC522(Status2Reg) & 0x08)))
    {   
	status = MI_ERR;   
    }
    
    return status;
}


/*
 * 函 数 名：MFRC522_Read
 * 功能描述：读块数据
 * 输入参数：blockAddr--块地址;recvData--读出的块数据
 * 返 回 值：成功返回MI_OK
 */
unsigned char  MFRC522_Read(unsigned char  blockAddr, unsigned char  *recvData)
{
    unsigned char  status;
    unsigned short unLen;

    recvData[0] = PICC_READ;
    recvData[1] = blockAddr;
    CalulateCRC(recvData,2, &recvData[2]);
    status = MFRC522_ToCard(PCD_TRANSCEIVE, recvData, 4, recvData, &unLen);

    if ((status != MI_OK) || (unLen != 0x90))
    {
        status = MI_ERR;
    }
    
    return status;
}


/*
 * 函 数 名：MFRC522_Write
 * 功能描述：写块数据
 * 输入参数：blockAddr--块地址;writeData--向块写16字节数据
 * 返 回 值：成功返回MI_OK
 */
unsigned char  MFRC522_Write(unsigned char  blockAddr, unsigned char  *writeData)
{
    unsigned char  status;
    unsigned short  recvBits;
    unsigned char  i;
    unsigned char  buff[18]; 
    
    buff[0] = PICC_WRITE;
    buff[1] = blockAddr;
    CalulateCRC(buff, 2, &buff[2]);
    status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);

    if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
    {   
		status = MI_ERR;   
	}
        
    if (status == MI_OK)
    {
        for (i=0; i<16; i++)		//向FIFO写16Byte数据
        {    
        	buff[i] = *(writeData+i);   
        }
        CalulateCRC(buff, 16, &buff[16]);
        status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);
        
		if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
        {   
			status = MI_ERR;   
		}
    }
    
    return status;
}


/*
 * 函 数 名：MFRC522_Halt
 * 功能描述：命令卡片进入休眠状态
 * 输入参数：无
 * 返 回 值：无
 */
unsigned char MFRC522_Halt(void)
{
    unsigned char  status;
    unsigned short  unLen;
    unsigned char  buff[4]; 

    buff[0] = PICC_HALT;
    buff[1] = 0;
    CalulateCRC(buff, 2, &buff[2]);
 
    status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff,&unLen);
    return status;
}