#ifndef APPDESIGN_H
#define APPDESIGN_H
#include <QDebug>
#include "Containerdesign.h"

#include <iostream>
#include <map>
// #include "../../engine/file_manager/SimpleSerializer.h"

#ifdef QT_IN_USE
class AppDesign{

    /*************** Assignment ***************/
    static inline const QString assignment_GeneralDesign = "GeneralDesign";
    static inline const QString assignment_SimpleItems = "SimpleItems";
    static inline const QString assignment_ViewScale = "ViewScale";
    static inline const QString assignment_Base = "Base";

    /*************** Target element ***************/
    static inline const QString itemElement_Font = "Font";
    static inline const QString itemElement_Color = "Color";
    static inline const QString itemElement_Height = "Height";
    static inline const QString itemElement_HeightToWidth = "HeightToWidth";
    static inline const QString itemElement_Ratio = "Ratio";
    static inline const QString itemElement_Width = "Width";
    static inline const QString itemElement_Gradient = "Gradient";

    /*************** Var name ***************/
    static inline const QString name_Main = "Main";
    static inline const QString name_ToolBar = "ToolBar";
    static inline const QString name_ToolBarText = "ToolBarText";
    static inline const QString name_DrawerTitleFrame = "DrawerTitleFrame";
    static inline const QString name_DrawerItemIcons = "DrawerItemIcons";
    static inline const QString name_DrawerItemText = "DrawerItemText";
    static inline const QString name_DrawerFrame = "DrawerFrame";
    static inline const QString name_DrawerFrameText = "DrawerFrameText";
    static inline const QString name_ButtonBorder = "ButtonBorder";
    static inline const QString name_FrameInactive = "FrameInactive";
    static inline const QString name_FrameActive = "FrameActive";
    static inline const QString name_ButtonText = "ButtonText";
    static inline const QString name_FrameDisabled = "FrameDisabled";
    static inline const QString name_Button = "Button";
    static inline const QString name_ButtonFont = "ButtonFont";
    static inline const QString name_ButtonOnPress = "ButtonOnPress";
    static inline const QString name_TitleToToolbar = "TitleToToolbar";
    static inline const QString name_ScreenAdjSideCrop = "ScreenAdjSideCrop";
    static inline const QString name_ScreenAdjVertContainerCrop = "ScreenAdjVCrop";
    static inline const QString name_Container = "Container";
    static inline const QString name_Navibar = "Navibar";
    static inline const QString name_Backstage = "Backstage";
    static inline const QString name_Icon = "Icon";
    static inline const QString name_IconOverlay = "IconOverlay";
    static inline const QString name_BaseFont = "BaseFont";
    static inline const QString name_GradientBackground = "GradientBackground";
    static inline const QString name_PositionA = "PositionA";
    static inline const QString name_PositionB = "PositionB";
    static inline const QString name_Frame = "Frame";
    static inline const QString name_Canva = "Canva";
    static inline const QString name_TerminalSz = "TerminalSz";
    static inline const QString name_ItemFrame = "ItemFrame";
    static inline const QString name_Item = "Item";
    static inline const QString name_FrameLight = "FrameLight";
    static inline const QString name_ButtonCanva = "ButtonCanva";
    static inline const QString name_PageGrid = "PageGrid";

    /*** View Scale ***/
    /* int */
    static inline const int default_ViewScale_Height_Container[] = {
        40, /* Sp_S */
        45, /* Sp_M */
        50, /* Sp_L */
        55, /* Sp_XL */
        60,
        65};

    /*** General Design Items ***/
    /* int */
    static inline const int default_GeneralDesign_Font_ToolBar[] = {
        85, /* Sp_S */
        90, /* Sp_M */
        95, /* Sp_L */
        100, /* Sp_XL */
        105,
        110};
    static inline const int default_GeneralDesign_Font_DrawerTitleFrame[] = {
        36, /* Sp_S */
        40, /* Sp_M */
        44, /* Sp_L */
        48, /* Sp_XL */
        52,
        56};
    static inline const int default_GeneralDesign_Font_DrawerItemText[] = {
        25, /* Sp_S */
        30, /* Sp_M */
        35, /* Sp_L */
        40, /* Sp_XL */
        45,
        45};
    static inline const int default_GeneralDesign_Height_DrawerTitleFrame[] = {
        215, /* Sp_S */
        220, /* Sp_M */
        225, /* Sp_L */
        230, /* Sp_XL */
        235,
        240};
    static inline const int default_GeneralDesign_Height_DrawerItemIcons[] = {
        45, /* Sp_S */
        50, /* Sp_M */
        55, /* Sp_L */
        60, /* Sp_XL */
        65,
        70};
    static inline const int default_GeneralDesign_Height_ToolBar[] = {
        44, /* Sp_S */
        52, /* Sp_M */
        60, /* Sp_L */
        68, /* Sp_XL */
        76,
        88};
    /* string */
    static inline const QString default_GeneralDesign_Color_ToolBar = "#04578B";
    static inline const QString default_GeneralDesign_Color_ToolBarText = "#F0F0C0";
    static inline const QString default_GeneralDesign_Color_DrawerFrame = "#006CFF";
    static inline const QString default_GeneralDesign_Color_DrawerItemText = "#000000";
    static inline const QString default_GeneralDesign_Color_DrawerFrameText = "#F0F0C0";
    /* float */
    static inline const float default_GeneralDesign_Ratio_TitleToToolbar[] = {
        1.70, /* Sp_S */
        1.60, /* Sp_M */
        1.50, /* Sp_L */
        1.40, /* Sp_XL */
        1.30,
        1.20};
    static inline const float default_GeneralDesign_Ratio_ScreenAdjSideCrop[] = {
        0.97, /* Sp_S */
        0.96, /* Sp_M */
        0.95, /* Sp_L */
        0.94, /* Sp_XL */
        0.93,
        0.92};
    static inline const float default_GeneralDesign_Ratio_ScreenAdjVertContainerCrop[] = {
        0.92, /* Sp_S */
        0.90, /* Sp_M */
        0.88, /* Sp_L */
        0.86, /* Sp_XL */
        0.85,
        0.85};
    static inline const float default_GeneralDesign_Gradient_Backstage = 1.20;

