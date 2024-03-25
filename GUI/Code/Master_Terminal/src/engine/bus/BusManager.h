#ifndef BUSMANAGER_H
#define BUSMANAGER_H

/***********************************************************************
 * BusManager <== CanBusTraceProperty     <==  CanBusItem
 *            <== CanBusMonitorProperty   <==  CanBusItemMonitor
 *
 *   CanBusTraceProperty *CanBusTraceModel(){return &m_CanBusTraceModel;}
 *   CanBusMonitorProperty *CanBusMonitorModel(){return &m_CanBusMonitorModel;}
 *
 *
 ************************************************************************/

#include <QObject>
#include <QDebug>
#include "BusDataProperty.h"
#include "FDCAN_BusDataProperty.h"
#include "LinBusDataProperty.h"
//#include "BusParser.h"
#include "ParseBuffer.h"
#include <QFile>


class BusManager : public QObject{
    Q_OBJECT

    /******************************************************************************************/
    /*                       Trace and monitor models                                         */
    /******************************************************************************************/

    //===================================== Standart CAN =======================================
    //=========== is current configuration monitor or trace ===========
    Q_PROPERTY(bool monitorScanOn READ getMonitorScanOn WRITE setMonitorScanOn NOTIFY monitorScanOnChanged)

    Q_PROPERTY(CanBusTraceProperty* CanBusTraceModel READ CanBusTraceModel CONSTANT)
    Q_PROPERTY(QString max_can_trace_items READ max_TraceItems WRITE setMaxTraceItems NOTIFY max_TraceItems_Changed)
    Q_PROPERTY(bool cdc_trace_empty READ cdc_trace_empty NOTIFY cdc_trace_emptyChanged)

    //=========== Monitor model===========
    Q_PROPERTY(CanBusMonitorProperty* CanBusMonitorModel READ CanBusMonitorModel CONSTANT)

    //=========== Trace and Monitor filter ===========
    Q_PROPERTY(bool range_id_used READ range_id_used WRITE set_range_id_used NOTIFY use_range_changed)

    //=========== Aux trace and monitor ===========
    Q_PROPERTY(int aux_trace_size READ aux_trace_size NOTIFY aux_trace_sizeChanged)


    //=====================================    FD CAN    ========================================
    //=========== is current configuration monitor or trace ===========
    Q_PROPERTY(bool fd_monitorScanOn READ fd_getMonitorScanOn WRITE fd_setMonitorScanOn NOTIFY fd_monitorScanOnChanged)

    Q_PROPERTY(FDCAN_CanBusTraceProperty* FdCanBusTraceModel READ FdCanBusTraceModel CONSTANT)
    Q_PROPERTY(QString fd_max_can_trace_items READ fd_max_TraceItems WRITE fd_setMaxTraceItems NOTIFY fd_max_TraceItems_Changed)
    Q_PROPERTY(bool fd_cdc_trace_empty READ fd_cdc_trace_empty NOTIFY fd_cdc_trace_emptyChanged)

    //=========== Monitor model===========
    Q_PROPERTY(FDCAN_CanBusMonitorProperty* FdCanBusMonitorModel READ FdCanBusMonitorModel CONSTANT)

    //=========== Trace and Monitor filter ===========
    Q_PROPERTY(bool fd_range_id_used READ fd_range_id_used WRITE fd_set_range_id_used NOTIFY fd_use_range_changed)

    //=========== Aux trace and monitor ===========
    Q_PROPERTY(int fd_aux_trace_size READ fd_aux_trace_size NOTIFY fd_aux_trace_sizeChanged)


    //========================================= LIN bus =========================================
    Q_PROPERTY(LinBusTraceProperty* LinBusTraceModel READ LinBusTraceModel CONSTANT)
    Q_PROPERTY(LinBusMonitorProperty* LinBusMonitorModel READ LinBusMonitorModel CONSTANT)
    //=========== is current configuration monitor or trace ===========
    Q_PROPERTY(bool monitorLinScanOn READ getMonitorLinScanOn WRITE setMonitorLinScanOn NOTIFY monitorLinScanOnChanged)


public:
    //===================================== Standart CAN =======================================
    static inline const QByteArray default_init_data    = "4001000000000000000000000008000000000000000000";
    static inline const QByteArray fd_default_init_data = "23010000000000000000000100000000";

    explicit BusManager(QObject *parent = 0){
    }
    ~BusManager() {};

    /******************************************************************************************/
    /******************************************************************************************/
    /*                                                                                        */
    /*                          Trace and monitor handling                                    */
    /*                                                                                        */
    /******************************************************************************************/
    /******************************************************************************************/

