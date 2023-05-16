import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "SimpleItems";

Item {
    /********* size settings ********/
    property int st_item_height: CoreImport._ViewScale_Height_Container
    property int st_item_font_sz: st_item_height/3
    property int st_max_displayed_cbx_items: 3
    property int st_item_width: root.width/3
    readonly property int st_common_font_pointsize: i_txt.fontInfo.pointSize

    /********* colors settings ********/
    property string st_clr_text: CoreImport._SimpleItems_Color_ButtonText /**/
    /********* values ********/

    /********* alias ********/

    /********* translated ********/
    property string st_header_text: qsTr("<b>Information.</b>")
    property string st_text_000: qsTr("<p> <b>Wiring nomination: </b><br>
1. V12+ Red <br>
2. GND Black <br>
3. CAN H (IN) Brown/Red <br>
4. CAN L (IN) Brown <br>
5. CAN H (OUT) Brown/Green <br>
6. CAN L (OUT) Brown <br></p>")
    property string st_text_001: qsTr("<p><b>Important!!! Disconnect the negative terminal of
the battery before connecting wires,  otherwise the device may be damaged by a short circuit..</b><br></p>")
    property string st_text_002: qsTr("<p>CAN-gateway's hardware and design of different manufactors
 is different and wiring set provided along with a device may have different colors.
Wiring color correspondence can be found in wiring nomination tables.<br></p>")


    function retranslateUi() {
        st_header_text = qsTr("<b>Information.</b>")
        st_text_000 = qsTr("<p> <b>Wiring nomination: </b><br>
1. V12+ Red <br>
2. GND Black <br>
3. CAN H (IN) Brown/Red <br>
4. CAN L (IN) Brown <br>
5. CAN H (OUT) Brown/Green <br>
6. CAN L (OUT) Brown <br></p>")
        st_text_001 = qsTr("<p> <b>Important!!! Disconnect the negative terminal of
the battery before connecting wires,  otherwise the device may be damaged by a short circuit.</b><br></p>")
        st_text_002 = qsTr("<p>CAN-gateway's hardware and design of different manufactors
is different and wiring set provided along with a device may have different colors.
Wiring color correspondence can be found in wiring nomination tables.<br></p>")
    }

    Connections {
        target: qmlTranslator
        onLanguageChanged:function(){
            retranslateUi()
        }
    }

    signal sendHeight(int msg)


    id: root
    width: parent.width
    height:  parent.height

    MouseArea{
        property string type: "focus_reset"
        anchors.fill: root
        onClicked: {
            root.forceActiveFocus()
        }
    }

    Component.onCompleted:{
        retranslateUi();
        calculateHeight();
    }
    onWidthChanged: {
        calculateHeight();
    }
    onHeightChanged: {
        calculateHeight();
    }

    function calculateHeight(){

        var total_height = 0
        for(var i = root.children.length; i > 0 ; i--) {
            if(root.children[i-1].type !== "focus_reset"){
                total_height += root.children[i-1].height
                total_height += root.children[i-1].anchors.topMargin
            }
        }
        root.height = total_height
    }


    Rectangle {
        id: i_main_rect
        width: st_container_width
        height: st_container_height
        x: composition_side_crop

        anchors.top: root.top
        color: "transparent"

        onWidthChanged: {
            calculateHeight();
        }
        onHeightChanged: {
            calculateHeight();
        }

        Label {
            id: i_txt
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            width: i_main_rect.width
            height: i_main_rect.height*0.8
            minimumPointSize: 5
            font.pointSize: 1 + i_main_rect.height*1.2 * st_ratio_font_sz
            color: st_clr_text
            fontSizeMode: Text.Fit
            clip: true

            text: st_header_text
        }
    }

    Text{
        id: i_text_000
        x: composition_side_crop
        anchors.top: i_main_rect.bottom
        width: st_container_width
        height: contentHeight
        font.pointSize: st_common_font_pointsize
        smooth: false
        wrapMode: Text.WordWrap
        text: st_text_000
    }
    Image {
        id: img_Achtung001
        x: composition_side_crop
        height: st_container_height
        width: height
        //anchors.verticalCenter: i_text_001.verticalCenter
        y: i_text_001.y //+ (i_text_001.contentHeight/2)
        anchors.right : i_text_001.left
        source: "./png/warning.png"
        fillMode: Image.PreserveAspectCrop
        clip: true
        visible: true
        antialiasing:  true
        smooth: true
        mipmap: true
    }
    Text{
        id: i_text_001
        height: contentHeight
        width: st_container_width - img_Achtung001.width
        x: img_Achtung001.x + img_Achtung001.width
        anchors.top: i_text_000.bottom
        // anchors.verticalCenter: img_Achtung001.verticalCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: st_common_font_pointsize
        smooth: true
        wrapMode: Text.WordWrap
        text: st_text_001
    }

    Text{
        id: i_text_002
        x: composition_side_crop
        anchors.top: i_text_001.bottom
        width: st_container_width
        height: contentHeight
        font.pointSize: st_common_font_pointsize
        smooth: false
        wrapMode: Text.WordWrap
        text: st_text_002
    }
    Text{
        id: i_text_003
        x: composition_side_crop
        anchors.top: i_text_002.bottom
        width: st_container_width
        height: contentHeight
        font.pointSize: st_common_font_pointsize
        smooth: false
        wrapMode: Text.WordWrap
        text: st_text_003
    }

}
