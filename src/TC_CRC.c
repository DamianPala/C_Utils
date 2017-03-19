/*=======================================================================================*
 * @file    TC_CRC.c
 * @author  Damian Pala
 * @date    19-03-2017
 * @brief   This file contains unit tests for CRC module.
 *======================================================================================*/

/**
 * @addtogroup TC_CRC CRC calculations tests
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

#include "CRC.c"

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
 * @brief   CRC Test Group.
 */
TEST_GROUP(CRC);

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
TEST_SETUP(CRC)
{

}

/**
 * @brief   Tear Down Test Environment.
 */
TEST_TEAR_DOWN(CRC)
{

}

#define TEST_DATA_LEN         12

typedef struct CRC_TestData_Tag
{
  uint8_t data[TEST_DATA_LEN];
  uint32_t crc8_polynom;
  uint32_t crc16_polynom;
  uint32_t crc32_polynom;
  uint32_t crc8_initVal;
  uint32_t crc16_initVal;
  uint32_t crc32_initVal;
  uint32_t crc8_xorVal;
  uint32_t crc16_xorVal;
  uint32_t crc32_xorVal;
  uint32_t crc8;
  uint32_t crc16;
  uint32_t crc32;
} CRC_TestData_T;

CRC_TestData_T CRC_TestData[4] =
{
  {
    .data = {0xab, 0xbc, 0xcd, 0xde, 0xa1, 0xb2, 0xc3, 0xd4, 0xa5, 0xb6, 0xc7, 0xd7},
    .crc8_polynom = 0xE0,
    .crc16_polynom = 0x8408,
    .crc32_polynom = 0xEDB88320,
    .crc8_initVal = 0xF1,
    .crc16_initVal = 0xF1F1,
    .crc32_initVal = 0xF1F1F1F1,
    .crc8_xorVal = 0xAB,
    .crc16_xorVal = 0xABAB,
    .crc32_xorVal = 0xABABABAB,
    .crc8 = 0x8B,
    .crc16 = 0x0C1B,
    .crc32 = 0xADB383EB,
  },
  {
    .data = {0x12, 0x34, 0x56, 0x78, 0x12, 0x32, 0x52, 0x72, 0x11, 0x31, 0x51, 0x71},
    .crc8_polynom = 0xE0,
    .crc16_polynom = 0x8408,
    .crc32_polynom = 0xEDB88320,
    .crc8_initVal = 0xF1,
    .crc16_initVal = 0xF1F1,
    .crc32_initVal = 0xF1F1F1F1,
    .crc8_xorVal = 0xAB,
    .crc16_xorVal = 0xABAB,
    .crc32_xorVal = 0xABABABAB,
    .crc8 = 0xCB,
    .crc16 = 0x9F23,
    .crc32 = 0x88C9AF4B,
  },
  {
    .data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    .crc8_polynom = 0xE0,
    .crc16_polynom = 0x8408,
    .crc32_polynom = 0xEDB88320,
    .crc8_initVal = 0xF1,
    .crc16_initVal = 0xF1F1,
    .crc32_initVal = 0xF1F1F1F1,
    .crc8_xorVal = 0xAB,
    .crc16_xorVal = 0xABAB,
    .crc32_xorVal = 0xABABABAB,
    .crc8 = 0x4B,
    .crc16 = 0x9333,
    .crc32 = 0x6EE5610B,
  },
  {
    .data = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    .crc8_polynom = 0xE0,
    .crc16_polynom = 0x8408,
    .crc32_polynom = 0xEDB88320,
    .crc8_initVal = 0xF1,
    .crc16_initVal = 0xF1F1,
    .crc32_initVal = 0xF1F1F1F1,
    .crc8_xorVal = 0xAB,
    .crc16_xorVal = 0xABAB,
    .crc32_xorVal = 0xABABABAB,
    .crc8 = 0x4B,
    .crc16 = 0xA3F3,
    .crc32 = 0x0DF7CBAB,
  }
};

TEST(CRC, CRC8_should_BeCalculatedProperly)
{
  uint32_t crc;
  uint8_t testIterator = 0;

  crc = CRC_CalcCRC8(CRC_TestData[testIterator].data, sizeof(CRC_TestData[testIterator].data));
  TEST_ASSERT_EQUAL_HEX8(CRC_TestData[testIterator].crc8, crc);

  testIterator++;
  crc = CRC_CalcCRC8(CRC_TestData[testIterator].data, sizeof(CRC_TestData[testIterator].data));
  TEST_ASSERT_EQUAL_HEX8(CRC_TestData[testIterator].crc8, crc);


  testIterator++;
  crc = CRC_CalcCRC8(CRC_TestData[testIterator].data, sizeof(CRC_TestData[testIterator].data));
  TEST_ASSERT_EQUAL_HEX8(CRC_TestData[testIterator].crc8, crc);

  testIterator++;
  crc = CRC_CalcCRC8(CRC_TestData[testIterator].data, sizeof(CRC_TestData[testIterator].data));
  TEST_ASSERT_EQUAL_HEX8(CRC_TestData[testIterator].crc8, crc);
}

TEST(CRC, CRC16_should_BeCalculatedProperly)
{
  uint32_t crc;
  uint8_t testIterator = 0;


  crc = CRC_CalcCRC16(CRC_TestData[testIterator].data, sizeof(CRC_TestData[testIterator].data));
  TEST_ASSERT_EQUAL_HEX16(CRC_TestData[testIterator].crc16, crc);


  testIterator++;
  crc = CRC_CalcCRC16(CRC_TestData[testIterator].data, sizeof(CRC_TestData[testIterator].data));
  TEST_ASSERT_EQUAL_HEX16(CRC_TestData[testIterator].crc16, crc);


  testIterator++;
  crc = CRC_CalcCRC16(CRC_TestData[testIterator].data, sizeof(CRC_TestData[testIterator].data));
  TEST_ASSERT_EQUAL_HEX16(CRC_TestData[testIterator].crc16, crc);


  testIterator++;
  crc = CRC_CalcCRC16(CRC_TestData[testIterator].data, sizeof(CRC_TestData[testIterator].data));
  TEST_ASSERT_EQUAL_HEX16(CRC_TestData[testIterator].crc16, crc);

}

TEST(CRC, CRC32_should_BeCalculatedProperly)
{
  uint32_t crc;
  uint8_t testIterator = 0;

  crc = CRC_CalcCRC32(CRC_TestData[testIterator].data, sizeof(CRC_TestData[testIterator].data));
  TEST_ASSERT_EQUAL_HEX32(CRC_TestData[testIterator].crc32, crc);


  testIterator++;
  crc = CRC_CalcCRC32(CRC_TestData[testIterator].data, sizeof(CRC_TestData[testIterator].data));
  TEST_ASSERT_EQUAL_HEX32(CRC_TestData[testIterator].crc32, crc);


  testIterator++;
  crc = CRC_CalcCRC32(CRC_TestData[testIterator].data, sizeof(CRC_TestData[testIterator].data));
  TEST_ASSERT_EQUAL_HEX32(CRC_TestData[testIterator].crc32, crc);


  testIterator++;
  crc = CRC_CalcCRC32(CRC_TestData[testIterator].data, sizeof(CRC_TestData[testIterator].data));
  TEST_ASSERT_EQUAL_HEX32(CRC_TestData[testIterator].crc32, crc);
}

/**
 * @} end of group TC_S-FIFO Static FIFO Queue unit tests
 */
