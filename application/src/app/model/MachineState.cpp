#include <MachineState.h>

std::function<void(const int)> MachineState::_timeoutCallback;
std::function<void(std::unordered_map<std::string, std::string>)> MachineState::_onChangedCallback;
std::unordered_map<std::string, std::string> MachineState::_data;
MachineData* MachineState::_database;

char *itoa(int num, char *str, int base)
{
    char *ptr = str, *ptr1 = str, tmp_char;
    int tmp_value;

    if (base < 2 || base > 36) {
        *str = '\0';
        return str;
    }

    do {
        tmp_value = num;
        num /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - num * base)];
    } while (num);

    if (tmp_value < 0) {
        *ptr++ = '-';
    }

    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }

    return str;
}