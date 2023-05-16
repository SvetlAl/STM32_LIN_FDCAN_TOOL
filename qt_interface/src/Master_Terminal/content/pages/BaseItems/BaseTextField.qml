import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.12
import Qt.labs.platform 1.0
import CoreImport

Rectangle {
    /********* size settings ********/
    property int st_border_width: CoreImport._Base_Width_ButtonBorder*2
    property int st_radius: (CoreImport._Base_Height_Navibar*0.6)/4
    property int st_font_sz: CoreImport._Base_Font_TerminalSz

    /********* colors settings ********/
    property string st_font_color: CoreImport._Base_Color_BaseFont
    property string st_canva_color: CoreImport._GeneralDesign_Color_ToolBar
    property string st_border_color: CoreImport._Base_Color_Frame // st_font_color

    property real _gradient_start_pos: 0.0
    property real _gradient_end_pos: 1.5
    property string st_gradient_end: Qt.tint(Qt.lighter(st_canva_color, 2.2), "#111111FF")
    property string st_gradient_start: Qt.tint(Qt.lighter(st_canva_color, 1.2), "#22222200")

    gradient: Gradient {
        orientation:Gradient.Horizontal
        GradientStop { position: _gradient_start_pos; color: st_gradient_start }
        GradientStop { position: _gradient_end_pos; color: st_gradient_end}
    }

    /********* values ********/
    property string st_text: "Connect"
    property bool editable: false

    /********* alias ********/
    property alias a_txt: i_text.text

    function cmd(){
        /* do something */
    }

    id: root
    width: 450
    height: 450
    border.color: st_border_color
    border.width: st_border_width
    radius: st_radius
    clip: false

    Component.onCompleted: {
     //   Qt.inputMethod.hide();
        i_flick.ensureVisible(i_text.cursorRectangle)
    }

    MouseArea {
        id: mouseArea
        z: 0
        anchors.fill: root
        acceptedButtons: Qt.RightButton
        onClicked: {
            i_text.forceActiveFocus();
            i_text.cursorVisible = true;
        }
    }

    function slide_cursor_position() {
        i_text.cursorPosition = i_text.text.length;
    }

    function clean() {
    }

    function fitMaxCache(){
        var count_to_slice = a_txt.length - st_max_cache;
        a_txt = a_txt.slice(count_to_slice);
    }

    function set_data(data) { 
        i_text.text = data
        i_text.cursorPosition = i_text.text.length;
    }

    function append_data(data) {
        i_text.append(data);
        i_text.cursorPosition = i_text.text.length;
    }
/*
    function adaptFontSize() {
        var width = i_text.width
        var length = i_text.text.length
        var newFontSize = _font_sz
        if (width/(_font_sz/2) < length) {
            newFontSize = 1.5*(i_text.width/i_text.text.length)
            if (newFontSize < 12)
                newFontSize = 12
        }
        i_text.font.pixelSize = newFontSize
    }
*/
    Flickable   {
        id: i_flick
        z: 0
        contentWidth: root.width - i_scrollbar.width*3
        contentHeight: i_text.paintedHeight

        height: root.height - st_radius // /4
        width: root.width - st_radius
        anchors.verticalCenter: root.verticalCenter
        anchors.horizontalCenter: root.horizontalCenter
        clip: true
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.vertical: ScrollBar {
            id: i_scrollbar
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            width: root.width/20
            height: i_flick.height - st_radius //- i_flick.height/10
        }

        function ensureVisible(r)
        {
            if (contentX >= r.x)
                contentX = r.x;
            else if (contentX+width <= r.x+r.width)
                contentX = r.x+r.width-width;
            if (contentY >= r.y)
                contentY = r.y;
            else if (contentY+height <= r.y+r.height)
                contentY = r.y+r.height-height;

           // i_text.forceActiveFocus();
           // i_text.cursorVisible = true;
        }

        TextEdit{
            //inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
            id: i_text
            z: 20
            selectByMouse: true
            height: parent.height //  - st_border_width*2
            width: parent.width // - i_scrollbar.width*3
            font.pixelSize: st_font_sz
            color: st_font_color
            text: st_text
            wrapMode: TextEdit.Wrap
            textFormat: TextEdit.PlainText
            readOnly: editable ? false : true
            clip: false //true

            onCursorRectangleChanged:{
                i_flick.ensureVisible(cursorRectangle)
            }
            onEditingFinished: {
                cmd();
            }
            Component.onCompleted: {
             //   Qt.inputMethod.hide();
             //   i_text.forceActiveFocus()
            }
        }

    }
}
