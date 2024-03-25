import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import CoreImport;
import "SimpleItems";

DrawerItem {
    /********* size settings ********/
    property int st_container_height: CoreImport._ViewScale_Height_Container
    property int st_container_width: root.width * st_side_margin
    property real st_ratio_font_sz: CoreImport._SimpleItems_Ratio_ButtonFont/2


    /********* colors settings ********/
    property string st_color_bckgrnd: CoreImport._GeneralDesign_Color_ToolBar
    property real st_background_opacity: CoreImport._GeneralDesign_Gradient_Backstage

    /********* values ********/
    st_title_description: _title_text
    st_title_logo: "./png/DrawerItem_Help.png"

    property int composition_side_crop: (width - (width * st_side_margin))/2

    /********* translated ********/
    property string _title_text: qsTr("Help: ")

    Connections {
        target: qmlTranslator
        function onLanguageChanged(){
            retranslateUi()
        }
    }

    function retranslateUi() {
        _title_text = qsTr("Help: ")
    }

    Component.onCompleted:{
        retranslateUi();
    }

    /********* alias and properties ********/

    id: root

    gradient: Gradient {
        orientation:Gradient.Horizontal
        GradientStop { position: 0.0; color: Qt.lighter(st_color_bckgrnd, st_background_opacity) }
        GradientStop { position: CoreImport._DrawerItem_GradientStop; color: "white" }
    }

    MouseArea{
        anchors.fill: root
        onClicked: {
            root.forceActiveFocus()
        }
    }

    Flickable {
        id: i_flickable
      //  x: composition_side_crop
        width: root.width
        height:  root.height - i_flickable.y
        anchors.top: a_title.bottom
       // property int extra_height: st_container_height*10
        contentHeight: i_content_loader.height // + extra_height
        clip: true
        flickDeceleration  : 1500.00
        maximumFlickVelocity : 1500.00
        ScrollBar.vertical:
            ScrollBar {
                policy: ScrollBar.AlwaysOn
        }

        Loader {
            id: i_content_loader
            height: i_content_Help_Main.height
            sourceComponent: i_content_Help_Main
        }

        Connections {
            target: i_content_loader.item
            function onSendHeight(msg) {
                i_content_loader.height = msg
            }
        }

        Component {
            id: i_content_Help_Main
            Component_DrawerItem_Help_Main {
            }
        }
    }

}
