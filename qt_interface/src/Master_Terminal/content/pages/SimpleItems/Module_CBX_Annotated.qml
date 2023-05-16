import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import CoreImport;

Rectangle {
    /********* size settings ********/

    property int st_initial_font_pixelSize:  1 + root.height * st_ratio_font_sz
    property int st_font_pixelSize:  st_initial_font_pixelSize
    property int st_font_pixelSize_info: i_cbx.st_font_pixelSize_info > i_label.st_font_pixelSize_info ? i_label.st_font_pixelSize_info : i_cbx.st_font_pixelSize_info
    property bool st_font_resize: true
    property real st_ratio_font_sz: CoreImport._SimpleItems_Ratio_ButtonFont

    property int st_item_width:  64
    property int st_item_height:  64

    /********* colors settings ********/
    property string st_clr_text: CoreImport._SimpleItems_Color_ButtonText

    /********* values ********/
    property string st_txt: "st_txt"
    property bool isActive: true

    required property var _model

    /********* alias ********/
    property alias a_cbx_txt: i_cbx.st_label_txt
    property alias a_cbx_start_index: i_cbx._start_index


    id: root
    color: "transparent"


    Label {
        id: i_label
        text: st_txt
        width: st_item_width
        height: st_item_height
        anchors.verticalCenter: root.verticalCenter
        anchors.left: root.left
        verticalAlignment: Text.AlignVCenter
        color: st_clr_text
        minimumPointSize: 5
        font.pixelSize: st_font_pixelSize
        fontSizeMode: Text.Fit

        property int st_initial_font_pixelSize: root.st_initial_font_pixelSize
        property int st_font_pixelSize: root.st_font_pixelSize
        readonly property int st_font_pixelSize_info: fontInfo.pixelSize
        property bool st_font_resize: root.st_font_resize

    }

    RoundedComboBox{
        id: i_cbx
        height: st_item_height
        width: st_item_width*2
        anchors.right: root.right
        anchors.verticalCenter: root.verticalCenter

        st_model: _model

        st_initial_font_pixelSize: root.st_initial_font_pixelSize
        st_font_pixelSize: root.st_font_pixelSize
        st_font_resize: root.st_font_resize

    }

}
