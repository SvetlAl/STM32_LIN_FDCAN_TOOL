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
    height: st_edit_mode ? (st_total_height + st_vertical_gap)*5 : (st_total_height + st_vertical_gap)
    border.width: CoreImport._SimpleItems_Width_ButtonBorder
    border.color: !st_editable ? st_N_color : st_edit_mode ? st_Y_color : st_B_color
    radius: 10
    color: "transparent"

    /********* size settings ********/
    //property real st_ratio_height_to_width: CoreImport._SimpleItems_HeightToWidth_Button
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
    property string st_enable_anno: "Enable"
    property string st_disable_anno: "Disable"
    property string st_textfield_anno: "CAN id"
    property string st_edit_anno: "Edit"
    property string st_accept_anno: "Accept"
    property string st_set_anno: "Set"
    property string st_reset_anno: "Reset"



    /*************************************************************************/
    /*****************   Add to every each text item     *********************/
    /*************************************************************************/

    /********* alias ********/
    property bool st_editable: false
    property bool st_filter_enabled: false
    property bool st_edit_mode: false
    property string theIdValue: "0"
    property int can_value: 1

    property string theByte0: "0"
    property bool enabled_0: false
    function setByte0Value(theIdValue){}
    function enableByte0filter(_val){}
    property string theByte1: "0"
    property bool enabled_1: false
    function setByte1Value(theIdValue){}
    function enableByte1filter(_val){}
    property string theByte2: "0"
    property bool enabled_2: false
    function setByte2Value(theIdValue){}
    function enableByte2filter(_val){}
    property string theByte3: "0"
    property bool enabled_3: false
    function setByte3Value(theIdValue){}
    function enableByte3filter(_val){}
    property string theByte4: "0"
    property bool enabled_4: false
    function setByte4Value(theIdValue){}
    function enableByte4filter(_val){}
    property string theByte5: "0"
    property bool enabled_5: false
    function setByte5Value(theIdValue){}
    function enableByte5filter(_val){}
    property string theByte6: "0"
    property bool enabled_6: false
    function setByte6Value(theIdValue){}
    function enableByte6filter(_val){}
    property string theByte7: "0"
    property bool enabled_7: false
    function setByte7Value(theIdValue){}
    function enableByte7filter(_val){}

    function onclick(){
    }

    function setIdValue(_val){
    }

    function onEditModeChanged(){
    }
    function onCanSelected(_val){
    }

    RoundedTextInput{
        id: i_id
        y: st_vertical_gap/3
        x: 0
        height: st_total_height
        width: st_side_gap*8
        _anno: st_textfield_anno
        _enabled: st_editable
        _value: theIdValue

        function update_initial_value(){
            if(theIdValue != a_txt_input.text){
                theIdValue = a_txt_input.text;
                setIdValue(theIdValue);
            }
        }
    }

    MltButton{
        id: i_can_select_button
        x: i_id.x + i_id.width + st_side_gap/2
        anchors.bottom: i_id.bottom
        height: st_total_height
        width: st_side_gap*3
        st_button_mode: st_editable

        st_text: can_value == 1 ? "CAN1" : "CAN2"
        st_normal_color: can_value == 1 ? st_B_color :st_Y_color
        function cmd(){
            root.forceActiveFocus();
            if(can_value ==1 ) can_value = 2
            else can_value = 1
            onCanSelected(can_value);
        }
    }


    MltButton{
        id: i_edit_button
        x: i_can_select_button.x + i_can_select_button.width + st_side_gap/2
        anchors.bottom: i_id.bottom
        height: st_total_height
        width: st_side_gap*3
        st_button_mode: true

        st_text: st_edit_anno
        st_normal_color: st_edit_mode ? st_Y_color : st_N_color
        function cmd(){
            if(st_editable){
                st_edit_mode = !st_edit_mode
                onEditModeChanged();
            }
        }
    }

    MltButton{
        id: i_ok_button
        x: i_edit_button.x + i_edit_button.width + st_side_gap/2
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

    //===================== Edit mode =======================

    //===================== Bytes 0 1 ============================
    RoundedTextInput{
        id: i_byte0
        y: i_id.y + i_id.height + st_vertical_gap
        x: 0
        height: st_total_height
        width: st_side_gap*4
        _anno: "Byte 0"
        _enabled: true
        visible : st_edit_mode
        _value: theByte0

        function update_initial_value(){
            _value = a_txt_input.text;
            setByte0Value(_value);
        }
    }

    MltButton{
        id: i_byte0_button
        x: i_byte0.x + i_byte0.width + st_side_gap
        anchors.bottom: i_byte0.bottom
        height: st_total_height
        width: st_side_gap*4
        st_button_mode: true
        visible : st_edit_mode

        st_text: enabled_0 ? st_reset_anno : st_set_anno
        st_normal_color: enabled_0 ? st_G_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            enableByte0filter(!enabled_0);
        }
    }

    RoundedTextInput{
        id: i_byte1
        y: i_byte0.y
        x: i_byte0_button.x + i_byte0_button.width + st_side_gap
        height: st_total_height
        width: st_side_gap*4
        _anno: "Byte 1"
        _enabled: true
        visible : st_edit_mode
        _value: theByte1

        function update_initial_value(){
            _value = a_txt_input.text;
            setByte1Value(_value);
        }
    }

    MltButton{
        id: i_byte1_button
        x: i_byte1.x + i_byte1.width + st_side_gap
        anchors.bottom: i_byte0.bottom
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

    //===================== Bytes 2 3 ============================
    RoundedTextInput{
        id: i_byte2
        y: i_byte0.y + i_byte0.height + st_vertical_gap
        x: 0
        height: st_total_height
        width: st_side_gap*4
        _anno: "Byte 2"
        _enabled: true
        visible : st_edit_mode
        _value: theByte2

        function update_initial_value(){
            _value = a_txt_input.text;
            setByte2Value(_value);
        }
    }

    MltButton{
        id: i_byte2_button
        x: i_byte2.x + i_byte2.width + st_side_gap
        anchors.bottom: i_byte2.bottom
        height: st_total_height
        width: st_side_gap*4
        st_button_mode: true
        visible : st_edit_mode

        st_text: enabled_2 ? st_reset_anno : st_set_anno
        st_normal_color: enabled_2 ? st_G_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            enableByte2filter(!enabled_2);
        }
    }

    RoundedTextInput{
        id: i_byte3
        y: i_byte2.y
        x: i_byte2_button.x + i_byte2_button.width + st_side_gap
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

}
