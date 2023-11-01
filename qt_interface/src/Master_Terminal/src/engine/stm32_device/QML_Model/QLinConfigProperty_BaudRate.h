#ifndef QLINCONFIGPROPERTY_BAUDRATE_H
#define QLINCONFIGPROPERTY_BAUDRATE_H

#include "QLinConfigProperty.h"



/*****************************************************************************************/
/*********************          DataBits      ********************************************/
/*****************************************************************************************/

#include "qtmetamacros.h"

class QLinConfigProperty_BaudRate: public QLinConfigProperty{
    Q_OBJECT

public:
    explicit QLinConfigProperty_BaudRate(): QLinConfigProperty(){
        QLinConfigProperty_BaudRate::init();
    };
    virtual ~QLinConfigProperty_BaudRate(){};

protected:
    void init () override{
        const QString default_BaudRate = "LIN_9600"; /* default name */

        QList<QString> _name_list = {
            "LIN_1200",
            "LIN_2400",
            "LIN_4800",
            default_BaudRate,
            "LIN_19200",
            "LIN_38400",
            "LIN_57600",
            "LIN_115200",
            "LIN_921600"
        };

        auto k = 0; /* from 0 to max value in Enum */
        for (k = 0; k <= LIN_921600 ; k++){

            auto _item = QSharedPointer<QLinConfigItem>(new QLinConfigItem(this, _name_list[k], k));

                this->append(_item);
                if(_name_list[k] == default_BaudRate){
                    current_index = default_index = k;
                }
        } /*** finished with presets ***/

    }

private:
};

#endif /* QLINCONFIGPROPERTY_BAUDRATE_H */
