#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>


#include "list_mtm1.h"

typedef struct sNode Node;

static Node* createNode (CopyListElement copy, ListElement element);
static void destoryNode(Node* current, FreeListElement freeElement);

struct sNode{
    ListElement element;
    struct sNode* next;
};

struct list_t{
    Node* elements_list;
    int size;
    Node* iterator;
    
    CopyListElement copy;
    FreeListElement free;
};


// =============================================================================
List listCreate(CopyListElement copyElement, FreeListElement freeElement){
    if (copyElement == NULL || freeElement == NULL) {
        return NULL;
    }
    
    List list = malloc(sizeof(*list));
    if (list == NULL) {
        return NULL;
    }
    
    list->elements_list = NULL;
    list->size = 0;
    list->iterator = NULL;
    list->copy = copyElement;
    list->free = freeElement;
    
    return list;
}


List listCopy(List list){
    if (list == NULL){
        return NULL;
    }
    List new_list = listCreate(list->copy, list->free);
    if (new_list == NULL){
        return NULL;
    }
//    new_list->size = list->size;
    Node* temp_iterator = list->iterator;
    int iterator_place=0;
    int i=0;
    LIST_FOREACH(ListElement, current, list){
        if (listInsertLast(new_list, current) != LIST_SUCCESS){
            listDestroy(new_list);
            return NULL;
        }
        if (temp_iterator != NULL && temp_iterator->element == current) {
            iterator_place = i;
        }
        i++;
    }
    listGetFirst(new_list);
    for (int j=0; j<iterator_place; j++) {
        listGetNext(new_list);
    }
    list->iterator = temp_iterator;
    return new_list;
}


int listGetSize(List list){
    if (list == NULL) {
        return -1;
    }
    return list->size;
}


ListElement listGetFirst(List list){
    if (list == NULL) {
        return NULL;
    }
    list->iterator = list->elements_list;
    if (list->iterator == NULL) {
        return NULL;
    }
//    printf("test getfirst: %d\n",*(int*)list->iterator->element);
    return list->iterator->element;
}


ListElement listGetNext(List list){
    if (list == NULL || list->iterator == NULL){
        return NULL;
    }
    list->iterator = list->iterator->next;
    if (list->iterator == NULL){
        return NULL;
    }
    return list->iterator->element;
}


ListElement listGetCurrent(List list){
    if (list == NULL || list->iterator == NULL){
        return NULL;
    }
    return list->iterator->element;
}


ListResult listInsertFirst(List list, ListElement element){
    if (list == NULL){
        return LIST_NULL_ARGUMENT;
    }
    Node* new_node = createNode(list->copy, element);
    if (new_node == NULL){
        return LIST_OUT_OF_MEMORY;
    }
    new_node->next = list->elements_list;
    list->elements_list = new_node;
    list->size++;
    return LIST_SUCCESS;
}


ListResult listInsertLast(List list, ListElement element){
    if (list == NULL) {
        return LIST_NULL_ARGUMENT;
    }
    Node* new_node = createNode(list->copy, element);
    if (new_node == NULL) {
        return LIST_OUT_OF_MEMORY;
    }
    new_node->next = NULL;
    if(list->elements_list == NULL){
        list->elements_list = new_node;
    } else{
        Node* tmp_iterator = list->elements_list;
        while (tmp_iterator->next != NULL){
            tmp_iterator = tmp_iterator->next;
        }
        tmp_iterator->next = new_node;
    }
    list->size++;
    return LIST_SUCCESS;
}


ListResult listInsertBeforeCurrent(List list, ListElement element){
    if (list == NULL) {
        return LIST_NULL_ARGUMENT;
    }
    Node* new_node = createNode(list->copy, element);
    if (new_node == NULL) {
        return LIST_OUT_OF_MEMORY;
    }
    Node* current = listGetCurrent(list);
    if (current == NULL) {
        destoryNode(new_node, list->free);
        return LIST_INVALID_CURRENT;
    }
    new_node->next = list->iterator;
    
    if(list->elements_list->element == current){
        list->elements_list = new_node;
    } else{
        Node* tmp_iterator = list->elements_list;
        while (tmp_iterator->next->element != current){
            tmp_iterator = tmp_iterator->next;
        }
        tmp_iterator->next = new_node;
    }
    list->size++;
    return LIST_SUCCESS;
}


