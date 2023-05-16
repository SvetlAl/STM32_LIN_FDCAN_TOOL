import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.12
import Qt.labs.platform 1.0
import QtQuick.Layouts
import CoreImport

Rectangle {
    /********* size settings ********/
    property int st_border_width: CoreImport._Base_Width_ButtonBorder*2
    property int st_radius: (CoreImport._Base_Height_Navibar*0.6)/4


    property int st_font_sz: CoreImport._Base_Font_TerminalSz
    property int st_header_height: st_font_sz*1.2 + st_font_sz*0.6 // root.height/10

    /********* colors settings ********/
    property string st_font_color: CoreImport._Base_Color_BaseFont
    property string st_font_color2: "#FFCC22"
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
    property bool st_editable: false
    property bool st_checkable: false
    property bool st_sortable: false
    property bool st_2can_trace_mode: false

    property string st_secondary_color_mark_value: "CAN 2";
    /********* alias ********/

    id: root
    width: 450
    height: 450
    border.color: st_border_color
    border.width: st_border_width
    radius: st_radius
    clip: false

    required property var model //: nameModel
    /*** column width depends on how many characters in a cell ***/
    property var columnWidths : root.width < 39*st_font_sz?
                                    [
                                    7*st_font_sz,
                                    6*st_font_sz,
                                    6*st_font_sz,
                                    6*st_font_sz,
                                    6*st_font_sz,
                                    8*st_font_sz
                                ] :
                                    [
                                    7*st_font_sz,
                                    6*st_font_sz,
                                    6*st_font_sz,
                                    6*st_font_sz,
                                    6*st_font_sz,
                                    (root.width - 31*st_font_sz )
                                ]

    function columnWidthProvider(column) {
        return columnWidths[column]
    }

    function sortColumn(column) {
    }

    onSt_font_szChanged: {
        st_header_height = st_font_sz*1.2 + st_font_sz*0.6//root.height/10
    }

    Component.onCompleted: {
        st_header_height = st_font_sz*1.2 + st_font_sz*0.6
        /*** column width depends on how many characters in a cell ***/
    }

    Rectangle {
        id: table
        x: st_radius/2
        y: st_radius/2
        width: root.width - st_radius
        height: root.height - st_radius
        color: "transparent"
        clip: true

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            HorizontalHeaderView {
                id: horizontalHeader
                reuseItems: false
                syncView: tableView /*Once this property is bound to another TableView, both header and table will synchronize with regard to column widths, column spacing, and flicking horizontally.
                                        If the model is not explicitly set, then the header will use the syncView's model to label the columns. */

                height: st_header_height
                //Layout.fillWidth: true
                boundsBehavior:Flickable.StopAtBounds

                delegate: Rectangle {
                    id: columnHeader
                    color: "transparent"
                    border.color: st_font_color
                    border.width: 1
                    radius: 10
                    implicitHeight: st_header_height
                    implicitWidth: headerText.contentWidth + 5*splitter.width
/*
                    Button{
                        visible: st_sortable
                        text: headerText.text
                        icon.color: "transparent"
                        anchors.fill: parent
                        font.pixelSize: st_font_sz
                        onClicked: {
                            sortColumn(column);
                        }
                    }
  */
                    MouseArea{
                        id: i_header_txt_mouseArea
                        anchors.fill: columnHeader
                        hoverEnabled: true
                        onClicked: {
                            sortColumn(column);
                        }
                    }


                        Text{
                            id: i_header_txt
                            enabled: st_sortable
                            visible: st_sortable
                            // anchors.fill: parent
                            anchors.centerIn: parent
                            //anchors.verticalCenter: parent.verticalCenter
                            x: 4
                            text: headerText.text
                            font.pixelSize: st_font_sz
                            // color: cellText.color


                        }



                    Text {
                        id: headerText
                        visible: !st_sortable
                        anchors.centerIn: parent
                        text: display
                        font.pixelSize: st_font_sz
                    }

                    Rectangle {
                        id: splitter
                        x: root.columnWidths[index] - width
                        height: horizontalHeader.height
                        width: 4
                        color: st_font_color
                        visible: dragArea.containsMouse || dragArea.drag.active

                        onXChanged: {
                            if (dragArea.drag.active) {
                                columnWidths[column] = (splitter.x + width)
                                tableView.forceLayout();
                            }
                        }
                    } // Rectangle splitter

                    MouseArea {
                        id: dragArea
                        anchors.fill: splitter
                        cursorShape: Qt.SizeHorCursor
                        drag.target: splitter
                        drag.axis: Drag.XAxis
                        drag.threshold: 0
                        drag.minimumX: parent.implicitWidth
                        hoverEnabled: true
                    }

                } // delegate Rectangle columnHeader

            } // HorizontalHeaderView

            TableView {
                id: tableView
                Layout.fillWidth: true
                Layout.fillHeight: true
                contentWidth: 2*st_font_sz*39
                clip: true
                boundsBehavior:Flickable.StopAtBounds
                columnWidthProvider: root.columnWidthProvider
                model: root.model

                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AlwaysOn
                    active: true
                    onActiveChanged: {
                        if (!active)
                            active = true;
                    }
                }

                ScrollBar.horizontal: ScrollBar {
                    policy: ScrollBar.AlwaysOn
                    active: true

                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    onActiveChanged: {
                        if (!active)
                            active = true;
                    }
                }


                delegate: Rectangle {
                    id: i_delegate
                    implicitHeight: 1 + st_header_height
                    height: st_header_height
                    implicitWidth: 50
                    color: "transparent"
                    border.color: st_font_color
                    border.width: 1

                    property string delegate_color: st_font_color

                    CheckBox {
                        visible:  st_checkable && column === 0
                        anchors.fill: parent
                        tristate: false
                        anchors.verticalCenter: parent.verticalCenter
                        checked: !visible ? Qt.Unchecked : boolData ? Qt.Checked : Qt.Unchecked

                        onClicked:{
                            if(st_checkable){
                                root.model.setData(root.model.index(row, 0), checked, Qt.EditRole)
                            }
                        }
                        //onCheckedChanged:
                    }

                    Text{// "EXT" : "STD"
                        id: i_ide_cell
                        enabled: st_2can_trace_mode && column === 3
                        visible: st_2can_trace_mode && column === 3
                        anchors.verticalCenter: parent.verticalCenter
                        x: 4
                        text: visible ? model.display : ""
                        font.pixelSize: st_font_sz
                        color: cellText.color

                        MouseArea{
                            id: i_ide_cell_mouseArea
                            anchors.fill: i_ide_cell
                            hoverEnabled: true
                            onClicked: {
                                var _value;
                                if(i_ide_cell.text === "EXT") _value = "STD";
                                else  _value = "EXT";
                                root.model.setData(root.model.index(row, 3), _value, Qt.EditRole)
                                i_ide_cell.text = visible ? model.display : ""
                            }
                        }
                    }

                    TextEdit {
                        id: cellText
                        width: i_delegate.width
                        wrapMode: Text.Wrap
                        //editable: st_editable
                        readOnly: !st_editable
                        selectByMouse: true
                        visible: (column === 0 && st_checkable) ? false:
                                                                   (column === 3  && st_2can_trace_mode)? false : true
                        text: display
                        color: i_delegate.delegate_color
                        font.pixelSize: st_font_sz
                        anchors.verticalCenter: parent.verticalCenter
                        x: 4
                        Component.onCompleted: {
                            if(st_2can_trace_mode){
                                color = Qt.binding(function() {
                                    if(root.model.getCan(row) === st_secondary_color_mark_value)
                                        return st_font_color2;
                                    else return st_font_color;
                                })
                            }
                        }

                        Keys.onReturnPressed: {editingFinished()} // Enter key
                        Keys.onEnterPressed: {editingFinished()} // Numpad enter key

                        onEditingFinished: {
                            root.model.setData(root.model.index(row,column), cellText.text);
                        }
                    }
                }

            } // TableView

        } // ColumnLayout

    } // Rectangle tabl
}
