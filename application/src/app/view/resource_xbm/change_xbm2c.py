# https://www.imageconvert.org/png-to-xbm
# Change to xbm file from png

import os
import shutil

resource_path = './'

list_name = [
    'SystemCheck',
    'Selling',
    'StopSelling',
    'EnterProductNumber',
    'EnterProductNumberNoGoods',
    'InputMoney_0',
    'InputMoney_1',
    'SystemSetting',
    'VendingMachineModeSetting',
    'BanknoteReaderModeSetting',
    'NumberOfRelaySetting',
    'NumberOfChannelSetting',
    'MotorTypeSetting',
    'MatchingChannelAndColumn',
    'EnterPasswordOfPasswordChange',
    'PasswordChange',
    'EnterPasswordOfSystemManagement',
    'EnterPasswordOfSystemSetting',
    'EnterPasswordOfVendingMachineModeSetting',
    'EnterPasswordOfMainManagement',
    'EnterPasswordOfAdditionalStock',
    'EnterPasswordOfManualSales',
    'ListOfColumnData',
    'MainManagement',
    'SalesInfo',
    'SetGoods',
    'WorkingTest',
    'ColumnTestManul',
    'ColumnTestSection',
    'ColumnTestAll',
    'ListOfCurrentStock',
    'ListOfAdditionalStock',
    'AdditionalStock',
    'ManualSales',
]
list_name.sort()

idx = 0
for f_xbm in  sorted(os.listdir(resource_path)):
    if '.xbm' in f_xbm:
        keyword = list_name[idx]
        src = os.path.join(resource_path, f_xbm)
        dst = os.path.join(resource_path, f'../resource/{keyword}.c')

        print(dst)
        with open(src) as f:
            newText = f.read().replace(f_xbm[:-4], keyword).replace('static char', 'const unsigned char')
            f.close()
        with open(dst, 'w') as f:
            f.write(newText)
            f.close()

        # shutil.copy(src, dst)
        idx += 1
