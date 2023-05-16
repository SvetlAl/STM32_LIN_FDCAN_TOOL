import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

AbstractButton {
    /********* size settings ********/

    /********* colors settings ********/
    property string st_overlay_color: CoreImport._GeneralDesign_Color_ToolBarText

    /********* values *********/
    property bool shown_hamburger: true

    /********* alias ********/
    property string _icon_path: CoreImport.toolbar_icons_path
    property string _hamburger_path: _icon_path + "navi_hamburger.png"
    property string _navi_back_path: _icon_path + "navi_back.png"

    id: root
    clip: true   

    function transformArrow(){
        shown_hamburger = false
    }

    function transformHamburger(){
       shown_hamburger = true
    }

    function clickResponse(){
    }

    Rectangle{
        id: i_frame
        anchors.fill: root
        color: "transparent"

        MouseArea{
            id: i_mouse_area
            anchors.fill: i_frame
            hoverEnabled: true
            onClicked:{
                clickResponse();
            }
        }
        Image{
            id: i_image
            source: shown_hamburger ? _hamburger_path : _navi_back_path
            anchors.fill: i_frame

            visible: true
            opacity: 1.0
            antialiasing:  true
            smooth: true
            mipmap: true

            /*
            ColorOverlay {
                id: i_image_overlay
                anchors.fill: i_image
                source: i_image
                color: st_overlay_color
                cached: true
            }*/


            states:[
                State{
                    name: "hovered"
                    when: i_mouse_area.containsMouse & !i_mouse_area.containsPress
                    PropertyChanges{
                        target: i_image
                        opacity: 0.5
                    }
                },
                State{
                    name: "pressed"
                    when: i_mouse_area.containsPress

                    PropertyChanges{
                        target: i_image
                        opacity: 1.00

                    }
                }
            ]
        }

    }
}
