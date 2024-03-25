#include "FDCAN_BusDataProperty.h"
//#include "BusParser.h"

/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************
 *
 *
 *                                  CanBusTraceProperty
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

void FDCAN_CanBusTraceProperty::addItem(const QByteArray &data_hdr, const QByteArray &data_data, bool validate){
    if(count() >= max_items()) return;
    auto _item = QSharedPointer<FDCAN_CanBusItem>(new FDCAN_CanBusItem(this, data_hdr, data_data));
    this->append(_item);
    emit changed();
}

void FDCAN_CanBusTraceProperty::addItem(const QByteArray &data_hdr, const QByteArray &data_data, const ParseFilter &filter, bool validate){
    if(count() >= max_items()) return;

    auto _item = QSharedPointer<FDCAN_CanBusItem>(new FDCAN_CanBusItem(this, data_hdr, data_data));
    if( !filter.m_can1 && (_item->intCan() == 1) ) return;
    if( !filter.m_can2 && (_item->intCan() == 2) ) return;

    if(filter.use_range){
        if((_item->int_id() > filter.end_id) | (_item->int_id() < filter.start_id)) return;
    }

    this->append(_item);
    emit changed();
}


/********************************************************************
 *
 *
 *                     Data access
 *
 *
********************************************************************/

int FDCAN_CanBusTraceProperty::columnCount(const QModelIndex& ) const {
    return ColumnCount;
}

QVariant FDCAN_CanBusTraceProperty::headerData(int section, Qt::Orientation orientation, int role) const {
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
void FDCAN_CanBusTraceProperty::sortColumn(const int col, bool fromTopToBottom){
    auto start = 0;
    auto end = count()  - 1;

    emit layoutAboutToBeChanged();
    beginInsertRows(QModelIndex(), start, end );

    switch (col){
    case IsSelected:{
        if(fromTopToBottom){
            std::sort(this->begin(), this->end(), FDCAN_CanBusItem::sortBySelection);
        }
        else{
            std::sort(this->begin(), this->end(), FDCAN_CanBusItem::sortBySelectionReverse);
        }
    }
        break;

    case Time:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b) {
            return a->int_time() > b->int_time();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b) {
            return a->int_time() < b->int_time();});  }
        break;

    case CAN:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b) {
            return a->intCan() > b->intCan();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b) {
            return a->intCan() < b->intCan();});  }
        break;

    case ID:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b) {
            return a->int_id() > b->int_id();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b) {
            return a->int_id() < b->int_id();});  }
        break;

    case DLC:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b) {
            return a->int_dlc() > b->int_dlc();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b) {
            return a->int_dlc() < b->int_dlc();});  }
        break;

    case Data:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b) {
            return a->data() > b->data();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b) {
            return a->data() < b->data();});  }
        break;

    case XTD:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b) {
            return a->XTDflag() > b->XTDflag();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b) {
            return a->XTDflag() < b->XTDflag();});  }
        break;

    case ESI:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b) {
            return a->ESIflag() > b->ESIflag();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b) {
            return a->ESIflag() < b->ESIflag();});  }
        break;

    case BRS:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b) {
            return a->BRSflag() > b->BRSflag();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b) {
            return a->BRSflag() < b->BRSflag();});  }
        break;

    case FDF:{
        if(fromTopToBottom){
        std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b) {
            return a->FDFflag() > b->FDFflag();});
        }
        else std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItem>& a, const QSharedPointer<FDCAN_CanBusItem>& b) {
            return a->FDFflag() < b->FDFflag();});  }
        break;

    default:
        break;
    }
    endInsertRows();
    emit layoutChanged();
}

void FDCAN_CanBusTraceProperty::switchSortColumn(const int col){
    sortColumn(col, sort_dir[col]);
    sort_dir[col] = !sort_dir[col];
}

//============================ delete operations ==============================

void FDCAN_CanBusTraceProperty::deleteSelected(){
    uint32_t i = (count() - 1);
    do{
        if(dataPtr(i)->isSelected()) {
            removeAt(i);
        }
    }while(i--);
    emit changed();
    emit layoutChanged();
}

