import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "SimpleItems";

DrawerItem {
    /********* size settings ********/
    property int st_container_height: CoreImport._ViewScale_Height_Container
    property int st_container_width: root.width * st_side_margin
    property int st_content_height: 500
    property int st_vertical_margin: (CoreImport._ViewScale_Height_Container - (CoreImport._ViewScale_Height_Container * CoreImport._GeneralDesign_Ratio_ScreenAdjVertContainerCrop))

    /********* colors settings ********/
    property string st_color_bckgrnd: CoreImport._GeneralDesign_Color_ToolBar
    property real st_background_opacity: CoreImport._GeneralDesign_Gradient_Backstage

    /********* values ********/
    st_title_description: _title_text
    st_title_logo: "./png/DrawerItem_View.png"

    /********* translated ********/
    property string _title_text: qsTr("View")
    property string _simple_button_text: qsTr("Simple")
    property string _advanced_button_text: qsTr("Advanced")
    property string _apply_button_text: qsTr("Apply")
    property string _save_button_text: qsTr("Save")

    function retranslateUi() {
        _title_text = qsTr("View")
        _simple_button_text = qsTr("Simple")
        _advanced_button_text = qsTr("Advanced")
        _apply_button_text = qsTr("Apply")
        _save_button_text = qsTr("Save")
    }

    Connections {
        target: qmlTranslator
        function onLanguageChanged(){
            retranslateUi()
        }
    }

    Component.onCompleted:{
        retranslateUi();
    }

    gradient: Gradient {
        orientation:Gradient.Horizontal
        GradientStop { position: 0.0; color: Qt.lighter(st_color_bckgrnd, st_background_opacity) }
        GradientStop { position: CoreImport._DrawerItem_GradientStop; color: "white" }
    }

    /********* alias ********/

    id: root

    MouseArea{
        anchors.fill: root
        onClicked: {
            root.forceActiveFocus()
        }
    }

    Rectangle{
        id: i_simple_advanced_container
        height: st_container_height
        anchors.topMargin: st_vertical_margin
        width: st_container_width
        anchors.top: a_title.bottom
        anchors.horizontalCenter: root.horizontalCenter
        color: "transparent"
        property int inline_margin: width/10

        RoundedButtonChBxA{
            id: i_RoundedButtonChBxA_simple
            anchors.verticalCenter: i_simple_advanced_container.verticalCenter
            width: i_simple_advanced_container.width /3
            height: st_container_height
            isChecked: true
            st_txt: _simple_button_text

            function cmd(){
                if(!isChecked && i_RoundedButtonChBxA_advanced.isChecked){
                    isChecked = true
                    i_RoundedButtonChBxA_advanced.isChecked = false;
                    i_save_apply_container.visible = false
                    i_content_loader.sourceComponent = i_content_Simple
                    i_content_loader.height = i_content_Simple.height
                }
            }
        }

        RoundedButtonChBxA{
            id: i_RoundedButtonChBxA_advanced
            anchors.verticalCenter: i_simple_advanced_container.verticalCenter
            anchors.left: i_RoundedButtonChBxA_simple.right
            anchors.leftMargin: i_simple_advanced_container.inline_margin
            width: i_simple_advanced_container.width /3
            height: st_container_height
            st_txt: _advanced_button_text

            function cmd(){
                if(!isChecked && i_RoundedButtonChBxA_simple.isChecked){
                    i_content_loader.sourceComponent = i_content_Advanced
                    i_content_loader.height = i_content_Advanced.height
                    isChecked = true
                    i_RoundedButtonChBxA_simple.isChecked = false;
                    i_save_apply_container.visible = true

                }
            }
        }
    }

    Rectangle{
        id: i_save_apply_container
        height: st_container_height
        anchors.topMargin: st_vertical_margin
        width: st_container_width
        anchors.top: i_simple_advanced_container.bottom
        anchors.horizontalCenter: root.horizontalCenter
        visible: false
        color: "transparent"
        property int inline_margin: width/10

        RoundedButtonA{
            id: i_RoundedButtonA_apply
            anchors.verticalCenter: i_save_apply_container.verticalCenter
            width: i_save_apply_container.width /3
            height: st_container_height

            st_txt: _apply_button_text
            function cmd(){
                core.test_print()
            }
        }

        RoundedButtonA{
            id: i_RoundedButtonA_save
            anchors.verticalCenter: i_save_apply_container.verticalCenter
            anchors.left: i_RoundedButtonA_apply.right
            anchors.leftMargin: i_save_apply_container.inline_margin
            width: i_save_apply_container.width /3
            height: st_container_height

            st_txt: _save_button_text
            function cmd(){
                core.saveSetting(CoreImport.CoreLoaderMode.LmAppDesign)
            }
        }
    }

    Flickable {
        id: i_flickable
        width: root.width //   * (1.00 - ((1.00 - root.st_side_margin) /2))
        y: i_save_apply_container.visible ? i_save_apply_container.y + i_save_apply_container.height*1.2 : i_simple_advanced_container.y + i_simple_advanced_container.height*1.2 // (i_title.height + i_title.y)
        height:  root.height - i_flickable.y
        contentHeight: i_content_loader.sourceComponent == i_content_Advanced ? (i_content_loader.height + height) : (i_content_loader.height)
        clip: true
        flickDeceleration  : 1500.00
        maximumFlickVelocity : 1500.00
        ScrollBar.vertical:
            ScrollBar {
                policy: ScrollBar.AlwaysOn
        }

        Loader {
            id: i_content_loader
            width: root.width * (1.00 - (1.00 - root.st_side_margin))
            x: i_simple_advanced_container.x
            height: i_content_Advanced.height
            sourceComponent: i_content_Simple

            MouseArea{
                anchors.fill: i_content_loader
                onClicked: {
                    i_content_loader.forceActiveFocus()
                }
            }
        }

        Component {
            id: i_content_Advanced
            Component_DrawerItem_View_Advanced {
            }
        }
        Component {
            id: i_content_Simple
            Component_DrawerItem_View_Simple {
            }
        }

    }
}


