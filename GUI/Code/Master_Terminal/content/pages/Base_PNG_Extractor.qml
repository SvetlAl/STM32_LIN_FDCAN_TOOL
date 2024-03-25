import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "BaseItems";
import "SimpleItems";

Base {
    /********* size settings ********/

    property real buttons_width_mlt: 2

    /********* colors settings ********/

    /********* values ********/
    property int width_grid_sz: width*st_side_crop / 10
    property int composition_side_crop: (width - (width * st_side_crop))/2

    property int vertical_gap: (height/20)/4

    property int input_pos: 0
    /********* alias ********/
    property string st_filename_anno: qsTr("Target filename");
    property string st_output_dir_anno: qsTr("Output dir");
    property string st_extract_all_anno: qsTr("Extract all");
    property string st_replacement_pos_anno: qsTr("Replacement pos");
    property string st_replacement_filename_anno: qsTr("Replacement filename");
    property string st_replace_anno: qsTr("Replace");

    function retranslateUi(){
        st_filename_anno = qsTr("Target filename");
        st_output_dir_anno = qsTr("Output dir");
        st_extract_all_anno = qsTr("Extract all");
        st_replacement_pos_anno = qsTr("Replacement pos");
        st_replacement_filename_anno = qsTr("Replacement filename");
        st_replace_anno = qsTr("Replace");
    }

    Connections {
        target: qmlTranslator  /* registered in root context */
        function onLanguageChanged(){
            retranslateUi();
        }
    }

    Component.onCompleted: {
        root.forceActiveFocus();
        retranslateUi();
    }

    id: root
    width: parent.width
    height: parent.height


    RoundedTextInput{
        id: i_filename
        y: vertical_gap/4
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        _anno: st_filename_anno
        _enabled: true
        _value: png_extractor.target_filename
        function update_initial_value(){
            _value = a_txt_input.text;
            png_extractor.target_filename = _value;
        }
    }

    RoundedTextInput{
        id: i_output_dir
        y: i_filename.y + i_filename.height + vertical_gap/4
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        _anno: st_output_dir_anno
        _enabled: true
        _value: png_extractor.output_folder
        function update_initial_value(){
            _value = a_txt_input.text;
            png_extractor.output_folder = _value;
        }
    }

    MltButton{
        id: i_extract_all_button
        x: i_output_dir.x
        y: i_output_dir.y + i_output_dir.height + vertical_gap/4

        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt * 2

        st_button_mode: true
        st_text: st_extract_all_anno
        st_normal_color: st_G_color

        function cmd(){
            root.forceActiveFocus();
            png_extractor.extract_all();
        }
    }

    RoundedTextInput{
        id: i_in_replacement_pos
        y: i_extract_all_button.y + i_extract_all_button.height + vertical_gap/4
        x: i_output_dir.x
        width: ((root.width * st_side_crop)/2) - composition_side_crop
        _anno: st_replacement_pos_anno
        _enabled: true
        _value: input_pos.toString()
        a_txt_input.font.capitalization: Font.AllUppercase
        function update_initial_value(){
            _value = a_txt_input.text;
            input_pos = parseInt(_value, 10);
        }
    }

    BaseTextField{
        id: i_ds_replacement_pos
        anchors.bottom: i_in_replacement_pos.bottom
        x: root.width - width - composition_side_crop
        height: i_in_replacement_pos.height*0.8
        width: ((root.width * st_side_crop)/2) - composition_side_crop
        st_text: input_pos.toString()
        editable: false
        function cmd(){
        }
    }

    RoundedTextInput{
        id: i_replacement_filename
        y: i_in_replacement_pos.y + i_in_replacement_pos.height + vertical_gap/4
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        _anno: st_replacement_filename_anno
        _enabled: true
        _value: png_extractor.replacement_filename
        function update_initial_value(){
            _value = a_txt_input.text;
            png_extractor.replacement_filename = _value;
        }
    }

    MltButton{
        id: i_replace_button
        x: i_output_dir.x
        y: i_replacement_filename.y + i_replacement_filename.height + vertical_gap/2

        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt * 2

        st_button_mode: true
        st_text: st_replace_anno
        st_normal_color: st_G_color

        function cmd(){
            root.forceActiveFocus();
            png_extractor.make_replacement(input_pos);
        }
    }

    MltButton{
        id: i_cmp_test_button
        x: i_replace_button.x + i_replace_button.width + st_initial_item_height/8
        y: i_replace_button.y

        height: st_initial_item_height
        width: width_grid_sz * buttons_width_mlt * 2

        st_button_mode: true
        st_text: "cmpr"
        st_normal_color: st_G_color

        function cmd(){
            root.forceActiveFocus();
            png_extractor.comp_test();
        }
    }


    BaseTextField{
        id: i_textfield
        y: (i_replace_button.y + i_replace_button.height  + vertical_gap/2 )
        height: freeMainframeSpace - y
        width: root.width * st_side_crop
        anchors.horizontalCenter: root.horizontalCenter
        st_text: png_extractor.operation_result

    }

}



