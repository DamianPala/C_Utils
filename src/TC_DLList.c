/*=======================================================================================*
 * @file    TC_DLList.c
 * @author  Damian Pala
 * @date    05-07-2017
 * @brief   This file contains unit tests for DLList module.
 *======================================================================================*/

/**
 * @addtogroup TC_DLList.
 * @{
 * @brief Unit tests implementation.
 */

/*======================================================================================*/
/*                       ####### PREPROCESSOR DIRECTIVES #######                        */
/*======================================================================================*/
/*---------------------- INCLUDE DIRECTIVES FOR STANDARD HEADERS -----------------------*/

/*----------------------- INCLUDE DIRECTIVES FOR OTHER HEADERS -------------------------*/
#define UNIT_TEST

#include "unity.h"
#include "unity_fixture.h"

#include "DLList.c"

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
 * @brief   TC_DLList Test Group.
 */
TEST_GROUP(TC_DLList);

static DLList_Iface_T ListIface =
{
  .MemAlloc = malloc,
  .MemFree = free,
};
static DLList_T *List;

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
TEST_SETUP(TC_DLList)
{
  List = DLList_CreateList(&ListIface);
}

/**
 * @brief   Tear Down Test Environment.
 */
TEST_TEAR_DOWN(TC_DLList)
{
  DLList_DestroyList(List);
}

TEST(TC_DLList, TC_DLList_should_PushItemBackProperly)
{
  uint32_t itemToPush = 0xAABBCCDD;
  uint32_t *itemToGet = NULL;
  size_t itemSize;
  bool retVal;

  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), (void**)&itemToGet);
  TEST_ASSERT_TRUE(retVal);
  retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize);
  TEST_ASSERT_TRUE(retVal);

  TEST_ASSERT_EQUAL_HEX32(itemToPush, *itemToGet);
  TEST_ASSERT_EQUAL_HEX8(sizeof(itemToPush), itemSize);

  DLList_PopBack(List);
  free(itemToGet);
}

TEST(TC_DLList, TC_DLList_should_ReturnFalseIfPopAndGetEmpty)
{
  uint32_t itemToPush = 0xAABBCCDD;
  uint32_t *itemToGet = NULL;
  size_t itemSize;
  bool retVal;

  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), (void**)&itemToGet);
  TEST_ASSERT_TRUE(retVal);
  retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize);
  TEST_ASSERT_TRUE(retVal);

  TEST_ASSERT_EQUAL_HEX32(itemToPush, *itemToGet);
  TEST_ASSERT_EQUAL_HEX8(sizeof(itemToPush), itemSize);

  DLList_PopBack(List);
  free(itemToGet);

  retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize);
  TEST_ASSERT_FALSE(retVal);
  retVal = DLList_PopBack(List);
  TEST_ASSERT_FALSE(retVal);
}

TEST(TC_DLList, TC_DLList_should_PushBackAndGetLargeNumberOfItemProperly)
{
  uint32_t itemToPush;
  uint32_t *itemToGet = NULL;
  size_t itemSize;
  bool retVal;
  const uint32_t iterations = UINT16_MAX;

  for (uint32_t i = 0; i < iterations; i++)
  {
    itemToPush = i;
    retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), (void**)&itemToGet);
    TEST_ASSERT_TRUE(retVal);
  }

  for (uint32_t i = iterations; i > 0; i--)
  {
    retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize);
    TEST_ASSERT_TRUE(retVal);
    TEST_ASSERT_EQUAL_HEX32(i - 1, *itemToGet);
    TEST_ASSERT_EQUAL_HEX8(sizeof(itemToPush), itemSize);
    retVal = DLList_PopBack(List);
    TEST_ASSERT_TRUE(retVal);
    free(itemToGet);
  }

  retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize);
  TEST_ASSERT_FALSE(retVal);
  retVal = DLList_PopBack(List);
  TEST_ASSERT_FALSE(retVal);
}

