import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;

Rectangle {
    /********* size settings ********/
    property real st_side_margin: CoreImport._GeneralDesign_Ratio_ScreenAdjSideCrop
    property real st_cont_vertical_margin: CoreImport._GeneralDesign_Ratio_ScreenAdjVertContainerCrop
    /********* colors settings ********/

    /********* values ********/

    /********* alias ********/
    property alias a_title: i_title

    id: root
    width: parent.width
    height: parent.height

    property string st_title_description: "description"
    property string st_title_logo: "logo"

    MouseArea{
        id: mouseArea
        anchors.fill: root
        hoverEnabled: true
        onClicked:{
            root.forceActiveFocus()
        }
    }

    Title{
        id: i_title
        st_description: st_title_description
        st_logo: st_title_logo
        anchors.top: root.top
        clip: true
    }
}
