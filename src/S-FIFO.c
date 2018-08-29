/*=======================================================================================*
 * @file    S-FIFO.c
 * @author  Damian Pala
 * @date    12-02-2017
 * @brief   This file contains all implementations for S-FIFO module.
 *======================================================================================*/

/**
 * @addtogroup S-FIFO Static FIFO Queue
 * @{
 * @brief This module contains implementation of Static FIFO.
 */

/*======================================================================================*/
/*                       ####### PREPROCESSOR DIRECTIVES #######                        */
/*======================================================================================*/
/*-------------------------------- INCLUDE DIRECTIVES ----------------------------------*/
#include <stdint.h>
#include <stdbool.h>

#include "S-FIFO.h"

/*----------------------------- LOCAL OBJECT-LIKE MACROS -------------------------------*/

/*---------------------------- LOCAL FUNCTION-LIKE MACROS ------------------------------*/

/*======================================================================================*/
/*                      ####### LOCAL TYPE DECLARATIONS #######                         */
/*======================================================================================*/
/*-------------------------------- OTHER TYPEDEFS --------------------------------------*/

/*------------------------------------- ENUMS ------------------------------------------*/

/*------------------------------- STRUCT AND UNIONS ------------------------------------*/

/*======================================================================================*/
/*                         ####### OBJECT DEFINITIONS #######                           */
/*======================================================================================*/
/*--------------------------------- EXPORTED OBJECTS -----------------------------------*/

/*---------------------------------- LOCAL OBJECTS -------------------------------------*/

/*======================================================================================*/
/*                    ####### LOCAL FUNCTIONS PROTOTYPES #######                        */
/*======================================================================================*/
static inline bool ShouldHeadBeWraparound(SFIFO_T * const fifo);
static inline void ShouldTailBeWraparound(SFIFO_T * const fifo);

/*======================================================================================*/
/*                   ####### LOCAL FUNCTIONS DEFINITIONS #######                        */
/*======================================================================================*/
static inline bool ShouldHeadBeWraparound(SFIFO_T * const fifo)
{
  if (fifo->head == fifo->queueSizeInItems - 1)
  {
    fifo->head = 0;
    return true;
  }
  else
  {
    return false;
  }
}

static inline void ShouldTailBeWraparound(SFIFO_T * const fifo)
{
  if ( (fifo->tail == fifo->queueSizeInItems) && ( fifo->tail > fifo->head - 1) )
  {
    fifo->tail = 0;
  }
  else if (fifo->tail > fifo->queueSizeInItems)
  {
    fifo->tail = 1;
  }
  else
  {
    /* Do nothing */
  }
}

/*======================================================================================*/
/*                  ####### EXPORTED FUNCTIONS DEFINITIONS #######                      */
/*======================================================================================*/
bool SFIFO_PushItem(SFIFO_T * const fifo, void const * const pToItem)
{
  bool ret;

  if ( (false == SFIFO_IsFull(fifo)) || (true == fifo->overwriteLastItems))
  {
    uint16_t offset;
    bool isWraparoundOccurred;

    isWraparoundOccurred = ShouldHeadBeWraparound(fifo);

    if ( (fifo->itemsCnt > 0) && (false == isWraparoundOccurred) )
    {
      fifo->head++;
    }
    else
    {
      /* Do nothing */
    }

    offset = fifo->head * fifo->itemSize;

    for (uint16_t byteCnt = 0; byteCnt < fifo->itemSize; byteCnt++)
    {
      fifo->buffer[offset + byteCnt] = ((uint8_t*)pToItem)[byteCnt];
    }

    if ((true == SFIFO_IsFull(fifo)) && (true == fifo->overwriteLastItems))
    {
      fifo->tail++;
      ShouldTailBeWraparound(fifo);
    }
    else
    {
      fifo->itemsCnt++;
    }

    fifo->isEmpty = false;

    ret = true;
  }
  else
  {
    ret = false;
  }

  return ret;
}

bool SFIFO_PopItem(SFIFO_T * const fifo, void * const pToItem)
{
  bool ret;

  if (false == SFIFO_IsEmpty(fifo))
  {
    uint16_t offset = fifo->tail * fifo->itemSize;

    for (uint16_t byteCnt = 0; byteCnt < fifo->itemSize; byteCnt++)
    {
      ((uint8_t*)pToItem)[byteCnt] = fifo->buffer[offset + byteCnt];
    }

    fifo->tail++;

    fifo->isFull = false;

    fifo->itemsCnt--;

    if (true == SFIFO_IsEmpty(fifo))
    {
      SFIFO_Clear(fifo);
    }
    else
    {
      /* Do nothing */
    }

    ShouldTailBeWraparound(fifo);

    ret = true;
  }
  else
  {
    ret = false;
  }

  return ret;
}

bool SFIFO_GetItem(SFIFO_T * const fifo, uint16_t itemIndex, void * const pToItem)
{
  bool ret;
  uint16_t offset;

  if ( (false == SFIFO_IsEmpty(fifo)) && (itemIndex < fifo->itemsCnt) )
  {
    if (fifo->tail + itemIndex >= fifo->queueSizeInItems)
    {
      offset = fifo->itemSize * (fifo->tail + itemIndex - fifo->queueSizeInItems);
    }
    else
    {
      offset = fifo->itemSize * (fifo->tail + itemIndex);
    }

    for (uint16_t byteCnt = 0; byteCnt < fifo->itemSize; byteCnt++)
    {
      ((uint8_t*)pToItem)[byteCnt] = fifo->buffer[offset + byteCnt];
    }

    ret = true;
  }
  else
  {
    ret = false;
  }

  return ret;
}

bool SFIFO_GetLastPushedItem(SFIFO_T * const fifo, void * const pToItem)
{
  uint16_t offset;

  if (false == SFIFO_IsEmpty(fifo))
  {
    offset = fifo->head * fifo->itemSize;

    for (uint16_t byteCnt = 0; byteCnt < fifo->itemSize; byteCnt++)
    {
      ((uint8_t*)pToItem)[byteCnt] = fifo->buffer[offset + byteCnt];
    }

    return true;
  }
  else
  {
    return false;
  }
}

void SFIFO_Clear(SFIFO_T * const fifo)
{
  fifo->head = 0;
  fifo->tail = 0;
  fifo->isEmpty = true;
  fifo->isFull = false;
  fifo->itemsCnt = 0;
}

bool SFIFO_IsEmpty(SFIFO_T * const fifo)
{
  if (0 == fifo->itemsCnt)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool SFIFO_IsFull(SFIFO_T * const fifo)
{
  if (fifo->itemsCnt == fifo->queueSizeInItems)
  {
    return true;
  }
  else
  {
    return false;
  }
}

uint16_t SFIFO_GetItemsInFifo(SFIFO_T * const fifo)
{
  return fifo->itemsCnt;
}

void SFIFO_OverwriteLastItems(SFIFO_T * const fifo, bool overwritable)
{
  fifo->overwriteLastItems = overwritable;
}

bool SFIFO_UpdateLastPushedItem(SFIFO_T * const fifo, void const * const pToItem)
{
  uint16_t offset;

  if (false == SFIFO_IsEmpty(fifo))
  {
    offset = fifo->head * fifo->itemSize;

    for (uint16_t byteCnt = 0; byteCnt < fifo->itemSize; byteCnt++)
    {
      fifo->buffer[offset + byteCnt] = ((uint8_t*)pToItem)[byteCnt];
    }

    return true;
  }
  else
  {
    return false;
  }
}

/**
 * @} end of group S-FIFO Static FIFO Queue
 */
