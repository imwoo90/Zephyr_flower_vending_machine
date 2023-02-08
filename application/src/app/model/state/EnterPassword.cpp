#include "EnterPassword.h"
#include "Selling.h"
#include "SystemSetting.h"

#include <algorithm>

MachineState* EnterPassword::pressKey(const char key) {
    MachineState* next = this;
    switch ( key ) {
    case '#':{
        std::string &param_0 = _data["param_0"];
        uint32_t pw = std::stoi(param_0);
        if (_isChangePasswords || isMatched(pw)) {
            next = decide(pw);
        }
        break;}
    case '*':{
        next = cancel();
        break;}
    default:{ //1~9
        std::string &param_0 = _data["param_0"];
        rotate(param_0.begin(), param_0.begin()+1, param_0.end());
        param_0[param_0.length()-1] = key;
        break;}
    }
    return next;
}