#include "Linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LinkedList_Init(struct LinkedList* list) {
    list->head = NULL;
    list->counter = 0;
}

void LinkedList_addBegin(struct LinkedList* list, Type newType, char* newMessage) {
    struct ListNode* newNode;
    newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->type = newType;
    strcpy(newNode->message,newMessage);
    newNode->next = list->head;
    list->head = newNode;
    list->counter++;
}


int LinkedList_count(struct LinkedList* list) {
    return list->counter;
}

void LinkedList_print(struct LinkedList* list) {
    struct ListNode* node; // (struct ListNode*)malloc(sizeof(struct ListNode));
    node = list->head;
    while (node != NULL) {
        printf(" %s\r\n ", node->message);
        node = node->next;
    }
    printf("\r\n");
    int counter = LinkedList_count(list);
    printf("counter=%d \n", counter);

}

void LinkedList_printAndDelete(struct LinkedList* list) {
    struct ListNode* node; // (struct ListNode*)malloc(sizeof(struct ListNode));
    char str[80];
    node = list->head;


    while (node != NULL) {
        printf("%d-  %s\r\n ",node->type, node->message);
        strcpy(str,node->message);
        node = node->next;
        LinkedList_delete(list, str);
    }
    printf("\n");
    //int counter = LinkedList_count(list);
    //printf("counter=%d \r\n", counter);

}

int LinkedList_delete(struct LinkedList* list, char* newMessage) {
    struct ListNode* node;
    struct ListNode* prevNode;
    prevNode = list->head;
    node = prevNode->next;
    if (strcmp(prevNode->message,newMessage) == 0) {
        list->head = node;
        list->counter--;
        return 1;
    }
    while (node != NULL) {
        if (node->message == newMessage) {
            prevNode->next = node->next;
            list->counter--;
            return 1;
        }
        prevNode = node;
        node = node->next;
    }
}


