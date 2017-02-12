/*=======================================================================================*
 * @file    header.h
 * @author  Damian Pala
 * @version 0.5
 * @date    XX-XX-20XX
 * @brief   Header file for XXX module
 *
 *          This file contains API of XXX module
 *======================================================================================*/
/*----------------------- DEFINE TO PREVENT RECURSIVE INCLUSION ------------------------*/
#ifndef FIFO_H_
#define FIFO_H_

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

/*----------------------------- LOCAL OBJECT-LIKE MACROS -------------------------------*/

/*---------------------------- LOCAL FUNCTION-LIKE MACROS ------------------------------*/
#define FIFO_Create(name, item_size, items_in_fifo) \
  static uint8_t name ## _buffer[item_size * items_in_fifo]; \
  static FIFO_T name = \
  { \
    .head = 0, \
    .tail = 0, \
    .buffer = name ## _buffer, \
    .itemSize = item_size, \
    .itemsInFifo = items_in_fifo, \
    .isEmpty = true, \
    .isFull = false, \
  }

/*======================================================================================*/
/*                     ####### EXPORTED TYPE DECLARATIONS #######                       */
/*======================================================================================*/
/*-------------------------------- OTHER TYPEDEFS --------------------------------------*/
typedef void* FIFO_Handle_T;

/*------------------------------------- ENUMS ------------------------------------------*/

/*------------------------------- STRUCT AND UNIONS ------------------------------------*/
typedef struct FIFO_Tag
{
  uint16_t head;
  uint16_t tail;
  uint8_t *buffer;
  uint16_t itemSize;
  uint16_t itemsInFifo;
  bool isEmpty;
  bool isFull;
} FIFO_T;

/*======================================================================================*/
/*                    ####### EXPORTED OBJECT DECLARATIONS #######                      */
/*======================================================================================*/

/*======================================================================================*/
/*                   ####### EXPORTED FUNCTIONS PROTOTYPES #######                      */
/*======================================================================================*/
bool FIFO_PushItem(FIFO_T *fifo, void *pToItem);
bool FIFO_PopItem(FIFO_T *fifo, void *pToItem);
uint16_t FIFO_GetItemsNumber(FIFO_T *fifo);

/*======================================================================================*/
/*                          ####### INLINE FUNCTIONS #######                            */
/*======================================================================================*/

/**
 * @}
 */

#endif /* FIFO_H_ */