    /*** Simple Items ***/
    /* int */
    static inline const int default_SimpleItems_Font_Main[] = {
        28, /* Sp_S */
        30, /* Sp_M */
        32, /* Sp_L */
        34, /* Sp_XL */
        34,
        34};
    static inline const int default_SimpleItems_Width_ButtonBorder[] = {
        2, /* Sp_S */
        2, /* Sp_M */
        2, /* Sp_L */
        3, /* Sp_XL */
        3,
        3};
    /* float */
    static inline const float default_SimpleItems_HeightToWidth_Button[] = {
        1.50, /* Sp_S */
        1.50, /* Sp_M */
        1.50, /* Sp_L */
        1.50, /* Sp_XL */
        1.50,
        1.50};
    static inline const float default_SimpleItems_Ratio_ButtonFont[] = {
        0.30, /* Sp_S */
        0.35, /* Sp_M */
        0.40, /* Sp_L */
        0.45, /* Sp_XL */
        0.50,
        0.50};
    static inline const float default_SimpleItems_Ratio_ButtonOnPress[] = {
        1.80, /* Sp_S */
        1.90, /* Sp_M */
        2.00, /* Sp_L */
        2.10, /* Sp_XL */
        2.15,
        2.20};
    /* string */
    static inline const QString default_SimpleItems_Color_FrameActive = "#FF6C00";
    static inline const QString default_SimpleItems_Color_FrameInactive = "#006CFF";
    static inline const QString default_SimpleItems_Color_FrameDisabled = "#444444";
    static inline const QString default_SimpleItems_Color_Button = "#F0F0C0";
    static inline const QString default_SimpleItems_Color_ButtonText = "#000000";

    /*** Base Items ***/
    /* int */
    static inline const int default_Base_Height_Navibar[] = {
        110, /* Sp_S */
        120, /* Sp_M */
        130, /* Sp_L */
        140, /* Sp_XL */
        145,
        150};
    static inline const int default_Base_Width_ButtonBorder[] = {
        1, /* Sp_S */
        1, /* Sp_M */
        1, /* Sp_L */
        2, /* Sp_XL */
        2,
        2};
    static inline const int default_Base_Font_TerminalSz[] = {
        12, /* Sp_S */
        15, /* Sp_M */
        17, /* Sp_L */
        19, /* Sp_XL */
        21,
        24};
    static inline const int default_Base_Width_ItemFrame[] = {
        380, /* Sp_S */
        410, /* Sp_M */
        420, /* Sp_L */
        425, /* Sp_XL */
        430,
        435};
    static inline const int default_Base_Height_Item[] = {
        36, /* Sp_S */
        40, /* Sp_M */
        44, /* Sp_L */
        48, /* Sp_XL */
        52,
        56};

    static inline const float default_Base_Ratio_ButtonFont[] = {
        0.36, /* Sp_S */
        0.40, /* Sp_M */
        0.44, /* Sp_L */
        0.48, /* Sp_XL */
        0.52,
        0.56};
    static inline const int default_Base_Height_PageGrid[] = {
        75, /* Sp_S */
        80, /* Sp_M */
        85, /* Sp_L */
        90, /* Sp_XL */
        92,
        95};

    /* float */
    static inline const float default_Base_Gradient_PositionA = 0.25;
    static inline const float default_Base_Gradient_PositionB = 1.75;
    /* string */
    static inline const QString default_Base_Color_Icon = "#0F44F0";
    static inline const QString default_Base_Color_IconOverlay = "#BBBBBB";
    static inline const QString default_Base_Color_BaseFont = "#F0F0C0";
    // static inline const string default_Base_Color_GradientBackground = "#9AAAA3";
    static inline const QString default_Base_Color_Frame = "#4433EE";
    static inline const QString default_Base_Color_Canva = "#04578B";
    static inline const QString default_Base_Color_ButtonCanva = "#2211A3";
    static inline const QString default_Base_Color_FrameLight = "#FFFFFF";

public:
    explicit AppDesign(){
    };
    ~AppDesign(){};

