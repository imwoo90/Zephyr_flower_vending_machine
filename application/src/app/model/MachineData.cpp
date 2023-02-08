#include <MachineData.h>

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(DB);


#define STATIC_DATA_PATH "/root/static_data"
#define COLUMN_DATA_PATH "/root/ColumnData"
#define RELAY_DATA_PATH "/root/RelayData"

void MachineData::defineDefaultsData() {
    // k_msleep(5000);
    // LOG_INF("little fs format start");
    // if ( !LittleFS.format() ) {
    //     LOG_ERR("little fs format failed");
    //     return ;
    // }
    LOG_INF("little fs format end");

    memset(_staticDataBuf, 0, sizeof(_staticDataBuf));
    memset(_columnDataBuf, 0, sizeof(_columnDataBuf));
    memset(_relayDataBuf, 0, sizeof(_relayDataBuf));

    //default static length data
    setPasswordOfSystemManagement(999);
    setPasswordOfSystemSetting(1234);
    setPasswordOfVendingMachineModeSetting(12345678);
    setPasswordOfMainManagement(123456);
    setPasswordOfAdditionalStock(123456);
    setPasswordOfManualSales(123456);
    setPasswordOfPasswordChange(123456);
    setBanknoteReaderMode(1);
    setNumberOfRelay(0);
    setMoneyOfTotalSales(0);
    setNumberOfTotalSales(0);
    setMoneyOfManualSales(0);
    setNumberOfManualSales(0);
    setStaticData(IsInit, 1);
    flush(TypeAll);
}
void MachineData::initialize() {
    _read(TypeAll);
    // setStaticData(IsInit, 0);

    struct stat tmp;
    // bool isNotInit = !LittleFS.exists(STATIC_DATA_PATH) || !getStaticData(IsInit)
    //     || !LittleFS.exists(COLUMN_DATA_PATH) || !LittleFS.exists(RELAY_DATA_PATH);
    bool isNotInit = stat(STATIC_DATA_PATH, &tmp) || !getStaticData(IsInit) || stat(COLUMN_DATA_PATH, &tmp) || stat(RELAY_DATA_PATH, &tmp);
    if (isNotInit) {
        defineDefaultsData();
    }

    _numberOfRelays = getNumberOfRelay();
    _numberOfColumns = 0;
    for(uint32_t i = 0; i < _numberOfRelays; i++) {
        _numberOfColumns += getNumberOfChannels(i);
    }
}

void MachineData::readOrWrite(int type, std::function<void(const char*, uint8_t *, uint32_t)> work) {
    const struct {
        const char* path;
        uint8_t* buf;
        uint32_t size;
    } __tmp[3] = {
        {STATIC_DATA_PATH, (uint8_t*)_staticDataBuf, sizeof(_staticDataBuf),},
        {COLUMN_DATA_PATH, (uint8_t*)_columnDataBuf, sizeof(_columnDataBuf),},
        {RELAY_DATA_PATH, (uint8_t*)_relayDataBuf, sizeof(_relayDataBuf),},
    };

    if (type < 3) {
        work(__tmp[type].path, __tmp[type].buf, __tmp[type].size);
    } else if (type == 3) {
        for (int i = 0; i < 3; i++){
            work(__tmp[i].path, __tmp[i].buf, __tmp[i].size);
        }
    }
}
void MachineData::_read(int type) {
    auto readFile = [](const char* path, uint8_t *buf, uint32_t size) {
        int fd = open(path, O_RDONLY);
        // lseek(0, )
        read(fd, buf, size);
        close(fd);
    };
    readOrWrite(type, readFile);
}

void MachineData::flush(int type) {
    auto writeFile = [](const char* path, uint8_t *buf, uint32_t size) {
        int fd = open(path, O_CREAT|O_WRONLY);
        write(fd, buf, size);
        close(fd);
        k_msleep(1);
    };
    readOrWrite(type, writeFile);
}

void MachineData::setStaticData(StaticData id, uint32_t data) {
    _staticDataBuf[id] = data;
}
uint32_t MachineData::getStaticData(StaticData id) {
    return _staticDataBuf[id];
}
void MachineData::setColumnData(int idx, ColumnData id, uint32_t data) {
    _columnDataBuf[NumofColumnData*idx + id] = data;
}
uint32_t MachineData::getColumnData(int idx, ColumnData id) {
    return _columnDataBuf[NumofColumnData*idx + id];
}
void MachineData::setRelayData(int idx, RelayData id, uint32_t data) {
    _relayDataBuf[NumOfRelayData*idx + id] = data;
}
uint32_t MachineData::getRelayData(int idx, RelayData id) {
    return _relayDataBuf[NumOfRelayData*idx + id];
}

//ColumnData
uint32_t MachineData::getMotorType(int idx) {
    return getColumnData(idx, MotorTpye);
}
uint32_t MachineData::getQuantity(int idx) {
    return getColumnData(idx, Quantity);
}
uint32_t MachineData::getPrice(int idx) {
    return getColumnData(idx, Price);
}
uint32_t MachineData::getChannel(int idx) {
    return getColumnData(idx, Channel);
}
uint32_t MachineData::getAdditional(int idx) {
    return getColumnData(idx, Additional);
}
uint32_t MachineData::getSalesAmount(int idx) {
    return getColumnData(idx, SalesAmount);
}
void MachineData::setMotorType(int idx, uint32_t data) {
    setColumnData(idx, MotorTpye, data);
}
void MachineData::setQuantity(int idx, uint32_t data) {
    setColumnData(idx, Quantity, data);
}
void MachineData::setPrice(int idx, uint32_t data) {
    setColumnData(idx, Price, data);
}
void MachineData::setChannel(int idx, uint32_t data) {
    setColumnData(idx, Channel, data);
}
void MachineData::setAdditional(int idx, uint32_t data) {
    setColumnData(idx, Additional, data);
}
void MachineData::setSalesAmount(int idx, uint32_t data) {
    setColumnData(idx, SalesAmount, data);
}

