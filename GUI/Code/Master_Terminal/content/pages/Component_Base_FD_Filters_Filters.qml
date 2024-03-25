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
    property string st_id_rect_anno: qsTr("ID and direction");
    property string st_can1_to_can2_anno: qsTr("CAN1>>CAN2");
    property string st_can2_to_can1_anno: qsTr("CAN2>>CAN1");
    property string st_FDCAN_ID_begin_anno: qsTr("FDCAN ID start ");
    property string st_FDCAN_ID_end_anno: qsTr("FDCAN ID end ");
    property string st_FDCAN_range_anno: qsTr("use ID range");


    function retranslateUi(){
        st_id_rect_anno = qsTr("ID and direction");
        st_can1_to_can2_anno = qsTr("CAN1>>CAN2");
        st_can2_to_can1_anno = qsTr("CAN2>>CAN1");
        st_FDCAN_ID_begin_anno = qsTr("FDCAN ID start ");
        st_FDCAN_ID_end_anno = qsTr("FDCAN ID end ");
        st_FDCAN_range_anno = qsTr("use ID range");
    }

    /********* alias ********/

    id: root
    color: "transparent"

    Component.onCompleted: {
        calculateHeight();
    }
    Component.onDestruction: {
    }

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

    Rectangle{
        id: i_fdcan_id_section
        y: 0// vertical_gap
        x: 0
        height: i_can2_button.y + i_can2_button.height + (vertical_gap/2)
        width: root.width // * st_side_crop
        color: "transparent"
        border.color: st_font_color
        radius: 20

        property int hor_space: width - (radius*2)
        property int hor_item_gap: radius
        property int hor_space_step: (hor_space/4)
        property int hor_item_width: hor_space_step - radius/2

        Text{
            id: i_fdcan_id_label
            y: 0
            x: i_fdcan_id_section.radius
            width: i_fdcan_id_section.width
            color: st_font_color
            text: st_id_rect_anno
            font.pixelSize: st_initial_item_height/2
        }

        //============= Id begin  ===============

        RoundedTextInput{
            id: i_idvalue_begin_ti
            x: i_fdcan_id_section.hor_item_gap + (i_fdcan_id_section.hor_space_step*0)
            width: i_fdcan_id_section.hor_item_width*2
            y: i_fdcan_id_label.y + i_fdcan_id_label.height + vertical_gap/4

            _anno: st_FDCAN_ID_begin_anno
            _enabled: true
            _value: device_manager.FdcanOverrideFilterModel.id_begin
            function update_initial_value(){
                var hexRegExp = /^(0x)?[0-9A-Fa-f]+$/;
                if(!hexRegExp.test(a_txt_input.text)){
                    a_txt_input.text = device_manager.FdcanOverrideFilterModel.id_begin;
                    return;
                }

                if (!a_txt_input.text.startsWith("0x")) {
                    a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                }

                if (parseInt(a_txt_input.text, 16) >= 1 && parseInt(a_txt_input.text, 16) <= 0x1FFFFFFF) {
                    if(device_manager.FdcanOverrideFilterModel.id_begin !== a_txt_input.text)changes_commited = true;
                }
                else {
                    a_txt_input.text = device_manager.FdcanOverrideFilterModel.id_begin;
                    console.log("Error: DLC out of range for extended frame");
                }

                a_txt_input.text = a_txt_input.text;
                device_manager.FdcanOverrideFilterModel.id_begin = a_txt_input.text;

            }

        }
        //============= use range  ===============
        MltButton{
            id: i_userange_button
            x: i_fdcan_id_section.hor_item_gap + (i_fdcan_id_section.hor_space_step*2)
            width: i_fdcan_id_section.hor_item_width

            y: i_idvalue_begin_ti.y
            height: st_initial_item_height

            st_button_mode: true
            st_text: st_FDCAN_range_anno
            st_normal_color: device_manager.FdcanOverrideFilterModel.range_used ? st_Y_color : st_N_color
            function cmd(){
                root.forceActiveFocus();
                device_manager.FdcanOverrideFilterModel.range_used = !device_manager.FdcanOverrideFilterModel.range_used;
                changes_commited = true;
            }
        }

        //============= CAN 1  ===============
        MltButton{
            id: i_can1_button
            x: i_fdcan_id_section.hor_item_gap + (i_fdcan_id_section.hor_space_step*3)
            width: i_fdcan_id_section.hor_item_width

            y: i_idvalue_begin_ti.y
            height: st_initial_item_height

            st_button_mode: true
            st_text: st_can1_to_can2_anno
            st_normal_color: device_manager.FdcanOverrideFilterModel.can1tocan2_dir ? st_G_color : st_N_color
            function cmd(){
                root.forceActiveFocus();
                device_manager.FdcanOverrideFilterModel.can1tocan2_dir = !device_manager.FdcanOverrideFilterModel.can1tocan2_dir;
                changes_commited = true;
            }
        }

        //============= Id end  ===============

        RoundedTextInput{
            id: i_idvalue_end_ti
            x: i_idvalue_begin_ti.x
            width: i_idvalue_begin_ti.width
            y: i_idvalue_begin_ti.y + i_idvalue_begin_ti.height + vertical_gap/4

            _anno: st_FDCAN_ID_end_anno
            _enabled: device_manager.FdcanOverrideFilterModel.range_used
            _value: device_manager.FdcanOverrideFilterModel.range_used ? device_manager.FdcanOverrideFilterModel.id_end : device_manager.FdcanOverrideFilterModel.id_begin
            function update_initial_value(){
                var hexRegExp = /^(0x)?[0-9A-Fa-f]+$/;
                if(!hexRegExp.test(a_txt_input.text)){
                    a_txt_input.text = device_manager.FdcanOverrideFilterModel.id_end;
                    return;
                }

                if (!a_txt_input.text.startsWith("0x")) {
                    a_txt_input.text = "0x" + a_txt_input.text.toLocaleUpperCase();
                }

                if (parseInt(a_txt_input.text, 16) >= 1 && parseInt(a_txt_input.text, 16) <= 0x1FFFFFFF) {
                    if(device_manager.FdcanOverrideFilterModel.id_end !== a_txt_input.text)changes_commited = true;
                }
                else {
                    a_txt_input.text = device_manager.FdcanOverrideFilterModel.id_end;
                    console.log("Error: DLC out of range for extended frame");
                }

                a_txt_input.text = a_txt_input.text;
                device_manager.FdcanOverrideFilterModel.id_end = a_txt_input.text;

            }
        }

            //============= CAN 2  ===============
            MltButton{
                id: i_can2_button
                x: i_fdcan_id_section.hor_item_gap + (i_fdcan_id_section.hor_space_step*3)
                width: i_fdcan_id_section.hor_item_width

                y: i_idvalue_end_ti.y
                height: st_initial_item_height

                st_button_mode: true
                st_text: st_can2_to_can1_anno
                st_normal_color: device_manager.FdcanOverrideFilterModel.can2tocan1_dir ? st_G_color : st_N_color
                function cmd(){
                    root.forceActiveFocus();
                    device_manager.FdcanOverrideFilterModel.can2tocan1_dir = !device_manager.FdcanOverrideFilterModel.can2tocan1_dir;
                    changes_commited = true;
                }
            }


    } // rect


    ListView  {
        id: listView
        parent: root
        anchors.top: i_fdcan_id_section.bottom
        anchors.topMargin: 20
        height: freeMainframeSpace - y - st_item_height*2.2

        //height: device_manager.FdcanOverrideFilterModel.length * st_item_height + st_item_height
        width: root.width
        boundsBehavior: Flickable.DragOverBounds
        clip: true
        cacheBuffer: 2

        ScrollBar.vertical:
            ScrollBar {
            policy: ScrollBar.AlwaysOn
        }

        model: device_manager.FdcanOverrideFilterModel
        delegate:
            Rectangle{

            height: i_filter.height
            width: root.width
            color: "transparent"

            Item_FDCAN_override_filter{
                    id: i_filter
                    st_total_height: st_item_height*1.2
                    height: st_active ? (st_initial_item_height/2 + (st_initial_item_height + st_vertical_gap)*max_rows) : (st_initial_item_height/2 + (st_initial_item_height + st_vertical_gap))

                    st_number: modelData.number
                    st_active: modelData.active
                    st_method: modelData.method
                    st_b_val:  "0x" + modelData.begin_val
                    st_e_val:  "0x" + modelData.end_val
                    st_step:   "0x" + modelData.step

                    function refreshAll(){
                        modelData.active = st_active
                        modelData.method = st_method
                        modelData.begin_val = st_b_val
                        modelData.end_val = st_e_val
                        modelData.step = st_step
                        changes_commited = true
                    }
                    function edit_checked(){
                        calculateHeight();
                    }

                }
                Rectangle{
                    height: st_item_height/4
                    color: "transparent"
                }
        }

    }
}
