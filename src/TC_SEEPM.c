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
#define UNIT_TEST

#if defined UNIT_TEST
#define MEM_ITEM_MAX_DATASIZE       0xFF
#endif

#include "unity.h"
#include "unity_fixture.h"

#include "SEEPM.c"
#include "EEPD.h"

/*----------------------------- LOCAL OBJECT-LIKE MACROS -------------------------------*/
#define UT_MEM_DEFAULT_SIZE         EEPROM_SIZE

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
#if defined UNIT_TEST
  MEM_SIZE = UT_MEM_DEFAULT_SIZE;
  MEM_END_ADDR = EEPROM_START_ADDR + MEM_SIZE;
#endif

  EEPD_Init();
  ActualMemItemCnt = 0;
  ActualMemItemAddress = MEM_START_ADDR;
  ActualMemItemTotalSize = 0;
}

/**
 * @brief   Tear Down Test Environment.
 */
TEST_TEAR_DOWN(SEEPM)
{

}

// TODO: Try add test for CRC calc

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
  SEEPM_InitStatus_T initStatus = SEEPM_INIT_STATUS_ERROR;
  uint8_t item[5] = {0x11, 0x22, 0x33, 0x44, 0x55};
  SEEPM_WriteRet_T writeRet;

  for (uint16_t i = 0; i < EEPROM_SIZE; i++)
  {
    EEPROM[i] = i & 0xFF;
  }

  initStatus = SEEPM_Init();
  TEST_ASSERT_EQUAL(SEEPM_INIT_STATUS_EMPTY_MEM, initStatus);

  writeRet = SEEPM_WriteItem((void*)item, 5);
  TEST_ASSERT_EQUAL(SEEPM_WRITE_SUCCESS, writeRet);

  initStatus = SEEPM_Init();
  TEST_ASSERT_EQUAL(SEEPM_INIT_STATUS_SUCCESS, initStatus);


  ActualMemItemCnt = 0;
  ActualMemItemAddress = MEM_START_ADDR;
  ActualMemItemTotalSize = 0;

  for (uint16_t i = 0; i < EEPROM_SIZE; i++)
  {
    EEPROM[i] = i & 0xFF;
  }

  EEPROM[0] = MEM_ITEM_HEADER_VALUE;
  EEPROM[1] = 0;
  EEPROM[2] = 10;

  initStatus = SEEPM_Init();
  TEST_ASSERT_EQUAL(SEEPM_INIT_STATUS_EMPTY_MEM, initStatus);

  writeRet = SEEPM_WriteItem((void*)item, 5);
  TEST_ASSERT_EQUAL(SEEPM_WRITE_SUCCESS, writeRet);

  initStatus = SEEPM_Init();
  TEST_ASSERT_EQUAL(SEEPM_INIT_STATUS_SUCCESS, initStatus);
}

TEST(SEEPM, SEEPM_should_InitMemoryProperlyAfterReset)
{
  SEEPM_InitStatus_T initStatus = SEEPM_INIT_STATUS_ERROR;
  uint8_t item[5] = {0x11, 0x22, 0x33, 0x44, 0x55};
  uint8_t buffer[5];
  SEEPM_WriteRet_T writeRet;
  SEEPM_ReadRet_T readRet;

  initStatus = SEEPM_Init();
  TEST_ASSERT_EQUAL(SEEPM_INIT_STATUS_EMPTY_MEM, initStatus);

  for (uint16_t i = 0; i < (MEM_SIZE / (MEM_ITEM_OVERHEAD_SIZE + 5)) * 15 / 10; i++)
  {
    item[1] = i & 0xFF;

    for (uint8_t buffCnt = 0; buffCnt < 9; buffCnt++)
    {
      buffer[buffCnt] = 0;
    }

    writeRet = SEEPM_WriteItem((void*)item, 5);
    TEST_ASSERT_EQUAL(SEEPM_WRITE_SUCCESS, writeRet);

    readRet = SEEPM_ReadItem((void*)buffer, 5);
    TEST_ASSERT_EQUAL(SEEPM_READ_SUCCESS, readRet);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(item, buffer, 5);
  }

  ActualMemItemCnt = 0;
  ActualMemItemAddress = MEM_START_ADDR;
  ActualMemItemTotalSize = 0;
  initStatus = SEEPM_Init();
  TEST_ASSERT_EQUAL(SEEPM_INIT_STATUS_SUCCESS, initStatus);

  readRet = SEEPM_ReadItem((void*)buffer, 5);
  TEST_ASSERT_EQUAL(SEEPM_READ_SUCCESS, readRet);
  TEST_ASSERT_EQUAL_HEX8_ARRAY(item, buffer, 5);
}

