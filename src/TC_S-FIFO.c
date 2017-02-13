/*=======================================================================================*
 * @file    TC_S-FIFO.c
 * @author  Damian Pala
 * @date    12-02-2017
 * @brief   This file contains unit tests for S-FIFO module.
 *======================================================================================*/

/**
 * @addtogroup TC_S-FIFO Static FIFO Queue unit tests
 * @{
 * @brief Unit tests implementation.
 */

/*======================================================================================*/
/*                       ####### PREPROCESSOR DIRECTIVES #######                        */
/*======================================================================================*/
/*---------------------- INCLUDE DIRECTIVES FOR STANDARD HEADERS -----------------------*/

/*----------------------- INCLUDE DIRECTIVES FOR OTHER HEADERS -------------------------*/
#include "unity.h"
#include "unity_fixture.h"

#include "S-FIFO.c"

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
/**
 * @brief   FIFO Test Group.
 */
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
/**
 * @brief   Setup Test Environment.
 */
TEST_SETUP(FIFO)
{

}

/**
 * @brief   Tear Down Test Environment.
 */
TEST_TEAR_DOWN(FIFO)
{

}

TEST(FIFO, FIFO_should_PushAndPopAndCountItemsProperlyAndReturnFalseWhenFullOrEmpty)
{
  enum {ITEM_SIZE = 4};
  enum {ITEM_NUMBER = 5};
  bool pushRet, popRet;

  uint32_t item1 = ('1' << 24) | ('1' << 16) | ('1' << 8) | ('1' << 0);
  uint32_t item2 = ('2' << 24) | ('2' << 16) | ('2' << 8) | ('2' << 0);
  uint32_t item3 = ('3' << 24) | ('3' << 16) | ('3' << 8) | ('3' << 0);
  uint32_t item4 = ('4' << 24) | ('4' << 16) | ('4' << 8) | ('4' << 0);
  uint32_t item5 = ('5' << 24) | ('5' << 16) | ('5' << 8) | ('5' << 0);
  uint32_t poppedItem = 0;

  SFIFO_Create(myFifo, ITEM_SIZE, ITEM_NUMBER);
  SFIFO_OverwriteLastItems(myFifo, false);

  TEST_ASSERT_TRUE(SFIFO_IsEmpty(myFifo));
  TEST_ASSERT_FALSE(SFIFO_IsFull(myFifo));
  TEST_ASSERT_EQUAL_UINT16(0, SFIFO_GetItemsInFifo(myFifo));

  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_FALSE(popRet);

  TEST_ASSERT_TRUE(SFIFO_IsEmpty(myFifo));
  TEST_ASSERT_FALSE(SFIFO_IsFull(myFifo));
  TEST_ASSERT_EQUAL_UINT16(0, SFIFO_GetItemsInFifo(myFifo));

  pushRet = SFIFO_PushItem(myFifo, (void*)&item1);
  TEST_ASSERT_TRUE(pushRet);

  TEST_ASSERT_FALSE(SFIFO_IsEmpty(myFifo));
  TEST_ASSERT_FALSE(SFIFO_IsFull(myFifo));
  TEST_ASSERT_EQUAL_UINT16(1, SFIFO_GetItemsInFifo(myFifo));

  pushRet = SFIFO_PushItem(myFifo, (void*)&item2);
  TEST_ASSERT_TRUE(pushRet);
  pushRet = SFIFO_PushItem(myFifo, (void*)&item3);
  TEST_ASSERT_TRUE(pushRet);
  pushRet = SFIFO_PushItem(myFifo, (void*)&item4);
  TEST_ASSERT_TRUE(pushRet);
  pushRet = SFIFO_PushItem(myFifo, (void*)&item5);
  TEST_ASSERT_TRUE(pushRet);

  TEST_ASSERT_FALSE(SFIFO_IsEmpty(myFifo));
  TEST_ASSERT_TRUE(SFIFO_IsFull(myFifo));
  TEST_ASSERT_EQUAL_UINT16(ITEM_NUMBER, SFIFO_GetItemsInFifo(myFifo));

  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_HEX32(item1, poppedItem);

  TEST_ASSERT_FALSE(SFIFO_IsEmpty(myFifo));
  TEST_ASSERT_FALSE(SFIFO_IsFull(myFifo));
  TEST_ASSERT_EQUAL_UINT16(4, SFIFO_GetItemsInFifo(myFifo));

  TEST_ASSERT_TRUE(popRet);
  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item2, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item3, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item4, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item5, poppedItem);
  TEST_ASSERT_TRUE(popRet);

  TEST_ASSERT_TRUE(SFIFO_IsEmpty(myFifo));
  TEST_ASSERT_FALSE(SFIFO_IsFull(myFifo));
  TEST_ASSERT_EQUAL_UINT16(0, SFIFO_GetItemsInFifo(myFifo));

  pushRet = SFIFO_PushItem(myFifo, (void*)&item1);
  TEST_ASSERT_TRUE(pushRet);
  pushRet = SFIFO_PushItem(myFifo, (void*)&item2);
  TEST_ASSERT_TRUE(pushRet);
  pushRet = SFIFO_PushItem(myFifo, (void*)&item3);
  TEST_ASSERT_TRUE(pushRet);
  pushRet = SFIFO_PushItem(myFifo, (void*)&item4);
  TEST_ASSERT_TRUE(pushRet);
  pushRet = SFIFO_PushItem(myFifo, (void*)&item5);
  TEST_ASSERT_TRUE(pushRet);

  TEST_ASSERT_FALSE(SFIFO_IsEmpty(myFifo));
  TEST_ASSERT_TRUE(SFIFO_IsFull(myFifo));
  TEST_ASSERT_EQUAL_UINT16(ITEM_NUMBER, SFIFO_GetItemsInFifo(myFifo));

  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_HEX32(item1, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item2, poppedItem);
  TEST_ASSERT_TRUE(popRet);

  TEST_ASSERT_EQUAL_UINT16(3, SFIFO_GetItemsInFifo(myFifo));

  pushRet = SFIFO_PushItem(myFifo, (void*)&item4);
  TEST_ASSERT_TRUE(pushRet);
  pushRet = SFIFO_PushItem(myFifo, (void*)&item5);
  TEST_ASSERT_TRUE(pushRet);

  TEST_ASSERT_EQUAL_UINT16(ITEM_NUMBER, SFIFO_GetItemsInFifo(myFifo));

  pushRet = SFIFO_PushItem(myFifo, (void*)&item4);
  TEST_ASSERT_FALSE(pushRet);
  pushRet = SFIFO_PushItem(myFifo, (void*)&item4);
  TEST_ASSERT_FALSE(pushRet);

  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item3, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(4, SFIFO_GetItemsInFifo(myFifo));
  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item4, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(3, SFIFO_GetItemsInFifo(myFifo));
  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item5, poppedItem);
  TEST_ASSERT_TRUE(popRet);

  TEST_ASSERT_FALSE(SFIFO_IsEmpty(myFifo));
  TEST_ASSERT_FALSE(SFIFO_IsFull(myFifo));
  TEST_ASSERT_EQUAL_UINT16(2, SFIFO_GetItemsInFifo(myFifo));

  pushRet = SFIFO_PushItem(myFifo, (void*)&item4);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(3, SFIFO_GetItemsInFifo(myFifo));
  pushRet = SFIFO_PushItem(myFifo, (void*)&item5);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(4, SFIFO_GetItemsInFifo(myFifo));

  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_HEX32(item4, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(3, SFIFO_GetItemsInFifo(myFifo));
  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item5, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(2, SFIFO_GetItemsInFifo(myFifo));
  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_HEX32(item4, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(1, SFIFO_GetItemsInFifo(myFifo));
  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item5, poppedItem);
  TEST_ASSERT_TRUE(popRet);

  TEST_ASSERT_TRUE(SFIFO_IsEmpty(myFifo));
  TEST_ASSERT_FALSE(SFIFO_IsFull(myFifo));
  TEST_ASSERT_EQUAL_UINT16(0, SFIFO_GetItemsInFifo(myFifo));
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

  SFIFO_Create(myFifo, ITEM_SIZE, ITEM_NUMBER);
  SFIFO_OverwriteLastItems(myFifo, true);

  TEST_ASSERT_TRUE(SFIFO_IsEmpty(myFifo));
  TEST_ASSERT_FALSE(SFIFO_IsFull(myFifo));
  TEST_ASSERT_EQUAL_UINT16(0, SFIFO_GetItemsInFifo(myFifo));

  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_FALSE(popRet);

  TEST_ASSERT_TRUE(SFIFO_IsEmpty(myFifo));
  TEST_ASSERT_FALSE(SFIFO_IsFull(myFifo));
  TEST_ASSERT_EQUAL_UINT16(0, SFIFO_GetItemsInFifo(myFifo));

  pushRet = SFIFO_PushItem(myFifo, (void*)&item1);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(1, SFIFO_GetItemsInFifo(myFifo));
  pushRet = SFIFO_PushItem(myFifo, (void*)&item2);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(2, SFIFO_GetItemsInFifo(myFifo));
  pushRet = SFIFO_PushItem(myFifo, (void*)&item3);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(3, SFIFO_GetItemsInFifo(myFifo));
  pushRet = SFIFO_PushItem(myFifo, (void*)&item4);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(4, SFIFO_GetItemsInFifo(myFifo));
  pushRet = SFIFO_PushItem(myFifo, (void*)&item5);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, SFIFO_GetItemsInFifo(myFifo));
  pushRet = SFIFO_PushItem(myFifo, (void*)&item6);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, SFIFO_GetItemsInFifo(myFifo));
  pushRet = SFIFO_PushItem(myFifo, (void*)&item1);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, SFIFO_GetItemsInFifo(myFifo));
  pushRet = SFIFO_PushItem(myFifo, (void*)&item2);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, SFIFO_GetItemsInFifo(myFifo));
  pushRet = SFIFO_PushItem(myFifo, (void*)&item3);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, SFIFO_GetItemsInFifo(myFifo));
  pushRet = SFIFO_PushItem(myFifo, (void*)&item4);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, SFIFO_GetItemsInFifo(myFifo));
  pushRet = SFIFO_PushItem(myFifo, (void*)&item5);
  TEST_ASSERT_TRUE(pushRet);
  TEST_ASSERT_EQUAL_UINT16(5, SFIFO_GetItemsInFifo(myFifo));

  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_HEX32(item1, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(4, SFIFO_GetItemsInFifo(myFifo));
  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item2, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(3, SFIFO_GetItemsInFifo(myFifo));
  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item3, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(2, SFIFO_GetItemsInFifo(myFifo));
  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item4, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(1, SFIFO_GetItemsInFifo(myFifo));
  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_UINT32(item5, poppedItem);
  TEST_ASSERT_TRUE(popRet);
  TEST_ASSERT_EQUAL_UINT16(0, SFIFO_GetItemsInFifo(myFifo));

  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_FALSE(popRet);
  TEST_ASSERT_EQUAL_UINT16(0, SFIFO_GetItemsInFifo(myFifo));
}

