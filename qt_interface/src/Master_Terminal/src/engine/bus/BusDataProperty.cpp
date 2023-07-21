#include "BusDataProperty.h"
//#include "BusParser.h"

/***********************************************************************************************
 *
 *
 *                                  CanBusTraceProperty
 *
 * ********************************************************************************************/

void CanBusTraceProperty::addItem(const QByteArray &data, bool validate){
    if(count() >= max_items()) return;
    //========= validate format ==============
//    if(validate) if(!BusParser::validateCanMsg(data))return;

    auto _item = QSharedPointer<CanBusItem>(new CanBusItem(this, data));

    this->append(_item);
//    emit changed();
//    emit layoutChanged();
}

void CanBusTraceProperty::addItem(const QByteArray &data, const ParseFilter &filter, bool validate){
    if(count() >= max_items()) return;
    //========= validate format ==============
//    if(validate) if(!BusParser::validateCanMsg(data))return;

    auto _item = QSharedPointer<CanBusItem>(new CanBusItem(this, data));
    if( !filter.m_can1 && (_item->intCan() == 1) ) return;
    if( !filter.m_can2 && (_item->intCan() == 2) ) return;

    if(filter.use_range){
        if((_item->int_id() > filter.end_id) | (_item->int_id() < filter.start_id)) return;
    }

    this->append(_item);
    emit changed();
//    emit layoutChanged();
}


//================ Extra data. Used if a terminal sends bus message data not in one piece ==============

uint32_t CanBusTraceProperty::max_items() const{
    return m_max_items;
}

void CanBusTraceProperty::setMax_items(uint32_t newMax_items){
    if (m_max_items == newMax_items){
        return;}
    m_max_items = newMax_items;
}

int CanBusTraceProperty::columnCount(const QModelIndex& ) const {
    return ColumnCount;
}

QVariant CanBusTraceProperty::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole || section >= columnCount())
        return QVariant();

    return m_columnNames.at(section);
}

//======================== sort functions =========================

void CanBusTraceProperty::deductTimeStamp(uint32_t tmstmp){
    if(count() == 0) return;

    uint32_t i = (count() - 1);
    do{
        auto _item = dataPtr(i);
        int deduction = _item->int_time() - tmstmp;
        if(deduction >= 0) _item->setIntTime(deduction);

    }while(i--);

    emit changed();
    emit layoutChanged();
}

void CanBusTraceProperty::deleteTimeStampRange(int start, int end){
    if(count() == 0) return;
    if(start > end){
        int tmp = start;
        start = end;
        end = tmp;
    }

    uint32_t i = (count() - 1);
    do{
        auto _item = dataPtr(i);
        if((_item->int_time() <= end) & (_item->int_time() >= start)){
            removeAt(i);
        }

    }while(i--);
    emit changed();
    emit layoutChanged();
}

void CanBusTraceProperty::sortColumn(const int col, bool fromTopToBottom){

    auto start = 0;
    auto end = count()  - 1;
    beginInsertRows(QModelIndex(), start, end );



    switch (col){
    case IsSelected:{
        if(fromTopToBottom){
            std::sort(this->begin(), this->end(), CanBusItem::sortBySelection);
        }
        else{
            std::sort(this->begin(), this->end(), CanBusItem::sortBySelectionReverse);
        }
    }
        break;

    case Time:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<CanBusItem>& a, const QSharedPointer<CanBusItem>& b) {
            return a->int_time() > b->int_time();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<CanBusItem>& a, const QSharedPointer<CanBusItem>& b) {
            return a->int_time() < b->int_time();});  }
        break;

    case CAN:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<CanBusItem>& a, const QSharedPointer<CanBusItem>& b) {
            return a->can() > b->can();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<CanBusItem>& a, const QSharedPointer<CanBusItem>& b) {
            return a->can() < b->can();});  }
        break;

    case ID:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<CanBusItem>& a, const QSharedPointer<CanBusItem>& b) {
            return a->id() > b->id();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<CanBusItem>& a, const QSharedPointer<CanBusItem>& b) {
            return a->id() < b->id();});  }
        break;

    case DLC:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<CanBusItem>& a, const QSharedPointer<CanBusItem>& b) {
            return a->dlc() > b->dlc();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<CanBusItem>& a, const QSharedPointer<CanBusItem>& b) {
            return a->dlc() < b->dlc();});  }
        break;

    case Data:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<CanBusItem>& a, const QSharedPointer<CanBusItem>& b) {
            return a->data() > b->data();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<CanBusItem>& a, const QSharedPointer<CanBusItem>& b) {
            return a->data() < b->data();});  }
        break;

    case IDE:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<CanBusItem>& a, const QSharedPointer<CanBusItem>& b) {
            return a->bool_ext_ide() > b->bool_ext_ide();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<CanBusItem>& a, const QSharedPointer<CanBusItem>& b) {
            return a->bool_ext_ide() < b->bool_ext_ide();});  }
        break;
    }
    endInsertRows();
    emit layoutChanged();
}

