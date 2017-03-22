/*=======================================================================================*
 * @file    SEEPM.h
 * @author  Damian Pala
 * @date    19-03-2017
 * @brief   Header file for SEEPM - Simple EEPROM Manager module
 *
 *          This file contains API of SEEPM module
 *======================================================================================*/
/*----------------------- DEFINE TO PREVENT RECURSIVE INCLUSION ------------------------*/
#ifndef SEEPM_H_
#define SEEPM_H_

/**
 * @addtogroup SEEPM Description
 * @{
 * @brief Module for managing EEPROM memory due to limited writing cycle - memory wear leveling.
 */

/*======================================================================================*/
/*                       ####### PREPROCESSOR DIRECTIVES #######                        */
/*======================================================================================*/
/*-------------------------------- INCLUDE DIRECTIVES ----------------------------------*/

/*----------------------------- LOCAL OBJECT-LIKE MACROS -------------------------------*/

/*---------------------------- LOCAL FUNCTION-LIKE MACROS ------------------------------*/

/*======================================================================================*/
/*                     ####### EXPORTED TYPE DECLARATIONS #######                       */
/*======================================================================================*/
/*-------------------------------- OTHER TYPEDEFS --------------------------------------*/

/*------------------------------------- ENUMS ------------------------------------------*/
typedef enum SEEPM_InitStatus_Tag
{
  SEEPM_INIT_STATUS_EMPTY_MEM = 1,
  SEEPM_INIT_STATUS_SUCCESS,
  SEEPM_INIT_STATUS_ERROR,
} SEEPM_InitStatus_T;

typedef enum SEEPM_WriteRet_Tag
{
  SEEPM_WRITE_SUCCESS = 1,
  SEEPM_WRITE_TOO_BIG_ITEM_SIZE,
  SEEPM_WRITE_ERROR,
} SEEPM_WriteRet_T;

typedef enum SEEPM_ReadRet_Tag
{
  SEEPM_READ_SUCCESS = 1,
  SEEPM_READ_ERROR,
} SEEPM_ReadRet_T;

/*------------------------------- STRUCT AND UNIONS ------------------------------------*/

/*======================================================================================*/
/*                    ####### EXPORTED OBJECT DECLARATIONS #######                      */
/*======================================================================================*/

/*======================================================================================*/
/*                   ####### EXPORTED FUNCTIONS PROTOTYPES #######                      */
/*======================================================================================*/
SEEPM_InitStatus_T SEEPM_Init(void);
SEEPM_ReadRet_T SEEPM_ReadItem(void *item, uint16_t size);
SEEPM_WriteRet_T SEEPM_WriteItem(void *item, uint16_t size);
void SEEPM_EraseMemory(void);
bool SEEPM_TestMemory(void);

/*======================================================================================*/
/*                          ####### INLINE FUNCTIONS #######                            */
/*======================================================================================*/

/**
 * @}
 */

#endif /* SEEPM_H_ */
