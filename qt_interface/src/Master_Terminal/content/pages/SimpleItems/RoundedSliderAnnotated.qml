import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import CoreImport;

Item {
    /********* size settings ********/
    property int st_height_total: CoreImport._ViewScale_Height_Container
    property real st_ratio_anno_to_slider: 0.50
    property int st_height_slider: root.height - root.height*st_ratio_anno_to_slider
    property int st_height_anno: root.height*st_ratio_anno_to_slider

    property int st_initial_font_pixelSize:  1 + root.height * st_ratio_font_sz
    property int st_font_pixelSize: st_initial_font_pixelSize
    property int st_font_pixelSize_info: i_anno.st_font_pixelSize_info
    property bool st_font_resize: true
    property real st_ratio_font_sz: CoreImport._SimpleItems_Ratio_ButtonFont

    /********* colors settings ********/

    /********* values ********/
    property string _anno: "annotation"
    property bool value_display_offset: true
    /********* alias ********/
    property alias a_slider: i_slider

    function a_update_initial_value(){}

    id: root
    height: st_height_total
    width: parent.width

    RoundedSlider {
        id: i_slider
        height: st_height_slider
        width: root.width
        anchors.bottom: root.bottom
        value_display_offset: root.value_display_offset
        function update_initial_value(){
            a_update_initial_value()
        }
    }

    Label {
        id: i_anno
        text: _anno
        width: root.width
        height: st_height_anno
        anchors.left: root.left
        anchors.top: root.top
        color: a_slider.st_clr_text
        minimumPointSize: 5
        fontSizeMode: Text.Fit
        font.pixelSize: st_font_pixelSize

        property int st_initial_font_pixelSize: root.st_initial_font_pixelSize
        property int st_font_pixelSize: root.st_font_pixelSize
        readonly property int st_font_pixelSize_info: fontInfo.pixelSize
        property bool st_font_resize: root.st_font_resize

    }
}

