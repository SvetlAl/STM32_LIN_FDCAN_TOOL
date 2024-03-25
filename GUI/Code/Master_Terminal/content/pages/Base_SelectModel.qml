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

    readonly property int default_vehicle_code: 0xFFFF
    property string selected_vehicle_model: theVehicle.model_name
    property int selected_vehicle_code: default_vehicle_code
    /********* alias ********/
    property string st_select_anno: qsTr("Select");

    function retranslateUi(){
        st_select_anno: qsTr("Select");
    }

    Connections {
        target: qmlTranslator  /* registered in root context */
        function onLanguageChanged(){
            retranslateUi();
        }
    }

    Component.onCompleted: {
      //  cmd_manager.init_vehicleNames_Model();
        retranslateUi();
    }
    Component.onDestruction: {
      //  cmd_manager.reset_vehicleNames_Model();
    }



    id: root
    width: parent.width
    height: parent.height


    MltButton{
        id: i_selected_model_label
        x: composition_side_crop
        y: heigth_grid_sz / 2
        height: st_initial_item_height
        width: width_grid_sz * 6

        st_button_mode: false
        st_text: selected_vehicle_model
        st_normal_color: st_Y_color
    }
    MltButton{
        id: i_select_button
        x: root.width - width - composition_side_crop
        y: heigth_grid_sz / 2
        height: st_initial_item_height
        width: width_grid_sz * 3

        st_button_mode: true
        st_text: st_select_anno
        st_normal_color: st_G_color
        function cmd(){            
            if((cmd_manager.isConnected) & (selected_vehicle_code != default_vehicle_code)){
                var operation_result = cmd_manager.setAndSaveVehicleModel(selected_vehicle_code);
                if(operation_result === true){
                    selected_vehicle_model = theVehicle.model_name;
                }
            }
        }
    }



    Flickable {
        id: i_flickable
        width: root.width
        y: (i_selected_model_label.y + i_selected_model_label.height + vertical_gap)
        height: freeMainframeSpace - y
        contentHeight: i_content_loader.height
        clip: true
        flickDeceleration  : 1500.00
        maximumFlickVelocity : 1500.00
        ScrollBar.vertical:
            ScrollBar {
                policy: ScrollBar.AlwaysOn
        }


            Loader {
                id: i_content_loader
                y: 0
                x: i_selected_model_label.x
                width: root.width - (composition_side_crop*2)
                height: i_content_ModelList.height
                sourceComponent: i_content_ModelList
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

        Connections {
            target: i_content_loader.item
            function onModelSelected(_modelname, _modelvalue) {
                //selected_vehicle_model = _modelname
                selected_vehicle_code = _modelvalue
            }
        }

        Component {
            id: i_content_ModelList
            Component_Base_SelectModel_Modellist{
                width: i_content_loader.width
                height: i_content_loader.height
                //i_content_loader.widthh
                Component.onCompleted: {
                }
            }
        }





}



