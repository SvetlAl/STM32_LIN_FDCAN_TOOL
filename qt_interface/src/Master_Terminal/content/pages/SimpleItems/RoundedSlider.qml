import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import CoreImport;



Item {
    /********* size settings ********/
    property real st_height_mlt : 0.5
    property int st_handle_height: root.height
    property int st_border_width : CoreImport._SimpleItems_Width_ButtonBorder
    property real st_radius: 0.8

    /********* colors settings ********/
    property string st_clr_active_frame: CoreImport._SimpleItems_Color_FrameActive
    property string st_clr_inactive_frame: CoreImport._SimpleItems_Color_FrameInactive
    property string st_clr_button: CoreImport._SimpleItems_Color_Button
    property string st_clr_text: CoreImport._SimpleItems_Color_ButtonText

    property string st_clr_disabled_frame: CoreImport._SimpleItems_Color_FrameDisabled

    /********* values ********/
    property string onclicked_txt: ""
    property string st_labelTxt: i_slider.value.toString()
    property int _value : 5
    property int _from: 0
    property int _to: 200
    property int _step: 1
    function update_initial_value(){}
    /********* alias ********/



    id: root
    height: (parent.height/3)*2
    width: 400 /* manual */

    property string _handle_color: st_clr_inactive_frame
    property string _frame_color: st_clr_text
    property string _filled_color: st_clr_inactive_frame
    property string _unfilled_color: st_clr_button

    Slider {
        id: i_slider
        height: root.height
        width: root.width
        anchors.verticalCenter: root.verticalCenter

        value: _value
        from: _from
        to: _to
        stepSize: _step

        onMoved: {      
            _value = value
            update_initial_value()
        }

        onPressedChanged: {
            if( pressed ) {
                _handle_color = st_clr_active_frame
                _frame_color = st_clr_active_frame
                update_initial_value()
                }
            else {
                update_initial_value()
                _frame_color = st_clr_text
                _handle_color = st_clr_inactive_frame
            }
        }

        handle: Item {
            height: st_handle_height
            width: st_handle_height
            anchors.verticalCenter: i_slider.verticalCenter

            x: i_slider.leftPadding + i_slider.visualPosition * (i_slider.availableWidth - width)
            Behavior on x {
                NumberAnimation {
                    easing.type: Easing.Linear
                    onRunningChanged: {
                        if (!running) {
                            enabled = true
                        }
                        else enabled = true
                    }
                }
            } /* Behavior on x ENDS */

            Rectangle {
                //anchors.fill: parent
                width: parent.width *1.2
                height: parent.height *1.2
                color: st_clr_button
                radius: st_radius*height
                border.color: _handle_color
                border.width: st_border_width
                clip : true

                Label {
                    text: st_labelTxt
                    width: i_slider.value < 10 ? parent.width : parent.width*0.8
                    height: i_slider.value < 10 ? parent.height : parent.height*0.8
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenterOffset: calculate_offset(i_slider.value)
                    color: st_clr_text
                    minimumPointSize: 5
                    font.pointSize: 500
                    fontSizeMode: Text.Fit

                    function calculate_offset(slider_val){
                        if(slider_val < 10){
                            return parent.width*0.3
                        }
                        else if(slider_val > 9 & slider_val < 100){
                            return parent.width*0.08
                        }
                        else return 0;
                    }
                }
            }
        } /* handler ENDS */

        background:

            Item{
            width: i_slider.width
            height: parent.height*st_height_mlt

            Rectangle {
                id: _r1
                x: i_slider.leftPadding
                y: i_slider.topPadding + i_slider.availableHeight / 2 - height / 2
                width: i_slider.availableWidth
                height: parent.height
                radius: st_radius*height
                color: _unfilled_color
                border.color: _frame_color
                border.width: st_border_width/2

            Behavior on width {
                NumberAnimation {
                    easing.type: Easing.Linear
                }
            } /* Behavior on x ENDS */

}
            Rectangle {
                id: _r2
                x: i_slider.leftPadding + st_border_width/2
                y: i_slider.topPadding + i_slider.availableHeight / 2 - height / 2
                width: i_slider.visualPosition > 0.5 ? i_slider.visualPosition*_r1.width: i_slider.visualPosition*_r1.width + st_handle_height/2
                height: parent.height - st_border_width
                radius: st_radius*height
                gradient: Gradient {
                    orientation:Gradient.Horizontal
                    GradientStop { position: 0.0; color: _filled_color }
                    GradientStop { position: 1.2; color: _unfilled_color }
                }
                Behavior on width {
                    NumberAnimation {
                        easing.type: Easing.Linear
                    }
                } /* Behavior on x ENDS */

            }
        }
    }
}

