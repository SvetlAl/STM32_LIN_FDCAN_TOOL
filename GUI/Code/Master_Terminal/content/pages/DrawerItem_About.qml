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
    readonly property int st_common_font_pointsize: i_author_text.fontInfo.pointSize

    /********* colors settings ********/
    property string st_color_bckgrnd: CoreImport._GeneralDesign_Color_ToolBar
    property real st_background_opacity: CoreImport._GeneralDesign_Gradient_Backstage
    property string st_clr_text: CoreImport._SimpleItems_Color_ButtonText

    /********* values ********/
    st_title_description: _title_text
    st_title_logo: "./png/DrawerItem_About.png"

    property int composition_side_crop: (width - (width * st_side_margin))/2

    /********* translated ********/
    property string _title_text: qsTr("About")
    property string _edition_text: qsTr("Edition: ")
    property string _version_text: qsTr("Version: ")
    property string _date_text: qsTr("Date: ")
    property string _author_text: qsTr("Author: ")

    property string _about_text_email: '<html><style type="text/css"></style><a href="mailto:svetlal@outlook.com">svetlal@outlook.com</a></html>'
    property string _about_text_git: '<html><style type="text/css"></style><a href="https://github.com/SvetlAl">GitHub</a></html>'
    property string _about_text_youtube: '<html><style type="text/css"></style><a href="https://www.youtube.com/channel/UCRs5WPEHp6iUyqss0WwUV7Q">YouTube</a></html>'

    Connections {
        target: qmlTranslator
        function onLanguageChanged(){
            retranslateUi()
        }
    }

    function retranslateUi() {
        _title_text = qsTr("About")
        _edition_text = qsTr("Edition: ")
        _version_text = qsTr("Version: ")
        _date_text = qsTr("Date: ")
        _author_text = qsTr("Author: ")
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
        id: i_header_rect
        width: st_container_width
        height: st_container_height
        x: composition_side_crop*2

        anchors.top: a_title.bottom
        color: "transparent"

        Label {
            id: i_txt
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            width: i_header_rect.width
            height: i_header_rect.height*0.8
            minimumPointSize: 5
            font.pointSize: st_common_font_pointsize
            color: st_clr_text
            fontSizeMode: Text.Fit
            clip: true

            text: _title_text
        }
    }

    Text{
        id: i_edition_text
        x: composition_side_crop
        anchors.top: i_header_rect.bottom
        width: st_container_width
        height: st_container_height/2
        font.pointSize: st_common_font_pointsize
        smooth: true
        text: _edition_text + CoreImport.app_name
    }
    Text{
        id: i_version_text
        x: composition_side_crop
        anchors.top: i_edition_text.bottom
        width: st_container_width
        height: st_container_height/2
        font.pointSize: st_common_font_pointsize
        smooth: true
        text: _version_text + versionManager.current_interface_version
    }
    Text{
        id: i_date_text
        x: composition_side_crop
        anchors.top: i_version_text.bottom
        width: st_container_width
        height: st_container_height/2
        font.pointSize: st_common_font_pointsize
        smooth: true
        text: _date_text + CoreImport.app_date
    }
    Text{
        id: i_author_text
        x: composition_side_crop
        anchors.top: i_date_text.bottom
        width: st_container_width
        height: st_container_height/2
        // font.pointSize: st_common_font_pointsize
        fontSizeMode: Text.Fit
        minimumPointSize : 10
        font.pointSize: 1 + st_container_height*1.2 * (st_ratio_font_sz)
        smooth: true
        text: _author_text + CoreImport.app_author
    }

    Text{
        id: i_description_text
        x: composition_side_crop
        anchors.top: i_author_text.bottom
        width: st_container_width
        height: contentHeight
        font.pointSize: st_common_font_pointsize
        smooth: true
        wrapMode: Text.WordWrap

        text: CoreImport.app_description
    }

    Rectangle {
        id: i_rect_youtube
        width: st_container_width
        height: st_container_height
        x: composition_side_crop
        anchors.top : i_description_text.bottom
        color: "transparent"
        Image {
            id: img_youtube
            height: i_rect_youtube.height
            width: height
            source: "./png/Youtube.png"
            fillMode: Image.PreserveAspectCrop
            clip: true
            visible: true
            antialiasing:  true
            smooth: true
            mipmap: true
        }
        Text{
            id: i_about_text_youtube
            anchors.left : img_youtube.right
            anchors.verticalCenter: img_youtube.verticalCenter
            font.pointSize: st_common_font_pointsize
            smooth: true
            text: _about_text_youtube
            onLinkActivated: Qt.openUrlExternally("https://www.youtube.com/channel/UCRs5WPEHp6iUyqss0WwUV7Q")
            MouseArea {
                id: mouseArea_youtube
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    Qt.openUrlExternally("https://www.youtube.com/channel/UCRs5WPEHp6iUyqss0WwUV7Q")
                }
            }
        }
    } /* youtube */

    Rectangle {
        id: i_rect_git
        width: st_container_width
        height: st_container_height
        x: composition_side_crop
        anchors.top : i_rect_youtube.bottom
        color: "transparent"
        Image {
            id: img_git
            height: i_rect_git.height
            width: height
            source: "./png/Git.png"
            fillMode: Image.PreserveAspectCrop
            clip: true
            visible: true
            antialiasing:  true
            smooth: true
            mipmap: true
        }
        Text{
            id: i_about_text_git
            anchors.left : img_git.right
            anchors.verticalCenter: img_git.verticalCenter
            font.pointSize: st_common_font_pointsize
            smooth: true
            text: _about_text_git
            onLinkActivated: Qt.openUrlExternally("https://github.com/SvetlAl")
            MouseArea {
                id: mouseArea_git
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    Qt.openUrlExternally("https://github.com/SvetlAl")
                }
            }
        }
    } /* git */

    Rectangle {
        id: i_rect_email
        width: st_container_width
        height: st_container_height
        x: composition_side_crop
        anchors.top : i_rect_git.bottom
        color: "transparent"
        Image {
            id: img_email
            height: i_rect_email.height
            width: height
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
            anchors.left : img_email.right
            anchors.verticalCenter: img_email.verticalCenter
            font.pointSize: st_common_font_pointsize
            smooth: true
            text: _about_text_email
            onLinkActivated: Qt.openUrlExternally("mailto:svetlal@outlook.com")
            MouseArea {
                id: mouseArea_email
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    Qt.openUrlExternally("mailto:svetlal@outlook.com")
                }
            }
        }
    } /* email */

}


