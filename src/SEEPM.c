/*=======================================================================================*
 * @file    SEEPM.c
 * @author  Damian Pala
 * @date    19-03-2017
 * @brief   This file contains all implementations for SEEPM module.
 *======================================================================================*/

/**
 * @addtogroup SEEPM Description
 * @{
  * @brief Module for managing EEPROM memory due to limited writing cycle - memory wear leveling.
 */

/*======================================================================================*/
/*                       ####### PREPROCESSOR DIRECTIVES #######                        */
/*======================================================================================*/
/*-------------------------------- INCLUDE DIRECTIVES ----------------------------------*/
#include <stdint.h>
#include <stdbool.h>

#include "SEEPM.h"
#include "EEPD.h"

/*----------------------------- LOCAL OBJECT-LIKE MACROS -------------------------------*/
#if !defined UNIT_TEST

#define MEM_START_ADDR                    EEPROM_START_ADDR
#define MEM_SIZE                          EEPROM_SIZE
#define MEM_END_ADDR                      (MEM_START_ADDR + MEM_SIZE)
#define MEM_CLEAR_VALUE                   EEPROM_INIT_VALUE

#if MEM_SIZE < 20 || MEM_SIZE > 0xFFFF
#error Invalid memory size!
#endif

#else
static uint32_t MEM_START_ADDR = EEPROM_START_ADDR;
static uint32_t MEM_SIZE = EEPROM_SIZE;
static uint32_t MEM_END_ADDR = (EEPROM_START_ADDR + EEPROM_SIZE);
static uint32_t MEM_CLEAR_VALUE = EEPROM_INIT_VALUE;
#endif

#define MEM_INITIALIZED_SIGN_VALUE        0xABCD
#define MEM_INITIALIZED_SIGN_VALUE_SIZE   2

#define MEM_ITEM_HEADER_VALUE             0x6B
#define MEM_ITEM_HEADER_SIZE              1
#define MEM_ITEM_CNT_SIZE                 2
#define MEM_ITEM_DATASIZE_SIZE            1
#define MEM_ITEM_CRC_SIZE                 1
#define MEM_ITEM_OVERHEAD_SIZE            (MEM_ITEM_HEADER_SIZE + MEM_ITEM_CNT_SIZE + MEM_ITEM_DATASIZE_SIZE + MEM_ITEM_CRC_SIZE)

#ifndef UNIT_TEST

#if (EEPROM_SIZE / 10) > 0xFF
#define MEM_ITEM_MAX_DATASIZE             128
#else
#define MEM_ITEM_MAX_DATASIZE             (EEPROM_SIZE / 10)
#endif
#if MEM_ITEM_MAX_DATASIZE > 0xFF
#error Too big maximum item data size parameter!
#endif

#endif

#define CRC8_INITIAL_VALUE                0xF1
#define CRC8_FINAL_XOR_VALUE              0xAB
#define CRC8_POLYNOMIAL                   0xE0
#define CRC8_MSBIT                        (1 << 7)

/*---------------------------- LOCAL FUNCTION-LIKE MACROS ------------------------------*/
#define GET_MSBYTE(word)                  ((word >> 8) & 0xFF)
#define GET_LSBYTE(word)                  (word & 0xFF)
#define BUILD_UINT16(hByte, lByte)        (((uint16_t)hByte << 8) + lByte)

#define CRC8_BYTE_TO_REMAINDER(byte)      (byte)

/*======================================================================================*/
/*                      ####### LOCAL TYPE DECLARATIONS #######                         */
/*======================================================================================*/
/*-------------------------------- OTHER TYPEDEFS --------------------------------------*/

/*------------------------------------- ENUMS ------------------------------------------*/
typedef enum CrcCalcMode_Tag
{
  CRC_CALC_DATA_FROM_READ_MEM = 1,
  CRC_CALC_DATA_FROM_ARG,
} CrcCalcMode_T;
/*------------------------------- STRUCT AND UNIONS ------------------------------------*/
typedef struct MemItem_Tag
{
  uint8_t header;
  uint16_t cnt;
  uint16_t dataSize;
  uint8_t *data;
  uint8_t crc;
} MemItem_T;

/*======================================================================================*/
/*                         ####### OBJECT DEFINITIONS #######                           */
/*======================================================================================*/
/*--------------------------------- EXPORTED OBJECTS -----------------------------------*/

/*---------------------------------- LOCAL OBJECTS -------------------------------------*/
#if !defined UNIT_TEST
uint16_t ActualMemItemCnt = 0;
uint32_t ActualMemItemAddress = MEM_START_ADDR;
uint32_t ActualMemItemTotalSize = 0;
#else
uint16_t ActualMemItemCnt = 0;
uint32_t ActualMemItemAddress = EEPROM_START_ADDR;
uint32_t ActualMemItemTotalSize = 0;
#endif

