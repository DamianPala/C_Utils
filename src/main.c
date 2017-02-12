/*=======================================================================================*
 * @file    source.c
 * @author  Damian Pala
 * @version 0.4
 * @date    XX-XX-20XX
 * @brief   This file contains all implementations for XXX module.
 *======================================================================================*/

/**
 * @addtogroup XXX Description
 * @{
 * @brief Module for... .
 */

/*======================================================================================*/
/*                       ####### PREPROCESSOR DIRECTIVES #######                        */
/*======================================================================================*/
/*-------------------------------- INCLUDE DIRECTIVES ----------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#include "unity_fixture.h"

/*----------------------------- LOCAL OBJECT-LIKE MACROS -------------------------------*/

/*---------------------------- LOCAL FUNCTION-LIKE MACROS ------------------------------*/

/*======================================================================================*/
/*                           ####### TESTS GROUPS #######                               */
/*======================================================================================*/
TEST_GROUP_RUNNER(FIFO)
{
  RUN_TEST_CASE(FIFO, FIFO_should_PushAndPopItemsProperly);
}

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

/*======================================================================================*/
/*                    ####### LOCAL FUNCTIONS PROTOTYPES #######                        */
/*======================================================================================*/
static void RunAllTests(void);

/*======================================================================================*/
/*                   ####### LOCAL FUNCTIONS DEFINITIONS #######                        */
/*======================================================================================*/
static void RunAllTests(void)
{
  RUN_TEST_GROUP(FIFO);
}

/*======================================================================================*/
/*                  ####### EXPORTED FUNCTIONS DEFINITIONS #######                      */
/*======================================================================================*/
int main(int argc, const char * argv[])
{
  return UnityMain(argc, argv, RunAllTests);
}

/**
 * @}
 */
