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

TEST(FIFO, FIFO_should_PushAndPopAndCountItemsProperlyAndReturnFalseWhenFullOrEmpty)
{
  enum {ITEM_SIZE = 4};
  enum {ITEM_NUMBER = 5};
  bool pushRet, popRet;

  uint32_t item1 = 0xABCDEFAC;
  uint32_t item2 = 0xABCDEFDD;
  uint32_t item3 = 0xAACC;
  uint32_t item4 = 0x00;
  uint32_t item5 = 0xFFFFFFFF;
  uint32_t poppedItem = 0;

  FIFO_Create(myFifo, ITEM_SIZE, ITEM_NUMBER);

  TEST_ASSERT_TRUE(FIFO_IsEmpty(&myFifo));
  TEST_ASSERT_FALSE(FIFO_IsFull(&myFifo));
  TEST_ASSERT_EQUAL_UINT16(0, FIFO_ItemsInFifo(&myFifo));

  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_FALSE(popRet);

  TEST_ASSERT_TRUE(FIFO_IsEmpty(&myFifo));
  TEST_ASSERT_FALSE(FIFO_IsFull(&myFifo));
  TEST_ASSERT_EQUAL_UINT16(0, FIFO_ItemsInFifo(&myFifo));

  pushRet = FIFO_PushItem(&myFifo, (void*)&item1);
  TEST_ASSERT_TRUE(pushRet);

  TEST_ASSERT_FALSE(FIFO_IsEmpty(&myFifo));
  TEST_ASSERT_FALSE(FIFO_IsFull(&myFifo));
  TEST_ASSERT_EQUAL_UINT16(1, FIFO_ItemsInFifo(&myFifo));

  pushRet = FIFO_PushItem(&myFifo, (void*)&item2);
  TEST_ASSERT_TRUE(pushRet);
  pushRet = FIFO_PushItem(&myFifo, (void*)&item3);
  TEST_ASSERT_TRUE(pushRet);
  pushRet = FIFO_PushItem(&myFifo, (void*)&item4);
  TEST_ASSERT_TRUE(pushRet);
  pushRet = FIFO_PushItem(&myFifo, (void*)&item5);
  TEST_ASSERT_TRUE(pushRet);

  TEST_ASSERT_FALSE(FIFO_IsEmpty(&myFifo));
  TEST_ASSERT_TRUE(FIFO_IsFull(&myFifo));
  TEST_ASSERT_EQUAL_UINT16(ITEM_NUMBER, FIFO_ItemsInFifo(&myFifo));

  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_HEX32(item1, poppedItem);

  TEST_ASSERT_FALSE(FIFO_IsEmpty(&myFifo));
  TEST_ASSERT_FALSE(FIFO_IsFull(&myFifo));
  TEST_ASSERT_EQUAL_UINT16(4, FIFO_ItemsInFifo(&myFifo));

  TEST_ASSERT_TRUE(popRet);
  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item2, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item3, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item4, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item5, poppedItem);
  TEST_ASSERT_TRUE(popRet);

  TEST_ASSERT_TRUE(FIFO_IsEmpty(&myFifo));
  TEST_ASSERT_FALSE(FIFO_IsFull(&myFifo));
  TEST_ASSERT_EQUAL_UINT16(0, FIFO_ItemsInFifo(&myFifo));

  pushRet = FIFO_PushItem(&myFifo, (void*)&item1);
  TEST_ASSERT_TRUE(pushRet);
  pushRet = FIFO_PushItem(&myFifo, (void*)&item2);
  TEST_ASSERT_TRUE(pushRet);
  pushRet = FIFO_PushItem(&myFifo, (void*)&item3);
  TEST_ASSERT_TRUE(pushRet);
  pushRet = FIFO_PushItem(&myFifo, (void*)&item4);
  TEST_ASSERT_TRUE(pushRet);
  pushRet = FIFO_PushItem(&myFifo, (void*)&item5);
  TEST_ASSERT_TRUE(pushRet);

  TEST_ASSERT_FALSE(FIFO_IsEmpty(&myFifo));
  TEST_ASSERT_TRUE(FIFO_IsFull(&myFifo));
  TEST_ASSERT_EQUAL_UINT16(ITEM_NUMBER, FIFO_ItemsInFifo(&myFifo));

  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_HEX32(item1, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item2, poppedItem);
  TEST_ASSERT_TRUE(popRet);

  TEST_ASSERT_EQUAL_UINT16(3, FIFO_ItemsInFifo(&myFifo));

  pushRet = FIFO_PushItem(&myFifo, (void*)&item4);
  TEST_ASSERT_TRUE(pushRet);
  pushRet = FIFO_PushItem(&myFifo, (void*)&item5);
  TEST_ASSERT_TRUE(pushRet);

  TEST_ASSERT_EQUAL_UINT16(ITEM_NUMBER, FIFO_ItemsInFifo(&myFifo));

  pushRet = FIFO_PushItem(&myFifo, (void*)&item4);
  TEST_ASSERT_FALSE(pushRet);
  pushRet = FIFO_PushItem(&myFifo, (void*)&item4);
  TEST_ASSERT_FALSE(pushRet);

  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item3, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(4, FIFO_ItemsInFifo(&myFifo));
  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item4, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(3, FIFO_ItemsInFifo(&myFifo));
  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item5, poppedItem);
  TEST_ASSERT_TRUE(popRet);

  TEST_ASSERT_FALSE(FIFO_IsEmpty(&myFifo));
  TEST_ASSERT_FALSE(FIFO_IsFull(&myFifo));
  TEST_ASSERT_EQUAL_UINT16(2, FIFO_ItemsInFifo(&myFifo));

  pushRet = FIFO_PushItem(&myFifo, (void*)&item4);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(3, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item5);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(4, FIFO_ItemsInFifo(&myFifo));

  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_HEX32(item4, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(3, FIFO_ItemsInFifo(&myFifo));
  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item5, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(2, FIFO_ItemsInFifo(&myFifo));
  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_HEX32(item4, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(1, FIFO_ItemsInFifo(&myFifo));
  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item5, poppedItem);
  TEST_ASSERT_TRUE(popRet);

  TEST_ASSERT_TRUE(FIFO_IsEmpty(&myFifo));
  TEST_ASSERT_FALSE(FIFO_IsFull(&myFifo));
  TEST_ASSERT_EQUAL_UINT16(0, FIFO_ItemsInFifo(&myFifo));
}

