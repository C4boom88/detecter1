#include "W25Q128.h"
#include "quadspi.h"
#include "W25Q128_reg.h"
/**
	4KbytesΪһ��Sector
	16������Ϊ1��Block
	W25Q128����Ϊ16M�ֽ�,����256��Block,4096��Sector
*/




/**
 * @brief	��ʼ��SPI FLASH��IO��
 *
 * @param   void
 *
 * @return  void
 */
void W25Q128_Init(void)
{
    MX_QUADSPI_Init();					//��ʼ��QSPI
 
}


/**
 * @brief	��ȡW25Q128��״̬�Ĵ�����W25Q128һ����3��״̬�Ĵ���
 * 			״̬�Ĵ���1��
 * 			BIT7  6   5   4   3   2   1   0
 * 			SPR   RV  TB BP2 BP1 BP0 WEL BUSY
 * 			SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
 * 			TB,BP2,BP1,BP0:FLASH����д��������
 * 			WEL:дʹ������
 * 			BUSY:æ���λ(1,æ;0,����)
 * 			Ĭ��:0x00
 * 			״̬�Ĵ���2��
 * 			BIT7  6   5   4   3   2   1   0
 * 			SUS   CMP LB3 LB2 LB1 (R) QE  SRP1
 * 			״̬�Ĵ���3��
 * 			BIT7      6    5    4   3   2   1   0
 * 			HOLD/RST  DRV1 DRV0 (R) (R) WPS ADP ADS
 *
 * @param   regno	״̬�Ĵ����ţ���:1~3
 *
 * @return  uint8_t		״̬�Ĵ���ֵ
 */
uint8_t W25Q128_ReadSR(uint8_t regno)
{
    uint8_t byte = 0, command = 0;

    switch(regno)
    {
        case 1:
            command = W25X_ReadStatusReg1;  //��״̬�Ĵ���1ָ��
            break;

        case 2:
            command = W25X_ReadStatusReg2;  //��״̬�Ĵ���2ָ��
            break;

        case 3:
            command = W25X_ReadStatusReg3;  //��״̬�Ĵ���3ָ��
            break;

        default:
            command = W25X_ReadStatusReg1;
            break;
    }

    QSPI_Send_CMD(command, 0, 0, QSPI_INSTRUCTION_1_LINE, QSPI_ADDRESS_NONE, QSPI_ADDRESS_8_BITS, QSPI_DATA_1_LINE);
    QSPI_Receive(&byte, 1);
    return byte;
}

/**
 * @brief	дW25Q128״̬�Ĵ���
 *
 * @param   void
 *
 * @return  void
 */
void W25Q128_Write_SR(uint8_t regno, uint8_t sr)
{
    uint8_t command = 0;

    switch(regno)
    {
        case 1:
            command = W25X_WriteStatusReg1;  //д״̬�Ĵ���1ָ��
            break;

        case 2:
            command = W25X_WriteStatusReg2;  //д״̬�Ĵ���2ָ��
            break;

        case 3:
            command = W25X_WriteStatusReg3;  //д״̬�Ĵ���3ָ��
            break;

        default:
            command = W25X_WriteStatusReg1;
            break;
    }

    QSPI_Send_CMD(command, 0, 0, QSPI_INSTRUCTION_1_LINE, QSPI_ADDRESS_NONE, QSPI_ADDRESS_8_BITS, QSPI_DATA_1_LINE);
    QSPI_Transmit(&sr, 1);
}


/**
 * @brief	W25Q128дʹ��,��S1�Ĵ�����WEL��λ
 *
 * @param   void
 *
 * @return  void
 */
void W25Q128_Write_Enable(void)
{
    QSPI_Send_CMD(W25X_WriteEnable, 0, 0, QSPI_INSTRUCTION_1_LINE, QSPI_ADDRESS_NONE, QSPI_ADDRESS_8_BITS, QSPI_DATA_NONE);
}

/**
 * @brief	W25Q128д��ֹ,��WEL����
 *
 * @param   void
 *
 * @return  void
 */
