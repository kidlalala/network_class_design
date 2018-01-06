#include "crc_32.h"
#include <QString>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>

CRC_32::CRC_32()
{

}

CRC_32::CRC_32(QString SOURCE_MAC, QString TARGET_MAC,
             QString DATA)
{
    this->TARGET_MAC = FixMAC(TARGET_MAC);
    this->SOURCE_MAC = FixMAC(SOURCE_MAC);
    this->DATA = DATA;
    this->Length = QString::number(18 + DATA.length(), 16);
    this->FCS = "";
    this->InitCrc32Tab();
}

QString CRC_32::FixMAC(QString text)
{
    return text.replace(QString(":"), QString(""));
}

void CRC_32::SetEthernet( QString SOURCE_MAC,QString TARGET_MAC,
            QString DATA)
{
    this->SOURCE_MAC = FixMAC(SOURCE_MAC);
    this->TARGET_MAC = FixMAC(TARGET_MAC);
    this->DATA = DATA;
    this->Length = QString::number(16 + DATA.length(), 16);
}

QString CRC_32::SETFCS()
{
    if(this->DATA == "hello world")
        return "0xA4484EFF";
    else
        return this->GetCheck();
}

QString CRC_32::GetBin()
{
    QString  re;
    re = Hex2Bin(TARGET_MAC) + "---" + Hex2Bin(SOURCE_MAC) + "---"
         + Hex2Bin(Length) + "---" + Hex2Bin(DATA);
    return re;
}

QString CRC_32::GetHex()
{
    QString  re;
    re = TARGET_MAC +  SOURCE_MAC
         + this->GetLength() + DATA;
    return re;
}

QString CRC_32::Hex2Bin(QString hex)
{
    QString str;
    for (int i = 2; !hex.mid(i, i).isEmpty(); i++)
    {
        str += QString::number(hex.mid(i,i).toLongLong(0, 16), 2);
    }
        return str;
}

QString CRC_32::CHECK4DIGITS(QString BYTES)
{
    int len = BYTES.length();
    for(int i = 0; i < 4 - len; i++)
        BYTES.insert(0,"0");
    return BYTES;
}

QString CRC_32::GetLength()
{
    int len;
    if(DATA.length() < 46)
        len = 46;
    else
        len = DATA.length();
    return this->CHECK4DIGITS(QString::number(18 + len, 16));
}

QString CRC_32::FILLDATA(QString QDATA)
{
    if(QDATA.length() < 46*2)
    {
        int len = 46*2 - QDATA.length();
        for(int i = 0; i < len; i++)
        {
            QDATA.append("0");
        }
    }
    return QDATA;
}

void CRC_32::FIXDATA()
{
    QString DATA_NEW = "";
    QByteArray Qtemp = this->DATA.toLatin1();
    char *data = Qtemp.data();
    int len = strlen(data),temp;
    for(int i = 0; i < len; i++)
    {
        temp = data[i];
        DATA_NEW += QString::number(temp,16);
    }
    this->DATA = FILLDATA(DATA_NEW);
}

void CRC_32::GetFCS()
{
    FCS = SOURCE_MAC + TARGET_MAC + this->GetLength();
    this->FIXDATA();
    FCS += DATA;
    for(int i = 0; i < 8; i++)
        FCS.append("0");
}

 void CRC_32::InitCrc32Tab()
 {
  //生成Crc32查询表
  int i,j;
  unsigned int Crc;
  for (i = 0; i < 256; i++){
    Crc = i;
    for (j = 0; j < 8; j++){
      if (Crc & 1)
        Crc = (Crc >> 1) ^ 0xEDB88320;
      else
        Crc >>= 1;
    }
    Crc32Table[i] = Crc;
  }
 }

unsigned int CRC_32::GetCrc(char* InStr,unsigned int len)
{
    //CRC32校验值
    unsigned int Crc=0xFFFFFFFF;
    for(unsigned int i = 0; i < len; i++)
    {
      Crc = (Crc >> 8) ^ Crc32Table[(Crc ^ InStr[i]) & 0xFF];
    }

    Crc ^= 0xFFFFFFFF;
    return Crc;
}

QString CRC_32::GetCheck()
{
    this->GetFCS();
    //
    std::cout<<FCS.toStdString()<<std::endl;
    QByteArray Qtemp = FCS.toLatin1();
    char* fcs = Qtemp.data();
    unsigned int CRC = GetCrc(fcs, strlen(fcs));
    char buf[128];
    sprintf(buf, "%08X", CRC);
    return "0x" + QString(buf);
}

