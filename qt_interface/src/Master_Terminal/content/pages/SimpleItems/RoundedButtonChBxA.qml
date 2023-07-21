import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport

Rectangle {
    /********* size settings ********/
    property real st_ratio_height_to_width: CoreImport._SimpleItems_HeightToWidth_Button
    property real st_ratio_font_sz: CoreImport._SimpleItems_Ratio_ButtonFont
    property real st_onpress_mlt: CoreImport._SimpleItems_Ratio_ButtonOnPress
    property int st_border_width: CoreImport._SimpleItems_Width_ButtonBorder

    /********* colors settings ********/
    property string st_clr_active_frame: CoreImport._SimpleItems_Color_FrameActive
    property string st_clr_inactive_frame: CoreImport._SimpleItems_Color_FrameInactive
    property string st_clr_disabled_frame: CoreImport._SimpleItems_Color_FrameDisabled
    property string st_clr_button: CoreImport._SimpleItems_Color_Button
    property string st_clr_text: CoreImport._SimpleItems_Color_ButtonText
    property int st_radius: 80

    /********* values ********/
    property bool isActive: true
    property bool isChecked: false
    property string st_txt: isChecked //qsTr("Button")

    /********* alias ********/
    property alias a_mouse_area: mouseArea



    id: rounded_button
    width: 300
    height: width / st_ratio_height_to_width
    color: "transparent"

    function cmd(){
        /* do something */
        if(isChecked)isChecked = false
        else isChecked = true
    }

    MouseArea{
        id: mouseArea
        anchors.fill: rounded_button
        hoverEnabled: true
        onClicked: {
            if(isActive) cmd()
        }
    }

    Rectangle {
        id: rectangle
        width: rounded_button.width
        height: rounded_button.height
        color: st_clr_button
        radius: st_radius
        border.color: st_clr_inactive_frame
        border.width: st_border_width
    }
    Label {
        id: btn_txt
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text: st_txt
        width: rectangle.width
        height: rectangle.height*0.8
        minimumPointSize: 5
        font.pointSize:  1 + rounded_button.height * st_ratio_font_sz
        color: st_clr_text
        fontSizeMode: Text.Fit
        clip: true
    }

    states:[
        State{
            name: "hovered checked"
            when: mouseArea.containsMouse & !mouseArea.pressed & isActive & rounded_button.isChecked
            PropertyChanges{
                target: rectangle
                border.color: st_clr_active_frame
           //     border.color: st_clr_inactive_frame
                border.width: st_border_width * st_onpress_mlt
            }
            PropertyChanges{
                target: btn_txt
                font.weight: Font.DemiBold
           //     color: st_clr_inactive_frame
            }
        },
        State{
            name: "hovered not checked"
            when: mouseArea.containsMouse & !mouseArea.pressed & isActive & !rounded_button.isChecked
            PropertyChanges{
                target: rectangle
                border.color: st_clr_active_frame
            }
        },
        State{
            name: "selected"
            when: mouseArea.containsMouse & mouseArea.pressed & isActive
            PropertyChanges{
                target: rectangle
                border.color: st_clr_active_frame
                border.width: st_border_width * st_onpress_mlt
            }
            PropertyChanges{
                target: btn_txt
                font.weight: Font.DemiBold
            }
        },
        State{
            name: "checked"
            when: rounded_button.isChecked & rounded_button.isActive
            PropertyChanges{
                target: rectangle
                border.color: st_clr_active_frame
                border.width: st_border_width * st_onpress_mlt
            }
            PropertyChanges{
                target: btn_txt
                font.weight: Font.DemiBold
            }
        },
        State{
            name: "disabled"
            when: !rounded_button.isActive

            PropertyChanges{
                target: btn_txt
                color: st_clr_disabled_frame
                }
            PropertyChanges{
                target: rectangle
                border.color: st_clr_disabled_frame
            }
        }
    ]
}




