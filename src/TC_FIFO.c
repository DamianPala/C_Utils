/*=======================================================================================*
 * @file    TC_FIFO.c
 * @author  Damian Pala
 * @date    29-01-2017
 * @brief   This file contains unit tests for Soft Timers module.
 *======================================================================================*/

/**
 * @addtogroup Soft Timers Unit Tests Description
 * @{
 * @brief Module for... .
 */

/*======================================================================================*/
/*                       ####### PREPROCESSOR DIRECTIVES #######                        */
/*======================================================================================*/
/*---------------------- INCLUDE DIRECTIVES FOR STANDARD HEADERS -----------------------*/

/*----------------------- INCLUDE DIRECTIVES FOR OTHER HEADERS -------------------------*/
#include "unity.h"
#include "unity_fixture.h"

#include "FIFO.c"

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
TEST_GROUP(FIFO);

/*======================================================================================*/
/*                    ####### LOCAL FUNCTIONS PROTOTYPES #######                        */
/*======================================================================================*/

/*======================================================================================*/
/*                   ####### LOCAL FUNCTIONS DEFINITIONS #######                        */
/*======================================================================================*/

/*======================================================================================*/
/*                        ####### TESTS DEFINITIONS #######                             */
/*======================================================================================*/
TEST_SETUP(FIFO)
{

}

TEST_TEAR_DOWN(FIFO)
{

}

TEST(FIFO, FIFO_should_PushAndPopItemsProperly)
{
  enum {ITEM_SIZE = 4};
  enum {ITEM_NUMBER = 5};

  uint32_t item1 = 0xABCDEFAC;
  uint32_t item2 = 0xABCDEFDD;
  uint32_t item3 = 0xAACC;
  uint32_t item4 = 0x00;
  uint32_t item5 = 0xFFFFFFFF;
  uint32_t poppedItem = 0;

  FIFO_Create(myFifo, ITEM_SIZE, ITEM_NUMBER);

  FIFO_PushItem(&myFifo, (void*)&item1);
  FIFO_PushItem(&myFifo, (void*)&item2);
  FIFO_PushItem(&myFifo, (void*)&item3);
  FIFO_PushItem(&myFifo, (void*)&item4);
  FIFO_PushItem(&myFifo, (void*)&item5);

  FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_HEX32(item1, poppedItem);
  FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item2, poppedItem);
  FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item3, poppedItem);
  FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item4, poppedItem);
  FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item5, poppedItem);
}



/**
 * @}
 */
