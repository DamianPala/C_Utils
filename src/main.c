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
  RUN_TEST_CASE(FIFO, SFIFO_GetItem_should_WorksProperlyWhenPushedMoreItemsThanFifoSizeWithOverwrite);
  RUN_TEST_CASE(FIFO, SFIFO_GetItem_should_WorksProperlyWhenFifoIsNotFull);
  RUN_TEST_CASE(FIFO, SFIFO_UpdateLastItem_should_UpdateLastItemProperlyWhenFifoIsNotFull);
  RUN_TEST_CASE(FIFO, SFIFO_UpdateLastItem_should_UpdateLastItemProperlyWhenFifoIsFull);
  RUN_TEST_CASE(FIFO, SFIFO_UpdateLastItem_should_UpdateLastItemProperlyWhenFifoIsOverflowed);
  RUN_TEST_CASE(FIFO, SFIFO_UpdateLastItem_should_UpdateLastItemProperlyWhenFifoIsOverwriten);
  RUN_TEST_CASE(FIFO, SFIFO_UpdateLastItem_should_UpdateLastItemProperlyInVariousSimpleCases);

  RUN_TEST_CASE(CRC, CRC8_should_BeCalculatedProperly);
  RUN_TEST_CASE(CRC, CRC16_should_BeCalculatedProperly);
  RUN_TEST_CASE(CRC, CRC32_should_BeCalculatedProperly);

  RUN_TEST_CASE(SEEPM, SEEPM_should_InitMemoryProperly);
  RUN_TEST_CASE(SEEPM, SEEPM_should_InitMemoryProperlyAfterReset);
  RUN_TEST_CASE(SEEPM, SEEPM_should_WriteSingleItemAndResetAndReadItemProperly)
  RUN_TEST_CASE(SEEPM, SEEPM_should_ClearMemoryProperly);
  RUN_TEST_CASE(SEEPM, SEEPM_should_PassTestMemoryFnc);
  RUN_TEST_CASE(SEEPM, SEEPM_should_ReturnEmptyStatusWhenMemoryIsVirgin);
  RUN_TEST_CASE(SEEPM, EEPD_should_WriteAndReadProperly);
  RUN_TEST_CASE(SEEPM, SEEPM_should_WriteAndReadSmallItemProperly);
  RUN_TEST_CASE(SEEPM, SEEPM_should_NotReadItemWithNotProperSize);
  RUN_TEST_CASE(SEEPM, SEEPM_should_NotWriteToBigItems);
  RUN_TEST_CASE(SEEPM, SEEPM_should_WriteAndReadMaxItemSizedProperlyWhenMaxItemSizeHasMaxValue);
  RUN_TEST_CASE(SEEPM, SEEPM_should_WriteItemManyTimesToManyWraparoundAndReadItemProperly);
  RUN_TEST_CASE(SEEPM, SEEPM_should_WriteWholeMemory);
  RUN_TEST_CASE(SEEPM, SEEPM_should_WriteAndReadItemProperlyAfterItsSizeChanged);
  RUN_TEST_CASE(SEEPM, SEEPM_should_WriteAndReadItemProperlyOnHugeMemSpace);

  RUN_TEST_CASE(MISC, IsEven_should_EvalNumberProperly);
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
