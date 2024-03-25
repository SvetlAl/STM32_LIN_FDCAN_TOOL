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
    property string st_override_inj_anno: qsTr("Override injection");
    property string st_discard_ids_anno: qsTr("Discard Id's");
    property string st_ovrd_filters_anno: qsTr("Override filters");

    function retranslateUi(){
        st_override_inj_anno = qsTr("Override injection");
        st_discard_ids_anno = qsTr("Discard Id's");
        st_ovrd_filters_anno = qsTr("Override filters");
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

    function setLoaderItem(page){
        switch(page){
        case 0:
            i_content_loader.sourceComponent = i_injection_ovr;
            break;
        case 1:
            i_content_loader.sourceComponent = i_discard_id;
            break;
        case 2:
            i_content_loader.sourceComponent = i_ovr_ids;
            break;
        }

    }

    id: root
    width: parent.width
    height: parent.height

    MltButton{
        id: i_override_inj_button
        x: composition_side_crop
        y: heigth_grid_sz / 2
        height: st_initial_item_height
        width: width_grid_sz * 3

        st_button_mode: true
        st_text: st_override_inj_anno
        st_normal_color: i_content_loader.sourceComponent === i_injection_ovr ? st_G_color : st_N_color

        function cmd(){
            root.forceActiveFocus();
            setLoaderItem(0);
        }
    }

    MltButton{
        id: i_discard_ids_button
        //x: composition_side_crop
        anchors.horizontalCenter: parent.horizontalCenter
        y: heigth_grid_sz / 2
        height: st_initial_item_height
        width: width_grid_sz * 3

        st_button_mode: true
        st_text: st_discard_ids_anno
        st_normal_color: i_content_loader.sourceComponent === i_discard_id ? st_G_color : st_N_color

        function cmd(){
            root.forceActiveFocus();
            setLoaderItem(1);
        }
    }



    MltButton{
        id: i_ovrd_filters_button
        x: root.width - width - composition_side_crop
        y: heigth_grid_sz / 2
        height: st_initial_item_height
        width: width_grid_sz * 3

        st_button_mode: true
        st_text: st_ovrd_filters_anno
        st_normal_color: i_content_loader.sourceComponent === i_ovr_ids ? st_G_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            setLoaderItem(2);
        }
    }



    Flickable {
        id: i_flickable
        width: root.width
        y: (i_override_inj_button.y + i_override_inj_button.height + vertical_gap)
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
            x: i_override_inj_button.x
            width: root.width - (composition_side_crop*2)
            height: i_injection_ovr.height
            sourceComponent: i_injection_ovr
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
            id: i_discard_id
            Component_Base_CAN_Override_discard_id{
                width: i_content_loader.width
                height: i_content_loader.height
                //i_content_loader.widthh
                Component.onCompleted: {
                }
            }
        }

        Component {
            id: i_injection_ovr
            Component_Base_CAN_Override_injection_ovr{
                width: i_content_loader.width
                height: i_content_loader.height
                //i_content_loader.widthh
                Component.onCompleted: {
                }
            }
        }

        Component {
            id: i_ovr_ids
            Component_Base_CAN_Override_ovr_ids{
                width: i_content_loader.width
                height: i_content_loader.height
                //i_content_loader.widthh
                Component.onCompleted: {
                }
            }
        }



}
