import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "SimpleItems";

Item {
    /********* size settings ********/
    property int st_label_font_sz: CoreImport._SimpleItems_Font_Main
    property int st_height_items: CoreImport._ViewScale_Height_Container
    property int st_vertical_margin: CoreImport._ViewScale_Height_Container - (CoreImport._ViewScale_Height_Container * CoreImport._GeneralDesign_Ratio_ScreenAdjVertContainerCrop)
    /********* colors settings ********/
    property string st_text_color: CoreImport._SimpleItems_Color_ButtonText
    /********* values ********/
    // property int st_ViewScale_Height_Container: core._ViewScale_Height_Container

    property string st_description: qsTr("Simple Items")
    property string st_SimpleItems_Font_Main_anno: qsTr("Font: Main")
    property string st_SimpleItems_Width_ButtonBorder_anno: qsTr("Width: Button Border")
    property string st_SimpleItems_HeightToWidth_Button_anno: qsTr("Height/Width: Button")
    property string st_SimpleItems_Ratio_ButtonFont_anno: qsTr("Ratio: ButtonFont")
    property string st_SimpleItems_Ratio_ButtonOnPress_anno: qsTr("Ratio: ButtonOnPress")
    property string st_SimpleItems_Color_FrameActive_anno: qsTr("Color: active frame")
    property string st_SimpleItems_Color_FrameInactive_anno: qsTr("Color: inactive frame")
    property string st_SimpleItems_Color_FrameDisabled_anno: qsTr("Color: disabled frame")
    property string st_SimpleItems_Color_Button_anno: qsTr("Color: Button")
    property string st_SimpleItems_Color_ButtonText_anno: qsTr("Color: Button text")

    /********* translated ********/

    function retranslateUi() {
        st_description = qsTr("Simple Items")
        st_SimpleItems_Font_Main_anno = qsTr("Font: Main")
        st_SimpleItems_Width_ButtonBorder_anno = qsTr("Width: Button Border")
        st_SimpleItems_HeightToWidth_Button_anno = qsTr("Height/Width: Button")
        st_SimpleItems_Ratio_ButtonFont_anno = qsTr("Ratio: ButtonFont")
        st_SimpleItems_Ratio_ButtonOnPress_anno = qsTr("Ratio: ButtonOnPress")
        st_SimpleItems_Color_FrameActive_anno = qsTr("Color: active frame")
        st_SimpleItems_Color_FrameInactive_anno = qsTr("Color: inactive frame")
        st_SimpleItems_Color_FrameDisabled_anno = qsTr("Color: disabled frame")
        st_SimpleItems_Color_Button_anno = qsTr("Color: Button")
        st_SimpleItems_Color_ButtonText_anno = qsTr("Color: Button text")
    }

    Connections {
        target: qmlTranslator
        function onLanguageChanged(){
            retranslateUi()
        }
    }

    Component.onCompleted:{
        retranslateUi();
        calculateHeight();
    }

    function calculateHeight(){
        var total_height = 0
        for(var i = root.children.length; i > 0 ; i--) {
            if(root.children[i-1].type !== "focus_reset"){
                total_height += root.children[i-1].height
                total_height += root.children[i-1].anchors.topMargin
            }
        }
        root.height = total_height
    }

    /********* alias ********/

    id: root
    width: parent.width

    MouseArea{
        property string type: "focus_reset"
        anchors.fill: root
        onClicked: {
            root.forceActiveFocus()
        }
    }

    Label {
        id: i_label
        parent: root
        height: st_height_items
        width: parent.width
        text: st_description
        color: st_text_color
        minimumPointSize: 5
        font.pointSize: st_label_font_sz
        fontSizeMode: Text.Fit
    }

    RoundedSliderAnnotated{
        id: i_SimpleItems_Font_Main
        parent: root
        anchors.top: i_label.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_SimpleItems_Font_Main_anno
        a_slider._value: CoreImport._SimpleItems_Font_Main
        function a_update_initial_value() {
            core.setDesignValue_int("SimpleItems", "Font", "Main", a_slider._value)
            CoreImport._SimpleItems_Font_Main = core.getDesignValue_int("SimpleItems", "Font", "Main")
            calculateHeight()
        }
    }
    RoundedSliderAnnotated{
        id: i_SimpleItems_Width_ButtonBorder
        parent: root
        anchors.top: i_SimpleItems_Font_Main.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_SimpleItems_Width_ButtonBorder_anno
        a_slider._value: CoreImport._SimpleItems_Width_ButtonBorder
        function a_update_initial_value() {
            core.setDesignValue_int("SimpleItems", "Width", "ButtonBorder", a_slider._value)
            CoreImport._SimpleItems_Width_ButtonBorder = core.getDesignValue_int("SimpleItems", "Width", "ButtonBorder")
            calculateHeight()
        }
    }
    RoundedSliderAnnotated{
        id: i_SimpleItems_HeightToWidth_Button
        parent: root
        anchors.top: i_SimpleItems_Width_ButtonBorder.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_SimpleItems_HeightToWidth_Button_anno
        a_slider._value: CoreImport._SimpleItems_HeightToWidth_Button * 100
        a_slider.st_labelTxt: (a_slider._value/100).toString().length === 3 ? (a_slider._value/100).toString() +"0" : (a_slider._value/100).toString().length === 1 ? (a_slider._value/100).toString() + ".00" : (a_slider._value/100).toString()
        a_slider._from: 1
        a_slider._to: 200
        a_slider._step: 1
        function a_update_initial_value() {
            core.setDesignValue_float("SimpleItems", "HeightToWidth", "Button", (a_slider._value/100))
            CoreImport._SimpleItems_HeightToWidth_Button = core.getDesignValue_float("SimpleItems", "HeightToWidth", "Button")
            calculateHeight()
        }
    }
    RoundedSliderAnnotated{
        id: i_SimpleItems_Ratio_ButtonFont
        parent: root
        anchors.top: i_SimpleItems_HeightToWidth_Button.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_SimpleItems_Ratio_ButtonFont_anno
        a_slider._value: CoreImport._SimpleItems_Ratio_ButtonFont * 100
        a_slider.st_labelTxt: (a_slider._value/100).toString().length === 3 ? (a_slider._value/100).toString() +"0" : (a_slider._value/100).toString().length === 1 ? (a_slider._value/100).toString() + ".00" : (a_slider._value/100).toString()
        a_slider._from: 1
        a_slider._to: 200
        a_slider._step: 1
        function a_update_initial_value() {
            core.setDesignValue_float("SimpleItems", "Ratio", "ButtonFont", (a_slider._value/100))
            CoreImport._SimpleItems_Ratio_ButtonFont = core.getDesignValue_float("SimpleItems", "Ratio", "ButtonFont")
            calculateHeight()
        }
    }
    RoundedSliderAnnotated{
        id: i_SimpleItems_Ratio_ButtonOnPress
        parent: root
        anchors.top: i_SimpleItems_Ratio_ButtonFont.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_SimpleItems_Ratio_ButtonOnPress_anno
        a_slider._value: CoreImport._SimpleItems_Ratio_ButtonOnPress * 100
        a_slider.st_labelTxt: (a_slider._value/100).toString().length === 3 ? (a_slider._value/100).toString() +"0" : (a_slider._value/100).toString().length === 1 ? (a_slider._value/100).toString() + ".00" : (a_slider._value/100).toString()
        a_slider._from: 100
        a_slider._to: 2000
        a_slider._step: 10
        function a_update_initial_value() {
            core.setDesignValue_float("SimpleItems", "Ratio", "ButtonOnPress", (a_slider._value/100))
            CoreImport._SimpleItems_Ratio_ButtonOnPress = core.getDesignValue_float("SimpleItems", "Ratio", "ButtonOnPress")
            calculateHeight()
        }
    }
    RoundedTextInput{
        id: i_SimpleItems_Color_FrameActive
        parent: root
        anchors.top: i_SimpleItems_Ratio_ButtonOnPress.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_SimpleItems_Color_FrameActive_anno
        _value: CoreImport._SimpleItems_Color_FrameActive
        a_txt_input.font.capitalization: Font.AllUppercase
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[#]([0-Fa-f]{5}[0-Fa-f])$/
        }
        st_clr_text: _value
        function update_initial_value(){
            _value = i_SimpleItems_Color_FrameActive.a_txt_input.text
            core.setDesignValue_string("SimpleItems", "Color", "FrameActive", _value)
            CoreImport._SimpleItems_Color_FrameActive = core.getDesignValue_string("SimpleItems", "Color", "FrameActive")
        }
    }
    RoundedTextInput{
        id: i_SimpleItems_Color_FrameInactive
        parent: root
        anchors.top: i_SimpleItems_Color_FrameActive.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_SimpleItems_Color_FrameInactive_anno
        _value: CoreImport._SimpleItems_Color_FrameInactive
        a_txt_input.font.capitalization: Font.AllUppercase
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[#]([0-Fa-f]{5}[0-Fa-f])$/
        }
        st_clr_text: _value
        function update_initial_value(){
            _value = i_SimpleItems_Color_FrameInactive.a_txt_input.text
            core.setDesignValue_string("SimpleItems", "Color", "FrameInactive", _value)
            CoreImport._SimpleItems_Color_FrameInactive = core.getDesignValue_string("SimpleItems", "Color", "FrameInactive")
        }
    }
    RoundedTextInput{
        id: i_SimpleItems_Color_FrameDisabled
        parent: root
        anchors.top: i_SimpleItems_Color_FrameInactive.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_SimpleItems_Color_FrameDisabled_anno
        _value: CoreImport._SimpleItems_Color_FrameDisabled
        a_txt_input.font.capitalization: Font.AllUppercase
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[#]([0-Fa-f]{5}[0-Fa-f])$/
        }
        st_clr_text: _value
        function update_initial_value(){
            _value = i_SimpleItems_Color_FrameDisabled.a_txt_input.text
            core.setDesignValue_string("SimpleItems", "Color", "FrameDisabled", _value)
            CoreImport._SimpleItems_Color_FrameDisabled = core.getDesignValue_string("SimpleItems", "Color", "FrameDisabled")
        }
    }
    RoundedTextInput{
        id: i_SimpleItems_Color_Button
        parent: root
        anchors.top: i_SimpleItems_Color_FrameDisabled.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_SimpleItems_Color_Button_anno
        _value: CoreImport._SimpleItems_Color_Button
        a_txt_input.font.capitalization: Font.AllUppercase
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[#]([0-Fa-f]{5}[0-Fa-f])$/
        }
        st_clr_text: _value
        function update_initial_value(){
            _value = i_SimpleItems_Color_Button.a_txt_input.text
            core.setDesignValue_string("SimpleItems", "Color", "Button", _value)
            CoreImport._SimpleItems_Color_Button = core.getDesignValue_string("SimpleItems", "Color", "Button")
        }
    }
    RoundedTextInput{
        id: i_SimpleItems_Color_ButtonText
        parent: root
        anchors.top: i_SimpleItems_Color_Button.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_SimpleItems_Color_ButtonText_anno
        _value: CoreImport._SimpleItems_Color_ButtonText
        a_txt_input.font.capitalization: Font.AllUppercase
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[#]([0-Fa-f]{5}[0-Fa-f])$/
        }
        st_clr_text: _value
        function update_initial_value(){
            _value = i_SimpleItems_Color_ButtonText.a_txt_input.text
            core.setDesignValue_string("SimpleItems", "Color", "ButtonText", _value)
            CoreImport._SimpleItems_Color_ButtonText = core.getDesignValue_string("SimpleItems", "Color", "ButtonText")
        }
    }
}
