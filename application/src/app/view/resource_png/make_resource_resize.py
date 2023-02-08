# Make resource using powerpoint and export png files

import os
import shutil
import natsort
from PIL import Image
from PIL import ImageFilter

resource_path = './'

list_name = [
    'SystemCheck.png',
    'Selling.png',
    'StopSelling.png',
    'EnterProductNumber.png',
    'EnterProductNumberNoGoods.png',
    'InputMoney_0.png',
    'InputMoney_1.png',
    'SystemSetting.png',
    'VendingMachineModeSetting.png',
    'BanknoteReaderModeSetting.png',
    'NumberOfRelaySetting.png',
    'NumberOfChannelSetting.png',
    'MotorTypeSetting.png',
    'MatchingChannelAndColumn.png',
    'EnterPasswordOfPasswordChange.png',
    'PasswordChange.png',
    'EnterPasswordOfSystemManagement.png',
    'EnterPasswordOfSystemSetting.png',
    'EnterPasswordOfVendingMachineModeSetting.png',
    'EnterPasswordOfMainManagement.png',
    'EnterPasswordOfAdditionalStock.png',
    'EnterPasswordOfManualSales.png',
    'ListOfColumnData.png',
    'MainManagement.png',
    'SalesInfo.png',
    'SetGoods.png',
    'WorkingTest.png',
    'ColumnTestManul.png',
    'ColumnTestSection.png',
    'ColumnTestAll.png',
    'ListOfCurrentStock.png',
    'ListOfAdditionalStock.png',
    'AdditionalStock.png',
    'ManualSales.png',
]

idx = 0
for f_png in natsort.natsorted(os.listdir(resource_path)):
    if 'png' in f_png or 'PNG' in f_png:
        change_name = list_name[idx]
        src = os.path.join(resource_path, f_png)
        dst = os.path.join(resource_path, change_name)
        print(f'{f_png}  {change_name}')
        os.rename(src, dst)
        idx += 1

for f_png in list_name:
    src = os.path.join(resource_path, f_png)
    ori = Image.open(src)
    # # Grayscale
    # ori = ori.convert("L")
    # # Threshold
    # ori = ori.point(lambda p : 255 if p > 190 else 0)
    # Mnno
    ori = ori.convert("1")
    ori = ori.resize((256, 160), Image.HAMMING)
    ori.save(src)
    ori.close()