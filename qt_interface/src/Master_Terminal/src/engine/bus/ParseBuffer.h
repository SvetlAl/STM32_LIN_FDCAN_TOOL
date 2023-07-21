#ifndef PARSEBUFFER_H
#define PARSEBUFFER_H

#include <QObject>
#include "CanBusItem.h"


class ParseBuffer : public QObject{
    Q_OBJECT

public:
    explicit ParseBuffer(QObject *parent = nullptr){};

    static constexpr int chunkSize = sizeof(can_message_info_raw);
    static constexpr uint8_t start_symbol = '@';
    static bool validateCanMsg(const QByteArray &_data);

    void append(const QByteArray &data);
    size_t size() const;
    int findEntryPoint() const;

    QList<QByteArray> extractAllParseableLines();


/*
  const QByteArray* ptr() const{return &m_parse_buffer;}
    const int size(){return m_parse_buffer.size();}
    bool isReady();

    QByteArray extractAll();
    void prepend(const QByteArray& data);

    bool isParsedDataPending(){
        if(m_parsed_data.size() > 0) return true;
        else return false;
    }

    QByteArray extractParsedLine(){
        parsedDataMutex.tryLock(20);
        QByteArray arr = m_parsed_data.first();
        m_parsed_data.removeFirst();
        parsedDataMutex.unlock();
        return arr;
    }

    void addParsedLine(const QByteArray arr){
        parsedDataMutex.tryLock(20);
        m_parsed_data.append(arr);
        parsedDataMutex.unlock();
    }
*/

signals:

private:
    QByteArray m_parse_buffer;
    const int max_parse_buffer_size = chunkSize*10000;
};

#endif // PARSEBUFFER_H
