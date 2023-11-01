#include "ParseBuffer.h"


void ParseBuffer::append(const QByteArray &data){
    if((data.size() + m_parse_buffer.size()) <= max_parse_buffer_size) m_parse_buffer.append(data);
}

 size_t ParseBuffer::size() const{
    return m_parse_buffer.size();
}


int ParseBuffer::findEntryPoint() const{
    if(size() < chunkSize)return -1;
     for(size_t i = 0; i < chunkSize; i++){
         if(m_parse_buffer.at(i) == start_symbol) {
             if(i + chunkSize <= size()){
                 if(validateCanMsg(m_parse_buffer.mid(i, chunkSize)))
                 return i;
             }
         }
     }
     return -1;
 }

QList<QByteArray>  ParseBuffer::extractAllParseableLines(){
    int _pos = findEntryPoint();
    const int _size = size();
    QList<QByteArray> theList;
    if((_pos == -1) | ((_size - _pos) < chunkSize))return theList;

    while(_pos < _size){
        if(_pos + chunkSize <= _size){
            const QByteArray _mid = m_parse_buffer.mid(_pos, chunkSize);
            if(_mid.size() == chunkSize) {
                // TEST
          //      if(validateCanMsg(_mid))
                theList << _mid;
            }
        }
        if(_pos+chunkSize <= _size)_pos+=chunkSize;
        else break;
    }

    if(_pos < _size){
        const int residue_size = _size - _pos;
        if(residue_size!=chunkSize){
            const QByteArray residue = m_parse_buffer.mid(_pos, residue_size);
            m_parse_buffer.clear();
            m_parse_buffer.resize(0);
            m_parse_buffer.append(residue);
        }
        else{
            m_parse_buffer.clear();
            m_parse_buffer.resize(0);
        }
    }
    else {
        m_parse_buffer.clear();
        m_parse_buffer.resize(0);
    }
    return theList;
}

bool ParseBuffer::validateCanMsg(const QByteArray &_data){
    if(_data.size() != chunkSize) return false;
   // if(_data.size() != sizeof(can_message_info_raw)) return false;
    if((_data.at(1)!= 0x01) && (_data.at(1)!= 0x02)) return false;   // CAN1/CAN2
    if((_data.at(12)!= 0x01) && (_data.at(13)!= 0x00)) return false; // IDE
    if(_data.at(13)!= 0x00) return false;                          // IDE
    if(_data.at(14) > 0x08) return false;                          // DLC
    if(_data.at(15)!= 0x00) return false;                          // DLC
    return true;
}















void LinParseBuffer::append(const QByteArray &data){
    if((data.size() + m_parse_buffer.size()) <= max_parse_buffer_size) m_parse_buffer.append(data);
}

 size_t LinParseBuffer::size() const{
    return m_parse_buffer.size();
}


int LinParseBuffer::findEntryPoint() const{
    if(size() < chunkSize)return -1;
     for(size_t i = 0; i < chunkSize; i++){
         if(m_parse_buffer.at(i) == start_symbol) {
             if(i + chunkSize <= size()){
                 if(validateLinMsg(m_parse_buffer.mid(i, chunkSize)))
                 return i;
             }
         }
     }
     return -1;
 }

QList<QByteArray>  LinParseBuffer::extractAllParseableLines(){
    int _pos = findEntryPoint();
    const int _size = size();
    QList<QByteArray> theList;
    if((_pos == -1) | ((_size - _pos) < chunkSize))return theList;

    while(_pos < _size){
        if(_pos + chunkSize <= _size){
            const QByteArray _mid = m_parse_buffer.mid(_pos, chunkSize);
            if(_mid.size() == chunkSize) {
                // TEST
          //      if(validateCanMsg(_mid))
                theList << _mid;
            }
        }
        if(_pos+chunkSize <= _size)_pos+=chunkSize;
        else break;
    }

    if(_pos < _size){
        const int residue_size = _size - _pos;
        if(residue_size!=chunkSize){
            const QByteArray residue = m_parse_buffer.mid(_pos, residue_size);
            m_parse_buffer.clear();
            m_parse_buffer.resize(0);
            m_parse_buffer.append(residue);
        }
        else{
            m_parse_buffer.clear();
            m_parse_buffer.resize(0);
        }
    }
    else {
        m_parse_buffer.clear();
        m_parse_buffer.resize(0);
    }
    return theList;
}

// 0   1  2  3  4  5  6  7  8    9      10
// 40 00 B8 0E 14 0A 00 00 02   02      03    19 85 61 00 00 00 00 00 00
// @  un msec  sec         role length  id    data

bool LinParseBuffer::validateLinMsg(const QByteArray &_data){
    if(_data.size() != chunkSize) return false;
   // if(_data.size() != sizeof(can_message_info_raw)) return false;
   // if((_data.at(1)!= 0x01) && (_data.at(1)!= 0x02)) return false;   // CAN1/CAN2
   // if((_data.at(12)!= 0x01) && (_data.at(13)!= 0x00)) return false; // IDE
    if(_data.at(8) > 0x05) return false;                          // role
    if(_data.at(6) > 0x08) return false;                          // length
    //if(_data.at(15)!= 0x00) return false;                          // DLC
    return true;
}
