import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "SimpleItems";

Item {
    /********* size settings ********/
    property int st_item_height: CoreImport._ViewScale_Height_Container*1.2
    property int st_item_font_sz: st_item_height/3
    /********* colors settings ********/
    /********* values ********/
    /********* translated ********/


    /********* alias ********/
    property var language_list
    property string _current_language: CoreImport.current_language
    property string _selected_language: CoreImport.current_language

    id: root
    width: parent.width

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

    signal setSelectedLanguage(string msg)
    function selectLanguage(lng){
        _selected_language = lng
        setSelectedLanguage(lng)
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
        i_column.fill_lang_list_items();
        calculateHeight();
    }

    Column {
        id: i_column
        width: root.width
        clip: true

        Component.onCompleted:{
            init();
        }

        function fill_lang_list_items(){
        language_list = CoreImport.supported_languages;

            for(var i=0; i < language_list.length ;i++){
                Qt.createQmlObject('import QtQuick
                                    import QtQuick.Controls
                                    import QtQuick.Layouts
                                    import CoreImport;
                                    import "SimpleItems";

                                        ItemDelegate {
                                            id: delegate_'+language_list[i]+'
                                            parent: i_column
                                            width: parent.width
                                            height: st_item_height

                                           Image {
                                             id: img_'+language_list[i]+'
                                             height: parent.width/7 > st_item_height ? st_item_height : parent.width/7
                                             width: height
                                             anchors.left: delegate_'+language_list[i]+'.left
                                             anchors.verticalCenter: delegate_'+language_list[i]+'.verticalCenter
                                             anchors.leftMargin: width/2
                                             opacity: 1.0
                                             fillMode: Image.PreserveAspectFit
                                             clip: true
                                             source: CoreImport.flag_files_path + "'+language_list[i]+'.png"
                                           }


                                            Text{
                                                id: text_'+language_list[i]+'
                                                x: img_'+language_list[i]+'.x + img_'+language_list[i]+'.width*1.5
                                                anchors.verticalCenter: delegate_'+language_list[i]+'.verticalCenter
                                                clip: true
                                                font.pixelSize: parent.width/text.length > st_item_font_sz ? st_item_font_sz : parent.width/text.length
                                                text: "'+language_list[i]+'"
                                                font.bold: _selected_language === "'+language_list[i]+'" ? true : false
                                            }

                                            onClicked :{
                                                selectLanguage("'+language_list[i]+'")
                                            }

                                        }', i_column, "DrawerItem_Language" );
            }
        }
    }
}
