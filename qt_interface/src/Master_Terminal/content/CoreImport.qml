pragma Singleton
import QtQuick

import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

Item {
    id: root


    readonly property string app_name: "CAN/LIN terminal"
    readonly property string app_author: "Alexander Svetlichnyy"
    readonly property string app_date: " "
    // readonly property string app_version: core.interface_version
    property string app_description: qsTr("Microcontroller user interface designed for CAN bus and LIN bus research and reprogramming. Based on a CAN gateway implemented with STM32 microcontrollers and flash memory. This multi-platform application (Android, PC) was created using Qt.")

    readonly property int appWidth: 840
    readonly property int appHeight: 960
    readonly property int mainContentHeight: appHeight - _GeneralDesign_Height_ToolBar - CoreImport._Base_Height_Navibar
    readonly property int mainContentHeightCollapsed: appHeight - _GeneralDesign_Height_ToolBar - CoreImport._Base_Height_CollapsedNavibar

    readonly property bool albumOrientation: false

    /********* alias ********/
    readonly property string flag_files_path: "./png/flags/"
    readonly property string brand_logos_path: "./png/model_logos/"
    readonly property string navibar_icons_path: "./png/Navibar/"
    readonly property string toolbar_icons_path: "./png/Toolbar/"
    readonly property string pages_path: "pages/"
    readonly property string img_path: "png/"
    readonly property string draweritem_group: "DrawerItem_"
    readonly property string base_group: "Base_"
    readonly property string default_page: "Main"



    //********************************************************
    //**********    Pixel density   **************************
    property int dpi: Screen.pixelDensity * 25.4

    function dp(x){
        if(dpi < 120) {
            return x;
        } else {
            return x*(dpi/160);
        }
    }


    enum NavibarStatus {
        Navibar_collapsed = 0,
        Navibar_regular = 1,
        Navibar_expanded = 2
    }
    property int navibar_status: 1

    function getPageGroup(page){
        if (page.indexOf(draweritem_group) >= 0) return draweritem_group;
        else return base_group;
    }

    property string current_user: core.getUserProfileValue(CoreImport.ProfileMembers.Name)
    property string current_language: core.getUserProfileValue(CoreImport.ProfileMembers.Language)

    enum UpdateMode {
        WebUpdate = 0,
        FileUpdate = 1,
        RecoveryOverride = 2
    }

    enum CoreLoaderMode {
        LmUserProfile = 0,
        LmAppDesign = 1,
        LmCoreStatus = 2
    }

    enum ProfileMembers {
        Name = 0,
        Language = 1,
        Email = 2,
        Phone = 3
    }

    enum ConnectionStatus{
        Disconnected = 0x00,
        Connected = 0x01,
        Failed = 0x02
    }

    enum ProfileMenuMode {
        Edit = 0,
        New = 1,
        Select = 3,
        Delete = 4
    }

    /*************** Design presets ***************/
    /* not used */
    enum DesignPresets {
        S = 0,
        M = 1,
        L = 2,
        XL = 3,
        XXL = 4,
        XXXL = 5
    }

    readonly property var design_preset_names:
        ["S",
        "M",
        "L",
        "XL",
        "XXL",
        "XXXL"];

    //=============================================================================
    //============================ Import from stm32 ==============================
    //=============================================================================
    /*************** Calibrator specific ***************/
    property string current_vehicle_model: "not available"
    readonly property int _ELP_VEHICLE_SET_SPEEDOMETER_MLT: 0x00000A03
    readonly property int _ELP_VEHICLE_SET_ODOMETER_MLT: 0x00000A04
    readonly property int _ELP_VEHICLE_SET_CRUISE_MLT: 0x00000A05
    readonly property int _ELP_VEHICLE_SET_TYRES_THRESHOLD: 0x00000A06
    readonly property int _ELP_VEHICLE_SET_MODE: 0x00000A07	/* @S00000A07@?08@!00000102@E reset 0x02 and set 0x01 */
    /*** Odo freeze mask ***/
    readonly property int _ELP_VEHICLE_SET_ODO_FREEZE_MSK:   0x0001
    readonly property int _ELP_VEHICLE_RESET_ODO_FREEZE_MSK: 0x0100
    /*** Connection test mask ***/
    readonly property int _ELP_VEHICLE_SET_TEST_MODE_MSK:    0x0002
    readonly property int _ELP_VEHICLE_RESET_TEST_MODE_MSK:  0x0200

    /*
    readonly property int  _CALIBRATOR_DEFAULT_MODE:			0x00000000
    readonly property int  _CALIBRATOR_ODO_FREEZE_MODE:     	0x01
    readonly property int  _CALIBRATOR_TEST_MODE:               0x02
    */


    /*************** Addresses defs ***************/

    readonly property int _VEHICLE_SETTINGS_ADDRESS : 0x000000 // VehicleStruct
    readonly property int _DEVICE_MODES_ADDRESS	: 0x010000 // uDeviceModel, can_override_status theOverrideStatus
    readonly property int _DEVICE_OVERRIDE_FILTER_SETTINGS_ADDRESS : 0x010200

    readonly property int _BOOTLOADER_EMERGENCY_PROGRAMM_ADDR : 0x020000
    readonly property int _BOOTLOADER_EMERGENCY_PROGRAMM_SIZE_ADDR : (0x030000 - 0x04)

    readonly property int _BOOTLOADER_UPDATE_PROGRAMM_ADDR : 0x030000
    readonly property int _BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR : (0x040000 - 0x04)

    readonly property int _FREE_MEMSPACE_ADDRESS : 0x040000

    /*************** Base items list ***************/
    readonly property var base_items_filenames:
        [base_group + default_page,
        base_group + "SelectModel",
        base_group + "AdjustSpeedMlt",
        base_group + "AdjustOdoMlt",
        base_group + "AdjustCruiseMlt",
        base_group + "AdjustTyresThreshold",
        base_group + "TestVehicleConnection",
        base_group + "ManualOverride",
        base_group + "MemoryMonitor",
        base_group + "MemoryWrite",
        base_group + "CAN_Override",
        base_group + "CAN_Scanner",
        base_group + "Device_Modes",
        base_group + "LIN_Override",
        base_group + "Update",
        base_group + "AndroidJNIDebug"];

    /*************** Base Items *******************/
    property var base_items:
        [qsTr("Main"),
        qsTr("SelectModel"),
        qsTr("Speedometer"),
        qsTr("Odometer"),
        qsTr("Cruise"),
        qsTr("Tyres threshold"),
        qsTr("Dashboard test"),
        qsTr("Manual Override"),
        qsTr("Memory Monitor"),      
        qsTr("Memory Write"),
        qsTr("CAN Override"),
        qsTr("CAN Scanner"),
        qsTr("Device Modes"),
        qsTr("LIN Override"),
        qsTr("Update"),
        qsTr("AndroidJNIDebug")];

    /*************** Drawer Items *******************/
    property var drawer_items:
        [qsTr("Settings"),
        qsTr("User Profile"),
        qsTr("View"),
        qsTr("Language"),
        qsTr("Debug"),
        qsTr("Help"),
        qsTr("About")];

    /*************** Drawer items list ***************/
    readonly property var drawer_items_filenames:
        [draweritem_group + "Settings",
        draweritem_group + "UserProfile",
        draweritem_group + "View",
        draweritem_group + "Language",
        draweritem_group + "Debug",
        draweritem_group + "Help",
        draweritem_group + "About"];

    /* Supported languages
        flags png are stored in content\pages\png\flags */

    readonly property var supported_languages:
        ["English",
        "Ukrainian",
        "Russian",
        "Chinese",
        "Czech",
        "Kyrgizian"];

    property string spd_clbr_available_description: qsTr("Speedometer calibration available.")
    property string spd_clbr_pulse_available_description: qsTr("Speedometer calibration is available via pulse calibrator.")
    property string spd_clbr_unavailable_description: qsTr("Speedometer calibration unavailable.")
    property string odo_clbr_pulse_available_description: qsTr("Ododometer calibration is available via pulse calibrator.")
    property string odo_clbr_available_description: qsTr("Ododometer calibration available. \n Notice: the greater the distance of the test, the more percision shown in odometer readings. Some models' odometers may ignore the speed below 1 km/h. Press \"Freeze\" to stop odometer.")
    property string odo_clbr_unavailable_description: qsTr("Ododometer calibration unavailable separatedly from speedometer. Use the speedometer calibration.")
    property string crs_clbr_available_description: qsTr("Cruise control calibration available.")
    property string crs_clbr_unavailable_description: qsTr("Cruise control calibration unavailable.")
    property string tyr_thr_available_description: qsTr("Tyres pressure threshold customization available.")
    property string tyr_thr_lin_available_description: qsTr("Tyres pressure threshold customization is available via LIN.")
    property string tyr_thr_unavailable_description: qsTr("Tyres pressure threshold customization unavailable.")
    property string test_available_description: qsTr("Press the button to check wires connection. When connected properly the speedometer dial would show a test value.")
    property string test_unavailable_description: qsTr("Connection test unavailable.")



    function retranslateUi() {
        app_description = qsTr("Microcontroller user interface designed for CAN bus and LIN bus research and reprogramming. Based on a CAN gateway implemented with STM32 microcontrollers and flash memory. This multi-platform application (Android, PC) was created using Qt.");
        drawer_items =
                [qsTr("Settings"),
                 qsTr("User Profile"),
                 qsTr("View"),
                 qsTr("Language"),
                 qsTr("Debug"),
                 qsTr("Help"),
                 qsTr("About")];
        base_items =
                [qsTr("Main"),
                 qsTr("SelectModel"),
                 qsTr("Speedometer"),
                 qsTr("Odometer"),
                 qsTr("Cruise"),
                 qsTr("Tyres threshold"),
                 qsTr("Dashboard test"),
                 qsTr("Manual Override"),
                 qsTr("Memory Monitor"),
                 qsTr("Memory Write"),
                 qsTr("CAN Override"),
                 qsTr("CAN Scanner"),
                 qsTr("Device Modes"),
                 qsTr("LIN Override"),
                 qsTr("Update"),
                 qsTr("AndroidJNIDebug")
                 ];

        // Arctic Trucks
        /*
        spd_clbr_available_description = qsTr("Speedometer calibration available.")
        spd_clbr_unavailable_description = qsTr("Speedometer calibration unavailable.")
        spd_clbr_pulse_available_description = qsTr("Speedometer calibration is available via pulse calibrator.")
        odo_clbr_pulse_available_description = qsTr("Ododometer calibration is available via pulse calibrator.")
        odo_clbr_available_description = qsTr("Ododometer calibration available. \n Notice: the greater the distance of the test, the more percision shown in odometer readings. Some models' odometers may ignore the speed below 1 km/h. Press \"Freeze\" to stop odometer.")
        odo_clbr_unavailable_description = qsTr("Ododometer calibration unavailable separatedly from speedometer. Use the speedometer calibration.")
        crs_clbr_available_description = qsTr("Cruise control calibration available.")
        crs_clbr_unavailable_description = qsTr("Cruise control calibration unavailable.")

        tyr_thr_available_description = qsTr("Tyres pressure threshold customization available.")
        tyr_thr_lin_available_description = qsTr("Tyres pressure threshold customization is available via LIN.")
        tyr_thr_unavailable_description = qsTr("Tyres pressure threshold customization unavailable.")
        test_available_description = qsTr("Press the button to check wires connection. When connected properly the speedometer dial would show a test value.")
        test_unavailable_description = qsTr("Connection test unavailable.")
        */
        // Public

        spd_clbr_available_description = qsTr("Big tires calibrator is available from https://www.arctictrucks.ru/")
        spd_clbr_unavailable_description = qsTr("Big tires calibrator is available from https://www.arctictrucks.ru/")
        spd_clbr_pulse_available_description = qsTr("Big tires calibrator is available from https://www.arctictrucks.ru/")
        odo_clbr_pulse_available_description = qsTr("Big tires calibrator is available from https://www.arctictrucks.ru/")
        odo_clbr_available_description = qsTr("Big tires calibrator is available from https://www.arctictrucks.ru/")
        odo_clbr_unavailable_description = qsTr("Big tires calibrator is available from https://www.arctictrucks.ru/")
        crs_clbr_available_description = qsTr("Big tires calibrator is available from https://www.arctictrucks.ru/")
        crs_clbr_unavailable_description = qsTr("Big tires calibrator is available from https://www.arctictrucks.ru/")

        tyr_thr_available_description = qsTr("Big tires calibrator is available from https://www.arctictrucks.ru/")
        tyr_thr_lin_available_description = qsTr("Big tires calibrator is available from https://www.arctictrucks.ru/")
        tyr_thr_unavailable_description = qsTr("Big tires calibrator is available from https://www.arctictrucks.ru/")
        test_available_description = qsTr("Big tires calibrator is available from https://www.arctictrucks.ru/")
        test_unavailable_description = qsTr("Big tires calibrator is available from https://www.arctictrucks.ru/")

    }

    /*************** View Scale ****************/
    /* Int */
    property int _ViewScale_Height_Container: dp(core.getDesignValue_int("ViewScale", "Height", "Container"))

    /*************** SimpleItems control ****************/
    /* Font */
    property int _SimpleItems_Font_Main: dp(core.getDesignValue_int("SimpleItems", "Font", "Main"))
    /* Width */
    property int _SimpleItems_Width_ButtonBorder: core.getDesignValue_int("SimpleItems", "Width", "ButtonBorder")
    /* Ratio */
    property real _SimpleItems_HeightToWidth_Button: core.getDesignValue_float("SimpleItems", "HeightToWidth", "Button")
    property real _SimpleItems_Ratio_ButtonFont: core.getDesignValue_float("SimpleItems", "Ratio", "ButtonFont")
    property real _SimpleItems_Ratio_ButtonOnPress: core.getDesignValue_float("SimpleItems", "Ratio", "ButtonOnPress")
    /* Color */
    property string _SimpleItems_Color_FrameActive: core.getDesignValue_string("SimpleItems", "Color", "FrameActive")
    property string _SimpleItems_Color_FrameInactive: core.getDesignValue_string("SimpleItems", "Color", "FrameInactive")
    property string _SimpleItems_Color_FrameDisabled: core.getDesignValue_string("SimpleItems", "Color", "FrameDisabled")
    property string _SimpleItems_Color_Button: core.getDesignValue_string("SimpleItems", "Color", "Button")
    property string _SimpleItems_Color_ButtonText: core.getDesignValue_string("SimpleItems", "Color", "ButtonText")

    /*************** GeneralDesign ****************/
    /* Font */
    property int _GeneralDesign_Font_ToolBar: dp(core.getDesignValue_int("GeneralDesign", "Font", "ToolBar"))
    property int _GeneralDesign_Font_DrawerTitleFrame: dp(core.getDesignValue_int("GeneralDesign", "Font", "DrawerTitleFrame"))
    property int _GeneralDesign_Font_DrawerItemText: dp(core.getDesignValue_int("GeneralDesign", "Font", "DrawerItemText"))
    /* Height */
    property int _GeneralDesign_Height_DrawerTitleFrame: dp(core.getDesignValue_int("GeneralDesign", "Height", "DrawerTitleFrame"))
    property int _GeneralDesign_Height_DrawerItemIcons: dp(core.getDesignValue_int("GeneralDesign", "Height", "DrawerItemIcons"))
    property int _GeneralDesign_Height_ToolBar: dp(core.getDesignValue_int("GeneralDesign", "Height", "ToolBar"))
    /* Color */
    property string _GeneralDesign_Color_ToolBar: core.getDesignValue_string("GeneralDesign", "Color", "ToolBar")
    property string _GeneralDesign_Color_ToolBarText: core.getDesignValue_string("GeneralDesign", "Color", "ToolBarText")
    property string _GeneralDesign_Color_DrawerFrame: core.getDesignValue_string("GeneralDesign", "Color", "DrawerFrame")
    property string _GeneralDesign_Color_DrawerItemText: core.getDesignValue_string("GeneralDesign", "Color", "DrawerItemText")
    property string _GeneralDesign_Color_DrawerFrameText: core.getDesignValue_string("GeneralDesign", "Color", "DrawerFrameText")
    /* Ratio */
    property real _GeneralDesign_Ratio_TitleToToolbar: core.getDesignValue_float("GeneralDesign", "Ratio", "TitleToToolbar")
    property real _GeneralDesign_Ratio_ScreenAdjSideCrop: core.getDesignValue_float("GeneralDesign", "Ratio", "ScreenAdjSideCrop")
    property real _GeneralDesign_Ratio_ScreenAdjVertContainerCrop: core.getDesignValue_float("GeneralDesign", "Ratio", "ScreenAdjVCrop")
    property real _GeneralDesign_Gradient_Backstage: core.getDesignValue_float("GeneralDesign", "Gradient", "Backstage")
    /*************** Base ****************/
    /* Height */
    property int _Base_Height_Navibar: dp(core.getDesignValue_int("Base", "Height", "Navibar"))
    property int _Base_Width_ButtonBorder: core.getDesignValue_int("Base", "Width", "ButtonBorder")
    property int _Base_Font_TerminalSz: dp(core.getDesignValue_int("Base", "Font", "TerminalSz"))
    property int _Base_Width_ItemFrame: dp(core.getDesignValue_int("Base", "Width", "ItemFrame"))
    property int _Base_Height_Item: dp(core.getDesignValue_int("Base", "Height", "Item"))
    readonly property int _Base_Height_CollapsedNavibar: _Base_Height_Navibar * 0.3
    property int _Base_Height_PageGrid: dp(core.getDesignValue_int("Base", "Height", "PageGrid"))

    /* Ratio */
    property real _Base_Gradient_PositionA: core.getDesignValue_float("Base", "Gradient", "PositionA")
    property real _Base_Gradient_PositionB: core.getDesignValue_float("Base", "Gradient", "PositionB")
    property real _Base_Ratio_ButtonFont: core.getDesignValue_float("Base", "Ratio", "ButtonFont")
    /* Color */
    property string _Base_Color_Icon: core.getDesignValue_string("Base", "Color", "Icon")
    property string _Base_Color_IconOverlay: core.getDesignValue_string("Base", "Color", "IconOverlay")
    property string _Base_Color_BaseFont: core.getDesignValue_string("Base", "Color", "BaseFont")
    // property string _Base_Color_GradientBackground: core.getDesignValue_string("Base", "Color", "GradientBackground")
    property string _Base_Color_Frame: core.getDesignValue_string("Base", "Color", "Frame")
    property string _Base_Color_Canva: core.getDesignValue_string("Base", "Color", "Canva")

    property string _Base_Color_ButtonCanva: core.getDesignValue_string("Base", "Color", "ButtonCanva")
    property string _Base_Color_FrameLight: core.getDesignValue_string("Base", "Color", "FrameLight")

    readonly property real _DrawerItem_GradientStop: 0.8

    /********************* Refresh *********************/

    Component.onCompleted: {
        retranslateUi();
    }

    Connections {
        target: core
        function onUserProfileChanged(){
            current_user = core.getUserProfileValue(CoreImport.ProfileMembers.Name)
        }
    }

    Connections {
        target: core
        function onAppDesignChanged(){
            /*************** View Scale ****************/
            /* Int */
            _ViewScale_Height_Container = dp(core.getDesignValue_int("ViewScale", "Height", "Container"))

            /*************** SimpleItems control ****************/
            /* Font */
            _SimpleItems_Font_Main = dp(core.getDesignValue_int("SimpleItems", "Font", "Main"))
            /* Width */
            _SimpleItems_Width_ButtonBorder = core.getDesignValue_int("SimpleItems", "Width", "ButtonBorder")
            /* Ratio */
            _SimpleItems_HeightToWidth_Button = core.getDesignValue_float("SimpleItems", "HeightToWidth", "Button")
            _SimpleItems_Ratio_ButtonFont = core.getDesignValue_float("SimpleItems", "Ratio", "ButtonFont")
            _SimpleItems_Ratio_ButtonOnPress = core.getDesignValue_float("SimpleItems", "Ratio", "ButtonOnPress")
            /* Color */
            _SimpleItems_Color_FrameActive = core.getDesignValue_string("SimpleItems", "Color", "FrameActive")
            _SimpleItems_Color_FrameInactive = core.getDesignValue_string("SimpleItems", "Color", "FrameInactive")
            _SimpleItems_Color_FrameDisabled = core.getDesignValue_string("SimpleItems", "Color", "FrameDisabled")
            _SimpleItems_Color_Button = core.getDesignValue_string("SimpleItems", "Color", "Button")
            _SimpleItems_Color_ButtonText = core.getDesignValue_string("SimpleItems", "Color", "ButtonText")

            /*************** GeneralDesign ****************/
            /* Font */
            _GeneralDesign_Font_ToolBar = dp(core.getDesignValue_int("GeneralDesign", "Font", "ToolBar"))
            _GeneralDesign_Font_DrawerTitleFrame = dp(core.getDesignValue_int("GeneralDesign", "Font", "DrawerTitleFrame"))
            _GeneralDesign_Font_DrawerItemText = dp(core.getDesignValue_int("GeneralDesign", "Font", "DrawerItemText"))
            /* Height */
            _GeneralDesign_Height_DrawerTitleFrame = dp(core.getDesignValue_int("GeneralDesign", "Height", "DrawerTitleFrame"))
            _GeneralDesign_Height_DrawerItemIcons = dp(core.getDesignValue_int("GeneralDesign", "Height", "DrawerItemIcons"))
            _GeneralDesign_Height_ToolBar = dp(core.getDesignValue_int("GeneralDesign", "Height", "ToolBar"))
            /* Color */
            _GeneralDesign_Color_ToolBar = core.getDesignValue_string("GeneralDesign", "Color", "ToolBar")
            _GeneralDesign_Color_ToolBarText = core.getDesignValue_string("GeneralDesign", "Color", "ToolBarText")
            _GeneralDesign_Color_DrawerFrame = core.getDesignValue_string("GeneralDesign", "Color", "DrawerFrame")
            _GeneralDesign_Color_DrawerItemText = core.getDesignValue_string("GeneralDesign", "Color", "DrawerItemText")
            _GeneralDesign_Color_DrawerFrameText = core.getDesignValue_string("GeneralDesign", "Color", "DrawerFrameText")
            /* Ratio */
            _GeneralDesign_Ratio_TitleToToolbar = core.getDesignValue_float("GeneralDesign", "Ratio", "TitleToToolbar")
            _GeneralDesign_Ratio_ScreenAdjSideCrop = core.getDesignValue_float("GeneralDesign", "Ratio", "ScreenAdjSideCrop")
            _GeneralDesign_Ratio_ScreenAdjVertContainerCrop = core.getDesignValue_float("GeneralDesign", "Ratio", "ScreenAdjVCrop")
            _GeneralDesign_Gradient_Backstage = core.getDesignValue_float("GeneralDesign", "Gradient", "Backstage")

            /*************** Base ****************/
            /* Height */
            _Base_Height_Navibar = dp(core.getDesignValue_int("Base", "Height", "Navibar"))
            _Base_Width_ButtonBorder = dp(core.getDesignValue_int("Base", "Width", "ButtonBorder"))
            _Base_Font_TerminalSz = dp(core.getDesignValue_int("Base", "Font", "TerminalSz"))
            _Base_Width_ItemFrame = dp(core.getDesignValue_int("Base", "Width", "ItemFrame"))
            _Base_Height_Item = dp(core.getDesignValue_int("Base", "Height", "Item"))
            _Base_Height_PageGrid = dp(core.getDesignValue_int("Base", "Height", "PageGrid"))

            /* Ratio */
            _Base_Gradient_PositionA = core.getDesignValue_float("Base", "Gradient", "PositionA")
            _Base_Gradient_PositionB = core.getDesignValue_float("Base", "Gradient", "PositionB")
            _Base_Ratio_ButtonFont = core.getDesignValue_float("Base", "Ratio", "ButtonFont")
            /* Color */
            _Base_Color_Icon = core.getDesignValue_string("Base", "Color", "Icon")
            _Base_Color_IconOverlay = core.getDesignValue_string("Base", "Color", "IconOverlay")
            _Base_Color_BaseFont = core.getDesignValue_string("Base", "Color", "BaseFont")
            //_Base_Color_GradientBackground = core.getDesignValue_string("Base", "Color", "GradientBackground")
            _Base_Color_Frame = core.getDesignValue_string("Base", "Color", "Frame")
            _Base_Color_Canva = core.getDesignValue_string("Base", "Color", "Canva")
            _Base_Color_ButtonCanva: core.getDesignValue_string("Base", "Color", "ButtonCanva")
            _Base_Color_FrameLight: core.getDesignValue_string("Base", "Color", "FrameLight")
        }
    }
}
