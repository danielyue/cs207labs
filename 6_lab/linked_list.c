
#include <stdlib.h>
#include <stdio.h>

typedef struct item {
    int value;
    struct item* rest;
} Item;

Item* new_item(int value){
    Item* newitem = (Item *) malloc(sizeof(Item));
    newitem->value = value;
    newitem->rest = NULL;
    return newitem;
}

Item* insert_front(Item* listptr, int value){
    Item* newitem = new_item(value);
    newitem->rest = listptr;
    return newitem;
}


int get(Item* listptr, int index){
    int ctr = 0;
    Item* p;
    for(p = listptr; p!= NULL; p = p->rest){
        if (ctr==index){
            return p->value;
        }
        ctr++;
    }
    return -1;
}


void free_all(Item* listptr) {
    Item *p;
    Item *next;
    for(p = listptr; p!= NULL; p = next){
        next = p->rest;
        free(p);
    }
}

// # which returns the index at which the value is found, and otherwise -1.
int get_index(Item* listptr, int value){
    int ctr = 0;
    Item* p;
    for(p = listptr; p!= NULL; p = p->rest){
        if (p->value == value){
            return ctr;
        }
        ctr++;
    }
    return -1;
}

// # Be careful to return NULL if the item with value was not in the list, and 
// # make sure that deletion repoints the pointer of the previous item to the next item.
Item* remove_item(Item* listptr, int value){
    Item* orig = listptr;
    Item* prev = listptr;
    Item* curr;
    for(curr = listptr; curr!= NULL; curr=curr->rest){
        if (curr->value == value){
            prev->rest = curr->rest;
            free(curr);
            return orig;
        }
        prev = curr;
    }
    return NULL; 
}


int main(){
    Item* listptr;
    int i;
    listptr = new_item(0);
    for (i=1; i < 6; i++){
        listptr=insert_front(listptr, i);
    }
    for (i=0; i < 6; i++){
        printf("i %d Item %d\n", i, get(listptr, i));
    }
    listptr = remove_item(listptr, 3);
    for (i=0; i <= 5; i++){
        printf("i %d Item %d\n", i, get(listptr, i));
    }
//    printf("Index for 0 %d\n", get_index(listptr, 0));
    printf("Index for 3 %d\n", get_index(listptr, 3));
    free_all(listptr);
}