void W25Q128_Write_Disable(void)
{
    QSPI_Send_CMD(W25X_WriteDisable, 0, 0, QSPI_INSTRUCTION_1_LINE, QSPI_ADDRESS_NONE, QSPI_ADDRESS_8_BITS, QSPI_DATA_NONE);
}

/**
 * @brief	��ȡW25Q128оƬID
 *
 * @param   void
 *
 * @return  uint8_t	����ֵ����
 * 				0XEF13,��ʾоƬ�ͺ�ΪW25Q80
 * 				0XEF14,��ʾоƬ�ͺ�ΪW25Q16
 * 				0XEF15,��ʾоƬ�ͺ�ΪW25Q32
 * 				0XEF16,��ʾоƬ�ͺ�ΪW25Q64
 * 				0XEF17,��ʾоƬ�ͺ�ΪW25Q128
 * 				0XEF18,��ʾоƬ�ͺ�ΪW25Q256
 */
uint16_t W25Q128_ReadID(void)
{
    uint8_t temp[2];
    uint16_t deviceid;
    QSPI_Send_CMD(W25X_ManufactDeviceID, 0, 0, QSPI_INSTRUCTION_1_LINE, QSPI_ADDRESS_1_LINE, QSPI_ADDRESS_24_BITS, QSPI_DATA_1_LINE);
    QSPI_Receive(temp, 2);
    deviceid = (temp[0] << 8) | temp[1];
    return deviceid;
}




/**
 * @brief	��ȡSPI FLASH����
 *
 * @param   pBuffer			���ݴ洢��
 * @param   ReadAddr		��ʼ��ȡ�ĵ�ַ(���32bit)
 * @param   NumByteToRead	Ҫ��ȡ���ֽ���(���65535)
 *
 * @return  void
 */
void W25Q128_Read(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    QSPI_Send_CMD(W25X_FastReadData, ReadAddr, 8, QSPI_INSTRUCTION_1_LINE, QSPI_ADDRESS_1_LINE, QSPI_ADDRESS_24_BITS, QSPI_DATA_1_LINE);
    QSPI_Receive(pBuffer, NumByteToRead);
}


/**
 * @brief	��ָ����ַ��ʼд�����256�ֽڵ�����
 *
 * @param   pBuffer			���ݴ洢��
 * @param   WriteAddr		��ʼд��ĵ�ַ(���32bit)
 * @param   NumByteToWrite	Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!
 *
 * @return  void
 */
void W25Q128_Write_Page(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    W25Q128_Write_Enable();					//дʹ��
    QSPI_Send_CMD(W25X_PageProgram, WriteAddr, 0, QSPI_INSTRUCTION_1_LINE, QSPI_ADDRESS_1_LINE, QSPI_ADDRESS_24_BITS, QSPI_DATA_1_LINE);
    QSPI_Transmit(pBuffer, NumByteToWrite);
    W25Q128_Wait_Busy();					   //�ȴ�д�����
}

/**
 * @brief	�޼���дSPI FLASH
 * 			����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
 * 			�����Զ���ҳ����
 * 			��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
 *
 * @param   pBuffer			���ݴ洢��
 * @param   WriteAddr		��ʼд��ĵ�ַ(���32bit)
 * @param   NumByteToWrite	Ҫд����ֽ���(���65535)
 *
 * @return  void
 */
void W25Q128_Write_NoCheck(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint16_t pageremain;
    pageremain = 256 - WriteAddr % 256; //��ҳʣ����ֽ���

    if(NumByteToWrite <= pageremain)pageremain = NumByteToWrite; //������256���ֽ�

    while(1)
    {
        W25Q128_Write_Page(pBuffer, WriteAddr, pageremain);

        if(NumByteToWrite == pageremain)break; //д�������

        else //NumByteToWrite>pageremain
        {
            pBuffer += pageremain;
            WriteAddr += pageremain;

            NumByteToWrite -= pageremain;			 //��ȥ�Ѿ�д���˵��ֽ���

            if(NumByteToWrite > 256)pageremain = 256; //һ�ο���д��256���ֽ�

            else pageremain = NumByteToWrite; 	 //����256���ֽ���
        }
    }
}


