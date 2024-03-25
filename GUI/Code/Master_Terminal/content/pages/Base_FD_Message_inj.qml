import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "BaseItems";
import "SimpleItems";

Base {
    id: root

    /********* size settings ********/
    property real buttons_width_mlt: 3.5
    property int width_grid_sz: width*st_side_crop / 10
    property int composition_side_crop: (width - (width * st_side_crop))/2
    property int vertical_gap: height/20
    /********* colors settings ********/

    /********* values ********/
    property bool can1_selected: true
    property bool can2_selected: false


    /********* alias ********/

    /********* translated ********/
    property string st_send_anno: qsTr("Send ");
    property string st_can1_anno: qsTr("CAN 1");
    property string st_can2_anno: qsTr("CAN 2");

    function retranslateUi(){
        st_send_anno = qsTr("Send ");
        st_can1_anno = qsTr("CAN 1");
        st_can2_anno = qsTr("CAN 2");
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

    property int hor_space: width - (composition_side_crop*2)
    property int hor_item_gap: composition_side_crop
    property int hor_space_step: (hor_space/4)
    property int hor_item_width: hor_space_step - composition_side_crop

    MltButton{
        id: i_send_button
        x: root.hor_item_gap + (root.hor_space_step*0)
        width: hor_item_width

        y: vertical_gap/4
        height: st_initial_item_height
        st_button_mode: true

        st_text: st_send_anno
        st_normal_color: st_O_color
        function cmd(){
            root.forceActiveFocus();    
            if(can1_selected){
                cmd_manager.fdcan_send_single_msg(0);
            }
            if(can2_selected){
               cmd_manager.fdcan_send_single_msg(1);
            }
        }
    }

    MltButton{
        id: i_can1_button
        x: root.hor_item_gap + (root.hor_space_step*2)
        width: hor_item_width

        y: i_send_button.y
        height: st_initial_item_height

        st_button_mode: true
        st_text: st_can1_anno
        st_normal_color: can1_selected ? st_G_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            can1_selected = !can1_selected;
        }
    }
    MltButton{
        id: i_can2_button
        x: root.hor_item_gap + (root.hor_space_step*3)
        width: hor_item_width

        y: i_send_button.y
        height: st_initial_item_height

        st_button_mode: true
        st_text: st_can2_anno
        st_normal_color: can2_selected ? st_G_color : st_N_color
        function cmd(){
            root.forceActiveFocus();
            can2_selected = !can2_selected;
        }
    }

    Flickable {
        id: i_flickable
        width: root.width
        y: i_can2_button.y + i_can2_button.height + (vertical_gap/4)
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
            x: 0
            width: root.width
            height: i_inj_data_id.height
            sourceComponent: i_inj_data_id
            onLoaded: function(){
            }
        }
    }

    Connections {
        target: i_content_loader.item
        function onSendHeight(msg) {
            i_content_loader.height = msg;
        }
    }

    Component {
        id: i_inj_data_id
        Component_Base_FD_Message_inj_data{
            width: i_content_loader.width
            height: i_content_loader.height
            Component.onCompleted: {
            }
        }
    }
}
