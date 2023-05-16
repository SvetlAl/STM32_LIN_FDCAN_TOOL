#ifndef COMMAND_H
#define COMMAND_H

#include "../../app_settings.h"
#ifdef QT_IN_USE
#include <QDebug>
#endif
#include "StringConvertor.h"

#define ELP_QUADRO_BUF_SIZE								64	/* el_quadro_buffer structure size. bytes */
#define ELP_MAX_STR_INPUT_LENGTH						64	/* TODO add anno */
#define ELP_MAX_STR_CMD_LENGTH							128	/* Buffer size to store incoming data, that needs to be processed. MAX - 256 */
#define ELP_CMD_STRING_LENGTH							8		/* Command symbols count "FFFFFFFF" - 8 bytes */
#define ELP_CMD_START_CMD_LENGTH						2		/* @S */
#define ELP_CMD_END_CMD_LENGTH							2		/* @E */
#define ELP_CMD_START_STRING_CMD_LENGTH                 2		/* @! */
#define ELP_CMD_STRING_CMD_SIZ							4	  /* @?XX */

#define ELP_MAX_CMD_PARAMS 16 /* 110/2=55 */ /*(ELP_MAX_STR_CMD_LENGTH - ELP_CMD_STRING_LENGTH - ELP_CMD_START_CMD_LENGTH - ELP_CMD_END_CMD_LENGTH - ELP_CMD_START_STRING_CMD_LENGTH - ELP_CMD_STRING_CMD_SIZ)/2 */

typedef union{
    uint32_t raw_data32[ELP_QUADRO_BUF_SIZE/4];
    uint8_t raw_data8[ELP_QUADRO_BUF_SIZE];
} el_quadro_buffer;


class Command{

public:
    Command(uint32_t _cmd, bool _be): cmd(_cmd), bigEndian(_be){
    };
    ~Command(){
    };

    static inline const QString ELP_OK_RESPONSE = "$OK$";
    static inline const QString ELP_BUSY_RESPONSE = "$BS$";
    static inline const QString ELP_ERROR_RESPONSE = "$ER$";
    static inline const QString ELP_IDLE_RESPONSE = "$DL$";

    bool set_cmd(uint32_t _cmd);
    bool fill_string(const QByteArray& input_buf);

    bool append_uint_to_string(uint32_t value);
    bool append_uint_to_string(uint16_t value);

    bool add_param(uint8_t value);

    bool makeString(QByteArray& _output);
    size_t calculateStringSize();
    void print();

private:
    uint32_t cmd = 0;						/* actually command itself */
    uint32_t string_siz = 0;				/* string length (if a command provides a char string) */
    el_quadro_buffer string_buffer = {0};		/* char string itself. If data length is 4-byte divisible, an application can work faster */
    uint32_t param_counter = 0;				/* how many parameters are in a command (if a command provides any parameters)  */
    uint8_t param[ELP_MAX_CMD_PARAMS] = {0};	/* parameters array (if a command provides any parameters) */

    bool bigEndian = false;
};

#endif // COMMAND_H
