#include "Command.h"

bool Command::fill_string(const QByteArray& input_buf){
    uint32_t length = input_buf.length();
    if(length > ELP_QUADRO_BUF_SIZE) return false;
    for(size_t i = 0; i < length; i++){
        string_buffer.raw_data8[i] = input_buf.at(i);
    }
    string_siz = length;
    return true;
}

bool Command::append_uint_to_string(uint32_t value){
    uint32_t length = 8;
    size_t i = string_siz;

    if(!bigEndian) StringConvertor::uint32_to_str_le(value, &string_buffer.raw_data8[i]);
    else StringConvertor::uint32_to_str_be(value, &string_buffer.raw_data8[i]);
    string_siz += length;
    return true;
}
/*
bool Command::append_uint_to_string(uint16_t value){
    uint32_t length = 4;
    size_t i = string_siz;

    if(!bigEndian) StringConvertor::uint16_to_str_le(value, &string_buffer.raw_data8[i]);
    else StringConvertor::uint16_to_str_be(value, &string_buffer.raw_data8[i]);
    string_siz += length;
    return true;
}
*/

bool Command::add_param(uint8_t value){
    if(param_counter > ELP_MAX_CMD_PARAMS) return false;
    param[param_counter++] = value;
    return true;
}

bool Command::set_cmd(uint32_t _cmd){
    cmd = _cmd;
    return true;
}


bool Command::makeString(QByteArray& _output){
    size_t i = 0;
    _output[i++] = '@';
    _output[i++] = 'S';
    if(!bigEndian) StringConvertor::uint32_to_qbytearray_le(cmd, _output, i);
    else StringConvertor::uint32_to_qbytearray_be(cmd, _output, i); 
    i+= ELP_CMD_STRING_LENGTH;
    if(param_counter > 0){
        for(size_t k = 0; k < param_counter; k++){
            _output[i++] = '#';
            if(!bigEndian) StringConvertor::uint8_to_qbytearray_le(param[k], _output, i);
            else StringConvertor::uint8_to_qbytearray_be(param[k], _output, i);
            i+= 2;
        }
    }

    if((string_siz > 0) & (string_siz <= ELP_QUADRO_BUF_SIZE)){
        _output[i++] = '@';
        _output[i++] = '?';
        if(!bigEndian) StringConvertor::uint8_to_qbytearray_le(string_siz, _output, i);
        else StringConvertor::uint8_to_qbytearray_be(string_siz, _output, i);
        i+= 2;
        _output[i++] = '@';
        _output[i++] = '!';
        for(size_t k = 0; k < string_siz; k++){
            _output[i++] = string_buffer.raw_data8[k];
        }
    }
    _output[i++] = '@';
    _output[i++] = 'E';
    return true;
}


size_t Command::calculateStringSize(){
    size_t st_sz = 4; /* @S @E*/
    if(cmd) st_sz+=8;
    if(param_counter){
        st_sz += param_counter*3;
    }
    if(string_siz){
        st_sz += (6 + string_siz);
    }
    return st_sz;
    ;}

void Command::print(){
    qDebug() << "cmd";
    qDebug() << cmd;
    qDebug() << "string_siz";
    qDebug() << string_siz;
    qDebug() << "string_buffer";
    qDebug() << string_buffer.raw_data8;
    qDebug() << "param_counter";
    qDebug() << param_counter;
    qDebug() << "param";
    qDebug() << param;
}

