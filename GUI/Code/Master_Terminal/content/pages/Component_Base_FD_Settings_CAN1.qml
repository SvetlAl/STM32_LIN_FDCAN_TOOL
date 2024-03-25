import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "BaseItems";
import "SimpleItems";

Rectangle {
    /********* alias ********/
    id: root
    color: "transparent"

    /********* size settings ********/
    property real buttons_width_mlt: 3.5
    property int width_grid_sz: width*st_side_crop / 10
    /********* colors settings ********/

    /********* values ********/

    property int composition_side_crop: (width - (width * st_side_crop))/2
    property int vertical_gap: st_initial_item_height/6

    /********* alias ********/

    /********* colors settings ********/
    property string st_font_color: CoreImport._Base_Color_BaseFont

    /********* translated ********/
    property string st_cccr_properties_anno: qsTr("CCCR register")

    property string st_ASM_anno:  qsTr("ASM ")
    property string st_DAR_anno:  qsTr("DAR ")
    property string st_FDOE_anno: qsTr("FDOE")
    property string st_BRSE_anno: qsTr("BRSE")

    property string st_PXHD_anno: qsTr("PXHD")
    property string st_EFBI_anno: qsTr("EFBI")
    property string st_TXP_anno:  qsTr("TXP")
    property string st_NISO_anno: qsTr("NISO")

    property string st_custom_btr_anno: qsTr("Bitrate configuration.")
    readonly property string calculator_link_txt: '<html><style type="text/css"></style><a href="https://phryniszak.github.io/stm32g-fdcan/"><font color=\"#DDDDDD\"> Calculator</font></a></html>'


    function retranslateUi(){
        st_cccr_properties_anno = qsTr("CCCR register");

        st_ASM_anno =   qsTr("ASM ")
        st_DAR_anno =   qsTr("DAR ")
        st_FDOE_anno =  qsTr("FDOE")
        st_BRSE_anno =  qsTr("BRSE")

        st_PXHD_anno =  qsTr("PXHD")
        st_EFBI_anno =  qsTr("EFBI")
        st_TXP_anno =   qsTr("TXP")
        st_NISO_anno =  qsTr("NISO")

        st_custom_btr_anno = qsTr("Bitrate configuration.")
    }


    Component.onCompleted: {
        calculateHeight();
    }
    Component.onDestruction: {
    }

    signal changesCommitted();
    signal sendHeight(int msg);
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
        id: i_cccr_settings_section
        y: vertical_gap
        x: composition_side_crop
        height: i_pxhd_button.y + i_pxhd_button.height + (vertical_gap)
        width: root.width * st_side_crop
        color: "transparent"
        border.color: st_font_color
        radius: 20

        property int hor_space: width - (radius*2)
        property int hor_item_gap: radius
        property int hor_space_step: (hor_space/4)
        property int hor_item_width: hor_space_step - radius

        Text{
            id: i_cccr_properties_label
            y: 0
            x: i_cccr_settings_section.radius
            width: i_cccr_settings_section.width
            color: st_font_color
            text: st_cccr_properties_anno
            font.pixelSize: st_initial_item_height/2
        }

        //============= ASM  ===============
        MltButton{
            id: i_asm_button
            x: i_cccr_settings_section.hor_item_gap + (i_cccr_settings_section.hor_space_step*0)
            width: i_cccr_settings_section.hor_item_width
            y: i_cccr_properties_label.y + i_cccr_properties_label.height + vertical_gap

            height: st_initial_item_height
            st_button_mode: true

            st_text: st_ASM_anno
            st_normal_color: device_manager.canfd1_ASM ? st_G_color : st_N_color
            function cmd(){
                root.forceActiveFocus();
                device_manager.canfd1_ASM = !device_manager.canfd1_ASM;
                changesCommitted();
            }
        }

        //============= DAR  ===============
        MltButton{
            id: i_dar_button
            y: i_asm_button.y

            x: i_cccr_settings_section.hor_item_gap + (i_cccr_settings_section.hor_space_step*1)
            width: i_cccr_settings_section.hor_item_width

            height: st_initial_item_height

            st_button_mode: true
            st_text: st_DAR_anno
            st_normal_color: device_manager.canfd1_DAR ? st_G_color : st_N_color
            function cmd(){
                root.forceActiveFocus();
                device_manager.canfd1_DAR = !device_manager.canfd1_DAR;
                changesCommitted();
            }
        }

        //============= FDOE  ===============
        MltButton{
            id: i_fdoe_button
            y: i_asm_button.y

            x: i_cccr_settings_section.hor_item_gap + (i_cccr_settings_section.hor_space_step*2)
            width: i_cccr_settings_section.hor_item_width

            height: st_initial_item_height

            st_button_mode: true
            st_text: st_FDOE_anno
            st_normal_color: device_manager.canfd1_FDOE ? st_G_color : st_N_color
            function cmd(){
                root.forceActiveFocus();
                device_manager.canfd1_FDOE = !device_manager.canfd1_FDOE;
                changesCommitted();
            }
        }

        //============= BRSE  ===============
        MltButton{
            id: i_brse_button
            y: i_asm_button.y

            x: i_cccr_settings_section.hor_item_gap + (i_cccr_settings_section.hor_space_step*3)
            width: i_cccr_settings_section.hor_item_width

            height: st_initial_item_height

            st_button_mode: true
            st_text: st_BRSE_anno
            st_normal_color: device_manager.canfd1_BRSE ? st_G_color : st_N_color
            function cmd(){
                root.forceActiveFocus();
                device_manager.canfd1_BRSE = !device_manager.canfd1_BRSE;
                changesCommitted();
            }
        }
        //============= PXHD  ===============
        MltButton{
            id: i_pxhd_button
            y: i_asm_button.y + i_asm_button.height + (vertical_gap*2)

            x: i_cccr_settings_section.hor_item_gap + (i_cccr_settings_section.hor_space_step*0)
            width: i_cccr_settings_section.hor_item_width

            height: st_initial_item_height

            st_button_mode: true
            st_text: st_PXHD_anno
            st_normal_color: device_manager.canfd1_PXHD ? st_G_color : st_N_color
            function cmd(){
                root.forceActiveFocus();
                device_manager.canfd1_PXHD = !device_manager.canfd1_PXHD;
                changesCommitted();
            }
        }
        //============= EFBI  ===============
        MltButton{
            id: i_efbi_button
            y: i_pxhd_button.y
            x: i_cccr_settings_section.hor_item_gap + (i_cccr_settings_section.hor_space_step*1)
            width: i_cccr_settings_section.hor_item_width

            height: st_initial_item_height

            st_button_mode: true
            st_text: st_EFBI_anno
            st_normal_color: device_manager.canfd1_EFBI ? st_G_color : st_N_color
            function cmd(){
                root.forceActiveFocus();
                device_manager.canfd1_EFBI = !device_manager.canfd1_EFBI;
                changesCommitted();
            }
        }
        //============= TXP  ===============
        MltButton{
            id: i_txp_button
            y: i_pxhd_button.y
            x: i_cccr_settings_section.hor_item_gap + (i_cccr_settings_section.hor_space_step*2)
            width: i_cccr_settings_section.hor_item_width

            height: st_initial_item_height

            st_button_mode: true
            st_text: st_TXP_anno
            st_normal_color: device_manager.canfd1_TXP ? st_G_color : st_N_color
            function cmd(){
                root.forceActiveFocus();
                device_manager.canfd1_TXP = !device_manager.canfd1_TXP;
                changesCommitted();
            }
        }
        //============= NISO  ===============
        MltButton{
            id: i_niso_button
            y: i_pxhd_button.y

            x: i_cccr_settings_section.hor_item_gap + (i_cccr_settings_section.hor_space_step*3)
            width: i_cccr_settings_section.hor_item_width

            height: st_initial_item_height

            st_button_mode: true
            st_text: st_NISO_anno
            st_normal_color: device_manager.canfd1_NISO ? st_G_color : st_N_color
            function cmd(){
                root.forceActiveFocus();
                device_manager.canfd1_NISO = !device_manager.canfd1_NISO;
                changesCommitted();
            }
        }
    } // rect



    Rectangle{
        id: i_custom_btr_section
        y: i_cccr_settings_section.y + i_cccr_settings_section.height + (vertical_gap/2)
        x: composition_side_crop
        height: st_initial_item_height*4 + vertical_gap
        width: root.width * st_side_crop
        color: "transparent"
        border.color: st_font_color
        radius: 20

        Text{
            id: i_custom_btr_label
            y: 0
            x: i_custom_btr_section.radius
            width: i_custom_btr_section.width
            color: st_font_color
            text: st_custom_btr_anno + " CAN frequency:  " + device_manager.val_FDCAN_freq + "Mhz"
            font.pixelSize: st_initial_item_height/2
        }


        Text{
            id: i_calculator_link
            x: i_custom_btr_label.x
            y: i_custom_btr_label.y + i_custom_btr_label.height
            font.pixelSize: st_initial_item_height/2
            smooth: true
            color: st_font_color
            text: calculator_link_txt
            onLinkActivated: Qt.openUrlExternally("https://phryniszak.github.io/stm32g-fdcan/")
            MouseArea {
                id: mouseArea_calculator
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    Qt.openUrlExternally("https://phryniszak.github.io/stm32g-fdcan/")
                }
            }
        }

        //============= PSC ===============
        RoundedTextInput{
            id: i_PSC
            x: i_custom_btr_section.radius
            y: i_calculator_link.y + i_calculator_link.height
            width: (i_custom_btr_section.width- composition_side_crop)/5 - composition_side_crop
            _anno: "PSC  "
            _enabled: true
            _value: device_manager.canfd1_nbtr_psc.toString()
            a_txt_input.font.capitalization: Font.AllUppercase
            function update_initial_value(){
                var _intvalue = a_txt_input.text;
                // Convert hex string to integer
                var _id = parseInt(_intvalue, 10);
                device_manager.canfd1_nbtr_psc = _intvalue;
                changesCommitted();
            }
        }
        //============= BS1 ===============
        RoundedTextInput{
            id: i_BS1
            x: i_PSC.x + i_PSC.width + composition_side_crop
            y: i_PSC.y
            width: i_PSC.width
            _anno: "BS1  "
            _enabled: true
            _value: device_manager.canfd1_nbtr_tseg1.toString()
            a_txt_input.font.capitalization: Font.AllUppercase
            function update_initial_value(){
                var _intvalue = a_txt_input.text;
                // Convert hex string to integer
                var _id = parseInt(_intvalue, 10);
                device_manager.canfd1_nbtr_tseg1 = _intvalue;
                changesCommitted();
            }
        }
        //============= BS2 ===============
        RoundedTextInput{
            id: i_BS2
            x: i_BS1.x + i_BS1.width + composition_side_crop
            y: i_PSC.y
            width: i_PSC.width
            _anno: "BS2  "
            _enabled: true
            _value: device_manager.canfd1_nbtr_tseg2.toString()
            a_txt_input.font.capitalization: Font.AllUppercase
            function update_initial_value(){
                var _intvalue = a_txt_input.text;
                // Convert hex string to integer
                var _id = parseInt(_intvalue, 10);
                device_manager.canfd1_nbtr_tseg2 = _intvalue;
                changesCommitted();
            }
        }
        //============= SJW ===============
        RoundedTextInput{
            id: i_SJW
            x: i_BS2.x + i_BS2.width + composition_side_crop
            y: i_PSC.y
            width: i_PSC.width
            _anno: "SJW  "
            _enabled: true
            _value: device_manager.canfd1_nbtr_sjw.toString()
            a_txt_input.font.capitalization: Font.AllUppercase
            function update_initial_value(){
                var _intvalue = a_txt_input.text;
                // Convert hex string to integer
                var _id = parseInt(_intvalue, 10);
                device_manager.canfd1_nbtr_sjw = _intvalue;
                changesCommitted();
            }
        }

        //============= Apply ===============
        MltButton{
            id: i_apply_custom_btr_button
            x: i_SJW.x + i_SJW.width + composition_side_crop
            anchors.bottom: i_PSC.bottom
            height: st_initial_item_height
            width: i_PSC.width
            st_button_mode: false
            st_text: "NBTR"
            st_normal_color: st_button_mode ? st_G_color : st_N_color
        }

        //============= PSC ===============
        RoundedTextInput{
            id: i_PSC_2
            x: i_PSC.x
            y: i_PSC.y + i_PSC.height + vertical_gap
            width: i_PSC.width
            _anno: "PSC  "
            _enabled: true
            _value: device_manager.canfd1_dbtr_psc.toString()
            a_txt_input.font.capitalization: Font.AllUppercase
            function update_initial_value(){
                var _intvalue = a_txt_input.text;
                // Convert hex string to integer
                var _id = parseInt(_intvalue, 10);
                device_manager.canfd1_dbtr_psc = _intvalue;
                changesCommitted();
            }
        }
        //============= BS1 ===============
        RoundedTextInput{
            id: i_BS1_2
            x: i_BS1.x
            y: i_PSC_2.y
            width: i_BS1.width
            _anno: "BS1  "
            _enabled: true
            _value: device_manager.canfd1_dbtr_tseg1.toString()
            a_txt_input.font.capitalization: Font.AllUppercase
            function update_initial_value(){
                var _intvalue = a_txt_input.text;
                // Convert hex string to integer
                var _id = parseInt(_intvalue, 10);
                device_manager.canfd1_dbtr_tseg1 = _intvalue;
                changesCommitted();
            }
        }
        //============= BS2 ===============
        RoundedTextInput{
            id: i_BS2_2
            x: i_BS2.x
            y: i_PSC_2.y
            width: i_BS2.width
            _anno: "BS2  "
            _enabled: true
            _value: device_manager.canfd1_dbtr_tseg2.toString()
            a_txt_input.font.capitalization: Font.AllUppercase
            function update_initial_value(){
                var _intvalue = a_txt_input.text;
                // Convert hex string to integer
                var _id = parseInt(_intvalue, 10);
                device_manager.canfd1_dbtr_tseg2 = _intvalue;
                changesCommitted();
            }
        }
        //============= SJW ===============
        RoundedTextInput{
            id: i_SJW_2
            x: i_SJW.x
            y: i_PSC_2.y
            width: i_PSC.width
            _anno: "SJW  "
            _enabled: true
            _value: device_manager.canfd1_dbtr_sjw.toString()
            a_txt_input.font.capitalization: Font.AllUppercase
            function update_initial_value(){
                var _intvalue = a_txt_input.text;
                // Convert hex string to integer
                var _id = parseInt(_intvalue, 10);
                device_manager.canfd1_dbtr_sjw = _intvalue;
                changesCommitted();
            }
        }

        //============= Apply ===============
        MltButton{
            id: i_apply_custom_btr_button_2
            x: i_apply_custom_btr_button.x
            anchors.bottom: i_PSC_2.bottom
            height: st_initial_item_height
            width: i_PSC.width
            st_button_mode: false
            st_normal_color: st_N_color
            st_text: "DBTR"
        }
    } // custom BTR section
}
