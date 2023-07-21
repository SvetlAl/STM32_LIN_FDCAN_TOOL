import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "BaseItems";

Base {
    /********* size settings ********/

    property real buttons_width_mlt: 4.2

    /********* colors settings ********/

    /********* values ********/
    property int width_grid_sz: width*st_side_crop / 10
    property int composition_side_crop: (width - (width * st_side_crop))/2

    property int vertical_gap: height/20

    /********* alias ********/

    property string st_update_anno: qsTr("Update");
    property string st_achtung_anno: qsTr("WARNINIG! Critical issues possible.");

    function retranslateUi(){
        st_update_anno = qsTr("Update");
        st_achtung_anno = qsTr("WARNINIG! Critical issues possible.");
    }

    Connections {
        target: qmlTranslator  /* registered in root context */
        function onLanguageChanged(){
            retranslateUi();
        }
    }

    Component.onCompleted: {
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
        st_text: st_update_anno //interface_console.connection_status_description[0]
        st_current_color: st_B_color
        function cmd(){
            webManager.put_up_download(1);
            interface_console.reset_cdc_string();
            // versionManager.printOnUpdate();
        }

    }

    MltButton{
        id: i_vehicle_model_status_button
        x: root.width - width - composition_side_crop
        y: (heigth_grid_sz / 2)
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        readonly property int st_button_center_x: x + width/2
        readonly property int st_button_center_y: y + height/2

        st_button_mode: false
        st_text: theVehicle.model_name
        st_current_color: interface_console.connection_status_description[1]
    }

    MltButton{
        id: i_device_hw_button
        x: composition_side_crop
        y: (heigth_grid_sz / 2) * 9.5
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        readonly property int st_button_center_x: x + width/2
        readonly property int st_button_center_y: y + height/2

        st_button_mode: false
        st_text: versionManager.hardware_device_model_name
        st_current_color: interface_console.isConnected ? i_device_hw_button.st_Y_color : interface_console.connection_status_description[1]
    }

    MltButton{
        id: i_username_button
        x: root.width - width - composition_side_crop
        y: (heigth_grid_sz / 2)* 9.5
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt
        readonly property int st_button_center_x: x + width/2
        readonly property int st_button_center_y: y + height/2

        st_button_mode: false
        st_text: CoreImport.current_user
    }

    readonly property int st_compostition_center_x: (i_update_button.st_button_center_x + i_vehicle_model_status_button.st_button_center_x) / 2
    readonly property int st_compostition_center_y: (i_update_button.st_button_center_y + i_device_hw_button.st_button_center_y) / 2
    readonly property int st_distance_from_UpBtm_to_LwrTop: ((i_device_hw_button.y - i_device_hw_button.height ) - i_update_button.y )

    CentralButton{
        id: i_connect_button
        x: st_compostition_center_x - (st_size/2)
        y: st_compostition_center_y - (st_size/2)
        st_size: st_distance_from_UpBtm_to_LwrTop  < i_username_button.width * 2.5 ? st_distance_from_UpBtm_to_LwrTop : i_username_button.width * 2.5

        st_text: interface_console.connection_status_description[0] === "Connected" ? "Disconnect" : "Connect"
        st_current_color: interface_console.connection_status_description[1]

        function cmd(){
            if(cmd_manager.connect_switch())
               // if(!versionManager.isDeviceInfoAppended){
                    versionManager.printDeviceVersions();
               //     versionManager.isDeviceInfoAppended = true;}
        }
    }
    readonly property int st_button_right_x: root.width - i_username_button.x - i_username_button.width

    Rectangle{
        id: i_achtung
        y: (i_device_hw_button.y + i_device_hw_button.height)
        width: root.width * st_side_crop
        height: st_initial_item_height
        anchors.horizontalCenter: root.horizontalCenter
        visible: versionManager.isCriticalAlert
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




    BaseTextField{
        id: i_textfield
        y: (i_achtung.y + i_achtung.height/* + vertical_gap*/)
        height: freeMainframeSpace - y
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        st_text: interface_console.cached_cdc_string

        Connections {
            target: interface_console
            function onCdc_new_string (){
                i_textfield.slide_cursor_position();
            }
        }
    }


}