/**
 * @brief	дSPI FLASH
 * 			��ָ����ַ��ʼд��ָ�����ȵ�����
 * 			�ú�������������!
 *
 * @param   pBuffer			���ݴ洢��
 * @param   WriteAddr		��ʼд��ĵ�ַ(���32bit)
 * @param   NumByteToWrite	Ҫд����ֽ���(���65535)
 *
 * @return  void
 */
uint8_t W25Q128_BUFFER[4096];
void W25Q128_Write(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint32_t secpos;
    uint16_t secoff;
    uint16_t secremain;
    uint16_t i;
    uint8_t * W25Q128_BUF;
    W25Q128_BUF = W25Q128_BUFFER;
    secpos = WriteAddr / 4096; //������ַ
    secoff = WriteAddr % 4096; //�������ڵ�ƫ��
    secremain = 4096 - secoff; //����ʣ��ռ��С

    //printf("ad:%X,nb:%X\r\n",WriteAddr,NumByteToWrite);//������
    if(NumByteToWrite <= secremain)secremain = NumByteToWrite; //������4096���ֽ�

    while(1)
    {
        W25Q128_Read(W25Q128_BUF, secpos * 4096, 4096); //������������������

        for(i = 0; i < secremain; i++) //У������
        {
            if(W25Q128_BUF[secoff + i] != 0XFF)break; //��Ҫ����
        }

        if(i < secremain) //��Ҫ����
        {
            W25Q128_Erase_Sector(secpos);//�����������

            for(i = 0; i < secremain; i++)	 //����
            {
                W25Q128_BUF[i + secoff] = pBuffer[i];
            }

            W25Q128_Write_NoCheck(W25Q128_BUF, secpos * 4096, 4096); //д����������

        }

        else W25Q128_Write_NoCheck(pBuffer, WriteAddr, secremain); //д�Ѿ������˵�,ֱ��д������ʣ������.

        if(NumByteToWrite == secremain)break; //д�������

        else//д��δ����
        {
            secpos++;//������ַ��1
            secoff = 0; //ƫ��λ��Ϊ0

            pBuffer += secremain; //ָ��ƫ��
            WriteAddr += secremain; //д��ַƫ��
            NumByteToWrite -= secremain;				//�ֽ����ݼ�

            if(NumByteToWrite > 4096)secremain = 4096;	//��һ����������д����

            else secremain = NumByteToWrite;			//��һ����������д����
        }
    };
}

/**
 * @brief	��������оƬ,�ȴ�ʱ�䳬��...
 *
 * @param   void
 *
 * @return  void
 */
void W25Q128_Erase_Chip(void)
{
    W25Q128_Write_Enable();					//SET WEL
    W25Q128_Wait_Busy();
    QSPI_Send_CMD(W25X_ChipErase, 0, 0, QSPI_INSTRUCTION_1_LINE, QSPI_ADDRESS_NONE, QSPI_ADDRESS_8_BITS, QSPI_DATA_NONE);
    W25Q128_Wait_Busy();						//�ȴ�оƬ��������
}

/**
 * @brief	����һ������������һ������������ʱ��:150ms
 *
 * @param   Dst_Addr	������ַ ����ʵ����������
 *
 * @return  void
 */
void W25Q128_Erase_Sector(uint32_t Dst_Addr)
{
    //printf("fe:%x\r\n",Dst_Addr);			//����flash�������,������
    Dst_Addr *= 4096;
    W25Q128_Write_Enable();                  //SET WEL
    W25Q128_Wait_Busy();
    QSPI_Send_CMD(W25X_SectorErase, Dst_Addr, 0, QSPI_INSTRUCTION_1_LINE, QSPI_ADDRESS_1_LINE, QSPI_ADDRESS_24_BITS, QSPI_DATA_NONE);
    W25Q128_Wait_Busy();   				    //�ȴ��������
}

/**
 * @brief	�ȴ�����
 *
 * @param   void
 *
 * @return  void
 */
void W25Q128_Wait_Busy(void)
{
    while((W25Q128_ReadSR(1) & 0x01) == 0x01); // �ȴ�BUSYλ���
}












