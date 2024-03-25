import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import CoreImport
import "SimpleItems";
import "BaseItems";


Rectangle {

    id: root
    width: parent.width
    height: st_active ? (st_total_height + st_vertical_gap)*max_rows : (st_total_height + st_vertical_gap)
    border.width: CoreImport._SimpleItems_Width_ButtonBorder
    border.color: st_active ? st_Y_color : st_N_color
    radius: 10
    color: "transparent"

    /********* size settings ********/
    readonly property int max_rows: 3
    property int st_initial_item_height: CoreImport._Base_Height_Item*1.2
    property int st_total_height: CoreImport._ViewScale_Height_Container
    property int st_side_gap : width/20
    property int st_vertical_gap : st_total_height/5

    /********* colors settings ********/

    readonly property string st_R_color: "#FF0000"
    readonly property string st_G_color: "#00FF00"
    readonly property string st_B_color: "#0000FF"
    readonly property string st_Y_color: "#FFCC22"
    readonly property string st_N_color: "#949391"


    /********* values *********/
    property string st_number:  "0"
    property bool st_active:    false
    property string st_b_val:   "0x00"
    property string st_e_val:   "0x00"
    property string st_step:    "0x00"

    // methods
    readonly property int method_off   : 0
    readonly property int method_inc   : 1
    readonly property int method_dec   : 2
    readonly property int method_const : 3
    property int st_method   : 0
    property bool isMethodOff:   st_method == method_off   ? true : false
    property bool isMethodDec:   st_method == method_dec   ? true : false
    property bool isMethodInc:   st_method == method_inc   ? true : false
    property bool isMethodConst: st_method == method_const ? true : false



    property string st_increase_anno:   "++"
    property string st_decrease_anno:   "--"
    property string st_const_anno:      "const"
    property string st_disabled_anno:   "disabled"
    property string st_disable_anno:    "Disable"
    property string st_value_anno:      "value (from) "
    property string st_e_value_anno:    "value range "
    property string st_step_anno:       "step "
    property string st_edit_anno:       "Edit"

    function refreshAll(){
    }
    function edit_checked(){
    }


    /*************************************************************************/
    /*****************   Add to every each text item     *********************/
    /*************************************************************************/
    Text{
        id: i_label
        y: st_vertical_gap/2
        x: root.radius
        width: root.width
        color: st_font_color
        text: "byte " + st_number
        font.pixelSize: st_initial_item_height/4
    }


    RoundedTextInput{
        id: i_value
        y: i_label.y + i_label.height + st_vertical_gap/2
        x: 10
        height: st_initial_item_height
        width: st_side_gap*4
        _anno: st_value_anno
        _enabled: true
        _value: st_b_val

        function update_initial_value(){
            st_b_val = a_txt_input.text;
            refreshAll();
        }
    }

    MltButton{
        id: i_edit_button
        x: i_value.x + i_value.width + st_side_gap
        anchors.bottom: i_value.bottom
        height: st_initial_item_height
        width: st_side_gap*4
        st_button_mode: true

        st_text: st_edit_anno
        st_normal_color: st_active ? st_Y_color :st_N_color
        function cmd(){
            root.forceActiveFocus();
            st_active = !st_active
            edit_checked();
        }
    }


    MltButton{
        id: i_disable_button
        x: i_edit_button.x + i_edit_button.width + st_side_gap
        anchors.bottom: i_value.bottom
        height: st_initial_item_height
        width: st_side_gap*4
        st_button_mode: true

        st_text: isMethodOff ? st_disabled_anno : st_disable_anno
        st_normal_color: isMethodOff ? st_N_color : st_B_color
        function cmd(){
            root.forceActiveFocus();
            st_method = method_off;
            refreshAll();
        }
    }
/*
    MltButton{
        id: i_ok_button
        x: i_disable_button.x + i_disable_button.width + st_side_gap/2
        anchors.bottom: i_id.bottom
        height: st_total_height
        width: st_side_gap*3
        st_button_mode: st_editable

        st_text: st_filter_enabled ? st_disable_anno : st_enable_anno
        st_normal_color: st_filter_enabled ? st_G_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            onclick();
        }
    }
*/
    //===================== Edit mode =======================
    RoundedTextInput{
        id: i_from_to_val
        y: i_value.y + i_value.height + st_vertical_gap
        x: 10
        height: st_initial_item_height
        width: st_side_gap*4
        _anno: st_e_value_anno
        _enabled: (isMethodConst || isMethodOff ) ? false :true
        visible : st_active
        _value: st_e_val

        function update_initial_value(){
            st_e_val = a_txt_input.text;
            refreshAll();
        }
    }

    MltButton{
        id: i_decrease_button
        x: i_from_to_val.x + i_from_to_val.width + st_side_gap
        anchors.bottom: i_from_to_val.bottom
        height: st_initial_item_height
        width: st_side_gap*4
        st_button_mode: true
        visible : st_active
        st_text: st_decrease_anno
        st_normal_color: isMethodDec ? st_R_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            st_method = method_dec;
            refreshAll();
        }
    }

    MltButton{
        id: i_increase_button
        y: i_from_to_val.y
        x: i_decrease_button.x + i_decrease_button.width + st_side_gap
        height: st_initial_item_height
        width: st_side_gap*4
        st_button_mode: true
        visible : st_active
        st_text: st_increase_anno
        st_normal_color: isMethodInc ? st_G_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            st_method = method_inc;
            refreshAll();
        }
    }
