import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "BaseItems";
import "SimpleItems";

Base {
    /********* size settings ********/
    property real buttons_width_mlt: 4.2
    property int width_grid_sz: width*st_side_crop / 10
    property int composition_side_crop: (width - (width * st_side_crop))/2

    /********* colors settings ********/
    property string st_font_color: CoreImport._Base_Color_BaseFont
    property string st_font_color2: "#FFCC22"

    /********* values ********/

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
    property string st_from_com_port_anno: qsTr("NOT FINISHED YET")
    property string st_reset_anno: qsTr("Reset")


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
        st_from_com_port_anno = qsTr("NOT FINISHED YET")
        st_reset_anno = qsTr("Reset")
    }

    Connections {
        target: qmlTranslator  /* registered in root context */
        function onLanguageChanged(){
            retranslateUi();
        }
    }
    property bool circular_injection_mode: false
    property bool can_reverse_injection_mode:  false
    property bool circular_injection_cdc_mode: false
    property bool can_reverse_injection_cdc_mode:  false


    Component.onCompleted: {
        calculateHeight();
        retranslateUi();
    }


    signal sendHeight(int msg)
    function calculateHeight(){
        var total_height = i_textfield.y + i_textfield.height

        for(var i = root.children.length; i > 0 ; i--) {
            if(root.children[i-1].type !== "focus_reset"){
                total_height += root.children[i-1].height
                total_height += root.children[i-1].anchors.topMargin
            }
        }
        root.height = total_height
        sendHeight(total_height)
    }

    id: root
    width: parent.width
    height: parent.height

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
    property int st_canInjection_Mode_CDC: device_manager.canInjection_Mode_CDC

    //================================================
    //================== USB CDC =====================
    //================================================
    Rectangle{
        id: i_from_com_port_section
        y: i_from_memchip_section.y + i_from_memchip_section.height + vertical_gap
        x: i_from_memchip_section.x
        height: (vertical_gap * 22) + ((st_initial_item_height + vertical_gap)*1)
        width: root.width * st_side_crop
        color: "transparent"
        border.color: st_font_color
        radius: 20

        Text{
            id: i_from_com_port_label
            y: 0
            x: i_from_com_port_section.radius
            width: i_from_com_port_section.width
            color: st_font_color
            text: st_from_com_port_anno
            font.pixelSize: st_initial_item_height/2
        }

        CentralButton{
            id: i_from_com_port_start_button
            anchors.horizontalCenter: i_from_com_port_section.horizontalCenter
            y: i_from_com_port_label.y + i_from_com_port_label.height + vertical_gap
            st_size: vertical_gap*16

            st_text: cmd_manager.cdc_pending ? "" : cmd_manager.AsynchRead ? st_stop_anno : st_start_anno
            st_current_color: cmd_manager.cdc_pending ? st_Y_color : cmd_manager.AsynchRead ? st_G_color : st_N_color

            function cmd(){
                if(cmd_manager.cdc_pending) return;

                if(cmd_manager.AsynchRead){
                    cmd_manager.stopCdcCanInection();
                }
                else{
                    cmd_manager.startCdcCanInection(can_reverse_injection_cdc_mode);
                }
            }
        }

        RoundedTextInput{
            id: i_from_com_port_filename
            y:  i_from_com_port_start_button.y // (i_connect_button.y + i_connect_button.height + vertical_gap*2)
            x: composition_side_crop
            width: (root.width * st_side_crop)/3  - composition_side_crop
            _anno: st_trace_file_anno
            _enabled: true
            _value: "trace.fdtrc"
            function update_initial_value(){
                _value = a_txt_input.text;
            }
        }

        MltButton{
            id: i_load_button
            x: composition_side_crop // root.width - width - composition_side_crop
            anchors.bottom: i_from_com_port_start_button.bottom
            // anchors.bottom: i_filename.bottom
            height: st_initial_item_height
            width: (root.width * st_side_crop)/3  - composition_side_crop

            st_button_mode: true
            st_text: st_load_anno
            st_normal_color: bus_manager.cdc_trace_empty ? st_R_color : st_G_color
            function cmd(){
                root.forceActiveFocus();
                bus_manager.fd_loadTrace(i_from_com_port_filename._value);
            }
        }

        MltButton{
            id: i_from_com_port_circular_button
            x: i_from_com_port_section.x + i_from_com_port_section.width - width - composition_side_crop*2 //i_filename.x
            y: i_from_com_port_start_button.y // i_filename.y + i_filename.height + vertical_gap
            height: st_initial_item_height
            width: (root.width * st_side_crop)/3  - composition_side_crop

            st_button_mode: true
            st_text: st_circular_mode_anno
            st_normal_color: circular_injection_cdc_mode ? st_Y_color : st_N_color
            function cmd(){
                root.forceActiveFocus();
                circular_injection_cdc_mode = !circular_injection_cdc_mode
                cmd_manager.cdc_circular = circular_injection_cdc_mode
            }
        }

        MltButton{
            id: i_from_com_port_can_reverse_button
            x: i_from_com_port_section.x + i_from_com_port_section.width - width - composition_side_crop*2
            anchors.bottom: i_from_com_port_start_button.bottom
            height: st_initial_item_height
            width: (root.width * st_side_crop)/3  - composition_side_crop

            st_button_mode: true
            st_text: st_reverse_anno
            st_normal_color: can_reverse_injection_cdc_mode ? st_Y_color : st_N_color
            function cmd(){
                root.forceActiveFocus();
                can_reverse_injection_cdc_mode = !can_reverse_injection_cdc_mode
            }
        }

        MltButton{
            id: i_trace_position_indicator
            x: i_load_button.x
            y: i_load_button.y + i_load_button.height + vertical_gap
            height: st_initial_item_height
            width: (root.width * st_side_crop)/3  - composition_side_crop

            st_button_mode: false
            st_text: cmd_manager.cdc_injection_pos
            st_normal_color: st_Y_color
        }

        MltButton{
            id: i_reset_button
            x: i_from_com_port_can_reverse_button.x
            anchors.bottom: i_trace_position_indicator.bottom
            height: st_initial_item_height
            width: (root.width * st_side_crop)/3  - composition_side_crop

            st_button_mode: true
            st_text: st_reset_anno
            st_normal_color: st_R_color
            function cmd(){
                root.forceActiveFocus();
                cmd_manager.cdc_injection_pos = 0;
            }
        }
    }
    //************************************************
    //****************** USB CDC *********************
    //************************************************

}












