/*=======================================================================================*
 * @file    source.c
 * @author  Damian Pala
 * @version 0.4
 * @date    XX-XX-20XX
 * @brief   This file contains all implementations for XXX module.
 *======================================================================================*/

/**
 * @addtogroup XXX Description
 * @{
 * @brief Module for... .
 */

/*======================================================================================*/
/*                       ####### PREPROCESSOR DIRECTIVES #######                        */
/*======================================================================================*/
/*-------------------------------- INCLUDE DIRECTIVES ----------------------------------*/
#include <stdint.h>
#include <stdbool.h>

#include "FIFO.h"

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
static inline void ShouldHeadBeWraparound(FIFO_T *fifo);
static inline void ShouldTailBeWraparound(FIFO_T *fifo);

/*======================================================================================*/
/*                   ####### LOCAL FUNCTIONS DEFINITIONS #######                        */
/*======================================================================================*/
static inline void ShouldHeadBeWraparound(FIFO_T *fifo)
{
  if (fifo->head == fifo->itemsInFifo)
  {
    fifo->head = 0;
  }
  else
  {
    /* Do nothing */
  }
}

static inline void ShouldTailBeWraparound(FIFO_T *fifo)
{
  if ( (fifo->tail == fifo->itemsInFifo) && ( fifo->tail > fifo->head) )
  {
    fifo->tail = 0;
  }
  else if (fifo->tail > fifo->itemsInFifo)
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
bool FIFO_PushItem(FIFO_T *fifo, void *pToItem)
{
  bool ret;

  if ( (false == FIFO_IsFull(fifo)) || (true == fifo->overwriteLastItems))
  {
    ShouldHeadBeWraparound(fifo);

    uint16_t offset = fifo->head * fifo->itemSize;

    for (uint16_t byteCnt = 0; byteCnt < fifo->itemSize; byteCnt++)
    {
      fifo->buffer[offset + byteCnt] = ((uint8_t*)pToItem)[byteCnt];
    }

    fifo->head++;

    if ((true == FIFO_IsFull(fifo)) && (true == fifo->overwriteLastItems))
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

bool FIFO_PopItem(FIFO_T *fifo, void *pToItem)
{
  bool ret;

  if (false == FIFO_IsEmpty(fifo))
  {
    uint16_t offset = fifo->tail * fifo->itemSize;

    for (uint16_t byteCnt = 0; byteCnt < fifo->itemSize; byteCnt++)
    {
      ((uint8_t*)pToItem)[byteCnt] = fifo->buffer[offset + byteCnt];
    }

    fifo->tail++;

    fifo->isFull = false;

    fifo->itemsCnt--;

    if (true == FIFO_IsEmpty(fifo))
    {
      FIFO_Clear(fifo);
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

void FIFO_Clear(FIFO_T *fifo)
{
  fifo->head = 0;
  fifo->tail = 0;
  fifo->isEmpty = true;
  fifo->isFull = false;
}

bool FIFO_IsEmpty(FIFO_T *fifo)
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

bool FIFO_IsFull(FIFO_T *fifo)
{
  if (fifo->itemsCnt == fifo->itemsInFifo)
  {
    return true;
  }
  else
  {
    return false;
  }
}

uint8_t FIFO_ItemsInFifo(FIFO_T *fifo)
{
  return fifo->itemsCnt;
}

void FIFO_OverwriteLastItems(FIFO_T *fifo, bool overwritable)
{
  fifo->overwriteLastItems = overwritable;
}

/**
 * @}
 */
