#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>

// Определяем переменные wifi
const char* ssid = "nikitos-2";  
const char* password = "0681830273"; 

uint8_t FAN = D5;
uint8_t RED_COL = D6;
uint8_t GREEN_COL = D7;
uint8_t BLUE_COL = D8;
uint8_t stepv = 50;
unsigned int fan_pwm = 80;
unsigned int red = 0;
unsigned int green = 0;
unsigned int blue = 0;
bool party;
// Web интерфейс для устройства
ESP8266WebServer server(80);


void setup() {
  analogWrite(FAN,255);
  delay(200);
  analogWrite(FAN,fan_pwm);
  Serial.begin(115200); // Устанавливаем скорость соединения с последовательным портом
// подключиться к вашей локальной wi-fi сети
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
// проверить, подключился ли wi-fi модуль к wi-fi сети
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(200);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
  server.on("/", handle_OnConnect);
  server.on("/fan_up", handle_fan_up);
  server.on("/fan_down", handle_fan_down);
  server.on("/red_up", handle_red_up);
  server.on("/red_down", handle_red_down);
  server.on("/green_up", handle_green_up);
  server.on("/green_down", handle_green_down);
  server.on("/blue_up", handle_blue_up);
  server.on("/blue_down", handle_blue_down);
  server.on("/rand", handle_rand);
  server.on("/lgbt", handle_lgbt);

  server.on("/black", handle_black);
  server.on("/white", handle_white);
  server.on("/red", handle_red);
  server.on("/green", handle_green);
  server.on("/blue", handle_blue);
  server.on("/yellow", handle_yellow);
  server.on("/orange", handle_orange);
  server.on("/lime", handle_lime);
  server.on("/magenta", handle_magenta);
  server.on("/violet", handle_violet);
  server.on("/cyan", handle_cyan);
  server.on("/sky", handle_sky);
  server.on("/rose", handle_rose);
  server.on("/indigo", handle_indigo);
  
//  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
  party = false;
}
  
void loop() {

  server.handleClient();

    Serial.println(fan_pwm);
    Serial.println(red);
    Serial.println(green);
    Serial.println(blue);
    Serial.println();

    if (party == true)
    {
      red=random(0,1023);
      green=random(0,1023);;
      blue=random(0,1023);;
      analogWrite(RED_COL,red);
      analogWrite(GREEN_COL,green);
      analogWrite(BLUE_COL,blue);
      server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue));
      delay(250);
    }
    delay(50);
}


void handle_OnConnect() 
{
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue)); 
}

void handle_fan_up() 
{
  fan_pwm+=stepv;
  if(fan_pwm>1023) fan_pwm=0;
  analogWrite(FAN,fan_pwm);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue)); 
}
void handle_fan_down() 
{
  fan_pwm-=stepv;
  if(fan_pwm>1023) fan_pwm=1023;
  analogWrite(FAN,fan_pwm);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue)); 
}
// red **********************************************
void handle_red_up() 
{
  party=false;
  red+=stepv;
  if(red>1023) red=0;
  analogWrite(RED_COL,red);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue)); 
}
void handle_red_down() 
{
  party=false;
  red-=stepv;
  if(red>1023) red=1023;
  analogWrite(RED_COL,red);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue)); 
}
// green ********************************************
void handle_green_up() 
{
  party=false;
  green+=stepv;
  if(green>1023) green=0;
  analogWrite(GREEN_COL,green);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue)); 
}
void handle_green_down() 
{
  party=false;
  green-=stepv;
  if(green>1023) green=1023;
  analogWrite(GREEN_COL,green);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue));
}
// blue *********************************************
void handle_blue_up() 
{
  party=false;
  blue+=stepv;
  if(blue>1023 && blue<1300) blue=0;
  analogWrite(BLUE_COL,blue);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue)); 
}
void handle_blue_down() 
{
  party=false;
  blue-=stepv;
  if(blue>1023) blue=1023;
  analogWrite(BLUE_COL,blue);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue));
}
//***************************************************
void handle_lgbt() 
{
    party = true;
}

void handle_rand() 
{
    party=false;
    red=random(0,1023);
    green=random(0,1023);;
    blue=random(0,1023);;
  analogWrite(RED_COL,red);
  analogWrite(GREEN_COL,green);
  analogWrite(BLUE_COL,blue);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue));
  party=false;
}

void handle_black() 
{
  party=false;
  red = 0;
  green = 0;
  blue = 0;
  analogWrite(RED_COL,red);
  analogWrite(GREEN_COL,green);
  analogWrite(BLUE_COL,blue);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue));
}