TEST(FIFO, FIFO_should_OverwriteLastItemsWhenPushedMoreItemsThanFifoSizeIterationTest)
{
  enum {ITEM_SIZE = 4};
  enum {ITEM_NUMBER = 5};
  bool pushRet, popRet;
  uint32_t poppedItem = 0;
  uint32_t items[10] =
  {
      0x11111111,
      0x22222222,
      0x33333333,
      0x44444444,
      0x55555555,
      0x66666666,
      0x77777777,
      0x88888888,
      0x99999999,
      0xAAAAAAAA,
  };

  SFIFO_Create(myFifo, ITEM_SIZE, ITEM_NUMBER);
  SFIFO_OverwriteLastItems(myFifo, true);

  TEST_ASSERT_TRUE(SFIFO_IsEmpty(myFifo));
  TEST_ASSERT_FALSE(SFIFO_IsFull(myFifo));
  TEST_ASSERT_EQUAL_UINT16(0, SFIFO_GetItemsInFifo(myFifo));

  for (uint16_t m = 0; m < 1000; m++)
  {
    static uint8_t itemIterator = 0;

    for (uint16_t i = 0; i < 10; i++)
    {
      if (i < 5 && itemIterator < 5)
      {
        itemIterator++;
      }

      pushRet = SFIFO_PushItem(myFifo, (void*)&items[i]);
      TEST_ASSERT_TRUE(pushRet);
      TEST_ASSERT_EQUAL_UINT16(itemIterator, SFIFO_GetItemsInFifo(myFifo));
    }
  }

  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_EQUAL_HEX32(items[5], poppedItem);

  for (uint16_t m = 0; m < 1000; m++)
  {
    for (uint8_t i = 0; i < 10; i++)
    {
      pushRet = SFIFO_PushItem(myFifo, (void*)&items[9 - i]);
      TEST_ASSERT_TRUE(pushRet);
      TEST_ASSERT_EQUAL_UINT16(5, SFIFO_GetItemsInFifo(myFifo));
    }
  }

  for (uint8_t i = 0; i < ITEM_NUMBER; i++)
  {
    popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
    TEST_ASSERT_EQUAL_HEX32(items[4 - i], poppedItem);
    TEST_ASSERT_TRUE(popRet);
    TEST_ASSERT_EQUAL_UINT16(ITEM_NUMBER - i - 1, SFIFO_GetItemsInFifo(myFifo));
  }

  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_FALSE(popRet);
  TEST_ASSERT_EQUAL_UINT16(0, SFIFO_GetItemsInFifo(myFifo));
}