TEST(FIFO, FIFO_should_OverwriteLastItemsWhenPushedMoreItemsThanFifoSize)
{
  enum {ITEM_SIZE = 4};
  enum {ITEM_NUMBER = 5};
  bool pushRet, popRet;

  uint32_t item1 = 0xABCDEFAC;
  uint32_t item2 = 0xABCDEFDD;
  uint32_t item3 = 0xAACC;
  uint32_t item4 = 0x00;
  uint32_t item5 = 0xFFFFFFFF;
  uint32_t item6 = 0xFFAAFFFF;
  uint32_t poppedItem = 0;

  FIFO_Create(myFifo, ITEM_SIZE, ITEM_NUMBER);
  FIFO_OverwriteLastItems(&myFifo, true);

  TEST_ASSERT_TRUE(FIFO_IsEmpty(&myFifo));
  TEST_ASSERT_FALSE(FIFO_IsFull(&myFifo));
  TEST_ASSERT_EQUAL_UINT16(0, FIFO_ItemsInFifo(&myFifo));

  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_FALSE(popRet);

  TEST_ASSERT_TRUE(FIFO_IsEmpty(&myFifo));
  TEST_ASSERT_FALSE(FIFO_IsFull(&myFifo));
  TEST_ASSERT_EQUAL_UINT16(0, FIFO_ItemsInFifo(&myFifo));

  pushRet = FIFO_PushItem(&myFifo, (void*)&item1);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(1, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item2);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(2, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item3);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(3, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item4);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(4, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item5);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item6);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item1);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item2);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item3);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item4);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item5);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, FIFO_ItemsInFifo(&myFifo));

  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_HEX32(item1, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(4, FIFO_ItemsInFifo(&myFifo));
  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item2, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(3, FIFO_ItemsInFifo(&myFifo));
  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item3, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(2, FIFO_ItemsInFifo(&myFifo));
  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item4, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(1, FIFO_ItemsInFifo(&myFifo));
  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item5, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(0, FIFO_ItemsInFifo(&myFifo));

  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_FALSE(popRet);
  TEST_ASSERT_EQUAL_UINT16(0, FIFO_ItemsInFifo(&myFifo));
}

TEST(FIFO, FIFO_should_OverwriteLastItemsWhenPushedMoreItemsThanFifoSizeIterationTest)
{
  enum {ITEM_SIZE = 4};
  enum {ITEM_NUMBER = 5};
  bool pushRet, popRet;

  uint32_t item1 = 0xABCDEFAC;
  uint32_t item2 = 0xABCDEFDD;
  uint32_t item3 = 0xAACC;
  uint32_t item4 = 0x00;
  uint32_t item5 = 0xFFFFFFFF;
  uint32_t item6 = 0xFFAAFFFF;
  uint32_t poppedItem = 0;

  FIFO_Create(myFifo, ITEM_SIZE, ITEM_NUMBER);
  FIFO_OverwriteLastItems(&myFifo, true);

  TEST_ASSERT_TRUE(FIFO_IsEmpty(&myFifo));
  TEST_ASSERT_FALSE(FIFO_IsFull(&myFifo));
  TEST_ASSERT_EQUAL_UINT16(0, FIFO_ItemsInFifo(&myFifo));

  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_FALSE(popRet);

  TEST_ASSERT_TRUE(FIFO_IsEmpty(&myFifo));
  TEST_ASSERT_FALSE(FIFO_IsFull(&myFifo));
  TEST_ASSERT_EQUAL_UINT16(0, FIFO_ItemsInFifo(&myFifo));

  pushRet = FIFO_PushItem(&myFifo, (void*)&item1);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(1, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item2);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(2, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item3);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(3, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item4);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(4, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item5);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item6);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item1);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item2);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item3);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item4);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, FIFO_ItemsInFifo(&myFifo));
  pushRet = FIFO_PushItem(&myFifo, (void*)&item5);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, FIFO_ItemsInFifo(&myFifo));

  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_HEX32(item1, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(4, FIFO_ItemsInFifo(&myFifo));
  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item2, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(3, FIFO_ItemsInFifo(&myFifo));
  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item3, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(2, FIFO_ItemsInFifo(&myFifo));
  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item4, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(1, FIFO_ItemsInFifo(&myFifo));
  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item5, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(0, FIFO_ItemsInFifo(&myFifo));

  popRet = FIFO_PopItem(&myFifo, (void*)&poppedItem);
  TEST_ASSERT_FALSE(popRet);
  TEST_ASSERT_EQUAL_UINT16(0, FIFO_ItemsInFifo(&myFifo));
}



/**
 * @}
 */