    //===================================== Standart CAN =======================================
    bool getMonitorScanOn() const;
    void setMonitorScanOn(bool newMonitorScanOn);
    bool cdc_trace_empty(){return (CanBusTraceModel()->count() == 0);}

    //=====================================    FD CAN    ========================================
    bool fd_getMonitorScanOn() const;
    void fd_setMonitorScanOn(bool newMonitorScanOn);
    bool fd_cdc_trace_empty(){return (FdCanBusTraceModel()->count() == 0);}


    //========================================= LIN ============================================
    bool getMonitorLinScanOn() const;
    void setMonitorLinScanOn(bool newMonitorScanOn);

    /******************************************************************************************/
    /*                                    Scanner filters                                     */
    /******************************************************************************************/

    //===================================== Standart CAN =======================================
    Q_INVOKABLE void setFilterCan(const int can_num, bool isEnabled);  // Select CAN1/CAN2 for scanner
    Q_INVOKABLE void setFilterRange(const int start, const int end, bool isEnabled); // Set CAN Id filters for scanner
    bool range_id_used(); // Is id filter enabled?
    void set_range_id_used(bool val); // Enable/disable Id filter

    //=====================================    FD CAN    ========================================
    Q_INVOKABLE void fd_setFilterCan(const int can_num, bool isEnabled);  // Select CAN1/CAN2 for scanner
    Q_INVOKABLE void fd_setFilterRange(const int start, const int end, bool isEnabled); // Set CAN Id filters for scanner
    bool fd_range_id_used(); // Is id filter enabled?
    void fd_set_range_id_used(bool val); // Enable/disable Id filter

    /******************************************************************************************/
    /*                                    Trace interface                                     */
    /******************************************************************************************/

    //===================================== Standart CAN =======================================
    Q_INVOKABLE void createNewTraceItem(const QString &newItem, bool _default);
    Q_INVOKABLE void saveTrace(const QString &filename);
    Q_INVOKABLE void loadTrace(const QString &filename);
    Q_INVOKABLE void sortTraceColumn(const int col, bool fromTopToBottom = true);
    Q_INVOKABLE void switchSortTraceColumn(const int col);
    Q_INVOKABLE void clearSortTrace();
    Q_INVOKABLE void deleteSelectedTrace();
    Q_INVOKABLE void deleteRangeTrace(int begin, int end);
    Q_INVOKABLE void setTraceIdDirection(int id, int can_n);

    Q_INVOKABLE void cropTime();
    Q_INVOKABLE void deleteTimeRangeTrace(const QString &begin, const QString &end);

    const QString max_TraceItems() const;
    void setMaxTraceItems(const QString &newMax_items);

    //=====================================    FD CAN    ========================================
    Q_INVOKABLE void fd_createNewTraceItem(const QString &newItem, bool _default);
    Q_INVOKABLE void fd_saveTrace(const QString &filename);
    Q_INVOKABLE void fd_loadTrace(const QString &filename);
    Q_INVOKABLE void fd_sortTraceColumn(const int col, bool fromTopToBottom = true);
    Q_INVOKABLE void fd_switchSortTraceColumn(const int col);
    Q_INVOKABLE void fd_clearSortTrace();
    Q_INVOKABLE void fd_deleteSelectedTrace();
    Q_INVOKABLE void fd_deleteRangeTrace(int begin, int end);
    Q_INVOKABLE void fd_setTraceIdDirection(int id, int can_n);

    Q_INVOKABLE void fd_cropTime();
    Q_INVOKABLE void fd_deleteTimeRangeTrace(const QString &begin, const QString &end);

    const QString fd_max_TraceItems() const;
    void fd_setMaxTraceItems(const QString &newMax_items);

    //========================================= LIN ============================================
    Q_INVOKABLE void sortLinTraceColumn(const int col, bool fromTopToBottom = true);
    Q_INVOKABLE void switchLinSortTraceColumn(const int col);
    Q_INVOKABLE void clearLinSortTrace();

    /******************************************************************************************/
    /******************************************************************************************/
    /*                                                                                        */
    /*                                 Aux trace/monitor                                      */
    /*                                                                                        */
    /******************************************************************************************/
    /******************************************************************************************/

    //===================================== Standart CAN =======================================
    Q_INVOKABLE void loadAuxTrace(const QString &filename);
    int aux_trace_size() const;

    //=====================================    FD CAN    ========================================
    Q_INVOKABLE void fd_loadAuxTrace(const QString &filename);
    int fd_aux_trace_size() const;

