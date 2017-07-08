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
 * @brief Module for Doubly Linked List implementation.
 *
 *        List is limited to UINT32_MAX elements
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
  uint32_t key;
  Node_T *pPrev;
  Node_T *pNext;
  void *pItem;
  size_t itemSize; ///< Size in bytes
};

typedef struct DLList_Tag
{
  Node_T *pHead;
  Node_T *pCurrent;
  Node_T *pTail;
  size_t size;
} DLList_T;

/*======================================================================================*/
/*                    ####### EXPORTED OBJECT DECLARATIONS #######                      */
/*======================================================================================*/

/*======================================================================================*/
/*                   ####### EXPORTED FUNCTIONS PROTOTYPES #######                      */
/*======================================================================================*/
DLList_T* DLList_CreateList(void);
void DLList_DestroyList(DLList_T * const pList);
bool DLList_IsEmpty(DLList_T * const pList);
void DLList_PushFront(DLList_T *pList);
bool DLList_PushBack(DLList_T * const pList, void *pItem, size_t itemSize, uint32_t * const pKey);
void DLList_PushAfter(DLList_T *pList);
void DLList_PushBefore(DLList_T *pList);

bool DLList_PopFront(DLList_T * const pList);
bool DLList_PopBack(DLList_T * const pList);
bool DLList_PopByKey(DLList_T * const pList, const uint32_t key);

bool DLList_GetFront(DLList_T * const pList, void *pItem, uint32_t * const pKey);
bool DLList_GetBack(DLList_T * const pList, void **pItem, size_t *pItemSize, uint32_t * const pKey);
bool DLList_GetByKey(DLList_T * const pList, const uint32_t key, void **pItem, size_t *pItemSize);
bool DLList_StartTraverse(DLList_T * const pList);
bool DLList_GetNext(DLList_T * const pList, void **pItem, size_t *pItemSize, uint32_t *pKey);

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
