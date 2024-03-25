#include "ParseBuffer.h"

//============================== ST CAN ==============================
void ParseBuffer::append(const QByteArray &data){
    if((data.size() + m_parse_buffer.size()) <= max_parse_buffer_size) m_parse_buffer.append(data);
}
//============================== FD CAN ==============================
void FDCAN_ParseBuffer::append(const QByteArray &data){
    if(data.size() < max_parse_buffer_size) m_parse_buffer.append(data);
}



//============================== ST CAN ==============================
 size_t ParseBuffer::size() const{
    return m_parse_buffer.size();
}
 //============================== FD CAN ==============================
 size_t FDCAN_ParseBuffer::size() const{
    return m_parse_buffer.size();
}



//============================== ST CAN ==============================
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
 //============================== FD CAN ==============================
int FDCAN_ParseBuffer::findEntryPoint() const{
    const size_t buf_size = size();
    if(buf_size < chunkSize)return -1;

    int end_pos = buf_size >= (chunkSize + 64) ? (chunkSize + 64) : buf_size;
     for(size_t i = 0; i < end_pos; i++){
         if(m_parse_buffer.at(i) == start_symbol) {
             if(i + chunkSize < buf_size){
                 if(validateCanMsg(m_parse_buffer.mid(i, chunkSize)))
                 return i;
             }
         }
     }
     return -1;
 }



//============================== ST CAN ==============================
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
//============================== FD CAN ==============================
bool FDCAN_ParseBuffer::validateCanMsg(const QByteArray &_data){
    //if(_data.size() != chunkSize) return false;
    if((_data.at(1)!= 0x00) & (_data.at(1)!= 0x01)) return false;   // CAN1/CAN2
    if((_data.at(14)!= 0x00) & (_data.at(15)!= 0x00)) return false;   // rxts

    return true;
}
//============================== ST CAN ==============================
QList<QByteArray>  ParseBuffer::extractAllParseableLines(){
    int _pos = findEntryPoint();
    const int _size = size();
    QList<QByteArray> theList;
    if((_pos == -1) | ((_size - _pos) < chunkSize))return theList;

    while(_pos < _size){
        if(_pos + chunkSize <= _size){
            const QByteArray _mid = m_parse_buffer.mid(_pos, chunkSize);
            if(_mid.size() == chunkSize) {
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
//============================== FD CAN ==============================
QList<QByteArray>  FDCAN_ParseBuffer::extractAllParseableLines(){
    int _pos = findEntryPoint();
    const size_t _size = size();
    QList<QByteArray> theList;
    if(_pos == -1)return theList;

    while(_pos < _size){
        uint8_t data_length = 0;
        if(_pos + chunkSize <= _size){
            QByteArray _line = m_parse_buffer.mid(_pos, chunkSize);
            data_length = calculate_fdmsg_data_length(_line);

            if(data_length == 0){
                theList << (_line);
            }
            else{
                if(_pos + (chunkSize + data_length) <= _size){
                    const QByteArray _data_line = m_parse_buffer.mid((_pos + chunkSize), data_length);
                    _line.append(_data_line);
                    theList << (_line);
                }
            }
        }
        if(_pos + (chunkSize + data_length) <= _size) _pos += (chunkSize + data_length);
        else break;
    }

    if(_pos < _size){
        const int residue_size = _size - _pos;
        if(residue_size != max_chunkSize){
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
