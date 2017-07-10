/*=======================================================================================*
 * @file    DLList.c
 * @author  Damian Pala
 * @date    05-07-2017
 * @brief   This file contains all implementations for DLList module.
 *======================================================================================*/

/**
 * @addtogroup DLList Description
 * @{
 * @brief Module for... .
 */

/*======================================================================================*/
/*                       ####### PREPROCESSOR DIRECTIVES #######                        */
/*======================================================================================*/
/*-------------------------------- INCLUDE DIRECTIVES ----------------------------------*/
#include "DLList.h"

#include "stddef.h"
#include "string.h"
#include "assert.h"

/*----------------------------- LOCAL OBJECT-LIKE MACROS -------------------------------*/

/*---------------------------- LOCAL FUNCTION-LIKE MACROS ------------------------------*/
#define LOC_ASSERT(exp)               //LOC_ASSERT(exp) // to your implementation

/*======================================================================================*/
/*                      ####### LOCAL TYPE DECLARATIONS #######                         */
/*======================================================================================*/
/*---------------------------- ALL TYPE DECLARATIONS -----------------------------------*/

/*-------------------------------- OTHER TYPEDEFS --------------------------------------*/

/*------------------------------------- ENUMS ------------------------------------------*/

/*------------------------------- STRUCT AND UNIONS ------------------------------------*/

/*======================================================================================*/
/*                    ####### LOCAL FUNCTIONS PROTOTYPES #######                        */
/*======================================================================================*/
static Node_T* pGetNodeByItem(DLList_T const *pList, const void * const pItem);

/*======================================================================================*/
/*                         ####### OBJECT DEFINITIONS #######                           */
/*======================================================================================*/
/*--------------------------------- EXPORTED OBJECTS -----------------------------------*/

/*---------------------------------- LOCAL OBJECTS -------------------------------------*/

/*======================================================================================*/
/*                  ####### EXPORTED FUNCTIONS DEFINITIONS #######                      */
/*======================================================================================*/
DLList_T* DLList_CreateList(DLList_Iface_T *iFace)
{
  DLList_T *pList = (DLList_T*)iFace->MemAlloc(sizeof(DLList_T));

  pList->iFace = iFace;
  pList->pHead = NULL;
  pList->pCurrent = NULL;
  pList->pTail = NULL;
  pList->size = 0;

  return pList;
}

void DLList_DestroyList(DLList_T * const pList)
{
  LOC_ASSERT(NULL != pList);
  if (NULL == pList) return;

  pList->iFace->MemFree(pList);
}

bool DLList_IsEmpty(DLList_T * const pList)
{
  LOC_ASSERT(NULL != pList);
  if (NULL == pList)
  {
    return true;
  }
  else
  {
    return (0 == pList->size);
  }
}

bool DLList_PushBack(DLList_T * const pList, void *pItemIn, size_t itemSize, void **ppItemOut)
{
  LOC_ASSERT( (NULL != pList) || (NULL != pItemIn) || (0 != itemSize) );
  if ( (NULL == pList) || (NULL == pItemIn) || (0 == itemSize) ) return false;

  Node_T *newNode = (Node_T*)pList->iFace->MemAlloc(sizeof(Node_T));
  LOC_ASSERT(NULL != newNode);
  if (NULL == newNode) return false;

  newNode->pItem = (Node_T*)pList->iFace->MemAlloc(itemSize);
  LOC_ASSERT(NULL != newNode);
  if (NULL == newNode) return false;
  memcpy(newNode->pItem, pItemIn, itemSize);

  newNode->itemSize = itemSize;
  newNode->pNext = NULL;

  if (DLList_IsEmpty(pList))
  {
    pList->pHead = newNode;
    pList->pHead->pPrev = NULL;
    pList->pTail = pList->pHead;
  }
  else
  {
    newNode->pPrev = pList->pTail;
    pList->pTail->pNext = newNode;
    pList->pTail = newNode;
  }

  *ppItemOut = newNode->pItem;

  pList->size++;

  return true;
}

bool DLList_GetFront(DLList_T * const pList, void **ppItem, size_t *pItemSize)
{
  LOC_ASSERT( (NULL != pList) || (NULL != pItem) );
  if ( (NULL == pList) || (NULL == ppItem) ) return false;

  if (DLList_IsEmpty(pList))
  {
    return false;
  }

  *ppItem = pList->pHead->pItem;
  if (pItemSize != NULL)
  {
    *pItemSize = pList->pHead->itemSize;
  }

  return true;
}

