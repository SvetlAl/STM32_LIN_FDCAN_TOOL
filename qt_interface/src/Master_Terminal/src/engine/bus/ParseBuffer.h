#ifndef PARSEBUFFER_H
#define PARSEBUFFER_H

#include <QObject>
#include "CanBusItem.h"
#include "LinBusItem.h"

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

signals:

private:
    QByteArray m_parse_buffer;
    const int max_parse_buffer_size = chunkSize*10000;
};




class LinParseBuffer : public QObject{
    Q_OBJECT

public:
    explicit LinParseBuffer(QObject *parent = nullptr){};

    static constexpr int chunkSize = sizeof(lin_message_info_raw);
    static constexpr uint8_t start_symbol = '@';
    static bool validateLinMsg(const QByteArray &_data);

    void append(const QByteArray &data);
    size_t size() const;
    int findEntryPoint() const;

    QList<QByteArray> extractAllParseableLines();

signals:

private:
    QByteArray m_parse_buffer;
    const int max_parse_buffer_size = chunkSize*10000;
};

#endif // PARSEBUFFER_H
