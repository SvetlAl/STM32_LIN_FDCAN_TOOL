import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import "pages/BaseItems" as BaseItems;

Rectangle {

    /********* size settings ********/
    property int st_height: CoreImport._Base_Height_CollapsedNavibar
    property int st_item_height: CoreImport._ViewScale_Height_Container
    property real st_label_height_ratio: 0.8

    /********* colors settings ********/
    property string st_theme_color: CoreImport._GeneralDesign_Color_ToolBar
    property string st_overlay_color: CoreImport._Base_Color_IconOverlay
    property string st_overlay_color_pressed: Qt.tint(st_overlay_color, "#33333300") // "#87D6FF"
    property string st_font_color: CoreImport._Base_Color_BaseFont
    property int st_border_width: CoreImport._Base_Width_ButtonBorder*2

    property string st_frame_color: st_overlay_color
    property color st_rect_color: Qt.tint(CoreImport._Base_Color_Canva, "#33333300") // "transparent"

    property string st_background_color: Qt.lighter(st_theme_color, 1.2) // TODO Base_Background_color
    property real st_gradient_positionA: CoreImport._Base_Gradient_PositionA
    property real st_gradient_positionB: CoreImport._Base_Gradient_PositionB

    /********* values ********/


    /********* alias ********/
    property var mainapp_pointer
    property string _icon_path: CoreImport.navibar_icons_path
    property string _expand_img_src: "../../" + _icon_path + "expand" + ".png"
    property string st_label_text: "navi menu" /* TODO */

    id: root
    width: parent.width
    height: st_height
    visible: true

    gradient: Gradient {
        orientation:Gradient.Horizontal
        GradientStop { position: st_gradient_positionA; color: st_background_color }
        GradientStop { position: st_gradient_positionB; color: "white" }
    }

    Component.onCompleted: {
    }

    Label {
        id: i_label
        width: root.width/2 /* TODO */
        height: root.height * st_label_height_ratio
        x: i_frame.x + i_frame.width/16
        text: st_label_text
        color: st_font_color
        minimumPointSize: 5
        font.pointSize: 600
        fontSizeMode: Text.Fit
        verticalAlignment: Text.AlignBottom
    }

    Rectangle{
        id: i_frame
        x: 0
        y: 0
        z: 20
        color: st_rect_color
        width: root.width
        height: root.height
        anchors.top: i_label.bottom
        border.width: st_border_width
        border.color: st_frame_color
        radius: border.width*width/height
        visible: true
        clip: false
    }
}





