  server.on("/temp.json", [](){
    String a="";
    a+="{\"temp\":" + (String)(19 + random(10)) + ",\"humid\":" + (String)20 + "}";
    server.send(200, "application/json", a);
    a="";
  });

可用jQuery網頁動態取得以上溫溼度資料