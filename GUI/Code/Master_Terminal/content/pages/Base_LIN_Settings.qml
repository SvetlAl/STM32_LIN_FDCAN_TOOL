import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "BaseItems";
import "SimpleItems";

Base {
    id: root

    /********* size settings ********/
    property real buttons_width_mlt: 3.5
    property int width_grid_sz: width*st_side_crop / 10
    property int composition_side_crop: (width - (width * st_side_crop))/2
    property int vertical_gap: st_initial_item_height/2

    property int st_item_height: root.width/2 < CoreImport._ViewScale_Height_Container*1.2 ? root.width/2 : CoreImport._ViewScale_Height_Container*1.2

    /********* colors settings ********/
    property string st_font_color: CoreImport._Base_Color_BaseFont

    /********* values ********/
    property bool changes_commited: false

    readonly property int lin_device_default_mode: 0
    readonly property int lin_device_gateway_mode: 1
    readonly property int lin_device_scanner_mode: 2
    readonly property int lin_device_filter_mode:  4
    readonly property int lin_device_device_mode:  8

    property bool st_lin_validation_mode: device_manager.lin_validation
    property int st_lin_mode: device_manager.lin_mode

    Component.onCompleted: {
        if(device_manager.OverrideLINFilterModel.length === 0)device_manager.OverrideLINFilterModel.init();
    }

    Connections {
        target: device_manager  /* registered in root context */
        function onChanged(){
            st_lin_validation_mode = device_manager.lin_validation;
            st_lin_mode = device_manager.lin_mode;
        }
    }
    /********* translated ********/
    property string st_saved_properties_anno: qsTr("Saved properties")
    property string st_save_button_text: qsTr("Save")
    property string st_validation_button_text: qsTr("Validation")
    property string st_device_button_text: qsTr("Device")
    property string st_gateway_button_text: qsTr("Gateway")
    property string st_filter_button_text: qsTr("Filter")
    property string st_filter_preset_anno: qsTr("Filter preset")
    property string st_poll_period_anno: qsTr("Device poll period")
    property string st_baudrate_text: qsTr("USART baudrate")
    property string st_ok_text: qsTr("OK")

    function retranslateUi(){
        st_saved_properties_anno = qsTr("Saved properties")
        st_save_button_text = qsTr("Save")
        st_validation_button_text = qsTr("Validation")
        st_device_button_text = qsTr("Device")
        st_gateway_button_text = qsTr("Gateway")
        st_filter_button_text = qsTr("Filter")
        st_filter_preset_anno = qsTr("Filter preset")
        st_poll_period_anno = qsTr("Device poll period")
        st_baudrate_text = qsTr("USART baudrate")
        st_ok_text = qsTr("OK")
    }

    Rectangle{
        id: i_save_settings_section
        y: vertical_gap
        x: composition_side_crop
        height: i_filter_preset_cbx.y + i_filter_preset_cbx.height + (vertical_gap/2)
        width: root.width * st_side_crop
        color: "transparent"
        border.color: st_font_color
        radius: 20

        Text{
            id: i_save_settings_label
            y: 0
            x: i_save_settings_section.radius
            width: i_save_settings_section.width
            //height: st_initial_item_height
            color: st_font_color
            text: st_saved_properties_anno
            font.pixelSize: st_initial_item_height/2
        }

        //============= Save ===============
        MltButton{
            id: i_save_button
            anchors.left: i_save_settings_section.left
            anchors.leftMargin: i_save_settings_section.radius

            y: i_save_settings_label.y + i_save_settings_label.height + vertical_gap

            height: st_initial_item_height
            width: (i_save_settings_section.width - i_save_settings_section.radius*4)/2

            st_button_mode: (interface_console.connection_status_description[0] === "Connected") ? true : false
            st_text: st_save_button_text
            st_normal_color: st_button_mode ? st_G_color : st_N_color
            function cmd(){
                root.forceActiveFocus();
                cmd_manager.saveDeviceStatus();
            }
        }

        //============= Validation ===============
        MltButton{
            id: i_validation_button
            y: i_save_button.y
            anchors.right: i_save_settings_section.right
            anchors.rightMargin: i_save_settings_section.radius

            height: st_initial_item_height
            width: i_save_button.width

            st_button_mode: interface_console.connection_status_description[0] === "Connected" ? true : false
            st_text: st_validation_button_text
            st_normal_color: st_lin_validation_mode ? st_G_color : st_N_color
            function cmd(){
                root.forceActiveFocus();
                if(st_lin_validation_mode == true)
                    cmd_manager.set_LIN_validation(false);
                else cmd_manager.set_LIN_validation(true);
            }
        }

        //============= Baudrate ===============
        Module_CBX_Annotated{
            id: i_baudrate_cbx
            width: (i_gateway_button.x + i_gateway_button.width) - i_save_settings_section.x
            height: st_initial_item_height
            x: i_save_settings_section.radius
            anchors.top: i_validation_button.bottom
            anchors.topMargin: st_item_height/5
            st_item_width: width/3 //root.st_item_width
            st_item_height: st_initial_item_height
            st_txt: st_baudrate_text
            _model: device_manager.lin_baudrate
            a_cbx_start_index: _model.current_index;
        }

        MltButton{
            id: i_baudrate_ok_button
            anchors.right: i_save_settings_section.right
            anchors.rightMargin: i_save_settings_section.radius
            y: i_baudrate_cbx.y // + i_can_gateway_button.height + vertical_gap
            height: st_initial_item_height
            width: i_device_button.width
            st_button_mode: interface_console.connection_status_description[0] === "Connected" ? true : false
            st_text: st_ok_text
            st_normal_color: st_N_color
            function cmd(){
                root.forceActiveFocus();
                cmd_manager.setDeviceValue(31, i_baudrate_cbx._model.current_index)
            }
        }

        //============= Device ===============
        MltButton{
            id: i_device_button
            anchors.left: i_save_settings_section.left
            anchors.leftMargin: i_save_settings_section.radius

            y: i_baudrate_cbx.y + i_baudrate_cbx.height + (vertical_gap/2)
            height: st_initial_item_height
            width: (i_save_button.width/3)*2
            st_button_mode: interface_console.connection_status_description[0] === "Connected" ? true : false
            st_text: st_device_button_text
            st_normal_color: (device_manager.lin_mode_device) ? st_G_color : st_N_color
            function cmd(){
                root.forceActiveFocus();
                if(device_manager.lin_mode_device)
                    cmd_manager.set_LIN_mode(lin_device_device_mode, false);
                else cmd_manager.set_LIN_mode(lin_device_device_mode, true);
            }
        }


        //============= Gateway ===============
        MltButton{
            id: i_gateway_button
            //x: i_device_button.x + i_device_button.width + composition_side_crop
            anchors.horizontalCenter: i_save_settings_section.horizontalCenter
            y: i_device_button.y
            height: st_initial_item_height
            width: i_device_button.width
            st_button_mode: interface_console.connection_status_description[0] === "Connected" ? true : false
            st_text: st_gateway_button_text
            st_normal_color: (device_manager.lin_mode_gateway) ? st_G_color : st_N_color
            function cmd(){
                root.forceActiveFocus();
                if(device_manager.lin_mode_gateway)
                    cmd_manager.set_LIN_mode(lin_device_gateway_mode, false);
                else cmd_manager.set_LIN_mode(lin_device_gateway_mode, true);
            }
        }

        //============= Filter ===============
        MltButton{
            id: i_filter_button
            anchors.right: i_save_settings_section.right
            anchors.rightMargin: i_save_settings_section.radius
            y: i_gateway_button.y // + i_can_gateway_button.height + vertical_gap
            height: st_initial_item_height
            width: i_device_button.width
            st_button_mode: interface_console.connection_status_description[0] === "Connected" ? true : false
            st_text: st_filter_button_text
            st_normal_color: (device_manager.lin_mode_filter) ? st_G_color : st_N_color
            function cmd(){
                root.forceActiveFocus();
                if(device_manager.lin_mode_filter)
                    cmd_manager.set_LIN_mode(lin_device_filter_mode, false);
                else cmd_manager.set_LIN_mode(lin_device_filter_mode, true);
            }
        }

        //============= Filter preset ===============
        Module_CBX_Annotated{
            id: i_filter_preset_cbx
            width: (i_gateway_button.x + i_gateway_button.width) - i_save_settings_section.x
            height: st_initial_item_height
            x: i_save_settings_section.radius
            anchors.top: i_device_button.bottom
            anchors.topMargin: st_item_height/5
            st_item_width: width/3 //root.st_item_width
            st_item_height: st_initial_item_height
            st_txt: st_filter_preset_anno
            _model: device_manager.lin_filter_preset
            a_cbx_start_index: _model.current_index; 
        }

        MltButton{
            id: i_filter_preset_ok_button
            anchors.right: i_save_settings_section.right
            anchors.rightMargin: i_save_settings_section.radius
            y: i_filter_preset_cbx.y // + i_can_gateway_button.height + vertical_gap
            height: st_initial_item_height
            width: i_device_button.width
            st_button_mode: interface_console.connection_status_description[0] === "Connected" ? true : false
            st_text: st_ok_text
            st_normal_color: st_N_color
            function cmd(){
                root.forceActiveFocus();
                cmd_manager.setDeviceValue(33, i_filter_preset_cbx._model.current_index)
            }
        }
    }

    RoundedSliderAnnotated{
        id: i_device_poll_period_scale

        x: i_save_settings_section.x
        y: i_save_settings_section.y + i_save_settings_section.height + vertical_gap
        height: st_initial_item_height
        width: i_save_settings_section.width - (i_save_settings_section.radius*2)
        enabled: true
        _anno: st_poll_period_anno
        value_display_offset: false
        a_slider._value: device_manager.lin_poll_period
        a_slider.st_labelTxt: a_slider._value.toString(10).toUpperCase()
        a_slider._from: 0
        a_slider._to: 65535
        a_slider._step: 255
        function a_update_initial_value(){
            cmd_manager.refresh_LIN_poll_period(a_slider._value)
           // set_cdc_threshold_value(a_slider._value)
           // cmd_manager.setDeviceValue(21, st_val_cdc_threshold_value);
        }
    }

    ListView  {
        id: listView
        parent: root
        anchors.top: i_device_poll_period_scale.bottom
        anchors.topMargin: vertical_gap
        height: freeMainframeSpace - y
        width: i_save_settings_section.width
        anchors.horizontalCenter: i_save_settings_section.horizontalCenter
        boundsBehavior: Flickable.DragOverBounds
        clip: true
        cacheBuffer: 2

        model: device_manager.OverrideLINFilterModel
        delegate:
            Rectangle{

            height: i_filter.height
            width: root.width
            color: "transparent"

                Item_LIN_override_filter{
                    id: i_filter
                    st_total_height: st_item_height*1.0
                    height: st_edit_mode ? (st_total_height + st_vertical_gap)*5 : (st_total_height + st_vertical_gap)
                    width: i_save_settings_section.width

                    st_editable: true // modelData.isEditable
                    theIdValue: "0x" + modelData.id_value
                    st_dir_mosi: modelData.dir_value
                    //st_filter_enabled: modelData.enabled
                    //dir_value: modelData.dir_value


                    /*
                    function onCanSelected(_val){
                        modelData.dir_value = _val
                        changes_commited = true;
                    }
                    */

                    function setIdValue(_val){
                   //     device_manager.set_discard_id_value(index, theValue);
                        modelData.id_value = _val
                        changes_commited = true;
                    }

                    function onclick(){
                   //     device_manager.enable_discard_id(index, !modelData.isEnabled);
                   //     device_manager.OverrideFilterModel.enable_filter(index, !st_filter_enabled);
                   //     changes_commited = true;
                    }

                    function onEditModeChanged(){
                    }

                    theByte0: "0x" + modelData.str_byte0
                    enabled_0: modelData.byte0_on
                    function setByte0Value(theIdValue){
                        modelData.str_byte0 = theIdValue;
                        changes_commited = true;
                    }
                    function enableByte0filter(_val){
                        modelData.byte0_on = _val
                        changes_commited = true;
                    }

                    theByte1: "0x" + modelData.str_byte1
                    enabled_1: modelData.byte1_on
                    function setByte1Value(theIdValue){
                        modelData.str_byte1 = theIdValue;
                        changes_commited = true;
                    }
                    function enableByte1filter(_val){
                        modelData.byte1_on = _val
                        changes_commited = true;
                    }

                    theByte2: "0x" + modelData.str_byte2
                    enabled_2: modelData.byte2_on
                    function setByte2Value(theIdValue){
                        modelData.str_byte2 = theIdValue;
                        changes_commited = true;
                    }
                    function enableByte2filter(_val){
                        modelData.byte2_on = _val
                        changes_commited = true;
                    }

                    theByte3: "0x" + modelData.str_byte3
                    enabled_3: modelData.byte3_on
                    function setByte3Value(theIdValue){
                        modelData.str_byte3 = theIdValue;
                        changes_commited = true;
                    }
                    function enableByte3filter(_val){
                        modelData.byte3_on = _val
                        changes_commited = true;
                    }

                    theByte4: "0x" + modelData.str_byte4
                    enabled_4: modelData.byte4_on
                    function setByte4Value(theIdValue){
                        modelData.str_byte4 = theIdValue;
                        changes_commited = true;
                    }
                    function enableByte4filter(_val){
                        modelData.byte4_on = _val
                        changes_commited = true;
                    }

                    theByte5: "0x" + modelData.str_byte5
                    enabled_5: modelData.byte5_on
                    function setByte5Value(theIdValue){
                        modelData.str_byte5 = theIdValue;
                        changes_commited = true;
                    }
                    function enableByte5filter(_val){
                        modelData.byte5_on = _val
                        changes_commited = true;
                    }

                    theByte6: "0x" + modelData.str_byte6
                    enabled_6: modelData.byte6_on
                    function setByte6Value(theIdValue){
                        modelData.str_byte6 = theIdValue;
                        changes_commited = true;
                    }
                    function enableByte6filter(_val){
                        modelData.byte6_on = _val
                        changes_commited = true;
                    }

                    theByte7: "0x" + modelData.str_byte7
                    enabled_7: modelData.byte7_on
                    function setByte7Value(theIdValue){
                        modelData.str_byte7 = theIdValue;
                        changes_commited = true;
                    }
                    function enableByte7filter(_val){
                        modelData.byte7_on = _val
                        changes_commited = true;
                    }




                }
                Rectangle{
                    height: st_item_height/4
                    color: "transparent"
                }
        }

    }




}
