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
    property string st_description: qsTr("Base")
    property string st_Base_Height_Navibar_anno: qsTr("Navibar Height")
    property string st_Base_Color_Icon_anno: qsTr("Icons")
    property string st_Base_Color_IconOverlay_anno: qsTr("Icon overlay")
    property string st_Base_Color_BaseFont_anno: qsTr("BaseFont")

    property string st_Base_Width_ButtonBorder_anno: qsTr("ButtonBorder Width")
    property string st_Base_Gradient_PositionA_anno: qsTr("Gradient PositionA")
    property string st_Base_Gradient_PositionB_anno: qsTr("Gradient PositionB")
    //property string st_Base_Color_GradientBackground_anno: qsTr("Gr.Bckgrnd")
    property string st_Base_Color_Frame_anno: qsTr("Frame")
    property string st_Base_Color_Canva_anno: qsTr("Canva")
    property string st_Base_Color_ButtonCanva_anno: qsTr("BtnCanva")
    property string st_Base_Color_FrameLight_anno: qsTr("FrameLight")

    property string st_Base_Font_TerminalSz_anno: qsTr("Terminal font size")
    property string st_Base_Width_ItemFrame_anno: qsTr("Colored frame width")
    property string st_Base_Height_Item_anno: qsTr("Base Item Height")
    property string st_Base_Ratio_ButtonFont_anno: qsTr("Base ButtonFont")
    property string st_Base_Height_PageGrid_anno: qsTr("Base PageGrid Height")


    /********* translated ********/

    function retranslateUi() {
        st_description = qsTr("Base")
        st_Base_Height_Navibar_anno =  qsTr("Navibar Height")
        st_Base_Color_Icon_anno = qsTr("Icons")
        st_Base_Color_IconOverlay_anno = qsTr("Icon overlay")
        st_Base_Color_BaseFont_anno = qsTr("BaseFont")
        st_Base_Width_ButtonBorder_anno = qsTr("ButtonBorder Width")
        st_Base_Gradient_PositionA_anno = qsTr("Gradient PositionA")
        st_Base_Gradient_PositionB_anno = qsTr("Gradient PositionB")
 //       st_Base_Color_GradientBackground_anno = qsTr("Gr.Bckgrnd")
        st_Base_Color_Frame_anno = qsTr("Frame")
        st_Base_Color_Canva_anno = qsTr("Canva")
        st_Base_Color_ButtonCanva_anno = qsTr("BtnCanva")
        st_Base_Color_FrameLight_anno = qsTr("FrameLight")
        st_Base_Font_TerminalSz_anno = qsTr("Terminal font size")
        st_Base_Width_ItemFrame_anno =  qsTr("Colored frame width")
        st_Base_Height_Item_anno = qsTr("Base Item Height")
        st_Base_Ratio_ButtonFont_anno = qsTr("Base ButtonFont")
        st_Base_Height_PageGrid_anno = qsTr("Base PageGrid Height")
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
            total_height += root.children[i-1].height
            total_height += root.children[i-1].anchors.topMargin
        }
        root.height = total_height
    }
    /********* alias ********/

    id: root
    width: parent.width
    Label {
        id: i_label
        height: st_height_items
        width: parent.width
        text: st_description
        color: st_text_color
        minimumPointSize: 5
        font.pointSize: st_label_font_sz
        fontSizeMode: Text.Fit
    }

    RoundedSliderAnnotated{
        id: i_Base_Height_Navibar
        anchors.top: i_label.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Base_Height_Navibar_anno
        a_slider._value: CoreImport._Base_Height_Navibar
        a_slider._from: 50
        a_slider._to: 300
        a_slider._step: 2
        function a_update_initial_value() {
            core.setDesignValue_int("Base", "Height", "Navibar", a_slider._value)
            CoreImport._Base_Height_Navibar = core.getDesignValue_int("Base", "Height", "Navibar")
            calculateHeight()
        }
    }

    RoundedTextInput{
        id: i_Base_Color_Icon
        parent: root
        anchors.top: i_Base_Height_Navibar.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Base_Color_Icon_anno
        _value: CoreImport._Base_Color_Icon
        a_txt_input.font.capitalization: Font.AllUppercase
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[#]([0-Fa-f]{5}[0-Fa-f])$/
        }
        st_clr_text: _value
        function update_initial_value(){
            _value = i_Base_Color_Icon.a_txt_input.text
            core.setDesignValue_string("Base", "Color", "Icon", _value)
            CoreImport._Base_Color_Icon = core.getDesignValue_string("Base", "Color", "Icon")
        }
    }

    RoundedTextInput{
        id: i_Base_Color_IconOverlay
        parent: root
        anchors.top: i_Base_Color_Icon.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Base_Color_IconOverlay_anno
        _value: CoreImport._Base_Color_IconOverlay
        a_txt_input.font.capitalization: Font.AllUppercase
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[#]([0-Fa-f]{5}[0-Fa-f])$/
        }
        st_clr_text: _value
        function update_initial_value(){
            _value = i_Base_Color_IconOverlay.a_txt_input.text
            core.setDesignValue_string("Base", "Color", "IconOverlay", _value)
            CoreImport._Base_Color_IconOverlay = core.getDesignValue_string("Base", "Color", "IconOverlay")
        }
    }

    RoundedTextInput{
        id: i_Base_Color_BaseFont
        parent: root
        anchors.top: i_Base_Color_IconOverlay.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Base_Color_BaseFont_anno
        _value: CoreImport._Base_Color_BaseFont
        a_txt_input.font.capitalization: Font.AllUppercase
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[#]([0-Fa-f]{5}[0-Fa-f])$/
        }
        st_clr_text: _value
        function update_initial_value(){
            _value = i_Base_Color_BaseFont.a_txt_input.text
            core.setDesignValue_string("Base", "Color", "BaseFont", _value)
            CoreImport._Base_Color_BaseFont = core.getDesignValue_string("Base", "Color", "BaseFont")
        }
    }

    RoundedTextInput{
        id: i_Base_Color_ButtonCanva
        parent: root
        anchors.top: i_Base_Color_BaseFont.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Base_Color_ButtonCanva_anno
        _value: CoreImport._Base_Color_ButtonCanva
        a_txt_input.font.capitalization: Font.AllUppercase
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[#]([0-Fa-f]{5}[0-Fa-f])$/
        }
        st_clr_text: _value
        function update_initial_value(){
            _value = i_Base_Color_ButtonCanva.a_txt_input.text
            core.setDesignValue_string("Base", "Color", "ButtonCanva", _value)
            CoreImport._Base_Color_GradientBackground = core.getDesignValue_string("Base", "Color", "ButtonCanva")
        }
    }

    RoundedTextInput{
        id: i_Base_Color_Frame
        parent: root
        anchors.top: i_Base_Color_ButtonCanva.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Base_Color_Frame_anno
        _value: CoreImport._Base_Color_Frame
        a_txt_input.font.capitalization: Font.AllUppercase
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[#]([0-Fa-f]{5}[0-Fa-f])$/
        }
        st_clr_text: _value
        function update_initial_value(){
            _value = i_Base_Color_Frame.a_txt_input.text
            core.setDesignValue_string("Base", "Color", "Frame", _value)
            CoreImport._Base_Color_Frame = core.getDesignValue_string("Base", "Color", "Frame")
        }
    }

    RoundedTextInput{
        id: i_Base_Color_FrameLight
        parent: root
        anchors.top: i_Base_Color_Frame.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Base_Color_FrameLight_anno
        _value: CoreImport._Base_Color_FrameLight
        a_txt_input.font.capitalization: Font.AllUppercase
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[#]([0-Fa-f]{5}[0-Fa-f])$/
        }
        st_clr_text: _value
        function update_initial_value(){
            _value = i_Base_Color_FrameLight.a_txt_input.text
            core.setDesignValue_string("Base", "Color", "FrameLight", _value)
            CoreImport._Base_Color_Frame = core.getDesignValue_string("Base", "Color", "FrameLight")
        }
    }

    RoundedTextInput{
        id: i_Base_Color_Canva
        parent: root
        anchors.top: i_Base_Color_FrameLight.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Base_Color_Canva_anno
        _value: CoreImport._Base_Color_Canva
        a_txt_input.font.capitalization: Font.AllUppercase
        a_txt_input.validator: RegularExpressionValidator{
            regularExpression:/^[#]([0-Fa-f]{5}[0-Fa-f])$/
        }
        st_clr_text: _value
        function update_initial_value(){
            _value = i_Base_Color_Canva.a_txt_input.text
            core.setDesignValue_string("Base", "Color", "Canva", _value)
            CoreImport._Base_Color_Canva = core.getDesignValue_string("Base", "Color", "Canva")
        }
    }

    RoundedSliderAnnotated{
        id: i_Base_Width_ButtonBorder
        anchors.top: i_Base_Color_Canva.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Base_Width_ButtonBorder_anno
        a_slider._value: CoreImport._Base_Width_ButtonBorder
        a_slider._from: 0
        a_slider._to: 10
        a_slider._step: 1
        function a_update_initial_value() {
            core.setDesignValue_int("Base", "Width", "ButtonBorder", a_slider._value)
            CoreImport._Base_Width_ButtonBorder = core.getDesignValue_int("Base", "Width", "ButtonBorder")
            calculateHeight()
        }
    }

    RoundedSliderAnnotated{
        id: i_Base_Gradient_PositionA
        parent: root
        anchors.top: i_Base_Width_ButtonBorder.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Base_Gradient_PositionA_anno
        a_slider._value: CoreImport._Base_Gradient_PositionA * 100
        a_slider.st_labelTxt: (a_slider._value/100).toString().length === 3 ? (a_slider._value/100).toString() +"0" : (a_slider._value/100).toString().length === 1 ? (a_slider._value/100).toString() + ".00" :  a_slider._value/100 < 0.10 ? ".0" + a_slider._value + "  " : (a_slider._value/100).toString()
        a_slider._from: 0
        a_slider._to: 200
        a_slider._step: 1
        function a_update_initial_value() {
            core.setDesignValue_float("Base", "Gradient", "PositionA", (a_slider._value/100))
            CoreImport._Base_Gradient_PositionA = core.getDesignValue_float("Base", "Gradient", "PositionA")
            calculateHeight()
        }
    }

    RoundedSliderAnnotated{
        id: i_Base_Gradient_PositionB
        parent: root
        anchors.top: i_Base_Gradient_PositionA.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Base_Gradient_PositionB_anno
        a_slider._value: CoreImport._Base_Gradient_PositionB * 100
        a_slider.st_labelTxt: (a_slider._value/100).toString().length === 3 ? (a_slider._value/100).toString() +"0" : (a_slider._value/100).toString().length === 1 ? (a_slider._value/100).toString() + ".00" :  a_slider._value/100 < 0.10 ? ".0" + a_slider._value + "  " : (a_slider._value/100).toString()
        a_slider._from: 0
        a_slider._to: 200
        a_slider._step: 1
        function a_update_initial_value() {
            core.setDesignValue_float("Base", "Gradient", "PositionB", (a_slider._value/100))
            CoreImport._Base_Gradient_PositionB = core.getDesignValue_float("Base", "Gradient", "PositionB")
            calculateHeight()
        }
    }

    RoundedSliderAnnotated{
        id: i_Base_Font_TerminalSz
        anchors.top: i_Base_Gradient_PositionB.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Base_Font_TerminalSz_anno
        a_slider._value: CoreImport._Base_Font_TerminalSz
        a_slider._from: 5
        a_slider._to: 50
        a_slider._step: 1
        function a_update_initial_value() {
            core.setDesignValue_int("Base", "Font", "TerminalSz", a_slider._value)
            CoreImport._Base_Font_TerminalSz = core.getDesignValue_int("Base", "Font", "TerminalSz")
            calculateHeight()
        }
    }

    RoundedSliderAnnotated{
        id: i_Base_Width_ItemFrame
        anchors.top: i_Base_Font_TerminalSz.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Base_Width_ItemFrame_anno
        a_slider._value: CoreImport._Base_Width_ItemFrame
        a_slider._from: 100
        a_slider._to: 800
        a_slider._step: 10
        function a_update_initial_value() {
            core.setDesignValue_int("Base", "Width", "ItemFrame", a_slider._value)
            CoreImport._Base_Width_ItemFrame = core.getDesignValue_int("Base", "Width", "ItemFrame")
            calculateHeight()
        }
    }

    RoundedSliderAnnotated{
        id: i_Base_Height_Item
        anchors.top: i_Base_Width_ItemFrame.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Base_Height_Item_anno
        a_slider._value: CoreImport._Base_Height_Item
        a_slider._from: 10
        a_slider._to: 400
        a_slider._step: 1
        function a_update_initial_value() {
            core.setDesignValue_int("Base", "Height", "Item", a_slider._value)
            CoreImport._Base_Height_Item = core.getDesignValue_int("Base", "Height", "Item")
            calculateHeight()
        }
    }
    RoundedSliderAnnotated{
        id: i_Base_Ratio_ButtonFont
        anchors.top: i_Base_Height_Item.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Base_Ratio_ButtonFont_anno
        a_slider._value: CoreImport._Base_Ratio_ButtonFont * 100
        a_slider.st_labelTxt: (a_slider._value/100).toString().length === 3 ? (a_slider._value/100).toString() +"0" : (a_slider._value/100).toString().length === 1 ? (a_slider._value/100).toString() + ".00" : (a_slider._value/100).toString()
        a_slider._from: 1
        a_slider._to: 200
        a_slider._step: 1
        function a_update_initial_value() {
            core.setDesignValue_float("Base", "Ratio", "ButtonFont", (a_slider._value/100))
            CoreImport._Base_Ratio_ButtonFont = core.getDesignValue_float("Base", "Ratio", "ButtonFont")
            calculateHeight()
        }
    }

    RoundedSliderAnnotated{
        id: i_Base_Height_PageGrid
        anchors.top: i_Base_Ratio_ButtonFont.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_Base_Height_PageGrid_anno
        a_slider._value: CoreImport._Base_Height_PageGrid
        a_slider._from: 10
        a_slider._to: 400
        a_slider._step: 1
        function a_update_initial_value() {
            core.setDesignValue_int("Base", "Height", "PageGrid", a_slider._value)
            CoreImport._Base_Height_PageGrid = core.getDesignValue_int("Base", "Height", "PageGrid")
            calculateHeight()
        }
    }

    //_Base_Ratio_ButtonFont = core.getDesignValue_float("Base", "Ratio", "ButtonFont")
}
