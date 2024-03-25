import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "BaseItems";
import "SimpleItems";

Rectangle {
    /********* alias ********/
    id: root
    color: "transparent"

    /********* size settings ********/
    property real buttons_width_mlt: 3.5
    property int width_grid_sz: width*st_side_crop / 10
    /********* colors settings ********/

    /********* values ********/

    property int composition_side_crop: (width - (width * st_side_crop))/2
    property int vertical_gap: st_initial_item_height/6

    /********* colors settings ********/
    property string st_font_color: CoreImport._Base_Color_BaseFont

    /********* alias ********/
    property string st_FDCAN_ID_anno: qsTr("FD CAN ID");
    property string st_extended_id_anno: qsTr("Extended ID");
    property string st_standart_id_anno: qsTr("Standart ID");
    property string st_flags_anno: qsTr("Flags");

    property string st_fdf_flag_anno: qsTr("FDF ");
    property string st_brs_flag_anno: qsTr("BRS ");

    property string st_data_anno: qsTr("Data ");
    property string st_msg_length_anno: qsTr("Message length(DLC)");


    property bool visible_row_01: i_byte0.visible
    property bool visible_row_02: i_byte4.visible
    property bool visible_row_03: i_byte8.visible
    property bool visible_row_04: i_byte12.visible
    property bool visible_row_05: i_byte16.visible
    property bool visible_row_06: i_byte20.visible
    property bool visible_row_07: i_byte24.visible
    property bool visible_row_08: i_byte28.visible
    property bool visible_row_09: i_byte32.visible
    property bool visible_row_10: i_byte36.visible
    property bool visible_row_11: i_byte40.visible
    property bool visible_row_12: i_byte44.visible
    property bool visible_row_13: i_byte48.visible
    property bool visible_row_14: i_byte52.visible
    property bool visible_row_15: i_byte56.visible
    property bool visible_row_16: i_byte60.visible

    /********* meta values ********/
    property int message_length  : 0
/*
    property var byte_values:[
    "0x00", "0x00", "0x00", "0x00", "0x00", "0x00", "0x00", "0x00",
    "0x00", "0x00", "0x00", "0x00", "0x00", "0x00", "0x00", "0x00",
    "0x00", "0x00", "0x00", "0x00", "0x00", "0x00", "0x00", "0x00",
    "0x00", "0x00", "0x00", "0x00", "0x00", "0x00", "0x00", "0x00",
    "0x00", "0x00", "0x00", "0x00", "0x00", "0x00", "0x00", "0x00",
    "0x00", "0x00", "0x00", "0x00", "0x00", "0x00", "0x00", "0x00",
    "0x00", "0x00", "0x00", "0x00", "0x00", "0x00", "0x00", "0x00",
    "0x00", "0x00", "0x00", "0x00", "0x00", "0x00", "0x00", "0x00"
    ]

    readonly property int pos_ESI : 1
    readonly property int pos_XTD : 2
    readonly property int pos_FDF : 4
    readonly property int pos_BRS : 8
*/

    property bool ext_flag: fdcan_inj_msg.xtd_flag
    property bool fdf_flag: fdcan_inj_msg.fdf_flag
    property bool brs_flag: fdcan_inj_msg.brs_flag

    function retranslateUi(){
        st_FDCAN_ID_anno = qsTr("FD CAN ID");
        st_extended_id_anno = qsTr("Extended ID");
        st_standart_id_anno = qsTr("Standart ID");
        st_flags_anno = qsTr("Flags");

        st_fdf_flag_anno =  qsTr("FDF ");
        st_brs_flag_anno =  qsTr("BRS ");

        st_data_anno =  qsTr("Data ");
        st_msg_length_anno =  qsTr("Message length(DLC)");
    }

    function isHexadecimal(input) {
        var hexRegex = /^[0-9A-Fa-f]+$/;
        return hexRegex.test(input);
    }

    function setMsgLength(_dlc){
        switch(_dlc){
        case 8:
            message_length = 8;
            break;
        case 9:
            message_length = (fdcan_inj_msg.fdf_flag == true) ? 12 : 8;
            break;
        case 10:
            message_length = (fdcan_inj_msg.fdf_flag == true) ? 16 : 8;
            break;
        case 11:
            message_length = (fdcan_inj_msg.fdf_flag == true) ? 20 : 8;
            break;
        case 12:
            message_length = (fdcan_inj_msg.fdf_flag == true) ? 24 : 8;
            break;
        case 13:
            message_length = (fdcan_inj_msg.fdf_flag == true) ? 32 : 8;
            break;
        case 14:
            message_length = (fdcan_inj_msg.fdf_flag == true) ? 48 : 8;
            break;
        case 15:
            message_length = (fdcan_inj_msg.fdf_flag == true) ? 64 : 8;
            break;
        case 7:
            message_length = 7;
            break;
        case 6:
            message_length = 6;
            break;
        case 5:
            message_length = 5;
            break;
        case 4:
            message_length = 4;
            break;
        case 3:
            message_length = 3;
            break;
        case 2:
            message_length = 2;
            break;
        case 1:
            message_length = 1;
            break;
        case 0:
            message_length = 0;
            break;
        default:
            message_length = 0;
            break;
        }
        calculateHeight();
    }

    Connections {
        target: qmlTranslator  /* registered in root context */
        function onLanguageChanged(){
            retranslateUi();
        }
    }

    Component.onCompleted: {
        root.forceActiveFocus();
        setMsgLength(fdcan_inj_msg.dlc);
        calculateHeight();
        retranslateUi();
    }


    signal sendHeight(int msg)
    function calculateHeight(){
        var total_height = 0//i_textfield.y + i_textfield.height

        for(var i = root.children.length; i > 0 ; i--) {
            if(root.children[i-1].type !== "focus_reset"){
                total_height += root.children[i-1].height
                total_height += root.children[i-1].anchors.topMargin
            }
        }
        root.height = total_height
        sendHeight(total_height)
    }


    Rectangle{
        id: i_fdcan_id_section
        y: vertical_gap
        x: composition_side_crop
        height: i_extended_id_button.y + i_extended_id_button.height + (vertical_gap)
        width: root.width * st_side_crop
        color: "transparent"
        border.color: st_font_color
        radius: 20

        property int hor_space: width - (radius*2)
        property int hor_item_gap: radius
        property int hor_space_step: (hor_space/4)
        property int hor_item_width: hor_space_step - radius

        Text{
            id: i_fdcan_id_label
            y: 0
            x: i_fdcan_id_section.radius
            width: i_fdcan_id_section.width
            color: st_font_color
            text: st_FDCAN_ID_anno
            font.pixelSize: st_initial_item_height/2
        }

        //============= Id  ===============

        RoundedTextInput{
            id: i_idvalue_button
            x: i_fdcan_id_section.hor_item_gap + (i_fdcan_id_section.hor_space_step*0)
            width: i_fdcan_id_section.hor_item_width*2
            y: i_fdcan_id_label.y + i_fdcan_id_label.height + vertical_gap/4

            _anno: st_FDCAN_ID_anno
            _enabled: true
            _value: fdcan_inj_msg.id
            function update_initial_value(){
                var hexRegExp = /^(0x)?[0-9A-Fa-f]+$/;
                if(!hexRegExp.test(a_txt_input.text)){
                    a_txt_input.text = fdcan_inj_msg.id;
                    return;
                }

                if (!a_txt_input.text.startsWith("0x")) {
                    a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                }

                if (ext_flag) {
                    if (parseInt(a_txt_input.text, 16) >= 1 && parseInt(a_txt_input.text, 16) <= 0x1FFFFFFF) {
                    } else {
                        a_txt_input.text = fdcan_inj_msg.id;
                        console.log("Error: DLC out of range for extended frame");
                    }
                } else {
                    if (parseInt(a_txt_input.text, 16) >= 1 && parseInt(a_txt_input.text, 16) <= 0x7FF) {
                    } else {
                        a_txt_input.text = fdcan_inj_msg.id;
                        console.log("Error: DLC out of range for standard frame");
                    }
                }
                a_txt_input.text =a_txt_input.text;
                fdcan_inj_msg.id = a_txt_input.text;
            }

        }

        //============= FDOE  ===============
        /*
        MltButton{
            id: i_fdoe_button
            y: i_idvalue_button.y

            x: i_fdcan_id_section.hor_item_gap + (i_fdcan_id_section.hor_space_step*2)
            width: i_fdcan_id_section.hor_item_width

            height: st_initial_item_height

            st_button_mode: true
            st_text: st_FDOE_anno
            st_normal_color: st_button_mode ? st_G_color : st_N_color
            function cmd(){
                root.forceActiveFocus();
            }
        }
        */

        //============= Extended  ===============
        MltButton{
            id: i_extended_id_button
            y: i_idvalue_button.y

            x: i_fdcan_id_section.hor_item_gap + (i_fdcan_id_section.hor_space_step*2.5)
            width: i_fdcan_id_section.hor_item_width*1.5
            height: st_initial_item_height

            st_button_mode: true
            st_text: fdcan_inj_msg.xtd_flag ? st_extended_id_anno : st_standart_id_anno
            st_normal_color: fdcan_inj_msg.xtd_flag ? st_Y_color : st_B_color
            function cmd(){
                root.forceActiveFocus();
                fdcan_inj_msg.xtd_flag = !fdcan_inj_msg.xtd_flag
            }
        }
    } // rect


    Rectangle{
        id: i_flags_section
        y: i_fdcan_id_section.y+ i_fdcan_id_section.height + (vertical_gap/2)
        x: composition_side_crop
        height: i_brs_button.y + i_brs_button.height + (vertical_gap)
        width: root.width * st_side_crop
        color: "transparent"
        border.color: st_font_color
        radius: 20

        property int hor_space: width - (radius*2)
        property int hor_item_gap: radius
        property int hor_space_step: (hor_space/4)
        property int hor_item_width: hor_space_step - radius

        Text{
            id: i_flags_label
            y: 0
            x: i_flags_section.radius
            width: i_flags_section.width
            color: st_font_color
            text: st_flags_anno
            font.pixelSize: st_initial_item_height/2
        }

        //============= FDF  ===============
        MltButton{
            id: i_fdf_button
            x: i_flags_section.hor_item_gap + (i_flags_section.hor_space_step*0)
            width: i_flags_section.hor_item_width
            y: i_flags_label.y + i_flags_label.height + vertical_gap/4
            height: st_initial_item_height

            //st_button_mode: (interface_console.connection_status_description[0] === "Connected") ? true : false
            st_button_mode: true

            st_text: st_fdf_flag_anno
            st_normal_color: fdcan_inj_msg.fdf_flag ? st_Y_color : st_B_color
            function cmd(){
                root.forceActiveFocus();
                fdcan_inj_msg.fdf_flag = !fdcan_inj_msg.fdf_flag;
            }
        }

        //============= BRS  ===============
        MltButton{
            id: i_brs_button
            y: i_fdf_button.y

            x: i_flags_section.hor_item_gap + (i_flags_section.hor_space_step*1)
            width: i_flags_section.hor_item_width

            height: st_initial_item_height

            st_button_mode: true
            st_text: st_brs_flag_anno
            st_normal_color: fdcan_inj_msg.brs_flag ? st_Y_color : st_B_color
            function cmd(){
                root.forceActiveFocus();
                fdcan_inj_msg.brs_flag = !fdcan_inj_msg.brs_flag
            }
        }
    } // rect



    Rectangle{
        id: i_data_section
        y: i_flags_section.y+ i_flags_section.height + (vertical_gap/2)
        x: composition_side_crop
       // height: i_message_length.y + i_message_length.height + (vertical_gap)
        height:                   !visible_row_01 ? const_height + (row_height * 0):
                                  !visible_row_02 ? const_height + (row_height * 1):
                                  !visible_row_03 ? const_height + (row_height * 2):
                                  !visible_row_04 ? const_height + (row_height * 3):
                                  !visible_row_05 ? const_height + (row_height * 4):
                                  !visible_row_06 ? const_height + (row_height * 5):
                                  !visible_row_07 ? const_height + (row_height * 6):
                                  !visible_row_08 ? const_height + (row_height * 7):
                                  !visible_row_09 ? const_height + (row_height * 8):
                                  !visible_row_10 ? const_height + (row_height * 9):
                                  !visible_row_11 ? const_height + (row_height * 10):
                                  !visible_row_12 ? const_height + (row_height * 11):
                                  !visible_row_13 ? const_height + (row_height * 12):
                                  !visible_row_14 ? const_height + (row_height * 13):
                                  !visible_row_15 ? const_height + (row_height * 14):
                                  !visible_row_16 ? const_height + (row_height * 15): const_height + (row_height * 16)















        width: root.width * st_side_crop
        color: "transparent"
        border.color: st_font_color
        radius: 20

        property int const_height: i_message_length.y + i_message_length.height + (vertical_gap)
        property int row_height: st_initial_item_height + (vertical_gap*2)

        property int hor_space: width - (radius*2)
        property int hor_item_gap: radius
        property int hor_space_step: (hor_space/4)
        property int hor_item_width: hor_space_step - radius

        Text{
            id: i_data_label
            y: 0
            x: i_flags_section.radius
            width: i_flags_section.width
            color: st_font_color
            text: st_data_anno
            font.pixelSize: st_initial_item_height/2
        }

        RoundedSliderAnnotated{
            id: i_message_length

            x: i_flags_section.hor_item_gap + (i_flags_section.hor_space_step*0)
            width: i_data_section.width + i_data_section.x - (i_flags_section.hor_item_gap*2)
            y: i_flags_label.y + i_flags_label.height + vertical_gap/4
            height: st_initial_item_height


            enabled: true
            _anno: st_msg_length_anno

            value_display_offset: false
            a_slider._value: fdcan_inj_msg.dlc
            a_slider.st_labelTxt: "0x" + a_slider._value.toString(16).toUpperCase()
            a_slider._from: 0
            a_slider._to: 15
            a_slider._step: 1
            function a_update_initial_value(){
               setMsgLength(a_slider._value);
               fdcan_inj_msg.dlc = a_slider._value;
               // cmd_manager.refresh_LIN_poll_period(a_slider._value)
               // set_cdc_threshold_value(a_slider._value)
               // cmd_manager.setDeviceValue(21, st_val_cdc_threshold_value);
            }
        }

        //===============================================================
        //============================ ROW 1 ============================
        //===============================================================

        //============= Byte 0  ===============
        RoundedTextInput{
            id: i_byte0
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*0)
            width: i_data_section.hor_item_width
            y: i_message_length.y + i_message_length.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 0 "
            _enabled: true
            visible : (message_length > 0) ? true : false
            _value: fdcan_inj_msg.data_00

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 0;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_00 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_00;
            }
        }

        //============= Byte 1  ===============
        RoundedTextInput{
            id: i_byte1
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*1)
            width: i_data_section.hor_item_width
            y: i_message_length.y + i_message_length.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 1 "
            _enabled: true
            visible : (message_length > 1) ? true : false
            _value: fdcan_inj_msg.data_01

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 1;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_01 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_01;
            }
        }

        //============= Byte 2  ===============
        RoundedTextInput{
            id: i_byte2
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*2)
            width: i_data_section.hor_item_width
            y: i_message_length.y + i_message_length.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 2 "
            _enabled: true
            visible : (message_length > 2) ? true : false
            _value: fdcan_inj_msg.data_02

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 2;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_02 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_02;
            }
        }

        //============= Byte 3  ===============
        RoundedTextInput{
            id: i_byte3
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*3)
            width: i_data_section.hor_item_width
            y: i_message_length.y + i_message_length.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 3 "
            _enabled: true
            visible : (message_length > 3) ? true : false
            _value: fdcan_inj_msg.data_03

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 3;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_03 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_03;
            }
        }

        //===============================================================
        //============================ ROW 2 ============================
        //===============================================================

        //============= Byte 4  ===============
        RoundedTextInput{
            id: i_byte4
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*0)
            width: i_data_section.hor_item_width
            y: i_byte0.y + i_byte0.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 4 "
            _enabled: true
            visible : (message_length > 4) ? true : false
            _value: fdcan_inj_msg.data_04

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 4;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_04 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_04;
            }
        }

        //============= Byte 5  ===============
        RoundedTextInput{
            id: i_byte5
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*1)
            width: i_data_section.hor_item_width
            y: i_byte4.y
            height: st_initial_item_height

            _anno: "Byte 5 "
            _enabled: true
            visible : (message_length > 5) ? true : false
            _value: fdcan_inj_msg.data_05

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 5;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_05 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_05;
            }
        }

        //============= Byte 6  ===============
        RoundedTextInput{
            id: i_byte6
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*2)
            width: i_data_section.hor_item_width
            y: i_byte4.y
            height: st_initial_item_height

            _anno: "Byte 6 "
            _enabled: true
            visible : (message_length > 6) ? true : false
            _value: fdcan_inj_msg.data_06

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 6;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_06 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_06;
            }
        }

        //============= Byte 7  ===============
        RoundedTextInput{
            id: i_byte7
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*3)
            width: i_data_section.hor_item_width
            y: i_byte4.y
            height: st_initial_item_height

            _anno: "Byte 7 "
            _enabled: true
            visible : (message_length > 7) ? true : false
            _value: fdcan_inj_msg.data_07

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 7;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_07 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_07;
            }
        }

        //===============================================================
        //============================ ROW 3 ============================
        //===============================================================

        //============= Byte 8  ===============
        RoundedTextInput{
            id: i_byte8
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*0)
            width: i_data_section.hor_item_width
            y: i_byte4.y + i_byte4.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 8 "
            _enabled: true
            visible : (message_length > 8) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_08

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 8;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_08 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_08;
            }
        }

        //============= Byte 9  ===============
        RoundedTextInput{
            id: i_byte9
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*1)
            width: i_data_section.hor_item_width
            y: i_byte8.y
            height: st_initial_item_height

            _anno: "Byte 9 "
            _enabled: true
            visible : (message_length > 9) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_09

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 9;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_09 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_09;
            }
        }

        //============= Byte 10  ===============
        RoundedTextInput{
            id: i_byte10
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*2)
            width: i_data_section.hor_item_width
            y: i_byte8.y
            height: st_initial_item_height

            _anno: "Byte 10 "
            _enabled: true
            visible : (message_length > 10) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_10

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 10;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_10 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_10;
            }
        }

        //============= Byte 11  ===============
        RoundedTextInput{
            id: i_byte11
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*3)
            width: i_data_section.hor_item_width
            y: i_byte8.y
            height: st_initial_item_height

            _anno: "Byte 11 "
            _enabled: true
            visible : (message_length > 11) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_11

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 11;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_11 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_11;
            }
        }

        //===============================================================
        //============================ ROW 4 ============================
        //===============================================================

        //============= Byte 12  ===============
        RoundedTextInput{
            id: i_byte12
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*0)
            width: i_data_section.hor_item_width
            y: i_byte8.y + i_byte8.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 12 "
            _enabled: true
            visible : (message_length > 12) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_12

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 12;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_12 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_12;
            }
        }

        //============= Byte 13  ===============
        RoundedTextInput{
            id: i_byte13
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*1)
            width: i_data_section.hor_item_width
            y: i_byte12.y
            height: st_initial_item_height

            _anno: "Byte 13 "
            _enabled: true
            visible : (message_length > 13) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_13

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 13;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_13 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_13;
            }
        }

        //============= Byte 14  ===============
        RoundedTextInput{
            id: i_byte14
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*2)
            width: i_data_section.hor_item_width
            y: i_byte12.y
            height: st_initial_item_height

            _anno: "Byte 14 "
            _enabled: true
            visible : (message_length > 14) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_14

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 14;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_14 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_14;
            }
        }

        //============= Byte 15  ===============
        RoundedTextInput{
            id: i_byte15
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*3)
            width: i_data_section.hor_item_width
            y: i_byte12.y
            height: st_initial_item_height

            _anno: "Byte 15 "
            _enabled: true
            visible : (message_length > 15) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_15

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 15;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_15 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_15;
            }
        }

        //===============================================================
        //============================ ROW 5 ============================
        //===============================================================

        //============= Byte 16  ===============
        RoundedTextInput{
            id: i_byte16
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*0)
            width: i_data_section.hor_item_width
            y: i_byte12.y + i_byte12.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 16 "
            _enabled: true
            visible : (message_length > 16) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_16

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 16;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_16 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_16;
            }
        }

        //============= Byte 17  ===============
        RoundedTextInput{
            id: i_byte17
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*1)
            width: i_data_section.hor_item_width
            y: i_byte16.y
            height: st_initial_item_height

            _anno: "Byte 17 "
            _enabled: true
            visible : (message_length > 17) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_17

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 17;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_17 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_17;
            }
        }

        //============= Byte 18  ===============
        RoundedTextInput{
            id: i_byte18
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*2)
            width: i_data_section.hor_item_width
            y: i_byte16.y
            height: st_initial_item_height

            _anno: "Byte 18 "
            _enabled: true
            visible : (message_length > 18) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_18

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 18;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_18 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_18;
            }
        }

        //============= Byte 19  ===============
        RoundedTextInput{
            id: i_byte19
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*3)
            width: i_data_section.hor_item_width
            y: i_byte16.y
            height: st_initial_item_height

            _anno: "Byte 19 "
            _enabled: true
            visible : (message_length > 19) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_19

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 19;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_19 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_19;
            }
        }

        //===============================================================
        //============================ ROW 6 ============================
        //===============================================================

        //============= Byte 20  ===============
        RoundedTextInput{
            id: i_byte20
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*0)
            width: i_data_section.hor_item_width
            y: i_byte16.y + i_byte16.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 20 "
            _enabled: true
            visible : (message_length > 20) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_20

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 20;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_20 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_20;
            }
        }

        //============= Byte 21  ===============
        RoundedTextInput{
            id: i_byte21
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*1)
            width: i_data_section.hor_item_width
            y: i_byte20.y
            height: st_initial_item_height

            _anno: "Byte 21 "
            _enabled: true
            visible : (message_length > 21) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_21

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 21;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_21 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_21;
            }
        }

        //============= Byte 22  ===============
        RoundedTextInput{
            id: i_byte22
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*2)
            width: i_data_section.hor_item_width
            y: i_byte20.y
            height: st_initial_item_height

            _anno: "Byte 22 "
            _enabled: true
            visible : (message_length > 22) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_22

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 22;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_22 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_22;
            }
        }

        //============= Byte 23  ===============
        RoundedTextInput{
            id: i_byte23
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*3)
            width: i_data_section.hor_item_width
            y: i_byte20.y
            height: st_initial_item_height

            _anno: "Byte 23 "
            _enabled: true
            visible : (message_length > 23) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_23

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 23;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_23 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_23;
            }
        }

        //===============================================================
        //============================ ROW 7 ============================
        //===============================================================

        //============= Byte 24  ===============
        RoundedTextInput{
            id: i_byte24
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*0)
            width: i_data_section.hor_item_width
            y: i_byte20.y + i_byte20.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 24 "
            _enabled: true
            visible : (message_length > 24) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_24

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 24;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_24 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_24;
            }
        }

        //============= Byte 25  ===============
        RoundedTextInput{
            id: i_byte25
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*1)
            width: i_data_section.hor_item_width
            y: i_byte24.y
            height: st_initial_item_height

            _anno: "Byte 25 "
            _enabled: true
            visible : (message_length > 25) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_25

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 25;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_25 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_25;
            }
        }

        //============= Byte 26  ===============
        RoundedTextInput{
            id: i_byte26
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*2)
            width: i_data_section.hor_item_width
            y: i_byte24.y
            height: st_initial_item_height

            _anno: "Byte 26 "
            _enabled: true
            visible : (message_length > 26) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_26

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 26;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_26 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_26;
            }
        }

        //============= Byte 27  ===============
        RoundedTextInput{
            id: i_byte27
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*3)
            width: i_data_section.hor_item_width
            y: i_byte24.y
            height: st_initial_item_height

            _anno: "Byte 27 "
            _enabled: true
            visible : (message_length > 27) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_27

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 27;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_27 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_27;
            }
        }

        //===============================================================
        //============================ ROW 8 ============================
        //===============================================================

        //============= Byte 28  ===============
        RoundedTextInput{
            id: i_byte28
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*0)
            width: i_data_section.hor_item_width
            y: i_byte24.y + i_byte24.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 28 "
            _enabled: true
            visible : (message_length > 28) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_28

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 28;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_28 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_28;
            }
        }

        //============= Byte 29  ===============
        RoundedTextInput{
            id: i_byte29
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*1)
            width: i_data_section.hor_item_width
            y: i_byte28.y
            height: st_initial_item_height

            _anno: "Byte 29 "
            _enabled: true
            visible : (message_length > 29) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_29

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 29;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_29 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_29;
            }
        }

        //============= Byte 30  ===============
        RoundedTextInput{
            id: i_byte30
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*2)
            width: i_data_section.hor_item_width
            y: i_byte28.y
            height: st_initial_item_height

            _anno: "Byte 30 "
            _enabled: true
            visible : (message_length > 30) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_30

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 30;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_30 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_30;
            }
        }

        //============= Byte 31  ===============
        RoundedTextInput{
            id: i_byte31
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*3)
            width: i_data_section.hor_item_width
            y: i_byte28.y
            height: st_initial_item_height

            _anno: "Byte 31 "
            _enabled: true
            visible : (message_length > 31) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_31

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 31;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_31 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_31;
            }
        }

        //===============================================================
        //============================ ROW 9 ============================
        //===============================================================

        //============= Byte 32  ===============
        RoundedTextInput{
            id: i_byte32
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*0)
            width: i_data_section.hor_item_width
            y: i_byte28.y + i_byte28.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 32 "
            _enabled: true
            visible : (message_length > 32) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_32

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 32;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_32 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_32;
            }
        }

        //============= Byte 33  ===============
        RoundedTextInput{
            id: i_byte33
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*1)
            width: i_data_section.hor_item_width
            y: i_byte32.y
            height: st_initial_item_height

            _anno: "Byte 33 "
            _enabled: true
            visible : (message_length > 33) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_33

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 33;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_33 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_33;
            }
        }

        //============= Byte 34  ===============
        RoundedTextInput{
            id: i_byte34
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*2)
            width: i_data_section.hor_item_width
            y: i_byte32.y
            height: st_initial_item_height

            _anno: "Byte 34 "
            _enabled: true
            visible : (message_length > 34) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_34

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 34;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_34 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_34;
            }
        }

        //============= Byte 35  ===============
        RoundedTextInput{
            id: i_byte35
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*3)
            width: i_data_section.hor_item_width
            y: i_byte32.y
            height: st_initial_item_height

            _anno: "Byte 35 "
            _enabled: true
            visible : (message_length > 35) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_35

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 35;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_35 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_35;
            }
        }

        //===============================================================
        //============================ ROW 10 ===========================
        //===============================================================

        //============= Byte 36  ===============
        RoundedTextInput{
            id: i_byte36
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*0)
            width: i_data_section.hor_item_width
            y: i_byte32.y + i_byte32.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 36 "
            _enabled: true
            visible : (message_length > 36) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_36

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 36;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_36 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_36;
            }
        }

        //============= Byte 37  ===============
        RoundedTextInput{
            id: i_byte37
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*1)
            width: i_data_section.hor_item_width
            y: i_byte36.y
            height: st_initial_item_height

            _anno: "Byte 37 "
            _enabled: true
            visible : (message_length > 37) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_37

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 37;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_37 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_37;
            }
        }

        //============= Byte 38  ===============
        RoundedTextInput{
            id: i_byte38
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*2)
            width: i_data_section.hor_item_width
            y: i_byte36.y
            height: st_initial_item_height

            _anno: "Byte 38 "
            _enabled: true
            visible : (message_length > 38) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_38

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 38;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_38 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_38;
            }
        }

        //============= Byte 39  ===============
        RoundedTextInput{
            id: i_byte39
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*3)
            width: i_data_section.hor_item_width
            y: i_byte36.y
            height: st_initial_item_height

            _anno: "Byte 39 "
            _enabled: true
            visible : (message_length > 39) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_39

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 39;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_39 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_39;
            }
        }

        //===============================================================
        //============================ ROW 11 ===========================
        //===============================================================

        //============= Byte 40  ===============
        RoundedTextInput{
            id: i_byte40
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*0)
            width: i_data_section.hor_item_width
            y: i_byte36.y + i_byte36.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 40 "
            _enabled: true
            visible : (message_length > 40) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_40

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 40;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_40 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_40;
            }
        }

        //============= Byte 41  ===============
        RoundedTextInput{
            id: i_byte41
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*1)
            width: i_data_section.hor_item_width
            y: i_byte40.y
            height: st_initial_item_height

            _anno: "Byte 41 "
            _enabled: true
            visible : (message_length > 41) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_41

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 41;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_41 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_41;
            }
        }

        //============= Byte 42  ===============
        RoundedTextInput{
            id: i_byte42
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*2)
            width: i_data_section.hor_item_width
            y: i_byte40.y
            height: st_initial_item_height

            _anno: "Byte 42 "
            _enabled: true
            visible : (message_length > 42) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_42

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 42;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_42 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_42;
            }
        }

        //============= Byte 43  ===============
        RoundedTextInput{
            id: i_byte43
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*3)
            width: i_data_section.hor_item_width
            y: i_byte40.y
            height: st_initial_item_height

            _anno: "Byte 43 "
            _enabled: true
            visible : (message_length > 43) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_43

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 43;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_43 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_43;
            }
        }

        //===============================================================
        //============================ ROW 12 ===========================
        //===============================================================

        //============= Byte 44  ===============
        RoundedTextInput{
            id: i_byte44
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*0)
            width: i_data_section.hor_item_width
            y: i_byte40.y + i_byte40.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 44 "
            _enabled: true
            visible : (message_length > 44) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_44

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 44;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_44 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_44;
            }
        }

        //============= Byte 45  ===============
        RoundedTextInput{
            id: i_byte45
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*1)
            width: i_data_section.hor_item_width
            y: i_byte44.y
            height: st_initial_item_height

            _anno: "Byte 45 "
            _enabled: true
            visible : (message_length > 45) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_45

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 45;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_45 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_45;
            }
        }

        //============= Byte 46  ===============
        RoundedTextInput{
            id: i_byte46
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*2)
            width: i_data_section.hor_item_width
            y: i_byte44.y
            height: st_initial_item_height

            _anno: "Byte 46 "
            _enabled: true
            visible : (message_length > 46) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_46

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 46;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_46 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_46;
            }
        }

        //============= Byte 47  ===============
        RoundedTextInput{
            id: i_byte47
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*3)
            width: i_data_section.hor_item_width
            y: i_byte44.y
            height: st_initial_item_height

            _anno: "Byte 47 "
            _enabled: true
            visible : (message_length > 47) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_47

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 47;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_47 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_47;
            }
        }

        //===============================================================
        //============================ ROW 13 ===========================
        //===============================================================

        //============= Byte 48  ===============
        RoundedTextInput{
            id: i_byte48
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*0)
            width: i_data_section.hor_item_width
            y: i_byte44.y + i_byte44.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 48 "
            _enabled: true
            visible : (message_length > 48) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_48

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 48;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_48 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_48;
            }
        }

        //============= Byte 49  ===============
        RoundedTextInput{
            id: i_byte49
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*1)
            width: i_data_section.hor_item_width
            y: i_byte48.y
            height: st_initial_item_height

            _anno: "Byte 49 "
            _enabled: true
            visible : (message_length > 49) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_49

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 49;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_49 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_49;
            }
        }

        //============= Byte 50  ===============
        RoundedTextInput{
            id: i_byte50
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*2)
            width: i_data_section.hor_item_width
            y: i_byte48.y
            height: st_initial_item_height

            _anno: "Byte 50 "
            _enabled: true
            visible : (message_length > 50) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_50

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 50;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_50 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_50;
            }
        }

        //============= Byte 51  ===============
        RoundedTextInput{
            id: i_byte51
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*3)
            width: i_data_section.hor_item_width
            y: i_byte48.y
            height: st_initial_item_height

            _anno: "Byte 51 "
            _enabled: true
            visible : (message_length > 51) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_51

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 51;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_51 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_51;
            }
        }

        //===============================================================
        //============================ ROW 14 ===========================
        //===============================================================

        //============= Byte 52  ===============
        RoundedTextInput{
            id: i_byte52
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*0)
            width: i_data_section.hor_item_width
            y: i_byte48.y + i_byte48.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 52 "
            _enabled: true
            visible : (message_length > 52) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_52

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 52;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_52 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_52;
            }
        }

        //============= Byte 53  ===============
        RoundedTextInput{
            id: i_byte53
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*1)
            width: i_data_section.hor_item_width
            y: i_byte52.y
            height: st_initial_item_height

            _anno: "Byte 53 "
            _enabled: true
            visible : (message_length > 53) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_53

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 53;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_53 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_53;
            }
        }

        //============= Byte 54  ===============
        RoundedTextInput{
            id: i_byte54
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*2)
            width: i_data_section.hor_item_width
            y: i_byte52.y
            height: st_initial_item_height

            _anno: "Byte 54 "
            _enabled: true
            visible : (message_length > 54) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_54

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 54;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_54 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_54;
            }
        }

        //============= Byte 55  ===============
        RoundedTextInput{
            id: i_byte55
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*3)
            width: i_data_section.hor_item_width
            y: i_byte52.y
            height: st_initial_item_height

            _anno: "Byte 55 "
            _enabled: true
            visible : (message_length > 55) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_55

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 55;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_55 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_55;
            }
        }

        //===============================================================
        //============================ ROW 15 ===========================
        //===============================================================

        //============= Byte 56  ===============
        RoundedTextInput{
            id: i_byte56
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*0)
            width: i_data_section.hor_item_width
            y: i_byte52.y + i_byte52.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 56 "
            _enabled: true
            visible : (message_length > 56) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_56

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 56;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_56 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_56;
            }
        }

        //============= Byte 57  ===============
        RoundedTextInput{
            id: i_byte57
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*1)
            width: i_data_section.hor_item_width
            y: i_byte56.y
            height: st_initial_item_height

            _anno: "Byte 57 "
            _enabled: true
            visible : (message_length > 57) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_57

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 57;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_57 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_57;
            }
        }

        //============= Byte 58  ===============
        RoundedTextInput{
            id: i_byte58
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*2)
            width: i_data_section.hor_item_width
            y: i_byte56.y
            height: st_initial_item_height

            _anno: "Byte 58 "
            _enabled: true
            visible : (message_length > 58) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_58

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 58;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_58 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_58;
            }
        }

        //============= Byte 59  ===============
        RoundedTextInput{
            id: i_byte59
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*3)
            width: i_data_section.hor_item_width
            y: i_byte56.y
            height: st_initial_item_height

            _anno: "Byte 59 "
            _enabled: true
            visible : (message_length > 59) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_59

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 59;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_59 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_59;
            }
        }

        //===============================================================
        //============================ ROW 16 ===========================
        //===============================================================

        //============= Byte 60  ===============
        RoundedTextInput{
            id: i_byte60
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*0)
            width: i_data_section.hor_item_width
            y: i_byte56.y + i_byte56.height + vertical_gap
            height: st_initial_item_height

            _anno: "Byte 60 "
            _enabled: true
            visible : (message_length > 60) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_60

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 60;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_60 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_60;
            }
        }

        //============= Byte 61  ===============
        RoundedTextInput{
            id: i_byte61
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*1)
            width: i_data_section.hor_item_width
            y: i_byte60.y
            height: st_initial_item_height

            _anno: "Byte 61 "
            _enabled: true
            visible : (message_length > 61) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_61

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 61;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_61 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_61;
            }
        }

        //============= Byte 62  ===============
        RoundedTextInput{
            id: i_byte62
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*2)
            width: i_data_section.hor_item_width
            y: i_byte60.y
            height: st_initial_item_height

            _anno: "Byte 62 "
            _enabled: true
            visible : (message_length > 62) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_62

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 62;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_62 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_62;
            }
        }

        //============= Byte 63  ===============
        RoundedTextInput{
            id: i_byte63
            x: i_data_section.hor_item_gap + (i_data_section.hor_space_step*3)
            width: i_data_section.hor_item_width
            y: i_byte60.y
            height: st_initial_item_height

            _anno: "Byte 63 "
            _enabled: true
            visible : (message_length > 63) ? (fdcan_inj_msg.fdf_flag) ? true : false : false
            _value: fdcan_inj_msg.data_63

            function update_initial_value(){
                // Check if the input is a valid hex value (0-9, A-F, a-f) and has a length of 2
                var regex = /^(0x)?[0-9A-Fa-f]{1,2}$/;
                var idx = 63;
                if (regex.test(a_txt_input.text)) {
                    if (a_txt_input.text.length === 1) {
                        a_txt_input.text = "0x0" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 2 && !a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 3 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x0" + a_txt_input.text.charAt(2).toLocaleUpperCase();
                    }
                    else if (a_txt_input.length === 4 && a_txt_input.text.startsWith("0x")) {
                        a_txt_input.text = "0x" + a_txt_input.text.charAt(2).toLocaleUpperCase() + a_txt_input.text.charAt(3).toLocaleUpperCase();
                    }
                    fdcan_inj_msg.data_63 =a_txt_input.text;
                }
                else {
                }
                a_txt_input.text = fdcan_inj_msg.data_63;
            }
        }

    } // rect
}