void handle_white() 
{
  party=false;
  red = 1023;
  green = 1023;
  blue = 1023;
  analogWrite(RED_COL,red);
  analogWrite(GREEN_COL,green);
  analogWrite(BLUE_COL,blue);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue));
}

void handle_red() 
{
  party=false;
  red = 1023;
  green = 0;
  blue = 0;
  analogWrite(RED_COL,red);
  analogWrite(GREEN_COL,green);
  analogWrite(BLUE_COL,blue);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue));
}

void handle_green() 
{
  party=false;
  red = 0;
  green = 1023;
  blue = 0;
  analogWrite(RED_COL,red);
  analogWrite(GREEN_COL,green);
  analogWrite(BLUE_COL,blue);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue));
}

void handle_blue() 
{
  party=false;
  red = 0;
  green = 0;
  blue = 1023;
  analogWrite(RED_COL,red);
  analogWrite(GREEN_COL,green);
  analogWrite(BLUE_COL,blue);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue));
}

void handle_yellow() 
{
  party=false;
  red = 1023;
  green = 300;
  blue = 0;
  analogWrite(RED_COL,red);
  analogWrite(GREEN_COL,green);
  analogWrite(BLUE_COL,blue);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue));
}

void handle_orange() 
{
  party=false;
  red = 1023;
  green = 150;
  blue = 0;
  analogWrite(RED_COL,red);
  analogWrite(GREEN_COL,green);
  analogWrite(BLUE_COL,blue);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue));
}

void handle_lime() 
{
  party=false;
  red = 1023;
  green = 800;
  blue = 0;
  analogWrite(RED_COL,red);
  analogWrite(GREEN_COL,green);
  analogWrite(BLUE_COL,blue);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue));
}

void handle_magenta() 
{
  party=false;
  red = 1023;
  green = 0;
  blue = 150;
  analogWrite(RED_COL,red);
  analogWrite(GREEN_COL,green);
  analogWrite(BLUE_COL,blue);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue));
}

void handle_violet() 
{
  party=false;
  red = 1023;
  green = 0;
  blue = 1023;
  analogWrite(RED_COL,red);
  analogWrite(GREEN_COL,green);
  analogWrite(BLUE_COL,blue);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue));
}

void handle_cyan() 
{
  red = 0;
  green = 750;
  blue = 1023;
  analogWrite(RED_COL,red);
  analogWrite(GREEN_COL,green);
  analogWrite(BLUE_COL,blue);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue));
}

void handle_sky() 
{
  party=false;
  red = 350;
  green = 550;
  blue = 1023;
  analogWrite(RED_COL,red);
  analogWrite(GREEN_COL,green);
  analogWrite(BLUE_COL,blue);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue));
}

void handle_rose() 
{
  party=false;
  red = 1023;
  green = 300;
  blue = 250;
  analogWrite(RED_COL,red);
  analogWrite(GREEN_COL,green);
  analogWrite(BLUE_COL,blue);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue));
}

void handle_indigo() 
{
  party=false;
  red = 75;
  green = 15;
  blue = 750;
  analogWrite(RED_COL,red);
  analogWrite(GREEN_COL,green);
  analogWrite(BLUE_COL,blue);
  server.send(200, "text/html", SendHTML(fan_pwm, red, green, blue));
}

