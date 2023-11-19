/*!*****************************************************************************
 * @file      filename.h
 * @brief     A brief definition.
 * @details   Detailed explanation.
 * @author    Name Surnames <mail@facomsa.com>
 * @date      20YY-MM-DD
 * @copyright FACOMSA
 * @version   v0:[20XX-XX-XX XXX] - Creation of the library
 * @warning   Library not validated
 * @bug       No known bugs
 ******************************************************************************/

#ifndef _INCLUDE_GUARD_H
#define _INCLUDE_GUARD_H 1

/* Unrecognized pragma warning disable (used for code organization) */
/* For GreenHillsSoftware */
#pragma ghs nowarning 161
/* For CodeWarrior */
#pragma warning off(10186)
/* For IAR it is not needed */

/*******************************************************************************
 *                            1. FILE INCLUDES
 ******************************************************************************/
#pragma region

#include "r_typedefs.h"
#include <stdint.h>

#pragma endregion

/*******************************************************************************
 *                           2. LIBRARY DEFINES
 ******************************************************************************/
#pragma region

#pragma endregion

/*******************************************************************************
 *                          3. LIBRARY TYPEDEFS
 ******************************************************************************/
#pragma region

#pragma endregion

/*******************************************************************************
 *                       4. LIBRARY GLOBAL VARIABLES
 ******************************************************************************/
#pragma region

#pragma endregion

/*******************************************************************************
 *                     5. LIBRARY FILE PUBLIC FUNCTIONS
 ******************************************************************************/
#pragma region

/**
 * @brief  Function to prepare the data into u08_messageTxBuff that will
 * be eventualy transmitted
 * @return r_bool_t.
 */
uint8_t u16_TXRX_sendMessage(uint8_t * u08_buff, uint8_t u08_buffLength);


/**
 * @brief  Function to be called in ordderr to give order to the ISR
 * be eventualy transmitted
 * @return r_bool_t.
 */
void vfn_TXRX_readMessage()
/**
 * @brief Gets the IsReadyToSend  used to calculate the IsReadyToSend
 * ADD EXTRA INFORMATION HERE TO HELP FUTURE DEVELOPERS UNDERTANDING!.
 * @return r_bool_t.
 */
r_bool_t bln_TXRX_GetIsReadyToSend(void);

/**
 * @brief Sets a bln_isReadyToSend value.
 * @param[in]  _bln_isReadyToSend: DESCRIPTION_OF_THE_INPUT_HERE (UNITS_OF_THE_INPUT_HERE).
 */
void vfn_TXRX_SetIsReadyToSend(r_bool_t _bln_isReadyToSend);

/**
 * @brief Gets the MessageTxBuff  used to calculate the MessageTxBuff
 * ADD EXTRA INFORMATION HERE TO HELP FUTURE DEVELOPERS UNDERTANDING!.
 * @return uint8_t.
 */
uint8_t u08_TXRX_GetMessageTxBuff(void);

/**
 * @brief Send bit by bit all the data contained in the trasmitter buffer.
 * @return uint8_t.
 */
void vfn_TXRX_sendBits(void);

/**
 * @brief Process bits until the sequence 101010... is detected.
 * @return uint8_t.
 */
void vfn_TXRX_pll(void)

/**
 * @brief Fill rx buffer with raw data.
 * @return uint8_t.
 */
void vfn_TXRX_readData(void)

/**
 * @brief Gets the IsReadyToReceive  used to calculate the IsReadyToReceive
 * ADD EXTRA INFORMATION HERE TO HELP FUTURE DEVELOPERS UNDERTANDING!.
 * @return r_bool_t.
 */
r_bool_t bln_TXRX_GetIsReadyToReceive(void);

/**
 * @brief Sets a bln_isReadyToReceive value.
 * @param[in]  _bln_isReadyToReceive: DESCRIPTION_OF_THE_INPUT_HERE (UNITS_OF_THE_INPUT_HERE).
 */
void vfn_TXRX_SetIsReadyToReceive(r_bool_t _bln_isReadyToReceive);




#pragma endregion

/* For GreenHillsSoftware */
#pragma ghs endnowarning 161
/* For CodeWarrior */
#pragma warning on(10186)

#endif





