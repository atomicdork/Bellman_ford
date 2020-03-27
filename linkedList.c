#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

struct ListNode
{
    // The value to store in this node
    int data;

    // And the nodes along side this one
    struct ListNode* next;
    struct ListNode* prev;
};
typedef struct ListNode ListNode;


struct List
{
    // Number of elements in the list
    int size;

    // Start and end of our list
    struct ListNode* head;
    struct ListNode* tail;
};
typedef struct List List;

// Allocate a new listNode with the provided value
struct ListNode* listNodeConstructor(int value)
{
    struct ListNode* newNode;

    // Reserve memory for a node
    newNode = malloc(sizeof(struct ListNode));

    // Set its values
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;

    // And return it
    return newNode;
}

// Release the memory of the provided node
void listNodeDestructor(struct ListNode* node)
{
    // We have no extra memory other than this node so simply free it
    free(node);
}

// Create a new linked list
struct List* listConstructor()
{
    // Check we are using the right list implementation
    printf("Linked list constructor\n");

    // Reserve memory for the list
    struct List* newLinkedList;
    newLinkedList = malloc(sizeof(struct List));

    // Initialise it appropriately
    newLinkedList->size = 0;
    newLinkedList->head = NULL;
    newLinkedList->tail = NULL;

    // And return it
    return newLinkedList;
}

void listDestructor(struct List* linkedList)
{
    printf("Linked list destructor\n");

    // We need these to traverse the list
    struct ListNode* currentRecord;
    struct ListNode* nextRecord = linkedList->head;

    // As long as the record to process exists
    while(nextRecord != NULL)
    {
        // Move to it
        currentRecord = nextRecord;

        // And update where to go next
        nextRecord = currentRecord->next;

        // And release the memory associated with this node
        listNodeDestructor(currentRecord);
    }

    // Now all of the nodes have been release so we can release the list too
    free(linkedList);
}

int listSize(struct List* list)
{
    return list->size;
}

int listIsEmpty(struct List* list)
{
    if(listSize(list) == 0)
        return 1;

    return 0;
}

// Add a new item to the end of the list
int listAdd(struct List* list, int entity)
{
    // Build our new node
    struct ListNode* newNode = listNodeConstructor(entity);

    // The node that will come before this node is currently the list tail
    // Note that this also works if the list is empty
    newNode->prev = list->tail;

    // And we will not have a next element
    newNode->next = NULL;

    // If the list is not empty
    if(list->tail != NULL)
    {
        // Tell the current tail that it now has a next element
        list->tail->next = newNode;
    }

    // And update the list to make the new node the tail
    list->tail = newNode;

    // List is empty
    if(list->head == NULL)
    {
        // So we are also the head
        list->head = newNode;
    }

    // Update the element count
    list->size++;

    // And indicate success
    return 1;
}

void listDisplay(struct List* list)
{
    // Start by printing an opening square bracket to denote the start of our list
    printf("[");

    // We start with the head of the list
    struct ListNode* currentNode = list->head;

    // And print each element in turn until we are looking at NULL
    while(currentNode != NULL)
    {
        // Print a comma before the values after the first
        if(currentNode != list->head)
        {
            printf(",");
        }

        // Print the current value
        printf(" %d", currentNode->data);

        // Move to the next node
        currentNode = currentNode->next;
    }

    // Finally print a closing square bracket
    printf(" ]");
}

struct ListNode* listGetNode(struct List* list, int index)
{
    // Sanity check the index
    if(index < 0 || index >= list->size)
    {
        // And indicate failure if it is invalid
        return NULL;
    }

    // Check if we should start from the head or tail
    if(index < (list->size / 2))
    {
        // We are closer to the start of the list so start at the head and move forwards
        struct ListNode* currentItem = list->head;

        // Move through index items
        for(int i = 0; i < index; i++)
        {
            // Make sure our links are not corrupt
            if(currentItem->next == NULL)
            {
                // And indicate failure if they are
                return NULL;
            }

            // Otherwise move on
            currentItem = currentItem->next;
        }

        // We have now moved to the requested item so return it
        return currentItem;
    }
    else
    {
        // We are closer to the end of the list so start at the tail and move backwards
        struct ListNode* currentItem = list->tail;

        // How many items should we move through?
        // If the index is size-1 then we move through 0 items
        // so we should move through (size-1) - index items
        int elementsToMoveThrough = (list->size - 1) - index;

        // Move through the elements in reverse
        for(int i = 0; i < elementsToMoveThrough; i++)
        {
            // Make sure our links are not corrupt
            if(currentItem->prev == NULL)
            {
                // And indicate failure if they are
                return NULL;
            }

            // Otherwise move back through the list
            currentItem = currentItem->prev;
        }

        // We have moved to the required element so can return it
        return currentItem;
    }
}

