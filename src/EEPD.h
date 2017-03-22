/*=======================================================================================*
 * @file    EEPD.h
 * @author  Damian Pala
 * @date    19-03-2017
 * @brief   Header file for EEPD - EEPROM Emulator
 *
 *          This file contains API of EEPD module
 *======================================================================================*/
/*----------------------- DEFINE TO PREVENT RECURSIVE INCLUSION ------------------------*/
#ifndef EEPD_H_
#define EEPD_H_

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

/*----------------------------- LOCAL OBJECT-LIKE MACROS -------------------------------*/
#define EEPROM_SIZE               1024
#define EEPROM_START_ADDR         0x310000
#define EEPROM_INIT_VALUE         0xFF

#define EEPROM_EMULATION_SIZE     0xFFFF

/*---------------------------- LOCAL FUNCTION-LIKE MACROS ------------------------------*/

/*======================================================================================*/
/*                     ####### EXPORTED TYPE DECLARATIONS #######                       */
/*======================================================================================*/
/*-------------------------------- OTHER TYPEDEFS --------------------------------------*/

/*------------------------------------- ENUMS ------------------------------------------*/

/*------------------------------- STRUCT AND UNIONS ------------------------------------*/

/*======================================================================================*/
/*                    ####### EXPORTED OBJECT DECLARATIONS #######                      */
/*======================================================================================*/
extern uint8_t EEPROM[EEPROM_EMULATION_SIZE];

/*======================================================================================*/
/*                   ####### EXPORTED FUNCTIONS PROTOTYPES #######                      */
/*======================================================================================*/
void EEPD_Init(void);
uint8_t EEPD_ReadByte(uint32_t address);
void EEPD_WriteByte(uint32_t address, uint8_t byte);

/*======================================================================================*/
/*                          ####### INLINE FUNCTIONS #######                            */
/*======================================================================================*/

/**
 * @}
 */

#endif /* EEPD_H_ */
