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
    property string st_text_003: qsTr("<p><b>Supported vehicle models and adjustable signals:<br></b>
<u>Toyota LC300:</u> Speedometer, odometer, cruise-control.<br>
<u>Toyota LC150:</u> Speedometer, odometer, cruise-control.<br>
<u>Toyota LC200:</u> Speedometer, odometer, cruise-control.<br>
<u>Lexus LX 2006-2022:</u> Speedometer, odometer, cruise-control.<br>
<u>Toyota Tundra 2008-2020:</u> Speedometer, odometer, cruise-control.<br>
<u>Toyota Hilux:</u> Cruise-control.<br>
<u>Isuzu D-MAX, MU-X:</u> Speedometer, cruise-control, TPMS threshold. <i>The odometer counter is locked on speedomter and can not be adjusted separatedly from speedometer.</i><br>
<u>Dodge RAM 2013:</u> Speedometer, cruise-control. <i>The odometer counter is locked on speedomter and can not be adjusted separatedly from speedometer.</i><br>
<u>Land Rover Defender:</u>  Speedometer, cruise-control. <i>The odometer counter is locked on speedomter and can not be adjusted separatedly from speedometer.</i><br>
<u>Mitsubishi L200 2019+:</u> Speedometer, odometer, cruise-control.<br>
<u>Mitsubishi Pajero Sport 2019+:</u>  Speedometer, odometer*, cruise-control.<br>
<i>Optionally: disabling ACC system. *Notice: 100 meter odometer readings  of a stock vehicle may show different results from test to test. Therefore odometer calibration is disabled by default. But It can be enabled and reprogrammed using this application.</i><br>
<u>Great Wall Wingle7:</u> :  Speedometer, cruise-control. <i>The odometer counter is locked on speedomter and can not be adjusted separatedly from speedometer.</i><br>
<u>Great Wall Poer:</u> Speedometer, odometer, cruise-control, TPMS threshold. <br></p>")
    property string st_text_004: qsTr("<p><i>Notice: the greater the distance of the test,
 the more percision shown in odometer readings. Some models' odometers may ignore the speed below 1 km/h.</i><br><br></p>")
    property string st_text_005: qsTr("<p><b>Device programming.</b><br>
The algorithm: <br>
- Plug in USB cable. <br>
- Establish connection with the button \"Connect\". <br>
- Select a vehicle model, unplug the cable, restart the application, repeat the steps 1 and 2. <br>
- Select a value parameter in the Menu (speedometer, odometer, etc) and set a supposed value. <br>
- If satisfied with the calibration value, it can be written into memory with the button \"Save\".<br><br></p>")
    property string st_text_006: qsTr("<p><i>Notice: memory write operation (button \"Save\" or model select)
 may require the following steps:  power down the device (unplug USB cable and/or disable vehicle battery),
 restart the application.</i><br></p>")
    property string st_text_007: qsTr("<p><b>Important!!! When USB cable is plugged in,
 the device board is powered with 5V. Make sure, the 12V+(red) wire is isolated when programming.
 Otherwise a short ciruit on supply wires may occur</b></p>")
    property string st_text_008: qsTr("<p>The Arctic Trucks TEC devices have a LED indicator:<br>
The Arctic Trucks TEC devices  also have a button located close to LED (can be reached with a needle.<br>
LED an button purposes can be read from the update server.
</p>")
    property string st_text_009: qsTr("<p><b>Troubleshooting:</b>
1. If unboxed, the device board is exposed to short circuit risk. Any contact with a metal (screwdriver or vehicle body)
 of a powered device may cause a total failure. Also if a powered wire meets Ground (for Example, when twisting wires
 during installation), this may fail into burned fuse. Therefore installation must be carried out with powered down
 vehicle. <br><br>
2. Some devices based on Starline manufactor hardware may have a supply chip overheating issue. While performing lab tests the
 heat seems to dissipate and get gone, but nevertheless the chip may malfunction. If this happens, replace the devce.<br><br>
3. All the dashboard  warning lights are on, OBD scanner shows no fault codes. Possible reasons:<br>
- No power (12V+)<br>
Solution: Check the wires connection (step 1)<br>
- CAN H OUT and CAN L OUT misconnection. CAN H OUT  may be mistaken for CAN L OUT.<br>
Solution:  Check CAN bus wires connection, soldering and isolation. Make sure no foreign particles that can cause
 a short circuit are inside the box.<br><br>
4. All the dashboard  warning lights are on, OBD scanner shows some fault codes. Possible reasons:<br>
- CAN H OUT and CAN L IN misconnection. Possible short circuit on a CAN bus.<br>
</p>")
    property string st_text_010: qsTr("<p><b>Important:  A CAN bus short circuit may lead to failure of the WHOLE CAN BUS of the vehicle.
</b></p>")
    property string st_text_011: qsTr("<p>5. Speed calibration does not happen:
- IN and OUT lines direction are wrong: reconnect IN and OUT vice versa.
- Wrong car model is selected.
Inspection: Select \"Test\" section in the application and try a control procedure. If the wires direction and model
 settings are correct, the dashboard would show a speed above 50 km/h.<br><br>
6. The device malfunction on Mitsubishi, but seems to be OK on the other models. This issue was solved in 2023.
- Install a 120 Ohm resistor in between CAN H OUT and CAN L OUT on the board.<br><br>
7. Some vehicle functions seem to fail, warning lights may come up on the dashboard.
 The failure keeps to stay on even after device removal and wiring recovery.<br>
- Check the fuse of the line, that power wire was connected to (for Example IG+)<br>
- Make sure GND и V12+ have no short circuit.<br>
</p>")
    property string st_text_012: qsTr("<p><b>Changes:</b><br>
6.02.2023 Odometer calibration reworked. Great Wall Poer.<br>
6.02.2023 Enhanced odometer algorithm. Toyota LC150, LC200.<br>
</p>")

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
        st_text_003 = qsTr("<p><b>Supported vehicle models and adjustable signals:<br></b>
        <u>Toyota LC300:</u> Speedometer, odometer, cruise-control.<br>
        <u>Toyota LC150:</u> Speedometer, odometer, cruise-control.<br>
        <u>Toyota LC200:</u> Speedometer, odometer, cruise-control.<br>
        <u>Lexus LX 2006-2022:</u> Speedometer, odometer, cruise-control.<br>
        <u>Toyota Tundra 2008-2020:</u> Speedometer, odometer, cruise-control.<br>
        <u>Toyota Hilux:</u> Cruise-control.<br>
        <u>Isuzu D-MAX, MU-X:</u> Speedometer, cruise-control, TPMS threshold. <i>The odometer counter is locked on speedomter and can not be adjusted separatedly from speedometer.</i><br>
        <u>Dodge RAM 2013:</u> Speedometer, cruise-control. <i>The odometer counter is locked on speedomter and can not be adjusted separatedly from speedometer.</i><br>
        <u>Land Rover Defender:</u>  Speedometer, cruise-control. <i>The odometer counter is locked on speedomter and can not be adjusted separatedly from speedometer.</i><br>
        <u>Mitsubishi L200 2019+:</u> Speedometer, odometer, cruise-control.<br>
        <u>Mitsubishi Pajero Sport 2019+:</u>  Speedometer, odometer*, cruise-control.<br>
        <i>Optionally: disabling ACC system. *Notice: 100 meter odometer readings  of a stock vehicle may show different results from test to test. Therefore odometer calibration is disabled by default. But It can be enabled and reprogrammed using this application.</i><br>
        <u>Great Wall Wingle7:</u> :  Speedometer, cruise-control. <i>The odometer counter is locked on speedomter and acn not be adjusted separatedly from speedometer.</i><br>
        <u>Great Wall Poer:</u> Speedometer, odometer, cruise-control, TPMS threshold. <br></p>")
        st_text_004 = qsTr("<p><i>Notice: the greater the distance of the test,
         the more percision shown in odometer readings. Some models' odometers may ignore the speed below 1 km/h.</i><br><br></p>")
        st_text_005 = qsTr("<p><b>Device programming.</b><br>
    The algorithm: <br>
    - Plug in USB cable. <br>
    - Establish connection with the button \"Connect\". <br>
    - Select a vehicle model, unplug the cable, restart the application, repeat the steps 1 and 2. <br>
    - Select a value parameter in the Menu (speedometer, odometer, etc) and set a supposed value. <br>
    - If satisfied with the calibration value, it can be written into memory with the button \"Save\".<br><br></p>")
        st_text_006 = qsTr("<p><i>Notice: memory write operation (button \"Save\" or model select)
     may require the following steps:  power down the device (unplug USB cable and/or disable vehicle battery),
     restart the application.</i><br></p>")
        st_text_007 = qsTr("<p><b>Important!!! When USB cable is plugged in,
         the device board is powered with 5V. Make sure, the 12V+(red) wire is isolated when programming.
         Otherwise a short ciruit on supply wires may occur</b></p>")
        st_text_008 = qsTr("<p>The Arctic Trucks TEC devices have a LED indicator:<br>
        The Arctic Trucks TEC devices  also have a button located close to LED (can be reached with a needle.<br>
        LED an button purposes can be read from the update server.
        </p>")
        st_text_009 = qsTr("<p><b>Troubleshooting:</b>
    1. If unboxed, the device board is exposed to short circuit risk. Any contact with a metal (screwdriver or vehicle body)
     of a powered device may cause a total failure. Also if a powered wire meets Ground (for Example, when twisting wires
     during installation), this may fail into burned fuse. Therefore installation must be carried out with powered down
     vehicle. <br><br>
    2. Some devices based on Starline manufactor hardware may have a supply chip overheating issue. While performing lab tests the
     heat seems to dissipate and get gone, but nevertheless the chip may malfunction. If this happens, replace the devce.<br><br>
    3. All the dashboard  warning lights are on, OBD scanner shows no fault codes. Possible reasons:<br>
    - No power (12V+)<br>
    Solution: Check the wires connection (step 1)<br>
    - CAN H OUT and CAN L OUT misconnection. CAN H OUT  may be mistaken for CAN L OUT.<br>
    Solution:  Check CAN bus wires connection, soldering and isolation. Make sure no foreign particles that can cause
     a short circuit are inside the box.<br><br>
    4. All the dashboard  warning lights are on, OBD scanner shows some fault codes. Possible reasons:<br>
    - CAN H OUT and CAN L IN misconnection. Possible short circuit on a CAN bus.<br>
    </p>")
        st_text_010 = qsTr("<p><b>Important:  A CAN bus short circuit may lead to failure of the WHOLE CAN BUS of the vehicle.
    </b></p>")
        st_text_011 = qsTr("<p>5. Speed calibration does not happen:
    - IN and OUT lines direction are wrong: reconnect IN and OUT vice versa.
    - Wrong car model is selected.
    Inspection: Select \"Test\" section in the application and try a control procedure. If the wires direction and model
     settings are correct, the dashboard would show a speed above 50 km/h.<br><br>
    6. The device malfunction on Mitsubishi, but seems to be OK on the other models. This issue was solved in 2023.
    - Install a 120 Ohm resistor in between CAN H OUT and CAN L OUT on the board.<br><br>
    7. Some vehicle functions seem to fail, warning lights may come up on the dashboard.
     The failure keeps to stay on even after device removal and wiring recovery.<br>
    - Check the fuse of the line, that power wire was connected to (for Example IG+)<br>
    - Make sure GND и V12+ have no short circuit.<br>
    </p>")
        st_text_012: qsTr("<p><b>Changes:</b><br>
    6.02.2023 Odometer calibration reworked. Great Wall Poer.<br>
    6.02.2023 Enhanced odometer algorithm. Toyota LC150, LC200.<br>
    </p>")
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
    Image {
        id: img_Achtung004
        x: composition_side_crop
        height: st_container_height
        width: height
        y: i_text_004.y
        anchors.right : i_text_004.left
        source: "./png/warning.png"
        fillMode: Image.PreserveAspectCrop
        clip: true
        visible: true
        antialiasing:  true
        smooth: true
        mipmap: true
    }
    Text{
        id: i_text_004
        height: contentHeight
        width: st_container_width - img_Achtung004.width
        x: img_Achtung004.x + img_Achtung004.width
        anchors.top: i_text_003.bottom
        verticalAlignment: Text.AlignVCenter
        font.pointSize: st_common_font_pointsize
        smooth: true
        wrapMode: Text.WordWrap
        text: st_text_004
    }
    Text{
        id: i_text_005
        x: composition_side_crop
        anchors.top: i_text_004.bottom
        width: st_container_width
        height: contentHeight
        font.pointSize: st_common_font_pointsize
        smooth: false
        wrapMode: Text.WordWrap
        text: st_text_005
    }
    Image {
        id: img_Achtung006
        x: composition_side_crop
        height: st_container_height
        width: height
        y: i_text_006.y
        anchors.right : i_text_006.left
        source: "./png/warning.png"
        fillMode: Image.PreserveAspectCrop
        clip: true
        visible: true
        antialiasing:  true
        smooth: true
        mipmap: true
    }
    Text{
        id: i_text_006
        height: contentHeight
        width: st_container_width - img_Achtung006.width
        x: img_Achtung006.x + img_Achtung006.width
        anchors.top: i_text_005.bottom
        verticalAlignment: Text.AlignVCenter
        font.pointSize: st_common_font_pointsize
        smooth: true
        wrapMode: Text.WordWrap
        text: st_text_006
    }
    Image {
        id: img_Achtung007
        x: composition_side_crop
        height: st_container_height
        width: height
        y: i_text_007.y
        anchors.right : i_text_007.left
        source: "./png/warning.png"
        fillMode: Image.PreserveAspectCrop
        clip: true
        visible: true
        antialiasing:  true
        smooth: true
        mipmap: true
    }
    Text{
        id: i_text_007
        height: contentHeight
        width: st_container_width - img_Achtung007.width
        x: img_Achtung007.x + img_Achtung007.width
        anchors.top: i_text_006.bottom
        verticalAlignment: Text.AlignVCenter
        font.pointSize: st_common_font_pointsize
        smooth: true
        wrapMode: Text.WordWrap
        text: st_text_007
    }
    Text{
        id: i_text_008
        x: composition_side_crop
        anchors.top: i_text_007.bottom
        width: st_container_width
        height: contentHeight
        font.pointSize: st_common_font_pointsize
        smooth: false
        wrapMode: Text.WordWrap
        text: st_text_008
    }
    Image {
        id: img_LED
        x: composition_side_crop
        height: st_container_width*1.5
        width: st_container_width
        anchors.top : i_text_008.bottom
        source: "./png/Help/LED.png"
        fillMode: Image.PreserveAspectCrop
        clip: true
        visible: true
        antialiasing:  true
        smooth: true
        mipmap: true
    }
    Text{
        id: i_text_009
        x: composition_side_crop
        anchors.top: img_LED.bottom
        width: st_container_width
        height: contentHeight
        font.pointSize: st_common_font_pointsize
        smooth: false
        wrapMode: Text.WordWrap
        text: st_text_009
    }
    Image {
        id: img_Achtung010
        x: composition_side_crop
        height: st_container_height
        width: height
        y: i_text_010.y
        anchors.right : i_text_010.left
        source: "./png/warning.png"
        fillMode: Image.PreserveAspectCrop
        clip: true
        visible: true
        antialiasing:  true
        smooth: true
        mipmap: true
    }
    Text{
        id: i_text_010
        height: contentHeight
        width: st_container_width - img_Achtung010.width
        x: img_Achtung010.x + img_Achtung010.width
        anchors.top: i_text_009.bottom
        verticalAlignment: Text.AlignVCenter
        font.pointSize: st_common_font_pointsize
        smooth: true
        wrapMode: Text.WordWrap
        text: st_text_010
    }
    Text{
        id: i_text_011
        x: composition_side_crop
        anchors.top: i_text_010.bottom
        width: st_container_width
        height: contentHeight
        font.pointSize: st_common_font_pointsize
        smooth: false
        wrapMode: Text.WordWrap
        text: st_text_011
    }
    Text{
        id: i_text_012
        x: composition_side_crop
        anchors.top: i_text_011.bottom
        width: st_container_width
        height: contentHeight
        font.pointSize: st_common_font_pointsize
        smooth: false
        wrapMode: Text.WordWrap
        text: st_text_012
    }
}
