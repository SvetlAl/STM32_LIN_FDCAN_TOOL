import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;

Rectangle {
    /********* size settings ********/
    property real st_side_crop: CoreImport._GeneralDesign_Ratio_ScreenAdjSideCrop
    property int st_initial_item_height: CoreImport._Base_Height_Item*1.2
    property int st_content_height: 0
    property int heigth_grid_sz: CoreImport._Base_Height_PageGrid // st_initial_item_height*2.0

    /********* colors settings ********/
    property string st_theme_color: CoreImport._GeneralDesign_Color_ToolBar
    property string st_background_color: Qt.lighter(st_theme_color, 1.2) // Base_Background_color
    property real st_gradient_positionA: CoreImport._Base_Gradient_PositionA
    property real st_gradient_positionB: CoreImport._Base_Gradient_PositionB

    /********* values ********/

    /********* alias ********/
    property var mainapp_pointer
    property int freeMainframeSpace: mainapp_pointer.freeMainframeSpace
    readonly property string type: "Base"

    id: root
    anchors.fill: parent

    function retranslateUi(){
    }

    Connections {
        target: qmlTranslator  /* registered in root context */
        function onLanguageChanged(){
            retranslateUi();
        }
    }

    Component.onCompleted:{
        retranslateUi();
        set_font_sz();
    }
    onWidthChanged: {
        set_font_sz();
    }

    function calculate_min_font_sz(){
        var sz = 1000;
        for(var i = 0; i < root.children.length ; i++) {
            if(root.children[i].st_font_resize === true & root.children[i].st_font_pixelSize_info < sz)sz = root.children[i].st_font_pixelSize_info;
        }
        return sz;
    }

    function set_font_sz(){
        for(var i = 0; i < root.children.length ; i++) {
            if(root.children[i].st_font_resize === true)root.children[i].st_font_pixelSize = root.children[i].st_initial_font_pixelSize;
        }
        var sz = calculate_min_font_sz();

        for(var l = 0; l < root.children.length ; l++) {
            if(root.children[l].st_font_resize === true)root.children[l].st_font_pixelSize = sz;
        }
    }

    gradient: Gradient {
        orientation:Gradient.Horizontal
        GradientStop { position: st_gradient_positionA; color: st_background_color }
        GradientStop { position: st_gradient_positionB; color: "white" }
    }
    /*
    Flickable {
        id: i_flickable
        width: root.width * st_side_crop
        height:  root.height
        contentHeight: st_content_height
        clip: true
        flickDeceleration  : 1500.00
        maximumFlickVelocity : 1500.00
        ScrollBar.vertical:
            ScrollBar {
        }
        ************************* Content *************************
    }
*/
}