    enum SizePreset {
        Sp_S = 0,
        Sp_M = 1,
        Sp_L = 2,
        Sp_XL = 3,
        Sp_XXL = 4,
        Sp_XXXL = 5
    };


    void default_init();

    void setSizePreset(int size_preset);
    void setColorPreset();
    void print();

    /********************************************************/
    /******************** Setters/Getters ******************/
    /********************************************************/
  //  template<typename T>
  //  ContainerDesign<T> *getContainerPointer(const QString _assignment, const QString _item_element);
    ContainerDesignInt *getIntContainerPointer(const QString _assignment, const QString _item_element);
    ContainerDesignFloat *getFloatContainerPointer(const QString _assignment, const QString _item_element);
    ContainerDesignQstring *getQstringContainerPointer(const QString _assignment, const QString _item_element);

    int getIntValue(const QString _assignment, const QString _item_element, const QString _name);
    void setIntValue(const QString _assignment, const QString _item_element, const QString _name, int _value);
    QString getStringValue(const QString _assignment, const QString _item_element, const QString _name);
    void setStringValue(const QString _assignment, const QString _item_element, const QString _name, QString _value);
    float getFloatValue(const QString _assignment, const QString _item_element, const QString _name);
    void setFloatValue(const QString _assignment, const QString _item_element, const QString _name, float _value);

    friend QDataStream& operator >>( QDataStream& d, AppDesign& ad);
    friend QDataStream& operator << (QDataStream& d, const AppDesign& ad);
    AppDesign& operator= (const AppDesign &cs){
        if (this == &cs)
            return *this;

        p_ViewScale_Height = cs.p_ViewScale_Height;
        p_GeneralDesign_Font = cs.p_GeneralDesign_Font;
        p_GeneralDesign_Height = cs.p_GeneralDesign_Height;
        p_GeneralDesign_Color = cs.p_GeneralDesign_Color;
        p_GeneralDesign_Ratio = cs.p_GeneralDesign_Ratio;
        p_GeneralDesign_Gradient = cs.p_GeneralDesign_Gradient;
        p_SimpleItems_Font = cs.p_SimpleItems_Font;
        p_SimpleItems_Width = cs.p_SimpleItems_Width;
        p_SimpleItems_HeightToWidth = cs.p_SimpleItems_HeightToWidth;
        p_SimpleItems_Ratio = cs.p_SimpleItems_Ratio;
        p_SimpleItems_Color = cs.p_SimpleItems_Color;
        p_Base_Height = cs.p_Base_Height;
        p_Base_Width = cs.p_Base_Width;
        p_Base_Font = cs.p_Base_Font;
        p_Base_Gradient = cs.p_Base_Gradient;
        p_Base_Ratio = cs.p_Base_Ratio;
        p_Base_Color = cs.p_Base_Color;

        return *this;
    }

private:
    /*** View Scale ***/
    /* int */
    ContainerDesignInt p_ViewScale_Height = ContainerDesignInt("ViewScale Height");

    /*** General Design Items ***/
    /* int */
    ContainerDesignInt p_GeneralDesign_Font = ContainerDesignInt("GeneralDesign Font");
    ContainerDesignInt p_GeneralDesign_Height = ContainerDesignInt("GeneralDesign Height");
    /* string */
    ContainerDesignQstring p_GeneralDesign_Color = ContainerDesignQstring("GeneralDesign Color");
    /* float */
    ContainerDesignFloat p_GeneralDesign_Ratio = ContainerDesignFloat("GeneralDesign Ratio");
    ContainerDesignFloat p_GeneralDesign_Gradient = ContainerDesignFloat("GeneralDesign Gradient");

    /*** Simple Items ***/
    /* int */
    ContainerDesignInt p_SimpleItems_Font = ContainerDesignInt("SimpleItems Font");
    ContainerDesignInt p_SimpleItems_Width = ContainerDesignInt("SimpleItems Width");
    /* float */
    ContainerDesignFloat p_SimpleItems_HeightToWidth = ContainerDesignFloat("SimpleItems HeightToWidth");
    ContainerDesignFloat p_SimpleItems_Ratio = ContainerDesignFloat("SimpleItems Ratio");
    /* string */
    ContainerDesignQstring p_SimpleItems_Color = ContainerDesignQstring("SimpleItems Color");

    /*** Base Items ***/
    /* int */
    ContainerDesignInt p_Base_Height = ContainerDesignInt("Base Height");
    ContainerDesignInt p_Base_Width = ContainerDesignInt("Base Width");
    ContainerDesignInt p_Base_Font = ContainerDesignInt("Base Font");
    /* float */
    ContainerDesignFloat p_Base_Gradient = ContainerDesignFloat("Base Gradient");
    ContainerDesignFloat p_Base_Ratio = ContainerDesignFloat("Base Ratio");

    /* string */
    ContainerDesignQstring p_Base_Color = ContainerDesignQstring("Base Color");

};


QDataStream& operator << (QDataStream& d, const AppDesign& ad);
QDataStream& operator >> (QDataStream& d, AppDesign& ad);

#endif


#endif // APPDESIGN_H
