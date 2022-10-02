/*
 * Linkedlist.h
 *
 *  Created on: Sep 22, 2022
 *      Author: student
 */

#ifndef INC_LINKEDLIST_H_
#define INC_LINKEDLIST_H_
#include "main.h"

typedef enum Type_{
    LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_EROR,
}Type;


struct ListNode {
    Type type;
    char message[80];
    struct ListNode* next;
};

typedef struct LinkedList {
    struct ListNode* head;
    int counter;
}LinkedList;

void LinkedList_Init(struct LinkedList* list);
void LinkedList_addBegin(struct LinkedList* list, Type newType, char* newMessage);
int LinkedList_count(struct LinkedList* list);
void LinkedList_print(struct LinkedList* list);
int LinkedList_delete(struct LinkedList* list, char* newMessage);
void LinkedList_printAndDelete(struct LinkedList* list);

#endif /* INC_LINKEDLIST_H_ */
