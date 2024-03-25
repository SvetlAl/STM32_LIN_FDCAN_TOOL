import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import CoreImport
import "pages/BaseItems" as BaseItems;

Rectangle {
    /********* size settings ********/
    property int st_height: CoreImport._Base_Height_Navibar
    property int st_border_width: CoreImport._Base_Width_ButtonBorder*2
    property real st_label_height_ratio: 0.25
    property int st_label_font_sz: (root.height * st_label_height_ratio )/1
    property real st_side_crop: CoreImport._GeneralDesign_Ratio_ScreenAdjSideCrop

    /********* colors settings ********/
    property string st_theme_color: CoreImport._GeneralDesign_Color_ToolBar
    property string st_overlay_color: CoreImport._Base_Color_IconOverlay
    property string st_overlay_color_pressed: Qt.tint(st_overlay_color, "#33333300") // "#87D6FF"
    property string st_font_color: CoreImport._Base_Color_BaseFont

    property string st_frame_color: st_overlay_color // CoreImport._Base_Color_Icon
    property color st_rect_color: Qt.tint(CoreImport._Base_Color_Canva, "#33333300") // "transparent"

    property string st_background_color: Qt.lighter(st_theme_color, 1.2) // TODO Base_Background_color
    property real st_gradient_positionA: CoreImport._Base_Gradient_PositionA
    property real st_gradient_positionB: CoreImport._Base_Gradient_PositionB

    /********* values ********/
    property string _left_img_src: _deadend_img_src
    property string _cntr_img_src: _icon_path + _root_filenames[_item_index] + ".png"
    property string _right_img_src: _root_filenames.length > 1 ? _icon_path + _root_filenames[_item_index + 1] + ".png" : _deadend_img_src
    property int _item_index: 0
    property var _root_items: CoreImport.base_items
    readonly property var _root_filenames: CoreImport.base_items_filenames

    /********* alias ********/
    property var mainapp_pointer
    property string _icon_path: CoreImport.navibar_icons_path
    property string _deadend_img_src: _icon_path + "Unavailable.png"
    property string _expand_img_src: "../../" + _icon_path + "expand" + ".png"
    property string _collapse_img_src: "../../" + _icon_path + "collapse" + ".png"

    id: root
    width: parent.width
    height: st_height
    visible: true

    gradient: Gradient {
        orientation:Gradient.Horizontal
        GradientStop { position: st_gradient_positionA; color: st_background_color }
        GradientStop { position: st_gradient_positionB; color: "white" }
    }

    function press_cntr_btn(){
        setPage(_item_index)
    }

    function setPage(page_num){
        mainapp_pointer.mainframe_handler.setPage(CoreImport.pages_path + _root_filenames[page_num]);
        mainapp_pointer.mainframe_handler.setIndex(page_num);
    }

    function reload_navi_view(num){
        _item_index = num;
        _left_img_src = num === 0 ?_deadend_img_src : _icon_path + _root_filenames[num - 1] + ".png"
        _cntr_img_src = _icon_path + _root_filenames[num] + ".png"
        _right_img_src = _root_filenames.length > num + 1 ? _icon_path + _root_filenames[num + 1] + ".png" : _deadend_img_src
    }

    function move_navi_left(){
        if(_item_index != 0){
            _item_index -=1
            reload_navi_view(_item_index)
            setPage(_item_index)
        }
        else {
        }
    }

    function move_navi_right(){
        if((_item_index + 1) < _root_filenames.length){
            _item_index +=1
            reload_navi_view(_item_index)
            setPage(_item_index)
        }
        else{
        }

    }
    Component.onCompleted: {
        reload_navi_view(0);
    }

    /********************* Label ********************/

    Label {
        id: i_label
        width: root.width/2
        height: root.height * st_label_height_ratio
        x: i_frame.x //+ i_frame.width/16
        text: CoreImport.base_items[_item_index]
        color: st_font_color
        minimumPointSize: 5
        font.pointSize: st_label_font_sz
        fontSizeMode: Text.Fit
        verticalAlignment: Text.AlignBottom
    }

    Rectangle{
        id: i_frame
        color: st_rect_color
        width: root.width * st_side_crop
        height: root.height  - i_label.height // i_title_frame.height
        anchors.horizontalCenter: root.horizontalCenter
        anchors.top: i_label.bottom // i_title_frame.bottom
        border.width: st_border_width
        border.color: st_frame_color
        radius: height / 4 // border.width*width/height
        visible: true

        Grid {
            id: i_grid
            width: root.width
            anchors.fill: i_frame
            property real _height_ratio: 2/3
            property real _press_ratio: 0.9
            rows: 1
            columns: 6
            // clip: false

            Rectangle{
                id: i_rect_arrow_left
                color: "transparent"
                width: i_grid.width/i_grid.columns;
                height: i_grid.height

                MouseArea{
                    id: _arrow_left_mouseArea
                    anchors.fill: i_rect_arrow_left
                    hoverEnabled: true
                    onClicked:{
                        root.move_navi_left()
                    }
                }
                Image{
                    id: i_arrow_left
                    source: CoreImport.navibar_icons_path + "navi_aleft.png"
                    width: parent.height < parent.width ? (parent.height* i_grid._press_ratio) : (parent.width * i_grid._press_ratio)
                    height: width
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: true
                    opacity: 0.8
                    antialiasing:  true
                    smooth: true
                    mipmap: true


                    states:[
                        State{
                            name: "hovered"
                            when: _arrow_left_mouseArea.containsMouse & !_arrow_left_mouseArea.containsPress
                            PropertyChanges{
                                target: i_arrow_left
                                width:  (parent.height < parent.width) ? (parent.height) : (parent.width)
                            }
                        },
                        State{
                            name: "pressed"
                            when: _arrow_left_mouseArea.containsPress
                            PropertyChanges{
                                target: i_arrow_left
                                width:  (parent.height < parent.width) ? (parent.height) : (parent.width)
                                opacity: 1.00
                            }
                        }
                    ]
                }
                Layout.column: 1
            }

            Rectangle{
                color: "transparent"
                width: i_grid.width/i_grid.columns;
                height: i_grid.height
                Image{
                    id: i_left_img
                    source: _left_img_src
                    width: parent.height < parent.width ? (parent.height * 0.75 * i_grid._press_ratio) : (parent.width * 0.75 * i_grid._press_ratio)
                    height: width
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: true
                    opacity: 0.8
                    antialiasing:  true
                    smooth: true
                    mipmap: true

                }
                ColorOverlay {
                    anchors.fill: i_left_img
                    source: i_left_img
                    color: st_overlay_color
                    cached: true
                }
                Layout.column: 2
            }

                        /*******************************************************/
                        /**********************  Central  **********************/
                        /*******************************************************/
            Rectangle{
                id: i_rect_centr_button
                color: "transparent"
                width: (i_grid.width/i_grid.columns)*2;
                height: i_grid.height

                MouseArea{
                    id: _centr_button_mouseArea
                    anchors.fill: i_rect_centr_button
                    hoverEnabled: true
                    onClicked:{
                      //  press_cntr_btn();
                    }
                }
                Image{
                    id: i_cntr_img
                    source: _cntr_img_src
                    width: parent.height < parent.width ? (parent.height * i_grid._press_ratio) : (parent.width  * i_grid._press_ratio)
                    height: width
                    y: (i_left_img.parent.height < i_left_img.parent.width) ? i_left_img.y - (i_cntr_img.height - i_left_img.height) : i_left_img.y - i_cntr_img.height*0.35
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: true
                    opacity: 0.8
                    antialiasing:  true
                    smooth: true
                    mipmap: true
                    z: 10


                    states:[
                        State{
                            name: "hovered"
                            when: _centr_button_mouseArea.containsMouse & !_centr_button_mouseArea.containsPress
                            PropertyChanges{
                                target: i_cntr_img
                                width: parent.height < parent.width ? (parent.height) : (parent.width)
                            }
                        },
                        State{
                            name: "pressed"
                            when: _centr_button_mouseArea.containsPress
                            PropertyChanges{
                                target: i_cntr_img
                                width: parent.height < parent.width ? (parent.height) : (parent.width)
                                opacity: 1.00
                            }
                            PropertyChanges{
                                target: i_cntr_img_c_overlay
                                color: st_overlay_color_pressed
                            }
                        }
                    ]
                }
                ColorOverlay {
                    id: i_cntr_img_c_overlay
                    anchors.fill: i_cntr_img
                    source: i_cntr_img
                    color: st_overlay_color
                    z: 10
                    cached: true
                }

                Layout.column: 3
                Layout.columnSpan: 2
            }
            Rectangle{
                color: "transparent"
                width: i_grid.width/i_grid.columns;
                height: i_grid.height
                Image{
                    id: i_right_img
                    source: _right_img_src
                    width: parent.height < parent.width ? (parent.height * 0.75 * i_grid._press_ratio) : (parent.width * 0.75 * i_grid._press_ratio)
                    height: width
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: true
                    opacity: 0.8
                    antialiasing:  true
                    smooth: true
                    mipmap: true

                }
                ColorOverlay {
                    anchors.fill: i_right_img
                    source: i_right_img
                    color: st_overlay_color
                    cached: true
                }
                Layout.column: 5
            }
            Rectangle{
                id: i_rect_arrow_right
                color: "transparent"
                width: i_grid.width/i_grid.columns;
                height: i_grid.height
                MouseArea{
                    id: _arrow_right_mouseArea
                    anchors.fill: i_rect_arrow_right
                    hoverEnabled: true
                    onClicked:{
                        move_navi_right()
                    }
            }
                Image{
                    id: i_arrow_right
                    source: CoreImport.navibar_icons_path +  "navi_aright.png"
                    width: parent.height < parent.width ? (parent.height* i_grid._press_ratio) : (parent.width * i_grid._press_ratio)
                    height: width
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: true
                    opacity: 0.8
                    antialiasing:  true
                    smooth: true
                    mipmap: true


                    states:[
                        State{
                            name: "hovered"
                            when: _arrow_right_mouseArea.containsMouse & !_arrow_right_mouseArea.containsPress
                            PropertyChanges{
                                target: i_arrow_right
                                width:  (parent.height < parent.width) ? (parent.height) : (parent.width)
                            }
                        },
                        State{
                            name: "pressed"
                            when: _arrow_right_mouseArea.containsPress

                            PropertyChanges{
                                target: i_arrow_right
                                width: (parent.height < parent.width) ? (parent.height) : (parent.width)
                                opacity: 1.00
                                }
                        }
                    ]
                }
                Layout.column: 6
            }
        }
    }
}





