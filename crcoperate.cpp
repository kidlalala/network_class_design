#include "crcoperate.h"
#include<QApplication>
#include<iostream>

CRCoperate::CRCoperate()
{

}

CRCoperate::CRCoperate(QString sourcemac, QString targetmac,
                       QString data)
{
    this->SOURCEMAC = sourcemac;
    this->TARGETMAC = targetmac;
    this->LENGTH = QString::number(data.length()-1, 16);
    this->DATA = data;
    CRCString = "";
    FCS = "";
    POLYNOMIAL = "100000111";
}

void CRCoperate::SetCRCoperate(QString sourcemac, QString targetmac,
                               QString data)
{
    this->SOURCEMAC = FIXMAC(sourcemac);
    this->TARGETMAC = FIXMAC(targetmac);
    this->LENGTH = QString::number(data.length() - 1, 16);
    this->DATA = data;
    CRCString = "";
    FCS = "";
}

void CRCoperate::SetPolynomial(QString polynomial)
{
    this->POLYNOMIAL = polynomial;
}

QString CRCoperate::CHECK4DIGITS(QString BYTES)
{
    int len = BYTES.length();
    for(int i = 0; i < 4 - len; i++)
        BYTES.insert(0,"0");
    return BYTES;
}

QString CRCoperate::HEX2BIN(QString HEX)
{
    bool OK;
    QString Qtemp(""), Qresult("");
    for(int i = 0;i < HEX.length();i++)
    {
        Qtemp = QString::number(HEX.mid(i,1).toInt(&OK,16),2);
        Qresult += CHECK4DIGITS(Qtemp);
    }
    return Qresult;
}

QString CRCoperate::FIXMAC(QString MAC)
{
    return MAC.replace( QString(":"), QString("") );
}

void CRCoperate::MAC2BIN()
{
    SOURCEMAC = FIXMAC(SOURCEMAC);
    TARGETMAC = FIXMAC(TARGETMAC);
    CRCString += HEX2BIN(SOURCEMAC);
    CRCString += HEX2BIN(TARGETMAC);
}

bool CRCoperate::CHECKMAC(QString MAC)
{
    QString pattern("([a-f0-9]{2}:){5}[a-f0-9]{2}");
    QRegExp regular(pattern);

    bool match = regular.exactMatch(MAC);
    return match;
}

bool CRCoperate::CHECKDATA(QString DATA)
{
    QString pattern("[a-f0-9]{1,}");
    QRegExp regular(pattern);

    bool match = regular.exactMatch(DATA);
    return match;
}

void CRCoperate::LEN2BIN()
{
    CRCString += HEX2BIN(LENGTH);
}

void CRCoperate::FILLDATA()
{
    DATA = HEX2BIN(DATA);
    int D_len = DATA.length();
    if(D_len < 46)
    {
        for(int i = 0; i < 46-D_len; i++)
            DATA.insert(0,"0");
    }
}

QString CRCoperate::GETFCS()
{
    MAC2BIN();
    LEN2BIN();
    CRCString += HEX2BIN(DATA);

    int len = POLYNOMIAL.length();

    QString Qtemp = CRCString;
    for(int i = 0; i < len - 1; i++)
        Qtemp += "0";
    int crc_len = Qtemp.length();
    QByteArray TempArray = Qtemp.toLatin1();
    char *Arr_crc = TempArray.data();
    TempArray = POLYNOMIAL.toLatin1();
    char *Arr_poly = TempArray.data();

    for(int i = 0; i + len < crc_len; i++)
    {
        if(Arr_crc[i] != '0')
        {
            for(int j = 0; j < len; j++)
            {
                Arr_crc[i+j] = ((Arr_crc[i+j] - '0')^(Arr_poly[j] - '0')) + '0';
            }
        }
    }

    Qtemp = QString(QLatin1String(Arr_crc));

    Qtemp = Qtemp.right(len - 1);
    CRCString += Qtemp;

    FILLDATA();

    return Qtemp;
}
//30:15:54:34:55:65
//75:84:06:47:ab:98
