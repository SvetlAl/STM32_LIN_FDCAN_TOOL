import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreImport;
import "SimpleItems";



Rectangle{
    /********* size settings ********/
    property int st_item_height: root.width/5 < CoreImport._ViewScale_Height_Container*1.2 ? root.width/5 : CoreImport._ViewScale_Height_Container*1.2
    property int st_item_font_sz: st_item_height/3 < st_item_height/3 ? st_item_height/3 : st_item_height/3
    /********* colors settings ********/
    property string st_font_color: CoreImport._Base_Color_BaseFont
    /********* values ********/
    property string preselected_vehicle_model: theVehicle.model_name
    /********* translated ********/


    /********* alias ********/
    // property alias _width: root.width

    id: root
    color: "transparent"

    Component.onCompleted: {
        cmd_manager.init_vehicleNames_Model();
        calculateHeight();
    }
    Component.onDestruction: {
        cmd_manager.reset_vehicleNames_Model();
    }

    enum ModelBrand {
        Toyota = 0,
        GreatWall = 1,
        Dodge = 2,
        LandRover = 3,
        Mitsubishi = 4,
        Isuzu = 5,
        Lexus = 6,
        Tank = 7,
        Honda = 8,
        Ford = 9,
        Nissan = 10,
        Extra = 11,
        Uaz = 12,
        Jeep = 13,
        Default = 14
    }

    function getLogoPath(_brand_code){
        var brand_name;
        switch(_brand_code){
        case Component_Base_SelectModel_Modellist.ModelBrand.Toyota:{  brand_name = "TOYOTA"; break; }
        case Component_Base_SelectModel_Modellist.ModelBrand.GreatWall:{  brand_name = "GREAT_WALL"; break; }
        case Component_Base_SelectModel_Modellist.ModelBrand.Dodge:{  brand_name = "DODGE"; break; }
        case Component_Base_SelectModel_Modellist.ModelBrand.LandRover:{  brand_name = "LAND_ROVER"; break; }
        case Component_Base_SelectModel_Modellist.ModelBrand.Mitsubishi:{  brand_name = "MITSUBISHI"; break; }
        case Component_Base_SelectModel_Modellist.ModelBrand.Isuzu:{  brand_name = "ISUZU"; break; }
        case Component_Base_SelectModel_Modellist.ModelBrand.Lexus:{  brand_name = "LEXUS"; break; }
        case Component_Base_SelectModel_Modellist.ModelBrand.Tank:{  brand_name = "TANK"; break; }
        case Component_Base_SelectModel_Modellist.ModelBrand.Honda:{  brand_name = "HONDA"; break; }
        case Component_Base_SelectModel_Modellist.ModelBrand.Ford:{  brand_name = "FORD"; break; }
        case Component_Base_SelectModel_Modellist.ModelBrand.Nissan:{  brand_name = "NISSAN"; break; }
        case Component_Base_SelectModel_Modellist.ModelBrand.Uaz:{  brand_name = "UAZ"; break; }
        case Component_Base_SelectModel_Modellist.ModelBrand.Jeep:{  brand_name = "JEEP"; break; }
        case Component_Base_SelectModel_Modellist.ModelBrand.Extra:{  brand_name = "EXTRA"; break; }
        default:{  brand_name = "EXTRA"; break; }
        }
        return CoreImport.brand_logos_path + brand_name + ".png";
    }


    signal modelSelected(string modelname, int modelvalue)

    signal sendHeight(int msg)
    function calculateHeight(){
        var total_height = 0
        for(var i = root.children.length; i > 0 ; i--) {
            if(root.children[i-1].type !== "focus_reset"){
                total_height += root.children[i-1].height
                total_height += root.children[i-1].anchors.topMargin
            }
        }
        root.height = total_height
        sendHeight(total_height)
    }

    ListView  {
        id: listView
        parent: root
        anchors.top: root.top
        height: cmd_manager.vehicleNames_Model.length * st_item_height
        width: root.width
        boundsBehavior: Flickable.DragOverBounds
        clip: true
        cacheBuffer: 2

        model: cmd_manager.vehicleNames_Model
        delegate:
            ItemDelegate {
            property var model_brand: modelData.brand_code
            property var mk_value_code: modelData.value

            parent: listView
            width: listView.width
            height: st_item_height

           Image {
             height: modelData.name === preselected_vehicle_model ? st_item_height*1.1 : st_item_height*0.8
             width: modelData.name === preselected_vehicle_model ? st_item_height*1.1 : st_item_height*0.8
             x: 0
             y: 0
             opacity: 1.0
             antialiasing:  true
             smooth: true
             mipmap: true
             fillMode: Image.PreserveAspectFit
             clip: true
             Component.onCompleted: {
                source = Qt.binding(function() { return getLogoPath(model_brand); })
             }
           }

            Text{
                y: (st_item_height/2 - st_item_font_sz)
                x: 0 + st_item_height*1.5
                clip: true
                color: st_font_color
                font.pixelSize: st_item_font_sz
                text: modelData.name
                font.bold: modelData.name === preselected_vehicle_model ? true : false
            }

            onClicked :{
                preselected_vehicle_model = modelData.name;
                modelSelected(modelData.name, modelData.value);
            }
        }
    }

}
