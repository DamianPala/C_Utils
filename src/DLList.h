/*=======================================================================================*
 * @file    DLList.h
 * @author  Damian Pala
 * @date    05-07-2017
 * @brief   Header file for DLList module
 *
 *          This file contains API of DLList module
 *======================================================================================*/
/*----------------------- DEFINE TO PREVENT RECURSIVE INCLUSION ------------------------*/
#ifndef DLLIST_H_
#define DLLIST_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup DLList Description
 * @{
 * @brief Module for... .
 */

/*======================================================================================*/
/*                       ####### PREPROCESSOR DIRECTIVES #######                        */
/*======================================================================================*/
/*-------------------------------- INCLUDE DIRECTIVES ----------------------------------*/
#include <stdbool.h>
#include <stdint.h>

/*----------------------------- LOCAL OBJECT-LIKE MACROS -------------------------------*/

/*---------------------------- LOCAL FUNCTION-LIKE MACROS ------------------------------*/

/*======================================================================================*/
/*                     ####### EXPORTED TYPE DECLARATIONS #######                       */
/*======================================================================================*/
/*---------------------------- ALL TYPE DECLARATIONS -----------------------------------*/

/*------------------------------------- ENUMS ------------------------------------------*/

/*------------------------------- STRUCT AND UNIONS ------------------------------------*/
typedef struct Node_Tag Node_T;

struct Node_Tag
{
  uint16_t key;
  Node_T *pPrev;
  Node_T *pNext;
  void *pItem;
};

typedef struct DLList_Tag
{
  Node_T *pHead;
  Node_T *pTail;
  size_t size;
} DLList_T;

/*======================================================================================*/
/*                    ####### EXPORTED OBJECT DECLARATIONS #######                      */
/*======================================================================================*/

/*======================================================================================*/
/*                   ####### EXPORTED FUNCTIONS PROTOTYPES #######                      */
/*======================================================================================*/
bool DLList_IsEmpty(DLList_T * const pList);
void DLList_PushFront(DLList_T *pList);
bool DLList_PushBack(DLList_T * const pList, void *pItem);
void DLList_PushAfter(DLList_T *pList);
void DLList_PushBefore(DLList_T *pList);

void DLList_PopFront(DLList_T *pList);
void DLList_PopBack(DLList_T *pList);
bool DLList_PopByKey(DLList_T *pList, void *pItem, const uint16_t key);

bool DLList_GetFirstItem(DLList_T * const pList, void *pItem, uint16_t * const pKey);
bool DLList_GetLastItem(DLList_T * const pList, void *pItem, uint16_t * const pKey);
bool DLList_GetItemByKey(DLList_T *pList, uint16_t key, void *item);

size_t DLList_GetLength(DLList_T *pList);

/*======================================================================================*/
/*                          ####### INLINE FUNCTIONS #######                            */
/*======================================================================================*/

/**
 * @} end of group DLList
 */

#ifdef __cplusplus
}
#endif

#endif /* DLLIST_H_ */
