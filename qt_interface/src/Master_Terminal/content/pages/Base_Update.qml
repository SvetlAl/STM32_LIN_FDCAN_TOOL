import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "BaseItems";
import "SimpleItems";

Base {
    /********* size settings ********/

    property real buttons_width_mlt: 4.2

    /********* colors settings ********/

    /********* values ********/
    property int width_grid_sz: width*st_side_crop / 10
    property int composition_side_crop: (width - (width * st_side_crop))/2
    property int vertical_gap: height/20


    property int update_mode: CoreImport.UpdateMode.WebUpdate



    function setUpdateMode(mode){
        if(mode === CoreImport.UpdateMode.WebUpdate){
            update_mode = CoreImport.UpdateMode.WebUpdate
            i_recovery_filename.visible = false
            i_recovery_filename._enabled = false
            i_filename.visible = false
            i_filename._enabled = false
            i_version_override.visible = true

            i_recovery_app_override_button.st_normal_color = i_recovery_app_override_button.st_B_color
            i_web_update_button.st_normal_color = i_web_update_button.st_G_color
            i_file_button.st_normal_color = i_file_button.st_N_color
        }
        else if(mode === CoreImport.UpdateMode.FileUpdate){
            update_mode = CoreImport.UpdateMode.FileUpdate
            i_recovery_filename.visible = false
            i_recovery_filename._enabled = false
            i_filename.visible = true
            i_filename._enabled = true
            i_version_override.visible = false

            i_recovery_app_override_button.st_normal_color = i_recovery_app_override_button.st_B_color
            i_web_update_button.st_normal_color = i_web_update_button.st_N_color
            i_file_button.st_normal_color = i_file_button.st_G_color
        }
        else if(mode === CoreImport.UpdateMode.RecoveryOverride){
            update_mode = CoreImport.UpdateMode.RecoveryOverride
            i_recovery_filename.visible = true
            i_recovery_filename._enabled = true
            i_filename.visible = false
            i_filename._enabled = false
            i_version_override.visible = false

            i_recovery_app_override_button.st_normal_color = i_recovery_app_override_button.st_R_color
            i_web_update_button.st_normal_color = i_web_update_button.st_N_color
            i_file_button.st_normal_color = i_file_button.st_N_color
        }
    }

    /********* alias ********/

    property string st_update_avail_anno: qsTr("Update available");
    property string st_update_unavail_anno: qsTr("Up-to-date");
    property string st_recovery_anno: qsTr("Recovery override");
    property string st_achtung_anno: qsTr("Customize update path in the Settings.");
    property string st_file_anno: qsTr("Filename");
    property string st_recovery_file_anno: qsTr("Recovery filename");
    property string st_fromWeb_anno: qsTr("From Web");
    property string st_fromDisk_anno: qsTr("From Disk");

    function retranslateUi(){
        st_update_avail_anno = qsTr("Update available");
        st_update_unavail_anno = qsTr("Up-to-date");
        st_recovery_anno = qsTr("Recovery override");
        st_achtung_anno = qsTr("Customize update path in the Settings.");
        st_file_anno = qsTr("Filename");
        st_recovery_file_anno = qsTr("Recovery filename");
        st_fromWeb_anno = qsTr("From Web");
        st_fromDisk_anno = qsTr("From Disk");
    }

    Connections {
        target: qmlTranslator  /* registered in root context */
        function onLanguageChanged(){
            retranslateUi();
        }
    }

    Component.onCompleted: {
        root.forceActiveFocus();
        if(!versionManager.isInterfaceInfoAppended){
            versionManager.printInterfaceVersions();
            versionManager.isInterfaceInfoAppended = true;
        }
        retranslateUi();
    }

    id: root
    width: parent.width
    height: parent.height

    MltButton{
        id: i_update_button
        x: composition_side_crop
        y: heigth_grid_sz / 2
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        readonly property int st_button_center_x: x + width/2
        readonly property int st_button_center_y: y + height/2

        st_button_mode: true
        st_text: versionManager.isNewHardwareApplicationAvailable ? st_update_avail_anno : st_update_unavail_anno ;
        st_normal_color: versionManager.isNewHardwareApplicationAvailable ? st_Y_color : st_B_color
        function cmd(){
            cmd_manager.verif_test()
            // interface_console.reset_firmware_update_string();
        }

    }

    MltButton{
        id: i_recovery_app_override_button
        x: root.width - width - composition_side_crop
        y: (heigth_grid_sz / 2)
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        readonly property int st_button_center_x: x + width/2
        readonly property int st_button_center_y: y + height/2

        st_button_mode: true
        st_text: st_recovery_anno
        st_normal_color: st_N_color
        function cmd(){
            setUpdateMode(CoreImport.UpdateMode.RecoveryOverride)
        }
    }

    MltButton{
        id: i_web_update_button
        x: composition_side_crop
        y: (heigth_grid_sz / 2) * 9.5
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        readonly property int st_button_center_x: x + width/2
        readonly property int st_button_center_y: y + height/2

        st_button_mode: true
        st_text: st_fromWeb_anno
        st_normal_color: st_G_color

        function cmd(){
            setUpdateMode(CoreImport.UpdateMode.WebUpdate)
        }
    }

    MltButton{
        id: i_file_button
        x: root.width - width - composition_side_crop
        y: (heigth_grid_sz / 2)* 9.5
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        readonly property int st_button_center_x: x + width/2
        readonly property int st_button_center_y: y + height/2

        st_button_mode: true
        st_text: st_fromDisk_anno
        st_normal_color: st_N_color

        function cmd(){
            setUpdateMode(CoreImport.UpdateMode.FileUpdate)
        }
    }

    readonly property int st_compostition_center_x: (i_update_button.st_button_center_x + i_recovery_app_override_button.st_button_center_x) / 2
    readonly property int st_compostition_center_y: (i_update_button.st_button_center_y + i_web_update_button.st_button_center_y) / 2
    readonly property int st_distance_from_UpBtm_to_LwrTop: ((i_web_update_button.y - i_web_update_button.height ) - i_update_button.y )

    CentralButton{
        id: i_main_button
        x: st_compostition_center_x - (st_size/2)
        y: st_compostition_center_y - (st_size/2)
        st_size: st_distance_from_UpBtm_to_LwrTop  < i_file_button.width * 3 ? st_distance_from_UpBtm_to_LwrTop : i_file_button.width * 3

        st_text: "Update"
        st_current_color: versionManager.isNewHardwareApplicationAvailable ? st_B_color : st_N_color

        function cmd(){
            interface_console.append_firmware_update("Please wait...")
           // delay(300);

           i_main_button.forceActiveFocus();
            switch(update_mode){
                case CoreImport.UpdateMode.WebUpdate:{
                    if(versionManager.isNewHardwareApplicationAvailable)
                        webManager.put_up_download(2);
                    else if(i_version_override.st_checkbox_value)
                        webManager.put_up_download(1);
                    else interface_console.append_firmware_update("No new firmware found.")
                    break;
                }

                case CoreImport.UpdateMode.FileUpdate:{
                    cmd_manager.startFileUpdate(i_filename._value)
                    break;
                }

                case CoreImport.UpdateMode.RecoveryOverride:{
                    cmd_manager.startEmerencyProgramm(i_recovery_filename._value);
                    break;
                }
                default:
                    break;

            }

        }
    }
    readonly property int st_button_right_x: root.width - i_file_button.x - i_file_button.width

    Rectangle{
        id: i_achtung
        y: (i_web_update_button.y + i_web_update_button.height)
        width: root.width * st_side_crop
        height: st_initial_item_height
        anchors.horizontalCenter: root.horizontalCenter
        visible: true
        color: "transparent"

        Image {
            id: img_achtung
            height: i_achtung.height
            width: height
            y: 0
            x: 0
            source: "./png/warning.png"
            fillMode: Image.PreserveAspectCrop
            clip: true
            visible: true
            antialiasing:  true
            mipmap: true
        }
        Label{
            id: i_achtung_text
            height: i_achtung.height
            width: i_achtung.width - img_achtung.width
            x: img_achtung.x + img_achtung.width
            y: 0
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 250
            smooth: true
            fontSizeMode: Text.Fit
            text: st_achtung_anno
        }
    }

    RoundedTextInput{
        id: i_filename
        y: (i_achtung.y + i_achtung.height + vertical_gap/4)
        x: composition_side_crop
        width: (root.width * st_side_crop)
        _anno: st_file_anno
        visible: false
        _enabled: false
        _value: "custom_can_gateway.bin"
        function update_initial_value(){
            _value = a_txt_input.text;
        }
    }

    RoundedTextInput{
        id: i_recovery_filename
        y: (i_achtung.y + i_achtung.height + vertical_gap/4)
        x: composition_side_crop
        width: (root.width * st_side_crop)
        visible: false
        _enabled: false
        _anno: st_recovery_file_anno
        _value: "recovery_can_gateway.bin"
        function update_initial_value(){
            _value = a_txt_input.text;
        }
    }

    MltButton{
        id: i_version_override
        y: (i_achtung.y + i_achtung.height + vertical_gap/4)
        x: composition_side_crop
        height: st_initial_item_height
        width: (width_grid_sz * buttons_width_mlt)
        visible: true

        st_checkbox_mode: true
        st_text: "Version override"
        st_normal_color: st_N_color
        st_checked_color: st_R_color
    }

    BaseTextField{
        id: i_textfield
        y: (i_filename.y + i_filename.height  + vertical_gap/4 )
        height: freeMainframeSpace - y
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        st_text: interface_console.firmware_update

    }


}