String SendHTML(int pwm, int r,int g,int b)
{
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<meta charset=\"utf-8\">";
  ptr +="<title>-Управление кулером-</title>";
  
  ptr +="<style>";
//Скорость***************************
  ptr +=".s1 {";
  ptr +="background: orange;";
  ptr +="color: blue;" ;
  ptr +="font-size: 16pt;";
  ptr +="}";
  ptr +=".s2 {";
  ptr +="background: indigo; ";
  ptr +="color: cyan; " ;
  ptr +="font-size: 16pt; ";
  ptr +="}";
//Красный***************************
  ptr +=".r1 {";
  ptr +="background: red;";
  ptr +="color: white;" ;
  ptr +="font-size: 16pt;";
  ptr +="}";
  ptr +=".r2 {";
  ptr +="background: salmon; ";
  ptr +="color: white; " ;
  ptr +="font-size: 16pt; ";
  ptr +="}";
//Зеленый***************************
ptr +=".g1 {";
  ptr +="background: green;";
  ptr +="color: white;" ;
  ptr +="font-size: 16pt;";
  ptr +="}";
  ptr +=".g2 {";
  ptr +="background: mediumseagreen; ";
  ptr +="color: white; " ;
  ptr +="font-size: 16pt; ";
  ptr +="}";
//Синий*****************************
ptr +=".b1 {";
  ptr +="background: blue;";
  ptr +="color: white;" ;
  ptr +="font-size: 16pt;";
  ptr +="}";
  ptr +=".b2 {";
  ptr +="background: royalblue; ";
  ptr +="color: white; " ;
  ptr +="font-size: 16pt; ";
  ptr +="}";
//Случайный цвет  
  ptr +=".rand {";
  ptr +="background: black;";
  ptr +="color: orange;" ;
  ptr +="font-size: 20pt;";
  ptr +="}";
//Диско  
  ptr +=".disco {";
  ptr +="background: orange;";
  ptr +="color: black;" ;
  ptr +="font-size: 20pt;";
  ptr +="}";
  ptr +="</style>";
  
  ptr +="</head>\n";
  ptr +="<body>";
  ptr +="<p><h1>Скорость вентилятора</h1>";
  ptr +="<p>";
  ptr +="<button class=\"s1\" onclick=\"window.location.href = '/fan_up';\">Быстрее</button>";
  ptr +=" "+String(fan_pwm)+" ";
  ptr +="<button class=\"s2\" onclick=\"window.location.href = '/fan_down';\">Медленнее</button>";
  ptr +="<p>";
  //************************************************************************************************
  ptr +="<p>";
  ptr +="<p><h1>Управление цветом</h1>";
//  ptr +="<a class=\"button button-up\" href=\"/red_up\">Красный ярче </a>";
  ptr +="<button class=\"r1\" onclick=\"window.location.href = '/red_up';\">Ярче</button>";
  ptr +=" "+String(red)+" ";
  ptr +="<button class=\"r2\" onclick=\"window.location.href = '/red_down';\">Тусклее</button>";
  //************************************************************************************************
  ptr +="<p>";
  ptr +="<button class=\"g1\" onclick=\"window.location.href = '/green_up';\">Ярче</button>";
  ptr +=" "+String(green)+" ";
  ptr +="<button class=\"g2\" onclick=\"window.location.href = '/green_down';\">Тусклее</button>";
  //************************************************************************************************
  ptr +="<p>";
  ptr +="<button class=\"b1\" onclick=\"window.location.href = '/blue_up';\">Ярче</button>";
  ptr +=" "+String(blue)+" ";
  ptr +="<button class=\"b2\" onclick=\"window.location.href = '/blue_down';\">Тусклее</button>";
  //************************************************************************************************
  //************************************************************************************************
  ptr +="<p>";
  ptr +="<button class=\"rand\" onclick=\"window.location.href = '/rand';\">Случайный цвет</button>";
  ptr +="   ";
  ptr +="<button class=\"disco\" onclick=\"window.location.href = '/lgbt';\">Дискотека</button>";
  //************************************************************************************************
  ptr +="<p>";
  ptr +="<p>";
  ptr +="<table>";
  ptr +="<tr>";
  ptr +="<td><button onclick=\"window.location.href = '/black';\">Выключено</button></td>";
  ptr +="<td><button onclick=\"window.location.href = '/white';\">Белый</button></td>";
  ptr +="<td><button style=\"background-color:red;\" onclick=\"window.location.href = '/red';\">Красный</button></td>";
  ptr +="<td><button style=\"background-color:green;\" onclick=\"window.location.href = '/green';\">Зеленый</button></td>";
  ptr +="<td><button style=\"background-color:blue;\" onclick=\"window.location.href = '/blue';\">Синий</button></td>";
  ptr +="<td><button style=\"background-color:yellow;\" onclick=\"window.location.href = '/yellow';\">Желтый</button></td>";
  ptr +="<td><button style=\"background-color:orange;\" onclick=\"window.location.href = '/orange';\">Оранжевый</button></td>";
  ptr +="</tr>";
  ptr +="<tr>";
  ptr +="<td><button style=\"background-color:lime;\" onclick=\"window.location.href = '/lime';\">Салатовый</button></td>";
  ptr +="<td><button style=\"background-color:magenta;\" onclick=\"window.location.href = '/magenta';\">Маджента</button></td>";
  ptr +="<td><button style=\"background-color:violet;\" onclick=\"window.location.href = '/violet';\">Фиолетовый</button></td>";
  ptr +="<td><button style=\"background-color:dodgerblue;\" onclick=\"window.location.href = '/cyan';\">Голубой</button></td>";
  ptr +="<td><button style=\"background-color:cyan;\" onclick=\"window.location.href = '/sky';\">Небесный</button></td>";
  ptr +="<td><button style=\"background-color:pink;\" onclick=\"window.location.href = '/rose';\">Розовый</button></td>";
  ptr +="<td><button style=\"background-color:mediumslateblue;\" onclick=\"window.location.href = '/indigo';\">Индиго</button></td>";
  ptr +="</tr>";
  ptr +="</table>";
  
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
