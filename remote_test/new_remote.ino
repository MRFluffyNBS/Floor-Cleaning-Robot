/*  
 New code that is adapted from previous remote testing...esp32 can now also act as a remote access point and and commands
 sent with html is faster */

#include <WiFi.h>
#include <WebServer.h>
#include "roomba_motors.h"

// Replace with your network credentials
const char* ssid     = "ssid";
const char* password = "password";

// Create an instance of the WebServer on port 80
WebServer server(80);

//right motor pin1 and pin2
const int motor_pin1 = 16;
const int motor_pin2 = 17;
//left motor pin3 and pin4 
const int motor_pin3 = 27;
const int motor_pin4 = 33; 
//duration and speed settings
const int duration = -1; //set the duration to -1 for the motors to turn continously until method stop() is called
int speed = 255;
//Motors initalize
Motors roomba(motor_pin1, motor_pin2, motor_pin3, motor_pin4, speed);

int dutyCycle = 0;
String valueString = String(0);

void handleRoot() {
  const char html[] PROGMEM = R"rawliteral(
  <!DOCTYPE HTML><html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <style>
      html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; }
      .button { -webkit-user-select: none; -moz-user-select: none; -ms-user-select: none; user-select: none; background-color: #4CAF50; border: none; color: white; padding: 12px 28px; text-decoration: none; font-size: 26px; margin: 1px; cursor: pointer; }
      .button2 {background-color: #555555;}
    </style>
    <script>
      var repeatId; // Keep ID value to we clear repeating.
      var count = 0; // Count to see the number of times of repeating


      function moveForward() { 
        repeatId = setInterval(
            // This function will be invoked after a period time
            function() {
            console.log("Holding" + (++count) + ", your value: " + value);
          }, 
          1000 // Repeat after 1 second.
        );
        fetch('/forward'); 
      }
      function moveLeft() { 
        repeatId = setInterval(
              // This function will be invoked after a period time
              function() {
              console.log("Holding" + (++count) + ", your value: " + value);
          }, 
          1000 // Repeat after 1 second.
        );
        fetch('/left'); 
      }
      function stopRobot() { fetch('/stop'); }
      function moveRight() {
        repeatId = setInterval(
            // This function will be invoked after a period time
            function() {
            console.log("Holding" + (++count) + ", your value: " + value);
          }, 
          1000 // Repeat after 1 second.
        );
        fetch('/right'); 
      }
      function moveReverse() { 
        repeatId = setInterval(
            // This function will be invoked after a period time
            function() {
            console.log("Holding" + (++count) + ", your value: " + value);
          }, 
          1000 // Repeat after 1 second.
        );
        fetch('/reverse'); 
      }

      function updateMotorSpeed(pos) {
        document.getElementById('motorSpeed').innerHTML = pos;
        fetch(`/speed?value=${pos}`);
      }
      
      function start() {
          repeatId = setInterval(
            // This function will be invoked after a period time
            function() {
            console.log("Holding" + (++count) + ", your value: " + value);
          }, 
          1000 // Repeat after 1 second.
        );
        moveForward();
      }
      function end() {
        clearInterval(repeatId);
        count = 0;
        stopRobot();
      }
    </script>
  </head>
  <body>
    <h1>ESP32 Motor Control</h1>
    <p><button class="button" onmousedown="moveForward()" touchstart="moveForward()" onmouseup="end()" onmouseleave="end()" onmouseout="end()" touchend="end()" touchcancel="end()">FORWARD</button></p>
    <div style="clear: both;">
      <p>
        <button class="button" onmousedown="moveLeft()" touchstart="moveLeft()" onmouseup="end()" onmouseleave="end()" onmouseout="end()" touchend="end()" touchcancel="end()">LEFT</button>
        <button class="button button2" onclick="stopRobot()">STOP</button>
        <button class="button" onmousedown="moveRight()" touchstart="moveRight()" onmouseup="end()" onmouseleave="end()" onmouseout="end()" touchend="end()" touchcancel="end()">RIGHT</button>
      </p>
    </div>
    <p><button class="button" onmousedown="moveReverse()" touchstart="moveReverse()" onmouseup="end()" onmouseleave="end()" onmouseout="end()" touchend="end()" touchcancel="end()">REVERSE</button></p>
    <p>Motor Speed: <span id="motorSpeed">0</span></p>
    <input type="range" min="0" max="100" step="25" id="motorSlider" oninput="updateMotorSpeed(this.value)" value="0"/>
  </body>
  </html>)rawliteral";
  server.send(200, "text/html", html);
}

void handleForward() {
  roomba.forward();
  server.send(200);
}

void handleLeft() {
  roomba.left();
  server.send(200);
}

void handleStop() {
  roomba.stop();  
  server.send(200);
}

void handleRight() {
  roomba.right(); 
  server.send(200);
}

void handleReverse() {
  roomba.reverse();         
  server.send(200);
}

void handleSpeed() {
  if (server.hasArg("value")) {
    valueString = server.arg("value");
    int value = valueString.toInt();
    if (value == 0) {
      roomba.setSpeed(0); 
    } else { 
      dutyCycle = map(value, 25, 100, 200, 255);
      roomba.setSpeed(dutyCycle);
      Serial.println("Motor speed set to " + String(value));
    }
  }
  server.send(200);
}

void setup() {
  Serial.begin(115200);

  // Set the Motor pins as outputs
  roomba.begin();
  roomba.printMotors();
  
  /*// Connect to Wi-Fi
  Serial.println("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("To control roomba, input http://");
  Serial.print(IP);
  Serial.println("   into your search bar.");*/

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Define routes
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/left", handleLeft);
  server.on("/stop", handleStop);
  server.on("/right", handleRight);
  server.on("/reverse", handleReverse);
  server.on("/speed", handleSpeed);

  // Start the server
  server.begin();
}

void loop() {
  server.handleClient();
}
