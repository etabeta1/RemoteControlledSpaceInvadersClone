
/*
 * remote controlled space invader clone for nodemcu 1.0 made by Andrea Oggioni
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "SpaceInvaders";
const char* password = "12345678";

IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);
int numToSend;
unsigned long long int timer;
void setup()
{
    pinMode(5, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(0, OUTPUT);
    Serial.begin(115200);
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    server.on("/", handle_OnConnect);
    server.on("/0", nope);
    server.on("/1", left);
    server.on("/2", right);
    server.on("/3", left_right);
    server.on("/4", shoot);
    server.on("/5", left_shoot);
    server.on("/6", right_shoot);
    server.on("/7", left_right_shoot);
    server.onNotFound(nope);

    server.begin();
    digitalWrite(0, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    Serial.println("HTTP server started");
}

void loop()
{
    if (millis() - timer > 15) {
        /*
     * pin4: left
     * pin5: right
     * pin0: shoot
     */
        timer = millis();
        switch (numToSend) {
        case 0:
            digitalWrite(0, LOW);
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
            break;
        case 1:
            digitalWrite(0, LOW);
            digitalWrite(4, HIGH);
            digitalWrite(5, LOW);
            break;
        case 2:
            digitalWrite(0, LOW);
            digitalWrite(4, LOW);
            digitalWrite(5, HIGH);
            break;
        case 3:
            digitalWrite(0, LOW);
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
            break;
        case 4:
            digitalWrite(0, HIGH);
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
            break;
        case 5:
            digitalWrite(0, HIGH);
            digitalWrite(4, HIGH);
            digitalWrite(5, LOW);
            break;
        case 6:
            digitalWrite(0, HIGH);
            digitalWrite(4, LOW);
            digitalWrite(5, HIGH);
            break;
        case 7:
            digitalWrite(0, HIGH);
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
            break;
        default:
            digitalWrite(0, LOW);
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
            break;
        }
    }
    server.handleClient();
}

void handle_OnConnect() {}
void nope()
{
    numToSend = 0;
    server.send(200, "text/html", " ");
    Serial.println(0);
}
void left()
{
    numToSend = 1;
    server.send(200, "text/html", " ");
    Serial.println(1);
}
void right()
{
    numToSend = 2;
    server.send(200, "text/html", " ");
    Serial.println(2);
}
void left_right()
{
    numToSend = 3;
    server.send(200, "text/html", " ");
    Serial.println(3);
}
void shoot()
{
    numToSend = 4;
    server.send(200, "text/html", " ");
    Serial.println(4);
}
void left_shoot()
{
    numToSend = 5;
    server.send(200, "text/html", " ");
    Serial.println(5);
}
void right_shoot()
{
    numToSend = 6;
    server.send(200, "text/html", " ");
    Serial.println(6);
}
void left_right_shoot()
{
    numToSend = 7;
    server.send(200, "text/html", " ");
    Serial.println(7);
}
