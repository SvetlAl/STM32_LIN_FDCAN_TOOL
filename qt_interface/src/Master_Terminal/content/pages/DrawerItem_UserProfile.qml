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
    st_title_description: _title_text  + CoreImport.current_user
    st_title_logo: "./png/DrawerItem_UserProfile.png"

    /********* translated ********/
    property string _title_text: qsTr("User profile: ")
    property string _save_button_text: qsTr("Save")
    property string _new_button_text: qsTr("New")
    property string _edit_button_text: qsTr("Edit")
    property string _load_button_text: qsTr("Load")
    property string _back_button_text: qsTr("Back")
    property string _delete_button_text: qsTr("Delete")
    property string _yes_button_text: qsTr("Yes")
    property string _no_button_text: qsTr("No")
    property string _select_button_text: qsTr("Select")

    Connections {
        target: qmlTranslator
        function onLanguageChanged(){
            retranslateUi()
        }
    }

    function retranslateUi() {
        _title_text = qsTr("User profile: ")
        _save_button_text = qsTr("Save")
        _new_button_text = qsTr("New")
        _edit_button_text = qsTr("Edit")
        _load_button_text = qsTr("Load")
        _back_button_text = qsTr("Back")
        _delete_button_text = qsTr("Delete")
        _yes_button_text: qsTr("Yes")
        _no_button_text: qsTr("No")
        _select_button_text: qsTr("Select")
    }

    Component.onCompleted:{
        retranslateUi();
    }

    /********* alias and properties ********/
    property string _current_user: CoreImport.current_user
    property string _selected_user: CoreImport.current_user

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

    function setEnabledButtons(){
        var args = [];
        for (var m = 0; m < arguments.length; m++) {
          args[m] = arguments[m];
        }

        for(var i = i_control_buttons_container.children.length; i > 0 ; i--) {
            var _item = i_control_buttons_container.children[i-1];
            if(_item.type === "ctl_button"){
                _item.visible = false;
                _item.isActive = false;

                for(var k = 0; k < args.length; k++){
                    if(_item.id_p === args[k]){
                        _item.visible = true;
                        _item.isActive = true;
                    }
                }
            }
        }
    }

    property var _page_mode: CoreImport.ProfileMenuMode.Edit

    function set_mode(mode){
        switch(mode){
            case CoreImport.ProfileMenuMode.Edit:
                _page_mode = CoreImport.ProfileMenuMode.Edit;
                root.forceActiveFocus()
                i_content_loader.sourceComponent = i_content_Userdata
                i_content_loader.item.switchEditNewMode(mode)
                setEnabledButtons("i_RoundedButtonA_new_1", "i_RoundedButtonA_save_2", "i_RoundedButtonA_load_3")
                _selected_user = _current_user
                break;
            case CoreImport.ProfileMenuMode.New:
                _page_mode = CoreImport.ProfileMenuMode.New;
                root.forceActiveFocus()
                i_content_loader.sourceComponent = i_content_Userdata
                i_content_loader.item.switchEditNewMode(mode)
                setEnabledButtons("i_RoundedButtonA_edit_1", "i_RoundedButtonA_save_2", "i_RoundedButtonA_load_3")
                _selected_user = i_content_loader.item._current_user
                break;
            case CoreImport.ProfileMenuMode.Select:
                _page_mode = CoreImport.ProfileMenuMode.Select;
                root.forceActiveFocus()
                i_content_loader.sourceComponent = i_content_Userlist
                setEnabledButtons("i_RoundedButtonA_select_1", "i_RoundedButtonA_delete_2", "i_RoundedButtonA_back_3")
                _selected_user = i_content_loader.item._selected_user
                break;
            case CoreImport.ProfileMenuMode.Delete:
                _page_mode = CoreImport.ProfileMenuMode.Delete;
                root.forceActiveFocus()
                setEnabledButtons("i_RoundedButtonA_yes_1", "i_RoundedButtonA_no_3")
                _selected_user = i_content_loader.item._selected_user
                break;
            default:
                break;
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
        /*********************** NEW ***********************/
        RoundedButtonA{
            id: i_RoundedButtonA_new
            anchors.verticalCenter: i_control_buttons_container.verticalCenter
            anchors.left: i_control_buttons_container.left
            width: (i_control_buttons_container.width/4)
            height: i_control_buttons_container.height * st_cont_vertical_margin
            visible: true
            property string type: "ctl_button"
            property string id_p: "i_RoundedButtonA_new_1"

            st_txt: _new_button_text
            function cmd(){
                set_mode(CoreImport.ProfileMenuMode.New);
            }
        }

        /*********************** SELECT ***********************/
        RoundedButtonA{
            id: i_RoundedButtonA_select
            anchors.verticalCenter: i_control_buttons_container.verticalCenter
            anchors.left: i_control_buttons_container.left
            width: (i_control_buttons_container.width/4)
            height: i_control_buttons_container.height * st_cont_vertical_margin
            isActive: false
            visible: false
            property string type: "ctl_button"
            property string id_p: "i_RoundedButtonA_select_1"

            st_txt: _select_button_text
            function cmd(){
                /* set current user */
                _selected_user = i_content_loader.item._selected_user
                core.setUserProfile(_selected_user)
                set_mode(CoreImport.ProfileMenuMode.Edit);
            }
        }

        /*********************** EDIT ***********************/
        RoundedButtonA{
            id: i_RoundedButtonA_edit
            anchors.verticalCenter: i_control_buttons_container.verticalCenter
            anchors.left: i_control_buttons_container.left
            width: (i_control_buttons_container.width/4)
            height: i_control_buttons_container.height * st_cont_vertical_margin
            isActive: false
            visible: false
            property string type: "ctl_button"
            property string id_p: "i_RoundedButtonA_edit_1"

            st_txt: _edit_button_text
            function cmd(){
                set_mode(CoreImport.ProfileMenuMode.Edit);
            }
        }
        /*********************** YES ***********************/
        RoundedButtonA{
            id: i_RoundedButtonA_yes
            anchors.verticalCenter: i_control_buttons_container.verticalCenter
            anchors.left: i_control_buttons_container.left
            width: (i_control_buttons_container.width/4)
            height: i_control_buttons_container.height * st_cont_vertical_margin
            isActive: false
            visible: false
            property string type: "ctl_button"
            property string id_p: "i_RoundedButtonA_yes_1"

            st_txt: _yes_button_text
            function cmd(){
                /* delete current user */
                core.deleteUserProfile(_selected_user);
                set_mode(CoreImport.ProfileMenuMode.Select);
                i_content_loader.item._selected_user = "default"
                i_content_loader.item.init();
            }
        }
        /******************** 2nd button *******************/
        /*********************** SAVE ***********************/
        RoundedButtonA{
            id: i_RoundedButtonA_save
            anchors.verticalCenter: i_control_buttons_container.verticalCenter
            anchors.horizontalCenter: i_control_buttons_container.horizontalCenter
            width: (i_control_buttons_container.width/4)
            height: i_control_buttons_container.height * st_cont_vertical_margin
            property string type: "ctl_button"
            property string id_p: "i_RoundedButtonA_save_2"

            st_txt: _save_button_text
            function cmd(){
                root.forceActiveFocus();
                i_content_loader.item.applyChanges();

                if(i_content_loader.item._mode === CoreImport.ProfileMenuMode.New){
                    _selected_user = i_content_loader.item._current_user
                    core.validateUserProfile();
                    core.createUserProfile();
                    console.log(_selected_user);
                    core.setUserProfile(_selected_user)
                    set_mode(CoreImport.ProfileMenuMode.Edit);
                }
                else{
                    core.saveSetting(CoreImport.CoreLoaderMode.LmUserProfile)
                }
            }
        }

        /*********************** DELETE ***********************/
        RoundedButtonA{
            id: i_RoundedButtonA_delete
            anchors.verticalCenter: i_control_buttons_container.verticalCenter
            anchors.horizontalCenter: i_control_buttons_container.horizontalCenter
            width: (i_control_buttons_container.width/4)
            height: i_control_buttons_container.height * st_cont_vertical_margin
            isActive: false
            visible: false
            property string type: "ctl_button"
            property string id_p: "i_RoundedButtonA_delete_2"

            st_txt: _delete_button_text
            function cmd(){
                set_mode(CoreImport.ProfileMenuMode.Delete);
            }
        }

        /******************** 3rd button *******************/
        /*********************** LOAD ***********************/
        RoundedButtonA{
            id: i_RoundedButtonA_load
            anchors.verticalCenter: i_control_buttons_container.verticalCenter
            anchors.right: i_control_buttons_container.right
            width: (i_control_buttons_container.width/4)
            height: i_control_buttons_container.height * st_cont_vertical_margin
            property string type: "ctl_button"
            property string id_p: "i_RoundedButtonA_load_3"

            st_txt: _load_button_text
            function cmd(){
                set_mode(CoreImport.ProfileMenuMode.Select);
            }
        }
        /*********************** NO ***********************/
        RoundedButtonA{
            id: i_RoundedButtonA_no
            anchors.verticalCenter: i_control_buttons_container.verticalCenter
            anchors.right: i_control_buttons_container.right
            width: (i_control_buttons_container.width/4)
            height: i_control_buttons_container.height * st_cont_vertical_margin
            isActive: false
            visible: false
            property string type: "ctl_button"
            property string id_p: "i_RoundedButtonA_no_3"

            st_txt: _no_button_text
            function cmd(){
                set_mode(CoreImport.ProfileMenuMode.Select);
            }
        }

        /*********************** BACK ***********************/
        RoundedButtonA{
            id: i_RoundedButtonA_back
            anchors.verticalCenter: i_control_buttons_container.verticalCenter
            anchors.right: i_control_buttons_container.right
            width: (i_control_buttons_container.width/4)
            height: i_control_buttons_container.height * st_cont_vertical_margin
            isActive: false
            visible: false
            st_txt: _back_button_text
            property string type: "ctl_button"
            property string id_p: "i_RoundedButtonA_back_3"

            function cmd(){
                set_mode(CoreImport.ProfileMenuMode.Edit);
            }
        }
    }
    Flickable {
        id: i_flickable
        width: root.width //   * (1.00 - ((1.00 - root.st_side_margin) /2))
        y: i_control_buttons_container.y + i_control_buttons_container.height
        height:  root.height - i_flickable.y
        contentHeight: i_content_loader.height// + height
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
            height: i_content_Userlist.height
            sourceComponent: i_content_Userdata
        }

        Connections {
            target: i_content_loader.item
            function onSendHeight(msg) {
                i_content_loader.height = msg
            }
        }

        Component {
            id: i_content_Userdata
            Component_DrawerItem_UserProfile_Userdata {
            }
        }
        Component {
            id: i_content_Userlist
            Component_DrawerItem_UserProfile_Userlist {
            }
        }
    }

}


