#ifndef QLINCONFIGPROPERTY_FILTERPRESET_H
#define QLINCONFIGPROPERTY_FILTERPRESET_H

#include "QLinConfigProperty.h"



/*****************************************************************************************/
/*********************          DataBits      ********************************************/
/*****************************************************************************************/

#include "qtmetamacros.h"

class QLinConfigProperty_FilterPreset: public QLinConfigProperty{
    Q_OBJECT
public:
    explicit QLinConfigProperty_FilterPreset(): QLinConfigProperty(){
        QLinConfigProperty_FilterPreset::init();
    };
    virtual ~QLinConfigProperty_FilterPreset(){};

protected:
    void init () override{
        const QString default_FilterPreset = "Default"; /* default name */

        QList<QString> _name_list = {
            default_FilterPreset,
            "User def",
            "MMC_Pajero TYR"
        };

        auto k = 0; /* from 0 to max value in Enum */
        for (k = 0; k < LIN_FILTER_COUNT ; k++){

            auto _item = QSharedPointer<QLinConfigItem>(new QLinConfigItem(this, _name_list[k], k));

                this->append(_item);
                if(_name_list[k] == default_FilterPreset){
                    current_index = default_index = k;
                }
        } /*** finished with presets ***/

    }

private:
};

#endif /* QLINCONFIGPROPERTY_FILTERPRESET_H */
