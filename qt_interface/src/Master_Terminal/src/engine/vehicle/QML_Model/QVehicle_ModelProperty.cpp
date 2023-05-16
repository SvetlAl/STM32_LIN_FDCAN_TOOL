#include "QVehicle_ModelProperty.h"

QVariant QVehicle_ModelProperty::current_item() {
    return item(current_index);
}

int QVehicle_ModelProperty::getCurrentIndex() const{
    return current_index;
}

void QVehicle_ModelProperty::setCurrentIndex(int _index){
    current_index = _index;
}

int QVehicle_ModelProperty::get_current_value(){
    QSharedPointer<QVehicle_ModelItem> val_ptr = dataPtr(current_index);
    return val_ptr->value();
}
const QString QVehicle_ModelProperty::get_current_name(){
    QSharedPointer<QVehicle_ModelItem> val_ptr = dataPtr(current_index);
    return val_ptr->name();
}

const int QVehicle_ModelProperty::get_property_value(const int i){
    QSharedPointer<QVehicle_ModelItem> val_ptr = dataPtr(i);
    return val_ptr->value();
}

const void QVehicle_ModelProperty::set_property_value(const int _new_val, const int i){
    QSharedPointer<QVehicle_ModelItem> val_ptr = dataPtr(i);
    val_ptr->setValue(_new_val);
}



void QVehicleNames_ModelProperty::init (){
    auto _item = QSharedPointer<QVehicle_ModelItem>
        (new QVehicle_ModelItem(this, "Toyota LC300", MODEL_TOYOTA_LC300, Vehicle::ModelBrand::Toyota));
    this->append(_item);

    _item = QSharedPointer<QVehicle_ModelItem>
        (new QVehicle_ModelItem(this, "Toyota LC150", MODEL_TOYOTA_LC150, Vehicle::ModelBrand::Toyota));
    this->append(_item);

    _item = QSharedPointer<QVehicle_ModelItem>
        (new QVehicle_ModelItem(this, "Toyota Hilux", MODEL_TOYOTA_HILUX, Vehicle::ModelBrand::Toyota));
    this->append(_item);

    _item = QSharedPointer<QVehicle_ModelItem>
        (new QVehicle_ModelItem(this, "Toyota Tundra 07+", MODEL_TOYOTA_TUNDRA_2008, Vehicle::ModelBrand::Toyota));
    this->append(_item);

    _item = QSharedPointer<QVehicle_ModelItem>
        (new QVehicle_ModelItem(this, "GreatWall Wingle7", MODEL_GREAT_WALL_WINGLE7, Vehicle::ModelBrand::GreatWall));
    this->append(_item);

    _item = QSharedPointer<QVehicle_ModelItem>
        (new QVehicle_ModelItem(this, "Dodge Ram 2013+", MODEL_DODGE_RAM_2013, Vehicle::ModelBrand::Dodge));
    this->append(_item);

    _item = QSharedPointer<QVehicle_ModelItem>
        (new QVehicle_ModelItem(this, "Isuzu DMAX/MUX", MODEL_ISUZU_DMAX_MUX, Vehicle::ModelBrand::Isuzu));
    this->append(_item);

    _item = QSharedPointer<QVehicle_ModelItem>
        (new QVehicle_ModelItem(this, "LandRover Defender 22+", MODEL_LAND_ROVER_DEFENDER_2022, Vehicle::ModelBrand::LandRover));
    this->append(_item);

    _item = QSharedPointer<QVehicle_ModelItem>
        (new QVehicle_ModelItem(this, "MMC L200 19+", MODEL_MITSUBISHI_L200, Vehicle::ModelBrand::Mitsubishi));
    this->append(_item);

    _item = QSharedPointer<QVehicle_ModelItem>
        (new QVehicle_ModelItem(this, "MMC PajeroSport 19+", MODEL_MITSUBISHI_PAJERO_SPORT, Vehicle::ModelBrand::Mitsubishi));
    this->append(_item);

    _item = QSharedPointer<QVehicle_ModelItem>
        (new QVehicle_ModelItem(this, "GreatWall Poer", MODEL_GREAT_WALL_POER, Vehicle::ModelBrand::GreatWall));
    this->append(_item);

    _item = QSharedPointer<QVehicle_ModelItem>
        (new QVehicle_ModelItem(this, "Toyota LC200", MODEL_TOYOTA_LC200, Vehicle::ModelBrand::Toyota));
    this->append(_item);

    _item = QSharedPointer<QVehicle_ModelItem>
        (new QVehicle_ModelItem(this, "Lexus LX 06+", MODEL_LEXUS_LX570, Vehicle::ModelBrand::Lexus));
    this->append(_item);

    _item = QSharedPointer<QVehicle_ModelItem>
        (new QVehicle_ModelItem(this, "Toyota Tundra 22+", MODEL_TOYOTA_TUNDRA_2022, Vehicle::ModelBrand::Toyota));
    this->append(_item);

    _item = QSharedPointer<QVehicle_ModelItem>
        (new QVehicle_ModelItem(this, "Tank 300", MODEL_TANK_300, Vehicle::ModelBrand::Tank));
    this->append(_item);

    _item = QSharedPointer<QVehicle_ModelItem>
        (new QVehicle_ModelItem(this, "Extra", MODEL_EXTRA, Vehicle::ModelBrand::Extra));
    this->append(_item);
}
