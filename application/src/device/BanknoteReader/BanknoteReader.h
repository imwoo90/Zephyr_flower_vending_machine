#ifndef BANKNOTE_READER_H
#define BANKNOTE_READER_H
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include <functional>
#include <vector>
#include <string>

class BanknoteReader {
private:
    std::vector<std::function<void(const int)> > _onRecognizedBankNotes;
public:
    std::string _name;

    void notifyBillData();

    void registerBillDataCallBack(std::function<void(const int)> onRecognizedBankNote);
    virtual int initialized();
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual int getBillData() = 0;
};

#endif