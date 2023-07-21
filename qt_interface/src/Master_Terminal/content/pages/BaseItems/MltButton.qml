import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import CoreImport


Rectangle {
    /********* size settings ********/
    property int st_border_width: CoreImport._Base_Width_ButtonBorder

    property int st_frame_width: (height/CoreImport._Base_Width_ItemFrame) * 100
    property int st_radius: 50


    property int st_initial_font_pixelSize:  1 + i_frame.height * st_ratio_font_sz
    property int st_font_pixelSize:  st_initial_font_pixelSize
    readonly property int st_font_pixelSize_info: i_label.fontInfo.pixelSize
    property bool st_font_resize: true
    property real st_ratio_font_sz: CoreImport._Base_Ratio_ButtonFont


    /********* colors settings presets ********/
    readonly property string st_R_color: "#FF0000"
    readonly property string st_G_color: "#00FF00"
    readonly property string st_B_color: "#0000FF"
    readonly property string st_Y_color: "#FFCC22"
    readonly property string st_N_color: "#949391"


    property string st_font_color: CoreImport._Base_Color_BaseFont
    property string st_canva_color: CoreImport._Base_Color_ButtonCanva
    property string st_border_color: CoreImport._Base_Color_FrameLight

    /********* values ********/
    property string st_text: "Connect"
    property string st_current_color: st_normal_color

    /********* st_current_color can be **********/
    property string st_normal_color: st_B_color
    property string st_hovered_color: st_normal_color
    property string st_pressed_color: st_normal_color
    property string st_checked_color: st_normal_color


    property bool st_button_mode: false
    property bool st_checkbox_mode: false
    property bool st_checkbox_value: false

    /********* alias ********/

    function chkbx_cmd(){
    }

    function cmd(){/*
        if(st_current_color === st_R_color)
        st_current_color =  st_B_color;
        else if(st_current_color === st_B_color)
        st_current_color =  st_G_color;
        else if(st_current_color === st_G_color)
        st_current_color =  st_Y_color;
        else st_current_color = st_R_color;
        */
    }

    id: root
    width: 450
    height: 200
    radius: st_radius //50
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
        height: root.height - st_frame_width
        anchors.verticalCenter: root.verticalCenter
        anchors.horizontalCenter: root.horizontalCenter
        radius: height / (root.height / st_radius)
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
                if(st_checkbox_mode){
                    st_checkbox_value = st_checkbox_value == false? true : false
                    chkbx_cmd();
                }
                if(st_button_mode)cmd();
            }
        }

        Label {
            id: i_label
            width: i_frame.width //* 0.75
            height: i_frame.height //* 0.35
            anchors.verticalCenter: i_frame.verticalCenter
            anchors.horizontalCenter: i_frame.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            text: st_text
            color: st_font_color

            minimumPointSize: 5
            font.pixelSize: st_font_pixelSize
            fontSizeMode: Text.Fit
        }
    }
    states:[
        State{
            name: "clicked"
            when: (st_button_mode | st_checkbox_mode) & i_frame_mouseArea.pressed
            PropertyChanges{
                target: i_frame
                width: root.width - st_frame_width*0.8
                height: root.height - st_frame_width*0.8
            }
            PropertyChanges{
                target: i_label
                font.bold: true
            }
            PropertyChanges{
                target: root
                st_current_color: st_pressed_color
            }
        },
        State{
            name: "hovered"
            when: (st_button_mode | st_checkbox_mode) & i_frame_mouseArea.containsMouse & !i_frame_mouseArea.pressed & !st_checkbox_value
            PropertyChanges{
                target: root
                border.width: st_border_width * 2
                st_current_color : st_hovered_color
            }
            PropertyChanges{
                target: i_frame
                border.width: st_border_width * 2
            }
            PropertyChanges{
                target: i_label
            }
        },
        State{
            name: "hovered checked"
            when: (st_button_mode | st_checkbox_mode) & i_frame_mouseArea.containsMouse & !i_frame_mouseArea.pressed & st_checkbox_value
            PropertyChanges{
                target: i_frame
                width: root.width - st_frame_width*0.8
                height: root.height - st_frame_width*0.8
            }
            PropertyChanges{
                target: root
                st_current_color: st_checked_color
            }
            PropertyChanges{
                target: i_frame
                border.width: st_border_width * 2
            }
            PropertyChanges{
                target: i_label
                font.bold: true
            }
        },
        State{
            name: "checked"
            when: (st_checkbox_mode & st_checkbox_value) & !i_frame_mouseArea.pressed
            PropertyChanges{
                target: root
                st_current_color: st_checked_color
            }
            PropertyChanges{
                target: i_label
                font.bold: true
            }
        }
    ]
}
