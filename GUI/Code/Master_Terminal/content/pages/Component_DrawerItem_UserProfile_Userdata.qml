import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "SimpleItems";

Item {
    /********* size settings ********/
    property int st_label_font_sz: CoreImport._SimpleItems_Font_Main
    property int st_height_items: CoreImport._ViewScale_Height_Container
    property real st_vertical_margin: CoreImport._ViewScale_Height_Container - (CoreImport._ViewScale_Height_Container * CoreImport._GeneralDesign_Ratio_ScreenAdjVertContainerCrop)
    /********* colors settings ********/
    property string st_text_color: CoreImport._SimpleItems_Color_ButtonText
    /********* values ********/
    // property int st_ViewScale_Height_Container: core._ViewScale_Height_Container

    /********* translated ********/
    property string st_description_edit: qsTr("User profile: ")
    property string st_description_new: qsTr("Create a new user")
    property string st_Name_anno: qsTr("Name")
    property string st_Language_anno: qsTr("Language")
    property string st_Email_anno: qsTr("Email")
    property string st_PhoneNumber_anno: qsTr("Phone number")

    function retranslateUi() {
        st_description_edit = qsTr("User profile: ")
        st_description_new = qsTr("Create a new user")
        st_Name_anno = qsTr("Name")
        st_Language_anno = qsTr("Language")
        st_Email_anno = qsTr("Email")
        st_PhoneNumber_anno = qsTr("Phone number")
    }
    Connections {
        target: qmlTranslator
        function onLanguageChanged(){
            retranslateUi()
        }
    }

    signal applyChanges()
    onApplyChanges: function ApplyChanges(){
        core.setUserProfileValue(CoreImport.ProfileMembers.Name, i_name_val._value)
        core.setUserProfileValue(CoreImport.ProfileMembers.Email, i_email_val._value)
        core.setUserProfileValue(CoreImport.ProfileMembers.Phone, i_phone_val._value)
        _current_user = CoreImport.current_user
    }

    signal switchEditNewMode(int mode)
    onSwitchEditNewMode: function SwitchEditNewMode(mode){
        root.forceActiveFocus()
        if(mode === CoreImport.ProfileMenuMode.New){
            _mode = CoreImport.ProfileMenuMode.New
            i_name_val.a_txt_input.text = ""
            i_name_val._value = ""
            i_name_val._enabled = true
            i_language_val.a_txt_input.text = "English"
            i_language_val._value = "English"
            i_email_val.a_txt_input.text = ""
            i_email_val._value = ""
            i_phone_val.a_txt_input.text = ""
            i_phone_val._value = ""
        }
        else if(mode === CoreImport.ProfileMenuMode.Edit){
            _mode = CoreImport.ProfileMenuMode.Edit

            i_name_val.a_txt_input.text = CoreImport.current_user
            i_name_val._value = CoreImport.current_user
            i_name_val._enabled = false
            i_language_val.a_txt_input.text = core.getUserProfileValue(CoreImport.ProfileMembers.Language)
            i_language_val._value = core.getUserProfileValue(CoreImport.ProfileMembers.Language)
            i_email_val.a_txt_input.text = core.getUserProfileValue(CoreImport.ProfileMembers.Email)
            i_email_val._value = core.getUserProfileValue(CoreImport.ProfileMembers.Email)
            i_phone_val.a_txt_input.text = core.getUserProfileValue(CoreImport.ProfileMembers.Phone)
            i_phone_val._value = core.getUserProfileValue(CoreImport.ProfileMembers.Phone)
        }
    }


    Component.onCompleted:{
        retranslateUi();
        calculateHeight();
    }

    MouseArea{
        property string type: "focus_reset"
        anchors.fill: root
        onClicked: {
            root.forceActiveFocus()
        }
    }

    signal sendHeight(int msg)
    function calculateHeight(){
        var total_height = 0
        for(var i = root.children.length; i > 0 ; i--) {
            if(root.children[i-1].type !== "focus_reset"){
                total_height += root.children[i-1].height
                total_height += root.children[i-1].anchors.topMargin
            }
        }
        root.height = total_height
        sendHeight(total_height)
    }

    /********* alias and properties ********/
    property int _mode: CoreImport.ProfileMenuMode.Edit
    property string _current_user: CoreImport.current_user

    id: root
    width: parent.width


    Label {
        id: i_label
        parent: root
        height: st_height_items
        width: parent.width
        text: _mode === CoreImport.ProfileMenuMode.Edit ? st_description_edit  + _current_user : st_description_new
        color: st_text_color
        minimumPointSize: 5
        font.pointSize: st_label_font_sz
        fontSizeMode: Text.Fit
    }

    RoundedTextInput{
        id: i_name_val
        parent: root
        anchors.top: i_label.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Name_anno
        _value: CoreImport.current_user
        _enabled: false
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[a-zA-Z][a-zA-Z0-9-_\.]{1,20}$/
        }
        function update_initial_value(){
            _value = i_name_val.a_txt_input.text
        }
    }

    RoundedTextInput{
        id: i_language_val
        parent: root
        anchors.top: i_name_val.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Language_anno
        _value: core.getUserProfileValue(CoreImport.ProfileMembers.Language)
        _enabled: false
        function update_initial_value(){
            _value = core.getUserProfileValue(CoreImport.ProfileMembers.Language)
        }
    }

    RoundedTextInput{
        id: i_email_val
        parent: root
        anchors.top: i_language_val.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Email_anno
        _value: core.getUserProfileValue(CoreImport.ProfileMembers.Email)
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/
        }
        function update_initial_value(){
            _value = i_email_val.a_txt_input.text
        }
    }
    RoundedTextInput{
        id: i_phone_val
        parent: root
        anchors.top: i_email_val.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_PhoneNumber_anno
        _value: core.getUserProfileValue(CoreImport.ProfileMembers.Phone)
        onclicked_txt: "+"
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^\+?(\d{1,3})?[- .]?\(?(?:\d{2,3})\)?[- .]?\d\d\d[- .]?\d\d\d\d$/
        }
        function update_initial_value(){
            _value = i_phone_val.a_txt_input.text
        }
    }
}
