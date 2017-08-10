#ifndef CRCOPERATE_H
#define CRCOPERATE_H

#include<QString>

class CRCoperate
{
private:
    QString SOURCEMAC;
    QString TARGETMAC;
    QString LENGTH;
    QString DATA;
    QString CRCString;
    QString FCS;
    QString POLYNOMIAL;
public:
    CRCoperate();
    CRCoperate(QString sourcemac, QString targetmac,
               QString data);

    void SetCRCoperate(QString sourcemac, QString targetmac,
                       QString data);
    void SetPolynomial(QString polynomial);

    QString CHECK4DIGITS(QString BYTES);
    QString HEX2BIN(QString HEX);
    QString FIXMAC(QString MAC);

    bool CHECKMAC(QString MAC);
    bool CHECKDATA(QString DATA);

    void MAC2BIN();
    void LEN2BIN();
    void FILLDATA();

    QString GETFCS();
};

#endif // CRCOPERATE_H
