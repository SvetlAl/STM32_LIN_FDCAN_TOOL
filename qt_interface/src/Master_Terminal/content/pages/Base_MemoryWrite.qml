import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "BaseItems";
import "SimpleItems";

Base {
    /********* size settings ********/

    property real buttons_width_mlt: 2

    /********* colors settings ********/

    /********* values ********/
    property int width_grid_sz: width*st_side_crop / 10
    property int composition_side_crop: (width - (width * st_side_crop))/2

    property int vertical_gap: (height/20)/4

    property int operation_size: 0
    property int operation_address: 0

    function set_info(msg){
        i_status_textfield_string.st_text = msg
    }

    function set_operation_address(val){
        operation_address = val;
        i_transaction_addr_tf.st_text = operation_address.toString(10);
        i_transaction_addr._value = "0x" + operation_address.toString(16).padStart(8, "0");
        i_transaction_addr.a_txt_input.text = i_transaction_addr._value;
    }
    function refresh_operation_address(){
        i_transaction_addr_tf.st_text = operation_address.toString(10);
        i_transaction_addr._value = "0x" + operation_address.toString(16).padStart(8, "0");
        i_transaction_addr.a_txt_input.text = i_transaction_addr._value;
    }

    function set_operation_size(val){
        operation_size = val;
        i_transaction_size_tf.st_text = operation_size.toString(10);
        i_transaction_size._value = "0x" + operation_size.toString(16).padStart(4, "0");
        i_transaction_size.a_txt_input.text = i_transaction_size._value;
    }
    function refresh_operation_size(){
        i_transaction_size_tf.st_text = operation_size.toString(10);
        i_transaction_size._value = "0x" + operation_size.toString(16).padStart(4, "0");
        i_transaction_size.a_txt_input.text = i_transaction_size._value;
    }


    /********* alias ********/

    property string st_addr_anno: qsTr("Address");
    property string st_size_anno: qsTr("Size");
    property string st_append_anno: qsTr("Append");
    property string st_send_file_anno: qsTr("Send File");
    property string st_write_anno: qsTr("Write");
    property string st_clear_anno: qsTr("Clear");
    property string st_filename_anno: qsTr("Filename");

    property string st_please_wait_anno: qsTr("Please wait...");
    property string st_write_error_anno: qsTr("Write Error.");
    property string st_write_ok_anno: qsTr("Write OK.");


    function retranslateUi(){
        st_append_anno = qsTr("Append");
        st_send_file_anno = qsTr("Send File");
        st_read_anno: qsTr("Write");
        st_clear_anno: qsTr("Clear");
        st_addr_anno = qsTr("Address");
        st_size_anno = qsTr("Size");
        st_filename_anno = qsTr("Filename");
        st_please_wait_anno = qsTr("Please wait...");
        st_write_error_anno = qsTr("Write Error.");
        st_write_ok_anno = qsTr("Write OK.");
    }

    Connections {
        target: qmlTranslator  /* registered in root context */
        function onLanguageChanged(){
            retranslateUi();
        }
    }

    Component.onCompleted: {
        root.forceActiveFocus();
        retranslateUi();
    }

    id: root
    width: parent.width
    height: parent.height

/*
    BaseTableView{
        id: i_tx_textfield_table
        y: vertical_gap/4
        visible: true
        height: i_view_button.y - vertical_gap
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter

        model: memory_manager.FlashSpi_DataModel
    }
*/
    BaseTextField{
        id: i_rx_textfield_string
        y: vertical_gap/4
        visible: true
        height: i_status_textfield_string.y - vertical_gap
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        st_text: ""
        editable: true
        function cmd(){
            root.forceActiveFocus();
            set_operation_size(a_txt.length);
            refresh_operation_size();
        }
    }

    BaseTextField{
        id: i_status_textfield_string
        y: i_append_button.y - i_append_button.height - vertical_gap
        visible: true
        height: st_initial_item_height
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        st_text: ""
        editable: false
        function cmd(){
        }
    }


    MltButton{
        id: i_append_button
        x: composition_side_crop
        y: i_filename.y - i_filename.height - vertical_gap
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt

        visible: true

        st_checkbox_mode: true
        st_checkbox_value: false

        st_text: st_append_anno
        st_normal_color: st_N_color
        st_checked_color: st_G_color

        function chkbx_cmd(){
            console.log(st_checkbox_value);
            root.forceActiveFocus();
        }
    }

    property int buttonX_gap: (i_write_button.x - i_append_button.x + i_append_button.width)/20

    MltButton{
        id: i_send_file_button
        x: i_append_button.x + i_append_button.width + buttonX_gap
        y: i_append_button.y
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        st_button_mode: true
        visible: true
        st_text: st_send_file_anno
        st_normal_color: st_B_color
        function cmd(){
            root.forceActiveFocus();
            set_info(st_please_wait_anno);
          //  delay(300);
            if(i_status_textfield_string.st_text == st_please_wait_anno){
                if(cmd_manager.writeRawData(operation_address, serialport_config.filename_to_send, true, i_append_button.st_checkbox_value)){
                    set_info(st_write_ok_anno);
                }
                else set_info(st_write_error_anno);
            }
        }
    }

    MltButton{
        id: i_clear_button
        x: i_write_button.x - i_clear_button.width - buttonX_gap
        y: i_append_button.y
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt

        st_button_mode: true
        st_text: st_clear_anno
        st_normal_color: st_R_color
        function cmd(){
            root.forceActiveFocus();
            i_rx_textfield_string.a_txt = "";
            set_operation_address(0);
        }
    }
    MltButton{
        id: i_write_button
        x: root.width - width - composition_side_crop
        y: i_append_button.y
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt

        st_button_mode: true
        st_text: st_write_anno
        st_normal_color: st_G_color
        function cmd(){
            root.forceActiveFocus();
            if(operation_size!=0)
                cmd_manager.writeRawData(operation_address, i_rx_textfield_string.a_txt, false, i_append_button.st_checkbox_value);
        }
    }

    RoundedTextInput{
        id: i_filename
        y: i_transaction_addr.y - i_transaction_addr.height - vertical_gap
        x: composition_side_crop
        width: (root.width * st_side_crop)
        _anno: st_filename_anno
        _enabled: true
        _value: serialport_config.filename_to_send
        function update_initial_value(){
            _value = a_txt_input.text;
            serialport_config.filename_to_send = _value;
        }
    }




    RoundedTextInput{
        id: i_transaction_addr
        y: i_transaction_size.y - i_transaction_size.height - vertical_gap
        x: composition_side_crop
        width: ((root.width * st_side_crop)/2) - composition_side_crop
        _anno: st_addr_anno
        _enabled: true
        _value: "0x00000000"
        a_txt_input.font.capitalization: Font.AllUppercase
        function update_initial_value(){
            var _intvalue = a_txt_input.text
            // Convert hex string to integer
            var _operation_address = parseInt(_intvalue, 16);
              // Check if operation_address is a multiple of 16
            if(operation_address !== _operation_address)
                set_operation_address(_operation_address);
            else refresh_operation_address();
        }
    }


    BaseTextField{
        id: i_transaction_addr_tf
     //   y: i_transaction_size_tf.y - i_transaction_size_tf.height - vertical_gap
        anchors.bottom: i_transaction_addr.bottom
        x: root.width - width - composition_side_crop
        height: i_transaction_size.height*0.8
        width: ((root.width * st_side_crop)/2) - composition_side_crop
        st_text: "0"
        editable: true
        function cmd(){
            var _value = parseInt(a_txt, 10);
            if(operation_address !== _value)
                set_operation_address(_value);
             else refresh_operation_address();
        }

    }

    RoundedTextInput{
        id: i_transaction_size
        y:freeMainframeSpace - height -  vertical_gap
        x: composition_side_crop
        width: ((root.width * st_side_crop)/2) - composition_side_crop
        _anno: st_size_anno
        _enabled: true
        _value: "0x0000"
        visible: (freeMainframeSpace != 0)
        a_txt_input.font.capitalization: Font.AllUppercase
        function update_initial_value(){
            var _intvalue = a_txt_input.text
            var _operation_size = parseInt(_intvalue, 16);
            if(operation_size !== _operation_size)
                set_operation_size(_operation_size);
            else refresh_operation_size();
        }
    }

    BaseTextField{
        id: i_transaction_size_tf
        anchors.bottom: i_transaction_size.bottom
        // y: freeMainframeSpace - height -  vertical_gap
        x: root.width - width - composition_side_crop
        height: i_transaction_size.height*0.8
        width: ((root.width * st_side_crop)/2) - composition_side_crop
        st_text: "000"
        editable: true
        visible: i_transaction_size.visible
        function cmd(){
            var _value = parseInt(a_txt, 10);
            if(operation_size !== _value)
                set_operation_size(_value);
        }
    }

}



