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
static inline void CheckIsFullAndSetFlag(FIFO_T *fifo);
static inline void CheckIsEmptyAndSetFlag(FIFO_T *fifo);
static inline void ShouldHeadBeWraparound(FIFO_T *fifo);
static inline void ShouldTailBeWraparound(FIFO_T *fifo);

/*======================================================================================*/
/*                   ####### LOCAL FUNCTIONS DEFINITIONS #######                        */
/*======================================================================================*/
static inline void CheckIsFullAndSetFlag(FIFO_T *fifo)
{
  if ( ( (fifo->head == fifo->itemsInFifo) && (0 == fifo->tail) ) ||
     ( (fifo->head == fifo->tail) && (fifo->tail != 0)) )
  {
    fifo->isFull = true;
  }
  else
  {
    fifo->isFull = false;
  }
}

static inline void CheckIsEmptyAndSetFlag(FIFO_T *fifo)
{
  if (fifo->head == fifo->tail)
  {
    fifo->isEmpty = true;
  }
  else
  {
    fifo->isFull = false;
  }
}

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
  if (fifo->tail == fifo->itemsInFifo)
  {
    fifo->tail = 0;
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

  if (fifo->isFull != true)
  {
    ShouldHeadBeWraparound(fifo);

    for (uint16_t byteCnt = 0; byteCnt < fifo->itemSize; byteCnt++)
    {
      fifo->buffer[fifo->head + byteCnt] = ((uint8_t*)pToItem)[byteCnt];
    }
    fifo->head++;

    fifo->isEmpty = false;
    CheckIsFullAndSetFlag(fifo);

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

  if (fifo->isEmpty != true)
  {
    fifo->tail++;

    for (uint16_t byteCnt = 0; byteCnt < fifo->itemSize; byteCnt++)
    {
      ((uint8_t*)pToItem)[byteCnt] = fifo->buffer[(fifo->head - 1) + byteCnt];
    }

    fifo->isFull = false;
    CheckIsEmptyAndSetFlag(fifo);

    ShouldTailBeWraparound(fifo);

    ret = true;
  }
  else
  {
    ret = false;
  }

  return ret;
}





void FIFO_Test(FIFO_T *fifo)
{
  uint32_t ab = 0xABCDEFAC;
  uint32_t out = 0;
  FIFO_PushItem(fifo, (void*)&ab);
  FIFO_PopItem(fifo, (void*)&out);
  out++;
}

/**
 * @}
 */
