import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "BaseItems";

Base {
    /********* size settings ********/

    property real buttons_width_mlt: 3.5

    /********* colors settings ********/

    /********* values ********/
    property int width_grid_sz: width*st_side_crop / 10
    property int composition_side_crop: (width - (width * st_side_crop))/2

    property int vertical_gap: height/20

    /********* alias ********/

    /********* translated ********/
    property string st_save_button_text: qsTr("Save")
    property string st_increase_button_text: qsTr("Up ++")
    property string st_decrease_button_text: qsTr("Down --")

    function try_to_set_value(_value){
        if(!(cmd_manager.isConnected)){
            i_textfield.append_data("not connected\n");
            return;
        }
        else if(!theVehicle.is_tyres_threshold_available){
            i_textfield.append_data("not supported\n");
            return;
        }
        if(_value > theVehicle.tyres_threshold){
            if(cmd_manager.setCalibratorValue(CoreImport._ELP_VEHICLE_SET_TYRES_THRESHOLD, _value)){
                i_centr_indctr.value_up();
            }
        }
        else if(_value < theVehicle.tyres_threshold){
            if(cmd_manager.setCalibratorValue(CoreImport._ELP_VEHICLE_SET_TYRES_THRESHOLD, _value)){
                i_centr_indctr.value_dwn();
            }
        }
        cmd_manager.updateVehicleStatus();
    }

    function retranslateUi(){
        st_save_button_text = qsTr("Save");
        st_increase_button_text = qsTr("Up ++");
        st_decrease_button_text = qsTr("Down --");
    }

    Connections {
        target: qmlTranslator  /* registered in root context */
        function onLanguageChanged(){
            retranslateUi();
        }
    }

    Component.onCompleted: {
        cmd_manager.updateVehicleStatus();
        retranslateUi();
    }

    id: root
    width: parent.width
    height: parent.height

    MltButton{
        id: i_save_button
        x: composition_side_crop
        y: heigth_grid_sz / 2
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        readonly property int st_button_center_x: x + width/2
        readonly property int st_button_center_y: y + height/2
        visible: theVehicle.is_tyres_threshold_available

        st_button_mode: true
        st_text: st_save_button_text
        st_current_color: st_B_color
        function cmd(){
            if(!(cmd_manager.isConnected)){
                i_textfield.append_data("not connected\n")
            }
            else if(theVehicle.is_tyres_threshold_available){
                cmd_manager.saveVehicleStatus(false);
            }
            else {
                i_textfield.append_data("failed to save\n")
            }
        }

    }

    MltButton{
        id: i_increase_button
        x: root.width - width - composition_side_crop
        y: (heigth_grid_sz / 2)
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        readonly property int st_button_center_x: x + width/2
        readonly property int st_button_center_y: y + height/2
        visible: theVehicle.is_tyres_threshold_available

        st_button_mode: true
        st_text: st_increase_button_text
        st_current_color: st_G_color
        function cmd(){
            try_to_set_value(theVehicle.tyres_threshold + 1);
        }
    }

    MltButton{
        id: i_freeze_button
        x: composition_side_crop
        y: (heigth_grid_sz / 2) * 9.5
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        readonly property int st_button_center_x: x + width/2
        readonly property int st_button_center_y: y + height/2
        visible: false

        st_checkbox_mode: true
        function chkbx_cmd() {
        }

        st_normal_color: st_N_color
        st_hovered_color: st_Y_color
        st_pressed_color: st_Y_color
        st_checked_color: st_Y_color
        st_button_mode: false
    }

    MltButton{
        id: i_decrease_button
        x: root.width - width - composition_side_crop
        y: (heigth_grid_sz / 2)* 9.5
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        readonly property int st_button_center_x: x + width/2
        readonly property int st_button_center_y: y + height/2
        visible: theVehicle.is_tyres_threshold_available

        st_button_mode: true
        st_current_color: st_R_color
        st_text: st_decrease_button_text
        function cmd(){
            try_to_set_value(theVehicle.tyres_threshold - 1);
        }
    }

    readonly property int st_compostition_center_x: (i_save_button.st_button_center_x + i_increase_button.st_button_center_x) / 2
    readonly property int st_compostition_center_y: (i_save_button.st_button_center_y + i_freeze_button.st_button_center_y) / 2
    readonly property int st_distance_from_UpBtm_to_LwrTop: ((i_freeze_button.y - i_freeze_button.height ) - i_save_button.y )


    ButtonPngBased{
        st_img_path: "green_neon_arrow_up.png"
        z: 30
        anchors.bottom: i_centr_indctr.top
        anchors.horizontalCenter: i_centr_indctr.horizontalCenter
        visible: theVehicle.is_tyres_threshold_available
        width: i_centr_indctr.width/2
        height: width/2
        function cmd(){
            try_to_set_value(theVehicle.tyres_threshold + 1);
        }
    }

    CentralButtonIndicator{
        id: i_centr_indctr
        x: st_compostition_center_x - (st_size/2)
        y: st_compostition_center_y - (st_size/2)
        st_size: st_distance_from_UpBtm_to_LwrTop  < i_decrease_button.width * 3 ? st_distance_from_UpBtm_to_LwrTop : i_decrease_button.width * 3
        st_value: theVehicle.is_tyres_threshold_available ? theVehicle.tyres_threshold : 0
    }

    ButtonPngBased{
        st_img_path: "red_neon_arrow_down.png"
        z: 30
        anchors.top: i_centr_indctr.bottom
        anchors.horizontalCenter: i_centr_indctr.horizontalCenter
        visible: theVehicle.is_tyres_threshold_available
        width: i_centr_indctr.width/2
        height: width/2
        function cmd(){
            try_to_set_value(theVehicle.tyres_threshold - 1);
        }
    }

    readonly property int st_button_right_x: root.width - i_decrease_button.x - i_decrease_button.width

    BaseTextField{
        id: i_textfield
        y: (i_freeze_button.y + i_freeze_button.height + vertical_gap)
        height: freeMainframeSpace - y
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        st_text: theVehicle.is_tyres_threshold_available ? CoreImport.tyr_thr_available_description :
                                                           theVehicle.model == 0x0009 ? /* MMC Pajero Sport */
                                                           CoreImport.tyr_thr_lin_available_description:
                                                           CoreImport.tyr_thr_unavailable_description

    }
}

