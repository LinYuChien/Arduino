**AT指令設定HC-05模組參考:**

 1. http://coopermaa2nd.blogspot.tw/2012/07/arduino-as-usb-to-ttl-adapter.html
 2. https://www.youtube.com/watch?v=fkS1elBSzgs


----------
**第一支測試程式:**
http://goo.gl/PulGt8
[註]手機安裝APK後先開藍芽，找到AT設定的名稱跟密碼後，開啟APP的BTList找到該名稱


----------


**結論:**
AT設定時將模組Vcc接上5V後需按下Reset(之後與MCU收發資料時可能也需要這個步驟)，進入可接收AT命令的狀態時，模組上的LED會慢速閃爍(間格約2秒)，Serial monitor要選擇**NL & CR**否則看不到OK訊息


----------


![enter image description here](http://i.imgur.com/3FB3YDh.jpg)


