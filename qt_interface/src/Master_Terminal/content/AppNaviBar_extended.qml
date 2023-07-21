import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import "pages/BaseItems" as BaseItems;

Rectangle {

    /********* size settings ********/
    property int st_height: 200 // CoreImport._Base_Height_Navibar
    property int st_item_height: CoreImport._ViewScale_Height_Container
    property real st_label_height: 0.2 /* TODO */
    property int st_item_font_sz: st_item_height/3
    property int st_border_width: CoreImport._Base_Width_ButtonBorder*2

    /********* colors settings ********/
    property string st_overlay_color: CoreImport._Base_Color_IconOverlay
    property string st_overlay_color_pressed: Qt.tint(st_overlay_color, "#33333300") // "#87D6FF"
    property string st_font_color: CoreImport._Base_Color_BaseFont
    property string st_frame_color: CoreImport._Base_Color_Icon
    property string st_backgr_color: "transparent"

    /********* values ********/
    property var navi_files_list
    property var navi_list

    /********* alias ********/
    property string _icon_path: CoreImport.navibar_icons_path
    property string _collapse_img_src: "../../" + _icon_path + "collapse" + ".png"
    property var mainapp_pointer
    property var _root_items: CoreImport.base_items
    property var _root_filenames: CoreImport.base_items_filenames

    id: root
    width: parent.width
    height: st_height
    color: "transparent"
    property color st_rect_color: "#ffffff"
    visible: true

    function press_cntr_btn(){
        setPage(_item_index)
    }

    function reload_navi_view(num){
    }

    function setPage(page_num){
     //   mainapp_pointer.mainframe_handler.setPage(CoreImport.pages_path + _root_filenames[page_num])
    }

    Component.onCompleted: {
    }

    function clearColumn(){
        for(var i = i_column.children.length; i > 0 ; i--) {
            if(i_column.children[i-1].type !== "focus_reset"){
               i_column.children[i-1].destroy();
            }
        }
    }

    function init(){
        clearColumn();
        i_column.fill_navi_items();
    }

    /*************************** Main frame **********************************/
    Rectangle{
        id: i_frame
        x: 0
        y: 0
        z: 20
        color: st_rect_color
        width: root.width
        height: root.height
        anchors.top: root.top
        border.width: st_border_width
        border.color: st_frame_color
        radius: 20
        visible: true
        clip: false

        Flickable {
            id: i_flickable
            width: root.width
            y: i_frame.y + i_frame.radius
            height:  root.height  - i_frame.radius*2
            contentHeight: _root_filenames.length * st_item_height
            clip: true
            flickDeceleration  : 1500.00
            maximumFlickVelocity : 1500.00
            ScrollBar.vertical:
                ScrollBar {
                    policy: ScrollBar.AlwaysOn
            }
    /*************************** Content **********************************/
                Column {
                    id: i_column
                    width: root.width
                    clip: true

                    Component.onCompleted:{
                        init();
                    }

                    function fill_navi_items(){
                    navi_files_list = _root_filenames;
                    navi_list = _root_items;

                    for(var i=0; i < navi_list.length ;i++){
                    Qt.createQmlObject('import QtQuick
                                        import QtQuick.Controls
                                        import QtQuick.Layouts
                                        import CoreImport;

                                            ItemDelegate {
                                                id: delegate_'+navi_files_list[i]+'
                                                parent: i_column
                                                width: parent.width
                                                height: st_item_height

                                               Image {
                                                 id: img_'+navi_files_list[i]+'
                                                 height: parent.width/7 > st_item_height*0.8 ? st_item_height*0.8 : parent.width/7
                                                 width: height
                                                 anchors.left: delegate_'+navi_files_list[i]+'.left
                                                 anchors.verticalCenter: delegate_'+navi_files_list[i]+'.verticalCenter
                                                 anchors.leftMargin: width/2
                                                 opacity: 1.0
                                                 fillMode: Image.PreserveAspectFit
                                                 clip: true
                                                 source: _icon_path + navi_files_list['+i+'] + ".png"
                                               }


                                                Text{
                                                    id: text_'+navi_files_list[i]+'
                                                    x: img_'+navi_files_list[i]+'.x + img_'+navi_files_list[i]+'.width*1.5
                                                    anchors.verticalCenter: delegate_'+navi_files_list[i]+'.verticalCenter
                                                    clip: true
                                                    font.pixelSize: parent.width/text.length > st_item_font_sz ? st_item_font_sz : parent.width/text.length
                                                    text: "'+navi_list[i]+'"

                                                }

                                                onClicked :{
                                                    mainapp_pointer.updateNaviBar('+i+');

                                                    mainapp_pointer.mainframe_handler.setIndex('+i+');
                                                    mainapp_pointer.mainframe_handler.setPage(CoreImport.pages_path + "'+navi_files_list[i]+'"); 
                                                    mainapp_pointer.resetNaviBar();
                                                }

                                            }', i_column, "AppNaviBar_extended" );}
                }
            }
        }
    }
}
                                                    // font.bold: _selected_language === "'+language_list[i]+'" ? true : false
