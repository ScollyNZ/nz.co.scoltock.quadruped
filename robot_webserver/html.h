const char html[] PROGMEM =\
"<html>\
  <head>\
    <title>Scoltock's Caravan</title>\
    <link rel=\"stylesheet\" type=\"text/css\" href=\"css\">\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
      <script>\
           var socket;\
\
           function begin() {\
               socket = new WebSocket('ws://' + window.location.hostname + '/ws','blah');\
\
            socket.addEventListener('message', function (event) {\
            if (event.data.charAt(0)==\"{\") {\
                lightStatus = JSON.parse(event.data);\
                document.getElementById(lightStatus.light).checked = lightStatus.state;\
                }\
            });\
            }\
\
\
           function changeStatus(control) {\
                var lightStatus={};\
                lightStatus.light=control.id;\
                lightStatus.state=control.checked?document.getElementById(\"kitchenBrightness\").value:0;\
                socket.send(JSON.stringify(lightStatus));\
                }\
      </script>\
  </head>\
  <body onload=\"begin()\">\
    <h1>Lighting Control</h1>\
    <div style=\"width:600px\">\
       <h2>Kitchen</h2>\
       <div class=\"onoffswitch\"> <input type=\"checkbox\" name=\"kitchen\" class=\"onoffswitch-checkbox\" id=\"kitchen\" onchange=\"changeStatus(this)\">\
          <label class=\"onoffswitch-label\" for=\"kitchen\">\
             <span class=\"onoffswitch-inner\"></span>\
             <span class=\"onoffswitch-switch\"></span>\
          </label>\
       </div>\
       <div class=\"slidecontainer\">\
  <input type=\"range\" min=\"1\" max=\"100\" value=\"100\" min=\"10\" class=\"slider\" id=\"kitchenBrightness\" onchange=\"changeStatus(document.getElementById('kitchen'))\">\
</div>\
       <h2>Double Bed</h2>\
       <div class=\"onoffswitch\"> <input type=\"checkbox\" name=\"doublebed\" class=\"onoffswitch-checkbox\" id=\"doublebed\" onchange=\"changeStatus(this)\">\
          <label class=\"onoffswitch-label\" for=\"doublebed\">\
             <span class=\"onoffswitch-inner\"></span>\
             <span class=\"onoffswitch-switch\"></span>\
          </label>\
       </div>\
       <h2>Bunks</h2>\
       <div style=\"float:left;width:100%\">\
         <div style=\"float:left\">\
           <h3 style=\"float:left\">left</h3>\
           <div style=\"float:right\" class=\"onoffswitch\"><input type=\"checkbox\" name=\"bunk-left\" class=\"onoffswitch-checkbox\" id=\"bunk-left\"  onchange=\"changeStatus(this)\">\
              <label class=\"onoffswitch-label\" for=\"bunk-left\">\
                 <span class=\"onoffswitch-inner\"></span>\
                 <span class=\"onoffswitch-switch\"></span>\
              </label>\
           </div>\
         </div>\
         <div style=\"float:right\">\
           <h3 style=\"float:left\">right</h3>\
           <div style=\"float:right\" class=\"onoffswitch\"><input type=\"checkbox\" name=\"bunk-right\" class=\"onoffswitch-checkbox\" id=\"bunk-right\"  onchange=\"changeStatus(this)\">\
              <label class=\"onoffswitch-label\" for=\"bunk-right\">\
                 <span class=\"onoffswitch-inner\"></span>\
                 <span class=\"onoffswitch-switch\"></span>\
              </label>\
           </div>\
         </div>\
       </div>\
       <h2>Tables</h2>\
       <div style=\"float:left\">\
          <h3 style=\"float:left\">front</h3>\
          <div style=\"float:right\" class=\"onoffswitch\"><input type=\"checkbox\" name=\"table-front\" class=\"onoffswitch-checkbox\" id=\"table-front\"  onchange=\"changeStatus(this)\">\
            <label class=\"onoffswitch-label\" for=\"table-front\">\
               <span class=\"onoffswitch-inner\"></span>\
               <span class=\"onoffswitch-switch\"></span>\
            </label>\
         </div>\
       </div>\
       <div style=\"float:right\">\
       <h3 style=\"float:left\">rear</h3>\
         <div style=\"float:right\" class=\"onoffswitch\"><input type=\"checkbox\" name=\"table-rear\" class=\"onoffswitch-checkbox\" id=\"table-rear\"  onchange=\"changeStatus(this)\">\
            <label class=\"onoffswitch-label\" for=\"table-rear\">\
               <span class=\"onoffswitch-inner\"></span>\
               <span class=\"onoffswitch-switch\"></span>\
            </label>\
         </div>\
       <div>\
    </div>\
  </body>\
</html>";
