#ifndef MEMORYDATAITEM_H
#define MEMORYDATAITEM_H

#include "../../app_settings.h"
#ifdef QT_IN_USE
#include <QDebug>
#endif
#include <stdio.h>
#include "../../engine/command_manager/StringConvertor.h"


/*****************************************************************************************/
/***********                                                                   ***********/
/*********** Memory data item represents the value "0123456789ABCDEF6396AC6435BA5F90" ****/
/*********** as QStringList theBytes;                                          ***********/
/***********     theBytes[0] = "01.23.45.67";                                  ***********/
/***********     theBytes[1] = "89.AB.CD.EF";                                  ***********/
/***********     theBytes[2] = "63.96.AC.64";                                  ***********/
/***********     theBytes[3] = "35.BA.5F.90";                                  ***********/
/***********                                                                   ***********/
/***********    and ASCII string                                               ***********/
/***********                                                                   ***********/
/***********                                                                   ***********/
/***********                                                                   ***********/
/***********                                                                   ***********/
/*****************************************************************************************/
/*****************************************************************************************/

class MemoryDataItem: public QObject{
    Q_OBJECT
    Q_PROPERTY(QString Address READ Address WRITE setAddress NOTIFY AddressChanged)
    Q_PROPERTY(QString Byte0 READ Byte0 WRITE setByte0 NOTIFY TheBytesChanged)
    Q_PROPERTY(QString Byte4 READ Byte4 WRITE setByte4 NOTIFY TheBytesChanged)
    Q_PROPERTY(QString Byte8 READ Byte8 WRITE setByte8 NOTIFY TheBytesChanged)
    Q_PROPERTY(QString ByteC READ ByteC WRITE setByteC NOTIFY TheBytesChanged)
    Q_PROPERTY(QString Ascii READ Ascii WRITE setAscii NOTIFY AsciiChanged)

public:

    explicit MemoryDataItem(QObject *parent = nullptr, QString addr = "", QString value = "") : QObject(parent), m_Address(addr){
        m_Address = "0x" + addr;
        /* value is supposed to be "3145" equal to "1E" in Ascii */
        /* value is supposed to be 32 length, representing 16 bytes of actual data */
        for(size_t i = 0; i < 32; i+=8){
            m_TheBytes.append(value.mid(i, 8).insert(2, ".").insert(5, ".").insert(8, "."));
        }

        // Convert each pair of symbols into an Ascii symbol

        for(int i=0; i<value.length(); i+=2) {
            QString hex = value.mid(i, 2);
            bool ok;
            int decimal = hex.toInt(&ok, 16);
            if(ok) {
                QChar asciiChar(decimal);
                m_Ascii += asciiChar;
            }
        }

        for(int i = 0; i < value.length(); i += 2) {
            QString byteStr = value.mid(i, 2);
            bool ok;
            uint8_t byte = byteStr.toUInt(&ok, 16);
            if(ok) {
                m_raw_data.append(byte);
            } else {
                qDebug() << "error";
            }
        }
        m_raw_data.resize(16);
    };

    ~MemoryDataItem( ){}

    static bool validate4bytes(const QString &bytes){
        static const QRegularExpression regex = QRegularExpression("^(?:[0-9A-F]{2}\\.?){4}$");
        QRegularExpressionMatch match = regex.match(bytes);
        if (match.hasMatch()) return true;
        else return false;
    }

    /*** setters and getters ***/

    const QString &Address() const;
    void setAddress(const QString &newAddress);

    const QString &Byte0() const;
    void setByte0(const QString &newTheBytes);
    const QString &Byte4() const;
    void setByte4(const QString &newTheBytes);
    const QString &Byte8() const;
    void setByte8(const QString &newTheBytes);
    const QString &ByteC() const;
    void setByteC(const QString &newTheBytes);

    void recalculateRawData();
    void recalculateAScii();
    const QString &Ascii() const;
    void setAscii(const QString &newAscii);

    Q_INVOKABLE QString print() const;

    const QByteArray &raw_data() const;
    void setRaw_data(const QByteArray &newRaw_data);

signals:
    void AddressChanged();
    void TheBytesChanged();
    void AsciiChanged();

private:
    QString m_Address;

    QStringList m_TheBytes;
    QByteArray m_raw_data;
    QString m_Ascii;
};


#endif // MEMORYDATAITEM_H
