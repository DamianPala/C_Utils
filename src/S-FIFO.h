/*=======================================================================================*
 * @file    S-FIFO.h
 * @author  Damian Pala
 * @version 0.5
 * @date    12-02-2017
 * @brief   Header file for S-FIFO module
 *
 *          This file contains API of S-FIFO module
 *======================================================================================*/
/*----------------------- DEFINE TO PREVENT RECURSIVE INCLUSION ------------------------*/
#ifndef S_FIFO_H_
#define S_FIFO_H_

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @addtogroup S-FIFO Static FIFO Queue
 * @{
 * @brief S-FIFO module contains implementation of Static FIFO queue. Static means that memory is static allocated.
 *
 *        Items in this FIFO have to be fixed size and also size of queue have to be fixed.
 *        Items size is in bytes, FIFO size is in items number.
 *        Buffer intended for use by queue is automatically allocated.
 *        Queue can operate in mode when pushing operation overwrite last item with new one. This mode can be set
 *        via #SFIFO_OverwriteLastItems function.
 */

/*======================================================================================*/
/*                       ####### PREPROCESSOR DIRECTIVES #######                        */
/*======================================================================================*/
/*-------------------------------- INCLUDE DIRECTIVES ----------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/*----------------------------- LOCAL OBJECT-LIKE MACROS -------------------------------*/

/*---------------------------- LOCAL FUNCTION-LIKE MACROS ------------------------------*/
/**
 * @brief Macro function responsible for memory allocation, queue object and handle creation.
 * @param [in] name is the name of queue handle
 * @param [in] item_size is the item size in bytes
 * @param [in] queue_size_in_items is the size of queue counted in items
 */
#define SFIFO_Create(name, item_size, queue_size_in_items) \
  static uint8_t name ## _buffer[item_size * queue_size_in_items]; \
  static SFIFO_T name ## _data = \
  { \
    0, \
    0, \
    name ## _buffer, \
    item_size, \
    queue_size_in_items, \
    0, \
    true, \
    false, \
    false \
  }; \
  static SFIFO_T * name = &name ## _data;

/**
 * @brief Macro function responsible for memory allocation, queue object and handle creation. Volatile type.
 * @param [in] name is the name of queue handle
 * @param [in] item_size is the item size in bytes
 * @param [in] queue_size_in_items is the size of queue counted in items
 */
#define SFIFO_CreateVolatile(name, item_size, queue_size_in_items) \
  static volatile uint8_t name ## _buffer[item_size * queue_size_in_items]; \
  static volatile SFIFO_T name ## _data = \
  { \
    0, \
    0, \
    (uint8_t*)name ## _buffer, \
    item_size, \
    queue_size_in_items, \
    0, \
    true, \
    false, \
    false \
  }; \
  static volatile SFIFO_T * name = &name ## _data;

/*======================================================================================*/
/*                     ####### EXPORTED TYPE DECLARATIONS #######                       */
/*======================================================================================*/
/*-------------------------------- OTHER TYPEDEFS --------------------------------------*/

/*------------------------------------- ENUMS ------------------------------------------*/

/*------------------------------- STRUCT AND UNIONS ------------------------------------*/
/** FIFO structure definition */
typedef struct SFIFO_Tag
{
  uint16_t head;                ///< Points to last item in queue
  uint16_t tail;                ///< Points to first item in queue
  uint8_t *buffer;              ///< Queue buffer
  uint16_t itemSize;            ///< Item size in bytes
  uint16_t queueSizeInItems;    ///< Queue size in items
  uint16_t itemsCnt;            ///< Items in queue counter
  bool isEmpty;                 ///< Is empty flag
  bool isFull;                  ///< Is full flag
  bool overwriteLastItems;      ///< Select overwrite mode flag
} SFIFO_T;

/*======================================================================================*/
/*                    ####### EXPORTED OBJECT DECLARATIONS #######                      */
/*======================================================================================*/

/*======================================================================================*/
/*                   ####### EXPORTED FUNCTIONS PROTOTYPES #######                      */
/*======================================================================================*/
/**
 * @brief   This function pushes item into queue.
 * @param   [in] fifo       is queue handle equals name of created FIFO queue
 * @param   [in] pToItem    is pointer to pushed item
 * @return  Result of the pushing operation.
 * @retval  true if item pushed properly
 * @retval  false if queue is full
 */
bool SFIFO_PushItem(SFIFO_T *fifo, void *pToItem);


/**
 * @brief   This function pops item from queue.
 * @param   [in] fifo       is queue handle equals name of created FIFO queue
 * @param   [out] pToItem   is pointer to place where popped item should be written
 * @return  Result of the popping operation.
 * @retval  true if item popped properly
 * @retval  false if queue is empty
 */
bool SFIFO_PopItem(SFIFO_T *fifo, void *pToItem);


/**
 * @brief   This function gets item from queue on given index.
 * @param   [in] fifo       is queue handle equals name of created FIFO queue
 * @param   [in] itemIndex  is index of item to get
 * @param   [out] pToItem   is pointer to place where obtained item should be written
 * @return  Result of the getting operation.
 * @retval  true if item got properly
 * @retval  false if queue is empty
 */
bool SFIFO_GetItem(SFIFO_T *fifo, uint16_t itemIndex, void *pToItem);


/**
 * @brief   This function gets item from queue on given index.
 * @param   [in] fifo       is queue handle equals name of created FIFO queue
 * @param   [out] pToItem   is pointer to place where obtained item should be written
 * @return  Result of the getting operation.
 * @retval  true if item got properly
 * @retval  false if queue is empty
 */
bool SFIFO_GetLastPushedItem(SFIFO_T *fifo, void *pToItem);


/**
 * @brief   This function clears queue.
 * @param   [in] fifo       is queue handle equals name of created FIFO queue
 */
void SFIFO_Clear(SFIFO_T *fifo);


/**
 * @brief   This function checks if queue is empty.
 * @param   [in] fifo       is queue handle equals name of created FIFO queue
 * @return  True or False
 */
bool SFIFO_IsEmpty(SFIFO_T *fifo);


/**
 * @brief   This function checks if queue is full.
 * @param   [in] fifo       is queue handle equals name of created FIFO queue
 * @return  True or False
 */
bool SFIFO_IsFull(SFIFO_T *fifo);


/**
 * @brief   This function returns number of items in queue.
 * @param   [in] fifo       is queue handle equals name of created FIFO queue
 * @return  Number of items in queue.
 */
uint16_t SFIFO_GetItemsInFifo(SFIFO_T *fifo);


/**
 * @brief   This function updates last item pushed into queue.
 * @param   [in] fifo       is queue handle equals name of created FIFO queue
 * @param   [out] pToItem   is pointer to item
 * @return  True or False
 */
bool SFIFO_UpdateLastPushedItem(SFIFO_T *fifo, void *pToItem);


/**
 * @brief   This function sets FIFO mode.
 * @param   [in] fifo           is queue handle equals name of created FIFO queue
 * @param   [in] overwritable   If set to true, queue overwrites last item with new pushed item.
 *                              If set to false, queue operates as normal queue without overwriting items.
 */
void SFIFO_OverwriteLastItems(SFIFO_T *fifo, bool overwritable);

/*======================================================================================*/
/*                          ####### INLINE FUNCTIONS #######                            */
/*======================================================================================*/

/**
 * @} end of group S-FIFO Static FIFO Queue
 */

#ifdef __cplusplus
}
#endif

#endif /* S_FIFO_H_ */
