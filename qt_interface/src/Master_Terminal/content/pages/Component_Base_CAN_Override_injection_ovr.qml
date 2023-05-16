


import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "BaseItems";
import "SimpleItems";

Rectangle {
    /********* size settings ********/
    property real buttons_width_mlt: 4.2

    /********* colors settings ********/

    /********* values ********/
    property int width_grid_sz: width*st_side_crop / 10
    property int composition_side_crop: (width - (width * st_side_crop))/2

    property int vertical_gap: st_initial_item_height/5
    /********* alias ********/

    /********* translated ********/
    property string st_load_anno: qsTr("Load trace");
    property string st_circular_mode_anno: qsTr("Circular mode");
    property string st_start_anno: qsTr("Start");
    property string st_stop_anno: qsTr("Stop");
    property string st_reverse_anno: qsTr("Reverse CAN1/CAN2");
    property string st_trace_file_anno: qsTr("Trace filename");
    property string st_write_anno: qsTr("Write to Memchip");

    property string st_description_anno: qsTr("1. Place a trace file into the app root directory or create your own using CAN scanner page. \n 2. Load the file into the device memory chip. If it's already written into memory, skip this step. \n 3. Select injection mode (circular or single shot). \n 4. Press start/stop.");


    function retranslateUi(){
        st_load_anno = qsTr("Load trace");
        st_circular_mode_anno = qsTr("Circular mode");
        st_start_anno = qsTr("Start");
        st_stop_anno = qsTr("Stop");
        st_reverse_anno = qsTr("Reverse CAN1/CAN2");
        st_trace_file_anno = qsTr("Trace filename");
        st_write_anno = qsTr("Write to Memchip");
        st_description_anno = qsTr("1. Place a trace file into the app root directory or create your own using CAN scanner page. \n 2. Load the file into the device memory chip. If it's already written into memory, skip this step. \n 3. Select injection mode (circular or single shot). \n 4. Press start/stop.");
    }

    Connections {
        target: qmlTranslator  /* registered in root context */
        function onLanguageChanged(){
            retranslateUi();
        }
    }
    property bool circular_injection_mode: false
    property bool can_reverse_injection_mode:  false


    Component.onCompleted: {
        calculateHeight();
        retranslateUi();
    }


    signal sendHeight(int msg)
    function calculateHeight(){
        var total_height = i_textfield.y + i_textfield.height
        /*
        for(var i = root.children.length; i > 0 ; i--) {
            if(root.children[i-1].type !== "focus_reset"){
                total_height += root.children[i-1].height
                total_height += root.children[i-1].anchors.topMargin
            }
        }*/
        root.height = total_height
        sendHeight(total_height)
    }

    id: root
    width: parent.width
    height: parent.height
    color: "transparent"

    readonly property int _DEVICE_OPERATION_MODE_DEFAULT: 255
    readonly property int _DEVICE_OPERATION_MODE_ON: 1
    readonly property int _DEVICE_OPERATION_MODE_OFF: 2
    readonly property int _DEVICE_OPERATION_MODE_REV: 3
    readonly property int _DEVICE_OPERATION_MODE_CIRCULAR_REV: 4
    readonly property int _DEVICE_OPERATION_MODE_CIRCULAR: 5

    property int st_canGateway_Mode: device_manager.canGateway_Mode
    property int st_calibratorFilter_Mode: device_manager.calibratorFilter_Mode
    property int st_canOverride_Mode: device_manager.canOverride_Mode
    property int st_canScanner_Mode: device_manager.canScanner_Mode
    property int st_can2Scanner_Mode: device_manager.can2Scanner_Mode
    property int st_memoryPrograming_Mode: device_manager.memoryPrograming_Mode
    property int st_canInjection_Mode: device_manager.canInjection_Mode

    CentralButton{
        id: i_connect_button
        anchors.horizontalCenter: root.horizontalCenter
        y: vertical_gap
        st_size: vertical_gap*32

        st_text: st_canInjection_Mode !== _DEVICE_OPERATION_MODE_OFF ? st_stop_anno : st_start_anno
        st_current_color: st_canInjection_Mode !== _DEVICE_OPERATION_MODE_OFF ? st_G_color : st_N_color

        function cmd(){
            if((st_canInjection_Mode != _DEVICE_OPERATION_MODE_OFF) && (st_canInjection_Mode != _DEVICE_OPERATION_MODE_DEFAULT))
                cmd_manager.setDeviceValue(8, _DEVICE_OPERATION_MODE_OFF);
            else if(circular_injection_mode & !can_reverse_injection_mode) cmd_manager.setDeviceValue(8, _DEVICE_OPERATION_MODE_CIRCULAR);
            else if(!circular_injection_mode & can_reverse_injection_mode) cmd_manager.setDeviceValue(8, _DEVICE_OPERATION_MODE_REV);
            else if(!circular_injection_mode & !can_reverse_injection_mode) cmd_manager.setDeviceValue(8, _DEVICE_OPERATION_MODE_ON);
            else if(circular_injection_mode & can_reverse_injection_mode) cmd_manager.setDeviceValue(8, _DEVICE_OPERATION_MODE_CIRCULAR_REV)
        }
    }

    RoundedTextInput{
        id: i_filename
        y: (i_connect_button.y + i_connect_button.height + vertical_gap*2)
        x: composition_side_crop
        width: (root.width * st_side_crop)/2.1
        _anno: st_trace_file_anno
        _enabled: true
        _value: "trace.svtrc"
        function update_initial_value(){
            _value = a_txt_input.text;
        }
    }
/*
    MltButton{
        id: i_load_button
        anchors.horizontalCenter: root.horizontalCenter
        anchors.bottom: i_filename.bottom
        height: st_initial_item_height
        width: (root.width * st_side_crop)/3

        st_button_mode: true
        st_text: st_load_anno
        st_normal_color: st_B_color
        function cmd(){
            root.forceActiveFocus();
            bus_manager.loadTrace(i_filename._value);
        }
    }
*/
    MltButton{
        id: i_write_button
        x: root.width - width - composition_side_crop
        anchors.bottom: i_filename.bottom
        height: st_initial_item_height
        width: (root.width * st_side_crop)/2.1

        st_button_mode: true
        st_text: st_write_anno
        st_normal_color: st_R_color
        function cmd(){
            root.forceActiveFocus();
            cmd_manager.writeRawData(CoreImport._FREE_MEMSPACE_ADDRESS, i_filename._value , true, false);
            //bus_manager.loadTrace(i_filename._value);
        }
    }

    MltButton{
        id: i_circular_button
        x: i_filename.x
        y: i_filename.y + i_filename.height + vertical_gap
        //anchors.bottom: i_filename.bottom
        height: st_initial_item_height
        width: (root.width * st_side_crop)/2.1

        st_button_mode: true
        st_text: st_circular_mode_anno
        st_normal_color: circular_injection_mode ? st_Y_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            circular_injection_mode = !circular_injection_mode
        }
    }

    MltButton{
        id: i_can_reverse_button
        x: i_write_button.x
        y: i_write_button.y + i_write_button.height + vertical_gap
        height: st_initial_item_height
        width: (root.width * st_side_crop)/2.1

        st_button_mode: true
        st_text: st_reverse_anno
        st_normal_color: can_reverse_injection_mode ? st_Y_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            can_reverse_injection_mode = !can_reverse_injection_mode
        }
    }

    BaseTextField{
        id: i_textfield
        y: (i_circular_button.y + i_circular_button.height + vertical_gap)
        height: vertical_gap * 64
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        st_text: st_description_anno
    }


}












