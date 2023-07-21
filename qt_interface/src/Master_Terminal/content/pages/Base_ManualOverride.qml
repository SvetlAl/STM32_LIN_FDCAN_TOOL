import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "BaseItems";

Base {
    /********* size settings ********/

    property real buttons_width_mlt: 3.1

    /********* colors settings ********/

    /********* values ********/
    property int width_grid_sz: width*st_side_crop / 10
    property int composition_side_crop: (width - (width * st_side_crop))/2

    property int vertical_gap: height/20

    /********* alias ********/

    property string st_cmd_exch_anno: qsTr("CmdExchange");
    property string st_send_anno: qsTr("Send");
    property string st_clear_anno: qsTr("Clear");
    property string st_read_anno: qsTr("Read");
    property string st_stop_anno: qsTr("Stop");
    property string st_hex_anno: qsTr("Hex");
    property string st_ascii_anno: qsTr("Ascii");

    readonly property int _DEVICE_OPERATION_MODE_DEFAULT: 255
    readonly property int _DEVICE_OPERATION_MODE_ON: 1
    readonly property int _DEVICE_OPERATION_MODE_OFF: 2

    property int st_canScanner_Mode: device_manager.canScanner_Mode
    property int st_can2Scanner_Mode: device_manager.can2Scanner_Mode

    function retranslateUi(){
        st_cmd_exch_anno = qsTr("CmdExchange");
        st_send_anno = qsTr("Send");
        st_clear_anno = qsTr("Clear");
        st_read_anno = qsTr("Read");
        st_stop_anno = qsTr("Stop");
        st_hex_anno = qsTr("Hex");
        st_ascii_anno = qsTr("Ascii");
    }


    Connections {
        target: qmlTranslator  /* registered in root context */
        function onLanguageChanged(){
            retranslateUi();
        }
    }

    Component.onCompleted: {
        retranslateUi();
    }

    id: root
    width: parent.width
    height: parent.height

    BaseTextField{
        id: i_tx_textfield
        y: vertical_gap/4 // heigth_grid_sz / 4
        height: heigth_grid_sz * 5
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        st_text: interface_console.cached_manual_override_string
        focus: false
        editable: false

        Connections {
            target: interface_console
            function onManual_override_new_string (){
                i_tx_textfield.slide_cursor_position();
            }
        }
    }

    MltButton{
        id: i_cmd_exch_mode_button
        x: composition_side_crop
        y: i_tx_textfield.y + i_tx_textfield.height + vertical_gap/2
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt

        st_checkbox_mode: true
        st_checkbox_value: false

        st_text: st_cmd_exch_anno

        st_normal_color: st_N_color
        st_checked_color: st_G_color
    }

    MltButton{
        id: i_clear_button
        anchors.horizontalCenter: root.horizontalCenter
        y: i_cmd_exch_mode_button.y
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt

        st_button_mode: true
        st_text: st_clear_anno
        st_normal_color: st_R_color
        function cmd(){
            interface_console.reset_manual_override_string();
        }
    }
    MltButton{
        id: i_send_button
        x: root.width - width - composition_side_crop
        y: i_cmd_exch_mode_button.y
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        focus: false

        st_button_mode: true
        st_text: st_send_anno
        st_normal_color: st_G_color
        function cmd(){
            if(i_cmd_exch_mode_button.st_checkbox_value){
                cmd_manager.exchange_cmd_string(i_rx_textfield.a_txt, true, false);
            }
        }
    }

    MltButton{
        id: i_hex_button
        anchors.horizontalCenter: root.horizontalCenter
        y: (i_cmd_exch_mode_button.y + i_cmd_exch_mode_button.height + vertical_gap/2)
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt

        st_button_mode: true
        st_text: st_hex_anno
        st_normal_color: st_B_color
        function cmd(){
            if(st_text === st_hex_anno) {
                st_text = st_ascii_anno;
                i_tx_textfield.st_text = Qt.binding(function() { return interface_console.cached_manual_override_string_hex })
            }
            else{
                st_text = st_hex_anno;
                i_tx_textfield.st_text = Qt.binding(function() { return interface_console.cached_manual_override_string})
            }
        }
    }

    MltButton{
        id: i_read_button
        x: root.width - width - composition_side_crop
        y: i_hex_button.y
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt

        st_button_mode: true
        st_text: st_read_anno
        st_normal_color: st_B_color
        function cmd(){
            if(!cmd_manager.AsynchRead){
                cmd_manager.setDeviceValue(5, _DEVICE_OPERATION_MODE_ON);
                cmd_manager.setDeviceValue(6, _DEVICE_OPERATION_MODE_ON);
                cmd_manager.start_asynch_read(0);
            }
            else{
                cmd_manager.setDeviceValue(5, _DEVICE_OPERATION_MODE_OFF);
                cmd_manager.setDeviceValue(6, _DEVICE_OPERATION_MODE_OFF);
                cmd_manager.stop_asynch_read(0);
                cmd_manager.setDeviceValue(5, _DEVICE_OPERATION_MODE_OFF);
                cmd_manager.setDeviceValue(6, _DEVICE_OPERATION_MODE_OFF);
            }
        }
    }

    BaseTextField{
        id: i_rx_textfield
        y: (i_hex_button.y + i_hex_button.height + vertical_gap/2)
        height: freeMainframeSpace - y
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        focus: false
        st_text:  "@S00000A0A@E"
        editable: true

    }


}



