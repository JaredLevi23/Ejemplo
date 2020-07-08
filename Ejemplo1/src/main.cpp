#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

//SE REALIZA LA CONEXION WEB
class conexionWeb{
  private:
  
  public:
    conexionWeb(const char *_SSID, const char* _PASSWORD ){
      WiFi.begin(_SSID, _PASSWORD);
      while(WiFi.status()!= WL_CONNECTED){
          delay(500);
          Serial.print("...");
      }
    }

}; 

//SE OBTIENEN LOS VALORES DE LA FECHA Y HORA
class DateTime
{
private:
  int defaultTime;
  struct tm timeinfo;
  const char *ntpServer = "pool.ntp.org";
  const long gmtOffset_sec = 0;
  const int daylightOffset_sec = 0;

public:
  char timeStringBuff[20];
  DateTime()
  {
    defaultTime = 0;
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    getTime();
  }

  void getTime()
  {   
    setLocalTime();
  }

  void setLocalTime()
  {
    
    if (!getLocalTime(&timeinfo))
    {
    }
    strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
  }
};

conexionWeb *webInterface;
DateTime *reloj;
StaticJsonDocument<512> horaActual;

//NOMBRE Y CLAVE DE ACCESO A RED
const char *ssid="Ubee16F8-2.4G";
const char *passwrd="5F99F616F8";

//REALIZA LA CONEXION A LA RED 
void setup() {
  Serial.begin(115200);
  webInterface= new conexionWeb(ssid,passwrd);
  //CREACION DE OBJETO DE FECHA Y HORA
  reloj=new DateTime();
  
}

int sumatoria=0;

void loop() {
  sumatoria++;
  horaActual.clear();
  reloj->getTime();
  horaActual["hora"]=reloj->timeStringBuff;
  horaActual["Sumatoria"]=sumatoria;
  serializeJson(horaActual,Serial);
  Serial.println("");
  delay(1000);
}

