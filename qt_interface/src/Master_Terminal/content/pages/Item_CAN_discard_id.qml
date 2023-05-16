import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import CoreImport
import "SimpleItems";
import "BaseItems";


Rectangle {
    /********* size settings ********/
    //property real st_ratio_height_to_width: CoreImport._SimpleItems_HeightToWidth_Button
    property int st_initial_item_height: CoreImport._Base_Height_Item*1.2
    property int st_total_height: CoreImport._ViewScale_Height_Container
    property int st_side_gap : width/20
    /********* colors settings ********/

    /********* values *********/
    property string st_enable_anno: "Enable"
    property string st_disable_anno: "Disable"
    property string st_textfield_anno: "CAN id"



    /*************************************************************************/
    /*****************   Add to every each text item     *********************/
    /*************************************************************************/

    /********* alias ********/
    property bool st_filter_enabled: false
    property bool st_editable: false
    property string theIdValue: "0"
    property int can_value: 1

    function onclick(){
    }

    function setIdValue(_val){
    }

    function setCanValue(_val){
    }

    id: root
    width: parent.width
    height: st_total_height
    color: "transparent"

    RoundedTextInput{
        id: i_id
        y: 0
        x: 0
        height: root.height
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
        x: i_id.x + i_id.width + st_side_gap
        anchors.bottom: i_id.bottom
        height: root.height
        width: st_side_gap*4
        st_button_mode: st_editable

        st_text: can_value == 1 ? "CAN1" : "CAN2"
        st_normal_color: can_value == 1 ? st_B_color :st_Y_color
        function cmd(){
            root.forceActiveFocus();
            if(can_value ==1 ) can_value = 2
            else can_value = 1
            setCanValue(can_value)
        }
    }

    MltButton{
        id: i_ok_button
        x: i_can_select_button.x + i_can_select_button.width + st_side_gap
        anchors.bottom: i_id.bottom
        height: root.height
        width: st_side_gap*5
        st_button_mode: st_editable

        st_text: st_filter_enabled ? st_disable_anno : st_enable_anno
        st_normal_color: st_filter_enabled ? st_G_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            onclick()
        }
    }

}
