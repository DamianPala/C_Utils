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

#include "misc.c"

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
TEST_GROUP(MISC);

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
TEST_SETUP(MISC)
{

}

/**
 * @brief   Tear Down Test Environment.
 */
TEST_TEAR_DOWN(MISC)
{

}

TEST(MISC, IsEven_should_EvalNumberProperly)
{
  bool IsEven = true;
  for (uint32_t num = 0; num < 0xFFFF + 1; num++)
  {
    if (IsEven)
    {
      TEST_ASSERT_TRUE(MISC_IsEven(num));
    }
    else
    {
      TEST_ASSERT_FALSE(MISC_IsEven(num));
    }

    if (IsEven)
    {
      IsEven = false;
    }
    else
    {
      IsEven = true;
    }
  }
}

/**
 * @} end of group TC_S-FIFO Static FIFO Queue unit tests
 */
