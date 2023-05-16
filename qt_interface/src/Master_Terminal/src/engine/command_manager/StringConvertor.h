#ifndef STRING_CONVERTOR_H
#define STRING_CONVERTOR_H

#include "../../app_settings.h"
#include <QDebug>

/*
#define BIG_ENDIAN      true
#define LITTLE_ENDIAN   false
*/

#define SC_4BIT_TO_ASCII(x) (uint8_t) ((x >= 10) ? ('A' + x -10) : ('0' + x))

#define DEV_CODE_HBYTE(x) (uint8_t) ((DEV_CODE >> (12 - x*4)) & ~0xF0)
#define DEV_CODE_ASCII(x) (uint8_t) ((DEV_CODE_HBYTE(x) >= 10) ? ('A' + DEV_CODE_HBYTE(x) -10) : ('0' + DEV_CODE_HBYTE(x)))

#define HALFBYTE_FROM_32(val32, x) (uint8_t) ((val32 >> (28 - x*4)) & ~0xF0)
#define HALFBYTE_FROM_32_2_ASCII(val32, x) (uint8_t) ((HALFBYTE_FROM_32(val32, x) >= 10) ? ('A' + HALFBYTE_FROM_32(val32, x) -10) : ('0' + HALFBYTE_FROM_32(val32, x)))
/*    uint32_t bal = 0x1234ABCD;
    for(size_t i = 0; i < 8; i++){
        cout << HALFBYTE_FROM_32_2_ASCII(bal, i);
    }
       i: 0 1 2 3  4 5 6 7
    cout: 1 2 3 4  A B C D
*/

#define SWAP_16BITS(val) (*val = (*val << 8) | (*val >> 8))
#define SWAP_32BITS(val) (*val = ((*val << 24) & 0xFF000000) | ((*val << 8) & 0x00FF0000) | ((*val >> 8) & 0x0000FF00) | ((*val >> 24) & 0x000000FF))

class StringConvertor {

public:
    explicit StringConvertor(){};
    ~StringConvertor(){};

    /**
    * brief  Translate a single hex (0-F) into an ascii symbol
    * param  0x0A 0x0B 0x0C 0x0D 0x0E 0x0F
    * param
    * retval   'A'  'B'  'C'  'D'  'E'  'F'
    */

    static uint8_t halfbyte_to_hexascii(uint8_t _halfbyte){
        uint8_t _ascii;
        _halfbyte &= 0x0F;
        if(_halfbyte >= 10){
            _ascii=('A' + _halfbyte -10);
        }
        else{
            _ascii=('0' + _halfbyte);
        }
        return _ascii;
    }

    /**
    * brief  Translate an ascii symbol into a hex (0-F)
    * param    'A'  'B'  'C'  'D'  'E'  'F'
    * param
    * retval 0x0A 0x0B 0x0C 0x0D 0x0E 0x0F
    */

    // Translate an ascii symbol into a hex (0-F)
    static uint8_t hexascii_to_halfbyte(uint8_t _ascii){
        uint8_t _halfbyte;
        if((_ascii >= '0') && (_ascii <= '9')){
        _halfbyte=(_ascii - '0');}
        else if((_ascii >= 'a') && (_ascii <= 'f')){
    //	_halfbyte=(_ascii - 'a');}
        _halfbyte=(_ascii - 87);}
        else if((_ascii >= 'A') && (_ascii <= 'F')){
    //	_halfbyte=(_ascii - 'A');}
        _halfbyte=(_ascii - 55);}
        else{
            return(0xFF);
        }
        return _halfbyte;
    }

    /**
    * brief  Translate an ascii symbol string into a hex (0-F) array
    * param   uint8_t array 'A'  'B'  'C'  'D'  'E'  'F'
    * param 	length  data_in array count
    * retval  uint8_t array 0xAB 0xCD 0xEF
    */

    static void str_to_ascii(uint8_t *data_in, uint8_t *data_out, uint16_t length){
        uint8_t cmd_byte = 0;

        uint32_t i = 0;
        for(uint32_t k = 0; k < length; k+=2){
            cmd_byte = hexascii_to_halfbyte(data_in[k+1]);
            data_out[i] = cmd_byte;
            cmd_byte = hexascii_to_halfbyte(data_in[k]);
            data_out[i++] |= (uint8_t)((cmd_byte << 4) & ~0x0F);
            }
    }

    /**
    * brief  Translate an ascii symbol string into a hex (0-F) uint32
    * param   uint8_t array 'A'  'B'  'C'  'D'  'E'  'F'
    * param
    * retval  uint32_t/uint16_t 0xABCDEF
    */