/*======================================================================================*/
/*                    ####### LOCAL FUNCTIONS PROTOTYPES #######                        */
/*======================================================================================*/
static void FindLastMemItem(void);
static bool IsMemItemWrittenOk(MemItem_T *memItem);
static void MakeWraparoundIfNeeded(uint8_t newMemItemTotalSize);
static void CalcItemCrc(MemItem_T *memItem, uint32_t offset, CrcCalcMode_T mode);

/*======================================================================================*/
/*                  ####### EXPORTED FUNCTIONS DEFINITIONS #######                      */
/*======================================================================================*/
SEEPM_InitStatus_T SEEPM_Init(void)
{
  SEEPM_InitStatus_T ret = SEEPM_INIT_STATUS_ERROR;

  FindLastMemItem();

  if (0 == ActualMemItemCnt)
  {
    ret = SEEPM_INIT_STATUS_EMPTY_MEM;
  }
  else
  {
    ret = SEEPM_INIT_STATUS_SUCCESS;
  }

  return ret;
}

SEEPM_ReadRet_T SEEPM_ReadItem(void *item, uint16_t size)
{
  MemItem_T readItem;
  uint8_t memItemCrc;
  uint32_t offset = ActualMemItemAddress;
  SEEPM_ReadRet_T ret = SEEPM_READ_ERROR;

  readItem.header = EEPD_ReadByte(offset++);
  readItem.cnt = EEPD_ReadByte(offset++) << 8;
  readItem.cnt += EEPD_ReadByte(offset++);
  readItem.dataSize = size; offset++;
  readItem.data = (uint8_t*)item;

  if (readItem.dataSize <= MEM_ITEM_MAX_DATASIZE)
  {
    for (uint16_t byteCnt = 0; byteCnt < readItem.dataSize; byteCnt++)
    {
      readItem.data[byteCnt] = EEPD_ReadByte(offset++);
    }

    memItemCrc = EEPD_ReadByte(offset++);

    CalcItemCrc(&readItem, 0, CRC_CALC_DATA_FROM_ARG);

    if (memItemCrc == readItem.crc)
    {
      ret = SEEPM_READ_SUCCESS;
    }
    else
    {
      ret = SEEPM_READ_ERROR;
    }
  }
  else
  {
    ret = SEEPM_READ_ERROR;
  }

  return ret;
}

SEEPM_WriteRet_T SEEPM_WriteItem(void *item, uint16_t size)
{
  SEEPM_WriteRet_T ret = SEEPM_WRITE_ERROR;
  uint32_t offset = 0;
  uint8_t newMemItemTotalSize = 0;
  MemItem_T memItem;

  memItem.header = MEM_ITEM_HEADER_VALUE;
  memItem.cnt = ActualMemItemCnt;
  memItem.data = (uint8_t*)item;
  memItem.dataSize = size;

  if ( (memItem.dataSize > 0) && (memItem.dataSize <= MEM_ITEM_MAX_DATASIZE) )
  {
    newMemItemTotalSize = memItem.dataSize + MEM_ITEM_OVERHEAD_SIZE;

    MakeWraparoundIfNeeded(newMemItemTotalSize);

    memItem.cnt++;

    offset = ActualMemItemAddress + ActualMemItemTotalSize;

    EEPD_WriteByte(offset++, memItem.header);
    EEPD_WriteByte(offset++, GET_MSBYTE(memItem.cnt));
    EEPD_WriteByte(offset++, GET_LSBYTE(memItem.cnt));
    EEPD_WriteByte(offset++, (uint8_t)memItem.dataSize);

    for (uint16_t byteCnt = 0; byteCnt < memItem.dataSize; byteCnt++)
    {
      EEPD_WriteByte(offset++, (memItem.data)[byteCnt]);
    }

    CalcItemCrc(&memItem, 0, CRC_CALC_DATA_FROM_ARG);

    EEPD_WriteByte(offset++, memItem.crc);

    if (IsMemItemWrittenOk(&memItem))
    {
      ret = SEEPM_WRITE_SUCCESS;

      ActualMemItemCnt = memItem.cnt;
      ActualMemItemAddress += ActualMemItemTotalSize;
      ActualMemItemTotalSize = newMemItemTotalSize;
    }
    else
    {
      ret = SEEPM_WRITE_ERROR;
    }
  }
  else
  {
    if (memItem.dataSize > MEM_ITEM_MAX_DATASIZE)
    {
      ret = SEEPM_WRITE_TOO_BIG_ITEM_SIZE;
    }
    else
    {
      ret = SEEPM_WRITE_ERROR;
    }
  }

  return ret;
}

void SEEPM_EraseMemory(void)
{
  for (uint16_t addr = 0; addr < MEM_SIZE; addr++)
  {
    EEPD_WriteByte(MEM_START_ADDR + addr, MEM_CLEAR_VALUE);
  }
}

