#ifndef PARSEBUFFER_H
#define PARSEBUFFER_H

#include <QObject>
#include "CanBusItem.h"
#include "FDCAN_CanBusItem.h"
#include "LinBusItem.h"

#define FDCAN_FD_MSG_LENGTH_FROM_BYTE(dlc)(dlc == 0x08) ? 8 :   \
                                          (dlc == 0x09) ? 12 : \
                                          (dlc == 0x0A) ? 16 : \
                                          (dlc == 0x0B) ? 20 : \
                                          (dlc == 0x0C) ? 24 : \
                                          (dlc == 0x0D) ? 32 : \
                                          (dlc == 0x0E) ? 48 : \
                                          (dlc == 0x0F) ? 64 : \
                                          (dlc == 0x07) ? 7 : \
                                          (dlc == 0x06) ? 6 : \
                                          (dlc == 0x05) ? 5 : \
                                          (dlc == 0x04) ? 4 : \
                                          (dlc == 0x03) ? 3 : \
                                          (dlc == 0x02) ? 2 : \
                                          (dlc == 0x01) ? 1 : 0


#define FDCAN_STD_MSG_LENGTH_FROM_BYTE(dlc) (dlc == 0x08) ? 8 : \
                                            (dlc == 0x07) ? 7 : \
                                            (dlc == 0x06) ? 6 : \
                                            (dlc == 0x05) ? 5 : \
                                            (dlc == 0x04) ? 4 : \
                                            (dlc == 0x03) ? 3 : \
                                            (dlc == 0x02) ? 2 : \
                                            (dlc == 0x01) ? 1 : 0

#define FDCAN_MSG_LENGTH_FROM_BYTE(is_fd, _dlc) (is_fd) ? FDCAN_FD_MSG_LENGTH_FROM_BYTE(_dlc) : FDCAN_STD_MSG_LENGTH_FROM_BYTE(_dlc)



//============================== ST CAN ==============================
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



//============================== FD CAN ==============================
class FDCAN_ParseBuffer : public QObject{
    Q_OBJECT

public:
    explicit FDCAN_ParseBuffer(QObject *parent = nullptr){};

    static constexpr int chunkSize = sizeof(fdcan_message_info);
    static constexpr int max_chunkSize = chunkSize + 64;
    static constexpr uint8_t start_symbol = '#';
    static bool validateCanMsg(const QByteArray &_data);

    static uint8_t calculate_fdmsg_data_length(const QByteArray &hdr_bytes){
        uint8_t dlc = hdr_bytes.at(12);
        uint8_t flags = hdr_bytes.at(13);
        bool fd_format = flags & 0x04;
        return FDCAN_MSG_LENGTH_FROM_BYTE(fd_format, dlc);
    }

    void append(const QByteArray &data);
    size_t size() const;
    int findEntryPoint() const;

    QList<QByteArray> extractAllParseableLines();

signals:

private:
    QByteArray m_parse_buffer;
    const int max_parse_buffer_size = chunkSize*10000;
};



//============================== LIN ==============================
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
