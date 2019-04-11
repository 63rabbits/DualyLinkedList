#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "DualyLinkedList.h"

//////////////////////////////////////////////////
DLL_t *createDLList() {
    DLL_t *list = malloc(sizeof(DLL_t));
    if (list == NULL) return NULL;
    
    list->head = NULL;
    list->tail = NULL;
    return list;
}

bool destroyDLList(DLL_t *list, DLL_OPTION_e option) {
    // Block illegal parameters.
    if (list == NULL) return false;
    
    clearDLList(list, option);
    free(list);
    
    return true;
}

bool clearDLList(DLL_t *list, DLL_OPTION_e option) {
    // Block illegal parameters.
    if (list == NULL) return false;
    
    while (!isEmptyDLList(list)) {
        void *element = pullDLList(list);
        if ((option == DLL_OPTION_WITH_ELEMENT) &&
            (element != NULL)) {
            free(element);
        }
    }
    
    return true;
}

bool insertDLList(DLL_t *list, void *element) {
    return insertAtTailOnDLList(list, element);
}

bool insertAtHeadOnDLList(DLL_t *list, void *element) {
    // Block illegal parameters.
    if (list == NULL) return false;
    if (element == NULL) return false;
    
    DLLC_t *cell = createCellOnDLList(element);
    if (list->head == NULL) {
        cell->prev = NULL;
        cell->next = NULL;
        list->head = cell;
        list->tail = cell;
    }
    else {
        cell->prev = NULL;
        cell->next = list->head;
        list->head->prev = cell;
        list->head = cell;
    }
    
    return true;
}

bool insertAtTailOnDLList(DLL_t *list, void *element) {
    // Block illegal parameters.
    if (list == NULL) return false;
    if (element == NULL) return false;
    
    DLLC_t *cell = createCellOnDLList(element);
    if (list->tail == NULL) {
        cell->prev = NULL;
        cell->next = NULL;
        list->head = cell;
        list->tail = cell;
    }
    else {
        cell->prev = list->tail;
        cell->next = NULL;
        list->tail->next = cell;
        list->tail = cell;
    }
    
    return true;
}

void *pullDLList(DLL_t *list) {
    return pullHeadOnDLList(list);
}

void *pullHeadOnDLList(DLL_t *list) {
    if (list == NULL) return NULL;
    if (list->head == NULL) return NULL;
    
    DLLC_t *cell = list->head;
    list->head = cell->next;
    if (list->head == NULL) {
        list->tail = NULL;
    }
    else {
        list->head->prev = NULL;
    }
    
    void *element = getElementOnDLList(cell);
    free(cell);
    return element;
}

void *pullTailOnDLList(DLL_t *list) {
    if (list == NULL) return NULL;
    if (list->head == NULL) return NULL;
    
    DLLC_t *cell = list->tail;
    list->tail = cell->prev;
    if (list->tail == NULL) {
        list->head = NULL;
    }
    else {
        list->tail->next = NULL;
    }
    
    void *element = getElementOnDLList(cell);
    free(cell);
    return element;
}

void *peekElementHeadOnList(DLL_t *list) {
    if (list == NULL) return NULL;
    if (list->head == NULL) return NULL;
    
    return list->head->element;
}

void *peekElementTailOnList(DLL_t *list) {
    if (list == NULL) return NULL;
    if (list->tail == NULL) return NULL;
    
    return list->tail->element;
}

DLLC_t *findHeadOnDLList(DLL_t *list) {
    // Block illegal parameters.
    if (list == NULL) return NULL;
    
    return list->head;
}

DLLC_t *findTailOnDLList(DLL_t *list) {
    // Block illegal parameters.
    if (list == NULL) return NULL;
    
    return list->tail;
}

DLLC_t *findPrevOnDLList(DLLC_t *cell) {
    // Block illegal parameters.
    if (cell == NULL) return NULL;
    
    return cell->prev;
}

DLLC_t *findNextOnDLList(DLLC_t *cell) {
    // Block illegal parameters.
    if (cell == NULL) return NULL;
    
    return cell->next;
}

void *findElementOnDLList(DLL_t *list, int (*comp)(void*, void*), void *element) {
    // Block illegal parameters.
    if (isEmptyDLList(list)) return NULL;
    
    DLLC_t *cell = findHeadOnDLList(list);
    while (cell != NULL) {
        int check = comp(cell->element, element);
        if (check == 0) {
            return cell->element;
        }
        cell = findNextOnDLList(cell);
    }
    return NULL;
}

void *findMinOnDLList(DLL_t *list, int (*comp)(void*, void*)) {
    // Block illegal parameters.
    if (isEmptyDLList(list)) return NULL;
    
    DLLC_t *cell = findHeadOnDLList(list);
    DLLC_t *min = cell;
    while (cell != NULL) {
        int check = comp(min->element, cell->element);
        if (check > 0) {
            min = cell;
        }
        cell = findNextOnDLList(cell);
    }
    return min->element;
}

void *findMaxOnDLList(DLL_t *list, int (*comp)(void*, void*)) {
    // Block illegal parameters.
    if (isEmptyDLList(list)) return NULL;
    
    DLLC_t *cell = findHeadOnDLList(list);
    DLLC_t *max = cell;
    while (cell != NULL) {
        int check = comp(max->element, cell->element);
        if (check < 0) {
            max = cell;
        }
        cell = findNextOnDLList(cell);
    }
    return max->element;
}

DLL_t *margeDLList(DLL_t *left, DLL_t *right) {
    DLL_t *marge = createDLList();
    
    // move left list into list m.
    if (left != NULL) {
        marge->head = left->head;
        marge->tail = left->tail;
        left->head = NULL;
        left->tail = NULL;
    }
    
    // marge right list into list m.
    if (!isEmptyDLList(right)) {
        marge->tail->next = right->head;
        right->head->prev = marge->tail;
        marge->tail = right->tail;
        right->head = NULL;
        right->tail = NULL;
    }
    
    return marge;
}

bool isEmptyDLList(DLL_t *list) {
    if (list == NULL) return true;
    if (list->head == NULL) return true;
    return false;
}

DLLC_t *createCellOnDLList(void *element) {
    DLLC_t *cell = malloc(sizeof(DLLC_t));
    if (cell == NULL) {
        free(cell);
        return NULL;
    }
    cell->element = element;
    cell->next = NULL;
    
    return cell;
}

void *getElementOnDLList(DLLC_t *cell) {
    // Block illegal parameters.
    if (cell == NULL) return NULL;
    
    return cell->element;
}
