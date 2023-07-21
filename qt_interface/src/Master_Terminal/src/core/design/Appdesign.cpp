#include "Appdesign.h"

#ifdef QT_IN_USE
void AppDesign::default_init(){
    setSizePreset(Sp_M);
    setColorPreset();
}

ContainerDesignInt *AppDesign::getIntContainerPointer(const QString _assignment, const QString _item_element){
    ContainerDesignInt *containerPointer = nullptr;
    /********************** General Design Items ******************************/
    if((_assignment == assignment_GeneralDesign)){
        /****** Font ******/
        if((_item_element == itemElement_Font)){
            containerPointer = &p_GeneralDesign_Font;
        }
        /****** Height ******/
        else if((_item_element == itemElement_Height)){
            containerPointer = &p_GeneralDesign_Height;
        }
    }

    /**************************** Simple Items ********************************/
    else if((_assignment == assignment_SimpleItems)){
        /****** Font ******/
        if((_item_element == itemElement_Font)){
            containerPointer = &p_SimpleItems_Font;
        }
        /****** Width ******/
        else if((_item_element == itemElement_Width)){
            containerPointer = &p_SimpleItems_Width;
        }
    }
    /**************************** View Scale ********************************/
    else if((_assignment == assignment_ViewScale)){
        /****** Height ******/
        if((_item_element == itemElement_Height)){
            containerPointer = &p_ViewScale_Height;
        }
    }

    /**************************** Base Items ********************************/
    else if((_assignment == assignment_Base)){
        /****** Height ******/
        if((_item_element == itemElement_Height)){
            containerPointer = &p_Base_Height;
        }
        /****** Width ******/
        else if((_item_element == itemElement_Width)){
            containerPointer = &p_Base_Width;
        }
        /****** Font ******/
        if((_item_element == itemElement_Font)){
            containerPointer = &p_Base_Font;
        }
    }
    return containerPointer;
}
ContainerDesignFloat *AppDesign::getFloatContainerPointer(const QString _assignment, const QString _item_element){
    ContainerDesignFloat *containerPointer = nullptr;

    /********************** General Design Items ******************************/
    if((_assignment == assignment_GeneralDesign)){
        /****** Ratio ******/
        if((_item_element == itemElement_Ratio)){
            containerPointer = &p_GeneralDesign_Ratio;
        }
        /****** Gradient ******/
        else if((_item_element == itemElement_Gradient)){
            containerPointer = &p_GeneralDesign_Gradient;
        }

    }

    /**************************** Simple Items ********************************/
    else if((_assignment == assignment_SimpleItems)){
        /****** HeightToWidth ******/
        if((_item_element == itemElement_HeightToWidth)){
            containerPointer = &p_SimpleItems_HeightToWidth;
        }
        /****** Ratio ******/
        else if((_item_element == itemElement_Ratio)){
            containerPointer = &p_SimpleItems_Ratio;
        }
    }
    /**************************** View Scale ********************************/

    /**************************** Base Items ********************************/
    else if((_assignment == assignment_Base)){
        /****** Gradient ******/
        if((_item_element == itemElement_Gradient)){
            containerPointer = &p_Base_Gradient;
        }
        /****** Ration ******/
        else if((_item_element == itemElement_Ratio)){
            containerPointer = &p_Base_Ratio;
        }
    }
    return containerPointer;
}
ContainerDesignQstring *AppDesign::getQstringContainerPointer(const QString _assignment, const QString _item_element){
    ContainerDesignQstring *containerPointer = nullptr;

    /********************** General Design Items ******************************/
    if((_assignment == assignment_GeneralDesign)){
        /****** Color ******/
        if((_item_element == itemElement_Color)){
            containerPointer = &p_GeneralDesign_Color;
        }
    }

    /**************************** Simple Items ********************************/
    else if((_assignment == assignment_SimpleItems)){
        /****** Color ******/
        if((_item_element == itemElement_Color)){
            containerPointer = &p_SimpleItems_Color;
        }
    }
    /**************************** Base Items ********************************/
    else if((_assignment == assignment_Base)){
        /****** Color ******/
        if((_item_element == itemElement_Color)){
            containerPointer = &p_Base_Color;
        }
    }
    return containerPointer;
}

int AppDesign::getIntValue(const QString _assignment, const QString _item_element, const QString _name){
    auto containerPtr = getIntContainerPointer(_assignment, _item_element);

    if((containerPtr!= nullptr) & (containerPtr->isKeyInited(_name))){
        return containerPtr->getItem(_name);
    }
    else{
        return 0;
    }
}


void AppDesign::setIntValue(const QString _assignment, const QString _item_element, const QString _name, int _value){
    auto *containerPtr = getIntContainerPointer(_assignment, _item_element);
    if(containerPtr== nullptr){
        return;
    }
    if(containerPtr->isKeyInited(_name)){
        containerPtr->replaceItem(_name, _value);
    }
    else{
        containerPtr->addItem(_name, _value);
    }
}

