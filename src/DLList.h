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
#include <stddef.h>

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
  Node_T *pPrev;
  Node_T *pNext;
  void *pItem;
  size_t itemSize; ///< Size in bytes
};

typedef struct DLList_Iface_Tag
{
  void* (*MemAlloc)(size_t size);
  void  (*MemFree)(void*);
} DLList_Iface_T;

typedef struct DLList_Tag
{
  DLList_Iface_T *pIface;
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
DLList_T* DLList_CreateList(DLList_Iface_T *pIface);
void DLList_DestroyList(DLList_T * const pList);
bool DLList_IsEmpty(DLList_T * const pList);
void DLList_PushFront(DLList_T *pList);
bool DLList_PushBack(DLList_T * const pList, void *pItemIn, size_t itemSize, void **ppItemOut);
void DLList_PushAfter(DLList_T *pList);
void DLList_PushBefore(DLList_T *pList);

bool DLList_PopFront(DLList_T * const pList);
bool DLList_PopBack(DLList_T * const pList);
bool DLList_PopByItem(DLList_T * const pList, void * const pItem);

bool DLList_GetFront(DLList_T * const pList, void **ppItem, size_t *pItemSize);
bool DLList_GetBack(DLList_T * const pList, void **ppItem, size_t *pItemSize);
bool DLList_StartTraverse(DLList_T * const pList);
bool DLList_StartTraverseWithGivenItem(DLList_T * const pList, void * const pItem);
bool DLList_GetNext(DLList_T * const pList, void **ppItem, size_t *pItemSize);

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
