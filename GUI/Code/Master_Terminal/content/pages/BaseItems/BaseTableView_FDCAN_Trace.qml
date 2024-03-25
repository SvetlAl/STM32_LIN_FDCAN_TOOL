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
   // property string st_font_color2: "#FFCC22"
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

    /*******************************************************************/
    /*                                Modes                            */
    /*******************************************************************/
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
    property var columnWidths : root.width < 39*st_font_sz ?
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
                                        46*st_font_sz] : //         9
                                    [
                                        2*st_font_sz, // IsSelected
                                        7*st_font_sz, // Time
                                        3*st_font_sz, // ESI
                                        3*st_font_sz, // FDF
                                        3*st_font_sz, // BRS
                                        4*st_font_sz, // CAN
                                        3*st_font_sz, // XTD
                                        6*st_font_sz, // ID
                                        4*st_font_sz, // DLC
                                        46*st_font_sz]

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
                boundsBehavior:Flickable.StopAtBounds

                delegate: Rectangle {
                    id: columnHeader
                    color: "transparent"
                    border.color: st_font_color
                    border.width: 1
                    radius: 10
                    implicitHeight: st_header_height
                    implicitWidth: sortable_header_txt.contentWidth + 5*splitter.width

                    MouseArea{
                        id: i_header_txt_mouseArea
                        anchors.fill: columnHeader
                        hoverEnabled: true
                        onClicked: {
                            sortColumn(column);
                            tableView.forceLayout();
                        }
                    }

                    Text{
                        id: sortable_header_txt
                        enabled: true
                        visible: true
                        anchors.centerIn: parent
                        x: 4
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

                reuseItems: false

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
                    implicitHeight: st_header_height * mlt_height + 1
                    height: st_header_height * mlt_height + 1
                    implicitWidth: 50
                    color: "transparent"
                    border.color: st_font_color
                    border.width: 1

                    readonly property int bytes_per_line: 16
                    property int mlt_height: (modelData.ByteCount <= bytes_per_line) ? 1 : Math.ceil(modelData.ByteCount/bytes_per_line)

                    CheckBox {
                        visible: column === 0
                        property bool st_checkable: column === 0
                        anchors.fill: parent
                        tristate: false
                        checked: !visible ? Qt.Unchecked : boolData ? Qt.Checked : Qt.Unchecked

                        onClicked:{
                            if(st_checkable){
                                root.model.setData(root.model.index(row, 0), checked, Qt.EditRole)
                            }
                        }
                        //onCheckedChanged:
                    }

                    Text{// "ESI"
                        id: i_esi_cell
                        enabled: column === 2
                        visible: column === 2
                        anchors.verticalCenter: parent.verticalCenter
                        x: 4
                        text: model.display
                        font.pixelSize: st_font_sz
                        color: modelData.Color //cellText.color
                    }
                    MouseArea{
                        id: i_esi_cell_mouseArea
                        anchors.fill: parent
                        enabled: column === 2
                        hoverEnabled: true
                        onClicked: {
                            var _value;
                            if(i_esi_cell.text === "ESI") _value = "   ";
                            else  _value = "ESI";
                            root.model.setData(root.model.index(row, 2), _value, Qt.EditRole)
                            i_esi_cell.text = visible ? model.display : ""

                        }
                    }


                    Text{// "FDF"
                        id: i_fdf_cell
                        enabled: column === 3
                        visible: column === 3
                        anchors.verticalCenter: parent.verticalCenter
                        x: 4
                        text: model.display
                        font.pixelSize: st_font_sz
                        color: modelData.Color
                    }
                    MouseArea{
                        id: i_fdf_cell_mouseArea
                        anchors.fill: parent
                        enabled: column === 3
                        hoverEnabled: true
                        onClicked: {
                            var _value;
                            if(i_fdf_cell.text === "FDF") _value = "   ";
                            else  _value = "FDF";
                            root.model.setData(root.model.index(row, 3), _value, Qt.EditRole)
                            i_fdf_cell.text = visible ? model.display : ""
                        }
                    }


                    Text{// "BRS"
                        id: i_brs_cell
                        enabled: column === 4
                        visible: column === 4
                        anchors.verticalCenter: parent.verticalCenter
                        x: 4
                        text: model.display
                        font.pixelSize: st_font_sz
                        color: modelData.Color
                    }
                    MouseArea{
                        id: i_brs_cell_mouseArea
                        anchors.fill: parent
                        enabled: column === 4
                        hoverEnabled: true
                        onClicked: {
                            var _value;
                            if(i_brs_cell.text === "BRS") _value = "   ";
                            else  _value = "BRS";
                            root.model.setData(root.model.index(row, 4), _value, Qt.EditRole)
                            i_brs_cell.text = visible ? model.display : ""
                        }
                    }


                    Text{// "XTD"
                        id: i_ext_cell
                        enabled: column === 6
                        visible: column === 6
                        anchors.verticalCenter: parent.verticalCenter
                        x: 4
                        text: model.display
                        font.pixelSize: st_font_sz
                        color: modelData.Color
                    }
                    MouseArea{
                        id: i_xtd_cell_mouseArea
                        anchors.fill: parent
                        enabled: column === 6

                        hoverEnabled: true
                        onClicked: {
                            var _value;
                            if(i_ext_cell.text === "XTD") _value = "   ";
                            else  _value = "XTD";
                            // console.log(_value);
                            root.model.setData(root.model.index(row, 6), _value, Qt.EditRole)
                            i_ext_cell.text = visible ? model.display : ""
                        }
                    }

                    Text{// "CAN"
                        id: i_can_cell
                        enabled: column === 5
                        visible: column === 5
                        anchors.verticalCenter: parent.verticalCenter
                        x: 4
                        text: model.display
                        font.pixelSize: st_font_sz
                        color: modelData.Color
                    }
                    MouseArea{
                        id: i_can_cell_mouseArea
                        anchors.fill: parent
                        enabled: column === 5
                        hoverEnabled: true
                        onClicked: {
                            var _value;
                            if(i_can_cell.text === "CAN 1") _value = "CAN 2";
                            else  _value = "CAN 1";
                            root.model.setData(root.model.index(row, 5), _value, Qt.EditRole)
                            i_can_cell.text = visible ? model.display : ""
                        }
                    }


                    TextEdit { // "Time" "CAN" "ID"
                        id: cellText
                        width: i_delegate.width
                        wrapMode: Text.Wrap
                        readOnly: false
                        textFormat: TextEdit.RichText
                        selectByMouse: true
                        visible:  ((column === 1 || column === 7 || column === 8 || column === 9))? true : false
                        text: (column === 9) ? modelData.Data : (column === 7  || column === 8 ) ?  ("0x" + display) : display
                        color: modelData.Color
                        font.pixelSize: st_font_sz
                        anchors.verticalCenter: parent.verticalCenter
                        x: 4
                        Component.onCompleted: {
                        }

                        Keys.onReturnPressed: {editingFinished()} // Enter key
                        Keys.onEnterPressed: {editingFinished()} // Numpad enter key

                        onEditingFinished: {
                            root.forceActiveFocus();
                            var plain_value = cellText.getText (0, cellText.length)
                            if((display === plain_value) || ("0x" + display === plain_value)){
                                return;
                            }
                            root.model.setData(root.model.index(row,column), plain_value);
                            if(column === 8) tableView.forceLayout();

                        }
                    }
                }

            } // TableView

        } // ColumnLayout

    } // Rectangle tabl
}
