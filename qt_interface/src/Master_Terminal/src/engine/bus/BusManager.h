#ifndef BUSMANAGER_H
#define BUSMANAGER_H

#include <QObject>
#include <QDebug>
#include "BusDataProperty.h"
//#include "BusParser.h"
#include "ParseBuffer.h"
#include <QFile>




class BusManager : public QObject{
    Q_OBJECT

    /******************************************************************************************/
    /*                       Trace and monitor models                                         */
    /******************************************************************************************/
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



public:
    static inline const QByteArray default_init_data = "4001000000000000000000000008000000000000000000";

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
    bool getMonitorScanOn() const;
    void setMonitorScanOn(bool newMonitorScanOn);
    bool cdc_trace_empty(){return (CanBusTraceModel()->count() == 0);}

    /******************************************************************************************/
    /*                                    Scanner filters                                     */
    /******************************************************************************************/

    Q_INVOKABLE void setFilterCan(const int can_num, bool isEnabled);  // Select CAN1/CAN2 for scanner
    Q_INVOKABLE void setFilterRange(const int start, const int end, bool isEnabled); // Set CAN Id filters for scanner
    bool range_id_used(); // Is id filter enabled?
    void set_range_id_used(bool val); // Enable/disable Id filter

    /******************************************************************************************/
    /*                                    Trace interface                                     */
    /******************************************************************************************/

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

    /******************************************************************************************/
    /******************************************************************************************/
    /*                                                                                        */
    /*                                 Aux trace/monitor                                      */
    /*                                                                                        */
    /******************************************************************************************/
    /******************************************************************************************/
    Q_INVOKABLE void loadAuxTrace(const QString &filename);
    int aux_trace_size() const;



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
    /*
    void startScanThread();
    void stopScanThread();
*/


    /******************************************************************************************/
    /*                                   Setters/getters                                      */
    /******************************************************************************************/
    CanBusTraceProperty *CanBusTraceModel(){return &m_CanBusTraceModel;}
    CanBusMonitorProperty *CanBusMonitorModel(){return &m_CanBusMonitorModel;}


signals:
    void use_range_changed();
    void max_TraceItems_Changed();
    void aux_trace_sizeChanged();
    void cdc_trace_emptyChanged();


    void monitorScanOnChanged();

public slots:
    /******************************************************************************************/
    /*                          On asynch scanner data recieved                               */
    /******************************************************************************************/

    bool processIncomingData(const QByteArray _data);

    void resetCanBusTraceModel(){
        m_CanBusTraceModel.clear();
        m_CanBusMonitorModel.reset();
    }

private:
    CanBusTraceProperty m_CanBusTraceModel;
    CanBusMonitorProperty m_CanBusMonitorModel;

    CanBusTraceProperty m_CanBusTraceModelAux;
    CanBusMonitorProperty m_CanBusMonitorModelAux;


    ParseFilter m_parse_filter;
    ParseBuffer m_parse_buffer;

    bool traceScanOn = false;
    bool monitorScanOn = true;

};

#endif // BUSMANAGER_H

