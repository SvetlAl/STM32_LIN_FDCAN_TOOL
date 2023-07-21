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

    property string st_description: qsTr("View Scale")
    property string st_ViewScale_Height_Container_anno: qsTr("Containers Height")
    /********* translated ********/

    function retranslateUi() {
        st_description = qsTr("View Scale")
        st_ViewScale_Height_Container_anno =  qsTr("Containers Height")
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
        id: i_ViewScale_Height_Container_anno
        anchors.top: i_label.bottom
        anchors.topMargin: st_vertical_margin
        _anno: st_ViewScale_Height_Container_anno
        a_slider._value: CoreImport._ViewScale_Height_Container
        function a_update_initial_value() {
            core.setDesignValue_int("ViewScale", "Height", "Container", a_slider._value)
            CoreImport._ViewScale_Height_Container = core.getDesignValue_int("ViewScale", "Height", "Container")
            calculateHeight()
        }
    }
}



