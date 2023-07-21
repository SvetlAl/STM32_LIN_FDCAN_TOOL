#include "MemoryManager.h"




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

const QString &MemoryManager::error_status() const
{
    return m_error_status;
}

void MemoryManager::setError_status(const QString &newError_status)
{
    if (m_error_status == newError_status)
        return;
    m_error_status = newError_status;
    emit error_statusChanged();
}

void MemoryManager::resetError_status()
{
    setError_status({}); // TODO: Adapt to use your actual default value
}