/*
    MltButton{
        id: i_byte1_button
        x: i_byte1.x + i_byte1.width + st_side_gap
        anchors.bottom: i_from_to_val.bottom
        height: st_total_height
        width: st_side_gap*4
        st_button_mode: true
        visible : st_edit_mode

        st_text: enabled_1 ? st_reset_anno : st_set_anno
        st_normal_color: enabled_1 ? st_G_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            enableByte1filter(!enabled_1);
        }
    }
*/
    //===================== Row 3 ============================
    RoundedTextInput{
        id: i_step_val
        y: i_from_to_val.y + i_from_to_val.height + st_vertical_gap
        x: 10
        height: st_initial_item_height
        width: st_side_gap*4
        _anno: st_step_anno
        _enabled: (isMethodConst || isMethodOff ) ? false :true
        visible : st_active
        _value: st_step

        function update_initial_value(){
            st_step = a_txt_input.text;
            refreshAll();
        }
    }

    MltButton{
        id: i_const_button
        x: i_step_val.x + i_step_val.width + st_side_gap
        anchors.bottom: i_step_val.bottom
        height: st_initial_item_height
        width: st_side_gap*4
        st_button_mode: true
        visible : st_active

        st_text: st_const_anno
        st_normal_color: isMethodConst ? st_Y_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            st_method = method_const;
            refreshAll();
        }
    }
/*
    RoundedTextInput{
        id: i_byte3
        y: i_byte2.y
        x: i_const_button.x + i_const_button.width + st_side_gap
        height: st_total_height
        width: st_side_gap*4
        _anno: "Byte 3"
        _enabled: true
        visible : st_edit_mode
        _value: theByte3

        function update_initial_value(){
            _value = a_txt_input.text;
            setByte3Value(_value);
        }
    }

    MltButton{
        id: i_byte3_button
        x: i_byte3.x + i_byte3.width + st_side_gap
        anchors.bottom: i_byte3.bottom
        height: st_total_height
        width: st_side_gap*4
        st_button_mode: true
        visible : st_edit_mode

        st_text: enabled_3 ? st_reset_anno : st_set_anno
        st_normal_color: enabled_3 ? st_G_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            enableByte3filter(!enabled_3);
        }
    }

    //===================== Bytes 4 5 ============================
    RoundedTextInput{
        id: i_byte4
        y: i_byte2.y + i_byte2.height + st_vertical_gap
        x: 0
        height: st_total_height
        width: st_side_gap*4
        _anno: "Byte 4"
        _enabled: true
        visible : st_edit_mode
        _value: theByte4

        function update_initial_value(){
            _value = a_txt_input.text;
            setByte4Value(_value);
        }
    }

    MltButton{
        id: i_byte4_button
        x: i_byte4.x + i_byte4.width + st_side_gap
        anchors.bottom: i_byte4.bottom
        height: st_total_height
        width: st_side_gap*4
        st_button_mode: true
        visible : st_edit_mode

        st_text: enabled_4 ? st_reset_anno : st_set_anno
        st_normal_color: enabled_4 ? st_G_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            enableByte4filter(!enabled_4);
        }
    }

    RoundedTextInput{
        id: i_byte5
        y: i_byte4.y
        x: i_byte4_button.x + i_byte4_button.width + st_side_gap
        height: st_total_height
        width: st_side_gap*4
        _anno: "Byte 5"
        _enabled: true
        visible : st_edit_mode
        _value: theByte5

        function update_initial_value(){
            _value = a_txt_input.text;
            setByte5Value(_value);
        }
    }

    MltButton{
        id: i_byte5_button
        x: i_byte5.x + i_byte5.width + st_side_gap
        anchors.bottom: i_byte5.bottom
        height: st_total_height
        width: st_side_gap*4
        st_button_mode: true
        visible : st_edit_mode

        st_text: enabled_5 ? st_reset_anno : st_set_anno
        st_normal_color: enabled_5 ? st_G_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            enableByte5filter(!enabled_5);
        }
    }

    //===================== Bytes 6 7 ============================
    RoundedTextInput{
        id: i_byte6
        y: i_byte4.y + i_byte4.height + st_vertical_gap
        x: 0
        height: st_total_height
        width: st_side_gap*4
        _anno: "Byte 6"
        _enabled: true
        visible : st_edit_mode
        _value: theByte6

        function update_initial_value(){
            _value = a_txt_input.text;
            setByte6Value(_value);
        }
    }

    MltButton{
        id: i_byte6_button
        x: i_byte6.x + i_byte6.width + st_side_gap
        anchors.bottom: i_byte6.bottom
        height: st_total_height
        width: st_side_gap*4
        st_button_mode: true
        visible : st_edit_mode

        st_text: enabled_6 ? st_reset_anno : st_set_anno
        st_normal_color: enabled_6 ? st_G_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            enableByte6filter(!enabled_6);
        }
    }

    RoundedTextInput{
        id: i_byte7
        y: i_byte6.y
        x: i_byte6_button.x + i_byte6_button.width + st_side_gap
        height: st_total_height
        width: st_side_gap*4
        _anno: "Byte 7"
        _enabled: true
        visible : st_edit_mode
        _value: theByte7

        function update_initial_value(){
            _value = a_txt_input.text;
            setByte7Value(_value);
        }
    }

    MltButton{
        id: i_byte7_button
        x: i_byte7.x + i_byte7.width + st_side_gap
        anchors.bottom: i_byte7.bottom
        height: st_total_height
        width: st_side_gap*4
        st_button_mode: true
        visible : st_edit_mode

        st_text: enabled_7 ? st_reset_anno : st_set_anno
        st_normal_color: enabled_7 ? st_G_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            enableByte7filter(!enabled_7);
        }
    }
    */

}
