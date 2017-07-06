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
#include "assert.h"

/*----------------------------- LOCAL OBJECT-LIKE MACROS -------------------------------*/

/*---------------------------- LOCAL FUNCTION-LIKE MACROS ------------------------------*/
#define ASSERT(exp)               assert(exp) // to your implementation
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
static Node_T* pGetNodeByKey(DLList_T const *pList, const uint16_t key);

/*======================================================================================*/
/*                         ####### OBJECT DEFINITIONS #######                           */
/*======================================================================================*/
/*--------------------------------- EXPORTED OBJECTS -----------------------------------*/

/*---------------------------------- LOCAL OBJECTS -------------------------------------*/

/*======================================================================================*/
/*                  ####### EXPORTED FUNCTIONS DEFINITIONS #######                      */
/*======================================================================================*/
bool DLList_IsEmpty(DLList_T * const pList)
{
  return (0 == pList->size);
}

bool DLList_PushBack(DLList_T * const pList, void *pItem)
{
  ASSERT( (NULL == pList) || (NULL == pItem) );
  if ( (NULL == pList) || (NULL == pItem) ) return false;

  Node_T *newNode = (Node_T*)malloc(sizeof(Node_T));
  ASSERT(NULL == newNode);
  if (NULL == newNode) return false;

  newNode->pItem = pItem;
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

  pList->size++;

  return true;
}

bool DLList_GetFirstItem(DLList_T * const pList, void *pItem, uint16_t * const pKey)
{
  ASSERT( (NULL == pList) || (NULL == pItem) || (NULL == pKey) );
  if ( (NULL == pList) || (NULL == pItem) || (NULL == pKey) ) return false;

  if (DLList_IsEmpty(pList))
  {
    return false;
  }

  pItem = pList->pHead->pItem;
  *pKey = pList->pHead->key;

  return true;
}

bool DLList_GetLastItem(DLList_T * const pList, void *pItem, uint16_t * const pKey)
{
  ASSERT( (NULL == pList) || (NULL == pItem) || (NULL == pKey) );
  if ( (NULL == pList) || (NULL == pItem) || (NULL == pKey) ) return false;

  if (DLList_IsEmpty(pList))
  {
    return false;
  }

  pItem = pList->pTail->pItem;
  *pKey = pList->pTail->key;

  return true;
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

bool DLList_PopByKey(DLList_T * const pList, void *pItem, const uint16_t key)
{
  ASSERT( (NULL == pList) || (NULL == pItem) );
  if ( (NULL == pList) || (NULL == pItem) ) return false;

  Node_T *node = pGetNodeByKey(pList, key);
  if (node != NULL)
  {
    pItem = node->pItem;

    // TODO change pointers!

    pList->size--;

    return true;
  }
  else
  {
    pItem = NULL;
    return false;
  }
}

/*======================================================================================*/
/*                   ####### LOCAL FUNCTIONS DEFINITIONS #######                        */
/*======================================================================================*/
static Node_T* pGetNodeByKey(DLList_T const *pList, const uint16_t key)
{
  ASSERT(NULL == pList);
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
