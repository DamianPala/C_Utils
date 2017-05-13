/*=======================================================================================*
 * @file    misc.h
 * @author  Damian Pala
 * @date    19-03-2017
 * @brief   Header file for misc calculations
 *
 *          This file contains API of misc module
 *======================================================================================*/
/*----------------------- DEFINE TO PREVENT RECURSIVE INCLUSION ------------------------*/
#ifndef MISC_H_
#define MISC_H_

/**
 * @addtogroup misc Description
 * @{
 * @brief Module for misc calculations.
 */

/*======================================================================================*/
/*                       ####### PREPROCESSOR DIRECTIVES #######                        */
/*======================================================================================*/
/*-------------------------------- INCLUDE DIRECTIVES ----------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/*----------------------------- LOCAL OBJECT-LIKE MACROS -------------------------------*/

/*---------------------------- LOCAL FUNCTION-LIKE MACROS ------------------------------*/
#define MISC_GET_MSB_BE(word)                         ((word >> 8) & 0xFF)
#define MISC_GET_LSB_BE(word)                         (word & 0xFF)
#define MISC_GET_MSB_LE(word)                         (word & 0xFF)
#define MISC_GET_LSB_LE(word)                         ((word >> 8) & 0xFF)
#define MISC_BUILD_UINT16(hByte, lByte)               (((uint16_t)hByte << 8) + lByte)
#define MISC_BUILD_UINT16_BE(rawBytes)                (((uint16_t)rawBytes[0] << 8) + rawBytes[1])
#define MISC_BUILD_UINT16_LE(rawBytes)                (((uint16_t)rawBytes[1] << 8) + rawBytes[0])

/*======================================================================================*/
/*                     ####### EXPORTED TYPE DECLARATIONS #######                       */
/*======================================================================================*/
/*-------------------------------- OTHER TYPEDEFS --------------------------------------*/

/*------------------------------------- ENUMS ------------------------------------------*/

/*------------------------------- STRUCT AND UNIONS ------------------------------------*/

/*======================================================================================*/
/*                    ####### EXPORTED OBJECT DECLARATIONS #######                      */
/*======================================================================================*/

/*======================================================================================*/
/*                   ####### EXPORTED FUNCTIONS PROTOTYPES #######                      */
/*======================================================================================*/
bool MISC_IsEven(uint16_t num);

/*======================================================================================*/
/*                          ####### INLINE FUNCTIONS #######                            */
/*======================================================================================*/

/**
 * @}
 */

#endif /* MISC_H_ */