    /******************************************************************************************/
    /******************************************************************************************/
    /*                                                                                        */
    /*                          Override and discard filters                                  */
    /*                                                                                        */
    /******************************************************************************************/
    /******************************************************************************************/

    /******************************************************************************************/
    /*                                    Scanner filters                                     */
    /******************************************************************************************/



    /******************************************************************************************/
    /******************************************************************************************/
    /*                                                                                        */
    /*                          Serial data reading and parsing                               */
    /*                                                                                        */
    /******************************************************************************************/
    /******************************************************************************************/

    /******************************************************************************************/
    /*                                       Start/stop                                       */
    /******************************************************************************************/


    /******************************************************************************************/
    /*                                   Setters/getters                                      */
    /******************************************************************************************/

    //===================================== Standart CAN =======================================
    CanBusTraceProperty *CanBusTraceModel(){return &m_CanBusTraceModel;}
    CanBusMonitorProperty *CanBusMonitorModel(){return &m_CanBusMonitorModel;}

    //=====================================    FD CAN    ========================================
    FDCAN_CanBusTraceProperty *FdCanBusTraceModel(){return &m_FdCanBusTraceModel;}
    FDCAN_CanBusMonitorProperty *FdCanBusMonitorModel(){return &m_FdCanBusMonitorModel;}

    //========================================= LIN ============================================
    LinBusTraceProperty *LinBusTraceModel(){return &m_LinBusTraceModel;}
    LinBusMonitorProperty *LinBusMonitorModel(){return &m_LinBusMonitorModel;}



signals:
    //===================================== Standart CAN =======================================
    void use_range_changed();
    void max_TraceItems_Changed();
    void aux_trace_sizeChanged();
    void cdc_trace_emptyChanged();

    //=====================================    FD CAN    ========================================
    void fd_use_range_changed();
    void fd_max_TraceItems_Changed();
    void fd_aux_trace_sizeChanged();
    void fd_cdc_trace_emptyChanged();

    //===================================== Standart CAN =======================================
    void monitorScanOnChanged();
    //=====================================    FD CAN    ========================================
    void fd_monitorScanOnChanged();
    //========================================= LIN ============================================
    void monitorLinScanOnChanged();

public slots:
    /******************************************************************************************/
    /*                          On asynch scanner data recieved                               */
    /******************************************************************************************/

    //===================================== Standart CAN ========================================
    bool processIncomingData(const QByteArray _data);
    //=====================================    FD CAN    ========================================
    bool fd_processIncomingData(const QByteArray _data);

    //=========================================== LIN ===========================================
    bool processLinIncomingData(const QByteArray _data);

    //===================================== Standart CAN ========================================
    void resetCanBusTraceModel(){
        m_CanBusTraceModel.clear();
        m_CanBusMonitorModel.reset();
    }
    //=====================================    FD CAN    ========================================
    void fd_resetCanBusTraceModel(){
        m_FdCanBusTraceModel.clear();
        m_FdCanBusMonitorModel.reset();
    }
    //========================================= LIN ============================================
    void resetLinBusTraceModel(){
        m_LinBusTraceModel.clear();
        m_LinBusMonitorModel.reset();
    }

private:
    //===================================== Standart CAN ========================================
    CanBusTraceProperty m_CanBusTraceModel;
    CanBusMonitorProperty m_CanBusMonitorModel;

    CanBusTraceProperty m_CanBusTraceModelAux;
    CanBusMonitorProperty m_CanBusMonitorModelAux;

    ParseFilter m_parse_filter;
    ParseBuffer m_parse_buffer;

    bool traceScanOn = false;
    bool monitorScanOn = true;

    //======================================== FD CAN ===========================================
    FDCAN_CanBusTraceProperty m_FdCanBusTraceModel;
    FDCAN_CanBusMonitorProperty m_FdCanBusMonitorModel;

    FDCAN_CanBusTraceProperty m_FdCanBusTraceModelAux;
    FDCAN_CanBusMonitorProperty m_FdCanBusMonitorModelAux;

    ParseFilter m_fd_parse_filter;
    FDCAN_ParseBuffer m_fd_parse_buffer;

    bool fd_traceScanOn = false;
    bool fd_monitorScanOn = true;


    //========================================= LIN ============================================
    LinBusTraceProperty m_LinBusTraceModel;
    LinBusMonitorProperty m_LinBusMonitorModel;

    LinParseBuffer m_lin_parse_buffer;

    bool traceLinScanOn = false;
    bool monitorLinScanOn = true;

};

#endif // BUSMANAGER_H

