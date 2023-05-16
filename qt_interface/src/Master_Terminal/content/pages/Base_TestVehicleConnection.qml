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
    function retranslateUi(){
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
        visible: false // theVehicle.is_odometer_mlt_available
    }

    MltButton{
        id: i_increase_button
        x: root.width - width - composition_side_crop
        y: (heigth_grid_sz / 2)
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        readonly property int st_button_center_x: x + width/2
        readonly property int st_button_center_y: y + height/2
        visible: false // theVehicle.is_odometer_mlt_available
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
    }

    MltButton{
        id: i_decrease_button
        x: root.width - width - composition_side_crop
        y: (heigth_grid_sz / 2)* 9.5
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        readonly property int st_button_center_x: x + width/2
        readonly property int st_button_center_y: y + height/2
        visible: false
    }

    readonly property int st_compostition_center_x: (i_save_button.st_button_center_x + i_increase_button.st_button_center_x) / 2
    readonly property int st_compostition_center_y: (i_save_button.st_button_center_y + i_freeze_button.st_button_center_y) / 2
    readonly property int st_distance_from_UpBtm_to_LwrTop: ((i_freeze_button.y - i_freeze_button.height ) - i_save_button.y )
    readonly property int st_button_right_x: root.width - i_decrease_button.x - i_decrease_button.width

    CentralButton{
        id: i_test_button
        x: st_compostition_center_x - (st_size/2)
        y: st_compostition_center_y - (st_size/2)
        st_size: st_distance_from_UpBtm_to_LwrTop  < i_decrease_button.width * 3 ? st_distance_from_UpBtm_to_LwrTop : i_decrease_button.width * 3
        st_text: "TEST"
        st_current_color: theVehicle.isTestMode ? st_Y_color : st_N_color

        function cmd(){
            if(!(cmd_manager.isConnected)) return;
            if(theVehicle.isTestMode){
                cmd_manager.setCalibratorValue(CoreImport._ELP_VEHICLE_SET_MODE, CoreImport._ELP_VEHICLE_RESET_TEST_MODE_MSK);
                cmd_manager.updateVehicleStatus();
            }
            else{
                cmd_manager.setCalibratorValue(CoreImport._ELP_VEHICLE_SET_MODE, CoreImport._ELP_VEHICLE_SET_TEST_MODE_MSK);
                cmd_manager.updateVehicleStatus();
            }
        }
    }

    BaseTextField{
        id: i_textfield
        y: (i_freeze_button.y + i_freeze_button.height + vertical_gap)
        height: freeMainframeSpace - y
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        st_text: theVehicle.is_speedometer_mlt_available ? CoreImport.test_available_description : CoreImport.test_unavailable_description
    }
}



