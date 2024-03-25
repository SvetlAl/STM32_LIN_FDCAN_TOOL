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
            if(device_manager.OverrideFilterModel.length === 0)device_manager.OverrideFilterModel.init();
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
                device_manager.update_OvrModel_from_OvrSts();
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
            device_manager.fill_OvrSts_from_OvrModel();

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
        height: device_manager.OverrideFilterModel.length * st_item_height
        width: root.width
        boundsBehavior: Flickable.DragOverBounds
        clip: true
        cacheBuffer: 2

        model: device_manager.OverrideFilterModel
        delegate:
            Rectangle{

            height: i_filter.height
            width: root.width
            color: "transparent"

                Item_CAN_override_filter{
                    id: i_filter
                    st_total_height: st_item_height*1.2
                    height: st_edit_mode ? (st_total_height + st_vertical_gap)*5 : (st_total_height + st_vertical_gap)

                    st_editable: modelData.isEditable
                    theIdValue: "0x" + modelData.id_value
                    st_filter_enabled: modelData.enabled
                    can_value: modelData.dir_value

                    function onCanSelected(_val){
                        modelData.dir_value = _val
                        changes_commited = true;
                    }

                    function setIdValue(_val){
                   //     device_manager.set_discard_id_value(index, theValue);
                        modelData.id_value = _val
                        changes_commited = true;
                    }

                    function onclick(){
                   //     device_manager.enable_discard_id(index, !modelData.isEnabled);
                        device_manager.OverrideFilterModel.enable_filter(index, !st_filter_enabled);
                        changes_commited = true;
                    }

                    function onEditModeChanged(){
                        calculateHeight();
                    }

                    theByte0: "0x" + modelData.str_byte0
                    enabled_0: modelData.byte0_on
                    function setByte0Value(theIdValue){
                        modelData.str_byte0 = theIdValue;
                        changes_commited = true;
                    }
                    function enableByte0filter(_val){
                        modelData.byte0_on = _val
                        changes_commited = true;
                    }

                    theByte1: "0x" + modelData.str_byte1
                    enabled_1: modelData.byte1_on
                    function setByte1Value(theIdValue){
                        modelData.str_byte1 = theIdValue;
                        changes_commited = true;
                    }
                    function enableByte1filter(_val){
                        modelData.byte1_on = _val
                        changes_commited = true;
                    }

                    theByte2: "0x" + modelData.str_byte2
                    enabled_2: modelData.byte2_on
                    function setByte2Value(theIdValue){
                        modelData.str_byte2 = theIdValue;
                        changes_commited = true;
                    }
                    function enableByte2filter(_val){
                        modelData.byte2_on = _val
                        changes_commited = true;
                    }

                    theByte3: "0x" + modelData.str_byte3
                    enabled_3: modelData.byte3_on
                    function setByte3Value(theIdValue){
                        modelData.str_byte3 = theIdValue;
                        changes_commited = true;
                    }
                    function enableByte3filter(_val){
                        modelData.byte3_on = _val
                        changes_commited = true;
                    }

                    theByte4: "0x" + modelData.str_byte4
                    enabled_4: modelData.byte4_on
                    function setByte4Value(theIdValue){
                        modelData.str_byte4 = theIdValue;
                        changes_commited = true;
                    }
                    function enableByte4filter(_val){
                        modelData.byte4_on = _val
                        changes_commited = true;
                    }

                    theByte5: "0x" + modelData.str_byte5
                    enabled_5: modelData.byte5_on
                    function setByte5Value(theIdValue){
                        modelData.str_byte5 = theIdValue;
                        changes_commited = true;
                    }
                    function enableByte5filter(_val){
                        modelData.byte5_on = _val
                        changes_commited = true;
                    }

                    theByte6: "0x" + modelData.str_byte6
                    enabled_6: modelData.byte6_on
                    function setByte6Value(theIdValue){
                        modelData.str_byte6 = theIdValue;
                        changes_commited = true;
                    }
                    function enableByte6filter(_val){
                        modelData.byte6_on = _val
                        changes_commited = true;
                    }

                    theByte7: "0x" + modelData.str_byte7
                    enabled_7: modelData.byte7_on
                    function setByte7Value(theIdValue){
                        modelData.str_byte7 = theIdValue;
                        changes_commited = true;
                    }
                    function enableByte7filter(_val){
                        modelData.byte7_on = _val
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
