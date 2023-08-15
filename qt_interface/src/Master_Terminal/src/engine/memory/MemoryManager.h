#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

/***********************************************************************
 * MemoryManager <== FlashSpiMemoryDataProperty
 *                   *MemoryDataProperty         <==  MemoryDataItem
 *
 *
 * MemoryManager contains an SPI memory chip data model
 *
 * Supported functions:
 *  add an item
 *  parse a recieved byte array into items
 *  clear the list
 *
 ************************************************************************/

#include <QObject>
#include <QDebug>
//#include "../../app_settings.h"
//#include "MemoryTablemodel.h"
#include "MemoryDataProperty.h"
//#include "../../engine/command_manager/StringConvertor.h"
#include <QFile>


class MemoryManager : public QObject{
    Q_OBJECT
    Q_PROPERTY(FlashSpiMemoryDataProperty* FlashSpi_DataModel READ FlashSpi_DataModel CONSTANT)
    Q_PROPERTY(QString error_status READ error_status WRITE setError_status RESET resetError_status NOTIFY error_statusChanged)

public:
    explicit MemoryManager(QObject *parent = 0){
    }
    ~MemoryManager() {};

    //==================================== init =====================================
    // Parse a byte array and add parsed items
    bool parseByteArray(int _addr, QByteArray &_data, int _transaction_length);
    void addMemoryItem(int _addr, const QString &_data);

    //================================= Service ======================================
    Q_INVOKABLE QString string_from_FlashSpiMemoryData();
    Q_INVOKABLE bool write_FlashSpiMemoryData_into_file(QString _filename);

    //========================== Class setters/getters ===============================
    const QString &error_status() const;
    void setError_status(const QString &newError_status);
    void resetError_status();
    FlashSpiMemoryDataProperty *FlashSpi_DataModel(){
        return &m_FlashSpiModel;
    }

signals:
    void error_statusChanged();

public slots:
    void resetFlashSpi_DataModel();

private:
    FlashSpiMemoryDataProperty m_FlashSpiModel;
    QString m_error_status = "";
};

#endif // MEMORYMANAGER_H