//RelayData
uint32_t MachineData::getNumberOfChannels(int idx) {
    return getRelayData(idx, NumberOfChannels);
}
uint32_t MachineData::getRelayType(int idx) {
    return getRelayData(idx, RelayType);
}
void MachineData::setNumberOfChannels(int idx, uint32_t data) {
    int _s, _e;
    int delta = data - getNumberOfChannels(idx);
    if (delta == 0) {
        return;
    } else if (delta > 0 ) { // Increase column
        _s = _numberOfColumns;
        _e = _s + delta;
    } else { // Decrease column
        _e = _numberOfColumns;
        _s = _e + delta;
    }

    for(int i = _s; i < _e; i += 1) {
        setMotorType(i, 1);
        setQuantity(i, 0);
        setPrice(i, 0);
        setChannel(i, i);
        setAdditional(i, 0);
        setSalesAmount(i, 0);
    }
    _numberOfColumns += delta;
    setRelayData(idx, NumberOfChannels, data);
}
void MachineData::setRelayType(int idx, uint32_t data) {
    setRelayData(idx, RelayType, data);
}

// StaticLengthData
uint32_t MachineData::getPasswordOfSystemManagement() {
    return getStaticData(PasswordOfSystemManagement);
}

uint32_t MachineData::getPasswordOfSystemSetting() {
    return getStaticData(PasswordOfSystemSetting);
}

uint32_t MachineData::getPasswordOfVendingMachineModeSetting() {
    return getStaticData(PasswordOfVMMS);
}

uint32_t MachineData::getPasswordOfMainManagement() {
    return getStaticData(PasswordOfMainManagement);
}

uint32_t MachineData::getPasswordOfAdditionalStock() {
    return getStaticData(PasswordOfAdditionalStock);
}

uint32_t MachineData::getPasswordOfManualSales() {
    return getStaticData(PasswordOfManualSales);
}

uint32_t MachineData::getPasswordOfPasswordChange() {
    return getStaticData(PasswordOfPasswordChange);
}
uint32_t MachineData::getBanknoteReaderMode() {
    return getStaticData(BanknoteReaderMode);
}
uint32_t MachineData::getNumberOfRelay() {
    return getStaticData(NumberOfRelay);
}
uint32_t MachineData::getMoneyOfTotalSales() {
    return getStaticData(MoneyOfTotalSales);
}
uint32_t MachineData::getNumberOfTotalSales() {
    return getStaticData(NumberOfTotalSales);
}
uint32_t MachineData::getMoneyOfManualSales() {
    return getStaticData(MoneyOfManualSales);
}
uint32_t MachineData::getNumberOfManualSales() {
    return getStaticData(NumberOfManualSales);
}
void MachineData::setPasswordOfSystemManagement(uint32_t password) {
    setStaticData(PasswordOfSystemManagement, password);
}
void MachineData::setPasswordOfSystemSetting(uint32_t password) {
    setStaticData(PasswordOfSystemSetting, password);
}
void MachineData::setPasswordOfVendingMachineModeSetting(uint32_t password) {
    setStaticData(PasswordOfVMMS, password);
}
void MachineData::setPasswordOfMainManagement(uint32_t password) {
    setStaticData(PasswordOfMainManagement, password);
}
void MachineData::setPasswordOfAdditionalStock(uint32_t password) {
    setStaticData(PasswordOfAdditionalStock, password);
}
void MachineData::setPasswordOfManualSales(uint32_t password) {
    setStaticData(PasswordOfManualSales, password);
}
void MachineData::setPasswordOfPasswordChange(uint32_t password) {
    setStaticData(PasswordOfPasswordChange, password);
}
void MachineData::setBanknoteReaderMode(uint32_t mode) {
    setStaticData(BanknoteReaderMode, mode);
}
void MachineData::setNumberOfRelay(uint32_t number) {
    int delta = number - _numberOfRelays;
    if (delta == 0) {
        // nothing to do
    } else if (delta > 0) { // Increase number of relays
        int _s = _numberOfRelays;
        int _e = number;
        for(int i = _s; i < _e; i++) {
            setNumberOfChannels(i, 0); // Default channel number is 0
            setRelayType(i, 1); // Default relay type is 1
        }
    } else { // Decrease number of relays
        int _s = _numberOfRelays;
        int _e = number;
        for(int i = _s; i >= _e; i--) {
            setNumberOfChannels(i, 0);
        }
    }
    _numberOfRelays = number;
    setStaticData(NumberOfRelay, number);
}
void MachineData::setMoneyOfTotalSales(uint32_t money) {
    setStaticData(MoneyOfTotalSales, money);
}
void MachineData::setNumberOfTotalSales(uint32_t number) {
    setStaticData(NumberOfTotalSales, number);
}
void MachineData::setMoneyOfManualSales(uint32_t money) {
    setStaticData(MoneyOfManualSales, money);
}
void MachineData::setNumberOfManualSales(uint32_t number) {
    setStaticData(NumberOfManualSales, number);
}