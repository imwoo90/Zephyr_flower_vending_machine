#include "BanknoteReader.h"

void BanknoteReader::notifyBillData() {
    int billdata = getBillData();
    if (billdata == 0)
        return;

    for (auto cb : _onRecognizedBankNotes) {
        cb(billdata);
    }
}

void BanknoteReader::registerBillDataCallBack(std::function<void(const int)> onRecognizedBankNote) {
    _onRecognizedBankNotes.push_back(onRecognizedBankNote);
}

int BanknoteReader::initialized() {
    disable();
    return 0;
}
