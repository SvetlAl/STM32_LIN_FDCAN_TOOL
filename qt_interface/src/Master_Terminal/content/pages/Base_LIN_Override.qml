import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "BaseItems";

Base {
    /********* size settings ********/
    property real buttons_width_mlt: 3.5
    property int width_grid_sz: width*st_side_crop / 10
    /********* colors settings ********/

    /********* values ********/

    property int composition_side_crop: (width - (width * st_side_crop))/2
    property int vertical_gap: height/20

    /********* alias ********/

    /********* translated ********/

}
