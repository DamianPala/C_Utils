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
  List = DLList_CreateList();
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
  uint32_t pushKey, getKey;
  size_t itemSize;
  bool retVal;

  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), &pushKey);
  TEST_ASSERT_TRUE(retVal);
  retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize, &getKey);
  TEST_ASSERT_TRUE(retVal);

  TEST_ASSERT_EQUAL_HEX32(itemToPush, *itemToGet);
  TEST_ASSERT_EQUAL_HEX8(sizeof(itemToPush), itemSize);
  TEST_ASSERT_EQUAL_HEX16(pushKey, getKey);

  DLList_PopBack(List);
  free(itemToGet);
}

TEST(TC_DLList, TC_DLList_should_ReturnFalseIfPopAndGetEmpty)
{
  uint32_t itemToPush = 0xAABBCCDD;
  uint32_t *itemToGet = NULL;
  uint32_t pushKey, getKey;
  size_t itemSize;
  bool retVal;

  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), &pushKey);
  TEST_ASSERT_TRUE(retVal);
  retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize, &getKey);
  TEST_ASSERT_TRUE(retVal);

  TEST_ASSERT_EQUAL_HEX32(itemToPush, *itemToGet);
  TEST_ASSERT_EQUAL_HEX8(sizeof(itemToPush), itemSize);
  TEST_ASSERT_EQUAL_HEX16(pushKey, getKey);

  DLList_PopBack(List);
  free(itemToGet);

  retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize, &getKey);
  TEST_ASSERT_FALSE(retVal);
  retVal = DLList_PopBack(List);
  TEST_ASSERT_FALSE(retVal);
}

TEST(TC_DLList, TC_DLList_should_PushBackAndGetLargeNumberOfItemProperly)
{
  uint32_t itemToPush;
  uint32_t *itemToGet = NULL;
  uint32_t pushKey, getKey;
  size_t itemSize;
  bool retVal;
  const uint32_t iterations = UINT16_MAX;

  for (uint32_t i = 0; i < iterations; i++)
  {
    itemToPush = i;
    retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), &pushKey);
    TEST_ASSERT_TRUE(retVal);
    TEST_ASSERT_EQUAL_HEX16(i, pushKey);
  }

  for (uint32_t i = iterations; i > 0; i--)
  {
    retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize, &getKey);
    TEST_ASSERT_TRUE(retVal);
    TEST_ASSERT_EQUAL_HEX32(i - 1, *itemToGet);
    TEST_ASSERT_EQUAL_HEX16(i - 1, getKey);
    TEST_ASSERT_EQUAL_HEX8(sizeof(itemToPush), itemSize);
    retVal = DLList_PopBack(List);
    TEST_ASSERT_TRUE(retVal);
    free(itemToGet);
  }

  retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize, &getKey);
  TEST_ASSERT_FALSE(retVal);
  retVal = DLList_PopBack(List);
  TEST_ASSERT_FALSE(retVal);
}

TEST(TC_DLList, TC_DLList_should_GetByKeyAndPopByKeyProperly)
{
  uint32_t itemToPush;
  uint32_t *itemToGet = NULL;
  uint32_t pushKey;
  size_t itemSize;
  bool retVal;
  const uint32_t items = 10000;

  for (uint32_t i = 0; i < items; i++)
  {
    itemToPush = i;
    retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), &pushKey);
    TEST_ASSERT_TRUE(retVal);
    TEST_ASSERT_EQUAL_HEX16(i, pushKey);
  }

  for (uint32_t i = items; i > 0; i--)
  {
    retVal = DLList_GetByKey(List, i - 1, (void**)&itemToGet, &itemSize);
    TEST_ASSERT_TRUE(retVal);
    TEST_ASSERT_EQUAL_HEX32(i - 1, *itemToGet);
    TEST_ASSERT_EQUAL_HEX8(sizeof(itemToPush), itemSize);
  }

  for (uint32_t i = items; i > 0; i--)
  {
    retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize, NULL);
    TEST_ASSERT_TRUE(retVal);
    retVal = DLList_PopByKey(List, i - 1);
    TEST_ASSERT_TRUE(retVal);
    free(itemToGet);
  }
}