int listRead(struct List* list, int index, int* entity)
{
    // Get the requested node
    struct ListNode* node = listGetNode(list, index);

    // If it does not exist then indicate failure
    if(node == NULL)
        return 0;

    // Otherwise set the output value
    *entity = node->data;

    // And indicate success
    return 1;
}

int listRemove(struct List* list, int index)
{
    // Get the requested node
    struct ListNode* node = listGetNode(list, index);

    // If the requested node is invalid then return failure now and do nothing else
    if(node == NULL)
        return 0;

    // We now know that the node exists and can start to remove it

    // If we have a previous item make it point to this node's next item
    if(node->prev != NULL)
        node->prev->next = node->next;

    // And similarly for the next node's previous item
    if(node->next != NULL)
        node->next->prev = node->prev;

    // We now need to check if our node was the first item
    // and if so make the head of the list the current node's next item
    if(node == list->head)
        list->head = node->next;

    // And similar for the last item
    if(node == list->tail)
        list->tail = node->prev;

    // There should now be no pointers to our list anywhere in our list structure
    // so we are free to release the memory associated with this node
    listNodeDestructor(node);

    // And update the element count
    list->size--;

    // Indicate success
    return 1;
}

int listSearch(struct List* list, int value)
{
    // Start at the first node
    struct ListNode* node = list->head;
    int index = 0;

    // As long as we have an element to test
    while(node != NULL)
    {
        // Check its value and return its index if we have a match
        if(node->data == value)
            return index;

        // If this node is not the one we are looking for then move on
        node = node->next;
        index++;
    }

    // If we reach here this point then we have not found the item in our list and should return our failure value
    return -1;
}
/*From here bellow is a linked list solution for strings*/
struct strListNode
{
    // The value to store in this node
    void *data;

    // And the nodes along side this one
    struct strListNode* next;
    struct strListNode* prev;
};
typedef struct strListNode strListNode;

//works
struct strList
{
    // Number of elements in the list
    int size;

    // Start and end of our list
    struct strListNode* head;
    struct strListNode* tail;
};
typedef struct strList strList;

// Allocate a new listNode with the provided value
//works
struct strListNode* strlistNodeConstructor(void *element)
{
    struct strListNode* newNode;

    // Reserve memory for a node
    newNode = malloc(sizeof(struct strListNode));

    //sets memory size of data
    //
    newNode->data = malloc(100);

    // Set its values
    memcpy(newNode->data, element, 100);
    newNode->next = NULL;
    newNode->prev = NULL;

    // And return it
    return newNode;
}

// Release the memory of the provided node
void strlistNodeDestructor(struct strListNode* node)
{
    // We have no extra memory other than this node so simply free it
    free(node);
}
//works
// Create a new linked list
struct strList* strlistConstructor()
{
    // Check we are using the right list implementation
    printf("Linked strlist constructor\n");

    // Reserve memory for the list
    struct strList* newstrLinkedList;
    newstrLinkedList = malloc(sizeof(struct strList));

    // Initialise it appropriately
    newstrLinkedList->size = 0;
    newstrLinkedList->head = NULL;
    newstrLinkedList->tail = NULL;

    // And return it
    return newstrLinkedList;
}
// does not delete the list fully notworking
void strlistDestructor(struct strList* strlinkedList){
    printf("Linked list destructor\n");

    // We need these to traverse the list
    struct strListNode* currentRecord;
    struct strListNode* nextRecord = strlinkedList->head;

    // As long as the record to process exists
    while(nextRecord != NULL)
    {
        // Move to it
        currentRecord = nextRecord;

        // And update where to go next
        nextRecord = currentRecord->next;

        // And release the memory associated with this node
        strlistNodeDestructor(currentRecord);
    }

    // Now all of the nodes have been release so we can release the list too
    free(strlinkedList);
}
//works
int strlistSize(struct strList* list)
{
    return list->size;
}

//works
int strlistIsEmpty(struct strList* list)
{
    if(strlistSize(list) == 0)
        return 1;

    return 0;
}

