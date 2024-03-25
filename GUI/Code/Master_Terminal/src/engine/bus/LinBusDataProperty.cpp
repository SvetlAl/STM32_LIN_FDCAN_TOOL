#include "LinBusDataProperty.h"
//#include "BusParser.h"

/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************
 *
 *
 *                                  LinBusTraceProperty
 *
 * ********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/


/********************************************************************
 *
 *
 *                     Initialization
 *
 *
********************************************************************/

void LinBusTraceProperty::addItem(const QByteArray &data, bool validate){
    if(count() >= max_items()) return;
    auto _item = QSharedPointer<LinBusItem>(new LinBusItem(this, data));
    this->append(_item);
    emit changed();
}

void LinBusTraceProperty::addItem(const QByteArray &data, const ParseFilter &filter, bool validate){
    if(count() >= max_items()) return;

    auto _item = QSharedPointer<LinBusItem>(new LinBusItem(this, data));
    //if( !filter.m_can1 && (_item->intCan() == 1) ) return;
    //if( !filter.m_can2 && (_item->intCan() == 2) ) return;

    if(filter.use_range){
        if((_item->int_id() > filter.end_id) | (_item->int_id() < filter.start_id)) return;
    }

    this->append(_item);
    emit changed();
//    emit layoutChanged();
}


/********************************************************************
 *
 *
 *                     Data access
 *
 *
********************************************************************/

int LinBusTraceProperty::columnCount(const QModelIndex& ) const {
    return ColumnCount;
}

QVariant LinBusTraceProperty::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole || section >= columnCount())
        return QVariant();

    return m_columnNames.at(section);
}

/********************************************************************
 *
 *
 *                     Edit model
 *
 *
********************************************************************/
void LinBusTraceProperty::sortColumn(const int col, bool fromTopToBottom){
    auto start = 0;
    auto end = count()  - 1;
    beginInsertRows(QModelIndex(), start, end );

    switch (col){
    case IsSelected:{
        if(fromTopToBottom){
            std::sort(this->begin(), this->end(), LinBusItem::sortBySelection);
        }
        else{
            std::sort(this->begin(), this->end(), LinBusItem::sortBySelectionReverse);
        }
    }
        break;

    case Time:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<LinBusItem>& a, const QSharedPointer<LinBusItem>& b) {
            return a->int_time() > b->int_time();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<LinBusItem>& a, const QSharedPointer<LinBusItem>& b) {
            return a->int_time() < b->int_time();});  }
        break;

    case LIN:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<LinBusItem>& a, const QSharedPointer<LinBusItem>& b) {
            return a->lin() > b->lin();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<LinBusItem>& a, const QSharedPointer<LinBusItem>& b) {
            return a->lin() < b->lin();});  }
        break;

    case ID:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<LinBusItem>& a, const QSharedPointer<LinBusItem>& b) {
            return a->id() > b->id();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<LinBusItem>& a, const QSharedPointer<LinBusItem>& b) {
            return a->id() < b->id();});  }
        break;

    case Length:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<LinBusItem>& a, const QSharedPointer<LinBusItem>& b) {
            return a->length() > b->length();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<LinBusItem>& a, const QSharedPointer<LinBusItem>& b) {
            return a->length() < b->length();});  }
        break;

    case Data:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<LinBusItem>& a, const QSharedPointer<LinBusItem>& b) {
            return a->data() > b->data();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<LinBusItem>& a, const QSharedPointer<LinBusItem>& b) {
            return a->data() < b->data();});  }
        break;
    }

    endInsertRows();
    emit layoutChanged();
}

void LinBusTraceProperty::switchSortColumn(const int col){
    sortColumn(col, sort_dir[col]);
    sort_dir[col] = !sort_dir[col];
}

//============================ delete operations ==============================

void LinBusTraceProperty::deleteSelected(){
    uint32_t i = (count() - 1);
    do{
        if(dataPtr(i)->isSelected()) {
            removeAt(i);
        }
    }while(i--);
    emit changed();
    emit layoutChanged();
}