TEST(TC_DLList, TC_DLList_should_PopByKeyProperlyVarious)
{
  uint32_t itemToPush;
  uint32_t *itemToGet = NULL;
  uint32_t pushKey, getKey;
  size_t itemSize;
  bool retVal;

  itemToPush = 1;
  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), &pushKey);
  TEST_ASSERT_TRUE(retVal);
  itemToPush = 2;
  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), &pushKey);
  TEST_ASSERT_TRUE(retVal);
  itemToPush = 3;
  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), &pushKey);
  TEST_ASSERT_TRUE(retVal);
  itemToPush = 4;
  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), &pushKey);
  TEST_ASSERT_TRUE(retVal);
  itemToPush = 5;
  retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), &pushKey);
  TEST_ASSERT_TRUE(retVal);

  retVal = DLList_GetByKey(List, 0, (void**)&itemToGet, &itemSize);
  TEST_ASSERT_TRUE(retVal);
  free(itemToGet);
  retVal = DLList_PopByKey(List, 0);
  TEST_ASSERT_TRUE(retVal);
  retVal = DLList_GetByKey(List, 1, (void**)&itemToGet, &itemSize);
  TEST_ASSERT_TRUE(retVal);
  free(itemToGet);
  retVal = DLList_PopByKey(List, 1);
  TEST_ASSERT_TRUE(retVal);
  retVal = DLList_GetByKey(List, 3, (void**)&itemToGet, &itemSize);
  TEST_ASSERT_TRUE(retVal);
  free(itemToGet);
  retVal = DLList_PopByKey(List, 3);
  TEST_ASSERT_TRUE(retVal);

  retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize, &getKey);
  TEST_ASSERT_TRUE(retVal);
  TEST_ASSERT_EQUAL_HEX32(5, *itemToGet);
  TEST_ASSERT_EQUAL_HEX8(sizeof(itemToPush), itemSize);
  TEST_ASSERT_EQUAL_HEX16(4, getKey);
  retVal = DLList_PopBack(List);
  TEST_ASSERT_TRUE(retVal);
  free(itemToGet);

  retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize, &getKey);
  TEST_ASSERT_TRUE(retVal);
  TEST_ASSERT_EQUAL_HEX32(3, *itemToGet);
  TEST_ASSERT_EQUAL_HEX8(sizeof(itemToPush), itemSize);
  TEST_ASSERT_EQUAL_HEX16(2, getKey);
  retVal = DLList_PopBack(List);
  TEST_ASSERT_TRUE(retVal);
  free(itemToGet);
}

TEST(TC_DLList, TC_DLList_should_PushBigItemsProperly)
{
  uint32_t itemToPush[100];
  uint32_t *itemToGet = NULL;
  uint32_t pushKey, getKey;
  size_t itemSize;
  bool retVal;
  const uint32_t items = 1000;

  for (uint32_t i = 0; i < items; i++)
  {
    itemToPush[99] = i;
    retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), &pushKey);
    TEST_ASSERT_TRUE(retVal);
    TEST_ASSERT_EQUAL_HEX16(i, pushKey);
  }

  for (uint32_t i = items; i > 0; i--)
  {
    retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize, &getKey);
    TEST_ASSERT_TRUE(retVal);
    TEST_ASSERT_EQUAL_HEX32(i - 1, itemToGet[99]);
    TEST_ASSERT_EQUAL_HEX16(i - 1, getKey);
    TEST_ASSERT_EQUAL_HEX8(sizeof(itemToPush), itemSize);
    retVal = DLList_PopBack(List);
    TEST_ASSERT_TRUE(retVal);
    free(itemToGet);
  }

  retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize, &getKey);
  TEST_ASSERT_FALSE(retVal);
  retVal = DLList_PopBack(List);
  TEST_ASSERT_FALSE(retVal);
}

TEST(TC_DLList, TC_DLList_should_TraverseForwardProperly)
{
  uint32_t itemToPush;
  uint32_t *itemToGet = NULL;
  uint32_t pushKey, getKey;
  size_t itemSize;
  bool retVal;
  const uint32_t items = 1000;

  for (uint32_t i = 0; i < items; i++)
  {
    itemToPush = i;
    retVal = DLList_PushBack(List, (void*)&itemToPush, sizeof(itemToPush), &pushKey);
    TEST_ASSERT_TRUE(retVal);
    TEST_ASSERT_EQUAL_HEX16(i, pushKey);
  }

  DLList_StartTraverse(List);
  for (uint32_t i = 0; i < items; i++)
  {
    retVal = DLList_GetNext(List, (void**)&itemToGet, &itemSize, &getKey);
    TEST_ASSERT_TRUE(retVal);
    TEST_ASSERT_EQUAL_HEX32(i, *itemToGet);
    TEST_ASSERT_EQUAL_HEX16(i, getKey);
    TEST_ASSERT_EQUAL_HEX8(sizeof(itemToPush), itemSize);
  }

  for (uint32_t i = 0; i < items; i++)
  {
    retVal = DLList_GetBack(List, (void**)&itemToGet, &itemSize, &getKey);
    TEST_ASSERT_TRUE(retVal);
    retVal = DLList_PopBack(List);
    TEST_ASSERT_TRUE(retVal);
    free(itemToGet);
  }

  retVal = DLList_GetNext(List, (void**)&itemToGet, &itemSize, &getKey);
  TEST_ASSERT_FALSE(retVal);
  retVal = DLList_PopBack(List);
  TEST_ASSERT_FALSE(retVal);
}

// TODO: addd test when list is empty and pop, get

/**
 * @} end of group TC_DLList
 */