TEST(FIFO, FIFO_should_BeClearedProperly)
{
  enum {ITEM_SIZE = 4};
  enum {ITEM_NUMBER = 5};
  bool pushRet, popRet;
  uint32_t poppedItem = 0;
  uint32_t items[10] =
  {
      0x11111111,
      0x22222222,
      0x33333333,
      0x44444444,
      0x55555555,
      0x66666666,
      0x77777777,
      0x88888888,
      0x99999999,
      0xAAAAAAAA,
  };

  SFIFO_Create(myFifo, ITEM_SIZE, ITEM_NUMBER);
  SFIFO_OverwriteLastItems(myFifo, true);

  TEST_ASSERT_TRUE(SFIFO_IsEmpty(myFifo));
  TEST_ASSERT_FALSE(SFIFO_IsFull(myFifo));
  TEST_ASSERT_EQUAL_UINT16(0, SFIFO_GetItemsInFifo(myFifo));

  for (uint16_t m = 0; m < 1000; m++)
  {
    static uint8_t itemIterator = 0;
    for (uint8_t i = 0; i < 10; i++)
    {
      if (i < 5 && itemIterator < 5)
      {
        itemIterator++;
      }

      pushRet = SFIFO_PushItem(myFifo, (void*)&items[9 - i]);
      TEST_ASSERT_TRUE(pushRet);
      TEST_ASSERT_EQUAL_UINT16(itemIterator, SFIFO_GetItemsInFifo(myFifo));
    }
  }

  SFIFO_Clear(myFifo);

  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_FALSE(popRet);
  TEST_ASSERT_EQUAL_UINT16(0, SFIFO_GetItemsInFifo(myFifo));
}

