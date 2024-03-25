import QtQuick
import QtQuick.Controls
import QtQuick.Window
import Qt.labs.platform
import CoreImport

Rectangle {
    property int st_top_offset: rounded_textfield_base.height/5
    property int st_text_side_offset_ratio: 15
    property int st_height_total: CoreImport._ViewScale_Height_Container

    /********* size settings ********/
    property real st_ratio_height_to_width: CoreImport._SimpleItems_HeightToWidth_Button
    property real st_onpress_mlt: CoreImport._SimpleItems_Ratio_ButtonOnPress
    property int st_border_width: CoreImport._SimpleItems_Width_ButtonBorder


    /********* colors settings ********/
    property string st_clr_button: "transparent"
    property string st_clr_text: CoreImport._SimpleItems_Color_ButtonText
    property string st_clr_active_frame: CoreImport._SimpleItems_Color_FrameActive
    property string st_clr_inactive_frame: CoreImport._SimpleItems_Color_FrameInactive
    property string st_clr_disabled_frame: CoreImport._SimpleItems_Color_FrameDisabled

    /********* values ********/
    property bool _enabled: true
    property string _anno: "anno"
    property string onclicked_txt: ""
    property string _value: "value"
    function update_initial_value(){
        _value = a_txt_input.text
    }
    /********* alias ********/
    property alias a_txt_input: textInput
    property alias a_text_small: text_small

    signal showTip(string tip)
    onShowTip: function ShowTip(tip){
        i_tooltip.text = tip
        i_tooltip.visible = true
    }


    id: rounded_textfield_base
    width: parent.width
    height:st_height_total  // width / st_ratio_height_to_width
    color: st_clr_button

    MouseArea{
        id: mouseArea
        anchors.fill: rounded_textfield_base
        hoverEnabled: true
        acceptedButtons: Qt.RightButton
        onClicked: {
            textInput.forceActiveFocus();
        }
    }




    /*****************************************************/
    /*****************       frame       *****************/
    /*****************************************************/
    BaseRectCutout {
        id: rectangle
        y: rounded_textfield_base.y + st_top_offset
        width: rounded_textfield_base.width
        height: rounded_textfield_base.height - st_top_offset //temp
        st_radius: 10
        st_border_width: st_border_width
        st_border_color:  st_clr_disabled_frame
        st_fill_color: st_clr_button
        st_cutout_x: st_radius + x + (width/st_text_side_offset_ratio) //temp
        st_cutout_width: rectangle_small.width * 1.05 //rectangle_small.width
        color: st_clr_button
        anchors.bottom: rounded_textfield_base.bottom
        anchors.horizontalCenter: rounded_textfield_base.horizontalCenter
    }
    /*****************************************************/
    /*****************     text input    *****************/
    /*****************************************************/

    TextInput {
        id: textInput
        width: rectangle.width
        height: rectangle.height
        anchors.fill: rectangle
        anchors.margins: rectangle.st_border_width * 2
        text: _value
        font.pixelSize: rectangle.height/2
        wrapMode: Text.WordWrap
        persistentSelection: true
        selectByMouse: true
        color: st_clr_text
        clip: true
        activeFocusOnPress: true
        enabled: _enabled ? true : false
        property bool focusOn: false

        ToolTip {
            id: i_tooltip

            delay: 1000
            timeout: 5000
            visible: false
            text: ""
        }

        onActiveFocusChanged: {
            update_initial_value();
            if(focusOn) focusOn = false
            else focusOn = true

            if (activeFocus & textInput.text === "") {
                textInput.text = onclicked_txt
            } else {
            }
        }

        Keys.onReturnPressed:{
            update_initial_value()
            root.forceActiveFocus()
        }

        Keys.onEnterPressed: {
           // console.log("Keys.onEnterPressed")
            update_initial_value()
            root.forceActiveFocus()
        }
    }

    /*****************************************************/
    /*****************     annotation    *****************/
    /*****************************************************/

    Rectangle {
        id: rectangle_small
        x: rectangle.st_cutout_x + 5 //rectangle.x + rectangle.width/15 + rectangle.radius
        width: text_small.contentWidth
        height: text_small.contentHeight*0.5
        anchors.verticalCenter: rectangle.top
        color: st_clr_button
        visible: true

            Text {
                id: text_small
                anchors.verticalCenter: rectangle_small.verticalCenter
                anchors.horizontalCenter: rectangle_small.horizontalCenter                
                color: st_clr_disabled_frame
                text: _anno
                font.pixelSize: (rectangle.height - rectangle.st_border_width)  /3
            }
        }

    states:[
        State{
            name: "hovered"
            when: mouseArea.containsMouse & !textInput.activeFocus & _enabled
            PropertyChanges{
                target: rectangle
                st_border_color: rounded_textfield_base.st_clr_active_frame
            }
            PropertyChanges{
                target: text_small
                color: rounded_textfield_base.st_clr_active_frame
            }
        },
        State{
            name: "normal"
            when: !mouseArea.containsMouse & !textInput.activeFocus & _enabled
            PropertyChanges{
                target: rectangle
                st_border_color: rounded_textfield_base.st_clr_disabled_frame
                st_border_width: rounded_textfield_base.st_border_width
                st_cutout_width: rectangle_small.width * 1.05 //rectangle_small.width
            }
            PropertyChanges{
                target: text_small
                color: st_clr_disabled_frame
            }
        },
        State{
            name: "selected"
            when: textInput.activeFocus & _enabled
            PropertyChanges{
                target: rectangle
                st_border_color: rounded_textfield_base.st_clr_active_frame
                st_border_width: rounded_textfield_base.st_border_width * st_onpress_mlt
                st_cutout_width: 0
            }
            PropertyChanges{
                target: rectangle_small
                visible: false
            }
        },
        State{
            name: "disabled"
            when: !_enabled
            PropertyChanges{
                target: rectangle
                st_border_color: rounded_textfield_base.st_clr_text
                st_border_width: rounded_textfield_base.st_border_width
                st_cutout_width: rectangle_small.width * 1.05 //rectangle_small.width
            }
            PropertyChanges{
                target: text_small
                color: rounded_textfield_base.st_clr_text
            }
        }
    ]

}




