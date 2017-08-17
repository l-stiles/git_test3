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
****��������:TF���˿ڳ�ʼ������
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/
void TF_Init(void)
{
      SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_4, SPI_MODE_MASTER,\
      SPI_CLOCKPOLARITY_LOW, SPI_CLOCKPHASE_1EDGE, \
      SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x07);
	
      SPI_Cmd(ENABLE);	/* ʹ��SPI */
	
	/* ����PE7���ţ���������SD��CS���� */
      GPIO_Init(TF_CS_PORT, TF_CS_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
      Clr_TF_CS;
}
/*******************************************************************************
****��������:
****��������:��TF������ΪSPIģʽ����ʼ��TF������
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/
unsigned char TF_Idle_Sta(void)
{
  	unsigned char r1;
	unsigned short i;
	unsigned int retry = 0;
 	
	do
	{
		for(i=0;i<10;i++) 
			SPI_FLASH_SendByte(0xff);
		
		r1 = TF_SendCommand(CMD0, 0,0x95);      //��CMD0�Կ����и�λ	
		if(++retry > 100) 
                  return 1;          //��ʱ�˳�
	}while(r1 != 0x01);   /* ����ֵΪ0x01ʱ��λ����ɹ� */
	
	retry = 0;
	do
	{
		r1 =TF_SendCommand(CMD1, 0,0x95);      //��CMD1�Կ����г�ʼ��  		
		if(++retry > 100) 
                  return 1;         //��ʱ�˳�
	} while(r1);	/* ����ֵΪ0ʱ��ʼ������ɹ� */
	
	r1 = TF_SendCommand(CMD59, 0,0x95);        //��crc
	
	r1 = TF_SendCommand(CMD16, 512,0x95);      //��������С512
	
	return 0;                           	//�������أ����ԶԿ����ж�д
}	
/*******************************************************************************
****��������:
****��������:�ȴ�TF����Ӧ����
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/
unsigned char TF_GetResponse(unsigned char Response)
{
	unsigned short Count=0xFFF;//�ȴ�����	
	
	while ((SPI_FLASH_SendByte(0XFF)!=Response)&&Count)
		Count--;//�ȴ��õ�׼ȷ�Ļ�Ӧ  	  
	
	if (Count==0)
	  	return MSD_RESPONSE_FAILURE;//�õ���Ӧʧ��   
	else return 
	  	MSD_RESPONSE_NO_ERROR;//��ȷ��Ӧ
}
/*******************************************************************************
****��������:
****��������:�ȴ�TF��д����ɺ���
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/
unsigned char TF_WaitDataReady(void)
{
	unsigned char r1=MSD_DATA_OTHER_ERROR;
	unsigned int retry;
	retry=0;
	do
	{
		r1=SPI_FLASH_SendByte(0xFF)&0X1F;//������Ӧ
		if(retry==0xfffe)
                  return 1; 
			retry++;
		switch (r1)
		{					   
			case MSD_DATA_OK://���ݽ�����ȷ��	 
			r1=MSD_DATA_OK;
			break;  
			case MSD_DATA_CRC_ERROR:  //CRCУ�����
			return MSD_DATA_CRC_ERROR;  
			case MSD_DATA_WRITE_ERROR://����д�����
			return MSD_DATA_WRITE_ERROR;  
			default://δ֪����    
			r1=MSD_DATA_OTHER_ERROR;
			break;	 
		}   
	}
	while(r1==MSD_DATA_OTHER_ERROR); //���ݴ���ʱһֱ�ȴ�
	
	retry=0;
	while(SPI_FLASH_SendByte(0XFF)==0)//��������Ϊ0,�����ݻ�δд���
	{
		retry++;
		//delay_us(10);//TF��д�ȴ���Ҫ�ϳ���ʱ��
		if(retry>=0XFFFFFFFE)
                  return 0XFF;//�ȴ�ʧ����
	};	    
	
	return 0;//�ɹ���
}	
/*******************************************************************************
****��������:
****��������:��TF��д�������
****�汾:V1.0
****����:14-2-2014
****��ڲ���:cmd���arg���������CRCУ��
****���ڲ���:
****˵��:
********************************************************************************/
unsigned char TF_SendCommand(unsigned char cmd, unsigned int arg, unsigned char crc)
{
	unsigned char r1;	
	unsigned char Retry=0;	
	
	Set_TF_CS;	/* ����Ƭѡ�� */
	SPI_FLASH_SendByte(0xff);
	SPI_FLASH_SendByte(0xff);     
	SPI_FLASH_SendByte(0xff);  	 
	SPI_FLASH_SendByte(0xff);		/* ����74��ʱ���ӳ� */
	
	
	Clr_TF_CS; //Ƭѡ���õͣ�ѡ��TF��
	
	/* ��һ�������ʽ���� */
	SPI_FLASH_SendByte(cmd | 0x40);//�ֱ�д������
	SPI_FLASH_SendByte(arg >> 24);
	SPI_FLASH_SendByte(arg >> 16);
	SPI_FLASH_SendByte(arg >> 8);
	SPI_FLASH_SendByte(arg);
	SPI_FLASH_SendByte(crc); 
	
	//�ȴ���Ӧ����ʱ�˳�
	r1=SPI_FLASH_SendByte(0xFF);
	while(r1==0xFF)
	{
		r1=SPI_FLASH_SendByte(0xFF);
		Retry++;	    
		if(Retry>200)break; 
	}   
	
	Set_TF_CS;	//�ر�Ƭѡ
	
	SPI_FLASH_SendByte(0xFF);	//�������϶�������8��ʱ�ӣ���SD�����ʣ�µĹ���
	
	return r1;	//����״ֵ̬
}	
/*******************************************************************************
****��������:
****��������:��TF��д������������CS������Ч���к������ݴ���
****�汾:V1.0
****����:14-2-2014
****��ڲ���:cmd���arg���������CRCУ��
****���ڲ���:
****˵��:
********************************************************************************/
unsigned char TF_SendCommand_NoDeassert(unsigned char cmd, unsigned int arg, unsigned char crc)
{
	unsigned char Retry=0;	         
	unsigned char r1;			   
	
	SPI_FLASH_SendByte(0xff);
	SPI_FLASH_SendByte(0xff);  	 	 
	Clr_TF_CS;//Ƭѡ���õͣ�ѡ��TF��	
	
	//����
	SPI_FLASH_SendByte(cmd | 0x40); //�ֱ�д������
	SPI_FLASH_SendByte(arg >> 24);
	SPI_FLASH_SendByte(arg >> 16);
	SPI_FLASH_SendByte(arg >> 8);
	SPI_FLASH_SendByte(arg);
	SPI_FLASH_SendByte(crc);   
	
	//�ȴ���Ӧ����ʱ�˳�
	while((r1=SPI_FLASH_SendByte(0xFF))==0xFF)
	{
		Retry++;	    
		if(Retry>200)break; 
	}  	  
	//������Ӧֵ
	return r1;
}
/*******************************************************************************
****��������:
****��������:��TF����ȡָ�����ȵ�����
****�汾:V1.0
****����:14-2-2014
****��ڲ���:u8 *data(��Ŷ������ݵ��ڴ�>len)
             u16 len(���ݳ��ȣ�
             u8 release(������ɺ��Ƿ��ͷ�����CS�ø� 0�����ͷ� 1���ͷţ�	
****���ڲ���:
****˵��:
********************************************************************************/
unsigned char TF_ReceiveData(unsigned char *data, unsigned short len, unsigned char release)
{
	// ����һ�δ���
	Clr_TF_CS;				  	  
	if(TF_GetResponse(0xFE))//�ȴ�TF������������ʼ����0xFE
	{	  
		Set_TF_CS;
		return 1;
	}
	
	while(len--)//��ʼ��������
	{
		*data=SPI_FLASH_SendByte(0xFF);
		data++;
	}
	//������2��αCRC��dummy CRC��
	SPI_FLASH_SendByte(0xFF);
	SPI_FLASH_SendByte(0xFF);
	
	if(release==RELEASE)//�����ͷ����ߣ���CS�ø�
	{
		Set_TF_CS;//�������
		SPI_FLASH_SendByte(0xFF);
	}											  					    
	return 0;
}	
/*******************************************************************************
****��������:
****��������:��TF����ȡCID
****�汾:V1.0
****����:14-2-2014
****��ڲ���:*cid���CID���ڴ�
****���ڲ���:
****˵��:
********************************************************************************/
unsigned char TF_GetCID(TF_CID *cid)
{
	unsigned char r1;	
	unsigned char cidTable[16];
	
	//��CMD10�����CID
	r1 = TF_SendCommand(CMD10,0,0xFF);
	
	if(r1 != 0x00)
	  	return r1;  //û������ȷӦ�����˳�������
	
	TF_ReceiveData(cidTable,16,RELEASE);	//����16���ֽڵ�����	
	
	// �ѻ�ȡֵ����CID�ṹ����
	cid->ManufacturerID = cidTable[0];           // Byte 0
	cid->OEM_AppliID = cidTable[1] << 8;      	 // Byte 1
	cid->OEM_AppliID |= cidTable[2];           	 // Byte 2
	cid->ProdName1 = cidTable[3] << 24;     	 // Byte 3
	cid->ProdName1 |= cidTable[4] << 16;     	 // Byte 4
	cid->ProdName1 |= cidTable[5] << 8;      	 // Byte 5
	cid->ProdName1 |= cidTable[6];           	 // Byte 6
	cid->ProdName2 = cidTable[7];           	 // Byte 7
	cid->ProdRev = cidTable[8];           	 	 // Byte 8
	cid->ProdSN = cidTable[9] << 24;     		 // Byte 9
	cid->ProdSN |= cidTable[10] << 16;    		 // Byte 10
	cid->ProdSN |= cidTable[11] << 8;     		 // Byte 11
	cid->ProdSN |= cidTable[12];          		 // Byte 12
	cid->Reserved1 |= (cidTable[13] & 0xF0) >> 4;       	// Byte 13
	cid->ManufactDate = (cidTable[13] & 0x0F) << 8;         // Byte 14
	cid->ManufactDate |= cidTable[14];           			// Byte 15
	cid->CID_CRC = (cidTable[15] & 0xFE) >> 1;
	cid->Reserved2 = 1;
	
	return 0;
}
/*******************************************************************************
****��������:
****��������:��TF����ȡCSD
****�汾:V1.0
****����:14-2-2014
****��ڲ���:*csd���CSD���ڴ棬����16���ֽ�
****���ڲ���:
****˵��:
********************************************************************************/
unsigned char TF_GetCSD(unsigned char * csd)
{
	unsigned char r1;	 
	
	r1=TF_SendCommand(CMD9, 0, 0xFF);//��CMD9�����CSD
	
	if(r1)
	  	return r1;  //û������ȷӦ�����˳�������  
	
	TF_ReceiveData(csd, 16, RELEASE);//����16���ֽڵ����� 

	return 0;
}  
/*******************************************************************************
****��������:
****��������:��ȡTF������
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:
****˵��:
********************************************************************************/
unsigned int TF_GetCapacity(void)
{
	unsigned char csd[16];
	unsigned int Capacity;
	unsigned char r1;
	unsigned short i;
	unsigned short temp;  				
	
	//ȡCSD��Ϣ������ڼ��������0
	if(TF_GetCSD(csd)!=0) return 0;	   
	
	//���ΪSDHC�����������淽ʽ����
	if((csd[0]&0xC0)==0x40)
	{									  
		Capacity=((u32)csd[8])<<8;
		Capacity+=(u32)csd[9]+1;	 
		Capacity = (Capacity)*1024;//�õ�������
		Capacity*=512;//�õ��ֽ���			   
	}
	else
	{		    
		i = csd[6]&0x03;
		i<<=8;
		i += csd[7];
		i<<=2;
		i += ((csd[8]&0xc0)>>6);
		//C_SIZE_MULT
		r1 = csd[9]&0x03;
		r1<<=1;
		r1 += ((csd[10]&0x80)>>7);	 
		r1+=2;//BLOCKNR
		temp = 1;
		while(r1)
		{
			temp*=2;
			r1--;
		}
		Capacity = ((u32)(i+1))*((u32)temp);	 
		// READ_BL_LEN
		i = csd[5]&0x0f;
		//BLOCK_LEN
		temp = 1;
		while(i)
		{
			temp*=2;
			i--;
		}
		//The final result
		Capacity *= (u32)temp;//�ֽ�Ϊ��λ 	  
	}
	return (unsigned int)Capacity;
}
/*******************************************************************************
****��������:
****��������:��ȡTF��һ��block
****�汾:V1.0
****����:14-2-2014
****��ڲ���:sector������ַ *buffer���ݴ�ŵ�ַ
****���ڲ���:
****˵��:
********************************************************************************/
unsigned char TF_ReadSingleBlock(unsigned int sector, unsigned char *buffer)
{
	unsigned char  r1;          
	unsigned short i;
	//byte retry=0;
	
	r1 =TF_SendCommand(CMD17, sector<<9,0x95);//������ 	
	if(r1 != 0x00)return r1;
	
	Clr_TF_CS;
	
	//�����ݵĿ�ʼ
	while(SPI_FLASH_SendByte(0xff) != 0xfe);
	
	for(i=0; i<512; i++)//��512������
	{
		*buffer++ = SPI_FLASH_SendByte(0xff);
	}
	
	(void)SPI_FLASH_SendByte(0xff);//αcrc
	(void)SPI_FLASH_SendByte(0xff);  	
	Set_TF_CS;
	
	return 0;
}
/*******************************************************************************
****��������:
****��������:��ȡTF�����block
****�汾:V1.0
****����:14-2-2014
****��ڲ���:sector������ַ *buffer���ݴ�ŵ�ַ count������Ŀ
****���ڲ���:
****˵��:
********************************************************************************/
unsigned char TF_ReadMultiBlock(unsigned int sector, unsigned char *buffer, unsigned char count)
{
	unsigned char  r1;          
	unsigned short i;
	r1 =TF_SendCommand(CMD18, sector<<9,0x95);//�����Block���� 	
	
	if(r1 != 0x00)return r1;
		Clr_TF_CS;
		
	while(SPI_FLASH_SendByte(0xff) != 0xfe)
	  	;
	
	do
	{
		for(i=0; i<512; i++)//��512������
		{
			*buffer++ = SPI_FLASH_SendByte(0xff);
		}
		(void)SPI_FLASH_SendByte(0xff);//αcrc
		(void)SPI_FLASH_SendByte(0xff); 
	}while(--count);
	
	//ȫ��������ϣ�����ֹͣ����
	TF_SendCommand(CMD12, 0, 0);
	//�ͷ�����
	Set_TF_CS;
	(void)SPI_FLASH_SendByte(0xff); 
	
	if(count != 0)
	  	return count;   //���û�д��꣬����ʣ�����	 
	else 
	  	return 0;
}
/*******************************************************************************
****��������:
****��������:��ָ��λ�ö���ָ���ֽڵ�����
****�汾:V1.0
****����:14-2-2014
****��ڲ���:address������ַ *buf���ݴ�Ż��� offset������ƫ���� bytes��Ҫ�����ֽ���Ŀ
****���ڲ���:
****˵��:
********************************************************************************/
unsigned char TF_Read_Bytes(unsigned long address,unsigned char *buf,unsigned int offset,unsigned int bytes)
{
	unsigned char r1;u16 i=0;  
	r1=TF_SendCommand(CMD17, address<<9,0x95);//���Ͷ���������  
    
	if(r1)
	  	return r1;  //Ӧ����ȷ��ֱ�ӷ���
	
	Clr_TF_CS;//ѡ��TF��
	
	if(TF_GetResponse(0xFE))//�ȴ�TF������������ʼ����0xFE
	{
		Set_TF_CS; //�ر�TF��
		return 1;//��ȡʧ��
	}	 
	
	for(i=0;i<offset;i++)
	  	SPI_FLASH_SendByte(0xff);//����offsetλ 
	
	for(;i<offset+bytes;i++)
	  	*buf++=SPI_FLASH_SendByte(0xff);//��ȡ��������	
	
	for(;i<512;i++) 
	  	SPI_FLASH_SendByte(0xff); 	 //����ʣ���ֽ�
	
	SPI_FLASH_SendByte(0xff);//����αCRC��
	SPI_FLASH_SendByte(0xff);  
	
	Set_TF_CS;//�ر�SD��
	
	return 0;
}
/*******************************************************************************
****��������:
****��������:д1��block������
****�汾:V1.0
****����:14-2-2014
****��ڲ���:sector������ַ*data ���ݻ���
****���ڲ���:
****˵��:
********************************************************************************/
unsigned char TF_WriteSingleBlock(unsigned int sector, unsigned char * buffer)
{
	unsigned char r1;
	unsigned short i;
	//byte retry=0;
	if(sector<1) 
	  	return 0xff;         //Ϊ�˱���TF������������������
	
	r1 =TF_SendCommand(CMD24, sector<<9,0x95);  //д����
	
	if(r1 != 0x00) 
	  	return r1;
	
	Clr_TF_CS;
	
	(void)SPI_FLASH_SendByte(0xff);
	(void)SPI_FLASH_SendByte(0xff);
	(void)SPI_FLASH_SendByte(0xff); 
	(void)SPI_FLASH_SendByte(0xfe);        //����ʼ��
	
	for(i=0; i<512; i++)              //��512�ֽ�����
	{
		(void)SPI_FLASH_SendByte(*buffer++);
	}
	
	(void)SPI_FLASH_SendByte(0xff);
	(void)SPI_FLASH_SendByte(0xff);
	
	r1 = SPI_FLASH_SendByte(0xff);
	
	if((r1&0x1f) != 0x05)             //�ȴ��Ƿ�ɹ�
	{
		Set_TF_CS;
		return r1;
	}
	//�ȴ�������
	while(!SPI_FLASH_SendByte(0xff));      
	
	Set_TF_CS;
	
	return 0;     
}
/*******************************************************************************
****��������:
****��������:д���block������
****�汾:V1.0
****����:14-2-2014
****��ڲ���:sector������ַ*data ���ݻ��� count ������Ŀ
****���ڲ���:
****˵��:
********************************************************************************/
unsigned char TF_WriteMultiBlock(unsigned int sector, const unsigned char *data, unsigned char count)
{
	unsigned char r1;
	unsigned short i;	 	
	if(sector<1) 
	  	return 0xff;         /*Ϊ�˱���TF������������������*/
	
	r1 =TF_SendCommand(CMD25, sector<<9,0x95);  /*�����д��ָ������*/
	
	if(r1 != 0x00)
	  	return r1;  /*Ӧ����ȷ��ֱ�ӷ���	*/ 
	
	Clr_TF_CS;	/*��ʼ׼�����ݴ��� */
	
	(void)SPI_FLASH_SendByte(0xff);/*�ȷ�3�������ݣ��ȴ�TF��׼����*/
	(void)SPI_FLASH_SendByte(0xff);   
	
	/*������N��sectorд���ѭ������*/
	do
	{
		/*����ʼ����0xFC �����Ƕ��д��*/
		(void)SPI_FLASH_SendByte(0xFC);	  
		
		/*��һ��sector������*/
		for(i=0;i<512;i++)
		{
			(void)SPI_FLASH_SendByte(*data++);
		}
		
		//��2��Byte��dummy CRC
		(void)SPI_FLASH_SendByte(0xff);
		(void)SPI_FLASH_SendByte(0xff);
	
		//�ȴ�SD��Ӧ��
		r1 = SPI_FLASH_SendByte(0xff);
		if((r1&0x1F)!=0x05)
		{
			Set_TF_CS;    /*���Ӧ��Ϊ��������������ֱ���˳�*/
			return r1;
		}		   
	}while(--count);//��sector���ݴ������  
	
	/*��������������0xFD*/
	r1 = SPI_FLASH_SendByte(0xFD);
	if(r1==0x00)
	{
		count =  0xfe;
	}		   
	
	Set_TF_CS; 
	return count;   //����countֵ�����д����count=0������count=1
}
/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/