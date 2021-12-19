/*
paho MQTT client built for linux

git clone https://github.com/eclipse/paho.mqtt.c.git
cd org.eclipse.paho.mqtt.c.git
make
sudo make install

sudo apt install libjson-c-dev


gcc -o random MQTTZohoTest.c -lpaho-mqtt3c -ljson-c

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

      /*Creating a json string*/
     // json_object *jstringVal = json_object_new_string("Joys of Programming");

      /*Creating a json integer*/
      json_object *jVal = json_object_new_int(value);
      json_object *jtime = json_object_new_int(time);

      // /*Creating a json boolean*/
      // json_object *jboolean = json_object_new_boolean(1);

      // /*Creating a json double*/
      // json_object *jdouble = json_object_new_double(2.14);

      // /*Creating a json array*/
      // json_object *jarray = json_object_new_array();

      // /*Creating json strings*/
      // json_object *jstring1 = json_object_new_string("c");
      // json_object *jstring2 = json_object_new_string("c++");
      // json_object *jstring3 = json_object_new_string("php");

      /*Adding the above created json strings to the array*/
      // json_object_array_add(jarray,jstring1);
      // json_object_array_add(jarray,jstring2);
      // json_object_array_add(jarray,jstring3);

      /*Form the json object*/
      /*Each of these is like a key value pair*/
      json_object_object_add(jobj,"value", jVal);
      json_object_object_add(jobj,"timestamp", jtime);


      /*Now printing the json object*/
      //printf ("The json object created: %s",json_object_to_json_string(jobj));

      char *JsonOut;
      JsonOut=(char*)malloc( strlen(json_object_to_json_string(jobj))* sizeof(char) );
      //sprintf(JsonOut, "%s", json_object_to_json_string(jobj));
      strcpy(JsonOut, json_object_to_json_string(jobj));
      return JsonOut;
}

int main(int argc, char* argv[])
{



    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    char *PAYLOAD;
    PAYLOAD=(char*)malloc( strlen(createJoson(getRandom(),time(NULL)))* sizeof(char) );
    strcpy(PAYLOAD,createJoson(getRandom(),time(NULL)));



    //strcpy(PAYLOAD,currentTime);
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
   
    createLog(PAYLOAD);
    return rc;
}


