import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import CoreImport

Rectangle{
    /********* size settings ********/

    /********* colors settings ********/
    property string st_main_color: CoreImport._Base_Color_IconOverlay
    property string st_overlay_color: CoreImport._Base_Color_IconOverlay
    property string st_overlay_color_pressed: Qt.tint(st_overlay_color, "#33333300")
    property string st_backgr_color: "transparent"


    /********* values ********/

    /********* alias ********/
    property string st_img_path: ""

    id: root
    color: st_backgr_color
    width: 100
    height: 100

    function cmd(){
        /* do something */
    }
    MouseArea{
        id: i_mouseArea
        anchors.fill: root
        hoverEnabled: true
        onClicked:{
            cmd();
        }
    }
    Image{
        id: i_img
        source: st_img_path
        width: parent.height
        height: width
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        visible: true
        opacity: 0.8
        antialiasing:  true
        smooth: true
        mipmap: true

        states:[
            State{
                name: "hovered"
                when: i_mouseArea.containsMouse & !i_mouseArea.containsPress
                PropertyChanges{
                    target: i_img
                    width:  parent.height*1.5
                    height:  parent.height*1.5
                    clip: false
                }
                PropertyChanges{
                    target: root
                    z: 90
                    clip: false
                }
            },
            State{
                name: "pressed"
                when: i_mouseArea.containsPress
                PropertyChanges{
                    target: i_img
                    width:  parent.height*2
                    height:  parent.height*2
                    clip: false
                }
                PropertyChanges{
                    target: root
                    z: 90
                    clip: false
                }
            }
        ]
    }
    ColorOverlay {
        id: i_collapse_img_c_overlay
        anchors.fill: i_img
        source: i_img
        color: st_overlay_color
        cached: true
    }
}
