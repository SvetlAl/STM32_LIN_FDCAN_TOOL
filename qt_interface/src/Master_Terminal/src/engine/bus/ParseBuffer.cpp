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
/*
typedef struct can_message{
    can_id id;
    uint16_t ide;
    uint16_t dlc;
    uint8_t data[8];
} can_message;

typedef struct can_message_info{
    uint8_t start_char; // '@'
    uint8_t can_number;
    uint16_t msec;
    uint32_t seconds;
    32 id;
    uint16_t ide; 12 13
    uint16_t dlc;
    uint8_t data[8];

} can_message_info;

typedef union can_message_info_raw{
    can_message_info info;
    uint8_t raw_msg_data[24];
}can_message_info_raw;

*/

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
/*




bool ParseBuffer::isReady(){
    if(m_parse_buffer.size() < chunkSize) return false;
    else return true;
}

QByteArray ParseBuffer::extractAll(){
    parseBufferMutex.tryLock(20);
    QByteArray extracted = m_parse_buffer;
    m_parse_buffer.clear();
    m_parse_buffer.resize(0);
    parseBufferMutex.unlock();
    return extracted;
}

void ParseBuffer::prepend(const QByteArray& data){
    parseBufferMutex.tryLock(20);
    m_parse_buffer.prepend(data);
    parseBufferMutex.unlock();
}

*/
