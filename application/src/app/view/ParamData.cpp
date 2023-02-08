#include <U8g2lib.h>
#include "ParamData.h"

const ParamData AdditionalStock_ParamDatas[] = {
    {.interval = -9, .x = 190, .y = 80, .font = u8g2_font_logisoso16_tr,},
    {.interval = -9, .x = 190, .y = 115, .font = u8g2_font_logisoso16_tr,},
    {.interval = -9, .x = 190, .y = 150, .font = u8g2_font_logisoso16_tr,},
};
const ParamData BanknoteReaderModeSetting_ParamDatas[] = {
    {.interval = 21, .x = 65, .y = 125, .font = u8g2_font_logisoso16_tr,},
};
const ParamData ColumnTestAll_ParamDatas[] = {
    {.interval = 21, .x = 75, .y = 110, .font = u8g2_font_logisoso16_tr,},
};
const ParamData ColumnTestManul_ParamDatas[] = {
    {.interval = 21, .x = 75, .y = 110, .font = u8g2_font_logisoso16_tr,},
};
const ParamData ColumnTestSection_ParamDatas[] = {
    {.interval = 21, .x = 30, .y = 110, .font = u8g2_font_logisoso16_tr,},
    {.interval = 21, .x = 120, .y = 110, .font = u8g2_font_logisoso16_tr,},
};
const ParamData EnterPasswordOfAdditionalStock_ParamDatas[] = {
    {.interval = 21, .x = 70, .y = 110, .font = u8g2_font_logisoso16_tr,},
};
const ParamData EnterPasswordOfMainManagement_ParamDatas[] = {
    {.interval = 21, .x = 70, .y = 110, .font = u8g2_font_logisoso16_tr,},
};
const ParamData EnterPasswordOfManualSales_ParamDatas[] = {
    {.interval = 21, .x = 70, .y = 110, .font = u8g2_font_logisoso16_tr,},
};
const ParamData EnterPasswordOfPasswordChange_ParamDatas[] = {
    {.interval = 21, .x = 70, .y = 110, .font = u8g2_font_logisoso16_tr,},
};
const ParamData EnterPasswordOfSystemManagement_ParamDatas[] = {
    {.interval = 21, .x = 102, .y = 110, .font = u8g2_font_logisoso16_tr,},
};
const ParamData EnterPasswordOfSystemSetting_ParamDatas[] = {
    {.interval = 21, .x = 90, .y = 110, .font = u8g2_font_logisoso16_tr,},
};
const ParamData EnterPasswordOfVendingMachineModeSetting_ParamDatas[] = {
    {.interval = 21, .x = 50, .y = 110, .font = u8g2_font_logisoso16_tr,},
};
const ParamData EnterProductNumber_ParamDatas[] = {
    {.interval = 40, .x = 80, .y = 95, .font = u8g2_font_logisoso32_tr,},
};
const ParamData EnterProductNumberNoGoods_ParamDatas[] = {
};
const ParamData InputMoney_0_ParamDatas[] = {
    {.interval = -34, .x = 180, .y = 95, .font = u8g2_font_logisoso32_tr,},
};
const ParamData InputMoney_1_ParamDatas[] = {
    {.interval = -16, .x = 200, .y = 80, .font = u8g2_font_logisoso16_tr,},
    {.interval = -16, .x = 200, .y = 105, .font = u8g2_font_logisoso16_tr,},
};
const ParamData ListOfAdditionalStock_ParamDatas[] = {
    // Left 4
    {.interval = 10, .x = 6, .y = 65, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 48, .y = 65, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 90, .y = 65, .font = u8g2_font_logisoso16_tr,},

    {.interval = 10, .x = 6, .y = 88, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 48, .y = 88, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 90, .y = 88, .font = u8g2_font_logisoso16_tr,},

    {.interval = 10, .x = 6, .y = 111, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 48, .y = 111, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 90, .y = 111, .font = u8g2_font_logisoso16_tr,},

    {.interval = 10, .x = 6, .y = 134, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 48, .y = 134, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 90, .y = 134, .font = u8g2_font_logisoso16_tr,},

    // Right 4
    {.interval = 10, .x = 134, .y = 65, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 176, .y = 65, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 218, .y = 65, .font = u8g2_font_logisoso16_tr,},

    {.interval = 10, .x = 134, .y = 88, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 176, .y = 88, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 218, .y = 88, .font = u8g2_font_logisoso16_tr,},

    {.interval = 10, .x = 134, .y = 111, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 176, .y = 111, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 218, .y = 111, .font = u8g2_font_logisoso16_tr,},

    {.interval = 10, .x = 134, .y = 134, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 176, .y = 134, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 218, .y = 134, .font = u8g2_font_logisoso16_tr,},

    //page
    {.interval = 10, .x = 218, .y = 157, .font = u8g2_font_logisoso16_tr,},
};
const ParamData ListOfColumnData_ParamDatas[] = {
    // Left 4
    {.interval = 10, .x = 6, .y = 65, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 48, .y = 65, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 90, .y = 65, .font = u8g2_font_logisoso16_tr,},

    {.interval = 10, .x = 6, .y = 88, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 48, .y = 88, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 90, .y = 88, .font = u8g2_font_logisoso16_tr,},

    {.interval = 10, .x = 6, .y = 111, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 48, .y = 111, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 90, .y = 111, .font = u8g2_font_logisoso16_tr,},

    {.interval = 10, .x = 6, .y = 134, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 48, .y = 134, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 90, .y = 134, .font = u8g2_font_logisoso16_tr,},

    // Right 4
    {.interval = 10, .x = 134, .y = 65, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 176, .y = 65, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 218, .y = 65, .font = u8g2_font_logisoso16_tr,},

    {.interval = 10, .x = 134, .y = 88, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 176, .y = 88, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 218, .y = 88, .font = u8g2_font_logisoso16_tr,},

    {.interval = 10, .x = 134, .y = 111, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 176, .y = 111, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 218, .y = 111, .font = u8g2_font_logisoso16_tr,},

    {.interval = 10, .x = 134, .y = 134, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 176, .y = 134, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 218, .y = 134, .font = u8g2_font_logisoso16_tr,},

    //page
    {.interval = 10, .x = 218, .y = 157, .font = u8g2_font_logisoso16_tr,},
};
const ParamData ListOfCurrentStock_ParamDatas[] = {
    // Left 4
    {.interval = 10, .x = 6, .y = 65, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 48, .y = 65, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 90, .y = 65, .font = u8g2_font_logisoso16_tr,},

    {.interval = 10, .x = 6, .y = 88, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 48, .y = 88, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 90, .y = 88, .font = u8g2_font_logisoso16_tr,},

    {.interval = 10, .x = 6, .y = 111, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 48, .y = 111, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 90, .y = 111, .font = u8g2_font_logisoso16_tr,},

    {.interval = 10, .x = 6, .y = 134, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 48, .y = 134, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 90, .y = 134, .font = u8g2_font_logisoso16_tr,},

    // Right 4
    {.interval = 10, .x = 134, .y = 65, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 176, .y = 65, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 218, .y = 65, .font = u8g2_font_logisoso16_tr,},

    {.interval = 10, .x = 134, .y = 88, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 176, .y = 88, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 218, .y = 88, .font = u8g2_font_logisoso16_tr,},

    {.interval = 10, .x = 134, .y = 111, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 176, .y = 111, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 218, .y = 111, .font = u8g2_font_logisoso16_tr,},

    {.interval = 10, .x = 134, .y = 134, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 176, .y = 134, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 218, .y = 134, .font = u8g2_font_logisoso16_tr,},

    //page
    {.interval = 10, .x = 218, .y = 157, .font = u8g2_font_logisoso16_tr,},
};
const ParamData MainManagement_ParamDatas[] = {
};
const ParamData ManualSales_ParamDatas[] = {
    {.interval = -9, .x = 190, .y = 80, .font = u8g2_font_logisoso16_tr,},
    {.interval = -9, .x = 190, .y = 115, .font = u8g2_font_logisoso16_tr,},
};
const ParamData MatchingChannelAndColumn_ParamDatas[] = {
    {.interval = 21, .x = 15, .y = 125, .font = u8g2_font_logisoso16_tr,},
    {.interval = 21, .x = 133, .y = 125, .font = u8g2_font_logisoso16_tr,},
};
const ParamData MotorTypeSetting_ParamDatas[] = {
    {.interval = 21, .x = 33, .y = 98, .font = u8g2_font_logisoso16_tr,},
    {.interval = 21, .x = 95, .y = 98, .font = u8g2_font_logisoso16_tr,},
    {.interval = 21, .x = 90, .y = 125, .font = u8g2_font_logisoso16_tr,},
};
const ParamData NumberOfChannelSetting_ParamDatas[] = {
    {.interval = 21, .x = 33, .y = 98, .font = u8g2_font_logisoso16_tr,},
    {.interval = 21, .x = 95, .y = 98, .font = u8g2_font_logisoso16_tr,},
    {.interval = 21, .x = 90, .y = 125, .font = u8g2_font_logisoso16_tr,},
};