/*======================================================================================*/
/*                   ####### LOCAL FUNCTIONS DEFINITIONS #######                        */
/*======================================================================================*/
static void FindLastMemItem(void)
{
  uint8_t memItemCrc;
  bool isCrcOk;
  uint32_t offset = MEM_START_ADDR;
  MemItem_T readItem;

  do
  {
    readItem.header = EEPD_ReadByte(offset++);
    if (MEM_ITEM_HEADER_VALUE == readItem.header)
    {
      readItem.cnt = EEPD_ReadByte(offset++) << 8;
      readItem.cnt += EEPD_ReadByte(offset++);
      readItem.dataSize = EEPD_ReadByte(offset++);

      CalcItemCrc(&readItem, offset, CRC_CALC_DATA_FROM_READ_MEM);

      memItemCrc = EEPD_ReadByte(offset++);
      if (memItemCrc == readItem.crc)
      {
        ActualMemItemCnt = readItem.cnt;
        ActualMemItemTotalSize = readItem.dataSize + MEM_ITEM_OVERHEAD_SIZE;
        ActualMemItemAddress = offset - readItem.dataSize - MEM_ITEM_OVERHEAD_SIZE;
        isCrcOk = true;
      }
      else
      {
        isCrcOk = false;
      }
    }
  }
  while ( (MEM_ITEM_HEADER_VALUE == readItem.header) && (offset < MEM_END_ADDR) && (true == isCrcOk));
}

static bool IsMemItemWrittenOk(MemItem_T *memItem)
{
  uint32_t addr;

  addr = ActualMemItemAddress + ActualMemItemTotalSize;
  if (EEPD_ReadByte(addr++) != MEM_ITEM_HEADER_VALUE)
  {
    return false;
  }
  if (EEPD_ReadByte(addr++) != GET_MSBYTE(memItem->cnt))
  {
    return false;
  }
  if (EEPD_ReadByte(addr++) != GET_LSBYTE(memItem->cnt))
  {
    return false;
  }
  if (EEPD_ReadByte(addr++) != memItem->dataSize)
  {
    return false;
  }
  for (uint16_t byteCnt = 0; byteCnt < memItem->dataSize; byteCnt++)
  {
    if (EEPD_ReadByte(addr++) != (memItem->data)[byteCnt])
    {
      return false;
    }
  }
  if (EEPD_ReadByte(addr++) != memItem->crc)
  {
    return false;
  }

  return true;
}

static void MakeWraparoundIfNeeded(uint8_t newMemItemTotalSize)
{
  if (ActualMemItemAddress + ActualMemItemTotalSize + newMemItemTotalSize > MEM_END_ADDR)
  {
    SEEPM_EraseMemory();
    ActualMemItemCnt = 0;
    ActualMemItemTotalSize = 0;
    ActualMemItemAddress = MEM_START_ADDR;
  }
}

static void CalcItemCrc(MemItem_T *memItem, uint32_t offset, CrcCalcMode_T mode)
{
  uint8_t remainder = CRC8_INITIAL_VALUE;

  for (uint16_t byte = 0; byte < memItem->dataSize + MEM_ITEM_OVERHEAD_SIZE; byte++)
  {
    if (0 == byte)
    {
      remainder ^= CRC8_BYTE_TO_REMAINDER(memItem->header);
    }
    else if (1 == byte)
    {
      remainder ^= CRC8_BYTE_TO_REMAINDER(GET_MSBYTE(memItem->cnt));
    }
    else if (2 == byte)
    {
      remainder ^= CRC8_BYTE_TO_REMAINDER(GET_LSBYTE(memItem->cnt));
    }
    else if (3 == byte)
    {
      remainder ^= CRC8_BYTE_TO_REMAINDER(memItem->dataSize);
    }
    else
    {
      if (CRC_CALC_DATA_FROM_ARG == mode)
      {
        remainder ^= CRC8_BYTE_TO_REMAINDER((memItem->data)[byte - MEM_ITEM_OVERHEAD_SIZE - MEM_ITEM_CRC_SIZE]);
      }
      else /* CRC_CALC_DATA_FROM_READ_MEM == mode */
      {
        remainder ^= CRC8_BYTE_TO_REMAINDER(EEPD_ReadByte(offset + byte - MEM_ITEM_OVERHEAD_SIZE - MEM_ITEM_CRC_SIZE));
      }
    }

    for (uint8_t nbit = 0; nbit < 8; nbit++)
    {
      if (remainder & CRC8_MSBIT)
      {
        remainder = (remainder << 1) ^ CRC8_POLYNOMIAL;
      }
      else
      {
        remainder = (remainder << 1);
      }
    }
  }

  memItem->crc = remainder ^ CRC8_FINAL_XOR_VALUE;
}

/**
 * @}
 */
