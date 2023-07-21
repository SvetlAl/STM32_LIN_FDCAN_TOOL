import QtQuick
import QtQuick.Controls

Drawer {
    property var mainapp_pointer
    property real st_pull_mlt: 0.66;

    property int st_text_sz: CoreImport._GeneralDesign_Font_DrawerItemText

    id: root
    width: parent.width  * st_pull_mlt
    height: parent.height

    onSt_text_szChanged: {
        if(loader_drawer.item != null){
            loader_drawer.item.st_initial_items_text_sz = st_text_sz;
            loader_drawer.item.forceRedraw();
        }
    }

    Loader {
        id: loader_drawer
        width: parent.width
        height: parent.height
        sourceComponent: component_Drawer
        onLoaded: {
            item.st_initial_items_text_sz = st_text_sz
        }
    }

    Component {
        id: component_Drawer
        AppDrawer_default {
            mainapp_pointer: root.mainapp_pointer
        }
    }
}




