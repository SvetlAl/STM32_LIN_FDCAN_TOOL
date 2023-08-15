import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import CoreImport;

Item{
    /********* size settings ********/
    property int st_drawer_title_frame_height: CoreImport._GeneralDesign_Height_DrawerTitleFrame
    property int st_drawer_font_sz: CoreImport._GeneralDesign_Font_DrawerTitleFrame
    property int st_items_icon_height: CoreImport._GeneralDesign_Height_DrawerItemIcons
    property int st_initial_items_text_sz: CoreImport._GeneralDesign_Font_DrawerItemText
    property int st_items_text_sz: st_initial_items_text_sz


    /********* colors settings ********/
    property string st_frame_font_color: CoreImport._GeneralDesign_Color_DrawerFrameText
    property string st_drawer_frame_color: CoreImport._GeneralDesign_Color_DrawerFrame
    property real st_drawer_icon_opacity: 0.6
    property string st_items_font_color: CoreImport._GeneralDesign_Color_DrawerItemText

    /********* values ********/
    property int st_logo_position: st_drawer_title_frame_height/10

    /********* alias ********/
    property var mainapp_pointer
    property int _min_label_width: root.width
    property int _max_label_index: 0

    id: root
    visible: true
    clip: true

    /* translated information */
    property string st_title_text: CoreImport.app_name //qsTr("st_title_text")

    function retranslateUi() {
    //    st_title_text = qsTr("st_title_text")
        column.retranslate_dynamic_items()
    }

    Connections {
        target: qmlTranslator
        function onLanguageChanged(){
            retranslateUi()
        }
    }

    function forceRedraw() {
        st_items_text_sz = st_initial_items_text_sz;
        column.find_index_of_max_label();
        column.calculate_font_sz();
    }

    Component.onCompleted: {
        retranslateUi();
    }

    Rectangle{
        id: frame
        width: root.width
        height: st_drawer_title_frame_height
        color: st_drawer_frame_color
        visible: true
        clip: true

        Rectangle{
            id: logo_rect
            width: frame.height < frame.width ? frame.height/2 : frame.width/2
            height: frame.height < frame.width ? frame.height/2 : frame.width/2

            anchors.topMargin: st_logo_position
            anchors.leftMargin: st_logo_position
            anchors.left: frame.left
            anchors.top: frame.top

            radius: 0.8*height
            visible: true
            clip: false

            Image {
                id: img_logo
                width: logo_rect.width
                height: logo_rect.height
                anchors.fill: logo_rect
                source: "./png/logo.jpg"
                fillMode: Image.PreserveAspectCrop
                antialiasing:  true
                smooth: true
                mipmap: true


                clip: false
                visible: false
            }
            OpacityMask {
                id: opacityMask
                anchors.fill: img_logo
                source: img_logo
                maskSource: logo_rect
            }
        }
        Label {
            id: frame_label
            x: st_logo_position/2
            y: frame.y + frame.height - height - st_logo_position/2
            text: st_title_text
            width: root.width - x
            color: st_frame_font_color
            minimumPointSize: height / st_drawer_font_sz
            font.pointSize: st_drawer_font_sz
            fontSizeMode: Text.Fit
            verticalAlignment: Text.AlignBottom
        }

    }

    Flickable {
        id: flickable
        y: frame.y + frame.height
        width: parent.width
        height: parent.height
        anchors.top: frame.bottom
        contentHeight: column.height + frame.height
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        ScrollBar.vertical: ScrollBar { }

        Column{
            id: column
            y: 0
            width: parent.width
            clip: true

            Component.onCompleted: {
                fill_drawer_items()
                find_index_of_max_label()
                calculate_font_sz()
            }

            onWidthChanged: {
                find_index_of_max_label()
                calculate_font_sz()
            }

            /**************** Function: Apply a translation to items in the column ****************/
            function retranslate_dynamic_items(){
                CoreImport.retranslateUi()
                for(var i = 0; i < column.children.length; i++) {
                    column.children[i]._tr_text = CoreImport.drawer_items[i]
                }
            } /* function retranslate_dynamic_items END */


            /**************** Function: Fill the column with labels, images ****************/
            function fill_drawer_items(){
                var drawer_items = CoreImport.drawer_items;
                var drawer_items_filenames = CoreImport.drawer_items_filenames;

                for(var i=0; i < drawer_items.length ;i++){
                    Qt.createQmlObject(
                    'import QtQuick;
                    import QtQuick.Controls;
                    import QtQuick.Layouts;
                    import Qt5Compat.GraphicalEffects;
                    import CoreImport;

                    ItemDelegate {
                        id: delegate_'+drawer_items_filenames[i]+'
                        parent: column
                        width: column.width
                        height: st_items_icon_height
                        topPadding: st_items_icon_height/4

                        Image {
                            id: img_'+drawer_items_filenames[i]+'
                            width: st_items_icon_height
                            height: width
                            anchors.left: delegate_'+drawer_items_filenames[i]+'.left
                            anchors.verticalCenter: delegate_'+drawer_items_filenames[i]+'.verticalCenter
                            anchors.leftMargin: st_items_icon_height / 2
                            opacity: st_drawer_icon_opacity
                            antialiasing:  true
                            smooth: true
                            mipmap: true
                            fillMode: Image.PreserveAspectFit
                            clip: true
                            source: "'+CoreImport.pages_path + CoreImport.img_path + drawer_items_filenames[i]+'.png"
                        }

                        property alias _tr_text: i_label_'+drawer_items_filenames[i]+'.text

                        Label {
                            id: i_label_'+drawer_items_filenames[i]+'
                            property string objtype: "label"
                            x: img_'+drawer_items_filenames[i]+'.x + img_'+drawer_items_filenames[i]+'.width + (img_'+drawer_items_filenames[i]+'.width/2)
                            anchors.verticalCenter: delegate_'+drawer_items_filenames[i]+'.verticalCenter
                            width: frame_label.width - x
                            text: CoreImport.drawer_items['+i+']
                            color: st_items_font_color
                            minimumPointSize: 5
                            font.pixelSize: st_items_text_sz
                            fontSizeMode: Text.Fit
                            verticalAlignment: Text.AlignTop
                        }

                        onClicked:{
                            mainapp_pointer.mainframe_handler.setPage("'+CoreImport.pages_path+''+drawer_items_filenames[i]+'")
                            }
                        }', column, "ContentDrawer_default" );

                }
            } /* fill items END */




            /**************** Function: Find an index of the label with a max width ****************/
            function find_index_of_max_label(){
                var max_label_index = 0;
                var max_label_value = 0;

                for(var i = 0; i < column.children.length; i++) {
                    for(var k = 0; k < column.children[i].children.length; k++) {
                        if(column.children[i].children[k].objtype === "label"){
                            if(column.children[i].children[k].contentWidth > max_label_value){
                                max_label_value = column.children[i].children[k].contentWidth
                                max_label_index = i
                            }
                        }
                    }
                }
                _max_label_index = max_label_index
            }


            /**************** Function: Calculate item labels font size ****************/
            function calculate_font_sz(){
                st_items_text_sz = st_initial_items_text_sz
                for(var m = 0; m < column.children[_max_label_index].children.length; m++) {
                    if(column.children[_max_label_index].children[m].objtype === "label"){
                        st_items_text_sz =  column.children[_max_label_index].children[m].fontInfo.pixelSize
                    }
                }
            }

        }
    }
}

