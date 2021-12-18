#define ADDRESS     "tcp://localhost:1883"
#define CLIENTID    "DossTestIOT"
#define TOPIC       "DOSSVAL"
#define QOS         1
#define TIMEOUT     10000L
//define PAYLOAD		"121212"



/*

Notes : 


The server listens on the following ports:

    1883 : MQTT, unencrypted, unauthenticated
    1884 : MQTT, unencrypted, authenticated
    8883 : MQTT, encrypted, unauthenticated
    8884 : MQTT, encrypted, client certificate required
    8885 : MQTT, encrypted, authenticated
    8886 : MQTT, encrypted, unauthenticated
    8887 : MQTT, encrypted, server certificate deliberately expired
    8080 : MQTT over WebSockets, unencrypted, unauthenticated
    8081 : MQTT over WebSockets, encrypted, unauthenticated
    8090 : MQTT over WebSockets, unencrypted, authenticated
    8091 : MQTT over WebSockets, encrypted, authenticated
*/