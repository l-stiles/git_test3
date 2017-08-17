/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
#include "include.h"

/*******************************************************************************
****��������:
****��������:��ʼ��ADC
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/

//4�ֽڿ����кţ���5�ֽ�ΪУ���ֽ�
unsigned char serNum[5];


//����ԭ������
void SetBitMask(unsigned char reg, unsigned char mask);
void ClearBitMask(unsigned char reg, unsigned char mask);
void AntennaOn(void);
void AntennaOff(void);
/*******************************************************************************
****��������:
****��������:��ʱ����
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��Ҫ��ʱ����Ŀ
****���ڲ���:��
****˵��:
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
* Description    : SPI��д����
* EntryParameter : dat - Ҫд�������
* ReturnValue    : ���ز������
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
* Description    : SPIд����
* EntryParameter : dat - Ҫд�������
* ReturnValue    : ���ز������
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
* Description    : SPI������
* EntryParameter : None
* ReturnValue    : ���ض�ȡ����
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
 * �� �� ����Write_MFRC5200
 * ������������MFRC522��ĳһ�Ĵ���дһ���ֽ�����
 * ���������addr--�Ĵ�����ַ��val--Ҫд���ֵ
 * �� �� ֵ����
 */
unsigned char Write_MFRC522(unsigned char addr, unsigned char val)
{
	unsigned char status;
       GPIO_WriteLow(RFID_CS_PORT, RFID_CS_PIN);

	//��ַ��ʽ��0XXXXXX0
	SPIWriteByte((addr<<1)&0x7E);	

	status=SPIWriteByte(val);
	
	GPIO_WriteHigh(RFID_CS_PORT, RFID_CS_PIN);
        return status;
}


/*
 * �� �� ����Read_MFRC522
 * ������������MFRC522��ĳһ�Ĵ�����һ���ֽ�����
 * ���������addr--�Ĵ�����ַ
 * �� �� ֵ�����ض�ȡ����һ���ֽ�����
 */
unsigned char Read_MFRC522(unsigned char addr)
{
	unsigned char val;

	GPIO_WriteLow(RFID_CS_PORT, RFID_CS_PIN);

	//��ַ��ʽ��1XXXXXX0
	SPIWriteByte(((addr<<1)&0x7E) | 0x80);	
        //SPIWriteByte(((addr & 0x3F) << 1) | 0x80);	
	val = SPIReadByte();
	
	GPIO_WriteHigh(RFID_CS_PORT, RFID_CS_PIN);
	
	return val;	
}

/*
 * �� �� ����SetBitMask
 * ������������RC522�Ĵ���λ
 * ���������reg--�Ĵ�����ַ;mask--��λֵ
 * �� �� ֵ����
 */
void SetBitMask(unsigned char reg, unsigned char mask)  
{
    unsigned char tmp;
    tmp = Read_MFRC522(reg);
    Write_MFRC522(reg, tmp | mask);  // set bit mask
}


/*
 * �� �� ����ClearBitMask
 * ������������RC522�Ĵ���λ
 * ���������reg--�Ĵ�����ַ;mask--��λֵ
 * �� �� ֵ����
 */
void ClearBitMask(unsigned char reg,unsigned char mask)  
{
    unsigned char tmp;
    tmp = Read_MFRC522(reg);
    Write_MFRC522(reg, tmp & (~mask));  // clear bit mask
} 


/*
 * �� �� ����AntennaOn
 * ������������������,ÿ��������ر����շ���֮��Ӧ������1ms�ļ��
 * �����������
 * �� �� ֵ����
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
 * �� �� ����AntennaOff
 * �����������ر�����,ÿ��������ر����շ���֮��Ӧ������1ms�ļ��
 * �����������
 * �� �� ֵ����
 */
void AntennaOff(void)
{
	ClearBitMask(TxControlReg, 0x03);
}


/*
 * �� �� ����ResetMFRC522
 * ������������λRC522
 * �����������
 * �� �� ֵ����
 */
void MFRC522_Reset(void)
{
    Write_MFRC522(CommandReg, PCD_RESETPHASE);
}


/*
 * �� �� ����InitMFRC522
 * ������������ʼ��RC522
 * �����������
 * �� �� ֵ����
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
    Write_MFRC522(ModeReg, 0x3D);		//CRC��ʼֵ0x6363	???
    
    AntennaOn();		//������
}


/*
 * �� �� ����MFRC522_Request
 * ����������Ѱ������ȡ�����ͺ�
 * ���������reqMode--Ѱ����ʽ��
 *			 TagType--���ؿ�Ƭ����
 *			 	0x4400 = Mifare_UltraLight
 *				0x0400 = Mifare_One(S50)
 *				0x0200 = Mifare_One(S70)
 *				0x0800 = Mifare_Pro(X)
 *				0x4403 = Mifare_DESFire
 * �� �� ֵ���ɹ�����MI_OK
 */
