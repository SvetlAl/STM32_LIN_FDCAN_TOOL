import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "BaseItems";
import "SimpleItems";

Base {
    /********* size settings ********/
    property real buttons_width_mlt: 2.2

    /********* colors settings ********/

    /********* values ********/
    property int width_grid_sz: (width * st_side_crop) / 10
    property int composition_side_crop: (width - (width * st_side_crop))/2

    property int vertical_gap: (height/20)/4

    /********* alias ********/
    property string st_scanner_anno: qsTr("Scanner");
    property string st_analyzer_anno: qsTr("Analyzer");

    function retranslateUi(){
        st_scanner_anno = qsTr("Scanner");
        st_analyzer_anno = qsTr("Analyzer");
    }

    Connections {
        target: qmlTranslator  /* registered in root context */
        function onLanguageChanged(){
            retranslateUi();
        }
    }

    Component.onCompleted: {
        root.forceActiveFocus();
        retranslateUi();
    }

    function setLoaderItem(page){
        if(page === 0){
            i_content_loader.sourceComponent =  i_scanner_id
        }
        else if( page === 1){
            i_content_loader.sourceComponent =  i_analyzer_id
        }
    }


    id: root
    width: parent.width
    height: parent.height

    MltButton{
        id: i_scanner_button
        x: composition_side_crop
        y: heigth_grid_sz / 6
        height: st_initial_item_height
        width: width_grid_sz * 4.5

        st_button_mode: true
        st_text: st_scanner_anno
        st_normal_color: i_content_loader.sourceComponent == i_scanner_id ? st_G_color : st_N_color

        function cmd(){
            root.forceActiveFocus();
            setLoaderItem(0);
        }
    }

    MltButton{
        id: i_analyzer_button
        x: root.width - width - composition_side_crop

        y: heigth_grid_sz / 6
        height: st_initial_item_height
        width: width_grid_sz * 4.5

        st_button_mode: true
        st_text: st_analyzer_anno
        st_normal_color: i_content_loader.sourceComponent == i_analyzer_id ? st_G_color : st_N_color

        function cmd(){
            root.forceActiveFocus();
            setLoaderItem(1);
        }
    }

    Flickable {
        id: i_flickable
        width: root.width
        y: (i_scanner_button.y + i_scanner_button.height + vertical_gap)
        height: freeMainframeSpace - y
        contentHeight: i_content_loader.height
        clip: true
        flickDeceleration  : 1500.00
        maximumFlickVelocity : 1500.00
        ScrollBar.vertical:
            ScrollBar {
            policy: ScrollBar.AlwaysOn
        }

        Loader {
            id: i_content_loader
            y: 0
            x: 0 // i_scanner_button.x
            width: root.width // - (composition_side_crop*2)
            height: i_scanner_id.height
            sourceComponent: i_scanner_id
            onLoaded: function(){
            }
        }
    }

    Connections {
        target: i_content_loader.item
        function onSendHeight(msg) {
            i_content_loader.height = msg;
            console.log(msg);
        }
    }

    Component {
        id: i_scanner_id
        Component_Base_CAN_Scanner_Scanner{
            width: i_content_loader.width
            //height: i_content_loader.height
            freeMainframeSpace: root.freeMainframeSpace - i_flickable.y //i_flickable.height
            Component.onCompleted: {
                height = root.freeMainframeSpace - i_flickable.y
             //   vertical_gap: (i_flickable.height/20)/4
             //   freeMainframeSpace = i_flickable.height
            }
        }
    }

    Component {
        id: i_analyzer_id
        Component_Base_CAN_Scanner_Analyzer{
            width: i_content_loader.width
            //height: i_content_loader.height
            parentHeight: i_flickable.height
            Component.onCompleted: {
            //    parentHeight = i_flickable.height
            }
        }
    }

}