QString AppDesign::getStringValue(const QString _assignment, const QString _item_element, const QString _name){
    auto containerPtr = getQstringContainerPointer(_assignment, _item_element);

    if((containerPtr!= nullptr) & (containerPtr->isKeyInited(_name))){
        return containerPtr->getItem(_name);
    }
    else{
        return "";
    }
}
void AppDesign::setStringValue(const QString _assignment, const QString _item_element, const QString _name, QString _value){
    auto containerPtr = getQstringContainerPointer(_assignment, _item_element);
    if(containerPtr == nullptr) return;
    if(containerPtr->isKeyInited(_name)){
        containerPtr->replaceItem(_name, _value);
    }
    else containerPtr->addItem(_name, _value);
}

float AppDesign::getFloatValue(const QString _assignment, const QString _item_element, const QString _name){
    auto containerPtr = getFloatContainerPointer(_assignment, _item_element);
    if((containerPtr!= nullptr) & (containerPtr->isKeyInited(_name))){
        return containerPtr->getItem(_name);
    }
    else{
        return 0;
    }
}

void AppDesign::setFloatValue(const QString _assignment, const QString _item_element, const QString _name, float _value){
    auto containerPtr = getFloatContainerPointer(_assignment, _item_element);
    if(containerPtr == nullptr) return;
    if(containerPtr->isKeyInited(_name)){
        containerPtr->replaceItem(_name, _value);
    }
    else containerPtr->addItem(_name, _value);
}

void AppDesign::print(){
    DEBUG_OUT("****************** AppDesign ******************");
    p_ViewScale_Height.print();
    p_GeneralDesign_Font.print();
    p_GeneralDesign_Height.print();
    p_GeneralDesign_Ratio.print();
    p_GeneralDesign_Gradient.print();

    p_GeneralDesign_Color.print();
    p_SimpleItems_Font.print();
    p_SimpleItems_Width.print();

    p_SimpleItems_HeightToWidth.print();
    p_SimpleItems_Ratio.print();

    p_SimpleItems_Color.print();

    p_Base_Height.print();
    p_Base_Width.print();
    p_Base_Font.print();
    p_Base_Gradient.print();
    p_Base_Color.print();
    p_Base_Ratio.print();
}


void AppDesign::setSizePreset(int size_preset){
    /*** View Scale ***/
    /* int */
    p_ViewScale_Height.addItem(name_Container, default_ViewScale_Height_Container[size_preset]);

    /************** General Design Items **************/
    /* int */
    p_GeneralDesign_Font.addItem(name_ToolBar, default_GeneralDesign_Font_ToolBar[size_preset]);
    p_GeneralDesign_Font.addItem(name_DrawerTitleFrame, default_GeneralDesign_Font_DrawerTitleFrame[size_preset]);
    p_GeneralDesign_Font.addItem(name_DrawerItemText, default_GeneralDesign_Font_DrawerItemText[size_preset]);
    p_GeneralDesign_Height.addItem(name_ToolBar, default_GeneralDesign_Height_ToolBar[size_preset]);
    p_GeneralDesign_Height.addItem(name_DrawerTitleFrame, default_GeneralDesign_Height_DrawerTitleFrame[size_preset]);
    p_GeneralDesign_Height.addItem(name_DrawerItemIcons, default_GeneralDesign_Height_DrawerItemIcons[size_preset]);
    /* string */

    /* float */
    p_GeneralDesign_Ratio.addItem(name_TitleToToolbar, default_GeneralDesign_Ratio_TitleToToolbar[size_preset]);
    p_GeneralDesign_Ratio.addItem(name_ScreenAdjSideCrop, default_GeneralDesign_Ratio_ScreenAdjSideCrop[size_preset]);
    p_GeneralDesign_Ratio.addItem(name_ScreenAdjVertContainerCrop, default_GeneralDesign_Ratio_ScreenAdjVertContainerCrop[size_preset]);
    p_GeneralDesign_Gradient.addItem(name_Backstage, default_GeneralDesign_Gradient_Backstage);

    /************** Simple Items **************/
    /* int */
    p_SimpleItems_Font.addItem(name_Main, default_SimpleItems_Font_Main[size_preset]);
    p_SimpleItems_Width.addItem(name_ButtonBorder, default_SimpleItems_Width_ButtonBorder[size_preset]);
    /* float */
    p_SimpleItems_HeightToWidth.addItem(name_Button, default_SimpleItems_HeightToWidth_Button[size_preset]);
    p_SimpleItems_Ratio.addItem(name_ButtonFont, default_SimpleItems_Ratio_ButtonFont[size_preset]);
    p_SimpleItems_Ratio.addItem(name_ButtonOnPress, default_SimpleItems_Ratio_ButtonOnPress[size_preset]);
    /* string */

    /************** Base **************/
    /* int */
    p_Base_Height.addItem(name_Navibar, default_Base_Height_Navibar[size_preset]);
    p_Base_Width.addItem(name_ButtonBorder, default_Base_Width_ButtonBorder[size_preset]);
    p_Base_Font.addItem(name_TerminalSz, default_Base_Font_TerminalSz[size_preset]);
    p_Base_Width.addItem(name_ItemFrame, default_Base_Width_ItemFrame[size_preset]);
    p_Base_Height.addItem(name_Item, default_Base_Height_Item[size_preset]);
    p_Base_Ratio.addItem(name_ButtonFont, default_Base_Ratio_ButtonFont[size_preset]);
    p_Base_Height.addItem(name_PageGrid, default_Base_Height_PageGrid[size_preset]);


    /* float */
    p_Base_Gradient.addItem(name_PositionA, default_Base_Gradient_PositionA);
    p_Base_Gradient.addItem(name_PositionB, default_Base_Gradient_PositionB);
    /* string */
}

