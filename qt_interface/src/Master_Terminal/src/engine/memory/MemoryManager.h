#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <QObject>
#include <QDebug>
#include "../../core/Console.h"
#include "../../app_settings.h"
//#include "MemoryTablemodel.h"
#include "MemoryDataProperty.h"
#include "../../engine/command_manager/StringConvertor.h"
#include <QFile>


class MemoryManager : public QObject{
    Q_OBJECT
    Q_PROPERTY(FlashSpiMemoryDataProperty* FlashSpi_DataModel READ FlashSpi_DataModel CONSTANT)
    Q_PROPERTY(QString error_status READ error_status WRITE setError_status RESET resetError_status NOTIFY error_statusChanged)

public:
    explicit MemoryManager(QObject *parent = 0){
    }
    ~MemoryManager() {};

    FlashSpiMemoryDataProperty *FlashSpi_DataModel(){
        return &m_FlashSpiModel;
    }

    void addMemoryItem(int _addr, const QString &_data){
        QString address = QString::number(_addr, 16);
        address = address.toUpper();
        m_FlashSpiModel.addItem(address, _data);
    }

    bool parseByteArray(int _addr, QByteArray &_data, int _transaction_length){
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

    Q_INVOKABLE QString string_from_FlashSpiMemoryData();
    Q_INVOKABLE bool write_FlashSpiMemoryData_into_file(QString _filename);

    const QString &error_status() const;
    void setError_status(const QString &newError_status);
    void resetError_status();

signals:

    void error_statusChanged();

public slots:
    void resetFlashSpi_DataModel(){
        m_FlashSpiModel.clear();
    }

private:
//    Console *m_pConsole;
    FlashSpiMemoryDataProperty m_FlashSpiModel;
    QString m_error_status = "";


};

#endif // MEMORYMANAGER_H
