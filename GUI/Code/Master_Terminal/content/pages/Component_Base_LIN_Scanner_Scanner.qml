import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "BaseItems";
import "SimpleItems";

Rectangle {
    /********* size settings ********/
    property real buttons_width_mlt: 2.2
    property int freeMainframeSpace


    /********* colors settings ********/
    color: "transparent"
    property string st_font_color: CoreImport._Base_Color_BaseFont

    /********* values ********/
    property int width_grid_sz: (width * st_side_crop) / 10
    property int composition_side_crop: (width - (width * st_side_crop))/2

    property int vertical_gap: (freeMainframeSpace/20)/4

    property int start_id: 0
    property int end_id: 536870911

    /********* alias ********/
    readonly property int _DEVICE_OPERATION_MODE_DEFAULT: 255
    readonly property int _DEVICE_OPERATION_MODE_ON: 1
    readonly property int _DEVICE_OPERATION_MODE_OFF: 2

    property string st_start_anno: qsTr("Start");
    property string st_stop_anno: qsTr("Stop");
    property string st_trace_anno: qsTr("Trace");
    property string st_monitor_anno: qsTr("Monitor");
    property string st_clear_anno: qsTr("Clear");
    property string st_options_anno: qsTr("Options");

    function retranslateUi(){

        st_start_anno = qsTr("Start");
        st_stop_anno = qsTr("Stop");
        st_trace_anno = qsTr("Trace");
        st_monitor_anno = qsTr("Monitor");
        st_options_anno = qsTr("Options");
        st_clear_anno = qsTr("Clear");
    }

    signal sendHeight(int msg)
    function calculateHeight(){
        var total_height = 0
        for(var i = root.children.length; i > 0 ; i--) {
            if(root.children[i-1].type !== "focus_reset"){
                total_height += root.children[i-1].height
                total_height += root.children[i-1].anchors.topMargin
            }
        }
        root.height = total_height
        sendHeight(total_height)
    }

    function set_info(msg){
        memory_manager.error_status = msg
        memory_manager.error_statusChanged();
    }

    property bool options_mode: false
    function setOptionsMode(option){
        if(options_mode == false && option === true){
            options_mode = option;
        }
        else if(options_mode == true && option === false){
            options_mode = option;
        }
    }
    Connections {
        target: qmlTranslator  /* registered in root context */
        function onLanguageChanged(){
            retranslateUi();
        }
    }

    Component.onCompleted: {
        calculateHeight();
        root.forceActiveFocus();
        retranslateUi();
    }

    id: root
    width: parent.width
    height: parent.height

    property bool monitor_mode: bus_manager.monitorLinScanOn

    function setMonitorMode(option){
        if(monitor_mode == false && option === true){
            bus_manager.monitorLinScanOn = option;
            i_monitor_trace_button.st_text =  st_monitor_anno
        }
        else if(monitor_mode == true && option === false){
            bus_manager.monitorLinScanOn = option;
            i_monitor_trace_button.st_text =  st_trace_anno;
        }
    }

    BaseTableViewLINMonitor{
        id: i_monitor_table
        y: vertical_gap/4
        visible: monitor_mode
        height: options_mode ? i_id_start.y - vertical_gap : i_monitor_trace_button.y - vertical_gap
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        // << "Lin"  << "ID" << "Length" << "Data" << "Period" << "Count";
        model: bus_manager.LinBusMonitorModel /* MODEL */
        columnWidths : i_trace_table.width < 39*i_trace_table.st_font_sz?
                                            [
                                            8*st_font_sz, // "LIN"
                                            7*st_font_sz, // "ID"
                                            4*st_font_sz, // "Length"
                                            15*st_font_sz, // "Data"
                                            8*st_font_sz, // "Period"
                                            5*st_font_sz // "Count"
                                           // 19*st_font_sz
                                        ] :
                                            [
                                            8*st_font_sz, // "LIN"
                                            7*st_font_sz, // "ID"
                                            4*st_font_sz, // "Length"
                                            15*st_font_sz, // "Data"
                                            8*st_font_sz, // "Period"
                                            5*st_font_sz, // "Count"
                                            (root.width - 23*st_font_sz )
                                        ]
    }

    BaseTableViewLIN{
        id: i_trace_table
        y: vertical_gap/4
        visible: !monitor_mode
        height: options_mode ? i_id_start.y - vertical_gap : i_monitor_trace_button.y - vertical_gap
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        st_editable: true
        st_checkable: true
        st_sortable: true

        model: bus_manager.LinBusTraceModel /* MODEL */
        columnWidths : i_trace_table.width < 39*i_trace_table.st_font_sz?
                                            [
                                            2*st_font_sz,
                                            7*st_font_sz, // Time
                                            7*st_font_sz, // LIN
                                            8*st_font_sz, // ID
                                            4*st_font_sz, // DLC
                                            19*st_font_sz
                                        ] :
                                            [
                                            2*st_font_sz,
                                            7*st_font_sz,
                                            7*st_font_sz, // LIN
                                            8*st_font_sz, // ID
                                            4*st_font_sz, // DLC
                                            (root.width - 23*st_font_sz )
                                        ]

        function sortColumn(column) {
            bus_manager.switchLinSortTraceColumn(column);
        }
    }

    MltButton{
        id: i_monitor_trace_button
        x: composition_side_crop
        y: freeMainframeSpace - height -  vertical_gap
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        visible: (freeMainframeSpace != 0)
        st_button_mode: true
        st_text: monitor_mode? st_monitor_anno : st_trace_anno
        st_normal_color: monitor_mode? st_B_color :st_G_color

        function cmd(){
            root.forceActiveFocus();
            if(monitor_mode){
                setMonitorMode(false);
            }
            else{
                setMonitorMode(true);
            }
        }
    }

    property int buttonX_gap: (i_start_button.x - i_monitor_trace_button.x + i_monitor_trace_button.width)/25

    MltButton{
        id: i_options_button
        x: i_monitor_trace_button.x + i_monitor_trace_button.width + buttonX_gap
        y: i_monitor_trace_button.y
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        visible: (freeMainframeSpace != 0)

        st_button_mode: false
        st_text: st_options_anno
        st_normal_color:st_N_color
        function cmd(){
        }
    }


    MltButton{
        id: i_clear_button
        x: i_start_button.x - i_clear_button.width - buttonX_gap
        y: i_monitor_trace_button.y
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        visible: (freeMainframeSpace != 0)

        st_button_mode: true
        st_text: st_clear_anno
        st_normal_color: st_R_color
        function cmd(){
            root.forceActiveFocus();
            bus_manager.resetLinBusTraceModel();
           // bus_manager.clearSortTrace();
        }
    }

    MltButton{
        id: i_start_button
        x: root.width - width - composition_side_crop
        y: i_monitor_trace_button.y
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        visible: (freeMainframeSpace != 0)

        st_button_mode: true
        st_text: cmd_manager.AsynchRead ? st_stop_anno : st_start_anno
        st_normal_color: cmd_manager.AsynchRead ? st_G_color : st_B_color
        function cmd(){
            root.forceActiveFocus();
            if(!cmd_manager.AsynchRead){
                cmd_manager.set_LIN_mode(2, true);
                cmd_manager.start_asynch_read(3);
            }
            else{
                cmd_manager.stop_asynch_read(3);
                cmd_manager.set_LIN_mode(2, false);
            }
        }
    }

}



