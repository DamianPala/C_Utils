/*=======================================================================================*
 * @file    main.c
 * @author  Damian Pala
 * @date    12-02-2017
 * @brief   This file contains code for main file.
 *======================================================================================*/

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
  RUN_TEST_CASE(FIFO, FIFO_should_PushAndPopAndCountItemsProperlyAndReturnFalseWhenFullOrEmpty);
  RUN_TEST_CASE(FIFO, FIFO_should_OverwriteLastItemsWhenPushedMoreItemsThanFifoSize);
  RUN_TEST_CASE(FIFO, FIFO_should_OverwriteLastItemsWhenPushedMoreItemsThanFifoSizeIterationTest);
  RUN_TEST_CASE(FIFO, FIFO_should_BeClearedProperly);
  RUN_TEST_CASE(FIFO, FIFO_should_WorkProperlyOnHugeItemNumber);
  RUN_TEST_CASE(FIFO, FIFO_should_WorkProperlyOnHugeItemSize);
  RUN_TEST_CASE(FIFO, FIFO_should_GetItemProperly);
  RUN_TEST_CASE(FIFO, SFIFO_GetItem_should_ReturnFalseWhenTryToGetNotExistItem);
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