    /********** Big Endian *************/
    static uint32_t str_to_uint32_be(uint8_t *data_in){
        uint32_t ret_val = 0;
        uint8_t shift_cnt = 28;
        uint8_t cmd_byte = 0;

        for(uint32_t k = 0; k < 8; k++){
            cmd_byte = hexascii_to_halfbyte(*data_in++);
            ret_val |= (uint32_t)((uint32_t)cmd_byte << shift_cnt);
            shift_cnt-=4;
            }
        return ret_val;
    }

    /********** Little Endian *************/
    static uint32_t str_to_uint32_le(uint8_t *data_in){
        uint32_t ret_val = 0;
        uint8_t shift_cnt =0;
        uint8_t cmd_byte = 0;

        data_in+=7;

        for(uint32_t k = 0; k < 8; k++){
            cmd_byte = hexascii_to_halfbyte(*data_in--);
            ret_val |= (uint32_t)((uint32_t)cmd_byte << shift_cnt);
            shift_cnt+=4;
            }
        return ret_val;
    }

    /********** Big Endian *************/
    static uint16_t str_to_uint16_be(uint8_t *data_in){
        uint16_t ret_val = 0;
        uint8_t shift_cnt = 12;
        uint8_t cmd_byte = 0;

        for(uint32_t k = 0; k < 4; k++){
            cmd_byte = hexascii_to_halfbyte(*data_in++);
            ret_val |= (uint16_t)((uint16_t)cmd_byte << shift_cnt);
            shift_cnt-=4;
            }
        return ret_val;
    }

    /********** Little Endian *************/
    static uint16_t str_to_uint16_le(uint8_t *data_in){
        uint32_t ret_val = 0;
        uint8_t shift_cnt =0;
        uint8_t cmd_byte = 0;

        data_in+=3;

        for(uint32_t k = 0; k < 4; k++){
            cmd_byte = hexascii_to_halfbyte(*data_in--);
            ret_val |= (uint16_t)((uint16_t)cmd_byte << shift_cnt);
            shift_cnt+=4;
            }
        return ret_val;
    }

    /**
    * brief  Translate a hex (0-F) uint32 into an ascii symbol string
    * param  uint32_t 0xABCDEF
    * param
    * retval uint8_t array 'A'  'B'  'C'  'D'  'E'  'F'
    */

    /********** Big Endian *************/
    static inline void uint32_to_str_be(uint32_t value, uint8_t *output){

        uint8_t shift_cnt = 0;
        uint8_t i2 = 0;
        for(uint32_t i = 0; i < 4; i++){
            output[i2++] = halfbyte_to_hexascii(value >> (shift_cnt + 4));
            output[i2++] = halfbyte_to_hexascii(value >> shift_cnt);
            shift_cnt+=8;
        }
    }

    /********** Little Endian *************/
    static inline void uint32_to_str_le(uint32_t value, uint8_t *output){

        uint8_t shift_cnt = 28;
        uint8_t i2 = 0;
        for(uint32_t i = 0; i < 4; i++){
            output[i2++] = halfbyte_to_hexascii(value >> (shift_cnt));
            output[i2++] = halfbyte_to_hexascii(value >> (shift_cnt - 4));
            shift_cnt-=8;
        }
    }

    /********** Big Endian *************/
    static inline void uint16_to_str_be(uint16_t value, uint8_t *output){

        uint8_t shift_cnt = 0;
        uint8_t i2 = 0;
        for(uint32_t i = 0; i < 2; i++){
            output[i2++] = halfbyte_to_hexascii(value >> (shift_cnt + 4));
            output[i2++] = halfbyte_to_hexascii(value >> shift_cnt);
            shift_cnt+=8;
        }
    }

    /********** Little Endian *************/
    static inline void uint16_to_str_le(uint16_t value, uint8_t *output){
        uint16_to_str_be(value, output);
 /*
        uint8_t shift_cnt = 12;
        uint8_t i2 = 0;
        for(uint32_t i = 0; i < 2; i++){
            output[i2++] = halfbyte_to_hexascii(value >> (shift_cnt));
            output[i2++] = halfbyte_to_hexascii(value >> (shift_cnt - 4));
            shift_cnt-=8;
        }
        */
    }

    /********** Big Endian *************/
    static inline void uint32_to_qbytearray_be(uint32_t value, QByteArray& _output, int pos){

        int total_length = _output.length();
        if((total_length - pos) < 8) return;

        uint8_t shift_cnt = 0;
        uint8_t i2 = pos;
        for(uint32_t i = 0; i < 4; i++){
            _output[i2++] = halfbyte_to_hexascii(value >> (shift_cnt + 4));
            _output[i2++] = halfbyte_to_hexascii(value >> shift_cnt);
            shift_cnt+=8;
        }
    }

