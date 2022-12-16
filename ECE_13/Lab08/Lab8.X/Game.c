#include "Game.h"
#include "stdio.h"
#include "Player.h"

#define string_offset 1
#define rpg_str_len 4
#define ZERO 0
#define roomfilename_len 20
#define whileloopstnerr 1000

typedef struct {
    char RoomTitle[GAME_MAX_ROOM_TITLE_LENGTH+string_offset];
    char RoomDesc[GAME_MAX_ROOM_DESC_LENGTH+string_offset];
    char roomfilename[roomfilename_len];
    int8_t roomnumber;
    int TitleLength;
    int DescLength;
    int NoOfItemsRequired;
    int NoOfItemsContained;
    int ItemReqMeet;
    int16_t NExit;
    int16_t SExit;
    int16_t EExit;
    int16_t WExit;
} RoomData;

static RoomData roomData;

//helper function to load room files to struct RoomData
int LoadRoomtoStruct(uint16_t RoomNo);

int LoadRoomtoStruct(uint16_t RoomNo){
    roomData.roomnumber = RoomNo;//determining file and file directory
    FILE *fileptr;//file pointer
    sprintf(roomData.roomfilename, "RoomFiles/room%d.txt",roomData.roomnumber);
    
    //checking fopen() for failure
    fileptr = fopen(roomData.roomfilename,"rb");
    if (fileptr==NULL){
        FATAL_ERROR();
    }
    
    //checking first 3 chars are RPG
    char rpgcheck[rpg_str_len];//check the file starts with RPG
    fgets(rpgcheck, rpg_str_len, fileptr);
    if ((rpgcheck[0] != 'R')|(rpgcheck[1] != 'P')|(rpgcheck[2] != 'G')){
        return STANDARD_ERROR;
    }
    
    //making a char to remember moving data
    char tempchar;
    
    //reading and storing new room title
    tempchar = fgetc(fileptr);
    roomData.TitleLength = tempchar;
    fgets(roomData.RoomTitle, roomData.TitleLength+string_offset, fileptr);
    
    //start loop for repeated items of a file for item requirements
    int ItemReqMeet = FALSE;
    int whilebreak = ZERO;
    while (ItemReqMeet == FALSE){
        //reutrn standard error if loop gets stuck
        whilebreak++;
        if (whilebreak==whileloopstnerr){
            return STANDARD_ERROR;
        }
        
        //read number of items
        tempchar = fgetc(fileptr);
        roomData.NoOfItemsRequired = tempchar;
        
        //checking if required items are meet or to move on to next portion of txt
        int ItemReqMeet = TRUE;
        for ( int i = ZERO; i < roomData.NoOfItemsRequired; i++ ) {//iterate through items
            tempchar = fgetc(fileptr);
            if (FindInInventory(tempchar) != SUCCESS){
                ItemReqMeet = FALSE;
            }
        }

        //loading current description len that may be overwritten given item requirements are not meet
        tempchar = fgetc(fileptr);
        roomData.DescLength = (uint8_t)tempchar;
        
        //loading current description into struct which may be overwritten given item requirements are not meet
        fgets(roomData.RoomDesc, roomData.DescLength+string_offset, fileptr);
        
        if (ItemReqMeet == TRUE){
            //if item requirement is meet then continue to the next items to save
            tempchar = fgetc(fileptr);
            roomData.NoOfItemsContained = tempchar;
            for ( int i = ZERO; i < roomData.NoOfItemsContained; i++ ) {
            tempchar = fgetc(fileptr);
            AddToInventory(tempchar);
            }
        }else{
            //if requirements not meet recheck the next requirements
            tempchar = fgetc(fileptr);
            roomData.NoOfItemsContained = tempchar;
            for ( int i = ZERO; i < roomData.NoOfItemsContained; i++ ) {
            tempchar = fgetc(fileptr);
            //AddToInventory(tempchar);
            }
        }
        
        //store the exits
        tempchar = fgetc(fileptr);
        roomData.NExit = tempchar;
        tempchar = fgetc(fileptr);
        roomData.EExit = tempchar;
        tempchar = fgetc(fileptr);
        roomData.SExit = tempchar;
        tempchar = fgetc(fileptr);
        roomData.WExit = tempchar;
        
        //making sure the while loop exits when item requirement is meet
        //this line of code isn't necessary but a failsafe
        if (ItemReqMeet == TRUE){
            break;
        }
    }
    fclose(fileptr);
    return SUCCESS;
}

int GameGoNorth(void){
    if (LoadRoomtoStruct(roomData.NExit) == STANDARD_ERROR){
        return STANDARD_ERROR;
    }else{
        return SUCCESS;
    }//load struct to north of current room
}
int GameGoEast(void){
    if (LoadRoomtoStruct(roomData.EExit) == STANDARD_ERROR){
        return STANDARD_ERROR;
    }else{
        return SUCCESS;
    }//load struct to east of current room
}
int GameGoSouth(void){
    if (LoadRoomtoStruct(roomData.SExit) == STANDARD_ERROR){
        return STANDARD_ERROR;
    }else{
        return SUCCESS;
    }//load struct to south of current room
}
int GameGoWest(void){
    if (LoadRoomtoStruct(roomData.WExit) == STANDARD_ERROR){
        return STANDARD_ERROR;
    }else{
        return SUCCESS;
    }//load struct to west of current room
}

int GameInit(){
    if (LoadRoomtoStruct(STARTING_ROOM) == STANDARD_ERROR){
        FATAL_ERROR();
        return STANDARD_ERROR;
    }else{
        return SUCCESS;
    }//load struct to starting room macro
}

int GameGetCurrentRoomTitle(char *title){
    //asks struct for room title and writes it to title ptr
    sprintf(title,"%s",roomData.RoomTitle);
    return roomData.TitleLength;
}

int GameGetCurrentRoomDescription(char *desc){
    //asks struct for room description and writes it to desc ptr
    sprintf(desc,"%s",roomData.RoomDesc);
    return roomData.DescLength;
}

uint8_t GameGetCurrentRoomExits(void){
    //binary or operation preformed to all exits that are avaliable to follow game.h enums
    uint8_t exits = ZERO;
    if (roomData.NExit != FALSE){
        exits = exits | GAME_ROOM_EXIT_NORTH_EXISTS;
    }
    if (roomData.EExit != FALSE){
        exits = exits | GAME_ROOM_EXIT_EAST_EXISTS;
    }
    if (roomData.SExit != FALSE){
        exits = exits | GAME_ROOM_EXIT_SOUTH_EXISTS;
    }
    if (roomData.WExit != FALSE){
        exits = exits | GAME_ROOM_EXIT_WEST_EXISTS;
    }
    return exits;
}