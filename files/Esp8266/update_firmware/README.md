燒寫ESP-01韌體(2016/08/05更新)
----------

esp8266 firmware update with nodemcu firmware programmer
----------

**舊版AT回應資料:**

![enter image description here](http://i.imgur.com/FzmK4c9.png)

> 剛買來時是舊版的韌體，下AT+RST指令最後一行為invalid而不是Ready，無法正常重置，也無法更改SSID以及Password，於[安信可公司](http://wiki.ai-thinker.com/doku.php)的資料並無找到此韌體的資料，因此更新韌體版本

**使用材料**


 - USB TTL Serial  FT232
 - ESP-01
 - [ESP8266Flasher.exe](https://github.com/nodemcu/nodemcu-flasher/tree/master/Win32/Release)
 - v0.9.2.4 AT Firmware-ESPFIX.bin

**更新步驟** [參考資料](https://ruten-proteus.blogspot.tw/2014/12/esp8266-firmware-burning.html) 

    FT232電流足夠，不需要再外接電源模組

 **接線**

> FT232_Tx       **———** ESP01_Rx
> FT232_Rx      **———** ESP01_Tx
> FT232_3.3v    **———** ESP01_Vcc & ESP01_CH_PD
> FT232_GND    **———** ESP01_GND & **ESP01_GPIO0**

[![](http://i.imgur.com/eb717No.png)](http://www.pighixxx.com/test/portfolio-items/esp8266/)

    GPIO0接地才能進入燒寫模式

 2. 開啟ESP8266Flasher.exe
 3. 接上USB to TTL 打開Log選擇對應的COM port(FT232)
 4. 於Config選擇韌體(v0.9.2.4 AT Firmware-ESPFIX.bin)燒入位址0x00000
 5. 於Advanced修改硬體資訊(見舊版AT回應資料)
 6. 打開麵包板電源模組，於Operation並點擊"Flash"，開始燒寫

**更新韌體後AT回應資料**

![enter image description here](http://i.imgur.com/xrAi5YE.png)

> AT+RST可以正常回傳Ready，也可以更改SSID與Password了

