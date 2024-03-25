import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import CoreImport


Item {
    /********* size settings ********/
    property int st_border_width : CoreImport._SimpleItems_Width_ButtonBorder /**/
    property int st_indicator_border_width: st_border_width
    property int st_background_border_width: st_border_width
    property int st_indicator_width: root.height  - st_indicator_border_width*4 - st_indicator_border_width*2
    property real st_radius: 2.00
    property real st_ratio_font_sz: CoreImport._SimpleItems_Ratio_ButtonFont

    /********* colors settings ********/
    property string st_clr_active_frame: CoreImport._SimpleItems_Color_FrameActive /**/
    property string st_clr_inactive_frame: CoreImport._SimpleItems_Color_FrameInactive /**/
    property string st_clr_button: CoreImport._SimpleItems_Color_Button /**/
    property string st_clr_text: CoreImport._SimpleItems_Color_ButtonText /**/
    property string  st_i_background_border_color: st_clr_inactive_frame

    /********* values *********/
    property bool _enabled: true
    required property var st_model
    property bool st_editable: false
    // property bool st_indicator_symbol_font_bold: false
    property int st_max_visible_items: 2
    property bool _i_item_text_font_bold: false

    property string st_label_txt: _enabled ? st_model.current_item.name : " n/a "// "st_label_txt"
    /*************************************************************************/
    /*****************   Add to every each text item     *********************/
    /*************************************************************************/
    property int st_initial_font_pixelSize:  1 + root.height * st_ratio_font_sz
    property int st_font_pixelSize: st_initial_font_pixelSize
    readonly property int st_font_pixelSize_info:  btn_txt.fontInfo.pixelSize
    property bool st_font_resize: true

    /********* alias ********/
    property alias _start_index: i_list.currentIndex


    id: root
    width: 250
    height: 100

    function delegateItemPressed(){
    }

    ComboBox {
        id: i_combobox

        width: root.width
        height: root.height
        editable: st_editable ? true : false

        /*****************************************************/
        /*****   Current item, displayed when collapsed   ****/
        /*****************************************************/

        contentItem:
            Rectangle{
            height: parent.height
            width: parent.width  - st_indicator_width*1.1
            anchors.left: parent.left
            color: "transparent"

            Label {
                id: btn_txt
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                /*****************************************************/
                /************  Current text displayed    *************/
                /*****************************************************/
                text: st_label_txt
                width: root.width - st_indicator_width
                height: root.height*0.8
                minimumPointSize: 5
                font.pixelSize:  st_font_pixelSize
                color: st_clr_text
                fontSizeMode: Text.Fit
                clip: true
            }
        }
        background:
            Rectangle {
            /*****************************************************/
            /*****************   Frame design   ******************/
            /*****************************************************/
              //  id: i_background
                width: root.width
                height: root.height
                color: st_clr_button
                border.color:  st_i_background_border_color
                border.width: st_border_width
                radius: height/st_radius
                clip: false
        }

        /*****************************************************/
        /*****************     indicator     *****************/
        /*****************************************************/
        indicator:
            Rectangle {
                height: st_indicator_width
                width: height
                color: st_i_background_border_color
                border.color: st_clr_button
                border.width: st_indicator_border_width
                radius: height/2
                anchors.right: parent.right
                anchors.rightMargin: border.width
                anchors.verticalCenter: parent.verticalCenter
                clip: true
        }
        /*****************************************************/
        /*****************       popup       *****************/
        /*****************************************************/
        popup:
            Popup {
            onAboutToShow:{
                st_indicator_border_width = st_border_width*2
                st_i_background_border_color = st_clr_text
            }
            onClosed:{
                st_indicator_border_width =  st_border_width
                st_i_background_border_color = st_clr_inactive_frame
            }

            height: 300

            background:
                Rectangle {
                y: root.y + root.height
                // id: i_popup
                width: root.width
                height: i_list.count < st_max_visible_items ? i_list.count  * (root.height)*1.25 :
                                                           st_max_visible_items * (root.height )*1.25
                color: st_clr_button
                border.color: st_clr_text
                border.width: st_border_width
                radius: root.height/2


                ListView {
                    id: i_list
                    anchors.fill: parent
                    /*****************************************************/
                    /*****************       Model       *****************/
                    /*****************************************************/
                    model: st_model
                    focus: true
                    height: i_list.count < st_max_visible_items ? i_list.count  * (root.height)*1.25 :
                                                                  st_max_visible_items * (root.height )*1.25
                    clip: true

                    ScrollBar.vertical:
                        ScrollBar {
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        height: parent.height - parent.height/5
                        width: st_background_border_width*10
                        policy: ScrollBar.AlwaysOn
                    }

                    delegate:
                        Component {
                        Item {
                            height: root.height*0.8
                            width: root.width - st_background_border_width*2

                            Text {
                                height: parent.height
                                width: parent.width
                                anchors.horizontalCenter: parent.horizontalCenter
                                fontSizeMode: Text.Fit;
                                minimumPixelSize: 10
                                font.pixelSize: st_font_pixelSize
                                color: st_clr_text
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                /*****************************************************/
                                /*******      Model ROLE displayed here     **********/
                                /*****************************************************/
                                text: modelData.name
                            }

                                MouseArea {
                                    anchors.fill: parent
                                    onPressed:{
                                    }
                                    onReleased:{
                                    }
                                    onClicked:{
                                        i_list.currentIndex = index;
                                        st_model.setCurrentIndex(index)
                                        st_label_txt = st_model.current_item.name
                                        delegateItemPressed();
                                        i_combobox.popup.close()
                                       // console.log(i_list.currentIndex);
                                    }
                                }
                            }
                        } /* component */
                        highlight: Rectangle {
                            color: st_clr_inactive_frame
                            x: parent.x + st_background_border_width
                            height: root.height - st_border_width*20
                            radius: root.height/2
                        }
                    }
            }
        }
    }
}
