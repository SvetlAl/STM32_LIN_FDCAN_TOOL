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

    property int operation_size: 4096
    property int operation_address: 1351680

    /********* alias ********/

    property string st_addr_anno: qsTr("Address");
    property string st_size_anno: qsTr("Size");

    property string st_view_anno: qsTr("View");
    property string st_save_anno: qsTr("Save");
    property string st_read_anno: qsTr("Read");
    property string st_clear_anno: qsTr("Clear");
    property string st_filename_anno: qsTr("Filename");

    property string st_please_wait_anno: qsTr("Please wait...");
    property string st_read_ok_anno: qsTr("Read OK.");

    function retranslateUi(){
        st_view_anno = qsTr("View");
        st_save_anno = qsTr("Save");
        st_read_anno: qsTr("Read");
        st_clear_anno: qsTr("Clear");
        st_addr_anno = qsTr("Address");
        st_size_anno = qsTr("Size");
        st_filename_anno = qsTr("Filename");
        st_please_wait_anno = qsTr("Please wait...");
        st_read_ok_anno = qsTr("Read OK.");
    }

    function set_info(msg){
        memory_manager.error_status = msg
        memory_manager.error_statusChanged();

    }

    Connections {
        target: qmlTranslator  /* registered in root context */
        function onLanguageChanged(){
            retranslateUi();
        }
    }

    Connections {
        target: cmd_manager  /* registered in root context */
        function onMemoryReadProgressSend(msg){
            i_status_textfield_string.st_text = msg;
        }
    }


    Component.onCompleted: {
        root.forceActiveFocus();
        retranslateUi();
    }

    id: root
    width: parent.width
    height: parent.height


    BaseTableView{
        id: i_tx_textfield_table
        y: vertical_gap/4
        visible: true
        height: i_status_textfield_string.y - vertical_gap
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter

        model: memory_manager.FlashSpi_DataModel /* MODEL */
    }

    BaseTextField{
        id: i_tx_textfield_string
        y: vertical_gap/4
        visible: false
        height: i_status_textfield_string.y - vertical_gap
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        st_text: ""
        editable: false
    }

    BaseTextField{
        id: i_status_textfield_string
        y: i_view_button.y - i_view_button.height - vertical_gap
        visible: true
        height: st_initial_item_height
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        st_text: memory_manager.error_status
        editable: false
        function cmd(){
        }
    }


    MltButton{
        id: i_view_button
        x: composition_side_crop
        y: i_filename.y - i_filename.height - vertical_gap
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt

        st_button_mode: true
        st_text: st_view_anno
        st_normal_color: st_G_color

        function cmd(){
            root.forceActiveFocus();
            if(i_tx_textfield_table.visible){
                i_tx_textfield_table.visible = false;
                i_tx_textfield_string.visible = true;
                i_tx_textfield_string.st_text = memory_manager.string_from_FlashSpiMemoryData();
                st_normal_color = st_G_color
            }
            else{
                i_tx_textfield_table.visible = true;
                i_tx_textfield_string.visible = false;
                st_normal_color = st_B_color
            }
        }
    }

    property int buttonX_gap: (i_read_button.x - i_view_button.x + i_view_button.width)/20

    MltButton{
        id: i_save_button
        x: i_view_button.x + i_view_button.width + buttonX_gap
        y: i_view_button.y
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        st_button_mode: true
        visible: true
        st_text: st_save_anno
        st_normal_color: st_B_color
        function cmd(){
            root.forceActiveFocus();
            memory_manager.write_FlashSpiMemoryData_into_file(serialport_config.filename_recieved);
        }
    }

    MltButton{
        id: i_clear_button
        x: i_read_button.x - i_clear_button.width - buttonX_gap
        y: i_view_button.y
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt

        st_button_mode: true
        st_text: st_clear_anno
        st_normal_color: st_R_color
        function cmd(){
            root.forceActiveFocus();
            memory_manager.resetFlashSpi_DataModel();
        }
    }
    MltButton{
        id: i_read_button
        x: root.width - width - composition_side_crop
        y: i_view_button.y
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt

        st_button_mode: true
        st_text: st_read_anno
        st_normal_color: st_G_color
        function cmd(){
            if(operation_size!=0){
                set_info(st_please_wait_anno);
                root.forceActiveFocus();
                cmd_manager.readMemoryData(operation_address, operation_size);
            }
        }

    }

    RoundedTextInput{
        id: i_filename
        y: i_transaction_addr.y - i_transaction_addr.height - vertical_gap
        x: composition_side_crop
        width: (root.width * st_side_crop)
        _anno: st_filename_anno
        _enabled: true
        _value: serialport_config.filename_recieved
        function update_initial_value(){
            _value = a_txt_input.text;
            serialport_config.filename_recieved = _value;
        }
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


    RoundedTextInput{
        id: i_transaction_addr
        y: i_transaction_size.y - i_transaction_size.height - vertical_gap
        x: composition_side_crop
        width: ((root.width * st_side_crop)/2) - composition_side_crop
        _anno: st_addr_anno
        _enabled: true
        _value: "0x0014A000"
        a_txt_input.font.capitalization: Font.AllUppercase
        function update_initial_value(){
            var _intvalue = a_txt_input.text
            // Convert hex string to integer
            var _operation_address = parseInt(_intvalue, 16);
              // Check if operation_address is a multiple of 16
            if (_operation_address % 16 != 0) {
                // Round up to the nearest multiple of 16
                _operation_address = (_operation_address - (_operation_address % 16));
            }
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
        st_text: "1351680"
        editable: true
        function cmd(){
            var _value = parseInt(a_txt, 10);
            if (_value % 16 != 0) {
                // Round up to the nearest multiple of 16
                _value = (_value - (_value % 16));
            }
            if(operation_address !== _value)
                set_operation_address(_value);
             else refresh_operation_address();
        }

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


    RoundedTextInput{
        id: i_transaction_size
        y:freeMainframeSpace - height -  vertical_gap
        x: composition_side_crop
        width: ((root.width * st_side_crop)/2) - composition_side_crop
        _anno: st_size_anno
        _enabled: true
        _value: "0x1000"
        visible: (freeMainframeSpace != 0)
        a_txt_input.font.capitalization: Font.AllUppercase
        function update_initial_value(){
            var _intvalue = a_txt_input.text
            // Convert hex string to integer
            var _operation_size = parseInt(_intvalue, 16);
              // Check if operation_address is a multiple of 16
            if (_operation_size % 16 != 0) {
                // Round up to the nearest multiple of 16
                _operation_size = (_operation_size - (_operation_size % 16));
            }
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
        st_text: "4096"
        editable: true
        visible: i_transaction_size.visible
        function cmd(){
            var _value = parseInt(a_txt, 10);
            if (_value % 16 != 0) {
                // Round up to the nearest multiple of 16
                _value = (_value - (_value % 16));
            }
            if(operation_size !== _value)
                set_operation_size(_value);
             else refresh_operation_size();
        }
    }

}



