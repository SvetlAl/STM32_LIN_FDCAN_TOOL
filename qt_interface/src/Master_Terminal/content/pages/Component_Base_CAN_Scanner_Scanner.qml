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

    property int st_canScanner_Mode: device_manager.canScanner_Mode
    property int st_can2Scanner_Mode: device_manager.can2Scanner_Mode

    property string st_id_range_anno: qsTr("id range");
    property string st_delete_range_anno: qsTr("Delete range");
    property string st_start_anno: qsTr("Start");
    property string st_stop_anno: qsTr("Stop");
    property string st_trace_anno: qsTr("Trace");
    property string st_monitor_anno: qsTr("Monitor");
    property string st_file_anno: qsTr("File");
    property string st_save_anno: qsTr("Save");
    property string st_load_anno: qsTr("Load");
    property string st_filename_anno: qsTr("Filename");
    property string st_clear_anno: qsTr("Clear");
    property string st_add_anno: qsTr("Add");
    property string st_delete_anno: qsTr("Delete");
    property string st_crop_rng_anno: qsTr("Crop rng");
    property string st_filter_anno: qsTr("Filter");
    property string st_options_anno: qsTr("Options");
    property string st_can1_anno: qsTr("CAN1");
    property string st_can2_anno: qsTr("CAN2");
    property string st_edit_anno: qsTr("Edit");
    property string st_crop_time_anno: qsTr("CropTime");

    property string st_hardware_filter_anno: qsTr("*see hardware id filter\n in DeviceModes");

    function retranslateUi(){
        st_id_range_anno = qsTr("id range");
        st_delete_range_anno = qsTr("Delete range");
        st_start_anno = qsTr("Start");
        st_stop_anno = qsTr("Stop");
        st_trace_anno = qsTr("Trace");
        st_monitor_anno = qsTr("Monitor");
        st_file_anno = qsTr("File");
        st_save_anno = qsTr("Save");
        st_load_anno = qsTr("Load");
        st_filename_anno = qsTr("Filename");
        st_clear_anno = qsTr("Clear");
        st_add_anno = qsTr("Add");
        st_delete_anno = qsTr("Delete");
        st_filter_anno = qsTr("Filter");
        st_options_anno = qsTr("Options");
        st_can1_anno = qsTr("CAN1");
        st_can2_anno = qsTr("CAN2");
        st_edit_anno = qsTr("Edit");
        st_crop_rng_anno = qsTr("Crop rng");
        st_crop_time_anno = qsTr("CropTime");
        st_hardware_filter_anno = qsTr("*see hardware id filter\n in DeviceModes");
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

    property bool can1_mode: true
    property bool can2_mode: true
    function setCanMode(_can1, _can2){
            if(_can1 !== can1_mode)can1_mode = _can1;
            if(_can2 !== can2_mode)can2_mode = _can2;
            bus_manager.setFilterCan(1, can1_mode);
            bus_manager.setFilterCan(2, can2_mode);
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



    property bool monitor_mode: bus_manager.monitorScanOn
    function setMonitorMode(option){
        if(monitor_mode == false && option === true){
            bus_manager.monitorScanOn = option;
            //monitor_mode = option;
            i_monitor_trace_button.st_text =  st_monitor_anno
        }
        else if(monitor_mode == true && option === false){
            bus_manager.monitorScanOn = option;
            //monitor_mode = option;
            i_monitor_trace_button.st_text =  st_trace_anno;
        }
    }

    BaseTableViewCANMonitor{
        id: i_monitor_table
        y: vertical_gap/4
        visible: monitor_mode
        height: options_mode ? i_id_start.y - vertical_gap : i_monitor_trace_button.y - vertical_gap
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        // << "CAN"  << "ID" << "DLC" << "Data" << "Period" << "Count";
        model: bus_manager.CanBusMonitorModel /* MODEL */
        columnWidths : i_trace_table.width < 39*i_trace_table.st_font_sz?
                                            [
                                            4*st_font_sz, // "CAN"
                                            8*st_font_sz, // "ID"
                                            4*st_font_sz, // "DLC"
                                            19*st_font_sz, // "Data"
                                            8*st_font_sz, // "Period"
                                            8*st_font_sz // "Count"
                                           // 19*st_font_sz
                                        ] :
                                            [
                                            4*st_font_sz, // "CAN"
                                            8*st_font_sz, // "ID"
                                            4*st_font_sz, // "DLC"
                                            19*st_font_sz, // "Data"
                                            8*st_font_sz, // "Period"
                                            8*st_font_sz, // "Count"
                                            (root.width - 23*st_font_sz )
                                        ]
    }

    BaseTableView{
        id: i_trace_table
        y: vertical_gap/4
        visible: !monitor_mode
        height: options_mode ? i_id_start.y - vertical_gap : i_monitor_trace_button.y - vertical_gap
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        st_editable: true
        st_checkable: true
        st_sortable: true
        st_2can_trace_mode: true

        model: bus_manager.CanBusTraceModel /* MODEL */
        columnWidths : i_trace_table.width < 39*i_trace_table.st_font_sz?
                                            [
                                            2*st_font_sz,
                                            7*st_font_sz, // Time
                                            4*st_font_sz, // CAN
                                            3*st_font_sz, // IDE
                                            8*st_font_sz, // ID
                                            4*st_font_sz, // DLC
                                            19*st_font_sz
                                        ] :
                                            [
                                            2*st_font_sz,
                                            7*st_font_sz,
                                            4*st_font_sz,
                                            3*st_font_sz, // IDE
                                            8*st_font_sz, // ID
                                            4*st_font_sz, // DLC
                                            (root.width - 23*st_font_sz )
                                        ]

        function sortColumn(column) {
            bus_manager.switchSortTraceColumn(column);
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

        st_button_mode: true
        st_text: st_options_anno
        st_normal_color: options_mode ? st_G_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            if(options_mode){
                setOptionsMode(false);
            }
            else if(!options_mode){
                setOptionsMode(true);
            }
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
            bus_manager.resetCanBusTraceModel();
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
                if(can1_mode){
                    cmd_manager.setDeviceValue(5, _DEVICE_OPERATION_MODE_ON);
                }
                if(can2_mode){
                    cmd_manager.setDeviceValue(6, _DEVICE_OPERATION_MODE_ON);
                }

                cmd_manager.start_asynch_read(1);
            }
            else{
                cmd_manager.stop_asynch_read(1);
                cmd_manager.setDeviceValue(5, _DEVICE_OPERATION_MODE_OFF);
                cmd_manager.setDeviceValue(6, _DEVICE_OPERATION_MODE_OFF);
                cmd_manager.setDeviceValue(5, _DEVICE_OPERATION_MODE_OFF);
                cmd_manager.setDeviceValue(6, _DEVICE_OPERATION_MODE_OFF);
                cmd_manager.setDeviceValue(5, _DEVICE_OPERATION_MODE_OFF);
                cmd_manager.setDeviceValue(6, _DEVICE_OPERATION_MODE_OFF);
            }
        }
    }

    RoundedTextInput{
        id: i_filename
        x: composition_side_crop
        y: i_monitor_trace_button.y - i_monitor_trace_button.height - vertical_gap

        //height: file_operation ? i_filename.st_height_total : 0
        width: (root.width * st_side_crop)/2
        _anno: st_filename_anno
        visible: options_mode
        _enabled: true
        _value: "trace.svtrc"
        function update_initial_value(){
            _value = a_txt_input.text;
        }
    }

    MltButton{
        id: i_save_button
        x: i_start_button.x - i_clear_button.width - buttonX_gap
        //y: i_monitor_trace_button.y
        anchors.bottom: i_filename.bottom
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        visible: options_mode

        st_button_mode: true
        st_text: st_save_anno
        st_normal_color: st_R_color
        function cmd(){
            root.forceActiveFocus();
            bus_manager.saveTrace(i_filename._value);
        }
    }
    MltButton{
        id: i_load_button
        x: root.width - width - composition_side_crop
        //y: i_monitor_trace_button.y
        anchors.bottom: i_filename.bottom
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        visible: options_mode

        st_button_mode: true
        st_text: st_load_anno
        st_normal_color: st_B_color
        function cmd(){
            root.forceActiveFocus();
            bus_manager.loadTrace(i_filename._value);
        }
    }

    Text{
        id: i_custom_cdc_threshold_label
        y: i_can1_button.y
        x: i_filename.x
        visible: options_mode
        width: i_can1_button.x -  composition_side_crop
        color: st_font_color
        text: st_hardware_filter_anno
        font.pixelSize: st_initial_item_height/2
    }


    MltButton{
        id: i_can1_button
        x: i_clear_button.x //i_start_button.x - i_clear_button.width - buttonX_gap
        y: i_filename.y - i_filename.height - vertical_gap*2
        //y: i_add_button.y
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt

        visible: options_mode
        st_button_mode: true
        st_text: st_can1_anno
        st_normal_color: can1_mode ? st_G_color :st_N_color

        function cmd(){
            root.forceActiveFocus();
            if(can1_mode && can2_mode){
                setCanMode(false, can2_mode);
            }
            else{
                setCanMode(true, can2_mode);
            }
        }
    }

    MltButton{
        id: i_can2_button
        x: i_start_button.x
        y: i_can1_button.y
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        st_button_mode: true
        visible: options_mode
        st_text: st_can2_anno
        st_normal_color: can2_mode ? st_G_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            if(can2_mode && can1_mode){
                setCanMode(can1_mode, false);
            }
            else{
                setCanMode(can1_mode, true);
            }
        }
    }



    function set_id_range(val, start){
        if(start) start_id = val;
        else end_id = val;
        if(start)i_id_start._value = "0x" + start_id.toString(16).padStart(8, "0");
        else i_id_end._value = "0x" + end_id.toString(16).padStart(8, "0");
    }
    function refresh_id_range(){
        i_id_start._value = "0x" + start_id.toString(16).padStart(8, "0");
        i_id_end._value = "0x" + end_id.toString(16).padStart(8, "0");
    }

    RoundedTextInput{
        id: i_id_start
        x: i_monitor_trace_button.x
        y: i_can1_button.y - i_can1_button.height - vertical_gap
        width: ((root.width * st_side_crop)/2.8) - composition_side_crop
        _anno: "start id"
        _enabled: true
        _value: "0x00000000"
        visible: options_mode
        a_txt_input.font.capitalization: Font.AllUppercase
        function update_initial_value(){
            var _intvalue = a_txt_input.text
            // Convert hex string to integer
            var _start_id = parseInt(_intvalue, 16);
            if(start_id !== _start_id)
                set_id_range(_start_id, true);
            else refresh_id_range();

            bus_manager.setFilterRange(start_id,end_id,false);
        }
    }


    RoundedTextInput{
        id: i_id_end
        y: i_id_start.y
        x: i_id_start.x + i_id_start.width + composition_side_crop
        width: ((root.width * st_side_crop)/2.8) - composition_side_crop
        _anno: "end id"
        _enabled: true
        _value: "0x1FFFFFFF"
        visible: options_mode
        a_txt_input.font.capitalization: Font.AllUppercase
        function update_initial_value(){
            var _intvalue = a_txt_input.text
            // Convert hex string to integer
            var _end_id = parseInt(_intvalue, 16);
            if(end_id !== _end_id)
                set_id_range(_end_id, false);
            else refresh_id_range();

            bus_manager.setFilterRange(start_id,end_id,false);
        }
    }

    MltButton{
        id: i_range_button
        x: root.width - width - composition_side_crop
        //y: i_id_start.y
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        anchors.bottom: i_id_start.bottom
        visible: options_mode

        st_button_mode: true
        st_text: st_id_range_anno
        st_normal_color: bus_manager.range_id_used ?  st_G_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            if(bus_manager.range_id_used){
                bus_manager.setFilterRange(start_id,end_id,false);
            }
            else if(!bus_manager.range_id_used){
                bus_manager.setFilterRange(start_id, end_id, true);
            }
        }
    }

}



