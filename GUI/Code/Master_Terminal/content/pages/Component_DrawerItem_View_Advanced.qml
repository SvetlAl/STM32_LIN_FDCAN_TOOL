import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "SimpleItems";

Item {
    /********* size settings ********/
    /********* colors settings ********/
    /********* values ********/
    /********* translated ********/

    function retranslateUi() {
    }

    Connections {
        target: qmlTranslator
        function onLanguageChanged(){
            retranslateUi()
        }
    }

    Component.onCompleted:{
        retranslateUi();
    }

    /********* alias ********/

    id: root
    height: i_adv_viewscale.height + i_adv_generaldesign.height + i_adv_simpleitems.height + i_adv_base.height
    width: parent.width

    function recalculateHeight(){
        i_adv_viewscale.calculateHeight();
        i_adv_generaldesign.calculateHeight();
        i_adv_simpleitems.calculateHeight();
        i_adv_base.calculateHeight();
    }

    Sub_View_Advanced_ViewScale{
        id: i_adv_viewscale
        onHeightChanged: {
            recalculateHeight();
            root.height = i_adv_viewscale.height + i_adv_generaldesign.height + i_adv_simpleitems.height + i_adv_base.height
        }
    }

    Sub_View_Advanced_GeneralDesign{
        id: i_adv_generaldesign
        anchors.top: i_adv_viewscale.bottom
        onHeightChanged: {
            recalculateHeight();
            root.height = i_adv_viewscale.height + i_adv_generaldesign.height + i_adv_simpleitems.height + i_adv_base.height
        }
    }

    Sub_View_Advanced_SimpleItems{
        id: i_adv_simpleitems
        anchors.top: i_adv_generaldesign.bottom
        onHeightChanged: {
            recalculateHeight();
            root.height = i_adv_viewscale.height + i_adv_generaldesign.height + i_adv_simpleitems.height + i_adv_base.height
        }
    }

    Sub_View_Advanced_Base{
        id: i_adv_base
        anchors.top: i_adv_simpleitems.bottom
        onHeightChanged: {
            recalculateHeight();
            root.height = i_adv_viewscale.height + i_adv_generaldesign.height + i_adv_simpleitems.height + i_adv_base.height
        }
    }
}


