/*!*****************************************************************************
 * @file filename.c
 ******************************************************************************/

/* Unrecognized pragma warning disable (used for code organization) */
/* For GreenHillsSoftware */
#pragma ghs nowarning 161
/* For CodeWarrior */
#pragma warning off(10186)
/* For IAR it is not needed */

/*******************************************************************************
 *                             1. FILE INCLUDES
 ******************************************************************************/
#pragma region

#include "TXTR_Tranceiver.h"
#include "r_typedefs.h"
#include <stdint.h>

#pragma endregion

/*******************************************************************************
 *                             2. FILE LOCAL DEFINES
 ******************************************************************************/
#pragma region
/* Num of Bytes in the message header  */
#define HEADER_MESSAGE_SIZE 8U
#define FRAME_MESSAGE_SIZE  8U
#define MESSAGE_RX_SIZE     16U
#define MESSAGE_TX_SIZE     16U
#define MESSAGE_DATA_SIZE   (MESSAGE_TX_SIZE - HEADER_MESSAGE_SIZE)

#pragma endregion

/*******************************************************************************
 *                             3. FILE LOCAL TYPEDEFS
 ******************************************************************************/
#pragma region

#pragma endregion

/*******************************************************************************
 *                      4. PUBLIC FILE GLOBAL VARIABLES
 ******************************************************************************/
#pragma region

#pragma endregion

/*******************************************************************************
 *                      5. PRIVATE FILE GLOBAL VARIABLES
 ******************************************************************************/
#pragma region


static uint8_t u08_messageHeaderBuff[HEADER_MESSAGE_SIZE] = { 0XAAU,
                                                              0XAAU,
                                                              0XAAU,
                                                              0XAAU,
                                                              0XAAU,
                                                              0XAAU,
                                                              0XAAU,
                                                              0XAAU
};

static uint8_t u08_messageTxBuff[MESSAGE_TX_SIZE];
static uint8_t u08_messageRxBuff[MESSAGE_RX_SIZE];
static r_bool_t bln_isReadyToSend = r_false;
static r_bool_t bln_isReadyToReceive = r_true;
static r_bool_t bln_isReadyToReadData = r_false;
static r_bool_t bln_isReadToSyncronizePll = r_false;


static uint8_t u08_dataLength = 0U;
static uint8_t u08_bitTXIndex = 0U;
static uint8_t u08_bitRXIndex = 0U;
static uint8_t u08_byteTXIndex = 0U;
static uint8_t u08_byteRXIndex = 0U;




#pragma endregion

/*******************************************************************************
 *                         6. FILE PRIVATE FUNCTIONS
 ******************************************************************************/
#pragma region

#pragma region PROTOTYPES

#pragma endregion PROTOTYPES

#pragma endregion

/*******************************************************************************
 *                          7. FILE PUBLIC FUNCTIONS
 ******************************************************************************/
#pragma region

uint8_t u16_TXRX_sendMessage(uint8_t * u08_buff, uint8_t u08_buffLength)
{
    u08_dataLength = u08_buffLength;
    /* Clean Tx Message */
	for ( uint8_t i = 0U; i < MESSAGE_TX_SIZE; ++i )
	{
        u08_messageTxBuff[i] = 0x00U;
	}

    *u08_messageTxBuff = *u08_messageHeaderBuff;
    u08_messageTxBuff += HEADER_MESSAGE_SIZE;

	if ( MESSAGE_DATA_SIZE > u08_buffLength )
	{
	    /* Set raw data from buffer into messageTxBuffer to transmit */
        for (uint8_t i = 0; i < u08_buffLength; ++i)
        {
            u08_messageTxBuff[i] = u08_buff[i];
        }

	    bln_isReadyToSend = r_true;
	}
	else
	{
	    bln_isReadyToSend = r_false;
	}
}

