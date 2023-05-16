import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "SimpleItems";
import "BaseItems";


Rectangle{
    /********* size settings ********/
    property int st_item_height: root.width/2 < CoreImport._ViewScale_Height_Container*1.2 ? root.width/2 : CoreImport._ViewScale_Height_Container*1.2
    // property int st_item_font_sz: st_item_height/3 < st_item_height/3 ? st_item_height/3 : st_item_height/3
    /********* colors settings ********/
    property string st_font_color: CoreImport._Base_Color_BaseFont
    /********* values ********/
    property bool changes_commited: false

    /********* translated ********/
    property string st_apply_anno: qsTr("Apply");
    property string st_refresh_anno: qsTr("Refresh");
    property string st_enable_anno: qsTr("Enable");
    property string st_disable_anno: qsTr("Disable");


    function retranslateUi(){
        st_apply_anno = qsTr("Apply");
        st_refresh_anno = qsTr("Refresh");
        st_enable_anno = qsTr("Enable");
        st_disable_anno = qsTr("Disable");
    }


    /********* alias ********/

    id: root
    color: "transparent"

    Component.onCompleted: {
        var update_result = cmd_manager.updateOverrideStatus();
        if(update_result === false){
            if(device_manager.DiscardIdModel.length === 0)device_manager.DiscardIdModel.init();
        }
        calculateHeight();
    }
    Component.onDestruction: {
     //   bus_manager.DiscardIdModel.deinit();
    }

    signal modelSelected(string modelname, int modelvalue)

    signal sendHeight(int msg)
    function calculateHeight(){
        var total_height = 0
        for(var i = root.children.length; i > 0 ; i--) {
            if(root.children[i-1].type !== "focus_reset"){
                total_height += root.children[i-1].height
                total_height += root.children[i-1].anchors.topMargin
            }
        }
        root.height = total_height
        sendHeight(total_height)
    }

    readonly property int _DEVICE_OPERATION_MODE_DEFAULT: 255
    readonly property int _DEVICE_OPERATION_MODE_ON: 1
    readonly property int _DEVICE_OPERATION_MODE_OFF: 2
    readonly property int _DEVICE_OPERATION_MODE_REV: 3
    readonly property int _DEVICE_OPERATION_MODE_CIRCULAR_REV: 4
    readonly property int _DEVICE_OPERATION_MODE_CIRCULAR: 5

    property int st_canOverride_Mode: device_manager.canOverride_Mode
    property int st_calibratorFilter_Mode: device_manager.calibratorFilter_Mode

    MltButton{
        id: i_en_disable_button
        anchors.top: root.top
        anchors.right: i_refresh_button.left
        anchors.rightMargin: width/5

        height: st_item_height
        width: root.width/4
        st_button_mode: true

        st_text: ((st_canOverride_Mode != _DEVICE_OPERATION_MODE_ON) | (st_canOverride_Mode != _DEVICE_OPERATION_MODE_ON)) ? st_enable_anno : st_disable_anno
        st_normal_color: ((st_canOverride_Mode != _DEVICE_OPERATION_MODE_ON) | (st_canOverride_Mode != _DEVICE_OPERATION_MODE_ON)) ? st_N_color : st_G_color
        function cmd(){
            root.forceActiveFocus();
            if(st_canOverride_Mode == _DEVICE_OPERATION_MODE_ON){
                cmd_manager.setDeviceValue(4, _DEVICE_OPERATION_MODE_OFF);
                if(st_calibratorFilter_Mode == _DEVICE_OPERATION_MODE_ON)
                    cmd_manager.setDeviceValue(3, _DEVICE_OPERATION_MODE_OFF);
            }
            else if(st_canOverride_Mode != _DEVICE_OPERATION_MODE_ON){
                cmd_manager.setDeviceValue(4, _DEVICE_OPERATION_MODE_ON);
                if(st_calibratorFilter_Mode != _DEVICE_OPERATION_MODE_ON)
                    cmd_manager.setDeviceValue(3, _DEVICE_OPERATION_MODE_OFF);
            }
        }
    }


    MltButton{
        id: i_refresh_button
        anchors.top: root.top
        anchors.horizontalCenter: root.horizontalCenter
        height: st_item_height
        width: root.width/4
        st_button_mode: true

        st_text: st_refresh_anno
        st_normal_color: st_B_color
        function cmd(){
            root.forceActiveFocus();
            var update_result = cmd_manager.updateOverrideStatus();
            if(update_result === true){
                device_manager.update_DscModel_from_OvrSts();
                changes_commited = false;
            }
        }
    }

    MltButton{
        id: i_apply_button
        anchors.top: root.top
        anchors.left: i_refresh_button.right
        anchors.leftMargin: width/5

        height: st_item_height
        width: root.width/4
        st_button_mode: true

        st_text: st_apply_anno
        st_normal_color: changes_commited ? st_R_color : st_B_color
        function cmd(){
            root.forceActiveFocus();
           // device_manager.update_DscModel_from_OvrSts();
            device_manager.fill_OvrSts_from_DscModel();


            var update_result = cmd_manager.sendOverrideFilterConfiguration();
            if(update_result === true){
                changes_commited = false;
            }

        }
    }

    ListView  {
        id: listView
        parent: root
        anchors.top: i_refresh_button.bottom
        anchors.topMargin: i_refresh_button.height/5
        height: device_manager.DiscardIdModel.length * st_item_height
        width: root.width
        boundsBehavior: Flickable.DragOverBounds
        clip: true
        cacheBuffer: 2

        model: device_manager.DiscardIdModel
        delegate:
            Rectangle{

            height: st_item_height + st_item_height/4
            width: root.width
            color: "transparent"

                Item_CAN_discard_id{
                    st_total_height: st_item_height
                    theIdValue: "0x" + modelData.id_value
                    st_filter_enabled: modelData.isEnabled
                    st_editable: modelData.isEditable
                    can_value: modelData.dir_value
                    visible: true

                    function setCanValue(_val){
                        root.forceActiveFocus();
                        device_manager.DiscardIdModel.set_filter_can_value(index, _val);
                        changes_commited = true;
                    }

                    function setIdValue(_val){
                       // root.forceActiveFocus();
                        device_manager.DiscardIdModel.set_filter_id_value(index, _val);
                        changes_commited = true
                    }

                    function onclick(){
                       // console.log(index)
                        root.forceActiveFocus();
                       device_manager.DiscardIdModel.enable_filter(index, !modelData.isEnabled);
                       changes_commited = true;
                    }
                }
                Rectangle{
                    height: st_item_height/4
                    color: "transparent"
                }
        }

    }

}
