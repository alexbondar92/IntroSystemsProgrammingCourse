#include "test_utilities.h"
#include "../list_mtm/list_mtm1.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

static ListElement copyString(ListElement str){
	assert(str);
	char* copy = malloc(strlen(str)+1);
	return copy != NULL ? strcpy(copy, str) : NULL;
}

static void freeString(ListElement str){
	free(str);
}

static bool isLongerThan(ListElement element,ListFilterKey number) {
	char* string = element;
    return strlen(string) > *(int*)number;
}

static bool testListCreate() {
	ASSERT_TEST(listCreate(NULL,NULL) == NULL);
	ASSERT_TEST(listCreate(NULL,NULL) == NULL);
	ASSERT_TEST(listCreate(copyString,NULL) == NULL);
	ASSERT_TEST(listCreate(NULL,freeString) == NULL);

	return true;
}
static bool testListFilter() {
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	List list = listCreate(copyString,freeString);
    if (list == NULL) {
        return false;
    }
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
    assert(strcmp(listGetFirst(list),"I") == 0);
    assert(strcmp(listGetNext(list),"hello mister fish") == 0);
    assert(strcmp(listGetNext(list),"NI") == 0);
    assert(strcmp(listGetNext(list),"bbb") == 0);
    assert(strcmp(listGetNext(list),"aaa") == 0);
    assert(listGetNext(list) == NULL);
    
	int key = 5;
	List filtered = listFilter(list,isLongerThan, &key);
	ASSERT_TEST(listGetSize(filtered) == 1);
	ASSERT_TEST(strcmp(listGetFirst(filtered),a[3])==0);
	listDestroy(list);
	listDestroy(filtered);
	return true;
}

static bool testListGetSize() {
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	List list = listCreate(copyString,freeString);
    if (list == NULL) {
        return false;
    }
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	listDestroy(list);
	return true;
}

static bool testListGetFirst() {
    char* a[8] = {"We","all","live","in","a","yellow","submarine","!"};
    List list = listCreate(copyString,freeString);
    if (list == NULL) {
        return false;
    }
    ASSERT_TEST(listGetFirst(list) == NULL);
    listInsertFirst(list, a[0]);
    ASSERT_TEST(strcmp(listGetFirst(list),a[0]) == 0);
    for(int i=1; i<=6; i++){
        listInsertFirst(list, a[i]);
    }
    for (int i=0; i<=10; i++){
        listGetNext(list);
    }
    ASSERT_TEST(strcmp(listGetFirst(list),a[6]) == 0);
    ASSERT_TEST(strcmp(listGetFirst(list),a[7]) != 0);
    
    List null_list = NULL;
    ASSERT_TEST(listGetFirst(null_list) == NULL);
    listDestroy(list);
	return true;
}

static bool testListGetNext() {
    char* a[6] = {"Despacito","Pasito","a","pasito","suave","suavecito"};
    List null_list = NULL;
    ASSERT_TEST(listGetNext(null_list) == NULL);
    listGetFirst(null_list);
    ASSERT_TEST(listGetNext(null_list) == NULL);
    
    List list = listCreate(copyString, freeString);
    if (list == NULL) {
        return false;
    }
    listInsertFirst(list, a[0]);
    listGetFirst(list);
    for(int i=1; i<6; i++){
        listInsertAfterCurrent(list, a[i]);
        listGetNext(list);
    }
    ASSERT_TEST(listGetNext(list) == NULL);
    listGetFirst(list);
    ASSERT_TEST(strcmp(listGetNext(list), a[1]) == 0);
    for(int i=2; i<6; i++){
        ASSERT_TEST(strcmp(listGetNext(list), a[i]) == 0);
    }
    ASSERT_TEST(listGetNext(list) == NULL);
    listDestroy(list);
	return true;
}

