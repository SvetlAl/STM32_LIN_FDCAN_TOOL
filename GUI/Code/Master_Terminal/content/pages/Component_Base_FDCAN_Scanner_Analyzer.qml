import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "BaseItems";
import "SimpleItems";

Rectangle {
    /********* size settings ********/
    property real buttons_width_mlt: 2.2
    property int parentHeight
    property int st_initial_item_height: CoreImport._Base_Height_Item*1.2
    property int buttonX_gap: composition_side_crop
    property int width_grid_sz: (width * st_side_crop) / 10
    property int composition_side_crop: (width - (width * st_side_crop))/2
    property int vertical_gap: (parentHeight/20)/4 > 20 ? (parentHeight/20)/4 : 20

    /********* colors settings ********/
    property string st_font_color: CoreImport._Base_Color_BaseFont
    property string st_font_color2: "#FFCC22"
    property string st_theme_color: CoreImport._GeneralDesign_Color_ToolBar
    property string st_background_color: Qt.lighter(st_theme_color, 1.2) // Base_Background_color
    property real st_gradient_positionA: CoreImport._Base_Gradient_PositionA
    property real st_gradient_positionB: CoreImport._Base_Gradient_PositionB
    color: "transparent"

    /********* values ********/
    property int start_del_id: 0
    property int end_del_id: 536870911

    function set_del_id_range(val, start){
        if(start) start_del_id = val;
        else end_del_id = val;
        if(start)i_del_id_start._value = "0x" + start_del_id.toString(16).padStart(8, "0");
        else i_del_id_end._value = "0x" + end_del_id.toString(16).padStart(8, "0");
    }
    function refresh_del_id_range(){
        i_del_id_start._value = "0x" + start_del_id.toString(16).padStart(8, "0");
        i_del_id_end._value = "0x" + end_del_id.toString(16).padStart(8, "0");
    }

    property int conversion_id: 0
    function set_conversion_id(val){
        conversion_id = val;
        i_conversion_id._value = "0x" + conversion_id.toString(16).padStart(8, "0");
    }
    function refresh_conversion_id(){
        i_conversion_id._value = "0x" + conversion_id.toString(16).padStart(8, "0");
    }

    id: root
    width: parent.width
    height: parent.height

    property string st_crop_time_anno: qsTr("CropTime");
    property string st_crop_time_expl_anno: qsTr("Recalculate timestamps start from 0");
    property string st_file_anno: qsTr("File");
    property string st_save_anno: qsTr("Save");
    property string st_load_anno: qsTr("Load");
    property string st_filename_trace_main_anno: qsTr("Filename trace Main");
    property string st_filename_trace_aux_anno: qsTr("Filename trace Aux");
    property string st_crop_id_range_anno: qsTr("Crop ID range");
    property string st_crop_time_range_anno: qsTr("Crop Time range");

    property string st_crop_range_expl_anno: qsTr("Delete all ID's within the range");
    property string st_add_delete_selected_anno: qsTr("Add/Delete selected items");
    property string st_add_anno: qsTr("Add");
    property string st_delete_anno: qsTr("Delete");
    property string st_clear_anno: qsTr("Clear all");
    property string st_id_conversion_anno: qsTr("Change multiple messages with selected ID");
    property string st_id_conversion_set_can1_anno: qsTr("Set CAN1");
    property string st_id_conversion_set_can2_anno: qsTr("Set CAN2");
    property string st_delete_others_anno: qsTr("Delete other than");


    function retranslateUi(){
        st_crop_time_anno = qsTr("CropTime");
        st_crop_time_expl_anno = qsTr("Recalculate timestamps start from 0");
        st_file_anno = qsTr("File");
        st_save_anno = qsTr("Save");
        st_load_anno = qsTr("Load");
        st_filename_trace_main_anno = qsTr("Filename trace Main");
        st_filename_trace_aux_anno = qsTr("Filename trace Aux");
        st_crop_id_range_anno = qsTr("Crop ID range");
        st_crop_time_range_anno = qsTr("Crop Time range");

        st_crop_range_expl_anno = qsTr("Delete all ID's within the range");
        st_add_delete_selected_anno = qsTr("Add/Delete selected items");
        st_add_anno = qsTr("Add");
        st_delete_anno = qsTr("Delete");
        st_clear_anno = qsTr("Clear all");
        st_id_conversion_anno = qsTr("Change multiple messages with selected ID");
        st_id_conversion_set_can1_anno = qsTr("Set CAN1");
        st_id_conversion_set_can2_anno = qsTr("Set CAN2");
        st_delete_others_anno = qsTr("Delete other than");
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
    onHeightChanged: {
        calculateHeight();
    }

    Connections {
        target: qmlTranslator  /* registered in root context */
        function onLanguageChanged(){
            retranslateUi();
        }
    }

    Component.onCompleted: {
        calculateHeight();
        root.forceActiveFocus();
        retranslateUi();
    }


    BaseTableView_FDCAN_Trace{
        id: i_trace_table
        y: vertical_gap/4
        height: st_initial_item_height*12
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        /*
        st_editable: true
        st_checkable: true
        st_sortable: true
        st_2can_trace_mode: true
*/

        model: bus_manager.FdCanBusTraceModel /* MODEL */
        columnWidths : i_trace_table.width < 39*i_trace_table.st_font_sz?
                           [
                               2*st_font_sz, // IsSelected 0
                               7*st_font_sz, // Time       1
                               3*st_font_sz, // ESI        2
                               3*st_font_sz, // FDF        3
                               3*st_font_sz, // BRS        4
                               4*st_font_sz, // CAN        5
                               3*st_font_sz, // XTD        6
                               6*st_font_sz, // ID         7
                               4*st_font_sz, // DLC        8
                               46*st_font_sz] : //         9:
                           [
                               2*st_font_sz, // IsSelected 0
                               7*st_font_sz, // Time       1
                               3*st_font_sz, // ESI        2
                               3*st_font_sz, // FDF        3
                               3*st_font_sz, // BRS        4
                               4*st_font_sz, // CAN        5
                               3*st_font_sz, // XTD        6
                               6*st_font_sz, // ID         7
                               4*st_font_sz, // DLC        8
                               46*st_font_sz]


        function sortColumn(column) {
            bus_manager.fd_switchSortTraceColumn(column);
        }
    }

    RoundedTextInput{
        id: i_filename_main
        x: composition_side_crop
        y: i_trace_table.y + i_trace_table.height + vertical_gap
        //height: file_operation ? i_filename.st_height_total : 0
        width: (root.width * st_side_crop)/2
        _anno: st_filename_trace_main_anno
        _enabled: true
        _value: "trace.fdtrc"
        function update_initial_value(){
            _value = a_txt_input.text;
        }
    }

    MltButton{
        id: i_save_button
        x: i_filename_main.x + i_filename_main.width + buttonX_gap
        //y: i_monitor_trace_button.y
        anchors.bottom: i_filename_main.bottom
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt

        st_button_mode: true
        st_text: st_save_anno
        st_normal_color: st_R_color
        function cmd(){
            root.forceActiveFocus();
            bus_manager.fd_saveTrace(i_filename_main._value);
        }
    }
    MltButton{
        id: i_load_button
        x: root.width - width - composition_side_crop
        //y: i_monitor_trace_button.y
        anchors.bottom: i_filename_main.bottom
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt

        st_button_mode: true
        st_text: st_load_anno
        st_normal_color: st_B_color
        function cmd(){
            root.forceActiveFocus();
            bus_manager.fd_loadTrace(i_filename_main._value);
        }
    }

    RoundedTextInput{
        id: i_filename_aux
        x: composition_side_crop
        y: i_filename_main.y + i_filename_main.height + vertical_gap
        //height: file_operation ? i_filename.st_height_total : 0
        width: (root.width * st_side_crop)/2
        _anno: st_filename_trace_aux_anno
        _enabled: true
        _value: "trace.fdtrc"
        function update_initial_value(){
            _value = a_txt_input.text;
        }
    }

    RoundedTextInput{
        id: i_aux_trace_size
        x: i_save_button.x
        y: i_filename_aux.y
        width: width_grid_sz * buttons_width_mlt
        _anno: "Items "
        _enabled: false
        st_clr_text: bus_manager.fd_aux_trace_size === 0 ? CoreImport._SimpleItems_Color_FrameDisabled : "#FFFF33"
        _value: bus_manager.fd_aux_trace_size
    }


    MltButton{
        id: i_load_button_aux
        x: root.width - width - composition_side_crop
        //y: i_monitor_trace_button.y
        anchors.bottom: i_filename_aux.bottom
        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt

        st_button_mode: true
        st_text: st_load_anno
        st_normal_color: st_B_color
        function cmd(){
            root.forceActiveFocus();
            bus_manager.fd_loadAuxTrace(i_filename_aux._value);
        }
    }


    Rectangle{
        id: i_crop_time_section
        y: i_filename_aux.y + i_filename_aux.height + vertical_gap
        anchors.horizontalCenter: root.horizontalCenter
        height: st_initial_item_height*2
        width: root.width * st_side_crop
        color: "transparent"
        border.color: st_font_color
        radius: 20

        Text{
            id: i_crop_time_label
            y: 0
            x: i_crop_time_section.radius
            width: i_crop_time_section.width
            //height: st_initial_item_height
            color: st_font_color
            text: st_crop_time_expl_anno
            font.pixelSize: st_initial_item_height/2
        }
        MltButton{
            id: i_crop_time_button
            x: i_crop_time_section.radius/2
            y: i_crop_time_label.y + i_crop_time_label.height
            height: st_initial_item_height
            width: width_grid_sz * buttons_width_mlt

            st_button_mode: true
            st_text: st_crop_time_anno
            st_normal_color: st_Y_color
            function cmd(){
                root.forceActiveFocus();
                bus_manager.fd_cropTime();
            }
        }
    }

    //========================================================================
    //==================== i_crop_range_section ==============================
    //========================================================================
    Rectangle{
        id: i_crop_range_section
        y: i_crop_time_section.y + i_crop_time_section.height + vertical_gap*2
        anchors.horizontalCenter: root.horizontalCenter
        height: st_initial_item_height*3
        width: root.width * st_side_crop
        color: "transparent"
        border.color: st_font_color
        radius: 20

        Text{
            id: i_crop_range_label
            y: 0
            x: i_crop_range_section.radius
            width: i_crop_range_section.width
            //height: st_initial_item_height
            color: st_font_color
            text: st_crop_range_expl_anno
            font.pixelSize: st_initial_item_height/2
        }

        RoundedTextInput{
            id: i_del_id_start
            x: i_crop_range_section.radius/2
            y: i_crop_range_label.y + i_crop_range_label.height
            width: i_crop_range_section.width/3 - composition_side_crop
            _anno: "start id "
            _enabled: true
            _value: "0x00000000"
            a_txt_input.font.capitalization: Font.AllUppercase
            function update_initial_value(){
                var _intvalue = a_txt_input.text
                // Convert hex string to integer
                var _start_id = parseInt(_intvalue, 16);
                if(start_del_id !== _start_id)
                    set_del_id_range(_start_id, true);
                else refresh_del_id_range();
            }
        }


        RoundedTextInput{
            id: i_del_id_end
            x: i_del_id_start.x + i_del_id_start.width + composition_side_crop
            y: i_del_id_start.y
            width: i_crop_range_section.width/3 - composition_side_crop
            _anno: "end id "
            _enabled: true
            _value: "0x1FFFFFFF"
            a_txt_input.font.capitalization: Font.AllUppercase
            function update_initial_value(){
                var _intvalue = a_txt_input.text
                // Convert hex string to integer
                var _end_id = parseInt(_intvalue, 16);
                if(end_del_id !== _end_id)
                    set_del_id_range(_end_id, false);
                else refresh_del_id_range();
            }
        }

        MltButton{
            id: i_del_id_range_button
            x: i_del_id_end.x + i_del_id_end.width + composition_side_crop
            height: st_initial_item_height
            width: i_crop_range_section.width/3 - composition_side_crop
            anchors.bottom: i_del_id_start.bottom

            st_button_mode: true
            st_text: st_crop_id_range_anno
            st_normal_color: st_R_color
            function cmd(){
                root.forceActiveFocus();
                bus_manager.fd_deleteRangeTrace(start_del_id, end_del_id);
            }
        }

        RoundedTextInput{
            id: i_del_time_start
            x: i_del_id_start.x
            y: i_del_id_start.y + i_del_id_start.height + vertical_gap/2
            width: i_del_id_start.width
            _anno: "start time "
            _enabled: true
            _value: "0.0000"
            a_txt_input.font.capitalization: Font.AllUppercase
            function update_initial_value(){
                _value = a_txt_input.text
            }
        }


        RoundedTextInput{
            id: i_del_time_end
            x: i_del_id_end.x
            y: i_del_time_start.y
            width: i_del_id_end.width
            _anno: "end time "
            _enabled: true
            _value: "0.0000"
            a_txt_input.font.capitalization: Font.AllUppercase
            function update_initial_value(){
               _value = a_txt_input.text
            }
        }

        MltButton{
            id: i_del_time_range_button
            x: i_del_id_range_button.x
            height: st_initial_item_height
            width: i_del_id_range_button.width
            anchors.bottom: i_del_time_start.bottom

            st_button_mode: true
            st_text: st_crop_time_range_anno
            st_normal_color: st_R_color
            function cmd(){
                root.forceActiveFocus();
                bus_manager.fd_deleteTimeRangeTrace(i_del_time_start._value, i_del_time_end._value)
            }
        }
    }
    //************************************************************************
    //******************** i_crop_range_section ******************************
    //************************************************************************


    Rectangle{
        id: i_add_delete_section
        y: i_crop_range_section.y + i_crop_range_section.height + vertical_gap
        anchors.horizontalCenter: root.horizontalCenter
        height: st_initial_item_height*2
        width: root.width * st_side_crop
        color: "transparent"
        border.color: st_font_color
        radius: 20

        Text{
            id: i_add_delete_label
            y: 0
            x: i_add_delete_section.radius
            width: i_add_delete_section.width
            //height: st_initial_item_height
            color: st_font_color
            text: st_add_delete_selected_anno
            font.pixelSize: st_initial_item_height/2
        }

        MltButton{
            id: i_add_button
            x: i_add_delete_section.radius/2
            y: i_add_delete_label.y + i_add_delete_label.height

            height: st_initial_item_height
            width: width_grid_sz * buttons_width_mlt

            st_button_mode: true
            st_text: st_add_anno
            st_normal_color: st_G_color

            function cmd(){
                root.forceActiveFocus();
                bus_manager.fd_createNewTraceItem("", true);
            }
        }

        MltButton{
            id: i_delete_button
            x: i_add_button.x + i_add_button.width + buttonX_gap
            y: i_add_button.y
            height: st_initial_item_height
            width: width_grid_sz * buttons_width_mlt
            st_button_mode: true

            st_text: st_delete_anno
            st_normal_color: st_R_color
            function cmd(){
                root.forceActiveFocus();
                bus_manager.fd_deleteSelectedTrace();
            }
        }

        MltButton{
            id: i_clear_button
            x: i_delete_button.x + i_delete_button.width + buttonX_gap
            y: i_add_button.y
            height: st_initial_item_height
            width: width_grid_sz * buttons_width_mlt

            st_button_mode: true
            st_text: st_clear_anno
            st_normal_color: st_R_color
            function cmd(){
                root.forceActiveFocus();
                bus_manager.fd_resetCanBusTraceModel();
               // bus_manager.clearSortTrace();
            }
        }
    }

    Rectangle{
        id: i_id_conversion_section
        y: i_add_delete_section.y + i_add_delete_section.height + vertical_gap
        anchors.horizontalCenter: root.horizontalCenter
        height: st_initial_item_height*3
        width: root.width * st_side_crop
        color: "transparent"
        border.color: st_font_color
        radius: 20

        Text{
            id: i_id_conversion_label
            y: 0
            x: i_id_conversion_section.radius
            width: i_id_conversion_section.width
            //height: st_initial_item_height
            color: st_font_color
            text: st_id_conversion_anno
            font.pixelSize: st_initial_item_height/2
        }

        RoundedTextInput{
            id: i_conversion_id
            x: i_id_conversion_section.radius/2
            y: i_id_conversion_label.y + i_id_conversion_label.height
            width: i_id_conversion_section.width/3 - composition_side_crop
            _anno: "Conversion id"
            _enabled: true
            _value: "0x00000000"
            a_txt_input.font.capitalization: Font.AllUppercase
            function update_initial_value(){
                var _intvalue = a_txt_input.text
                // Convert hex string to integer
                var _id = parseInt(_intvalue, 16);
                if(end_del_id !== _id)
                    set_conversion_id(_id);
                else refresh_conversion_id();
            }
        }

        MltButton{
            id: i_conversion_set_can1_button
            x: i_conversion_id.x + i_conversion_id.width + composition_side_crop
            anchors.bottom: i_conversion_id.bottom

            height: st_initial_item_height
            width: i_id_conversion_section.width/3 - composition_side_crop

            st_button_mode: true
            st_text: st_id_conversion_set_can1_anno
            st_normal_color: st_Y_color
            function cmd(){
                root.forceActiveFocus();
                bus_manager.fd_setTraceIdDirection(conversion_id, 1);
            }
        }

        MltButton{
            id: i_conversion_set_can2_button
            x: i_conversion_set_can1_button.x + i_conversion_set_can1_button.width + composition_side_crop
            anchors.bottom: i_conversion_id.bottom

            height: st_initial_item_height
            width: i_id_conversion_section.width/3 - composition_side_crop

            st_button_mode: true
            st_text: st_id_conversion_set_can2_anno
            st_normal_color: st_Y_color
            function cmd(){
                root.forceActiveFocus();
                bus_manager.fd_setTraceIdDirection(conversion_id, 2);
            }
        }



        MltButton{
            id: i_conversion_delete_button
            y: i_conversion_id.y + i_conversion_id.height + vertical_gap/2
            x: i_conversion_id.x

            height: st_initial_item_height
            width: i_id_conversion_section.width/3 - composition_side_crop

            st_button_mode: true
            st_text: st_delete_anno
            st_normal_color: st_R_color

            function cmd(){
                root.forceActiveFocus();
                bus_manager.fd_deleteRangeTrace(conversion_id, conversion_id);
            }
        }

        MltButton{
            id: i_conversion_delete_other_button
            x: i_conversion_set_can1_button.x
            anchors.bottom: i_conversion_delete_button.bottom

            height: st_initial_item_height
            width: i_id_conversion_section.width/3 - composition_side_crop

            st_button_mode: true
            st_text: st_delete_others_anno
            st_normal_color: st_Y_color
            function cmd(){
                root.forceActiveFocus();
                bus_manager.fd_deleteRangeTrace(0, (conversion_id - 1));
                bus_manager.fd_deleteRangeTrace((conversion_id + 1), 536870911);
            }
        }

    }


}