void AppDesign::setColorPreset(){
    /*** View Scale ***/
    /* int */

    /************** General Design Items **************/
    /* int */
    /* string */
    p_GeneralDesign_Color.addItem(name_ToolBar, default_GeneralDesign_Color_ToolBar);
    p_GeneralDesign_Color.addItem(name_ToolBarText, default_GeneralDesign_Color_ToolBarText);
    p_GeneralDesign_Color.addItem(name_DrawerFrame, default_GeneralDesign_Color_DrawerFrame);
    p_GeneralDesign_Color.addItem(name_DrawerItemText, default_GeneralDesign_Color_DrawerItemText);
    p_GeneralDesign_Color.addItem(name_DrawerFrameText, default_GeneralDesign_Color_DrawerFrameText);
    /* float */


    /************** Simple Items **************/
    /* int */

    /* float */

    /* string */
    p_SimpleItems_Color.addItem(name_FrameActive, default_SimpleItems_Color_FrameActive);
    p_SimpleItems_Color.addItem(name_FrameInactive, default_SimpleItems_Color_FrameInactive);
    p_SimpleItems_Color.addItem(name_FrameDisabled, default_SimpleItems_Color_FrameDisabled);
    p_SimpleItems_Color.addItem(name_Button, default_SimpleItems_Color_Button);
    p_SimpleItems_Color.addItem(name_ButtonText, default_SimpleItems_Color_ButtonText);

    /************** Base **************/
    /* int */

    /* float */

    /* string */
    p_Base_Color.addItem(name_Icon, default_Base_Color_Icon);
    p_Base_Color.addItem(name_IconOverlay, default_Base_Color_IconOverlay);
    p_Base_Color.addItem(name_BaseFont, default_Base_Color_BaseFont);
    // p_Base_Color.addItem(name_GradientBackground, default_Base_Color_GradientBackground);
    p_Base_Color.addItem(name_Frame, default_Base_Color_Frame);
    p_Base_Color.addItem(name_Canva, default_Base_Color_Canva);
    p_Base_Color.addItem(name_ButtonCanva, default_Base_Color_ButtonCanva);
    p_Base_Color.addItem(name_FrameLight, default_Base_Color_FrameLight);

}

QDataStream& operator << (QDataStream& d, const AppDesign& ad){
    d << ad.p_ViewScale_Height;

    d << ad.p_GeneralDesign_Font;
    d << ad.p_GeneralDesign_Height;
    /* string */
    d << ad.p_GeneralDesign_Color;
    /* float */
    d << ad.p_GeneralDesign_Ratio;
    d << ad.p_GeneralDesign_Gradient;

    /*** Simple Items ***/
    /* int */
    d << ad.p_SimpleItems_Font;
    d << ad.p_SimpleItems_Width;
    /* float */
    d << ad.p_SimpleItems_HeightToWidth;
    d << ad.p_SimpleItems_Ratio;
    /* string */
    d << ad.p_SimpleItems_Color;

    /*** Base Items ***/
    d << ad.p_Base_Height;
    d << ad.p_Base_Width;
    d << ad.p_Base_Font;
    /* float */
    d << ad.p_Base_Gradient;
    d << ad.p_Base_Ratio;
    /* string */
    d << ad.p_Base_Color;
    return d;
}

QDataStream& operator >> (QDataStream& d, AppDesign& ad){
    d >> ad.p_ViewScale_Height;

    d >> ad.p_GeneralDesign_Font;
    d >> ad.p_GeneralDesign_Height;
    /* string */
    d >> ad.p_GeneralDesign_Color;
    /* float */
    d >> ad.p_GeneralDesign_Ratio;
    d >> ad.p_GeneralDesign_Gradient;

    /*** Simple Items ***/
    /* int */
    d >> ad.p_SimpleItems_Font;
    d >> ad.p_SimpleItems_Width;
    /* float */
    d >> ad.p_SimpleItems_HeightToWidth;
    d >> ad.p_SimpleItems_Ratio;
    /* string */
    d >> ad.p_SimpleItems_Color;

    /*** Base Items ***/
    d >> ad.p_Base_Height;
    d >> ad.p_Base_Width;
    d >> ad.p_Base_Font;
    /* float */
    d >> ad.p_Base_Gradient;
    d >> ad.p_Base_Ratio;
    /* string */
    d >> ad.p_Base_Color;
    return d;
}
#endif
