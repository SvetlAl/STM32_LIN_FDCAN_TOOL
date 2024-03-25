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
        i_content_loader.sourceComponent =  i_scanner_id
    }


    id: root
    width: parent.width
    height: parent.height

    Flickable {
        id: i_flickable
        width: root.width
        y: vertical_gap //(i_scanner_button.y + i_scanner_button.height + vertical_gap)
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
        Component_Base_LIN_Scanner_Scanner{
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
}



