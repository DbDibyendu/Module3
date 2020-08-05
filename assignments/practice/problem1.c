/** @file problem1.c
 *  @brief HeartBeat
 *  
 *  Getting Important Infomation from heartbeat device and uploading it to the MQQT Server 
 *  in JSON format to the client
 *  
 *  @author Dibyendu Biswas
 *  @bug I didn't find any from my side 
 */

/*
 *#####################################################################
 *  Initialization block
 *  ---------------------
 *  This block contains initialization code for this particular file.
 *  It typically contains Includes, constants or global variables used
 *  throughout the file.
 *#####################################################################
 */

/* --- Standard Includes --- */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> /* for strncpy */
#include <errno.h>
#include <time.h>
#include "MQTTClient.h"             // download this and include this from "https://github.com/eclipse/paho.mqtt.c"

/* includes for ipAddress */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
/* --- Project Includes --- */


/*
 *#####################################################################
 *  Process block
 *  -------------
 *  Solve all your problems here 
 *#####################################################################
 */

/* Declaring Global Variables */

#define CLIENTID    "HEARTBEAT_Information"
#define TOPIC       "MQTT"
#define QOS         1
#define TIMEOUT     10000L

char DeviceId[10];                               // for storing the devicId address location


/************************** 
 * Error-handling functions
 **************************/
/* $begin errorfuns */
/* $begin unixerror */
void unix_error(char *msg) /* unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}
/* $end unixerror */

void posix_error(int code, char *msg) /* posix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(code));
    exit(0);
}

void app_error(char *msg) /* application error */
{
    fprintf(stderr, "%s\n", msg);
    exit(0);
}
/* $end errorfuns */

FILE *Fopen(const char *filename, const char *mode)
{
   FILE *fp;

   if ((fp = fopen(filename, mode)) == NULL)
   unix_error((char*)"Fopen error");

   return fp;
}

void Fclose(FILE *fp) 
{
    if (fclose(fp) != 0)
    unix_error((char*)"Fclose error");
}



/** 
 *  @brief IpAddress
 *  
 *  finds out IpAddress of system
 *
 *  @return returns IpAddres
 */

const char *IP_ADDRESS()
{
 int fd;
 struct ifreq ifr;

 fd = socket(AF_INET, SOCK_DGRAM, 0);

 /* I want to get an IPv4 IP address */
 ifr.ifr_addr.sa_family = AF_INET;

 /* I want IP address attached to "eth0" */
 strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);

 ioctl(fd, SIOCGIFADDR, &ifr);

 close(fd);    

// returning ipAddress
 return inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);

}


/** 
 *  @brief DeviceId
 *  
 *  Gets the deviceId from /etc/shunya/deviceid
 *
 *  @return returns deviceId
 */

const char *DEVICE_ID(){
    FILE *fp=Fopen("/etc/shunya/deviceid","rb");
    fscanf(fp, "%[^\n]", DeviceId);
    return DeviceId;
}

/* Important Functions for asynchronous publication on MQTT Server  */

volatile MQTTClient_deliveryToken deliveredtoken;
void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    int i;
    char* payloadptr;
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: ");
    payloadptr = message->payload;
    for(i=0; i<message->payloadlen; i++)
    {
        putchar(*payloadptr++);
    }
    putchar('\n');
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}


/** 
 *  @brief Publishing MQTT in JSON format
 *  
 *  Getting all the details through different functions and connecting to the MQTT server to send
 *  the message to the client in JSON format
 *
 *  @return List all Function returns 
 */

int main (void)
{
    // Declaring all the variables
        unsigned long timestamp=(unsigned long)time(NULL);                         //getting the value of timestamp
        char eventType[10]="heartbeat";                                 // event type is fixed
        char deviceId[20];                                                          // creating char for storing deviceId
        char ipAddress[10];                                                     // creating char for storing ipAddress
        char time[10];                                                      // creaating char for timestamp
        strcpy(ipAddress,IP_ADDRESS());                                          // copying the address to the char variable
        sprintf(time, "%ld", timestamp);                                        // converting long to string
        int x;
        char url[100];

    // Getting User input about the x interval and server address
        printf("\nEnter value of x in seconds to send in interval:");
        scanf("%d",&x);
        printf("\nEnter URL of MQQT server:");
        scanf("%s",url);

    // Printing all the values
        printf("Address: \"%s\"\n",ipAddress);                             
        printf("device: \"%s\"\n",eventType);
        printf("timestamp: %s\n",time);
        strcpy(deviceId,DEVICE_ID());
        printf("deviceId: \"%s\"\n",deviceId);
    
    // Creating message which will be sent to the MQTT Server

        char msg[1000]="{\n    \"ipAddress\": \"";
        strcat(msg,ipAddress);
        strcat(msg,"\", \n    \"timestamp\": ");
        strcat(msg,time);
        strcat(msg,",\n    \"eventType\": \"");
        strcat(msg,eventType);
        strcat(msg,"\", \n    \"deviceId\": \"");
        strcat(msg,deviceId);
        strcat(msg,"\"\n}");

    // uploading the data to MQTT server

    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;
    MQTTClient_create(&client, url, CLIENTID,MQTTCLIENT_PERSISTENCE_NONE, NULL);                    // creating the Client with given url
    conn_opts.keepAliveInterval = x;                                            // time in seconds to send the data in intervals
    conn_opts.cleansession = 1;
    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }
    pubmsg.payload = msg;
    pubmsg.payloadlen = strlen(msg);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    deliveredtoken = 0;
    MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
    printf("\nWaiting for publication of\n %s\n"  "on topic %s for client with ClientID: %s\n", msg, TOPIC, CLIENTID);   // publishing the message if connected
    while(deliveredtoken != token);
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
    
    // Compile and run using command "gcc problem1.c -lpaho-mqtt3c"

}


