ESP-01 AP mode 網頁控制Arduino
===================


ESP-01作為橋接器，接收網頁資料並傳給Arduino並控制其腳位輸出

[參考資料](http://allaboutee.com/2015/01/02/esp8266-arduino-led-control-from-webpage/)


> **材料:**

> - Arduino UNO
> - ESP-01
> - 3V3電源供應

 1. 將程式上傳Arduino，內含sendData函式是用來下AT指令並且設定ESP-01，**esp8266.find()**取得網頁回傳字串，並擷取button id，控制該腳位
 2.  為ESP-01上電，等候一段時間，進入AP模式後，Wifi連上ESP-01
 3. 開啟寫好的Webpage，開始控制!
 
