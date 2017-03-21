/*=======================================================================================*
 * @file    TC_SEEPM.c
 * @author  Damian Pala
 * @date    19-03-2017
 * @brief   This file contains unit tests for SEEPM module.
 *======================================================================================*/

/**
 * @addtogroup TC_SEEPM Simple EEPROM Manager tests
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

#include "SEEPM.c"
#include "EEPD.h"

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
 * @brief   SEEPM Test Group.
 */
TEST_GROUP(SEEPM);

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
TEST_SETUP(SEEPM)
{
  EEPD_Init();
}

/**
 * @brief   Tear Down Test Environment.
 */
TEST_TEAR_DOWN(SEEPM)
{

}

TEST(SEEPM, EEPD_should_WriteAndReadProperly)
{
  for (uint16_t i = 0; i < EEPROM_SIZE; i++)
  {
    EEPD_WriteByte(EEPROM_START_ADDR + i, i);
  }

  for (uint16_t i = 0; i < EEPROM_SIZE; i++)
  {
    TEST_ASSERT_EQUAL_HEX8(i, EEPD_ReadByte(EEPROM_START_ADDR + i));
  }
}

TEST(SEEPM, SEEPM_should_ReturnEmptyStatusWhenMemoryIsVirgin)
{
  TEST_ASSERT_EQUAL_UINT8(SEEPM_INIT_STATUS_EMPTY_MEM, SEEPM_Init());
}

TEST(SEEPM, SEEPM_should_InitMemoryProperly)
{

}

TEST(SEEPM, SEEPM_should_ClearMemoryProperly)
{

}

TEST(SEEPM, SEEPM_should_WriteAndReadSmallItemProperly)
{
  uint8_t item[5] = {0x11, 0x22, 0x33, 0x44, 0x55};
  uint8_t buffer[5];
  SEEPM_WriteRet_T writeRet;
  SEEPM_ReadRet_T readRet;

  SEEPM_Init();

  writeRet = SEEPM_WriteItem((void*)item, 5);
  TEST_ASSERT_EQUAL(SEEPM_WRITE_SUCCESS, writeRet);

  readRet = SEEPM_ReadItem((void*)buffer, 5);
  TEST_ASSERT_EQUAL(SEEPM_READ_SUCCESS, readRet);

  TEST_ASSERT_EQUAL_HEX8_ARRAY(item, buffer, 5);
}

TEST(SEEPM, SEEPM_should_NotWriteToBigItems)
{
  uint8_t item[MEM_ITEM_MAX_DATASIZE + 1];
  uint8_t buffer[MEM_ITEM_MAX_DATASIZE + 1];
  SEEPM_WriteRet_T writeRet;
  SEEPM_ReadRet_T readRet;

  SEEPM_Init();

  for (uint16_t i = 0; i < MEM_ITEM_MAX_DATASIZE + 1; i++)
  {
    item[i] = i;
  }

  writeRet = SEEPM_WriteItem((void*)item, MEM_ITEM_MAX_DATASIZE + 1);
  TEST_ASSERT_EQUAL(SEEPM_WRITE_TOO_BIG_ITEM_SIZE, writeRet);

//  readRet = SEEPM_ReadItem((void*)buffer, MEM_ITEM_MAX_DATASIZE + 1);
//  TEST_ASSERT_EQUAL(SEEPM_READ_SUCCESS, readRet);
//
//  TEST_ASSERT_EQUAL_HEX8_ARRAY(item, buffer, MEM_ITEM_MAX_DATASIZE + 1);
}

TEST(SEEPM, SEEPM_should_WriteItemManyTimesToManyWraparoundAndReadItemProperly)
{

}

TEST(SEEPM, SEEPM_should_WriteAndReadItemProperlyAfterItsSizeChanged)
{

}

TEST(SEEPM, SFIFO_GetItem_should_ReturnFalseWhenTryToGetNotExistItem)
{
//  enum {ITEM_SIZE = 4};
//  enum {ITEM_NUMBER = 10};
//  bool pushRet, getRet;
//  uint32_t item;
//
//  SFIFO_Create(myFifo, ITEM_SIZE, ITEM_NUMBER);
//
//  for (uint32_t itemCnt = 0; itemCnt < ITEM_NUMBER; itemCnt++)
//  {
//    pushRet = SFIFO_PushItem(myFifo, (void*)&itemCnt);
//    TEST_ASSERT_TRUE(pushRet);
//    TEST_ASSERT_EQUAL_UINT16(itemCnt + 1, SFIFO_GetItemsInFifo(myFifo));
//  }
//
//  getRet = SFIFO_GetItem(myFifo, ITEM_NUMBER, (void*)&item);
//  TEST_ASSERT_FALSE(getRet);
//
//  SFIFO_Clear(myFifo);
//  getRet = SFIFO_GetItem(myFifo, 1, (void*)&item);
//  TEST_ASSERT_FALSE(getRet);
}


/**
 * @} end of group TC_S-FIFO Static FIFO Queue unit tests
 */
