#ifndef CRC_32_H
#define CRC_32_H
#include <QString>
class CRC_32
{
private:
    QString TARGET_MAC;
    QString SOURCE_MAC;
    QString Length;
    QString DATA;
    QString FCS;
    unsigned int Crc32Table[256];

public:
    CRC_32();
    CRC_32(QString TARGET_MAC, QString SOURCE_MAC,
                QString DATA);

    void SetEthernet(QString TARGET_MAC, QString SOURCE_MAC,
                 QString DATA);
    void InitCrc32Tab();
    QString CHECK4DIGITS(QString BYTES);
    QString GetLength();
    QString GetBin();
    QString GetHex();
    void FIXDATA();
    void GetFCS();
    QString FILLDATA(QString QDATA);
    QString Hex2Bin(QString hex);
    QString GetCheck();
    QString FixMAC(QString);
    QString SETFCS();
    unsigned int GetCrc(char* InStr,unsigned int len);
};

#endif // CRC_32_H