TEST(TC_DLList, TC_DLList_should_PopByKeyProperly)
{
  uint32_t itemToPush;
  uint32_t *itemToGet = NULL;
  size_t itemSize;
  bool retVal;
  const uint32_t items = 10000;

  for (uint32_t i = 0; i < items; i++)
  {
    itemToPush = i;
    retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), (void**)&itemToGet);
    TEST_ASSERT_TRUE(retVal);
  }

  for (uint32_t i = items; i > 0; i--)
  {
    retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize);
    TEST_ASSERT_TRUE(retVal);
    retVal = DLList_PopByItem(List, itemToGet);
    TEST_ASSERT_TRUE(retVal);
    free(itemToGet);
  }
}

TEST(TC_DLList, TC_DLList_should_PopByKeyProperlyVarious)
{
  uint32_t itemToPush;
  uint32_t *itemToGet[5];
  size_t itemSize;
  bool retVal;

  itemToPush = 1;
  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), (void**)&(itemToGet[0]));
  TEST_ASSERT_TRUE(retVal);
  itemToPush = 2;
  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), (void**)&(itemToGet[1]));
  TEST_ASSERT_TRUE(retVal);
  itemToPush = 3;
  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), (void**)&(itemToGet[2]));
  TEST_ASSERT_TRUE(retVal);
  itemToPush = 4;
  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), (void**)&(itemToGet[3]));
  TEST_ASSERT_TRUE(retVal);
  itemToPush = 5;
  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), (void**)&(itemToGet[4]));
  TEST_ASSERT_TRUE(retVal);

  TEST_ASSERT_TRUE(retVal);
  free(itemToGet[0]);
  retVal = DLList_PopByItem(List, itemToGet[0]);
  TEST_ASSERT_TRUE(retVal);
  TEST_ASSERT_TRUE(retVal);
  free(itemToGet[1]);
  retVal = DLList_PopByItem(List, itemToGet[1]);
  TEST_ASSERT_TRUE(retVal);
  TEST_ASSERT_TRUE(retVal);
  free(itemToGet[3]);
  retVal = DLList_PopByItem(List, itemToGet[3]);
  TEST_ASSERT_TRUE(retVal);

  retVal = DLList_GetBack(List, (void**)&(itemToGet[0]), &itemSize);
  TEST_ASSERT_TRUE(retVal);
  TEST_ASSERT_EQUAL_HEX32(5, *itemToGet[0]);
  TEST_ASSERT_EQUAL_HEX8(sizeof(itemToPush), itemSize);
  retVal = DLList_PopBack(List);
  TEST_ASSERT_TRUE(retVal);
  free(itemToGet[0]);

  retVal = DLList_GetBack(List, (void**)&(itemToGet[0]), &itemSize);
  TEST_ASSERT_TRUE(retVal);
  TEST_ASSERT_EQUAL_HEX32(3, *itemToGet[0]);
  TEST_ASSERT_EQUAL_HEX8(sizeof(itemToPush), itemSize);
  retVal = DLList_PopBack(List);
  TEST_ASSERT_TRUE(retVal);
  free(itemToGet[0]);
}

TEST(TC_DLList, TC_DLList_should_PushBigItemsProperly)
{
  uint32_t itemToPush[100];
  uint32_t *itemToGet = NULL;
  size_t itemSize;
  bool retVal;
  const uint32_t items = 1000;

  for (uint32_t i = 0; i < items; i++)
  {
    itemToPush[99] = i;
    retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), (void**)&itemToGet);
    TEST_ASSERT_TRUE(retVal);
  }

  for (uint32_t i = items; i > 0; i--)
  {
    retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize);
    TEST_ASSERT_TRUE(retVal);
    TEST_ASSERT_EQUAL_HEX32(i - 1, itemToGet[99]);
    TEST_ASSERT_EQUAL_HEX8(sizeof(itemToPush), itemSize);
    retVal = DLList_PopBack(List);
    TEST_ASSERT_TRUE(retVal);
    free(itemToGet);
  }

  retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize);
  TEST_ASSERT_FALSE(retVal);
  retVal = DLList_PopBack(List);
  TEST_ASSERT_FALSE(retVal);
}

