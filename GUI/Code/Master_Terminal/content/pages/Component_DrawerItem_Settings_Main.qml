import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "SimpleItems";

Item {
    /********* size settings ********/
    property int st_item_height: CoreImport._ViewScale_Height_Container
    property int st_item_font_sz: st_item_height/3
    property int st_max_displayed_cbx_items: 3
    property int st_item_width: root.width/3
    property int st_vertical_margin: CoreImport._ViewScale_Height_Container - (CoreImport._ViewScale_Height_Container * CoreImport._GeneralDesign_Ratio_ScreenAdjVertContainerCrop)

    readonly property real st_slider_height_mlt: 1.3
    /********* colors settings ********/
    property string st_clr_text: CoreImport._SimpleItems_Color_ButtonText /**/
    /********* values ********/

    /********* alias ********/

    /********* translated ********/
  //  property string st_custom_baudrate_text_edit_text: qsTr("User value")
    property string st_custom_baudrate_chkbox_text: qsTr("Custom")
    property string st_com_port_text: qsTr("COM port")
    property string st_baudrate_text: qsTr("Baud Rate")
    property string st_databits_text: qsTr("Data Bits")
    property string st_stopbits_text: qsTr("Stop Bits")
    property string st_parity_text: qsTr("Parity")
    property string st_flowcontrol_text: qsTr("Flow Control")

    property string st_Cdc_write_timeout_text: qsTr("CDC write timeout")
    property string st_Cdc_read_timeout_text: qsTr("CDC read timeout")
    property string st_Cdc_cmd_process_timeout_text: qsTr("CDC command process timeout")
    property string st_Cdc_Jni_drv_timeout_text: qsTr("Android driver timeout")
    property string st_Cdc_busy_cmd_trials_text: qsTr("Trials count for BSY response")

    property string st_max_TX_bytes_text: qsTr("Max TX bytes per request")
    property string st_max_RX_bytes_text: qsTr("Max RX bytes per request")

    property string st_version_info_url_text: qsTr("V. Info url")
    property string st_update_url_text: qsTr("Update url")
    property string st_code_override_url_text: qsTr("Code override")

    property string st_max_bus_trace_text: qsTr("Max CAN trace items")


    function retranslateUi() {
      //  st_custom_baudrate_text_edit_text = qsTr("User value")
        st_custom_baudrate_chkbox_text = qsTr("Custom")
        st_com_port_text = qsTr("COM port")
        st_baudrate_text = qsTr("Baud Rate")
        st_databits_text = qsTr("Data Bits")
        st_stopbits_text = qsTr("Stop Bits")
        st_parity_text = qsTr("Parity")
        st_flowcontrol_text = qsTr("Flow Control")
        st_Cdc_write_timeout_text = qsTr("CDC write timeout")
        st_Cdc_read_timeout_text = qsTr("CDC read timeout")
        st_Cdc_cmd_process_timeout_text = qsTr("CDC command process timeout")
        st_Cdc_Jni_drv_timeout_text = qsTr("Android driver timeout")
        st_Cdc_busy_cmd_trials_text = qsTr("Trials count for BSY response")
        st_max_TX_bytes_text = qsTr("Max TX bytes per request")
        st_max_RX_bytes_text = qsTr("Max RX bytes per request")
        st_version_info_url_text = qsTr("V. Info url")
        st_update_url_text = qsTr("Update url")
        st_code_override_url_text = qsTr("Code override")
        st_max_bus_trace_text = qsTr("Max CAN trace items")
    }


    id: root
    width: parent.width
  //  height:  parent.height

    Connections {
        target: qmlTranslator
        function onLanguageChanged(){
            retranslateUi()
        }
    }

    signal sendHeight(int msg)

    function calculateHeight(){
        var total_length = 0;
        for(var i = 0; i < root.children.length ; i++) {
            total_length += root.children[i].height;
            total_length += root.children[i].anchors.topMargin;
        }
        height = total_length
        sendHeight(total_length);
    }

    MouseArea{
        property string type: "focus_reset"
        anchors.fill: root
        onClicked: {
            root.forceActiveFocus()
        }
    }

    Component.onCompleted:{
        retranslateUi();
        set_font_sz();
        calculateHeight();
    }
    onWidthChanged: {
        set_font_sz();
     //   calculateHeight();
    }

    function calculate_min_font_sz(){
        var sz = 1000;
        for(var i = 0; i < root.children.length ; i++) {
            if(root.children[i].st_font_resize === true & root.children[i].st_font_pixelSize_info < sz)sz = root.children[i].st_font_pixelSize_info;
        }
        return sz;
    }

    function set_font_sz(){
        for(var i = 0; i < root.children.length ; i++) {
            if(root.children[i].st_font_resize === true)root.children[i].st_font_pixelSize = root.children[i].st_initial_font_pixelSize;
        }
        var sz = calculate_min_font_sz();

        for(var l = 0; l < root.children.length ; l++) {
            if(root.children[l].st_font_resize === true)root.children[l].st_font_pixelSize = sz;
        }
    }


    Module_CBX_Annotated{
        id: i_com_port_cbx
        width: root.width
        height: st_item_height
        st_item_width: root.st_item_width
        st_item_height: root.st_item_height
        st_txt: st_com_port_text
        _model: serialport_config.portnames
        a_cbx_start_index: _model.current_index;
    }
    Module_CBX_Annotated{
        id: i_baudrate_cbx
        width: root.width
        height: st_item_height
        anchors.top: i_com_port_cbx.bottom
        anchors.topMargin: st_item_height/5
        st_item_width: root.st_item_width
        st_item_height: root.st_item_height
        st_txt: st_baudrate_text
        _model: serialport_config.baudrate
        a_cbx_start_index: _model.current_index;
    }
    /******************************   Custom   **************************************/
    RoundedTextInput{
        id: i_custom_baudrate_inputBx
        parent: root
        anchors.top: i_baudrate_cbx.bottom
        _anno: st_custom_baudrate_chkbox_text
        _enabled: i_baudrate_cbx.a_cbx_txt == "Custom" ? true : false
        _value: serialport_config.baudrate.custom_value
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[0-9]{1,6}$/
        }
        function update_initial_value(){
            serialport_config.baudrate.custom_value = i_custom_baudrate_inputBx.a_txt_input.text
        }
    }
    Module_CBX_Annotated{
        id: i_stopbits_cbx
        width: root.width
        height: st_item_height
        anchors.top: i_custom_baudrate_inputBx.bottom
        anchors.topMargin: st_item_height/5
        st_item_width: root.st_item_width
        st_item_height: root.st_item_height
        st_txt: st_stopbits_text
        _model: serialport_config.stopbits
        a_cbx_start_index: _model.current_index;
    }
    Module_CBX_Annotated{
        id: i_databits_cbx
        width: root.width
        height: st_item_height
        anchors.top: i_stopbits_cbx.bottom
        anchors.topMargin: st_item_height/5
        st_item_width: root.st_item_width
        st_item_height: root.st_item_height
        st_txt: st_databits_text
        _model: serialport_config.databits
        a_cbx_start_index: _model.current_index;
    }
    Module_CBX_Annotated{
        id: i_flowcontrol_cbx
        width: root.width
        height: st_item_height
        anchors.top: i_databits_cbx.bottom
        anchors.topMargin: st_item_height/5
        st_item_width: root.st_item_width
        st_item_height: root.st_item_height
        st_txt: st_flowcontrol_text
        _model: serialport_config.flowcontrol
        a_cbx_start_index: _model.current_index;
    }

    Module_CBX_Annotated{
        id: i_parity_cbx
        width: root.width
        height: st_item_height
        anchors.top: i_flowcontrol_cbx.bottom
        anchors.topMargin: st_item_height/5
        st_item_width: root.st_item_width
        st_item_height: root.st_item_height
        st_txt: st_parity_text
        _model: serialport_config.parity
        a_cbx_start_index: _model.current_index;
    }

    RoundedSliderAnnotated{
        id: i_Cdc_write_timeout
        parent: root
        height: st_item_height * st_slider_height_mlt
        anchors.top: i_parity_cbx.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Cdc_write_timeout_text
        a_slider._from: 1
        a_slider._to: 360
        a_slider._step: 1
        a_slider._value: serialport_config.Cdc_write_timeout
        function a_update_initial_value() {
            serialport_config.Cdc_write_timeout = a_slider._value
        }
    }

    RoundedSliderAnnotated{
        id: i_Cdc_read_timeout
        parent: root
        height: st_item_height * st_slider_height_mlt
        anchors.top: i_Cdc_write_timeout.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Cdc_read_timeout_text
        a_slider._from: 1
        a_slider._to: 360
        a_slider._step: 1
        a_slider._value: serialport_config.Cdc_read_timeout
        function a_update_initial_value() {
            serialport_config.Cdc_read_timeout = a_slider._value
        }
    }

    RoundedSliderAnnotated{
        id: i_Cdc_cmd_process_timeout
        parent: root
        height: st_item_height * st_slider_height_mlt
        anchors.top: i_Cdc_read_timeout.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Cdc_cmd_process_timeout_text
        a_slider._from: 1
        a_slider._to: 360
        a_slider._step: 1
        a_slider._value: serialport_config.Cdc_cmd_process_timeout
        function a_update_initial_value() {
            serialport_config.Cdc_cmd_process_timeout = a_slider._value
        }
    }

    RoundedSliderAnnotated{
        id: i_Cdc_Jni_drv_timeout
        parent: root
        height: st_item_height * st_slider_height_mlt
        anchors.top: i_Cdc_cmd_process_timeout.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Cdc_Jni_drv_timeout_text
        a_slider._value: serialport_config.Cdc_Jni_drv_timeout
        a_slider._from: 1
        a_slider._to: 360
        a_slider._step: 1
        function a_update_initial_value() {
            serialport_config.Cdc_Jni_drv_timeout = a_slider._value
        }
    }

    RoundedSliderAnnotated{
        id: i_Cdc_busy_cmd_trials
        parent: root
        height: st_item_height * st_slider_height_mlt
        anchors.top: i_Cdc_Jni_drv_timeout.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Cdc_busy_cmd_trials_text
        a_slider._from: 1
        a_slider._to: 36
        a_slider._step: 1
        a_slider._value: serialport_config.Cdc_busy_cmd_trials
        function a_update_initial_value() {
            serialport_config.Cdc_busy_cmd_trials = a_slider._value
        }
    }

    RoundedSliderAnnotated{
        id: i_max_TX_bytes
        parent: root
        height: st_item_height * st_slider_height_mlt
        anchors.top: i_Cdc_busy_cmd_trials.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_max_TX_bytes_text
        a_slider._from: 64
        a_slider._to: 2048
        a_slider._step: 64
        a_slider._value: serialport_config.max_transmit_data_per_request
        function a_update_initial_value() {
            serialport_config.max_transmit_data_per_request = a_slider._value
        }
    }

    RoundedSliderAnnotated{
        id: i_max_RX_bytes
        parent: root
        height: st_item_height * st_slider_height_mlt
        anchors.top: i_max_TX_bytes.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_max_RX_bytes_text
        a_slider._from: 64
        a_slider._to: 2048
        a_slider._step: 64
        a_slider._value: serialport_config.max_recieve_data_per_request
        function a_update_initial_value() {
            serialport_config.max_recieve_data_per_request = a_slider._value
        }
    }

    RoundedTextInput{
        id: i_version_info_url
        st_height_total: CoreImport._ViewScale_Height_Container * 4
        parent: root
        anchors.top: i_max_RX_bytes.bottom
        _anno: st_version_info_url_text
        _enabled: true
        _value: webConfig.version_info_url
        a_txt_input.wrapMode: Text.WrapAnywhere
        a_txt_input.font.pixelSize: (CoreImport._ViewScale_Height_Container)/2
        a_text_small.font.pixelSize: (CoreImport._ViewScale_Height_Container)/3
        function update_initial_value(){
            webConfig.version_info_url = i_version_info_url.a_txt_input.text
        }
    }

    RoundedTextInput{
        id: i_update_url
        st_height_total: CoreImport._ViewScale_Height_Container * 4
        parent: root
        anchors.top: i_version_info_url.bottom
        _anno: st_update_url_text
        _enabled: true
        _value: webConfig.update_url
        a_txt_input.wrapMode: Text.WrapAnywhere
        a_txt_input.font.pixelSize: (CoreImport._ViewScale_Height_Container)/2
        a_text_small.font.pixelSize: (CoreImport._ViewScale_Height_Container)/3

        function update_initial_value(){
            webConfig.update_url = i_update_url.a_txt_input.text
        }
    }

    RoundedTextInput{
        id: i_code_override_url
        st_height_total: CoreImport._ViewScale_Height_Container * 4
        parent: root
        anchors.top: i_update_url.bottom
        _anno: st_code_override_url_text
        _enabled: true
        _value: webConfig.code_override_url
        a_txt_input.wrapMode: Text.WrapAnywhere
        a_txt_input.font.pixelSize: (CoreImport._ViewScale_Height_Container)/2
        a_text_small.font.pixelSize: (CoreImport._ViewScale_Height_Container)/3

        function update_initial_value(){
            webConfig.code_override_url = i_code_override_url.a_txt_input.text
        }
    }

    RoundedTextInput{
        id: i_max_bus_trace
      //  st_height_total: CoreImport._ViewScale_Height_Container * 4
        parent: root
        anchors.top: i_code_override_url.bottom
        _anno: st_max_bus_trace_text
        _enabled: true
        _value: bus_manager.max_can_trace_items
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[0-9]{1,10}$/
        }
        function update_initial_value(){
            bus_manager.max_can_trace_items = i_max_bus_trace.a_txt_input.text
        }
    }

}