void CanBusTraceProperty::switchSortColumn(const int col){
    sortColumn(col, sort_dir[col]);
    sort_dir[col] = !sort_dir[col];
}

//============================ delete operations ==============================

void CanBusTraceProperty::deleteSelected(){
    uint32_t i = (count() - 1);
    do{
        if(dataPtr(i)->isSelected()) {
            removeAt(i);
        }
    }while(i--);
    emit changed();
    emit layoutChanged();
}

void CanBusTraceProperty::deleteRange(int begin, int end){
    if(count() == 0) return;
    uint32_t i = (count() - 1);
    if(begin > end){
        int tmp = begin;
        begin = end;
        end = tmp;
    }
    do{
        if((dataPtr(i)->int_id() <= end) & (dataPtr(i)->int_id() >= begin)) removeAt(i);
    }while(i--);

    emit changed();
    emit layoutChanged();
}

//============================ mass conversion operations ==============================

void CanBusTraceProperty::setAllMsgsDirection(int id, int dir){
    uint32_t i = (count() - 1);
    do{
        if((dataPtr(i)->int_id() == id)){
            dataPtr(i)->setIntCan(dir);
        }
    }while(i--);

    emit changed();
    emit layoutChanged();
}



/***********************************************************************************************
 *
 *
 *                                  CanBusMonitorProperty
 *
 * ********************************************************************************************/

int CanBusMonitorProperty::columnCount(const QModelIndex& ) const {
    return ColumnCount;
}

QVariant CanBusMonitorProperty::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole || section >= columnCount())
        return QVariant();

    return m_monitorColumnNames.at(section);
}

//------------------------- add item without a filter ---------------------------------------------------

void CanBusMonitorProperty::addItem(const QByteArray &_can_msg_data, bool validate){
    auto _item = QSharedPointer<CanBusItemMonitor>(new CanBusItemMonitor(this, _can_msg_data));

    //if(validate) if(!BusParser::validateCanMsg(_can_msg_data))return;

    if(!containsId(_item->int_id())){
        this->append(_item);
        const int last_index = count() - 1;
        m_idSet.insert(_item->int_id(), last_index);

        auto start = 0;
        auto end = count()  - 1;
        beginInsertRows(QModelIndex(), start, end );

        std::sort(this->begin(), this->end(), [](const QSharedPointer<CanBusItemMonitor>& a, const QSharedPointer<CanBusItemMonitor>& b) {
            return a->id() < b->id();});


        QList<int> idList = m_idSet.keys();
        std::sort(idList.begin(), idList.end());

        int index = 0;
        foreach (int id, idList) {
            m_idSet[id] = index++;
        }
        endInsertRows();
        emit layoutChanged();
        emit changed();
    }
    else{
        const int last_index = m_idSet.value(_item->int_id());
        QSharedPointer<CanBusItemMonitor> val_ptr = dataPtr(last_index);
        val_ptr->set_can_msg_data(CanBusItem::byteArrayToCanMsg(_can_msg_data));
    }
//    emit layoutChanged();
}

//------------------------- add item with a filter ---------------------------------------------------

void CanBusMonitorProperty::addItem(const QByteArray &_can_msg_data, const ParseFilter &filter, bool validate){
    auto _item = QSharedPointer<CanBusItemMonitor>(new CanBusItemMonitor(this, _can_msg_data));
 //   if(validate) if(!BusParser::validateCanMsg(_can_msg_data))return;

    if(filter.use_range){
        if((_item->int_id() > filter.end_id) | (_item->int_id() < filter.start_id)) return;
    }
    if(!containsId(_item->int_id())){
        this->append(_item);
        const int last_index = count() - 1;
        m_idSet.insert(_item->int_id(), last_index);

        auto start = 0;
        auto end = count()  - 1;
        beginInsertRows(QModelIndex(), start, end );

        std::sort(this->begin(), this->end(), [](const QSharedPointer<CanBusItemMonitor>& a, const QSharedPointer<CanBusItemMonitor>& b) {
            return a->id() < b->id();});


        QList<int> idList = m_idSet.keys();
        std::sort(idList.begin(), idList.end());

        int index = 0;
        foreach (int id, idList) {
            m_idSet[id] = index++;
        }
        endInsertRows();
        emit layoutChanged();
        emit changed();
    }
    else{
        const int last_index = m_idSet.value(_item->int_id());
        QSharedPointer<CanBusItemMonitor> val_ptr = dataPtr(last_index);
        val_ptr->set_can_msg_data(CanBusItem::byteArrayToCanMsg(_can_msg_data));
    }
//    emit layoutChanged();
}

