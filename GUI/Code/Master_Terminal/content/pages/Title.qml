import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import CoreImport;

Item{
    /********* size settings ********/
    property real st_img_ratio: 0.65
    property real st_radius: 0.8
    property real st_side_margin: CoreImport._GeneralDesign_Ratio_ScreenAdjSideCrop
    property real st_title_to_toolbar_ratio: CoreImport._GeneralDesign_Ratio_TitleToToolbar
    property int st_height: CoreImport._GeneralDesign_Height_ToolBar * st_title_to_toolbar_ratio

    /********* colors settings ********/
    property string st_text_color: CoreImport._GeneralDesign_Color_ToolBarText
    property string st_background_color: Qt.lighter(CoreImport._GeneralDesign_Color_ToolBar, 1.2)

    /********* values ********/
    property string st_description: "description"
    property string st_logo: "st_logo"

    /********* alias ********/

    id: root
    width: parent.width
    height: st_height

    Rectangle{
        id:  i_title_frame
        width: root.width
        height: root.height
        color: st_background_color
        visible: true

        /* Logo picture */
        Rectangle{
            id: i_logo_rect
            width: i_title_frame.height * st_img_ratio
            height:i_title_frame.height * st_img_ratio

            anchors.verticalCenter: i_title_frame.verticalCenter
            anchors.leftMargin: (root.width - (root.width * st_side_margin)) / 2
            anchors.left: i_title_frame.left

            radius: st_radius * height
            visible: false
            clip: true
      }
      Image {
          id: img_logo
          width: i_logo_rect.height
          height: i_logo_rect.height
          anchors.fill: i_logo_rect
          source: st_logo
          fillMode: Image.PreserveAspectCrop

          clip: true
          visible: true
          antialiasing:  true
          smooth: true
          mipmap: true
      }

      ColorOverlay {
          anchors.fill: img_logo
          source: img_logo
          color: st_text_color
          cached: true
      }

    Label {
          id: i_label
          x: img_logo.x + img_logo.width + (img_logo.width/2)
          y: (root.height - contentHeight)/2
          width: root.width - img_logo.width - root.height/2
          height: ((root.height - (root.height - img_logo.height)) * CoreImport._GeneralDesign_Font_ToolBar)/100

          text: st_description
          color: st_text_color

          minimumPointSize: 5
          font.pointSize: 600
          fontSizeMode: Text.Fit
      }

    } /* Logo and picture END */
}
