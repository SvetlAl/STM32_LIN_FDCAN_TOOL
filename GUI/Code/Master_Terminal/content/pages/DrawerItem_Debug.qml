import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import CoreImport;
import "SimpleItems";

DrawerItem {
    /********* size settings ********/
    property int st_container_height: CoreImport._ViewScale_Height_Container*2
    property int st_container_width: root.width * st_side_margin
    property real st_ratio_font_sz: CoreImport._SimpleItems_Ratio_ButtonFont/2

    /********* colors settings ********/
    property string st_color_bckgrnd: CoreImport._GeneralDesign_Color_ToolBar
    property real st_background_opacity: CoreImport._GeneralDesign_Gradient_Backstage
    property string st_clr_text: CoreImport._SimpleItems_Color_ButtonText

    /********* values ********/
    st_title_description: _title_text
    st_title_logo: "./png/DrawerItem_Debug.png"

    property int composition_side_crop: (width - (width * st_side_margin))/2

    /********* translated ********/
    property string _title_text: qsTr("Bug report")
    property string _report_bug_text: qsTr("Please report bugs to: ")
    property string _email_text: "svetlal@outlook.com"

    Connections {
        target: qmlTranslator
        function onLanguageChanged(){
            retranslateUi()
        }
    }

    function retranslateUi() {
        _title_text = qsTr("Bug report")
        _report_bug_text = qsTr("Please report bugs to: ")
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

    Rectangle {
        id: i_main_rect
        width: st_container_width
        height: st_container_height
        x: composition_side_crop

        anchors.top: a_title.bottom
        color: "transparent"

        Label {
            id: i_txt
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            width: i_main_rect.width
            height: i_main_rect.height*0.8
            minimumPointSize: 5
            font.pointSize: 1 + i_main_rect.height * st_ratio_font_sz
            color: st_clr_text
            fontSizeMode: Text.Fit
            clip: true

            text: _report_bug_text
        }
    }

    Rectangle {
        id: i_rect_email
        x: composition_side_crop
        width: st_container_width
        height: st_container_height/2
        anchors.top : i_main_rect.bottom
        color: "transparent"
        Image {
            id: img_email
            height: i_rect_email.height
            width: height
            // x: ((root.width/_side_crop)*8)
            source: "./png/Email.png"
            fillMode: Image.PreserveAspectCrop
            clip: true
            visible: true
            antialiasing:  true
            smooth: true
            mipmap: true
        }
        Text{
            id: i_about_text_email
            width: i_rect_email.width - img_email.width
            height: i_rect_email.height
            anchors.left : img_email.right
            anchors.verticalCenter: img_email.verticalCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 1 + st_container_height * (st_ratio_font_sz)
            smooth: true
            text:_email_text
            onLinkActivated: Qt.openUrlExternally("mailto:svetlal@outlook.com")
            fontSizeMode: Text.Fit
            MouseArea {
                id: mouseArea_email
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    Qt.openUrlExternally("mailto:svetlal@outlook.com")
                }
            }
        }
    } /* i_rect_email */
}


