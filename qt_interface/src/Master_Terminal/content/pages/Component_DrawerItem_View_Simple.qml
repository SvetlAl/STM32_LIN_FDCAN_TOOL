import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "SimpleItems";

Item {
    /********* size settings ********/
    property int st_item_height: CoreImport._ViewScale_Height_Container*2
    property int st_item_font_sz: st_item_height/3
    /********* colors settings ********/
    /********* values ********/
    /********* translated ********/

    function retranslateUi() {
    }

    Connections {
        target: qmlTranslator
        function onLanguageChanged(){
            retranslateUi()
        }
    }

    Component.onCompleted:{
        retranslateUi();
    }

    signal sendHeight(int msg)
    function calculateHeight(){
        var total_height = 0
        for(var i = i_column.children.length; i > 0 ; i--) {
            if(i_column.children[i-1].type !== "focus_reset"){
                total_height += i_column.children[i-1].height
                total_height += i_column.children[i-1].anchors.topMargin
            }
        }
        root.height = total_height
        sendHeight(total_height)
    }
    /********* alias ********/

    id: root
    width: parent.width

    function clearColumn(){
        for(var i = i_column.children.length; i > 0 ; i--) {
            if(i_column.children[i-1].type !== "focus_reset"){
               i_column.children[i-1].destroy();
            }
        }
    }

    function init(){
        //clearColumn();
        i_column.fill_preset_items();
        calculateHeight();
    }

    Column {
        id: i_column
        width: root.width
        clip: true

        Component.onCompleted:{
            init();
        }

        function fill_preset_items(){
            var preset_names = CoreImport.design_preset_names;

            for(var i=0; i < preset_names.length ;i++){
                Qt.createQmlObject('import QtQuick
                                    import QtQuick.Controls
                                    import QtQuick.Layouts
                                    import CoreImport;
                                    import "SimpleItems";

                                        ItemDelegate {
                                            id: delegate_'+preset_names[i]+'
                                            parent: i_column
                                            width: parent.width
                                            height: st_item_height

                                           Image {
                                             id: img_'+preset_names[i]+'
                                             height: parent.width/7 > st_item_height ? st_item_height : parent.width/7
                                             width: height
                                             anchors.left: delegate_'+preset_names[i]+'.left
                                             anchors.verticalCenter: delegate_'+preset_names[i]+'.verticalCenter
                                             anchors.leftMargin: width/2
                                             opacity: 1.0
                                             fillMode: Image.PreserveAspectFit
                                             clip: true
                                             antialiasing:  true
                                             smooth: true
                                             mipmap: true
                                             source: CoreImport.img_path + "'+preset_names[i]+'.png"
                                           }


                                            Text{
                                                id: text_'+preset_names[i]+'
                                                x: img_'+preset_names[i]+'.x + img_'+preset_names[i]+'.width*1.5
                                                anchors.verticalCenter: delegate_'+preset_names[i]+'.verticalCenter
                                                clip: true
                                                font.pixelSize: parent.width/text.length > st_item_font_sz ? st_item_font_sz : parent.width/text.length
                                                text: "'+preset_names[i]+'"
                                            }

                                            onClicked :{
                                                core.setDesignSizePreset('+[i]+');
                                                calculateHeight();
                                            }

                                        }', i_column, "DrawerItem_View" );
            }
        }
    }
}