static bool testListInsertFirst() {
    char* a[5] = {"yoav","noam","sahar","alen","omer"};
    List null_list = NULL;
    ASSERT_TEST(listInsertFirst(null_list, a[0]) == LIST_NULL_ARGUMENT);
    List list = listCreate(copyString, freeString);
    if (list == NULL) {
        return false;
    }
    ASSERT_TEST(listInsertFirst(list, a[0]) == LIST_SUCCESS);
    listInsertFirst(list, a[1]);
    listInsertFirst(list, a[2]);
    ASSERT_TEST(strcmp(listGetFirst(list),a[2]) == 0);
    listGetNext(list);
    listGetNext(list);
    ASSERT_TEST(listInsertFirst(list, a[3]) == LIST_SUCCESS);
    ASSERT_TEST(strcmp(listGetFirst(list), a[3]) == 0);
    listDestroy(list);
	return true;
}

static bool testListInsertLast() {
    char* a[5] = {"sagi","maor","noy"};
    List null_list = NULL;
    ASSERT_TEST(listInsertLast(null_list, a[0]) == LIST_NULL_ARGUMENT);
    List list = listCreate(copyString, freeString);
    if (list == NULL) {
        return false;
    }
    ASSERT_TEST(listInsertLast(list, a[0]) == LIST_SUCCESS);
    listGetFirst(list);
    ASSERT_TEST(listInsertLast(list, a[1]) == LIST_SUCCESS);
    ASSERT_TEST(strcmp(listGetNext(list), a[1]) == 0);
    listInsertLast(list, a[2]);
    ASSERT_TEST(strcmp(listGetNext(list),a[2]) == 0);
    listDestroy(list);
	return true;
}

static bool testListInsertBeforeCurrent() {
    char* a[5] = {"tel aviv", "rishon", "haifa", "jerusalem"};
    List null_list = NULL;
    ASSERT_TEST(listInsertBeforeCurrent(null_list, a[0]) == LIST_NULL_ARGUMENT);
    List list = listCreate(copyString, freeString);
    if (list == NULL) {
        return false;
    }
    ASSERT_TEST(listInsertBeforeCurrent(list, a[0]) == LIST_INVALID_CURRENT);
    listGetFirst(list);
    ASSERT_TEST(listInsertBeforeCurrent(list, a[0]) == LIST_INVALID_CURRENT);
    listInsertFirst(list, a[0]);
    ASSERT_TEST(listInsertBeforeCurrent(list, a[1]) == LIST_INVALID_CURRENT);
    listGetFirst(list);
    ASSERT_TEST(listInsertBeforeCurrent(list, a[1]) == LIST_SUCCESS);
    ASSERT_TEST(strcmp(listGetFirst(list),a[1]) == 0);
    ASSERT_TEST(listInsertBeforeCurrent(list, a[2]) == LIST_SUCCESS);
    ASSERT_TEST(strcmp(listGetFirst(list),a[2]) == 0);
    listGetNext(list);
    listInsertBeforeCurrent(list, a[3]);
    listGetFirst(list);
    ASSERT_TEST(strcmp(listGetNext(list),a[3]) == 0);

    listDestroy(list);
	return true;
}

static bool testListInsertAfterCurrent() {
    char* a[8] = {"We","all","live","in","a","yellow","submarine","!"};
    List null_list = NULL;
    ASSERT_TEST(listInsertAfterCurrent(null_list, a[0]) == LIST_NULL_ARGUMENT);
    List list = listCreate(copyString,freeString);
    if (list == NULL) {
        return false;
    }
    ASSERT_TEST(listInsertAfterCurrent(list, a[0]) == LIST_INVALID_CURRENT);
    listGetFirst(list);
    ASSERT_TEST(listInsertAfterCurrent(list, a[0]) == LIST_INVALID_CURRENT);
    listInsertFirst(list, a[0]);
    ASSERT_TEST(listInsertAfterCurrent(list, a[1]) == LIST_INVALID_CURRENT);
    listGetFirst(list);
    
    ASSERT_TEST(listInsertAfterCurrent(list, a[1]) == LIST_SUCCESS);
    ASSERT_TEST(strcmp(listGetNext(list),a[1]) == 0);
    ASSERT_TEST(listInsertAfterCurrent(list, a[2]) == LIST_SUCCESS);
    ASSERT_TEST(strcmp(listGetNext(list),a[2]) == 0);
    listGetFirst(list);
    listInsertAfterCurrent(list, a[3]);
    ASSERT_TEST(strcmp(listGetNext(list),a[3]) == 0);
    
    listDestroy(list);
	return true;
}

