import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import CoreImport

Rectangle {
    /********* size settings ********/
    property int st_border_width:CoreImport._Base_Width_ButtonBorder
    property int st_frame_width: width/10
    property int st_size: 450

    /********* colors settings ********/
    readonly property string st_R_color: "#FF0000"
    readonly property string st_G_color: "#33AA33"
    readonly property string st_B_color: "#0000FF"
    readonly property string st_Y_color: "#FFCC22"
    readonly property string st_N_color: "#949391"

    property string st_font_color: CoreImport._Base_Color_BaseFont
    property string st_canva_color: CoreImport._Base_Color_ButtonCanva
    property string st_border_color: CoreImport._Base_Color_FrameLight

    /********* values ********/
    property string st_text: "Connect"
    property string st_current_color: st_B_color

    /********* alias ********/
    property var st_button_colors: [st_R_color, st_G_color, st_B_color]

    function cmd(){
        if(st_current_color === st_R_color)
        st_current_color =  st_B_color;
        else if(st_current_color === st_B_color)
        st_current_color =  st_G_color;
        else if(st_current_color === st_G_color)
        st_current_color =  st_Y_color;
        else st_current_color = st_R_color;
    }

    id: root
    width: st_size
    height: width
    radius: width/2
    border.color: st_border_color
    border.width: st_border_width

    gradient: Gradient {
        orientation:Gradient.Horizontal
        GradientStop { position: 0.0; color: st_current_color }
        GradientStop { position: 1.5; color: "white"}
    }

    Rectangle{
        id: i_frame
        width: root.width - st_frame_width
        height: width
        anchors.verticalCenter: root.verticalCenter
        anchors.horizontalCenter: root.horizontalCenter
        radius: width/2
        border.color: st_border_color
        border.width: st_border_width

        gradient: Gradient {
            orientation:Gradient.Horizontal
            GradientStop { position: 0.0; color: st_canva_color }
            GradientStop { position: 3.5; color: "white"}
        }

        MouseArea{
            id: i_frame_mouseArea
            anchors.fill: i_frame
            hoverEnabled: true
            onClicked: {
              cmd();
            }
        }

        Label {
            id: i_label
            width: i_frame.width * 0.75
            height: i_frame.height * 0.35
            anchors.verticalCenter: i_frame.verticalCenter
            anchors.horizontalCenter: i_frame.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            text: st_text
            color: st_font_color

            minimumPointSize: 5
            font.pointSize: 600
            fontSizeMode: Text.Fit
        }
    }
    states:[
        State{
            name: "clicked"
            when: i_frame_mouseArea.pressed
            PropertyChanges{
                target: root
                st_frame_width: width/8
            }
            PropertyChanges{
                target: i_label
                font.bold: true
            }
        },
        State{
            name: "hovered"
            when: i_frame_mouseArea.containsMouse & !i_frame_mouseArea.pressed
            PropertyChanges{
                target: root
                st_frame_width: width/9
            }
        }
    ]
}