void vfn_TXRX_sendBits()
{
	if ( bln_isReadyToSend )
	{

        /* Each time the transmitter sends 8bits,
        * increment Byte counter */
        if (u08_bitTXIndex % 8U)
        {
            ++u08_byteTXIndex;
            u08_bitTXIndex = 0U;
        }
        else
        {

        }
        uint8_t u08_txBit = u08_messageTxBuff[u08_byteTXIndex] &
                            (1 << u08_bitTXIndex++);
        //P1OUT = u08_txBit;
        P1OUT |= BIT0 & u08_txBit;

        if (u08_txBit) {
            // P1.3 is high, turn on the LED on P1.0
            P1OUT |= BIT0;
        } else {
            // P1.3 is low, turn off the LED on P1.0
            P1OUT &= ~BIT0;
        }





	}
	else
	{
	    /* Do nothing */
	}

    /* Whenever message is fully tranmitted,
     * Restart all the variables and set transmitter not ready to send
     * since no data is avaliable */
    if( u08_bitTXIndex == (HEADER_MESSAGE_SIZE + u08_buffLength)*8U )
    {
        u08_bitTXIndex = 0U;
        u08_byteTXIndex = 0U;
        bln_isReadyToSend = r_false;
    }
}


void vfn_TXRX_pll()
{
    static uint8_t u08_rxBit = 0U;
    static uint8_t u08_prevRxBit = 0U;
    static uint8_t u08_pllCount = 0U;

    u08_rxBit = P1IN & BIT3;

	if ( u08_rxBit != u08_prevRxBit )
	{
        u08_pllCount++;

        if ( u08_pllCount > 8U )
        {
            bln_isReadToSyncronizePll = r_true;
            bln_isReadyToReadData = r_true;
        }
        u08_prevRxBit = u08_rxBit;
	}
	else
	{
	    /* Do nothing */
	}
}

void vfn_TXRX_readData()
{
    /* Take each bit of the raw data */
    u08_rxBit = P1IN & BIT3;
    uint8_t _u08_rxIndex = u08_bitRXIndex*u08_byteRXIndex;
	if ( u08_bitTXIndex < (FRAME_MESSAGE_SIZE - 1U) )
	{
	    /* Insert data into rx buffer */
        if( _u08_rxIndex < MESSAGE_RX_SIZE)
        {
            u08_messageRxBuff[_u08_rxIndex] = u08_rxBit;
        }
        else
        {
            /* Do nothing */
        }
	}
	else
	{
	    /* Next received frame */
        u08_byteTXIndex++;
	}

    u08_messageRxBuff[u08_bitRXIndex++] = u08_rxBit;


}

void vfn_TXRX_readBits()
{
	if ( bln_isReadyToReceive )
	{
        if ( !bln_isReadyToReadData )
        {
            vfn_TXRX_pll();
        }
        else
        {
            vfn_TXRX_readData();

        }
	    /* Write something */
	}
	else
	{
	    /* Do nothing */
	}
}

void vfn_TXRX_readMessage()
{
	if ( !bln_isReadyToReceive )
	{
        bln_isReadyToReceive = r_true;
	    /* Write something */
	}
	else
	{
	    /* Do nothing */
	}
}

r_bool_t bln_TXRX_GetIsReadyToSend()
{
    return bln_isReadyToSend;
}

void vfn_TXRX_SetIsReadyToSend(r_bool_t _bln_isReadyToSend)
{
    bln_isReadyToSend = _bln_isReadyToSend;
}

uint8_t u08_TXRX_GetMessageTxBuff()
{
    return u08_messageTxBuff;
}


r_bool_t bln_TXRX_GetIsReadyToReceive()
{
    return bln_isReadyToReceive;
}

void vfn_TXRX_SetIsReadyToReceive(r_bool_t _bln_isReadyToReceive)
{
    bln_isReadyToReceive = _bln_isReadyToReceive;
}

#pragma endregion

/* For GreenHillsSoftware */
#pragma ghs endnowarning 161
/* For CodeWarrior */
#pragma warning on(10186)
