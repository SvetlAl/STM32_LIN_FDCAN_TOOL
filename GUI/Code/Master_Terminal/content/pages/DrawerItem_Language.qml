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

    /********* colors settings ********/
    property string st_color_bckgrnd: CoreImport._GeneralDesign_Color_ToolBar
    property real st_background_opacity: CoreImport._GeneralDesign_Gradient_Backstage

    /********* values ********/
    st_title_description: _title_text + _current_language
    st_title_logo: "./png/DrawerItem_Language.png"

    /********* translated ********/
    property string _title_text: qsTr("Curent language: ")
    property string _save_button_text: qsTr("Save")
    property string _apply_button_text: qsTr("Apply")

    Connections {
        target: qmlTranslator
        function onLanguageChanged(){
            retranslateUi()
        }
    }

    function retranslateUi() {
        _title_text = qsTr("Curent language: ")
        _save_button_text = qsTr("Save")
        _apply_button_text = qsTr("Apply")
    }

    Component.onCompleted:{
        retranslateUi();
    }

    function setSelectedLanguage(msg) {
        _selected_language = msg
    }
    function setCurrentLanguage() {
        i_content_loader.item._current_language = _selected_language
        _current_language = _selected_language
        core.setUserProfileValue(CoreImport.ProfileMembers.Language, _current_language);
        qmlTranslator.setTranslation(_current_language)
        CoreImport.current_language = _selected_language
    }
    function saveLanguageSettings(){
        core.setUserProfileValue(CoreImport.ProfileMembers.Language, _current_language);
        core.saveSetting(CoreImport.CoreLoaderMode.LmUserProfile);
    }

    /********* alias and properties ********/
    property string _current_language: CoreImport.current_language
    property string _selected_language: CoreImport.current_language

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

    Rectangle{
        id: i_control_buttons_container
        height: st_container_height
        width: st_container_width
        anchors.top: a_title.bottom
        color: "transparent"
        anchors.horizontalCenter: root.horizontalCenter
        property int inline_margin: width/10

        /******************** 1st button *******************/
        /*********************** APPLY ***********************/
        RoundedButtonA{
            id: i_RoundedButtonA_apply
            anchors.verticalCenter: i_control_buttons_container.verticalCenter
          //  anchors.left: i_control_buttons_container.left
            width: i_control_buttons_container.width /3
            height: i_control_buttons_container.height * st_cont_vertical_margin
            property string type: "ctl_button"
            property string id_p: "i_RoundedButtonA_apply_1"
            st_txt: _apply_button_text

            function cmd(){
                setCurrentLanguage();
            }
        }
        /******************** 2nd button *******************/
        /*********************** SAVE ***********************/
        RoundedButtonA{
            id: i_RoundedButtonA_save
            anchors.verticalCenter: i_control_buttons_container.verticalCenter
            anchors.left: i_RoundedButtonA_apply.right
            anchors.leftMargin: i_control_buttons_container.inline_margin
            width: i_control_buttons_container.width /3
            height: i_control_buttons_container.height * st_cont_vertical_margin

            property string type: "ctl_button"
            property string id_p: "i_RoundedButtonA_save_2"
            st_txt: _save_button_text

            function cmd(){
                saveLanguageSettings();
            }
        }
    }

    Flickable {
        id: i_flickable
        width: root.width
        y: i_control_buttons_container.y + i_control_buttons_container.height
        height:  root.height - i_flickable.y
        contentHeight: i_content_loader.height
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
            x: i_control_buttons_container.x
            height: i_content_LanguageList.height
            sourceComponent: i_content_LanguageList
        }

        Connections {
            target: i_content_loader.item
            function onSendHeight(msg) {
                i_content_loader.height = msg
            }
        }

        Connections {
            target: i_content_loader.item
            function onSetSelectedLanguage(msg) {
                setSelectedLanguage(msg)
            }
        }

        Component {
            id: i_content_LanguageList
            Component_DrawerItem_Language_Languagelist {
            }
        }
    }

}