void LinBusTraceProperty::deleteRange(int begin, int end){
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
void LinBusTraceProperty::setAllMsgsDirection(int id, int dir){
    uint32_t i = (count() - 1);
    do{
        if((dataPtr(i)->int_id() == id)){
            dataPtr(i)->setIntLin(dir);
        }
    }while(i--);

    emit changed();
    emit layoutChanged();
}

//======================== sort functions =========================
void LinBusTraceProperty::deductTimeStamp(uint32_t tmstmp){
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

void LinBusTraceProperty::deleteTimeStampRange(int start, int end){
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

/********************************************************************
 *
 *
 *                     Class setters/getters
 *
 *
********************************************************************/
//================ Extra data. Used if a terminal sends bus message data not in one piece ==============
uint32_t LinBusTraceProperty::max_items() const{
    return m_max_items;
}

void LinBusTraceProperty::setMax_items(uint32_t newMax_items){
    if (m_max_items == newMax_items){
        return;}
    m_max_items = newMax_items;
}


/********************************************************************
 *
 *
 *                    Print and debug
 *
 *
********************************************************************/
void LinBusTraceProperty::debug() const{
    uint32_t i = (count() - 1);
    do{
        dataPtr(i)->print();
    }while(i--);
}

/********************************************************************
 *
 *
 *                     Class service
 *
 *
********************************************************************/
const QByteArray LinBusTraceProperty::get_raw_data_for_cdc(int *start_pos, int msg_count, bool circular_mode) const{
    QByteArray arr;
    const int max_pos = count() - 1;
    int pos = *start_pos;
    int messages_to_send = msg_count;
    while(messages_to_send--){
        if(pos > max_pos){// the end of a trace reached
            if(circular_mode) pos = 0;
            else{
                arr.append(LinBusItem::makeInvalidByteArray());
            }
        }
        if(pos <= max_pos){
            arr.append(raw_data(pos++));
        }
    }
    *start_pos = pos;
    return arr;
}









/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************
 *
 *
 *                                  LinBusMonitorProperty
 *
 * ********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/

/********************************************************************
 *
 *
 *                     Initialization
 *
 *
********************************************************************/

void LinBusMonitorProperty::reset(){
    m_idSet.clear();
    clear();
}

//------------------------- add item without a filter ---------------------------------------------------
void LinBusMonitorProperty::addItem(const QByteArray &_lin_msg_data, bool validate){
    auto _item = QSharedPointer<LinBusItemMonitor>(new LinBusItemMonitor(this, _lin_msg_data));

    //if(validate) if(!BusParser::validateCanMsg(_can_msg_data))return;

    if(!containsId(_item->int_id())){
        this->append(_item);
        const int last_index = count() - 1;
        m_idSet.insert(_item->int_id(), last_index);

        auto start = 0;
        auto end = count()  - 1;
        beginInsertRows(QModelIndex(), start, end );

        std::sort(this->begin(), this->end(), [](const QSharedPointer<LinBusItemMonitor>& a, const QSharedPointer<LinBusItemMonitor>& b) {
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
        QSharedPointer<LinBusItemMonitor> val_ptr = dataPtr(last_index);
        val_ptr->set_lin_msg_data(LinBusItem::byteArrayToLinMsg(_lin_msg_data));
    }
//    emit layoutChanged();
}

//------------------------- add item with a filter ---------------------------------------------------
void LinBusMonitorProperty::addItem(const QByteArray &_lin_msg_data, const ParseFilter &filter, bool validate){
    auto _item = QSharedPointer<LinBusItemMonitor>(new LinBusItemMonitor(this, _lin_msg_data));
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

        std::sort(this->begin(), this->end(), [](const QSharedPointer<LinBusItemMonitor>& a, const QSharedPointer<LinBusItemMonitor>& b) {
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
        QSharedPointer<LinBusItemMonitor> val_ptr = dataPtr(last_index);
        val_ptr->set_lin_msg_data(LinBusItem::byteArrayToLinMsg(_lin_msg_data));
    }
//    emit layoutChanged();
}

/********************************************************************
 *
 *
 *                     Static preset
 *
 *
********************************************************************/

int LinBusMonitorProperty::columnCount(const QModelIndex& ) const {
    return ColumnCount;
}

QVariant LinBusMonitorProperty::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole || section >= columnCount())
        return QVariant();

    return m_monitorColumnNames.at(section);
}


/********************************************************************
 *
 *
 *                    Data access
 *
 *
********************************************************************/


/********************************************************************
 *
 *
 *                     Class setters/getters
 *
 *
********************************************************************/
bool LinBusMonitorProperty::containsId(int id) const {
    return m_idSet.contains(id);
}