TEST(FIFO, FIFO_should_WorkProperlyOnHugeItemNumber)
{
  enum {ITEM_SIZE = 4};
  enum {ITEM_NUMBER = 10000};
  bool pushRet, popRet;
  uint32_t poppedItem = 0;
  uint32_t item;

  SFIFO_Create(myFifo, ITEM_SIZE, ITEM_NUMBER);

  TEST_ASSERT_TRUE(SFIFO_IsEmpty(myFifo));
  TEST_ASSERT_FALSE(SFIFO_IsFull(myFifo));
  TEST_ASSERT_EQUAL_UINT16(0, SFIFO_GetItemsInFifo(myFifo));


  for (uint32_t itemCnt = 0; itemCnt < ITEM_NUMBER; itemCnt++)
  {
    item = itemCnt + 1;
    pushRet = SFIFO_PushItem(myFifo, (void*)&item);
    TEST_ASSERT_TRUE(pushRet);
    TEST_ASSERT_EQUAL_UINT16(itemCnt + 1, SFIFO_GetItemsInFifo(myFifo));
  }

  for (uint32_t itemCnt = 0; itemCnt < ITEM_NUMBER; itemCnt++)
  {
    popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
    TEST_ASSERT_EQUAL_UINT32(itemCnt + 1, poppedItem);
    TEST_ASSERT_TRUE(popRet);
    TEST_ASSERT_EQUAL_UINT16(ITEM_NUMBER - itemCnt - 1, SFIFO_GetItemsInFifo(myFifo));
  }

  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_FALSE(popRet);
  TEST_ASSERT_EQUAL_UINT16(0, SFIFO_GetItemsInFifo(myFifo));
}

