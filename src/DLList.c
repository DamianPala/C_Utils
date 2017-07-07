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
static Node_T* pGetNodeByKey(DLList_T const *pList, const uint32_t key);

/*======================================================================================*/
/*                         ####### OBJECT DEFINITIONS #######                           */
/*======================================================================================*/
/*--------------------------------- EXPORTED OBJECTS -----------------------------------*/

/*---------------------------------- LOCAL OBJECTS -------------------------------------*/

/*======================================================================================*/
/*                  ####### EXPORTED FUNCTIONS DEFINITIONS #######                      */
/*======================================================================================*/
DLList_T* DLList_CreateList(void)
{
  DLList_T *pList = (DLList_T*)malloc(sizeof(DLList_T));

  pList->pHead = NULL;
  pList->pCurrent = NULL;
  pList->pTail = NULL;
  pList->size = 0;

  return pList;
}

void DLList_DestroyList(DLList_T *pList)
{
  LOC_ASSERT(NULL != pList);
  if (NULL == pList) return;

  free(pList);
}

bool DLList_IsEmpty(DLList_T * const pList)
{
  return (0 == pList->size);
}

bool DLList_PushBack(DLList_T * const pList, void *pItem, size_t itemSize, uint32_t * const pKey)
{
  LOC_ASSERT( (NULL != pList) || (NULL != pItem) || (0 != itemSize) );
  if ( (NULL == pList) || (NULL == pItem) || (0 == itemSize) ) return false;

  Node_T *newNode = (Node_T*)malloc(sizeof(Node_T));
  LOC_ASSERT(NULL != newNode);
  if (NULL == newNode) return false;

  newNode->pItem = malloc(itemSize);
  LOC_ASSERT(NULL != newNode);
  if (NULL == newNode) return false;
  memcpy(newNode->pItem, pItem, itemSize);

  newNode->itemSize = itemSize;
  newNode->pNext = NULL;

  if (DLList_IsEmpty(pList))
  {
    newNode->key = 0;
    pList->pHead = newNode;
    pList->pHead->pPrev = NULL;
    pList->pTail = pList->pHead;
  }
  else
  {
    newNode->key = pList->pTail->key + 1;
    newNode->pPrev = pList->pTail;
    pList->pTail->pNext = newNode;
    pList->pTail = newNode;
  }

  *pKey = newNode->key;

  pList->size++;

  return true;
}

// TODO: finish
bool DLList_GetFront(DLList_T * const pList, void *pItem, uint32_t * const pKey)
{
  LOC_ASSERT( (NULL != pList) || (NULL != pItem) || (NULL != pKey) );
  if ( (NULL == pList) || (NULL == pItem) || (NULL == pKey) ) return false;

  if (DLList_IsEmpty(pList))
  {
    return false;
  }

  pItem = pList->pHead->pItem;
  *pKey = pList->pHead->key;

  return true;
}

bool DLList_GetBack(DLList_T * const pList, void **pItem, size_t *itemSize, uint32_t * const pKey)
{
  LOC_ASSERT(NULL != pList);
  if (NULL == pList) return false;

  if (DLList_IsEmpty(pList))
  {
    return false;
  }

  *pItem = pList->pTail->pItem;
  if (itemSize != NULL)
  {
    *itemSize = pList->pTail->itemSize;
  }
  if (pKey != NULL)
  {
    *pKey = pList->pTail->key;
  }

  return true;
}

bool DLList_GetByKey(DLList_T * const pList, const uint32_t key, void **pItem, size_t *itemSize)
{
  LOC_ASSERT(NULL != pList);
  if (NULL == pList) return false;

  Node_T *node = pGetNodeByKey(pList, key);

  if (node != NULL)
  {
    *pItem = node->pItem;
    if (itemSize != NULL)
    {
      *itemSize = node->itemSize;
    }
    return true;
  }
  else
  {
    return false;
  }
}

size_t DLList_GetLength(DLList_T * const pList)
{
  if (NULL == pList)
  {
    return 0;
  }
  else
  {
    return pList->size;
  }
}

bool DLList_PopByKey(DLList_T * const pList, const uint32_t key)
{
  LOC_ASSERT(NULL != pList);
  if (NULL == pList) return false;

  Node_T *node = pGetNodeByKey(pList, key);
  if (node != NULL)
  {
    // TODO: what if its head or tail?
    node->pPrev->pNext = node->pNext;
    node->pNext->pPrev = node->pPrev;

    free(node);

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
      free(pList->pTail);
      pList->pHead = NULL;
      pList->pCurrent = NULL;
      pList->pTail = NULL;
    }
    else
    {
      Node_T *tailToFree = pList->pTail;
      pList->pTail = pList->pTail->pPrev;
      pList->pTail->pNext = NULL;
      free(tailToFree);
    }

    pList->size--;

    return true;
  }
  else
  {
    return false;
  }
}

bool DLList_StartTraverse(DLList_T * const pList)
{
  LOC_ASSERT(NULL != pList);
  if ( (NULL == pList) || (NULL == pList->pHead) ) return false;

  pList->pCurrent = pList->pHead;

  return true;
}

bool DLList_GetNext(DLList_T * const pList, void *pItem, uint32_t * const pKey)
{
  LOC_ASSERT( (NULL != pList) || (NULL == pItem) );
  if ( (NULL == pList) || (NULL == pItem) ) return false;

  if (pList->pCurrent->pNext != NULL)
  {
    pList->pCurrent = pList->pCurrent->pNext;
    pItem = pList->pCurrent->pItem;
    *pKey = pList->pCurrent->key;

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
static Node_T* pGetNodeByKey(DLList_T const *pList, const uint32_t key)
{
  LOC_ASSERT(NULL != pList);
  if (NULL == pList) return NULL;

  Node_T *node = NULL;
  size_t nodeIterator = 0;

  node = pList->pHead;

  while (nodeIterator < pList->size)
  {
    if (key == node->key)
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
