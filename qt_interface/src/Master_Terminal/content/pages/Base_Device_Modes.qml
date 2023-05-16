import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "BaseItems";
import "SimpleItems";

Base {
    /********* size settings ********/
    property real buttons_width_mlt: 3.5
    property int width_grid_sz: width*st_side_crop / 10
    /********* colors settings ********/

    /********* values ********/

    property int composition_side_crop: (width - (width * st_side_crop))/2
    property int vertical_gap: height/20

    /********* alias ********/
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

    property string st_memchip_name: device_manager.memchip_name


    property bool circular_injection_mode: false
    property bool can_reverse_injection_mode:  false


    Connections {
        target: device_manager  /* registered in root context */
        function onChanged(){
            st_canGateway_Mode = device_manager.canGateway_Mode;
            st_calibratorFilter_Mode = device_manager.calibratorFilter_Mode;
            st_canOverride_Mode = device_manager.canOverride_Mode;
            st_canScanner_Mode = device_manager.canScanner_Mode;
            st_can2Scanner_Mode = device_manager.can2Scanner_Mode;
            st_memoryPrograming_Mode = device_manager.memoryPrograming_Mode
        }
    }
    Connections {
        target: device_manager  /* registered in root context */
        function onMemchip_changed(){
            st_memchip_name = device_manager.memchip_name;
        }
    }
    Component.onCompleted: {
    }

    /********* translated ********/
    property string st_memchip_name_anno: qsTr("Memory chip")
    property string st_save_button_text: qsTr("Save")
    property string st_calibrator_button_text: qsTr("Calibrator")
    property string st_can_gateway_button_text: qsTr("CAN gateway")
    property string st_1can_scanner_button_text: qsTr("1CAN scanner")
    property string st_2can_scanner_button_text: qsTr("2CAN scanner")
    property string st_can_override_button_text: qsTr("CAN override")
    property string st_memory_programm_button_text: qsTr("MemProgramm Mode")

    property string st_trace_injection_button_text: qsTr("Trace injection")
    property string st_reverse_button_text: qsTr("Reverse CAN1/CAN2")
    property string st_circular_button_text: qsTr("Circular")

    function retranslateUi(){
        st_memchip_name_anno = qsTr("Memory chip")
        st_save_button_text = qsTr("Save")
        st_calibrator_button_text = qsTr("Calibrator")
        st_can_gateway_button_text = qsTr("CAN gateway")
        st_1can_scanner_button_text = qsTr("1CAN scanner")
        st_2can_scanner_button_text = qsTr("2CAN scanner")
        st_can_override_button_text = qsTr("CAN override")
        st_memory_programm_button_text = qsTr("MemProgramm Mode")

        st_trace_injection_button_text = qsTr("Trace injection")
        st_reverse_button_text = qsTr("Reverse CAN1/CAN2")
        st_circular_button_text = qsTr("Circular")
    }

    MltButton{
        id: i_save_button
        x: composition_side_crop
        anchors.bottom: i_memchip_name.bottom

        height: st_initial_item_height
        width: ((root.width * st_side_crop)/2) - vertical_gap

        st_button_mode: true
        st_text: st_save_button_text
        st_normal_color: st_G_color
        function cmd(){
            cmd_manager.saveDeviceStatus();
        }
    }

    RoundedTextInput{
        id: i_memchip_name
        y: root.y + vertical_gap
        x: root.width - width - composition_side_crop
        width: ((root.width * st_side_crop)/2)
        _anno: st_memchip_name_anno
        _enabled: false
        _value: st_memchip_name
        a_txt_input.font.capitalization: Font.AllUppercase
        function update_initial_value(){
        }
    }

    MltButton{
        id: i_can_gateway_button
        x: composition_side_crop
        y: i_save_button.y + i_save_button.height + vertical_gap
        height: st_initial_item_height
        width: ((root.width * st_side_crop)/2) - vertical_gap
        st_button_mode: (st_canGateway_Mode == _DEVICE_OPERATION_MODE_DEFAULT) ? false : true
        st_text: st_can_gateway_button_text
        st_normal_color: (st_canGateway_Mode == _DEVICE_OPERATION_MODE_ON) ? st_G_color : st_N_color
        function cmd(){
            if(st_canGateway_Mode == _DEVICE_OPERATION_MODE_ON)
                cmd_manager.setDeviceValue(1, _DEVICE_OPERATION_MODE_OFF);
            else cmd_manager.setDeviceValue(1, _DEVICE_OPERATION_MODE_ON);
        }
    }

    MltButton{
        id: i_calibrator_button
        x: root.width - width - composition_side_crop
        y: i_can_gateway_button.y
        height: st_initial_item_height
        width: ((root.width * st_side_crop)/2) - vertical_gap
        st_button_mode: (st_calibratorFilter_Mode == _DEVICE_OPERATION_MODE_DEFAULT) ? false : true
        st_normal_color: (st_calibratorFilter_Mode == _DEVICE_OPERATION_MODE_ON) ? st_G_color : st_N_color
        st_text: st_calibrator_button_text
        function cmd(){
            if(st_calibratorFilter_Mode == _DEVICE_OPERATION_MODE_ON)
                cmd_manager.setDeviceValue(3, _DEVICE_OPERATION_MODE_OFF);
            else cmd_manager.setDeviceValue(3, _DEVICE_OPERATION_MODE_ON);
        }
    }

    MltButton{
        id: i_1can_scanner_button
        x: composition_side_crop
        y: i_can_gateway_button.y + i_can_gateway_button.height + vertical_gap
        height: st_initial_item_height
        width: ((root.width * st_side_crop)/2) - vertical_gap
        st_button_mode: (st_canScanner_Mode == _DEVICE_OPERATION_MODE_DEFAULT) ? false : true
        st_normal_color: (st_canScanner_Mode == _DEVICE_OPERATION_MODE_ON) ? st_G_color : st_N_color
        st_text: st_1can_scanner_button_text
        function cmd(){
            if(st_canScanner_Mode == _DEVICE_OPERATION_MODE_ON)
                cmd_manager.setDeviceValue(5, _DEVICE_OPERATION_MODE_OFF);
            else cmd_manager.setDeviceValue(5, _DEVICE_OPERATION_MODE_ON);
        }
    }

    MltButton{
        id: i_2can_scanner_button
        x: root.width - width - composition_side_crop
        y: i_1can_scanner_button.y
        height: st_initial_item_height
        width: ((root.width * st_side_crop)/2) - vertical_gap
        st_button_mode: (st_can2Scanner_Mode == _DEVICE_OPERATION_MODE_DEFAULT) ? false : true
        st_normal_color: (st_can2Scanner_Mode == _DEVICE_OPERATION_MODE_ON) ? st_G_color : st_N_color
        st_text: st_2can_scanner_button_text
        function cmd(){
            if(st_can2Scanner_Mode == _DEVICE_OPERATION_MODE_ON)
                cmd_manager.setDeviceValue(6, _DEVICE_OPERATION_MODE_OFF);
            else cmd_manager.setDeviceValue(6, _DEVICE_OPERATION_MODE_ON);
        }
    }

    MltButton{
        id: i_can_override_button
        x: composition_side_crop
        y: i_1can_scanner_button.y + i_1can_scanner_button.height + vertical_gap
        height: st_initial_item_height
        width: ((root.width * st_side_crop)/2) - vertical_gap
        st_button_mode: (st_canOverride_Mode == _DEVICE_OPERATION_MODE_DEFAULT) ? false : true
        st_normal_color: (st_canOverride_Mode == _DEVICE_OPERATION_MODE_ON) ? st_G_color : st_N_color
        st_text: st_can_override_button_text
        function cmd(){
            if(st_canOverride_Mode == _DEVICE_OPERATION_MODE_ON)
                cmd_manager.setDeviceValue(4, _DEVICE_OPERATION_MODE_OFF);
            else cmd_manager.setDeviceValue(4, _DEVICE_OPERATION_MODE_ON);
        }
    }

    MltButton{
        id: i_memprogramm_button
        x: root.width - width - composition_side_crop
        y: i_can_override_button.y
        height: st_initial_item_height
        width: ((root.width * st_side_crop)/2) - vertical_gap
        visible: true
        st_button_mode: false
        st_text: st_memory_programm_button_text
        st_normal_color: (st_memoryPrograming_Mode == _DEVICE_OPERATION_MODE_ON) ? st_Y_color : st_N_color
        function cmd(){
        }
    }

    MltButton{
        id: i_trace_injection_button
        x: composition_side_crop
        y: i_can_override_button.y + i_can_override_button.height + vertical_gap
        height: st_initial_item_height
        width: (root.width * st_side_crop)*0.30
        st_button_mode: (st_canInjection_Mode == _DEVICE_OPERATION_MODE_DEFAULT) ? false : true
        st_normal_color: ((st_canInjection_Mode != _DEVICE_OPERATION_MODE_OFF) && (st_canInjection_Mode != _DEVICE_OPERATION_MODE_DEFAULT)) ? st_G_color : st_N_color
        st_text: st_trace_injection_button_text
        function cmd(){
            if((st_canInjection_Mode != _DEVICE_OPERATION_MODE_OFF) && (st_canInjection_Mode != _DEVICE_OPERATION_MODE_DEFAULT))
                cmd_manager.setDeviceValue(8, _DEVICE_OPERATION_MODE_OFF);
            else if(circular_injection_mode & !can_reverse_injection_mode) cmd_manager.setDeviceValue(8, _DEVICE_OPERATION_MODE_CIRCULAR);
            else if(!circular_injection_mode & can_reverse_injection_mode) cmd_manager.setDeviceValue(8, _DEVICE_OPERATION_MODE_REV);
            else if(!circular_injection_mode & !can_reverse_injection_mode) cmd_manager.setDeviceValue(8, _DEVICE_OPERATION_MODE_ON);
            else if(circular_injection_mode & can_reverse_injection_mode) cmd_manager.setDeviceValue(8, _DEVICE_OPERATION_MODE_CIRCULAR_REV)
        }
    }



    MltButton{
        id: i_circular_injection_button
        anchors.horizontalCenter: parent.horizontalCenter
        //x: i_trace_injection_button.x + i_trace_injection_button.width + composition_side_crop
        y: i_trace_injection_button.y
        height: st_initial_item_height
        width: (root.width * st_side_crop)*0.30
        st_button_mode: true
        st_normal_color: circular_injection_mode ? st_Y_color : st_N_color
        st_text: st_circular_button_text
        function cmd(){
            circular_injection_mode = !circular_injection_mode
        }
    }

    MltButton{
        id: i_can_reverse_button
        x: root.width - width - composition_side_crop
        y: i_trace_injection_button.y
        height: st_initial_item_height
        width: (root.width * st_side_crop)*0.30
        st_button_mode: true
        st_normal_color: can_reverse_injection_mode ? st_Y_color : st_N_color
        st_text: st_reverse_button_text
        function cmd(){
            can_reverse_injection_mode = !can_reverse_injection_mode
        }
    }


}