bool DLList_GetBack(DLList_T * const pList, void **ppItem, size_t *pItemSize)
{
  LOC_ASSERT( (NULL != pList) || (NULL != pItem) );
  if ( (NULL == pList) || (NULL == ppItem) ) return false;

  if (DLList_IsEmpty(pList))
  {
    return false;
  }

  *ppItem = pList->pTail->pItem;
  if (pItemSize != NULL)
  {
    *pItemSize = pList->pTail->itemSize;
  }

  return true;
}

size_t DLList_GetLength(DLList_T * const pList)
{
  LOC_ASSERT(NULL != pList);
  if (NULL == pList)
  {
    return 0;
  }
  else
  {
    return pList->size;
  }
}

bool DLList_PopFront(DLList_T * const pList)
{
  LOC_ASSERT(NULL != pList);
  if (NULL == pList) return false;

  if (pList->pHead != NULL)
  {
    if (1 == pList->size)
    {
      pList->iFace->MemFree(pList->pHead);
      pList->pHead = NULL;
      pList->pCurrent = NULL;
      pList->pTail = NULL;
    }
    else
    {
      Node_T *headToFree = pList->pHead;
      pList->pHead = pList->pHead->pNext;
      pList->pHead->pPrev = NULL;
      pList->iFace->MemFree(headToFree);
    }

    pList->size--;

    return true;
  }
  else
  {
    return false;
  }
}

bool DLList_PopBack(DLList_T * const pList)
{
  LOC_ASSERT(NULL != pList);
  if (NULL == pList) return false;

  if (pList->pTail != NULL)
  {
    if (1 == pList->size)
    {
      pList->iFace->MemFree(pList->pTail);
      pList->pHead = NULL;
      pList->pCurrent = NULL;
      pList->pTail = NULL;
    }
    else
    {
      Node_T *tailToFree = pList->pTail;
      pList->pTail = pList->pTail->pPrev;
      pList->pTail->pNext = NULL;
      pList->iFace->MemFree(tailToFree);
    }

    pList->size--;

    return true;
  }
  else
  {
    return false;
  }
}

bool DLList_PopByItem(DLList_T * const pList, void * const pItem)
{
  LOC_ASSERT(NULL != pList);
  if (NULL == pList) return false;

  Node_T *node = pGetNodeByItem(pList, pItem);
  if (node != NULL)
  {
    if (1 == pList->size)
    {
      pList->iFace->MemFree(node);
      pList->pHead = NULL;
      pList->pCurrent = NULL;
      pList->pTail = NULL;
      pList->size--;
    }
    else
    {
      if (node == pList->pHead)
      {
        DLList_PopFront(pList);
      }
      else if (node == pList->pTail)
      {
        DLList_PopBack(pList);
      }
      else
      {
        node->pPrev->pNext = node->pNext;
        node->pNext->pPrev = node->pPrev;
        pList->iFace->MemFree(node);
        pList->size--;
      }
    }

    return true;
  }
  else
  {
    return false;
  }
}

bool DLList_StartTraverse(DLList_T * const pList)
{
  LOC_ASSERT( (NULL != pList) || (NULL == pList->pHead) );
  if ( (NULL == pList) || (NULL == pList->pHead) ) return false;

  pList->pCurrent = pList->pHead;

  return true;
}

bool DLList_StartTraverseWithGivenItem(DLList_T * const pList, void * const pItem)
{
  LOC_ASSERT(NULL != pList);
  if (NULL == pList) return false;

  Node_T *node = pGetNodeByItem(pList, pItem);
  if (node != NULL)
  {
    pList->pCurrent = node;
    return true;
  }
  else
  {
    return false;
  }
}

bool DLList_GetNext(DLList_T * const pList, void **ppItem, size_t *pItemSize)
{
  LOC_ASSERT( (NULL != pList) || (NULL == pItem) );
  if ( (NULL == pList) || (NULL == ppItem) ) return false;

  if (pList->pCurrent != NULL)
  {
    *ppItem = pList->pCurrent->pItem;
    if (pItemSize != NULL)
    {
      *pItemSize = pList->pCurrent->itemSize;
    }

    pList->pCurrent = pList->pCurrent->pNext;

    return true;
  }
  else
  {
    return false;
  }
}

/*======================================================================================*/
/*                   ####### LOCAL FUNCTIONS DEFINITIONS #######                        */
/*======================================================================================*/
static Node_T* pGetNodeByItem(DLList_T const *pList, const void * const pItem)
{
  LOC_ASSERT( (NULL != pList) || (NULL != pItem) );
  if ( (NULL == pList) || (NULL == pItem) ) return NULL;

  Node_T *node = NULL;
  size_t nodeIterator = 0;

  node = pList->pHead;

  while (nodeIterator < pList->size)
  {
    if (pItem == node->pItem)
    {
      return node;
    }
    else
    {
      node = node->pNext;
    }

    nodeIterator++;
  }

  return NULL;
}

/**
 * @} end of group DLList
 */
