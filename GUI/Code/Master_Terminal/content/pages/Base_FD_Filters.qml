import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "BaseItems";

Base {
    /********* size settings ********/

    property real buttons_width_mlt: 2.5

    /********* colors settings ********/

    /********* values ********/
    property int width_grid_sz: width*st_side_crop / 10
    property int composition_side_crop: (width - (width * st_side_crop))/2
    property int vertical_gap: height/20

    /********* alias ********/
    property string st_enable_anno: qsTr("Enable");
    property string st_disable_anno: qsTr("Disable");
    property string st_refresh_anno: qsTr("Refresh");
    property string st_apply_anno: qsTr("Apply");

    function retranslateUi(){
        st_enable_anno = qsTr("Enable");
        st_refresh_anno = qsTr("Refresh");
        st_apply_anno = qsTr("Apply");
        st_disable_anno = qsTr("Disable");
    }

    Connections {
        target: qmlTranslator  /* registered in root context */
        function onLanguageChanged(){
            retranslateUi();
        }
    }
    Component.onCompleted: {
        retranslateUi();
    }
    Component.onDestruction: {
    }

    id: root
    width: parent.width
    height: parent.height

    readonly property int _DEVICE_OPERATION_MODE_DEFAULT: 255
    readonly property int _DEVICE_OPERATION_MODE_ON: 1
    readonly property int _DEVICE_OPERATION_MODE_OFF: 2
    readonly property int _DEVICE_OPERATION_MODE_REV: 3
    readonly property int _DEVICE_OPERATION_MODE_CIRCULAR_REV: 4
    readonly property int _DEVICE_OPERATION_MODE_CIRCULAR: 5

    property int st_canOverride_Mode: device_manager.canOverride_Mode
    property int st_calibratorFilter_Mode: device_manager.calibratorFilter_Mode

    MltButton{
        id: i_enable_button
        x: composition_side_crop
        y: heigth_grid_sz / 2
        height: st_initial_item_height
        width: width_grid_sz * 3

        st_button_mode: true

        st_text: (st_canOverride_Mode != _DEVICE_OPERATION_MODE_ON)  ? st_enable_anno : st_disable_anno
        st_normal_color: (st_canOverride_Mode != _DEVICE_OPERATION_MODE_ON) ? st_N_color : st_G_color
        function cmd(){
            root.forceActiveFocus();
            if(st_canOverride_Mode != _DEVICE_OPERATION_MODE_ON) {
                cmd_manager.setDeviceValue(4, _DEVICE_OPERATION_MODE_ON);
            }
            else{
                cmd_manager.setDeviceValue(4, _DEVICE_OPERATION_MODE_OFF);
            }


        }
    }

    MltButton{
        id: i_refresh_button
        anchors.horizontalCenter: parent.horizontalCenter
        y: heigth_grid_sz / 2
        height: st_initial_item_height
        width: width_grid_sz * 3

        st_button_mode: true
        st_text: st_refresh_anno
        st_normal_color: st_O_color

        function cmd(){
            //device_manager.FdcanOverrideFilterModel.init();
            root.forceActiveFocus();
            var update_result = cmd_manager.fdcan_updateOverrideStatus();
          //  if(update_result === true){
                device_manager.fdcan_update_OvrModel_from_OvrSts();
                i_content_loader.item.changes_commited = false;
         //   }

        }
    }



    MltButton{
        id: i_apply_button
        x: root.width - width - composition_side_crop
        y: heigth_grid_sz / 2
        height: st_initial_item_height
        width: width_grid_sz * 3

        st_button_mode: i_content_loader.item.changes_commited
        st_text: st_apply_anno
        st_normal_color: i_content_loader.item.changes_commited ? st_R_color : st_N_color
        function cmd(){
            root.forceActiveFocus();

            device_manager.fdcan_fill_OvrSts_from_OvrModel();

            var update_result = cmd_manager.fdcan_sendOverrideFilterConfiguration();
            if(update_result === true){
                i_content_loader.item.changes_commited = false;
            }

        }
    }



    Flickable {
        id: i_flickable
        width: root.width
        y: (i_enable_button.y + i_enable_button.height + vertical_gap)
        height: freeMainframeSpace - y
        contentHeight: i_content_loader.height
        clip: true
        flickDeceleration  : 1500.00
        maximumFlickVelocity : 1500.00
        ScrollBar.vertical:
            ScrollBar {
                policy: ScrollBar.AlwaysOff
        }


        Loader {
            id: i_content_loader
            y: 0
            x: i_enable_button.x
            width: root.width - (composition_side_crop*2)
            height: i_flickable.height
            sourceComponent: i_ovr_ids
            onLoaded: function(){
            }
        }
    }

        Connections {
            target: i_content_loader.item
            function onSendHeight(msg) {
                i_content_loader.height = msg
            }
        }

        Component {
            id: i_ovr_ids
            Component_Base_FD_Filters_Filters{
                width: i_content_loader.width
                height: i_content_loader.height
                //i_content_loader.widthh
                Component.onCompleted: {
                }
            }
        }



}
