import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: root

    /********* size settings ********/
    width: CoreImport.appWidth /* TODO import */
    height: CoreImport.appHeight /* TODO import */
    property int freeMainframeSpace: root.height - i_app_toolbar.height - i_app_navibar.height


    /********* colors settings ********/

    /********* values ********/
    readonly property int st_collapsed_navibar_height: CoreImport._Base_Height_CollapsedNavibar

    /********* alias ********/
    property alias mainframe_handler: i_mainframe_handler
    property alias current_page_group: i_mainframe_handler.current_group

    visible: true

    onClosing: {
        if((Qt.platform.os === "android") & i_mainframe_handler.base_page_index !== 0 ){
            close.accepted = false
            console.log("android")
            i_mainframe_handler.setIndex(0);
            i_mainframe_handler.setPage(CoreImport.pages_path + CoreImport.base_group + CoreImport.default_page);
        }
    }

    /*******************************************************/
    /**********************  Context Menu  *****************/
    /*******************************************************/
    /*
    Menu {
        id: contextMenu
        MenuItem {
            text: qsTr("C&ut")
            shortcut: StandardKey.Cut
            enabled: textInput.selectedText
            onTriggered: textInput.cut()
        }
        MenuItem {
            text: qsTr("&Copy")
            shortcut: StandardKey.Copy
            enabled: textInput.selectedText
            onTriggered: textInput.copy()
        }

        MenuItem {
            text: qsTr("&Paste")
            shortcut: StandardKey.Paste
            enabled: textInput.canPaste
            onTriggered: textInput.paste()
        }
    }
*/

    /*******************************************************/
    /*********************   Drawer   **********************/
    /*******************************************************/
    AppDrawer{
        id: i_app_drawer
        mainapp_pointer: root
    }
    /*******************************************************/
    /*********************   ToolBar  **********************/
    /*******************************************************/
    AppToolBar {
        id: i_app_toolbar
        anchors.top: root.top
        mainapp_pointer: root
        st_toolbar_anno: root.height - i_app_toolbar.height - i_app_navibar.height
    }
    /*******************************************************/
    /*********************   Main area  ********************/
    /*******************************************************/
    AppMainFrame {
        id: i_app_mainframe
        mainapp_pointer: root
        height: root.height - i_app_toolbar.height - i_app_navibar.height
        width: root.width
        anchors.top: i_app_toolbar.bottom
    }

    /*******************************************************/
    /*********************    Navibar   ********************/
    /*******************************************************/
    function collapseNaviBar(){
        i_app_navibar.sourceComponent = component_AppNaviBar_collapsed
        i_app_mainframe.height = Qt.binding(function() { return root.height - i_app_toolbar.height - i_app_navibar.height })
        i_app_navibar.height = Qt.binding(function() { return st_collapsed_navibar_height})
        i_app_navibar.y = Qt.binding(function() { return root.height - i_app_navibar.height })
        CoreImport.navibar_status = CoreImport.NavibarStatus.Navibar_collapsed
    }
    function expandNaviBar(){
        i_app_navibar.sourceComponent = component_AppNaviBar_extended
        i_app_navibar.height = Qt.binding(function() { return root.height - i_app_toolbar.height })
        //i_app_mainframe.height = Qt.binding(function() { return i_app_mainframe.height })
        i_app_navibar.y = Qt.binding(function() { return i_app_mainframe.y })
        CoreImport.navibar_status = CoreImport.NavibarStatus.Navibar_expanded
    }
    function resetNaviBar(){
        i_app_navibar.sourceComponent = component_AppNaviBar
        i_app_mainframe.height = Qt.binding(function() { return root.height - i_app_toolbar.height - i_app_navibar.height })
        i_app_navibar.height = Qt.binding(function() { return CoreImport._Base_Height_Navibar })
        i_app_navibar.y = Qt.binding(function() { return root.height - i_app_navibar.height })
        updateNaviBar(getPageIndex());
        CoreImport.navibar_status = CoreImport.NavibarStatus.Navibar_regular
    }

    function navigatorDown(){
        if(CoreImport.navibar_status === CoreImport.NavibarStatus.Navibar_regular){
            collapseNaviBar();
        }
        else if(CoreImport.navibar_status === CoreImport.NavibarStatus.Navibar_expanded){
            resetNaviBar();
        }
    }
    function navigatorUp(){
        if(CoreImport.navibar_status === CoreImport.NavibarStatus.Navibar_regular){
            expandNaviBar();
        }
        else if(CoreImport.navibar_status === CoreImport.NavibarStatus.Navibar_collapsed){
            resetNaviBar();
        }
    }

    Loader{
       id: i_app_navibar
       width: root.width
       height: CoreImport._Base_Height_Navibar
       y: root.height - height

       property var mainapp_pointer: root
       sourceComponent: component_AppNaviBar

       Component {
           id: component_AppNaviBar
           AppNaviBar {
               mainapp_pointer: i_app_navibar.mainapp_pointer
               _item_index: i_mainframe_handler.base_page_index
           }
       }
       Component {
           id: component_AppNaviBar_collapsed
           AppNaviBar_collapsed {
               mainapp_pointer: i_app_navibar.mainapp_pointer
           }
       }

       Component {
           id: component_AppNaviBar_extended
           AppNaviBar_extended {
               mainapp_pointer: i_app_navibar.mainapp_pointer
           }
       }
   }

    function updateNaviBar(number){
        i_app_navibar.item.reload_navi_view(number);

    }
    function getPageIndex(){
        return i_mainframe_handler.base_page_index;
    }

    Item{
        id: i_mainframe_handler
        property string current_base_page: CoreImport.pages_path + CoreImport.base_group + CoreImport.default_page
        property string current_page: CoreImport.pages_path + CoreImport.base_group + CoreImport.default_page
        property string current_group: CoreImport.base_group
        property int base_page_index: 0

        function setIndex(index){
            base_page_index = index;
        }
        /* page == File path, ".qml" is added in i_app_mainframe.loadItem() */
        function setPage(page){ 
            var group = CoreImport.getPageGroup(page);
            /* transition from Drawer to Base */
            if((group === CoreImport.base_group) && (current_group === CoreImport.draweritem_group)){
                i_app_toolbar.buttonToHamburger();
                current_group = CoreImport.base_group;
                current_page = page;
                current_base_page = page; /* 28.01 */
                showNavibar();
                /* set Nabibar item */
            }
            /* transition from Base to Drawer */
            else if((group === CoreImport.draweritem_group) && (current_group === CoreImport.base_group)){
                i_app_toolbar.buttonToArrow();
                current_group = CoreImport.draweritem_group;
                current_page = page;
                i_app_drawer.close();
                hideNavibar();
                /* hide Nabibar */
            }
            /* transition from Base to Base */
            else if((group === CoreImport.base_group) && (current_group === CoreImport.base_group)){
                current_page = page;
                current_base_page = page;
            }
            i_app_mainframe.loadItem(page)
        }
    }

    /* handles press on Hamburger button */
    function handleToolbarButton(){
        if(mainframe_handler.current_group === CoreImport.base_group){
            i_app_drawer.open();
        }
        else {
            mainframe_handler.setPage(i_mainframe_handler.current_base_page);
        }
    }

    function hideNavibar(){
        i_app_navibar.visible = false;
        i_app_navibar.height = 0;
        //i_app_mainframe.height = Qt.binding(function() { return root.height - i_app_toolbar.height - i_app_navibar.height })
        i_app_navibar.y = Qt.binding(function() { return root.height - i_app_navibar.height })
    }

    function showNavibar(){
        i_app_navibar.visible = true;
        i_app_navibar.height = CoreImport._Base_Height_Navibar;
        i_app_navibar.y = Qt.binding(function() { return root.height - i_app_navibar.height })
        i_app_mainframe.height = Qt.binding(function() { return root.height - i_app_toolbar.height - i_app_navibar.height })

        if(i_app_navibar.sourceComponent == component_AppNaviBar_collapsed){
            collapseNaviBar();
        }
        else if(i_app_navibar.sourceComponent == component_AppNaviBar_extended){
            expandNaviBar();
        }
        else if(i_app_navibar.sourceComponent == component_AppNaviBar){
            resetNaviBar();
        }
    }
}
