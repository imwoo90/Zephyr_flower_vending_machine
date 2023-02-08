#pragma once

#define RESOURCES \
    X(AdditionalStock)\
    X(BanknoteReaderModeSetting)\
    X(ColumnTestAll)\
    X(ColumnTestManul)\
    X(ColumnTestSection)\
    X(EnterPasswordOfAdditionalStock)\
    X(EnterPasswordOfMainManagement)\
    X(EnterPasswordOfManualSales)\
    X(EnterPasswordOfPasswordChange)\
    X(EnterPasswordOfSystemManagement)\
    X(EnterPasswordOfSystemSetting)\
    X(EnterPasswordOfVendingMachineModeSetting)\
    X(EnterProductNumber)\
    X(EnterProductNumberNoGoods)\
    X(InputMoney_0)\
    X(InputMoney_1)\
    X(ListOfAdditionalStock)\
    X(ListOfColumnData)\
    X(ListOfCurrentStock)\
    X(MainManagement)\
    X(ManualSales)\
    X(MatchingChannelAndColumn)\
    X(MotorTypeSetting)\
    X(NumberOfChannelSetting)\
    X(NumberOfRelaySetting)\
    X(PasswordChange)\
    X(SalesInfo)\
    X(Selling)\
    X(SetGoods)\
    X(StopSelling)\
    X(SystemCheck)\
    X(SystemSetting)\
    X(VendingMachineModeSetting)\
    X(WorkingTest)\

#define X(name) extern const unsigned char name##_bits[];
    RESOURCES
#undef X

typedef enum {
#define X(name) name,
    RESOURCES
#undef X
    NumberOfResourceType
} ResourceType;