void FDCAN_CanBusTraceProperty::deleteRange(int begin, int end){
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
void FDCAN_CanBusTraceProperty::setAllMsgsDirection(int id, int dir){
    uint32_t i = (count() - 1);
    do{
        if((dataPtr(i)->int_id() == id)){
            dataPtr(i)->setIntCan(dir);
        }
    }while(i--);

    emit changed();
    emit layoutChanged();
}

//======================== sort functions =========================
void FDCAN_CanBusTraceProperty::deductTimeStamp(uint32_t tmstmp){
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

void FDCAN_CanBusTraceProperty::deleteTimeStampRange(int start, int end){
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
uint32_t FDCAN_CanBusTraceProperty::max_items() const{
    return m_max_items;
}

void FDCAN_CanBusTraceProperty::setMax_items(uint32_t newMax_items){
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
void FDCAN_CanBusTraceProperty::debug() const{
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
const QByteArray FDCAN_CanBusTraceProperty::get_raw_data_for_cdc(int *start_pos, int msg_count, bool circular_mode) const{
    QByteArray arr;
    const int max_pos = count() - 1;
    int pos = *start_pos;
    int messages_to_send = msg_count;
    while(messages_to_send--){
        if(pos > max_pos){// the end of a trace reached
            if(circular_mode) pos = 0;
            else{
                arr.append(FDCAN_CanBusItem::makeInvalidByteArray());
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
 *                                  CanBusMonitorProperty
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

void FDCAN_CanBusMonitorProperty::reset(){
    m_idSet.clear();
    clear();
}

//------------------------- add item without a filter ---------------------------------------------------
void FDCAN_CanBusMonitorProperty::addItem(const QByteArray &_can_msg_hdr, const QByteArray &_can_msg_data, bool validate){
    auto _item = QSharedPointer<FDCAN_CanBusItemMonitor>(new FDCAN_CanBusItemMonitor(this, _can_msg_hdr, _can_msg_data));

    if(!containsId(_item->int_id())){
        this->append(_item);
        const int last_index = count() - 1;
        m_idSet.insert(_item->int_id(), last_index);

        auto start = 0;
        auto end = count()  - 1;
        beginInsertRows(QModelIndex(), start, end );

        std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItemMonitor>& a, const QSharedPointer<FDCAN_CanBusItemMonitor>& b) {
            return a->int_id() < b->int_id();});


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
        int last_index = m_idSet.value(_item->int_id());
        QSharedPointer<FDCAN_CanBusItemMonitor> val_ptr = dataPtr(last_index);
        val_ptr->set_fdcan_msg_hdr_and_data(FDCAN_CanBusItem::byteArrayToFDCanHdr(_can_msg_hdr), _can_msg_data);
    }
//    emit layoutChanged();
}

//------------------------- add item with a filter ---------------------------------------------------
void FDCAN_CanBusMonitorProperty::addItem(const QByteArray &_can_msg_hdr, const QByteArray &_can_msg_data, const ParseFilter &filter, bool validate){
    auto _item = QSharedPointer<FDCAN_CanBusItemMonitor>(new FDCAN_CanBusItemMonitor(this, _can_msg_hdr, _can_msg_data));

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

        std::sort(this->begin(), this->end(), [](const QSharedPointer<FDCAN_CanBusItemMonitor>& a, const QSharedPointer<FDCAN_CanBusItemMonitor>& b) {
            return a->int_id() < b->int_id();});



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
        QSharedPointer<FDCAN_CanBusItemMonitor> val_ptr = dataPtr(last_index);
        val_ptr->set_fdcan_msg_hdr_and_data(FDCAN_CanBusItem::byteArrayToFDCanHdr(_can_msg_hdr), _can_msg_data);
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

int FDCAN_CanBusMonitorProperty::columnCount(const QModelIndex& ) const {
    return ColumnCount;
}

QVariant FDCAN_CanBusMonitorProperty::headerData(int section, Qt::Orientation orientation, int role) const {
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
bool FDCAN_CanBusMonitorProperty::containsId(int id) const {
    return m_idSet.contains(id);
}





