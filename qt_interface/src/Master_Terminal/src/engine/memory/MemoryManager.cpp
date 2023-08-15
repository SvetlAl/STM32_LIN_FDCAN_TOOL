#include "MemoryManager.h"

/********************************************************************
 *
 *
 *                     Initialization
 *
 *
********************************************************************/
// Parse a byte array and add parsed items
bool MemoryManager::parseByteArray(int _addr, QByteArray &_data, int _transaction_length){
    resetError_status();
    int transaction_addr = _addr;
    const int chunkSize = 16;
    int byte_pos = 0;

    if(_data.size() != _transaction_length){
        setError_status("FAILED: Read data length mismatch.");
        return false;
    }

    for(size_t i = 0 ; i < _transaction_length; i += chunkSize){
        QByteArray chunk = _data.mid(byte_pos, chunkSize);
        uint8_t cmd_byte = 0;
        QByteArray chunk_ascii;
        chunk_ascii.resize(chunkSize*2);
        uint32_t j = 0;

        for(uint32_t k = 0; k < chunkSize; k++){
            cmd_byte = StringConvertor::halfbyte_to_hexascii(chunk[k] >> 4);
            chunk_ascii[j++] = cmd_byte;
            cmd_byte = StringConvertor::halfbyte_to_hexascii(chunk[k]);
            chunk_ascii[j++] = cmd_byte;
        }
        addMemoryItem(transaction_addr, QString::fromUtf8(chunk_ascii));
        byte_pos += chunkSize;
        transaction_addr += chunkSize;
    }
    return true;
}

void MemoryManager::addMemoryItem(int _addr, const QString &_data){
    QString address = QString::number(_addr, 16);
    address = address.toUpper();
    m_FlashSpiModel.addItem(address, _data);
}


/********************************************************************
 *
 *
 *                     Slots
 *
 *
********************************************************************/

void MemoryManager::resetFlashSpi_DataModel(){
    m_FlashSpiModel.clear();
}


/********************************************************************
 *
 *
 *                     Service
 *
 *
********************************************************************/
QString MemoryManager::string_from_FlashSpiMemoryData(){
    QString response;
    for(size_t i = 0; i < m_FlashSpiModel.size(); i++){
        response.append(m_FlashSpiModel.dataPtr(i)->print());
    }
    return response;
}

bool MemoryManager::write_FlashSpiMemoryData_into_file(QString _filename){
    resetError_status();
    int line_count = m_FlashSpiModel.length();
    if(line_count==0){
        setError_status("FAILED: The file length mismatch.");
        return false;
    }

    QFile flashFile(_filename);
    bool open = flashFile.open(QFile::WriteOnly);
    if(!open){
        setError_status("FAILED: The file unavailable.");
        return false;
    }

    QDataStream stream(&flashFile);
    for(size_t i = 0; i < line_count ; i++){
        QByteArray line = m_FlashSpiModel.raw_data(i);
        stream.writeRawData(line, 16);
    }
    flashFile.close();
    return true;
}

/********************************************************************
 *
 *
 *                     Class setters/getters
 *
 *
********************************************************************/

const QString &MemoryManager::error_status() const{
    return m_error_status;
}

void MemoryManager::setError_status(const QString &newError_status){
    if (m_error_status == newError_status)
        return;
    m_error_status = newError_status;
    emit error_statusChanged();
}

void MemoryManager::resetError_status(){
    setError_status({}); // TODO: Adapt to use your actual default value
}