static bool testListRemoveCurrent() {
    char* a[8] = {"We","all","live","in","a","yellow","submarine","!"};
    List list = listCreate(copyString,freeString);
    if (list == NULL) {
        return false;
    }
    ASSERT_TEST(listRemoveCurrent(list) == LIST_INVALID_CURRENT);

    listGetFirst(list);
    listInsertFirst(list, a[0]);
    for(int i=1; i<=7; i++){
        listInsertFirst(list, a[i]);
    }
    
    List null_list = NULL;
    ASSERT_TEST(listRemoveCurrent(null_list) == LIST_NULL_ARGUMENT);
    listGetFirst(list);
    ASSERT_TEST(listRemoveCurrent(list) == LIST_SUCCESS);
    ASSERT_TEST(listRemoveCurrent(list) == LIST_INVALID_CURRENT);
    listGetFirst(list);
    listGetNext(list);
    listGetNext(list);
    ASSERT_TEST(listRemoveCurrent(list) == LIST_SUCCESS);
    
    listDestroy(list);
	return true;
}

static bool testListSort() {
	return true;
}

static bool testListClear() {
    List null_list = NULL;
    ASSERT_TEST(listClear(null_list) == LIST_NULL_ARGUMENT);

    char* a[8] = {"We","all","live","in","a","yellow","submarine","!"};
    List list = listCreate(copyString,freeString);
    if (list == NULL) {
        return false;
    }
    for(int i=0; i<=7; i++){
        listInsertFirst(list, a[i]);
    }
    ASSERT_TEST(listClear(list) == LIST_SUCCESS);
    ASSERT_TEST(listClear(list) == LIST_SUCCESS);

    listDestroy(list);
	return true;
}

static bool testListCopy() {
    List null_list = NULL;
    ASSERT_TEST(listCopy(null_list) == NULL);
    
    char* a[8] = {"We","all","live","in","a","yellow","submarine","!"};
    List list = listCreate(copyString,freeString);
    if (list == NULL) {
        return false;
    }
    for(int i=0; i<=7; i++){
        listInsertFirst(list, a[i]);
    }
    listGetFirst(list);
    listGetNext(list);
    listGetNext(list);
    List copied_list = listCopy(list);
    ASSERT_TEST(copied_list != NULL);
    ASSERT_TEST(strcmp(listGetCurrent(list), listGetCurrent(copied_list)) == 0);
    ASSERT_TEST(listGetSize(list) == listGetSize(copied_list));
    ASSERT_TEST(strcmp(listGetNext(list),listGetNext(copied_list)) == 0);
    
    listGetFirst(list);
    listGetFirst(copied_list);
    for(int i=0; i<=7; i++){
        ASSERT_TEST(strcmp(listGetCurrent(list), listGetCurrent(copied_list))==0);
        listGetNext(list);
        listGetNext(copied_list);
    }
    listDestroy(list);
    listDestroy(copied_list);
    
    return true;
}

static bool testListDestroy() {
    /* ========== already had been chacked in all other tests ============ */
	return true;
}

int main (int argv, char** arc){
	RUN_TEST(testListCreate);
	RUN_TEST(testListFilter);
	RUN_TEST(testListGetSize);
	RUN_TEST(testListGetFirst);
	RUN_TEST(testListGetNext);
	RUN_TEST(testListInsertFirst);
	RUN_TEST(testListInsertLast);
	RUN_TEST(testListInsertBeforeCurrent);
	RUN_TEST(testListInsertAfterCurrent);
	RUN_TEST(testListRemoveCurrent);
	RUN_TEST(testListSort);
	RUN_TEST(testListClear);
 	RUN_TEST(testListCopy);
	RUN_TEST(testListDestroy);
	return 0;
}

