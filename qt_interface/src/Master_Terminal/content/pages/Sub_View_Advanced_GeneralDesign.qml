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

    /********* translated ********/

    property string st_description: qsTr("General Design")
    property string st_GeneralDesign_Font_ToolBar_anno: qsTr("Font: Toolbar")
    property string st_GeneralDesign_Font_DrawerTitleFrame_anno: qsTr("Font: Drawer Title Frame")
    property string st_GeneralDesign_Font_DrawerItemText_anno: qsTr("Font: Drawer Items")
    property string st_GeneralDesign_Height_DrawerTitleFrame_anno: qsTr("Height: Drawer Title Frame")
    property string st_GeneralDesign_Height_DrawerItemIcons_anno: qsTr("Height: Drawer Item Icons")
    property string st_GeneralDesign_Height_ToolBar_anno: qsTr("Height: Toolbar")
    property string st_GeneralDesign_Color_ToolBar_anno: qsTr("Toolbar")
    property string st_GeneralDesign_Color_ToolBarText_anno: qsTr("ToolbarTxt")
    property string st_GeneralDesign_Color_DrawerFrame_anno: qsTr("DrawerFrame")
    property string st_GeneralDesign_Color_DrawerItemText_anno: qsTr("DrwItmTxt")
    property string st_GeneralDesign_Color_DrawerFrameText_anno: qsTr("DrwFrmTxt")
    property string st_GeneralDesign_Ratio_TitleToToolbar_anno: qsTr("Ratio: Title to Toolbar")
    property string st_GeneralDesign_Ratio_ScreenAdjSideCrop_anno: qsTr("Ratio: ScreenAdjust side crop")
    property string st_GeneralDesign_Ratio_ScreenAdjVertContainerCrop_anno: qsTr("Ratio: ScreenAdjust vertical crop")
    property string st_GeneralDesign_Gradient_Backstage: qsTr("Gradient: Backstage")


    function retranslateUi() {
        st_description = qsTr("General Design")
        st_GeneralDesign_Font_ToolBar_anno =  qsTr("Font: Toolbar")
        st_GeneralDesign_Font_DrawerTitleFrame_anno = qsTr("Font: Drawer Title Frame")
        st_GeneralDesign_Font_DrawerItemText_anno = qsTr("Font: Drawer Items")
        st_GeneralDesign_Height_DrawerTitleFrame_anno = qsTr("Height: Drawer Title Frame")
        st_GeneralDesign_Height_DrawerItemIcons_anno = qsTr("Height: Drawer Item Icons")
        st_GeneralDesign_Height_ToolBar_anno = qsTr("Height: Toolbar")
        st_GeneralDesign_Color_ToolBar_anno = qsTr("Toolbar")
        st_GeneralDesign_Color_ToolBarText_anno = qsTr("ToolbarTxt")
        st_GeneralDesign_Color_DrawerFrame_anno = qsTr("DrawerFrame")
        st_GeneralDesign_Color_DrawerItemText_anno = qsTr("DrwItmTxt")
        st_GeneralDesign_Color_DrawerFrameText_anno = qsTr("DrwFrmTxt")
        st_GeneralDesign_Ratio_TitleToToolbar_anno = qsTr("Ratio: Title to Toolbar")
        st_GeneralDesign_Ratio_ScreenAdjSideCrop_anno = qsTr("Ratio: ScreenAdjust side crop")
        st_GeneralDesign_Ratio_ScreenAdjVertContainerCrop_anno = qsTr("Ratio: ScreenAdjust vertical crop")
        st_GeneralDesign_Gradient_Backstage = qsTr("Gradient: Backstage")
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

    MouseArea{
        property string type: "focus_reset"
        anchors.fill: root
        onClicked: {
            root.forceActiveFocus()
        }
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
        id: i_GeneralDesign_Font_ToolBar
        parent: root
        anchors.top: i_label.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_GeneralDesign_Font_ToolBar_anno
        a_slider._value: CoreImport._GeneralDesign_Font_ToolBar
        function a_update_initial_value() {
            core.setDesignValue_int("GeneralDesign", "Font", "ToolBar", a_slider._value)
            CoreImport._GeneralDesign_Font_ToolBar = core.getDesignValue_int("GeneralDesign", "Font", "ToolBar")
            calculateHeight()
        }
    }

    RoundedSliderAnnotated{
        id: i_GeneralDesign_Font_DrawerTitleFrame
        parent: root
        anchors.top: i_GeneralDesign_Font_ToolBar.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_GeneralDesign_Font_DrawerTitleFrame_anno
        a_slider._value: CoreImport._GeneralDesign_Font_DrawerTitleFrame
        function a_update_initial_value() {
            core.setDesignValue_int("GeneralDesign", "Font", "DrawerTitleFrame", a_slider._value)
            CoreImport._GeneralDesign_Font_DrawerTitleFrame = core.getDesignValue_int("GeneralDesign", "Font", "DrawerTitleFrame")
            calculateHeight()
        }
    }

    RoundedSliderAnnotated{
        id: i_GeneralDesign_Font_DrawerItemText
        parent: root
        anchors.top: i_GeneralDesign_Font_DrawerTitleFrame.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_GeneralDesign_Font_DrawerItemText_anno
        a_slider._value: CoreImport._GeneralDesign_Font_DrawerItemText
        function a_update_initial_value() {
            core.setDesignValue_int("GeneralDesign", "Font", "DrawerItemText", a_slider._value)
            CoreImport._GeneralDesign_Font_DrawerItemText = core.getDesignValue_int("GeneralDesign", "Font", "DrawerItemText")
            calculateHeight()
        }
    }
    RoundedSliderAnnotated{
        id: i_GeneralDesign_Height_DrawerTitleFrame
        parent: root
        anchors.top: i_GeneralDesign_Font_DrawerItemText.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_GeneralDesign_Height_DrawerTitleFrame_anno
        a_slider._value: CoreImport._GeneralDesign_Height_DrawerTitleFrame
        a_slider._from: 100
        a_slider._to: 300
        a_slider._step: 1
        function a_update_initial_value() {
            core.setDesignValue_int("GeneralDesign", "Height", "DrawerTitleFrame", a_slider._value)
            CoreImport._GeneralDesign_Height_DrawerTitleFrame = core.getDesignValue_int("GeneralDesign", "Height", "DrawerTitleFrame")
            calculateHeight()
        }
    }

    RoundedSliderAnnotated{
        id: i_GeneralDesign_Height_DrawerItemIcons
        parent: root
        anchors.top: i_GeneralDesign_Height_DrawerTitleFrame.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_GeneralDesign_Height_DrawerItemIcons_anno
        a_slider._value: CoreImport._GeneralDesign_Height_DrawerItemIcons
        function a_update_initial_value() {
            core.setDesignValue_int("GeneralDesign", "Height", "DrawerItemIcons", a_slider._value)
            CoreImport._GeneralDesign_Height_DrawerItemIcons = core.getDesignValue_int("GeneralDesign", "Height", "DrawerItemIcons")
            calculateHeight()
        }
    }
    RoundedSliderAnnotated{
        id: i_GeneralDesign_Height_ToolBar
        parent: root
        anchors.top: i_GeneralDesign_Height_DrawerItemIcons.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_GeneralDesign_Height_ToolBar_anno
        a_slider._value: CoreImport._GeneralDesign_Height_ToolBar
        function a_update_initial_value() {
            core.setDesignValue_int("GeneralDesign", "Height", "ToolBar", a_slider._value)
            CoreImport._GeneralDesign_Height_ToolBar = core.getDesignValue_int("GeneralDesign", "Height", "ToolBar")
            calculateHeight()
        }
    }
    RoundedSliderAnnotated{
        id: i_GeneralDesign_Ratio_TitleToToolbar
        parent: root
        anchors.top: i_GeneralDesign_Height_ToolBar.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_GeneralDesign_Ratio_TitleToToolbar_anno
        a_slider._value: CoreImport._GeneralDesign_Ratio_TitleToToolbar * 100
        a_slider.st_labelTxt: (a_slider._value/100).toString().length === 3 ? (a_slider._value/100).toString() +"0" : (a_slider._value/100).toString().length === 1 ? (a_slider._value/100).toString() + ".00" : (a_slider._value/100).toString()
        a_slider._from: 1
        a_slider._to: 200
        a_slider._step: 1
        function a_update_initial_value() {
            core.setDesignValue_float("GeneralDesign", "Ratio", "TitleToToolbar", (a_slider._value/100))
            CoreImport._GeneralDesign_Ratio_TitleToToolbar = core.getDesignValue_float("GeneralDesign", "Ratio", "TitleToToolbar")
            calculateHeight()
        }
    }
    RoundedSliderAnnotated{
        id: i_GeneralDesign_Ratio_ScreenAdjSideCrop
        parent: root
        anchors.top: i_GeneralDesign_Ratio_TitleToToolbar.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_GeneralDesign_Ratio_ScreenAdjSideCrop_anno
        a_slider._value: CoreImport._GeneralDesign_Ratio_ScreenAdjSideCrop * 100
        a_slider.st_labelTxt: (a_slider._value/100).toString().length === 3 ? (a_slider._value/100).toString() +"0" : (a_slider._value/100).toString().length === 1 ? (a_slider._value/100).toString() + ".00" : (a_slider._value/100).toString()
        a_slider._from: 50
        a_slider._to: 100
        a_slider._step: 1
        function a_update_initial_value() {
            core.setDesignValue_float("GeneralDesign", "Ratio", "ScreenAdjSideCrop", (a_slider._value/100))
            CoreImport._GeneralDesign_Ratio_ScreenAdjSideCrop = core.getDesignValue_float("GeneralDesign", "Ratio", "ScreenAdjSideCrop")
            calculateHeight()
        }
    }
    RoundedSliderAnnotated{
        id: i_GeneralDesign_Ratio_ScreenAdjVertContainerCrop
        parent: root
        anchors.top: i_GeneralDesign_Ratio_ScreenAdjSideCrop.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_GeneralDesign_Ratio_ScreenAdjVertContainerCrop_anno
        a_slider._value: CoreImport._GeneralDesign_Ratio_ScreenAdjVertContainerCrop * 100
        a_slider.st_labelTxt: (a_slider._value/100).toString().length === 3 ? (a_slider._value/100).toString() +"0" : (a_slider._value/100).toString().length === 1 ? (a_slider._value/100).toString() + ".00" : (a_slider._value/100).toString()
        a_slider._from: 1
        a_slider._to: 200
        a_slider._step: 1
        function a_update_initial_value() {
            core.setDesignValue_float("GeneralDesign", "Ratio", "ScreenAdjVCrop", (a_slider._value/100))
            CoreImport._GeneralDesign_Ratio_ScreenAdjVertContainerCrop = core.getDesignValue_float("GeneralDesign", "Ratio", "ScreenAdjVCrop")
            calculateHeight()
        }
    }
    RoundedTextInput{
        id: i_GeneralDesign_Color_ToolBar
        parent: root
        anchors.top: i_GeneralDesign_Ratio_ScreenAdjVertContainerCrop.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_GeneralDesign_Color_ToolBar_anno
        _value: CoreImport._GeneralDesign_Color_ToolBar
        a_txt_input.font.capitalization: Font.AllUppercase
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[#]([0-Fa-f]{5}[0-Fa-f])$/
        }
        st_clr_text: _value
        function update_initial_value(){
            _value = i_GeneralDesign_Color_ToolBar.a_txt_input.text
            core.setDesignValue_string("GeneralDesign", "Color", "ToolBar", _value)
            CoreImport._GeneralDesign_Color_ToolBar = core.getDesignValue_string("GeneralDesign", "Color", "ToolBar")
        }
    }
    RoundedTextInput{
        id: i_GeneralDesign_Color_ToolBarText
        parent: root
        anchors.top: i_GeneralDesign_Color_ToolBar.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_GeneralDesign_Color_ToolBarText_anno
        _value: CoreImport._GeneralDesign_Color_ToolBarText
        a_txt_input.font.capitalization: Font.AllUppercase
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[#]([0-Fa-f]{5}[0-Fa-f])$/
        }
        st_clr_text: _value
        function update_initial_value(){
            _value = i_GeneralDesign_Color_ToolBarText.a_txt_input.text
            core.setDesignValue_string("GeneralDesign", "Color", "ToolBarText", _value)
            CoreImport._GeneralDesign_Color_ToolBarText = core.getDesignValue_string("GeneralDesign", "Color", "ToolBarText")
        }
    }
    RoundedTextInput{
        id: i_GeneralDesign_Color_DrawerFrame
        parent: root
        anchors.top: i_GeneralDesign_Color_ToolBarText.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_GeneralDesign_Color_DrawerFrame_anno
        _value: CoreImport._GeneralDesign_Color_DrawerFrame
        a_txt_input.font.capitalization: Font.AllUppercase
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[#]([0-Fa-f]{5}[0-Fa-f])$/
        }
        st_clr_text: _value
        function update_initial_value(){
            _value = i_GeneralDesign_Color_DrawerFrame.a_txt_input.text
            core.setDesignValue_string("GeneralDesign", "Color", "DrawerFrame", _value)
            CoreImport._GeneralDesign_Color_DrawerFrame = core.getDesignValue_string("GeneralDesign", "Color", "DrawerFrame")
        }
    }
    RoundedTextInput{
        id: i_GeneralDesign_Color_DrawerItemText
        parent: root
        anchors.top: i_GeneralDesign_Color_DrawerFrame.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_GeneralDesign_Color_DrawerItemText_anno
        _value: CoreImport._GeneralDesign_Color_DrawerItemText
        a_txt_input.font.capitalization: Font.AllUppercase
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[#]([0-Fa-f]{5}[0-Fa-f])$/
        }
        st_clr_text: _value
        function update_initial_value(){
            _value = i_GeneralDesign_Color_DrawerItemText.a_txt_input.text
            core.setDesignValue_string("GeneralDesign", "Color", "DrawerItemText", _value)
            CoreImport._GeneralDesign_Color_DrawerItemText = core.getDesignValue_string("GeneralDesign", "Color", "DrawerItemText")
        }
    }
    RoundedTextInput{
        id: i_GeneralDesign_Color_DrawerFrameText
        parent: root
        anchors.top: i_GeneralDesign_Color_DrawerItemText.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_GeneralDesign_Color_DrawerFrameText_anno
        _value: CoreImport._GeneralDesign_Color_DrawerFrameText
        a_txt_input.font.capitalization: Font.AllUppercase
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[#]([0-Fa-f]{5}[0-Fa-f])$/
        }
        st_clr_text: _value
        function update_initial_value(){
            _value = i_GeneralDesign_Color_DrawerFrameText.a_txt_input.text
            core.setDesignValue_string("GeneralDesign", "Color", "DrawerFrameText", _value)
            CoreImport._GeneralDesign_Color_DrawerFrameText = core.getDesignValue_string("GeneralDesign", "Color", "DrawerFrameText")
        }
    }

    RoundedSliderAnnotated{
        id: i_GeneralDesign_Gradient_Backstage
        parent: root
        anchors.top: i_GeneralDesign_Color_DrawerFrameText.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_GeneralDesign_Gradient_Backstage
        a_slider._value: CoreImport._GeneralDesign_Gradient_Backstage * 100
        a_slider.st_labelTxt: (a_slider._value/100).toString().length === 3 ? (a_slider._value/100).toString() +"0" : (a_slider._value/100).toString().length === 1 ? (a_slider._value/100).toString() + ".00" : (a_slider._value/100).toString()
        a_slider._from: 1
        a_slider._to: 200
        a_slider._step: 1
        function a_update_initial_value() {
            core.setDesignValue_float("GeneralDesign", "Gradient", "Backstage", (a_slider._value/100))
            CoreImport._GeneralDesign_Gradient_Backstage = core.getDesignValue_float("GeneralDesign", "Gradient", "Backstage")
            calculateHeight()
        }
    }

}
