import QtQuick
import QtQuick.Controls
import "pages/BaseItems" as BaseItems;

ToolBar {
    /********* size settings ********/
    property int st_font_sz: CoreImport._GeneralDesign_Font_ToolBar*0.8
    property int st_height: CoreImport._GeneralDesign_Height_ToolBar

    property int st_sqr_button_height: root.height*0.75

    /********* colors settings ********/
    property string st_toolbar_color: CoreImport._GeneralDesign_Color_ToolBar
    property string st_toolbarText_color: CoreImport._GeneralDesign_Color_ToolBarText

    /********* values ********/
    property var mainapp_pointer
    property string st_toolbar_anno: mainapp_pointer.height

    /********* alias ********/
    property string _icon_path: CoreImport.navibar_icons_path

    property string _expand_img_src: "../../" + _icon_path + "expand" + ".png"
    property string _collapse_img_src: "../../" + _icon_path + "collapse" + ".png"
    property string _home_img_src: "../../" + _icon_path + CoreImport.base_group + CoreImport.default_page + ".png"

    property int _inline_gap: root.width/20
    property int _used_space: root.width - _used_start_x
    property int _used_start_x: i_apptoolbar_button.x + i_apptoolbar_button.width + _inline_gap

    id: root
    width: parent.width
    height: st_height
    position: ToolBar.Footer
    clip: true
    enabled: true
   // layer.enabled: false
    Material.primary: st_toolbar_color

    onHeightChanged: {
    }

    function buttonToArrow(){
        i_apptoolbar_button.transformArrow()
    }

    function buttonToHamburger(){
        i_apptoolbar_button.transformHamburger()
    }

    AppToolBarButton{
        id: i_apptoolbar_button
        height: st_sqr_button_height
        width: st_sqr_button_height
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: width/4

         function clickResponse() {
             mainapp_pointer.handleToolbarButton()
        }
    }

    Label {
        id: i_apptoolbar_label
        x: _used_start_x
        y: (root.height - (contentHeight*1.1))/2
        text: versionManager.current_device_version == "" ? "Serial terminal" : "V " + versionManager.current_device_version
        width: i_home.x - _used_start_x
        height: ((root.height - (i_apptoolbar_button.height -root.height)) * st_font_sz)/100
        minimumPointSize: 5
        font.pointSize: 600
        color: st_toolbarText_color
        fontSizeMode: Text.Fit
    }

    BaseItems.PinIcon{
        id: i_home
        width: st_sqr_button_height*0.9
        height: width
        x: i_collapse.x - i_collapse.width - _inline_gap/2
        anchors.verticalCenter: i_apptoolbar_button.verticalCenter
        st_img_path: _home_img_src
        st_overlay_color: st_toolbarText_color

        function cmd(){
            if(mainapp_pointer.current_page_group === CoreImport.base_group){
                mainapp_pointer.updateNaviBar(0);

                mainapp_pointer.mainframe_handler.setIndex(0);
                mainapp_pointer.mainframe_handler.setPage(CoreImport.pages_path + CoreImport.base_group + CoreImport.default_page);
                mainapp_pointer.resetNaviBar();
            }
        }
    }

    BaseItems.PinIcon{
        id: i_expand
        width: st_sqr_button_height
        height: width
        x: root.width - width*1.0
        anchors.verticalCenter: i_apptoolbar_button.verticalCenter
        st_img_path: _expand_img_src
        st_overlay_color: st_toolbarText_color

        function cmd(){
            if(mainapp_pointer.current_page_group === CoreImport.base_group)
                mainapp_pointer.navigatorUp();
        }
    }

    BaseItems.PinIcon{
        id: i_collapse
        x: i_expand.x - i_expand.width - _inline_gap/2
        width: st_sqr_button_height
        height: width
        anchors.verticalCenter: i_apptoolbar_button.verticalCenter
        st_img_path: _collapse_img_src
        st_overlay_color: st_toolbarText_color
        function cmd(){
            if(mainapp_pointer.current_page_group === CoreImport.base_group)
                mainapp_pointer.navigatorDown();
        }
    }
}