    /********** Little Endian *************/
    static inline void uint32_to_qbytearray_le(uint32_t value, QByteArray& _output, int pos){

        int total_length = _output.length();
        if((total_length - pos) < 8) return;

        uint8_t shift_cnt = 28;
        uint8_t i2 = pos;
        for(uint32_t i = 0; i < 4; i++){
            _output[i2++] = halfbyte_to_hexascii(value >> (shift_cnt));
            _output[i2++] = halfbyte_to_hexascii(value >> (shift_cnt - 4));
            shift_cnt-=8;
        }
    }


    /**
    * brief  Translate an ascii symbol string into a hex (0-F)
    * param   uint8_t 'A'  'F'
    * param
    * retval  uint8_t 0xAF
    */

    static uint8_t str_to_uint8(uint8_t lowbyte, uint8_t highbyte){
        uint8_t ret_val = hexascii_to_halfbyte(lowbyte) | ((uint8_t)(hexascii_to_halfbyte(highbyte) << 4));
        return ret_val;
    }

    /**
    * brief  Translate  a hex (0-F) into an ascii symbol string
    * param   uint8_t 0xAF
    * param
    * retval  uint8_t 'A'  'F'
    */

    /********** Big Endian *************/
    static inline void uint8_to_qbytearray_be(uint8_t value, QByteArray& _output, int pos){

        int total_length = _output.length();
        if((total_length - pos) < 2) return;

        uint8_t shift_cnt = 0;
        uint8_t i2 = pos;
        _output[i2++] = halfbyte_to_hexascii(value >> (shift_cnt + 4));
        _output[i2++] = halfbyte_to_hexascii(value >> shift_cnt);
    }

    /********** Little Endian *************/
    static inline void uint8_to_qbytearray_le(uint8_t value, QByteArray& _output, int pos){
        uint8_to_qbytearray_be(value, _output, pos);
        /*
        int total_length = _output.length();
        if((total_length - pos) < 2) return;

        uint8_t shift_cnt = 4;
        uint8_t i2 = pos;

        _output[i2++] = halfbyte_to_hexascii(value >> (shift_cnt));
        _output[i2++] = halfbyte_to_hexascii(value >> (shift_cnt - 4));
        */
    }

    /**
    * brief  Translate bytes array into a char string
    * param uint8_t array {0x01 0x02 0x03 0x04 }
    * param
    * retval array {'0' '1' '0' '2' '0' '3' '0' '4'}
    */

    static void hexArray2asciiArray(uint8_t *in_buf, uint8_t *out_buf, uint32_t input_length){
        uint8_t i2 = 0;
        for(uint32_t i = 0; i < input_length; i++){
            out_buf[i2++] = halfbyte_to_hexascii((in_buf[i]>> 4));
            out_buf[i2++] = halfbyte_to_hexascii((in_buf[i]));
        }
    }


    /**
    * brief  Translate uint32_t into QString as HEX
    * param uint32_t 0X012345AF
    * param
    * retval QString "012345AF"
    */

    static QString uint32_t_to_QString_as_HEX(uint32_t size_address){
        QString hexval = QString("%1").arg(size_address, 8, 16, QChar('0'));
        return hexval;
    }

    /**
    * brief  Translate uint16_t into QString as HEX
    * param uint32_t 0X0123
    * param
    * retval QString "0123"
    */

    static QString uint16_t_to_QString_as_HEX(uint16_t size_address){
        QString hexval = QString("%1").arg(size_address, 4, 16, QChar('0'));
        return hexval;
    }

    /**
    * brief  Translate uint8_t into QString as HEX
    * param uint32_t 0X01
    * param
    * retval QString "01"
    */

    static QString uint8_t_to_QString_as_HEX(uint16_t size_address){
        QString hexval = QString("%1").arg(size_address, 2, 16, QChar('0'));
        return hexval;
    }


    /**
    * brief Convert symbol representation in QString from Ascii to hex
    * param "12345"
    * param
    * retval "31 32 33 34 35"
    */
    static QString asciiToHex(const QString& str) {
        QByteArray ascii_arr = str.toLocal8Bit(); // Convert QString to QByteArray with ASCII representation
        QByteArray hex_arr = ascii_arr.toHex(' '); // Convert ASCII QByteArray to Hex QByteArray with spaces between each byte
        QString hex_str = QString(hex_arr); // Convert Hex QByteArray to QString

        return hex_str;
    }




private:

};


// Q_DECLARE_METATYPE(CommandManager);
#endif // STRING_CONVERTOR_H
