#pragma once

#include <zephyr/kernel.h>

#include <functional>
#include <algorithm>
//PasswordOfVendingMachineModeSetting too long file name
// PasswordOfVendingMachineModeSetting - > PasswordOfVMMS
#define STATIC_DATA\
    X(IsInit)\
    X(PasswordOfSystemManagement)\
    X(PasswordOfSystemSetting)\
    X(PasswordOfVMMS)\
    X(PasswordOfMainManagement)\
    X(PasswordOfAdditionalStock)\
    X(PasswordOfManualSales)\
    X(PasswordOfPasswordChange)\
    X(BanknoteReaderMode)\
    X(NumberOfRelay)\
    X(MoneyOfTotalSales)\
    X(NumberOfTotalSales)\
    X(MoneyOfManualSales)\
    X(NumberOfManualSales)

#define COLUMN_DATA\
    X(MotorTpye)\
    X(Quantity)\
    X(Price)\
    X(Channel)\
    X(Additional)\
    X(SalesAmount)

#define RELAY_DATA\
    X(NumberOfChannels)\
    X(RelayType)


#define X(name) name,
typedef enum {
    STATIC_DATA
} StaticData;
typedef enum {
    COLUMN_DATA
} ColumnData;

typedef enum {
    RELAY_DATA
} RelayData;
#undef X

enum {
    TypeStaticData = 0,
    TypeColumnData = 1,
    TypeRelayData = 2,
    TypeAll = 3,
    NumOfStaticData = NumberOfManualSales + 1,
    NumofColumnData = SalesAmount + 1,
    NumOfRelayData = RelayType + 1,
    MaxNumOfColumn = 999,
    MaxNumOfRelay = 99,
};

class MachineData {
private:
    uint32_t _numberOfRelays = 0;
    uint32_t _numberOfColumns = 0;

    uint32_t _staticDataBuf[NumOfStaticData];
    uint32_t _columnDataBuf[NumofColumnData*MaxNumOfColumn];
    uint32_t _relayDataBuf[NumOfRelayData*MaxNumOfRelay];

    void readOrWrite(int type, std::function<void(const char*, uint8_t *, uint32_t)> _work);
    void _read(int type);

    //static length data
    void setStaticData(StaticData pos, uint32_t data);
    uint32_t getStaticData(StaticData pos);

    //dynamic length data
    uint32_t getRelayData(int idx, RelayData pos);
    uint32_t getColumnData(int idx, ColumnData pos);
    void setRelayData(int idx, RelayData pos, uint32_t data);
    void setColumnData(int idx, ColumnData pos, uint32_t data);

    MachineData() {}
public:
    static MachineData* getInstance() {
        static MachineData singleton_instance;
        return &singleton_instance;
    }
    inline uint32_t getNumberOfColumns() { return _numberOfColumns;}
    inline uint32_t getNumberOfRelays() { return _numberOfRelays;}

    void defineDefaultsData();
    void initialize();

    void flush(int type);

    //ColumnData
    uint32_t getMotorType(int idx);
    uint32_t getQuantity(int idx);
    uint32_t getPrice(int idx);
    uint32_t getChannel(int idx);
    uint32_t getAdditional(int idx);
    uint32_t getSalesAmount(int idx);
    void setMotorType(int idx, uint32_t data);
    void setQuantity(int idx, uint32_t data);
    void setPrice(int idx, uint32_t data);
    void setChannel(int idx, uint32_t data);
    void setAdditional(int idx, uint32_t data);
    void setSalesAmount(int idx, uint32_t data);

    //RelayData
    uint32_t getNumberOfChannels(int idx);
    uint32_t getRelayType(int idx);
    void setNumberOfChannels(int idx, uint32_t data);
    void setRelayType(int idx, uint32_t data);

    // StaticLengthData
    uint32_t getPasswordOfSystemManagement();
    uint32_t getPasswordOfSystemSetting();
    uint32_t getPasswordOfVendingMachineModeSetting();
    uint32_t getPasswordOfMainManagement();
    uint32_t getPasswordOfAdditionalStock();
    uint32_t getPasswordOfManualSales();
    uint32_t getPasswordOfPasswordChange();
    uint32_t getBanknoteReaderMode();
    uint32_t getNumberOfRelay();
    uint32_t getMoneyOfTotalSales();
    uint32_t getNumberOfTotalSales();
    uint32_t getMoneyOfManualSales();
    uint32_t getNumberOfManualSales();
    void setPasswordOfSystemManagement(uint32_t password);
    void setPasswordOfSystemSetting(uint32_t password);
    void setPasswordOfVendingMachineModeSetting(uint32_t password);
    void setPasswordOfMainManagement(uint32_t password);
    void setPasswordOfAdditionalStock(uint32_t password);
    void setPasswordOfManualSales(uint32_t password);
    void setPasswordOfPasswordChange(uint32_t password);
    void setBanknoteReaderMode(uint32_t mode);
    void setNumberOfRelay(uint32_t number);
    void setMoneyOfTotalSales(uint32_t money);
    void setNumberOfTotalSales(uint32_t number);
    void setMoneyOfManualSales(uint32_t money);
    void setNumberOfManualSales(uint32_t number);

};
