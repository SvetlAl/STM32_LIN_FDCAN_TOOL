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

    function clearColumn(){
        for(var i = i_column.children.length; i > 0 ; i--) {
            if(i_column.children[i-1].type !== "focus_reset"){
               i_column.children[i-1].destroy();
            }
        }
    }

    /********* alias ********/
    property var userlist
    property var userLanglist
    property string _current_user: CoreImport.current_user
    property string _selected_user: CoreImport.current_user

    id: root
    width: parent.width

    function init(){
        clearColumn();
        i_column.fill_userlist_items();
        calculateHeight();
    }

    Column {
        id: i_column
        width: root.width
        clip: true

        Component.onCompleted:{
            init();
        }

        function fill_userlist_items(){
        userlist = core.makeUserList();
        userLanglist = core.makeUserLanguagesList();

        for(var i=0; i < userlist.length ;i++){
            Qt.createQmlObject('import QtQuick
                                import QtQuick.Controls
                                import QtQuick.Layouts
                                import CoreImport;
                                import "SimpleItems";

                                    ItemDelegate {
                                        id: delegate_'+userlist[i]+'
                                        parent: i_column
                                        width: parent.width
                                        height: st_item_height

                                       Image {
                                         id: img_'+userlist[i]+'
                                         height: parent.width/7 > st_item_height ? st_item_height : parent.width/7
                                         width: height
                                         anchors.left: delegate_'+userlist[i]+'.left
                                         anchors.verticalCenter: delegate_'+userlist[i]+'.verticalCenter
                                         anchors.leftMargin: width/2
                                         opacity: 1.0
                                         fillMode: Image.PreserveAspectFit
                                         clip: true
                                         source: CoreImport.flag_files_path + "'+userLanglist[i]+'.png"
                                       }


                                        Text{
                                            id: text_'+userlist[i]+'
                                            x: img_'+userlist[i]+'.x + img_'+userlist[i]+'.width*1.5
                                            anchors.verticalCenter: delegate_'+userlist[i]+'.verticalCenter
                                            clip: true
                                            font.pixelSize: parent.width/text.length > st_item_font_sz ? st_item_font_sz : parent.width/text.length
                                            text: "'+userlist[i]+'"
                                            font.bold: _selected_user === "'+userlist[i]+'" ? true : false
                                        }

                                        onClicked :{
                                            _selected_user = "'+userlist[i]+'";
                                        }

                                    }', i_column, "DrawerItem_UserProfile" );}
        }
    }
}
