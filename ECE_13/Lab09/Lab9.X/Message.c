/* 
 * File:   Negotiation.c
 * Author: kgshah
 *
 * Created on March 10, 2022, 12:49 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Message.h"
#include "string.h"
#include "BOARD.h"

char ongoingdecode[MESSAGE_MAX_LEN];
int ongoingdecodeoffset = 0;

uint8_t Message_CalculateChecksum(const char* payload){
    int to_return = 0;
    for (int i = 0;i<strlen(payload);i++){
        to_return = to_return^payload[i];
    }
    return to_return;
}

int Message_ParseMessage(const char* payload, const char* checksum_string, BB_Event * message_event){
    if (strlen(checksum_string)!=2){
        message_event->type = BB_EVENT_ERROR;
        message_event->param0 = 0;
        message_event->param1 = 0;
        message_event->param2 = 0;
        return STANDARD_ERROR;
    }
    if (Message_CalculateChecksum(payload) != strtol(checksum_string, 0,16)){
        message_event->type = BB_EVENT_ERROR;
        message_event->param0 = 0;
        message_event->param1 = 0;
        message_event->param2 = 0;
        return STANDARD_ERROR;
    }
    char *token;
    char payload2[100];
    strncpy(payload2,payload,strlen(payload));
    token = strtok(payload2,",");
    if (strcmp(token,"CHA")==0){//CHA,
        message_event->type = BB_EVENT_CHA_RECEIVED;
        message_event->param1 = 0;
        message_event->param2 = 0;
        token = strtok(NULL,",");
        message_event->param0 = (uint8_t)(strtol(token,0,10));
    }else if (strcmp(token,"ACC")==0){//ACC,
        message_event->type = BB_EVENT_ACC_RECEIVED;
        message_event->param1 = 0;
        message_event->param2 = 0;
        token = strtok(NULL,",");
        message_event->param0 = (uint8_t)(strtol(token,0,10));
    }else if (strcmp(token,"REV")==0){//REV,
        message_event->type = BB_EVENT_REV_RECEIVED;
        message_event->param1 = 0;
        message_event->param2 = 0;
        token = strtok(NULL,",");
        message_event->param0 = (uint8_t)(strtol(token,0,10));
    }else if (strcmp(token,"SHO")==0){//SHO,
        message_event->type = BB_EVENT_SHO_RECEIVED;
        message_event->param2 = 0;
        token = strtok(NULL,",");
        message_event->param0 = (uint8_t)(strtol(token,0,10));
        token = strtok(NULL,",");
        message_event->param1 = (uint8_t)(strtol(token,0,10));
        //printf("%d,%d,%d,%d",message_event->type,message_event->param0,message_event->param1,message_event->param0);
    }else if (strcmp(token,"RES")==0){//RES,
        message_event->type = BB_EVENT_RES_RECEIVED;
        token = strtok(NULL,",");
        message_event->param0 = (uint8_t)(strtol(token,0,10));
        token = strtok(NULL,",");
        message_event->param1 = (uint8_t)(strtol(token,0,10));
        token = strtok(NULL,",");
        message_event->param2 = (uint8_t)(strtol(token,0,10));
    }else{
        message_event->type = BB_EVENT_NO_EVENT;
        message_event->param0 = 0;
        message_event->param1 = 0;
        message_event->param2 = 0;
        //printf("no msg type");
        return STANDARD_ERROR;
    }
    return SUCCESS;
}

int Message_Encode(char *message_string, Message message_to_encode){
    char temppayload[MESSAGE_MAX_PAYLOAD_LEN];
    if (message_to_encode.type == MESSAGE_NONE){
        return STANDARD_ERROR;
    }else if (message_to_encode.type == MESSAGE_CHA){
        sprintf(temppayload,PAYLOAD_TEMPLATE_CHA,message_to_encode.param0);
        sprintf(message_string,"$" PAYLOAD_TEMPLATE_CHA "*%X\n",message_to_encode.param0,Message_CalculateChecksum(temppayload));
    }else if (message_to_encode.type == MESSAGE_ACC){
        sprintf(temppayload,PAYLOAD_TEMPLATE_ACC,message_to_encode.param0);
        sprintf(message_string,"$" PAYLOAD_TEMPLATE_ACC "*%X\n",message_to_encode.param0,Message_CalculateChecksum(temppayload));
    }else if (message_to_encode.type == MESSAGE_REV){
        sprintf(temppayload,PAYLOAD_TEMPLATE_REV,message_to_encode.param0);
        sprintf(message_string,"$" PAYLOAD_TEMPLATE_REV "*%X\n",message_to_encode.param0,Message_CalculateChecksum(temppayload));
    }else if (message_to_encode.type == MESSAGE_SHO){
        sprintf(temppayload,PAYLOAD_TEMPLATE_SHO,message_to_encode.param0,message_to_encode.param1);
        sprintf(message_string,"$" PAYLOAD_TEMPLATE_SHO "*%X\n",message_to_encode.param0,message_to_encode.param1,Message_CalculateChecksum(temppayload));
    }else if (message_to_encode.type == MESSAGE_RES){
        sprintf(temppayload,PAYLOAD_TEMPLATE_RES,message_to_encode.param0,message_to_encode.param1,message_to_encode.param2);
        sprintf(message_string,"$" PAYLOAD_TEMPLATE_RES "*%X\n",message_to_encode.param0,message_to_encode.param1,message_to_encode.param2,Message_CalculateChecksum(temppayload));
    }else if (message_to_encode.type == MESSAGE_ERROR){
        return STANDARD_ERROR;
    }else{
        return STANDARD_ERROR;
    }
    return strlen(message_string);
}

int Message_Decode(unsigned char char_in, BB_Event * decoded_message_event){
    if (char_in=='$'){
        decoded_message_event->type=0;
        decoded_message_event->param0=0;
        decoded_message_event->param1=0;
        decoded_message_event->param2=0;
        ongoingdecodeoffset = 0;
        memset(ongoingdecode,0,MESSAGE_MAX_LEN);
    }else{
        if (char_in=='\n'){
            char payloadcur[MESSAGE_MAX_PAYLOAD_LEN];
            char checksumcur[MESSAGE_CHECKSUM_LEN+1];
            char *token;
            token = strtok(ongoingdecode, "*");
            strcpy(payloadcur,token);
            token = strtok(NULL, "\0");
            strcpy(checksumcur,token);
            if (Message_ParseMessage(payloadcur,checksumcur,decoded_message_event)==STANDARD_ERROR){
                return STANDARD_ERROR;
            }
        }
        ongoingdecode[ongoingdecodeoffset] = char_in;
        ongoingdecodeoffset++;
    }
    return SUCCESS;
}