TEST(FIFO, FIFO_should_WorkProperlyOnHugeItemSize)
{
  enum {ITEM_SIZE = 300};
  enum {ITEM_NUMBER = 100};
  bool pushRet, popRet;
  char poppedItem[1024];
  char itemBase[] = "fjldksajflasjflajflkajfkdjfafadfjkajfkldsajfkjasdfjasdkfjlkiogioejgk"
      "jgklafjdkjgiafodjgfkldjgaogjak;gjiaogjgjiwjglfdsjgidofajwiojawiodjafjdiwfajdjfaklc"
      "vzkxjflwahdafadsioqjrioewmjzlxnvjnruiaeipojioxjvklxnmvznvzjkhnfiodhiaohfafjofkozmvcl"
      "k;ndfjkoaooipjfopajmzvipojioajdfhdaoiphjjpoajfdsojvziopjjjjjjjjjjj";

  SFIFO_Create(myFifo, ITEM_SIZE, ITEM_NUMBER);

  TEST_ASSERT_TRUE(SFIFO_IsEmpty(myFifo));
  TEST_ASSERT_FALSE(SFIFO_IsFull(myFifo));
  TEST_ASSERT_EQUAL_UINT16(0, SFIFO_GetItemsInFifo(myFifo));


  for (uint32_t itemCnt = 0; itemCnt < ITEM_NUMBER; itemCnt++)
  {
    itemBase[123]++;
    pushRet = SFIFO_PushItem(myFifo, (void*)&itemBase);
    TEST_ASSERT_TRUE(pushRet);
    TEST_ASSERT_EQUAL_UINT16(itemCnt + 1, SFIFO_GetItemsInFifo(myFifo));
  }

  for (uint32_t itemCnt = 0; itemCnt < ITEM_NUMBER; itemCnt++)
  {
    itemBase[123]--;
  }

  for (uint32_t itemCnt = 0; itemCnt < ITEM_NUMBER; itemCnt++)
  {
    itemBase[123]++;
    popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
    TEST_ASSERT_EQUAL_STRING(itemBase, poppedItem);
    TEST_ASSERT_TRUE(popRet);
    TEST_ASSERT_EQUAL_UINT16(ITEM_NUMBER - itemCnt - 1, SFIFO_GetItemsInFifo(myFifo));
  }

  popRet = SFIFO_PopItem(myFifo, (void*)&poppedItem);
  TEST_ASSERT_FALSE(popRet);
  TEST_ASSERT_EQUAL_UINT16(0, SFIFO_GetItemsInFifo(myFifo));
}


/**
 * @} end of group TC_S-FIFO Static FIFO Queue unit tests
 */
