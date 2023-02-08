#include "SetGoods.h"

#include "MainManagement.h"

void SetGoods::initialize() {
    // init data
    _data.clear();
    _data["state"] = "SetGoods";
    _data["param_0"] = "000";
    _data["param_1"] = "000000";
    _data["param_2"] = "00";
    _selection = 0;
    _data["selection"] = "param_0";
}

SetGoods* SetGoods::getInstance() {
    static SetGoods singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* SetGoods::pressKey(const char key) {
    MachineState* next = this;
    switch ( key ) {
    case '*':
        next = MainManagement::getInstance();
        break;
    case '#':
        if ( _selection == 0) {
            uint32_t column = std::stoi(_data["param_0"]) - 1;
            if (0 <= column && column < _database->getNumberOfColumns()) {
                _selection = 1;
                _data["selection"] = "param_1";
            }
        } else if ( _selection == 1) {
            uint32_t price = std::stoi(_data["param_1"]);
            if (price <= 999000) {
                _selection = 2;
                _data["selection"] = "param_2";
            }
        } else if ( _selection == 2) {
            uint32_t column = std::stoi(_data["param_0"]) - 1;
            uint32_t quantity = std::stoi(_data["param_2"]);
            _database->setQuantity(column, quantity);
            _database->setPrice(column, std::stoi(_data["param_1"]));
            // _database->flush(TypeColumnData);
            _selection = 0;
            _data["selection"] = "param_0";
        }
        break;
    default: {//1~9
        char param_idx[] = "param_0";
        param_idx[6] = '0' + _selection;
        std::string &param = _data[param_idx];
        int size = param.size();
        if(_selection == 1)
            size = 3;

        rotate(param.begin(), param.begin()+1, param.begin() + size);
        param[size-1] = key;
        _data["selection"] = param_idx;
        break;}
    }
    return next;
}
