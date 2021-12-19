// #define ADDRESS     "tcp://localhost:1883"
// #define CLIENTID    "DossTestIOT"
// #define TOPIC       "device1"
// #define QOS         1
// #define TIMEOUT     10000L
// #define RANDOMLENGTH   4
// #define LOGSTATUS   0 // 1-ON, 0-FF

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

void callConfig()
{
    FILE *fp;
    char buffer[1024];
    struct json_object *parsed_json;

    struct json_object * ADDRESS;
    struct json_object * CLIENTID;
    struct json_object * TOPIC;
    struct json_object * QOS;
    struct json_object * TIMEOUT;
    struct json_object * RANDOMLENGTH;
    struct json_object * LOGSTATUS;

    fp = fopen("config.json","r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);
    //json_object * jobj = json_tokener_parse(string);

    json_object_object_get_ex(parsed_json, "ADDRESS",&ADDRESS);
    json_object_object_get_ex(parsed_json, "CLIENTID",&CLIENTID);
    json_object_object_get_ex(parsed_json, "TOPIC",&TOPIC);
    json_object_object_get_ex(parsed_json, "QOS",&QOS);
    json_object_object_get_ex(parsed_json, "TIMEOUT",&TIMEOUT);
    json_object_object_get_ex(parsed_json, "RANDOMLENGTH",&RANDOMLENGTH);
    json_object_object_get_ex(parsed_json, "LOGSTATUS",&LOGSTATUS);

    #define ADDRESS json_object_get_string(ADDRESS);
    #define CLIENTID json_object_get_string(CLIENTID);
    #define TOPIC json_object_get_string(TOPIC);
    #define QOS json_object_get_int(QOS);
    #define TIMEOUT json_object_get_string(TIMEOUT);
    #define RANDOMLENGTH json_object_get_int(RANDOMLENGTH);
    #define LOGSTATUS json_object_get_int(LOGSTATUS);
}