TEST(SEEPM, SEEPM_should_WriteSingleItemAndResetAndReadItemProperly)
{
  SEEPM_InitStatus_T initStatus = SEEPM_INIT_STATUS_ERROR;
  uint8_t item[5] = {0x11, 0x22, 0x33, 0x44, 0x55};
  uint8_t buffer[5];
  SEEPM_WriteRet_T writeRet;
  SEEPM_ReadRet_T readRet;

  initStatus = SEEPM_Init();
  TEST_ASSERT_EQUAL(SEEPM_INIT_STATUS_EMPTY_MEM, initStatus);

  writeRet = SEEPM_WriteItem((void*)item, 5);
  TEST_ASSERT_EQUAL(SEEPM_WRITE_SUCCESS, writeRet);

  readRet = SEEPM_ReadItem((void*)buffer, 5);
  TEST_ASSERT_EQUAL(SEEPM_READ_SUCCESS, readRet);
  TEST_ASSERT_EQUAL_HEX8_ARRAY(item, buffer, 5);

  ActualMemItemCnt = 0;
  ActualMemItemAddress = MEM_START_ADDR;
  ActualMemItemTotalSize = 0;
  initStatus = SEEPM_Init();
  TEST_ASSERT_EQUAL(SEEPM_INIT_STATUS_SUCCESS, initStatus);

  readRet = SEEPM_ReadItem((void*)buffer, 5);
  TEST_ASSERT_EQUAL(SEEPM_READ_SUCCESS, readRet);
  TEST_ASSERT_EQUAL_HEX8_ARRAY(item, buffer, 5);
}

TEST(SEEPM, SEEPM_should_ClearMemoryProperly)
{
  SEEPM_Init();

  for (uint16_t i = 0; i < MEM_SIZE; i++)
  {
    EEPROM[i] = i & 0xFF;
  }

  SEEPM_EraseMemory();

  for (uint16_t i = 0; i < MEM_SIZE; i++)
  {
    TEST_ASSERT_BYTES_EQUAL(0xFF, EEPROM[i]);
  }
}

