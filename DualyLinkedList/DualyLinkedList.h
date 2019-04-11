#ifndef DualyLinkedList_h
#define DualyLinkedList_h

#include <stdbool.h>

//////////////////////////////////////////////////
typedef enum DLLOption {
    DLL_OPTION_NONE,
    DLL_OPTION_WITH_ELEMENT
} DLL_OPTION_e;

typedef struct DublyLinkedList_Cell {
    void *element;
    struct DublyLinkedList_Cell *prev;
    struct DublyLinkedList_Cell *next;
} DLLC_t;

typedef struct DublyLinkedList {
    DLLC_t *head;
    DLLC_t *tail;
} DLL_t;

//////////////////////////////////////////////////
DLL_t *createDLList(void);
bool destroyDLList(DLL_t *list, DLL_OPTION_e option);
bool clearDLList(DLL_t *list, DLL_OPTION_e option);
bool insertDLList(DLL_t *list, void *element);
bool insertAtHeadOnDLList(DLL_t *list, void *element);
bool insertAtTailOnDLList(DLL_t *list, void *element);
void *pullDLList(DLL_t *list);
void *pullHeadOnDLList(DLL_t *list);
void *pullTailOnDLList(DLL_t *list);
void *peekElementHeadOnList(DLL_t *list);
void *peekElementTailOnList(DLL_t *list);
DLLC_t *findHeadOnDLList(DLL_t *list);
DLLC_t *findTailOnDLList(DLL_t *list);
DLLC_t *findPrevOnDLList(DLLC_t *cell);
DLLC_t *findNextOnDLList(DLLC_t *cell);
void *findElementOnDLList(DLL_t *list, int (*comp)(void*, void*), void *element);
void *findMinOnDLList(DLL_t *list, int (*comp)(void*, void*));
void *findMaxOnDLList(DLL_t *list, int (*comp)(void*, void*));
DLL_t *margeDLList(DLL_t *left, DLL_t *right);
bool isEmptyDLList(DLL_t *list);
DLLC_t *createCellOnDLList(void *element);
void *getElementOnDLList(DLLC_t *cell);

#endif
