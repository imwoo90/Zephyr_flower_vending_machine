#include "ListOfCurrentStock.h"

#include "MainManagement.h"

#define NUMBER_PER_PAGE 8

ListOfCurrentStock::ListOfCurrentStock() {

}

void ListOfCurrentStock::initialize() {
    // init data
    _data.clear();
    _data["state"] = "ListOfCurrentStock";
    _page = 0;
    loadListOfCurrentStock();
}

ListOfCurrentStock* ListOfCurrentStock::getInstance() {
    static ListOfCurrentStock singleton_instance;
    singleton_instance.initialize();
    return &singleton_instance;
}

MachineState* ListOfCurrentStock::pressKey(const char key) {
    MachineState* next = this;

    switch ( key ) {
    case '1':
        if (_page == 0)
            break;

        _page -= 1;
        loadListOfCurrentStock();
        break;
    case '2':
        _page += 1;
        if (NUMBER_PER_PAGE*_page >= _database->getNumberOfColumns()) {
            _page -= 1;
            break;
        }
        loadListOfCurrentStock();
        break;
    case '*':
        next = MainManagement::getInstance();
        break;
    }
    return next;
}

void ListOfCurrentStock::loadListOfCurrentStock() {
    char buf[32];
    int param_index = 0;
    std::string param;
    std::string prefix = "param_";
    for (int i = 0; i < NUMBER_PER_PAGE; i++) {
        uint32_t column = _page*NUMBER_PER_PAGE + i;
        uint32_t price = _database->getPrice(column);
        uint32_t quantity = _database->getQuantity(column);
        bool isOverRange = column >= _database->getNumberOfColumns();

        column += 1;// match user's recognize column
        param = prefix + itoa(param_index++, buf, 10);
        _data[param] = isOverRange ? "" : itoa(column, buf, 10);
        param = prefix + itoa(param_index++, buf, 10);
        _data[param] = isOverRange ? "" : itoa(price/1000, buf, 10);
        param = prefix + itoa(param_index++, buf, 10);
        _data[param] = isOverRange ? "" : itoa(quantity, buf, 10);
    }
    param = prefix + itoa(param_index++, buf, 10);
    _data[param] = std::string("p")+itoa(_page+1, buf, 10);
}