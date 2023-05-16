/******************************************************************************
**
** Copyright (C) 2020 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Quick Ultralite module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

import QtQuick 2.15
import QtQuick.Controls

Item {
    /********* size settings ********/
    property int st_width: 50
    property int st_height: 100

    property int st_total_width: st_width
    property int st_total_height: st_height * 3

    property int st_font_pixelsize: (st_height - st_width)*2.5

    /********* colors settings ********/
    property string st_font_color: "#3d464d"

    property alias reversed: animation.reversed
    /********* values ********/
    property alias stopAnimation: animation.stopAnimation

    property int currentDigit: 99
    property int prevDigit: (currentDigit+9)%10
    property int nextDigit: (currentDigit+1)%10

    property int prevValue: 0
    property int value: 0

    property int st_initial_duartion: 200
    property int st_duartion: st_initial_duartion

    property bool reposition_flag: false
    /********* alias ********/

    id: slider
    y: 0
    height: st_total_height
    width: st_total_width

    Connections {
        target: slider
        function onValueChanged(){
            animation.start()
            prevValue = value
        }
    }

    function reset_duration(){
        st_duartion = st_initial_duartion;
    }

    function make_reposition(){
        st_duartion = 0;
        reposition_flag = true;
        reposition_flag = false;
        reset_duration();
        nextValueText.visible = false;
        prevValueText.visible = false;
    }

    onWidthChanged: {
        make_reposition();
    }

    Column {
        height: root.height
        width: root.width

        Rectangle{
            y: -st_height
            width: st_width
            height: st_height
            color: "transparent"
            Label {
                id: nextValueText
                anchors.fill: parent
                color: st_font_color;
                text: slider.nextDigit
                font.pixelSize: st_font_pixelsize;
                font.family: "Roboto"
                font.weight: Font.Medium
                verticalAlignment: Text.AlignVCenter
            }
        }
        Rectangle{
            width: st_width
            height: st_height
            y: 0
            color: "transparent"
            Label {
                id: currentValueText
                anchors.fill: parent
                visible: true
                color: st_font_color;
                text: slider.currentDigit
                font.pixelSize: st_font_pixelsize;
                font.family: "Roboto"
                font.weight: Font.ExtraBold
                verticalAlignment: Text.AlignVCenter
            }
        }
        Rectangle{
            width: st_width
            height: st_height
            y: st_height
            color: "transparent"
            Label {
                id: prevValueText
                anchors.fill: parent
                color: st_font_color;
                text: slider.prevDigit
                font.pixelSize: st_font_pixelsize;
                font.family: "Roboto"
                font.weight: Font.Medium
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    SequentialAnimation {
        id: animation
        property bool reversed: true
        property bool stopAnimation: true// false
        running: /* !reposition_flag ? (slider.currentDigit != slider.value) : */ true

        ScriptAction {
            script: { // this script prevent situation when digits are not changed during fast change
                nextValueText.visible = animation.reversed ? false : true;
                prevValueText.visible = animation.reversed ? true : false;
                slider.currentDigit = ((animation.reversed ? slider.value + 1 : slider.value - 1) + 10) % 10

            }
        }
        NumberAnimation {
            target: slider
            property: "y"
            duration: animation.stopAnimation ? 0 : st_duartion
            from: -st_height
            to: animation.reversed ? -st_height*2 : 0
        }

        ScriptAction {
            script: {
                slider.currentDigit = slider.value
                slider.y = -st_height
                nextValueText.visible = false;
                prevValueText.visible = false;
            }
        }
    }
}