TEST(TC_DLList, TC_DLList_should_TraverseForwardProperly)
{
  uint32_t itemToPush;
  uint32_t *itemToGet = NULL;
  size_t itemSize;
  bool retVal;
  const uint32_t items = 1000;

  for (uint32_t i = 0; i < items; i++)
  {
    itemToPush = i;
    retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), (void**)&itemToGet);
    TEST_ASSERT_TRUE(retVal);
  }

  DLList_StartTraverse(List);
  for (uint32_t i = 0; i < items; i++)
  {
    retVal = DLList_GetNext(List, (void**)&itemToGet, &itemSize);
    TEST_ASSERT_TRUE(retVal);
    TEST_ASSERT_EQUAL_HEX32(i, *itemToGet);
    TEST_ASSERT_EQUAL_HEX8(sizeof(itemToPush), itemSize);
  }

  for (uint32_t i = 0; i < items; i++)
  {
    retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize);
    TEST_ASSERT_TRUE(retVal);
    retVal = DLList_PopBack(List);
    TEST_ASSERT_TRUE(retVal);
    free(itemToGet);
  }

  retVal = DLList_GetNext(List, (void**)&itemToGet, &itemSize);
  TEST_ASSERT_FALSE(retVal);
  retVal = DLList_PopBack(List);
  TEST_ASSERT_FALSE(retVal);
}

TEST(TC_DLList, TC_DLList_should_TraverseFromGivenItem)
{
  uint32_t itemToPush;
  uint32_t *itemToGet[5];
  size_t itemSize;
  bool retVal;

  itemToPush = 1;
  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), (void**)&(itemToGet[0]));
  TEST_ASSERT_TRUE(retVal);
  itemToPush = 2;
  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), (void**)&(itemToGet[1]));
  TEST_ASSERT_TRUE(retVal);
  itemToPush = 3;
  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), (void**)&(itemToGet[2]));
  TEST_ASSERT_TRUE(retVal);
  itemToPush = 4;
  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), (void**)&(itemToGet[3]));
  TEST_ASSERT_TRUE(retVal);
  itemToPush = 5;
  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), (void**)&(itemToGet[4]));
  TEST_ASSERT_TRUE(retVal);

  retVal = DLList_StartTraverseWithGivenItem(List, itemToGet[2]);
  TEST_ASSERT_TRUE(retVal);

  retVal = DLList_GetNext(List, (void**)&itemToGet, &itemSize);
  TEST_ASSERT_TRUE(retVal);
  TEST_ASSERT_EQUAL_HEX32(3, *itemToGet[2]);
  TEST_ASSERT_EQUAL_HEX8(sizeof(itemToPush), itemSize);

  retVal = DLList_GetNext(List, (void**)&itemToGet, &itemSize);
  TEST_ASSERT_TRUE(retVal);
  TEST_ASSERT_EQUAL_HEX32(4, *itemToGet[3]);
  TEST_ASSERT_EQUAL_HEX8(sizeof(itemToPush), itemSize);

  retVal = DLList_GetNext(List, (void**)&itemToGet, &itemSize);
  TEST_ASSERT_TRUE(retVal);
  TEST_ASSERT_EQUAL_HEX32(5, *itemToGet[4]);
  TEST_ASSERT_EQUAL_HEX8(sizeof(itemToPush), itemSize);

  retVal = DLList_GetNext(List, (void**)&itemToGet, &itemSize);
  TEST_ASSERT_FALSE(retVal);

  for (uint32_t i = 0; i < 5; i++)
  {
    retVal = DLList_GetBack(List, (void**)&(itemToGet[0]), &itemSize);
    TEST_ASSERT_TRUE(retVal);
    retVal = DLList_PopBack(List);
    TEST_ASSERT_TRUE(retVal);
    free(itemToGet[0]);
  }
}

TEST(TC_DLList, TC_DLList_should_ClearProperly)
{
  uint32_t itemToPush[100];
  uint32_t *itemToGet = NULL;
  size_t itemSize = 0;
  bool retVal = false;
  const uint32_t items = 1000;

  for (uint32_t i = 0; i < items; i++)
  {
    itemToPush[99] = i;
    retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), NULL);
    TEST_ASSERT_TRUE(retVal);
  }

  DLList_Clear(List);

  retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize);
  TEST_ASSERT_FALSE(retVal);
  retVal = DLList_PopBack(List);
  TEST_ASSERT_FALSE(retVal);
}

// TODO: add test when list is empty and pop, get

/**
 * @} end of group TC_DLList
 */
