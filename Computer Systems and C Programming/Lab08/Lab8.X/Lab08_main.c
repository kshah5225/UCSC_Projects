// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

//CSE013E Support Library
#include "UNIXBOARD.h"

// User libraries
#include "Game.h"
#include "Player.h"
// **** Set any macros or preprocessor directives here ****
#define string_offset 1
#define NONE 0

// **** Declare any data types here ****

// **** Define any global or external variables here ****

// **** Declare any function prototypes here ****

int main()
{

    /******************************** Your custom code goes below here ********************************/
    //initilization of vars
    int errorchck = FALSE;
    int qcheck = FALSE;
    char dir;
    char dirs;
    char ret;
    char desc[GAME_MAX_ROOM_DESC_LENGTH+string_offset];
    char title[GAME_MAX_ROOM_TITLE_LENGTH+string_offset];
    GameInit();
    
    while(1){
        // retreiveing current room info
        GameGetCurrentRoomTitle(title);
        GameGetCurrentRoomDescription(desc);
        
        //displaying current room info
        printf("\n\n%s\n%s\n",title,desc);
        
        //while loop to re-querry for user's input until acceptable
        while(1){
            //if no exits game over pt.1
            if (GameGetCurrentRoomExits() == NONE){
                break;
            }
            
            //printing what directions you can go
            printf("You can go in the following directions:\n");
            if ((GameGetCurrentRoomExits()&GAME_ROOM_EXIT_NORTH_EXISTS) == GAME_ROOM_EXIT_NORTH_EXISTS){
                printf("    >North(n)\n");
            }
            if ((GameGetCurrentRoomExits()&GAME_ROOM_EXIT_EAST_EXISTS) == GAME_ROOM_EXIT_EAST_EXISTS){
                printf("    >East(e)\n");
            }
            if ((GameGetCurrentRoomExits()&GAME_ROOM_EXIT_SOUTH_EXISTS) == GAME_ROOM_EXIT_SOUTH_EXISTS){
                printf("    >South(s)\n");
            }
            if ((GameGetCurrentRoomExits()&GAME_ROOM_EXIT_WEST_EXISTS) == GAME_ROOM_EXIT_WEST_EXISTS){
                printf("    >West(w)\n");
            }
            
            //ask user for input
            printf("Pick A Direction to go by using n,e,s,w and pressing enter:");
            
            //waiting for user input?
            dir = getchar();
            if (dir!='\n'){
                dirs = getchar();
                if(dirs != '\n'){
                    while(dirs != '\n'){
                        dirs = getchar();
                    }
                    dir = 'g';
                    printf("PLEASE INPUT ONLY ONE CHAR AT A TIME\n");
                }
            }
            /*dir = getchar();
            ret = getchar();
            if (ret!='\n'){
                printf("PLEASE INPUT ONLY ONE CHAR AT A TIME\n");
                dir = 'g';
            }*/
            //dir = getchar();
            /*do{
                dir = getchar();
            } while (isspace(dir));
            printf("\n---%c---\n", dir);*/
            
            //interpreting user input and go in that direction then breaking loop
            //or if input is invalid then re-querry for valid input
            if (dir == 'n'|dir == 'e'|dir == 's'|dir == 'w'|dir == 'q'){//do these count as magic numbers?
                if ((dir == 'n')&&((GameGetCurrentRoomExits()&GAME_ROOM_EXIT_NORTH_EXISTS)==GAME_ROOM_EXIT_NORTH_EXISTS)){
                    if (GameGoNorth()==STANDARD_ERROR){
                        errorchck = TRUE;
                    }
                    break;
                }else if((dir == 'e')&&((GameGetCurrentRoomExits()&GAME_ROOM_EXIT_EAST_EXISTS)==GAME_ROOM_EXIT_EAST_EXISTS)){
                    if (GameGoEast()==STANDARD_ERROR){
                        errorchck = TRUE;
                    }
                    break;
                }else if((dir == 's')&&((GameGetCurrentRoomExits()&GAME_ROOM_EXIT_SOUTH_EXISTS)==GAME_ROOM_EXIT_SOUTH_EXISTS)){
                    if (GameGoSouth()==STANDARD_ERROR){
                        errorchck = TRUE;
                    }
                    break;
                }else if((dir == 'w')&&((GameGetCurrentRoomExits()&GAME_ROOM_EXIT_WEST_EXISTS)==GAME_ROOM_EXIT_WEST_EXISTS)){
                    if (GameGoWest()==STANDARD_ERROR){
                        errorchck = TRUE;
                    }
                    break;
                }else if(dir == 'q'){
                    qcheck = TRUE;
                    break;
                }else{
                    //if a blocked off direction is picked
                    printf("You Cannot Go in That Direction please pick an avaliable Direction\n");
                }
            }else{
                //if the input is an invalid character
                printf("Please input one of the valid characters:n,e,s,w\n");
            }
        }
        //if no exits game over pt.2
        if (qcheck == TRUE){
            printf("---user input of q has force quit the game---\n");
            break;
        }
        if (errorchck == TRUE){
            printf("ERROR:Likely from reading \nPROGRAM WILL NOW EXIT");
            break;
        }
        if (GameGetCurrentRoomExits() == NONE){
            GameGetCurrentRoomTitle(title);
            GameGetCurrentRoomDescription(desc);
            printf("\n\n%s\n%s\n",title,desc);
            break;
        }
    }
    /**************************************************************************************************/
}

