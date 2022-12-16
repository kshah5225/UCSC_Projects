/* 
 * File:   MessageTest.c
 * Author: kshah
 *
 * Created on March 8, 2022, 5:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Message.h"
#include "string.h"
#include "BattleBoats.h"
#include "BOARD.h"

/*
 * 
 */
int main(int argc, char** argv) {
    printf("-----This is the Message Tester-----\n");
    if (Message_CalculateChecksum("SHO,2,9") == 95){
        printf("CORRECT:Message_CalculateChecksum(SHO,2,9) == 95\n");
    }else{
        printf("INCORRECT:Message_CalculateChecksum(SHO,2,9) == 95\n");
    }
    if (Message_CalculateChecksum("REV,6") == 91){
        printf("CORRECT:Message_CalculateChecksum(REV,6) == 91\n");
    }else{
        printf("INCORRECT:Message_CalculateChecksum(REV,6) == 91\n");
    }
    
    BB_Event the_BB_Event;
    if (Message_ParseMessage("SHO,2,9","5F\0",&the_BB_Event)){
        if ((the_BB_Event.type == 6)&&(the_BB_Event.param0 == 2)&&(the_BB_Event.param1==9)&&(the_BB_Event.param2==0)){
            printf("CORRECT:ParseMessage(''SHO,2,9'',''5F\\0'')==6,2,9,0\n");
        }else{
            printf("INCORRECT:ParseMessage(''SHO,2,9'',''5F\\0'')==6,2,9,0\n");

        }
    }else{
        printf("INCORRECT:ParseMessage(''SHO,2,9'',''5F\\0'')==6,2,9,0\n");

    }
    BB_Event the_BB_Event3;
    if (Message_ParseMessage("REV,6","5B\0",&the_BB_Event3)){
        if ((the_BB_Event3.type == 5)&&(the_BB_Event3.param0 == 6)&&(the_BB_Event3.param1==0)&&(the_BB_Event3.param2==0)){
            printf("CORRECT:ParseMessage(''SHO,6'',''5B\\0'')==5,6,0,0\n");
        }else{
            printf("INCORRECT:ParseMessage(''SHO,6'',''5B\\0'')==5,6,0,0\n");

        }
    }else{
        printf("INCORRECT:ParseMessage(''SHO,6'',''5B\\0'')==5,6,0,0\n");

    }
    
    char Mes_Enc_str[MESSAGE_MAX_LEN];
    Message message_to_encode = {MESSAGE_SHO,2,9};
    int templen = Message_Encode(Mes_Enc_str, message_to_encode);
    if (((strcmp(Mes_Enc_str,"$SHO,2,9*5F\n"))==0)&&templen==12){
        printf("CORRECT:Message_Encode({MESSAGE_SHO,2,9})==$SHO,2,9*5F\n");
    }else{
        printf("INCORRECT:Message_Encode({MESSAGE_SHO,2,9})==$SHO,2,9*5F\n");
    }
    Message message_to_encode2 = {MESSAGE_RES,2,9,1};
    templen = Message_Encode(Mes_Enc_str, message_to_encode2);
    if (((strcmp(Mes_Enc_str,"$RES,2,9,1*52\n"))==0)&&templen==14){
        printf("CORRECT:Message_Encode({MESSAGE_RES,2,9,1})==$RES,2,9,1*52\n");
    }else{
        printf("INCORRECT:Message_Encode({MESSAGE_RES,2,9,1})==$RES,2,9,1*52\n");
    }
    
    int successFlag = SUCCESS;
    BB_Event the_BB_Event2;
    if (Message_Decode('$', &the_BB_Event2) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('S', &the_BB_Event2) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('H', &the_BB_Event2) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('O', &the_BB_Event2) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode(',', &the_BB_Event2) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('2', &the_BB_Event2) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode(',', &the_BB_Event2) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('9', &the_BB_Event2) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('*', &the_BB_Event2) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('5', &the_BB_Event2) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('F', &the_BB_Event2) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('\n', &the_BB_Event2) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if ((successFlag == SUCCESS)&&(the_BB_Event2.type==6)&&(the_BB_Event2.param0==2)&&(the_BB_Event2.param1==9)&&(the_BB_Event2.param2==0)){
        printf("CORRECT:Message_Decode(''$SHO,2,9*5F\\n'')==6,2,9,0\n");
    }else{
        printf("INCORRECT:Message_Decode(''$SHO,2,9*5F\\n'')==6,2,9,0\n");
    }
    successFlag = SUCCESS;
    BB_Event the_BB_Event4;
    if (Message_Decode('$', &the_BB_Event4) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('R', &the_BB_Event4) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('E', &the_BB_Event4) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('S', &the_BB_Event4) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode(',', &the_BB_Event4) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('2', &the_BB_Event4) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode(',', &the_BB_Event4) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('9', &the_BB_Event4) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode(',', &the_BB_Event4) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('1', &the_BB_Event4) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('*', &the_BB_Event4) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('5', &the_BB_Event4) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('2', &the_BB_Event4) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if (Message_Decode('\n', &the_BB_Event4) != SUCCESS){
        successFlag = STANDARD_ERROR;
    }
    if ((successFlag == SUCCESS)&&(the_BB_Event4.type==7)&&(the_BB_Event4.param0==2)&&(the_BB_Event4.param1==9)&&(the_BB_Event4.param2==1)){
        printf("CORRECT:Message_Decode(''$RES,2,9,1*52\\n'')==5,2,9,1\n");
    }else{
        printf("INCORRECT:Message_Decode(''$RES,2,9,1*52\\n'')==5,2,9,1\n");
    }
    
    return (EXIT_SUCCESS);
}