ListResult listInsertAfterCurrent(List list, ListElement element){
    if (list == NULL) {
        return LIST_NULL_ARGUMENT;
    }
    Node* current = listGetCurrent(list);
    if (current == NULL) {
        return LIST_INVALID_CURRENT;
    }
    Node* new_node = createNode(list->copy, element);
    if (new_node == NULL) {
        return LIST_OUT_OF_MEMORY;
    }
    new_node->next = list->iterator->next;
    list->iterator->next = new_node;
    list->size++;
    return LIST_SUCCESS;
}


ListResult listRemoveCurrent(List list){
    if (list == NULL) {
        return LIST_NULL_ARGUMENT;
    }
    if (list->iterator == NULL) {
        return LIST_INVALID_CURRENT;
    }
    ListElement current = listGetCurrent(list);
    Node* tmp_iterator = list->elements_list;
    if (list->elements_list == NULL) {
        return LIST_SUCCESS;
    } else if(tmp_iterator->element == current){
        list->elements_list = list->elements_list->next;
//    } else if(tmp_iterator->next->next){
        
    } else{
        while (tmp_iterator->next->element != current){
            tmp_iterator = tmp_iterator->next;
        }
        Node* tmp2 = tmp_iterator->next; // ====================== chenge names ===========================
        tmp_iterator->next = tmp_iterator->next->next;
        tmp_iterator = tmp2;
//        tmp_iterator = tmp_iterator->next;
    }
    destoryNode(tmp_iterator, list->free);
    list->size--;
    list->iterator = NULL;
    return LIST_SUCCESS;
}


ListResult listSort(List list, CompareListElements compareElement){
    if (list == NULL || compareElement == NULL) {
        return LIST_NULL_ARGUMENT;
    }
    if (listGetFirst(list) == NULL || listGetNext(list) == NULL) {
        return LIST_SUCCESS;
    }
    for (int i=0; i<listGetSize(list); i++) {
        bool swapped = false;
        Node* ptr1 = list->elements_list;
        Node* ptr2 = list->elements_list->next;
        for(int j=0; j< listGetSize(list)-i-1; j++) {
            if (compareElement(ptr1->element,ptr2->element) > 0) {
                ListElement tmp = ptr1->element;
                ptr1->element = ptr2->element;
                ptr2->element = tmp;
                swapped = true;
            }
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
            if (ptr2 == NULL) {
                break;
            }
        }
        if (swapped == false) {
            break;
        }
    }
    return LIST_SUCCESS;
}


List listFilter(List list, FilterListElement filterElement, ListFilterKey key){
    if (list == NULL || filterElement == NULL){
        return NULL;
    }
    List new_list = listCopy(list);
    if (new_list == NULL){
        return NULL;
    }

    Node* temp_ptr = new_list->elements_list;
    while (temp_ptr != NULL) {
        if (filterElement(temp_ptr->element, key) == false){
            new_list->iterator = temp_ptr;
            temp_ptr = temp_ptr->next;
            listRemoveCurrent(new_list);
        } else{
            temp_ptr = temp_ptr->next;
        }
    }
    
    
    
    
/*
    while (new_list->iterator != NULL ){
        if (filterElement(listGetCurrent(new_list), key) == false) {
            listRemoveCurrent(new_list);
            listGetFirst(new_list);
        } else{
            listGetNext(new_list);
        }
    }*/
//    LIST_FOREACH(ListElement, current, new_list){
//        if (filterElement(current, key) == false) {
//            listRemoveCurrent(new_list);
//            listGetFirst(new_list);
//        }
//    }
    return new_list;
}


ListResult listClear(List list){
    if (list == NULL) {
        return LIST_NULL_ARGUMENT;
    }
    Node* current = listGetFirst(list);
    while (current != NULL/* || listGetSize(list) > 0*/){
        listRemoveCurrent(list);
        current = listGetFirst(list);
    }
    return LIST_SUCCESS;
}


void listDestroy(List list){
    if (list == NULL) {
        return;
    }
    listClear(list);
    free(list);
    list = NULL;
}


static Node* createNode(CopyListElement copy, ListElement element){
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL){
        return NULL;
    }
    if (element == NULL){
        new_node->element = NULL;
    } else {
        new_node->element = copy(element);
    }
    return new_node;
}


static void destoryNode(Node* current, FreeListElement freeElement){
//    if (current == NULL){
//        return;
//    }
    assert(current != NULL);
    assert(freeElement != NULL);
    
    freeElement(current->element);
    free(current);
}