const ParamData NumberOfRelaySetting_ParamDatas[] = {
    {.interval = 21, .x = 70, .y = 125, .font = u8g2_font_logisoso16_tr,},
};
const ParamData PasswordChange_ParamDatas[] = {
    {.interval = 10, .x = 165, .y = 38, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 165, .y = 58, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 165, .y = 77, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 165, .y = 96, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 165, .y = 115, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 165, .y = 135, .font = u8g2_font_logisoso16_tr,},
    {.interval = 10, .x = 165, .y = 155, .font = u8g2_font_logisoso16_tr,},
};
const ParamData SalesInfo_ParamDatas[] = {
    {.interval = -9, .x = 210, .y = 55, .font = u8g2_font_logisoso16_tr,},
    {.interval = -9, .x = 210, .y = 75, .font = u8g2_font_logisoso16_tr,},
    {.interval = -9, .x = 210, .y = 95, .font = u8g2_font_logisoso16_tr,},
    {.interval = -9, .x = 210, .y = 115, .font = u8g2_font_logisoso16_tr,},
};
const ParamData Selling_ParamDatas[] = {
};
const ParamData SetGoods_ParamDatas[] = {
    {.interval = -9, .x = 190, .y = 80, .font = u8g2_font_logisoso16_tr,},
    {.interval = -9, .x = 190, .y = 115, .font = u8g2_font_logisoso16_tr,},
    {.interval = -9, .x = 190, .y = 150, .font = u8g2_font_logisoso16_tr,},
};

const ParamData StopSelling_ParamDatas[] = {
    {.interval = 32, .x = 90, .y = 130, .font = u8g2_font_logisoso16_tr,},
};
const ParamData SystemCheck_ParamDatas[] = {
    {.interval = 32, .x = 170, .y = 60, .font = u8g2_font_logisoso16_tr,},
    {.interval = 32, .x = 170, .y = 90, .font = u8g2_font_logisoso16_tr,},
    {.interval = 32, .x = 170, .y = 120, .font = u8g2_font_logisoso16_tr,},
    {.interval = 32, .x = 170, .y = 150, .font = u8g2_font_logisoso16_tr,},
};
const ParamData SystemSetting_ParamDatas[] = {
};
const ParamData VendingMachineModeSetting_ParamDatas[] = {
};
const ParamData WorkingTest_ParamDatas[] = {
};