unsigned char MFRC522_Request(unsigned char reqMode, unsigned char *TagType)
{
	unsigned char status;  
	unsigned short backBits;			//���յ�������λ��

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
 * �� �� ����MFRC522_ToCard
 * ����������RC522��ISO14443��ͨѶ
 * ���������command--MF522�����֣�
 *			 sendData--ͨ��RC522���͵���Ƭ������, 
 *			 sendLen--���͵����ݳ���		 
 *			 backData--���յ��Ŀ�Ƭ�������ݣ�
 *			 backLen--�������ݵ�λ����
 * �� �� ֵ���ɹ�����MI_OK
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
        case PCD_AUTHENT:		//��֤����
		{
			irqEn = 0x12;
			waitIRq = 0x10;
			break;
		}
		case PCD_TRANSCEIVE:	//����FIFO������
		{
			irqEn = 0x77;
			waitIRq = 0x30;
			break;
		}
		default:
			break;
    }
   
    Write_MFRC522(CommIEnReg, irqEn|0x80);	//�����ж�����
    ClearBitMask(CommIrqReg, 0x80);			//��������ж�����λ
    SetBitMask(FIFOLevelReg, 0x80);			//FlushBuffer=1, FIFO��ʼ��
    
    Write_MFRC522(CommandReg, PCD_IDLE);	//NO action;ȡ����ǰ����	???

	//��FIFO��д������
    for (i=0; i<sendLen; i++)
    {   
	n=Write_MFRC522(FIFODataReg, sendData[i]);    
    }

	//ִ������
    Write_MFRC522(CommandReg, command);
    n = Read_MFRC522(CommandReg);
    if (command == PCD_TRANSCEIVE)
    {    
	SetBitMask(BitFramingReg, 0x80);		//StartSend=1,transmission of data starts  
    }   
    
	//�ȴ������������
    i = 2000;	//i����ʱ��Ƶ�ʵ���������M1�����ȴ�ʱ��25ms	???
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
				
				//��ȡFIFO�н��յ�������
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
 * �� �� ����MFRC522_Anticoll
 * ��������������ͻ��⣬��ȡѡ�п�Ƭ�Ŀ����к�
 * ���������serNum--����4�ֽڿ����к�,��5�ֽ�ΪУ���ֽ�
 * �� �� ֵ���ɹ�����MI_OK
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
		//У�鿨���к�
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
 * �� �� ����CalulateCRC
 * ������������MF522����CRC
 * ���������pIndata--Ҫ����CRC�����ݣ�len--���ݳ��ȣ�pOutData--�����CRC���
 * �� �� ֵ����
 */
void CalulateCRC(unsigned char  *pIndata, unsigned char  len, unsigned char  *pOutData)
{
    unsigned char  i, n;

    ClearBitMask(DivIrqReg, 0x04);			//CRCIrq = 0
    SetBitMask(FIFOLevelReg, 0x80);			//��FIFOָ��
    //Write_MFRC522(CommandReg, PCD_IDLE);

	//��FIFO��д������	
    for (i=0; i<len; i++)
    {   
	Write_MFRC522(FIFODataReg, *(pIndata+i));   
    }
    Write_MFRC522(CommandReg, PCD_CALCCRC);

	//�ȴ�CRC�������
    i = 0xFF;
    do 
    {
        n = Read_MFRC522(DivIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x04));			//CRCIrq = 1

	//��ȡCRC������
    pOutData[0] = Read_MFRC522(CRCResultRegL);
    pOutData[1] = Read_MFRC522(CRCResultRegM);
}


/*
 * �� �� ����MFRC522_SelectTag
 * ����������ѡ������ȡ���洢������
 * ���������serNum--���뿨���к�
 * �� �� ֵ���ɹ����ؿ�����
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
 * �� �� ����MFRC522_Auth
 * ������������֤��Ƭ����
 * ���������authMode--������֤ģʽ
                 0x60 = ��֤A��Կ
                 0x61 = ��֤B��Կ 
             BlockAddr--���ַ
             Sectorkey--��������
             serNum--��Ƭ���кţ�4�ֽ�
 * �� �� ֵ���ɹ�����MI_OK
 */
unsigned char  MFRC522_Auth(unsigned char  authMode, unsigned char  BlockAddr, unsigned char  *Sectorkey, unsigned char  *serNum)
{
    unsigned char  status;
    unsigned short  recvBits;
    unsigned char  i;
    unsigned char  buff[12]; 

	//��ָ֤��+���ַ���������룫�����к�
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
 * �� �� ����MFRC522_Read
 * ������������������
 * ���������blockAddr--���ַ;recvData--�����Ŀ�����
 * �� �� ֵ���ɹ�����MI_OK
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
 * �� �� ����MFRC522_Write
 * ����������д������
 * ���������blockAddr--���ַ;writeData--���д16�ֽ�����
 * �� �� ֵ���ɹ�����MI_OK
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
        for (i=0; i<16; i++)		//��FIFOд16Byte����
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
 * �� �� ����MFRC522_Halt
 * �������������Ƭ��������״̬
 * �����������
 * �� �� ֵ����
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