// #include "logger.h"

FILE *fp ;
static int SESSION_TRACKER; //Keeps track of session

char* print_time()
{
    int size = 0;
    time_t t;
    char *buf;
    
    t=time(NULL); /* get current calendar time */
    
    char *timestr = asctime( localtime(&t) );
    timestr[strlen(timestr) - 1] = 0;  //Getting rid of \n
    
    size = strlen(timestr)+ 1 + 2; //Additional +2 for square braces
    buf = (char*)malloc(size);
    
    memset(buf, 0x0, size);
    snprintf(buf,size,"[%s]", timestr);
   
    return buf;
}



char* createLog(char * logdata)
{ 
    //printf("====%s",logdata);
    //exit(0);
    FILE* fp;
    fp = fopen("mqttLog.log", "a+");
    fprintf(fp,"%s" ,print_time());
    fprintf(fp," ADDRESS : "); 
    fprintf(fp,"%s" ,ADDRESS);
    fprintf(fp," | CLIENTID : "); 
    fprintf(fp,"%s" ,CLIENTID); 
    fprintf(fp," | TOPIC : "); 
    fprintf(fp,"%s" ,TOPIC); 
    fprintf(fp," | Data : "); 
    fprintf(fp,"%s" ,logdata); 
    fprintf(fp,"\n"); 
    
    fclose(fp);
}