TEST(SEEPM, SEEPM_should_PassTestMemoryFnc)
{
  TEST_ASSERT_TRUE(SEEPM_TestMemory());
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

TEST(SEEPM, SEEPM_should_NotReadItemWithNotProperSize)
{
  uint8_t item[5] = {0x11, 0x22, 0x33, 0x44, 0x55};
  uint8_t buffer[5];
  SEEPM_WriteRet_T writeRet;
  SEEPM_ReadRet_T readRet;

  SEEPM_Init();

  writeRet = SEEPM_WriteItem((void*)item, 5);
  TEST_ASSERT_EQUAL(SEEPM_WRITE_SUCCESS, writeRet);

  readRet = SEEPM_ReadItem((void*)buffer, 4);
  TEST_ASSERT_EQUAL(SEEPM_READ_ERROR, readRet);
}

TEST(SEEPM, SEEPM_should_WriteAndReadMaxItemSizedProperlyWhenMaxItemSizeHasMaxValue)
{
  uint8_t item[MEM_ITEM_MAX_DATASIZE];
  uint8_t buffer[MEM_ITEM_MAX_DATASIZE];
  SEEPM_WriteRet_T writeRet;
  SEEPM_ReadRet_T readRet;

  SEEPM_Init();

  for (uint16_t i = 0; i < MEM_ITEM_MAX_DATASIZE; i++)
  {
    item[i] = i;
  }

  writeRet = SEEPM_WriteItem((void*)item, MEM_ITEM_MAX_DATASIZE);
  TEST_ASSERT_EQUAL(SEEPM_WRITE_SUCCESS, writeRet);

  readRet = SEEPM_ReadItem((void*)buffer, MEM_ITEM_MAX_DATASIZE);
  TEST_ASSERT_EQUAL(SEEPM_READ_SUCCESS, readRet);

  TEST_ASSERT_EQUAL_HEX8_ARRAY(item, buffer, MEM_ITEM_MAX_DATASIZE);
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

  readRet = SEEPM_ReadItem((void*)buffer, MEM_ITEM_MAX_DATASIZE + 1);
  TEST_ASSERT_EQUAL(SEEPM_READ_ERROR, readRet);
}

TEST(SEEPM, SEEPM_should_WriteItemManyTimesToManyWraparoundAndReadItemProperly)
{
  uint8_t item[5] = {0x11, 0x22, 0x33, 0x44, 0x55};
  uint8_t buffer[5];
  SEEPM_WriteRet_T writeRet;
  SEEPM_ReadRet_T readRet;

  SEEPM_Init();

  for (uint16_t i = 0; i < 2000; i++)
  {
    item[1] = i & 0xFF;
    writeRet = SEEPM_WriteItem((void*)item, 5);
    TEST_ASSERT_EQUAL(SEEPM_WRITE_SUCCESS, writeRet);

    readRet = SEEPM_ReadItem((void*)buffer, 5);
    TEST_ASSERT_EQUAL(SEEPM_READ_SUCCESS, readRet);

    TEST_ASSERT_EQUAL_HEX8_ARRAY(item, buffer, 5);
  }
}

TEST(SEEPM, SEEPM_should_WriteWholeMemory)
{
  uint8_t item[5] = {0x11, 0x22, 0x33, 0x44, 0x55};
  uint8_t buffer[5];
  SEEPM_WriteRet_T writeRet;
  SEEPM_ReadRet_T readRet;
  uint8_t offset;

  SEEPM_Init();

  for (uint16_t i = 0; i < MEM_SIZE / (5 + MEM_ITEM_OVERHEAD_SIZE); i++)
  {
    writeRet = SEEPM_WriteItem((void*)item, 5);
    TEST_ASSERT_EQUAL(SEEPM_WRITE_SUCCESS, writeRet);

    readRet = SEEPM_ReadItem((void*)buffer, 5);
    TEST_ASSERT_EQUAL(SEEPM_READ_SUCCESS, readRet);

    TEST_ASSERT_EQUAL_HEX8_ARRAY(item, buffer, 5);
  }

  for (uint16_t i = 0; i < MEM_SIZE / (5 + MEM_ITEM_OVERHEAD_SIZE); i++)
  {
    offset = 0;
    TEST_ASSERT_EQUAL_HEX8(MEM_ITEM_HEADER_VALUE, EEPROM[i * (5 + MEM_ITEM_OVERHEAD_SIZE) + offset++]);
    TEST_ASSERT_EQUAL_HEX8(GET_MSBYTE((i + 1)), EEPROM[i * (5 + MEM_ITEM_OVERHEAD_SIZE) + offset++]);
    TEST_ASSERT_EQUAL_HEX8(GET_LSBYTE((i + 1)), EEPROM[i * (5 + MEM_ITEM_OVERHEAD_SIZE) + offset++]);
    TEST_ASSERT_EQUAL_HEX8(5, EEPROM[i * (5 + MEM_ITEM_OVERHEAD_SIZE) + offset++]);
    for (uint8_t itemCnt = 0; itemCnt < 5; itemCnt++)
    {
      TEST_ASSERT_EQUAL_HEX8(item[itemCnt], EEPROM[i * (5 + MEM_ITEM_OVERHEAD_SIZE) + offset++]);
    }
    offset++; // for CRC
  }
}

TEST(SEEPM, SEEPM_should_WriteAndReadItemProperlyAfterItsSizeChanged)
{
  uint8_t item[9] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99};
  uint8_t buffer[9];
  SEEPM_WriteRet_T writeRet;
  SEEPM_ReadRet_T readRet;

  SEEPM_Init();

  for (uint16_t i = 0; i < 2000; i++)
  {
    for (uint8_t j = 0; j < 5; j++)
    {
      item[1] = i & 0xFF;

      for (uint8_t buffCnt = 0; buffCnt < 9; buffCnt++)
      {
        buffer[buffCnt] = 0;
      }

      writeRet = SEEPM_WriteItem((void*)item, j + 5);
      TEST_ASSERT_EQUAL(SEEPM_WRITE_SUCCESS, writeRet);

      readRet = SEEPM_ReadItem((void*)buffer, j + 5);
      TEST_ASSERT_EQUAL(SEEPM_READ_SUCCESS, readRet);

      TEST_ASSERT_EQUAL_HEX8_ARRAY(item, buffer, j + 5);
    }
  }
}

TEST(SEEPM, SEEPM_should_WriteAndReadItemProperlyOnHugeMemSpace)
{
  uint8_t item[9] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99};
  uint8_t buffer[9];
  SEEPM_WriteRet_T writeRet;
  SEEPM_ReadRet_T readRet;

#if defined UNIT_TEST
  MEM_SIZE = 0xFFFF;
  MEM_END_ADDR = EEPROM_START_ADDR + MEM_SIZE;
#endif

  SEEPM_Init();

  for (uint16_t i = 0; i < 0xFFFF; i++)
  {
    for (uint8_t j = 0; j < 5; j++)
    {
      item[1] = i & 0xFF;

      for (uint8_t buffCnt = 0; buffCnt < 9; buffCnt++)
      {
        buffer[buffCnt] = 0;
      }

      writeRet = SEEPM_WriteItem((void*)item, j + 5);
      TEST_ASSERT_EQUAL(SEEPM_WRITE_SUCCESS, writeRet);

      readRet = SEEPM_ReadItem((void*)buffer, j + 5);
      TEST_ASSERT_EQUAL(SEEPM_READ_SUCCESS, readRet);

      TEST_ASSERT_EQUAL_HEX8_ARRAY(item, buffer, j + 5);
    }
  }
}

/**
 * @} end of group TC_S-FIFO Static FIFO Queue unit tests
 */
