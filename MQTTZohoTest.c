/*
paho MQTT client built for linux

git clone https://github.com/eclipse/paho.mqtt.c.git
cd org.eclipse.paho.mqtt.c.git
make
sudo make install

sudo apt install libjson-c-dev


gcc -o MQTTOutput MQTTZohoTest.c -lpaho-mqtt3c -ljson-c

*/


#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "MQTTClient.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "config.c" // config file 
#include "stdlib.h"
#include "json-c/json.h"
#include "logger.c"

int getRandom()
{
    srand(time(0));

    int lower = pow(10,(RANDOMLENGTH-1));
    int upper = (pow(10,RANDOMLENGTH)-1);
    int num = (rand() %
           (upper - lower + 1)) + lower;

    return num;

}





char* createJoson(int value,int time)
{
     /*Creating a json object*/
      json_object * jobj = json_object_new_object();


      json_object *jVal = json_object_new_int(value);
      json_object *jtime = json_object_new_int(time);


      json_object_object_add(jobj,"value", jVal);
      json_object_object_add(jobj,"timestamp", jtime);

      char *JsonOut;
      JsonOut=(char*)malloc( strlen(json_object_to_json_string(jobj))* sizeof(char) );
      strcpy(JsonOut, json_object_to_json_string(jobj));
      return JsonOut;
}



int main(int argc, char* argv[])
{

    //callConfig();

    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    char *PAYLOAD;
    PAYLOAD=(char*)malloc( strlen(createJoson(getRandom(),time(NULL)))* sizeof(char) );
    strcpy(PAYLOAD,createJoson(getRandom(),time(NULL)));


    MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    // get error report
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        // display the error code
        printf("Failed to connect, return code %d\n", rc);
        createLog("Failed to connect");
        exit(-1);
    }



    pubmsg.payload = PAYLOAD;
    pubmsg.payloadlen = strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
    printf("Waiting for up to %d seconds for publication of %s\n"
            "on topic %s for client with ClientID: %s\n",
            (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    if(LOGSTATUS==1)
    {
        createLog(PAYLOAD);
    }
    
    return rc;
}


