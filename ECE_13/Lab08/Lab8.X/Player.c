#include "stdio.h"
#include "Player.h"

#define ItemReqmaxuniqueitems 256
#define ZERO 0
#define offset 1

typedef struct {
    int ItemReq[ItemReqmaxuniqueitems+offset];
} PlayerData;

static PlayerData playerData = {STANDARD_ERROR};

int AddToInventory(uint8_t item){
    uint16_t sumofitems = ZERO;//finding number of items currently possessed
    for(uint16_t i = ZERO; i < ItemReqmaxuniqueitems; i++){
          sumofitems = sumofitems + playerData.ItemReq[i];
    }
    
    //ensureing you have the ability to pickup that item
    if ((item>ItemReqmaxuniqueitems-offset)|(item<ZERO)|(sumofitems>=INVENTORY_SIZE)){
        return STANDARD_ERROR;
    }
    
    playerData.ItemReq[item] = TRUE;//stores item to invintory spot
    return SUCCESS;
}

int FindInInventory(uint8_t item){
    if (playerData.ItemReq[item] == 1){
        return SUCCESS;
    }else{
        return STANDARD_ERROR;
    }//checks spot for that particular invintory item
}