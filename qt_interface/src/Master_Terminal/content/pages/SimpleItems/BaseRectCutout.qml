import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport

Rectangle {
    property int st_width: width
    property int st_height: height
    property int st_radius: 10
    property int st_border_width: 5
    property string st_border_color: "#000000"
    property string st_fill_color: "transparent"
    property int st_cutout_x: 100
    property int st_cutout_width: 50

    id: i_canva_base
    width: parent.width
    height: parent.height
    border.width: 0
    border.color: "transparent"
    color: "transparent"

    onSt_widthChanged: i_canva.requestPaint();
    onSt_heightChanged: i_canva.requestPaint();
    onSt_radiusChanged: i_canva.requestPaint();
    onSt_border_widthChanged: i_canva.requestPaint();
    onSt_border_colorChanged: i_canva.requestPaint();
    onSt_cutout_widthChanged: i_canva.requestPaint();
    onSt_cutout_xChanged: i_canva.requestPaint();
    onSt_fill_colorChanged: i_canva.requestPaint();

    Canvas {
        id: i_canva
        width: i_canva_base.width
        height: i_canva_base.height
        antialiasing: true
        smooth: true
        visible: true

        function roundRect(r_x, r_y, r_width, r_height, co_x, co_width, r_radius){
            var ctx = i_canva.getContext("2d");
            var r_x_end = r_x + r_width;
            var r_y_end = r_y + r_height;
            //ctx.save();
            ctx.clearRect(i_canva.x, i_canva.y, i_canva.width, i_canva.height);
            ctx.beginPath();
            ctx.strokeStyle = st_border_color;
            ctx.lineWidth = st_border_width;
            ctx.fillStyle = st_fill_color;
            ctx.moveTo(r_x + co_x + co_width/*r_radius */, r_y);
            ctx.lineTo(r_x_end - r_radius, r_y);
            ctx.lineTo(r_x_end - r_radius, r_y);
            ctx.quadraticCurveTo(r_x_end, r_y, r_x_end, r_y + r_radius);
            ctx.lineTo(r_x_end, r_y + r_height - r_radius);
            ctx.quadraticCurveTo(r_x_end, r_y_end, r_x_end - r_radius, r_y_end);
            ctx.lineTo(r_x + r_radius, r_y_end);
            ctx.quadraticCurveTo(r_x, r_y_end, r_x, r_y_end - r_radius);
            ctx.lineTo(r_x, r_y + r_radius);
            ctx.quadraticCurveTo(r_x, r_y, r_x + r_radius, r_y);
            ctx.lineTo(r_x + co_x /*r_radius */, r_y);
            ctx.fill();
            ctx.stroke();
          }

            onPaint: {
                roundRect(st_border_width, st_border_width, st_width - st_border_width*2,
                          st_height - st_border_width*2, st_cutout_x, st_cutout_width, st_radius);
            }
        }   /* canva */
    }





