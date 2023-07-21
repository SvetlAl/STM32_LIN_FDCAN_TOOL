#include "MemoryDataItem.h"


const QString &MemoryDataItem::Address() const
{
    return m_Address;
}

void MemoryDataItem::setAddress(const QString &newAddress)
{
    if (m_Address == newAddress)
        return;
    m_Address = newAddress;
    emit AddressChanged();
}



const QString &MemoryDataItem::Ascii() const
{
    return m_Ascii;
}

void MemoryDataItem::setAscii(const QString &newAscii)
{
    if (m_Ascii == newAscii)
        return;
    m_Ascii = newAscii;
    emit AsciiChanged();
}
/*
 * const QStringList &MemoryDataItem::TheBytes() const
{
    return m_TheBytes;
}

void MemoryDataItem::setTheBytes(const QStringList &newTheBytes)
{
    if (m_TheBytes == newTheBytes)
        return;
    m_TheBytes = newTheBytes;
    emit TheBytesChanged();
}
*/
const QString &MemoryDataItem::Byte0() const{
    return m_TheBytes[0];
}
void MemoryDataItem::setByte0(const QString &newTheBytes){
    if(!validate4bytes(newTheBytes)) return;
    if (m_TheBytes[0] == newTheBytes)
        return;
    m_TheBytes[0] = newTheBytes;
    recalculateAScii();
    emit TheBytesChanged();
}

const QString &MemoryDataItem::Byte4() const{
    return m_TheBytes[1];
}
void MemoryDataItem::setByte4(const QString &newTheBytes){
    if(!validate4bytes(newTheBytes)) return;
    if (m_TheBytes[1] == newTheBytes)
        return;
    m_TheBytes[1] = newTheBytes;
    recalculateAScii();
    emit TheBytesChanged();
}

const QString &MemoryDataItem::Byte8() const{
    return m_TheBytes[2];
}
void MemoryDataItem::setByte8(const QString &newTheBytes){
    if(!validate4bytes(newTheBytes)) return;
    if (m_TheBytes[2] == newTheBytes)
        return;
    m_TheBytes[2] = newTheBytes;
    recalculateAScii();
    emit TheBytesChanged();
}

const QString &MemoryDataItem::ByteC() const{
    return m_TheBytes[3];
}
void MemoryDataItem::setByteC(const QString &newTheBytes){
    if(!validate4bytes(newTheBytes)) return;
    if (m_TheBytes[3] == newTheBytes)
        return;
    m_TheBytes[3] = newTheBytes;
    recalculateAScii();
    emit TheBytesChanged();
}

void MemoryDataItem::recalculateAScii(){
    QString initialValue;
    for(size_t i = 0; i < 4; i++){
        initialValue.append(m_TheBytes[i].replace(QString("."), QString("")));
    }
    QString result;
    for(int i=0; i < initialValue.length(); i+=2) {
        QString hex = initialValue.mid(i, 2);
        bool ok;
        int decimal = hex.toInt(&ok, 16);
        if(ok) {
            QChar asciiChar(decimal);
            result += asciiChar;
        }
    }
    recalculateRawData();
    setAscii(result);
}

void MemoryDataItem::recalculateRawData(){
    QString initialValue;
    for(size_t i = 0; i < 4; i++){
        initialValue.append(m_TheBytes[i].replace(QString("."), QString("")));
    }
    m_raw_data.clear();
    m_raw_data.resize(16);
    for(size_t i = 0; i < 16; i++){
        m_raw_data[i] = (StringConvertor::hexascii_to_halfbyte(initialValue.at(i).toLatin1()) >> 4 );
        m_raw_data[i] |= StringConvertor::hexascii_to_halfbyte(initialValue.at(i+1).toLatin1()) ;
    }
}





QString MemoryDataItem::print() const{
   QString response = Address();
   response.append(": ");
   for(size_t i = 0; i < 4; i++){
       QString tmpByte = m_TheBytes[i];
       response.append(tmpByte.replace(QString("."), QString("")));
   }
   response.append("\n");
   return response;
}

const QByteArray &MemoryDataItem::raw_data() const{
    return m_raw_data;
}

void MemoryDataItem::setRaw_data(const QByteArray &newRaw_data){
    m_raw_data = newRaw_data;
}
