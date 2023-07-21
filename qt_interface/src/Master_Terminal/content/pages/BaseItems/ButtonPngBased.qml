import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    /********* size settings ********/
    property real st_size_normal_mlt: 0.8

    /********* colors settings ********/


    /********* values ********/
    required property string st_img_path

    property bool isActive: true
    /********* alias ********/
    property alias a_mouse_area: mouseArea

    id: root
    color: "transparent"

    function cmd(){
        /* do something */
    }

    MouseArea{
        id: mouseArea
        anchors.fill: root
        hoverEnabled: true
        onClicked: {
            if(isActive) cmd()
        }
    }

    Image{
        id: i_image
        anchors.horizontalCenter: root.horizontalCenter
        anchors.verticalCenter: root.verticalCenter
        source: st_img_path
        width: root.width*st_size_normal_mlt
        height: root.height*st_size_normal_mlt

        visible: true
        opacity: 0.8
        antialiasing:  true
        smooth: true
        mipmap: true

        states:[
            State{
                name: "hovered"
                when: mouseArea.containsMouse & !mouseArea.containsPress
                PropertyChanges{
                    target: i_image
                    opacity: 0.9
                    width: root.width*0.9
                    height: root.height*0.9
                }
            },
            State{
                name: "pressed"
                when: mouseArea.containsPress
                PropertyChanges{
                    target: i_image
                    opacity: 1.0
                    width: root.width
                    height: root.height
                }
            }
        ]
    }

}
