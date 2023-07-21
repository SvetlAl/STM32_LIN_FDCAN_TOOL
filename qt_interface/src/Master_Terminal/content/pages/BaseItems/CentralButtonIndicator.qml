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

    property real st_digit_width_mlt: 0.25
    property real st_digit_height_mlt: 0.40

    property int st_digit_width: root.width * st_digit_width_mlt
    property int st_digit_height: root.height * st_digit_height_mlt

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
    // property string st_text: "Connect"
    property string st_current_color: st_B_color

    readonly property int st_max_value: 255
    readonly property int st_min_value: 0
    property int st_value: 0

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

        function value_up(){
            if(st_value !== st_max_value){
                i_0XX.stopAnimation = false
                i_X0X.stopAnimation = false
                i_XX0.stopAnimation = false
                i_0XX.reversed = false
                i_X0X.reversed = false
                i_XX0.reversed = false
                st_value++;
            }
        }

        function value_dwn(){
            if(st_value !== st_min_value){
                i_0XX.stopAnimation = false
                i_X0X.stopAnimation = false
                i_XX0.stopAnimation = false
                i_0XX.reversed = true
                i_X0X.reversed = true
                i_XX0.reversed = true
                st_value--;
            }
        }

        function set_value_without_animation(value){
            if(st_value !== value & value >= st_min_value & value <= st_max_value){
                i_0XX.reposition_flag = true
                i_X0X.reposition_flag = true
                i_XX0.reposition_flag = true

                i_0XX.stopAnimation = true
                i_X0X.stopAnimation = true
                i_XX0.stopAnimation = true
                st_value = value;
                i_0XX.make_reposition();
                i_X0X.make_reposition();
                i_XX0.make_reposition();
            }
        }

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

            Row {
                id: i_digit_frame
                y: (i_frame.height - height)/2
                x: (i_frame.width - width)*0.7
                height: st_digit_height
                width: st_digit_width * 3
                AnimatedDigit{
                    id: i_0XX
                    st_width: st_digit_width
                    st_height: st_digit_height
                    st_font_color: root.st_font_color
                    value: root.st_value / 100
                }
                AnimatedDigit{
                    id: i_X0X
                    st_width: st_digit_width
                    st_height: st_digit_height
                    st_font_color: root.st_font_color
                    value: (root.st_value / 10) % 10
                }
                AnimatedDigit{
                    id: i_XX0
                    st_width: st_digit_width
                    st_height: st_digit_height
                    st_font_color: root.st_font_color
                    value: root.st_value % 10
                }
            }

            gradient: Gradient {
                orientation:Gradient.Horizontal
                GradientStop { position: 0.0; color: st_canva_color }
                GradientStop { position: 3.5; color: "white"}
            }
        }

}

