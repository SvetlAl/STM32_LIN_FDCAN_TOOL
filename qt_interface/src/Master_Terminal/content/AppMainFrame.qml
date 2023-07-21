import QtQuick
import QtQuick.Controls
import CoreImport
import "pages" as Pages

Loader {
    property var mainapp_pointer

    id: mainframe_content
    sourceComponent: component_default


    onLoaded: {
        if(item.type === "Base")item.mainapp_pointer = mainapp_pointer
    //    loadItem(CoreImport.pages_path + CoreImport.base_group + CoreImport.default_page);
    }

    signal loadItem(string msg)
    onLoadItem: function LoadItem(msg){
        var component = Qt.createComponent(msg + ".qml");
        if (component === null) {
            console.log("Error creating object " + msg);
        }
        else{
            sourceComponent = component;
            if(item.type === "Base")item.mainapp_pointer = mainapp_pointer
        }
    }

    Component {
        id: component_default
        Pages.Base_Main {
            anchors.fill: parent
        }
    }

}