//works
//  a new item to the end of the list
int strlistAdd(struct strList* list, void *element)
{
    // Build our new node
    struct strListNode* newNode = strlistNodeConstructor(element);

    // The node that will come before this node is currently the list tail
    // Note that this also works if the list is empty
    newNode->prev = list->tail;

    // And we will not have a next element
    newNode->next = NULL;

    // If the list is not empty
    if(list->tail != NULL)
    {
        // Tell the current tail that it now has a next element
        list->tail->next = newNode;
    }

    // And update the list to make the new node the tail
    list->tail = newNode;

    // List is empty
    if(list->head == NULL)
    {
        // So we are also the head
        list->head = newNode;
    }

    // Update the element count
    list->size++;

    // And indicate success
    return 1;
}

//working
void strlistDisplay(struct strList* list)
{
    // Start by printing an opening square bracket to denote the start of our list
    printf("[");

    // We start with the head of the list
    struct strListNode* currentNode = list->head;

    // And print each element in turn until we are looking at NULL
    while(currentNode != NULL)
    {
        // Print a comma before the values after the first
        if(currentNode != list->head)
        {
            printf(",");
        }

        // Print the current value
        printf("%s", currentNode->data);

        // Move to the next node
        currentNode = currentNode->next;
    }

    // Finally print a closing square bracket
    printf(" ]\n");
}
//works
struct strListNode* strlistGetNode(struct strList* list, int index)
{
    // Sanity check the index
    if(index < 0 || index >= list->size)
    {
        // And indicate failure if it is invalid
        return NULL;
    }

    // Check if we should start from the head or tail
    if(index < (list->size / 2))
    {
        // We are closer to the start of the list so start at the head and move forwards
        struct strListNode* currentItem = list->head;

        // Move through index items
        for(int i = 0; i < index; i++)
        {
            // Make sure our links are not corrupt
            if(currentItem->next == NULL)
            {
                // And indicate failure if they are
                return NULL;
            }

            // Otherwise move on
            currentItem = currentItem->next;
        }

        // We have now moved to the requested item so return it
        return currentItem;
    }
    else
    {
        // We are closer to the end of the list so start at the tail and move backwards
        struct strListNode* currentItem = list->tail;

        // How many items should we move through?
        // If the index is size-1 then we move through 0 items
        // so we should move through (size-1) - index items
        int elementsToMoveThrough = (list->size - 1) - index;

        // Move through the elements in reverse
        for(int i = 0; i < elementsToMoveThrough; i++)
        {
            // Make sure our links are not corrupt
            if(currentItem->prev == NULL)
            {
                // And indicate failure if they are
                return NULL;
            }

            // Otherwise move back through the list
            currentItem = currentItem->prev;
        }

        // We have moved to the required element so can return it
        return currentItem;
    }
}
//notworking this return is returning address need to get it to pass to element
int strlistRead(struct strList* list, int index, void *element)
{
    // Get the requested node
    struct strListNode* node = strlistGetNode(list, index);

    // If it does not exist then indicate failure
    if(node == NULL)
        return 0;

    // Otherwise set the output value
    //*entity = node->data;
//    *element = node->data;
    memcpy(&element, node->data, 100);

    // And indicate success
    return 1;
}
//works
int strlistRemove(struct strList* list, int index)
{
    // Get the requested node
    struct strListNode* node = strlistGetNode(list, index);

    // If the requested node is invalid then return failure now and do nothing else
    if(node == NULL)
        return 0;

    // We now know that the node exists and can start to remove it

    // If we have a previous item make it point to this node's next item
    if(node->prev != NULL)
        node->prev->next = node->next;

    // And similarly for the next node's previous item
    if(node->next != NULL)
        node->next->prev = node->prev;

    // We now need to check if our node was the first item
    // and if so make the head of the list the current node's next item
    if(node == list->head)
        list->head = node->next;

    // And similar for the last item
    if(node == list->tail)
        list->tail = node->prev;

    // There should now be no pointers to our list anywhere in our list structure
    // so we are free to release the memory associated with this node
    strlistNodeDestructor(node);

    // And update the element count
    list->size--;

    // Indicate success
    return 1;
}

//works although the capitalisation needs to be an exact match which is ok for our uses
int strlistSearch(struct strList* list, char *str)
{
    // Start at the first node
    struct strListNode* node = list->head;
    int index = 0;

    // As long as we have an element to test
    while(node != NULL)
    {

        // Check its value and return its index if we have a match
        if(strcmp((node->data), str) == 0) {
            return index;
        }
        // If this node is not the one we are looking for then move on
        node = node->next;
        index++;
    }

    // If we reach here this point then we have not found the item in our list and should return our failure value
    return -1;
}
