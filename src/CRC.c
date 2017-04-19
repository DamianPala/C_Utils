/*=======================================================================================*
 * @file    CRC.c
 * @author  Damian Pala
 * @date    19-03-2017
 * @brief   This file contains all implementations for CRC module.
 *======================================================================================*/

/**
 * @addtogroup CRC Description
 * @{
  * @brief Module for calculating CRC.
 */

/*======================================================================================*/
/*                       ####### PREPROCESSOR DIRECTIVES #######                        */
/*======================================================================================*/
/*-------------------------------- INCLUDE DIRECTIVES ----------------------------------*/
#include <stdint.h>

#include "CRC.h"

/*----------------------------- LOCAL OBJECT-LIKE MACROS -------------------------------*/
#define CRC8_INITIAL_VALUE            0xF1
#define CRC16_INITIAL_VALUE           0xF1F1
#define CRC32_INITIAL_VALUE           0xF1F1F1F1

#define CRC8_FINAL_XOR_VALUE          0xAB
#define CRC16_FINAL_XOR_VALUE         0xABAB
#define CRC32_FINAL_XOR_VALUE         0xABABABAB

#define CRC8_POLYNOMIAL               0xE0
#define CRC16_POLYNOMIAL              0x8408
#define CRC32_POLYNOMIAL              0xEDB88320

#define CRC8_MSBIT                    (1 << 7)
#define CRC16_MSBIT                   (1 << 15)
#define CRC32_MSBIT                   (1 << 31)

/*---------------------------- LOCAL FUNCTION-LIKE MACROS ------------------------------*/
#define CRC8_BYTE_TO_REMAINDER(byte)  (byte)
#define CRC16_BYTE_TO_REMAINDER(byte) (byte << 8)
#define CRC32_BYTE_TO_REMAINDER(byte) (byte << 24)

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
static uint32_t Remainder = 0;

/*======================================================================================*/
/*                    ####### LOCAL FUNCTIONS PROTOTYPES #######                        */
/*======================================================================================*/

/*======================================================================================*/
/*                  ####### EXPORTED FUNCTIONS DEFINITIONS #######                      */
/*======================================================================================*/
uint8_t  CRC_CalcCRC8(uint8_t *data, uint16_t nBytes)
{
  uint8_t remainder = CRC8_INITIAL_VALUE;

  for (uint16_t byte = 0; byte < nBytes; byte++)
  {
    remainder ^= CRC8_BYTE_TO_REMAINDER(data[byte]);

    for (uint8_t nBit = 0; nBit < 8; nBit++)
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

  return (remainder ^ CRC8_FINAL_XOR_VALUE);
}

uint16_t CRC_CalcCRC16(uint8_t *data, uint16_t nBytes)
{
  uint16_t remainder = CRC16_INITIAL_VALUE;

  for (uint16_t byte = 0; byte < nBytes; byte++)
  {
    remainder ^= CRC16_BYTE_TO_REMAINDER(data[byte]);

    for (uint8_t nBit = 0; nBit < 8; nBit++)
    {
      if (remainder & CRC16_MSBIT)
      {
        remainder = (remainder << 1) ^ CRC16_POLYNOMIAL;
      }
      else
      {
        remainder = (remainder << 1);
      }
    }
  }

  return (remainder ^ CRC16_FINAL_XOR_VALUE);
}

uint32_t CRC_CalcCRC32(uint8_t *data, uint16_t nBytes)
{
  uint32_t remainder = CRC32_INITIAL_VALUE;

  for (uint16_t byte = 0; byte < nBytes; byte++)
  {
    remainder ^= CRC32_BYTE_TO_REMAINDER(data[byte]);

    for (uint8_t nBit = 0; nBit < 8; nBit++)
    {
      if (remainder & CRC32_MSBIT)
      {
        remainder = (remainder << 1) ^ CRC32_POLYNOMIAL;
      }
      else
      {
        remainder = (remainder << 1);
      }
    }
  }

  return (remainder ^ CRC32_FINAL_XOR_VALUE);
}

void CRC_CalcIterateStart(CRC_CalcSize_T crcSize)
{
  switch(crcSize)
  {
    case CRC_CALC_SIZE_8:
    default:
    {
      Remainder = CRC8_INITIAL_VALUE;
      break;
    }
    case CRC_CALC_SIZE_16:
    {
      Remainder = CRC16_INITIAL_VALUE;
      break;
    }
    case CRC_CALC_SIZE_32:
    {
      Remainder = CRC32_INITIAL_VALUE;
      break;
    }
  }
}

uint32_t CRC_CalcIterate(uint8_t byte, CRC_CalcSize_T crcSize)
{
  uint32_t msBit, polynomial, finalXorValue;

  switch(crcSize)
  {
    case CRC_CALC_SIZE_8:
    default:
    {
      Remainder ^= CRC8_BYTE_TO_REMAINDER(byte);
      msBit = CRC8_MSBIT;
      polynomial = CRC8_POLYNOMIAL;
      finalXorValue = CRC8_FINAL_XOR_VALUE;
      break;
    }
    case CRC_CALC_SIZE_16:
    {
      Remainder ^= CRC16_BYTE_TO_REMAINDER(byte);
      msBit = CRC16_MSBIT;
      polynomial = CRC16_POLYNOMIAL;
      finalXorValue = CRC16_FINAL_XOR_VALUE;
      break;
    }
    case CRC_CALC_SIZE_32:
    {
      Remainder ^= CRC32_BYTE_TO_REMAINDER(byte);
      msBit = CRC32_MSBIT;
      polynomial = CRC32_POLYNOMIAL;
      finalXorValue = CRC32_FINAL_XOR_VALUE;
      break;
    }
  }

  for (uint8_t nBit = 0; nBit < 8; nBit++)
  {
    if (Remainder & msBit)
    {
      Remainder = (Remainder << 1) ^ polynomial;
    }
    else
    {
      Remainder = (Remainder << 1);
    }
  }

  return (Remainder ^ finalXorValue);
}

/*======================================================================================*/
/*                   ####### LOCAL FUNCTIONS DEFINITIONS #######                        */
/*======================================================================================*/

/**
 * @}
 */
