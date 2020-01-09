/*
 * Pos_functions.c
 *
 *  Created on: 29 kwi 2019
 *      Author: Hotwater
 */

//#include "main.h"
#include "Pos_functions.h"

#ifdef POS_FUNCTIONS
#ifdef TAG

static uint64 get_tx_timestamp_u64(void)
{
    uint8 ts_tab[5];
    uint64 ts = 0;
    int i;
    dwt_readtxtimestamp(ts_tab);
    for (i = 4; i >= 0; i--)
    {
        ts <<= 8;
        ts |= ts_tab[i];
    }
    return ts;
}

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn get_rx_timestamp_u64()
 *
 * @brief Get the RX time-stamp in a 64-bit variable.
 *        /!\ This function assumes that length of time-stamps is 40 bits, for both TX and RX!
 *
 * @param  none
 *
 * @return  64-bit value of the read time-stamp.
 */
static uint64 get_rx_timestamp_u64(void)
{
    uint8 ts_tab[5];
    uint64 ts = 0;
    int i;
    dwt_readrxtimestamp(ts_tab);
    for (i = 4; i >= 0; i--)
    {
        ts <<= 8;
        ts |= ts_tab[i];
    }
    return ts;
}

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn final_msg_set_ts()
 *
 * @brief Fill a given timestamp field in the final message with the given value. In the timestamp fields of the final
 *        message, the least significant byte is at the lower address.
 *
 * @param  ts_field  pointer on the first byte of the timestamp field to fill
 *         ts  timestamp value
 *
 * @return none
 */
static void final_msg_set_ts(uint8 *ts_field, uint64 ts)
{
    int i;
    for (i = 0; i < FINAL_MSG_TS_LEN; i++)
    {
        ts_field[i] = (uint8) ts;
        ts >>= 8;
    }
}

static void final_msg_get_ts(const uint8 *ts_field, uint32 *ts)
{
    int i;
    *ts = 0;
    for (i = 0; i < FINAL_MSG_TS_LEN; i++)
    {
        *ts += ts_field[i] << (i * 8);
    }
}

void UWB_Tag_Init()
{
    reset_DW1000(); /* Target specific drive of RSTn line into DW1000 low for a period. */
    port_set_dw1000_slowrate();
    char uartBuffer[20];
    if (dwt_initialise(DWT_LOADUCODE) == DWT_ERROR)
    {



        while (1)
        {
        	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        	HAL_UART_Transmit(&huart3, uartBuffer,sprintf(uartBuffer, "DW Readout Error \r \n"), 100U);
        	HAL_Delay(300);
        };
    }
    port_set_dw1000_fastrate();
   // dwt_setlnapamode(DWT_LNA_ENABLE | DWT_PA_ENABLE);
    dwt_setleds(DWT_LEDS_ENABLE);
    /* Configure DW1000. See NOTE 7 below. */
    dwt_configure(&config);

    /* Apply default antenna delay value. See NOTE 1 below. */
    dwt_setrxantennadelay(RX_ANT_DLY);
    dwt_settxantennadelay(TX_ANT_DLY);

    /* Set preamble timeout for expected frames. See NOTE 6 below. */
    dwt_setpreambledetecttimeout(PRE_TIMEOUT);
}

uint8_t UWB_Tag_Get_Distance(uwb_data_t *dataPtr, uint8_t anchor)
{
	uint8_t rx_expected_poll[sizeof(rx_poll_msg)];
    /* Clear reception timeout to start next ranging process. */
    dwt_setrxtimeout(0);

    /* Activate reception immediately. */
    dwt_rxenable(DWT_START_RX_IMMEDIATE);
    dataPtr->debugMsg = 0x10;
    /* Poll for reception of a frame or error/timeout. See NOTE 8 below. */
    while (!((status_reg = dwt_read32bitreg(SYS_STATUS_ID)) & (SYS_STATUS_RXFCG | SYS_STATUS_ALL_RX_TO | SYS_STATUS_ALL_RX_ERR)))
    {
    	dataPtr->debugMsg = 0x11;
    };

    if (status_reg & SYS_STATUS_RXFCG)
    {
        uint32 frame_len;
        dataPtr->debugMsg = 0x70;
       // HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
        /* Clear good RX frame event in the DW1000 status register. */
        dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_RXFCG);

        /* A frame has been received, read it into the local buffer. */
        frame_len = dwt_read32bitreg(RX_FINFO_ID) & RX_FINFO_RXFL_MASK_1023;
        if (frame_len <= RX_BUFFER_LEN)
        {
            dwt_readrxdata(rx_buffer, frame_len, 0);
        }

        /* Check that the frame is a poll sent by "DS TWR initiator" example.
         * As the sequence number field of the frame is not relevant, it is cleared to simplify the validation of the frame. */

        //Check if message contains data from sensors
        if(rx_buffer[0] == 'd') return 2;

        switch(anchor)
        {
    		case 1:
    		{
    			memcpy(rx_expected_poll, rx_poll_msg_1, sizeof(rx_poll_msg_1));
    			break;
    		}
    		case 2:
    		{
    			memcpy(rx_expected_poll, rx_poll_msg_2, sizeof(rx_poll_msg_2));
    			break;
    		}
    		case 3:
    		{
    			memcpy(rx_expected_poll, rx_poll_msg_3, sizeof(rx_poll_msg_3));
    			break;
    		}
    		case 4:
    		{
    			memcpy(rx_expected_poll, rx_poll_msg_4, sizeof(rx_poll_msg_4));
    			break;
    		}
    		default:
    		{
    			break;
    		}
        }

        //rx_expected_poll[ALL_MSG_SN_IDX] = 0;
        rx_buffer[ALL_MSG_SN_IDX] = 0;


        //if (memcmp(rx_buffer, rx_poll_msg, ALL_MSG_COMMON_LEN) == 0)
        if (memcmp(rx_buffer, rx_expected_poll, ALL_MSG_COMMON_LEN) == 0)
        {
      	  //Try uint64_t
            uint32 resp_tx_time;
            int ret = DWT_SUCCESS;
            char intBuf[25];
            /* Retrieve poll reception timestamp. */
            poll_rx_ts = get_rx_timestamp_u64();

            /* Set send time for response. See NOTE 9 below. */

            //resp_tx_time = ((poll_rx_ts) + (POLL_RX_TO_RESP_TX_DLY_UUS * UUS_TO_DWT_TIME)) >> 8;
            resp_tx_time = ((poll_rx_ts) + (dataPtr->timeout* UUS_TO_DWT_TIME)) >> 8;
            dwt_setdelayedtrxtime((resp_tx_time));

            /* Set expected delay and timeout for final message reception. See NOTE 4 and 5 below. */
            dwt_setrxaftertxdelay(RESP_TX_TO_FINAL_RX_DLY_UUS);
            dwt_setrxtimeout(FINAL_RX_TIMEOUT_UUS);

            /* Write and send the response message. See NOTE 10 below.*/
            tx_resp_msg[ALL_MSG_SN_IDX] = frame_seq_nb;
            dwt_writetxdata(sizeof(tx_resp_msg), tx_resp_msg, 0); /* Zero offset in TX buffer. */
            dwt_writetxfctrl(sizeof(tx_resp_msg), 0, 1); /* Zero offset in TX buffer, ranging. */
            dwt_write8bitoffsetreg(PMSC_ID, PMSC_CTRL0_OFFSET, PMSC_CTRL0_TXCLKS_125M);
            ret = dwt_starttx(DWT_START_TX_DELAYED | DWT_RESPONSE_EXPECTED);
            //dwt_starttx(DWT_START_TX_IMMEDIATE | DWT_RESPONSE_EXPECTED);

            dataPtr->debugError = ret;
            /* If dwt_starttx() returns an error, abandon this ranging exchange and proceed to the next one. See NOTE 11 below. */
            //todo TUTAJ WYWALA
            if(ret == DWT_ERROR)
            {
            	dataPtr->debugMsg = 0x09;
                return 1;
            }

            /* Poll for reception of expected "final" frame or error/timeout. See NOTE 8 below. */
            //status_reg = dwt_read32bitreg(SYS_STATUS_ID);


            //while(!(status_reg & (SYS_STATUS_RXFCG | SYS_STATUS_ALL_RX_TO | SYS_STATUS_ALL_RX_ERR)))
            while (!((status_reg = dwt_read32bitreg(SYS_STATUS_ID)) & (SYS_STATUS_RXFCG | SYS_STATUS_ALL_RX_TO | SYS_STATUS_ALL_RX_ERR)))
            {

          	  status_reg = dwt_read32bitreg(SYS_STATUS_ID);
          	  dataPtr->debugMsg = 0x07;
          	  //debugTimer = status_reg;
            };



            //debugMsg = status_reg;
            /* Increment frame sequence number after transmission of the response message (modulo 256). */
            frame_seq_nb++;
            dataPtr->debugMsg = 0x28;
            if (status_reg & SYS_STATUS_RXFCG)
            {
                dataPtr->debugMsg = 0x15;
                /* Clear good RX frame event and TX frame sent in the DW1000 status register. */
                dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_RXFCG | SYS_STATUS_TXFRS);


                /* A frame has been received, read it into the local buffer. */
                frame_len = dwt_read32bitreg(RX_FINFO_ID) & RX_FINFO_RXFLEN_MASK;
                if (frame_len <= RX_BUF_LEN)
                {
                    dwt_readrxdata(rx_buffer, frame_len, 0);

                }

                /* Check that the frame is a final message sent by "DS TWR initiator" example.
                 * As the sequence number field of the frame is not used in this example, it can be zeroed to ease the validation of the frame. */
                rx_buffer[ALL_MSG_SN_IDX] = 0;
                if (memcmp(rx_buffer, rx_final_msg, ALL_MSG_COMMON_LEN) == 0)
                {
                    uint32 poll_tx_ts, resp_rx_ts, final_tx_ts;
                    uint32 poll_rx_ts_32, resp_tx_ts_32, final_rx_ts_32;
                    double Ra, Rb, Da, Db;
                    uint64_t /*Ra, Rb, Da, Db,*/ tof64, dist64;
                    int64 tof_dtu;

                   // HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
                    dataPtr->debugMsg = 0x80;
                    /* Retrieve response transmission and final reception timestamps. */
                    resp_tx_ts = get_tx_timestamp_u64();
                    final_rx_ts = get_rx_timestamp_u64();

                    /* Get timestamps embedded in the final message. */
                    final_msg_get_ts(&rx_buffer[FINAL_MSG_POLL_TX_TS_IDX], &poll_tx_ts);
                    final_msg_get_ts(&rx_buffer[FINAL_MSG_RESP_RX_TS_IDX], &resp_rx_ts);
                    final_msg_get_ts(&rx_buffer[FINAL_MSG_FINAL_TX_TS_IDX], &final_tx_ts);

                    /* Compute time of flight. 32-bit subtractions give correct answers even if clock has wrapped. See NOTE 12 below. */
                    poll_rx_ts_32 = (uint32)poll_rx_ts;
                    resp_tx_ts_32 = (uint32)resp_tx_ts;
                    final_rx_ts_32 = (uint32)final_rx_ts;
                   // result32 = final_rx_ts_32;
                    //TODO: Does this really need to be double?

                    Ra = (double)(resp_rx_ts - poll_tx_ts);
                    Rb = (double)(final_rx_ts_32 - resp_tx_ts_32);
                    Da = (double)(final_tx_ts - resp_rx_ts);
                    Db = (double)(resp_tx_ts_32 - poll_rx_ts_32);
/*
                    Ra = (resp_rx_ts - poll_tx_ts);
                    Rb = (final_rx_ts_32 - resp_tx_ts_32);
                    Da = (final_tx_ts - resp_rx_ts);
                    Db = (resp_tx_ts_32 - poll_rx_ts_32);
*/
                    tof_dtu = (int64)((Ra * Rb - Da * Db) / (Ra + Rb + Da + Db));

                    tof64 = (uint64_t)tof_dtu*1565;
                    dist64 = (uint64_t)(tof64*299702547)/1000000;

                    //TODO: DWT_TIME_UNITS = 15,65ps. Try to use constant decimal point

                    tof = tof_dtu * DWT_TIME_UNITS;
                    distance = tof * SPEED_OF_LIGHT;
                    dataPtr->debugMsg = 0x90;

                    dataPtr->uwbTof = tof;
                    dataPtr->uwbDistance = distance;
                    dataPtr->uwbDistance64 = dist64;

                    //HAL_UART_Transmit(&huart3, intBuf, sprintf(intBuf, "%ld ps \r \n", tof64), 100U);
                    HAL_UART_Transmit(&huart3, intBuf, sprintf(intBuf, "%ldE-6 \r \n", dist64), 10U);
                    return 0;


                }
            }
            else
            {
                /* Clear RX error/timeout events in the DW1000 status register. */
                dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_ALL_RX_TO | SYS_STATUS_ALL_RX_ERR);
                dataPtr->debugMsg = 0x10;
                HAL_UART_Transmit(&huart3, intBuf, sprintf(intBuf, "RESP \r \n"), 100U);
                Send_Timestamp(resp_tx_time);
                HAL_UART_Transmit(&huart3, intBuf, sprintf(intBuf, "POLL \r \n"), 100U);
                Send_Timestamp(poll_rx_ts);

                /* Reset RX to properly reinitialise LDE operation. */
                dwt_rxreset();
                return 1;

            }
        }
    }
    else
    {
        /* Clear RX error/timeout events in the DW1000 status register. */
        dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_ALL_RX_TO | SYS_STATUS_ALL_RX_ERR);

        /* Reset RX to properly reinitialise LDE operation. */
        dwt_rxreset();
        return 1;
    }
    return 1;

}

#endif

#ifdef ANCHOR

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn get_tx_timestamp_u64()
 *
 * @brief Get the TX time-stamp in a 64-bit variable.
 *        /!\ This function assumes that length of time-stamps is 40 bits, for both TX and RX!
 *
 * @param  none
 *
 * @return  64-bit value of the read time-stamp.
 */
static uint64 get_tx_timestamp_u64(void)
{
    uint8 ts_tab[5];
    uint64 ts = 0;
    int i;
    dwt_readtxtimestamp(ts_tab);
    for (i = 4; i >= 0; i--)
    {
        ts <<= 8;
        ts |= ts_tab[i];
    }
    return ts;
}

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn get_rx_timestamp_u64()
 *
 * @brief Get the RX time-stamp in a 64-bit variable.
 *        /!\ This function assumes that length of time-stamps is 40 bits, for both TX and RX!
 *
 * @param  none
 *
 * @return  64-bit value of the read time-stamp.
 */
static uint64 get_rx_timestamp_u64(void)
{
    uint8 ts_tab[5];
    uint64 ts = 0;
    int i;
    dwt_readrxtimestamp(ts_tab);
    for (i = 4; i >= 0; i--)
    {
        ts <<= 8;
        ts |= ts_tab[i];
    }
    return ts;
}

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn final_msg_set_ts()
 *
 * @brief Fill a given timestamp field in the final message with the given value. In the timestamp fields of the final
 *        message, the least significant byte is at the lower address.
 *
 * @param  ts_field  pointer on the first byte of the timestamp field to fill
 *         ts  timestamp value
 *
 * @return none
 */
static void final_msg_set_ts(uint8 *ts_field, uint64 ts)
{
    int i;
    for (i = 0; i < FINAL_MSG_TS_LEN; i++)
    {
        ts_field[i] = (uint8) ts;
        ts >>= 8;
    }
}


void UWB_Anchor_Init()
{
	  reset_DW1000(); /* Target specific drive of RSTn line into DW1000 low for a period. */
	    port_set_dw1000_slowrate();
	    if (dwt_initialise(DWT_LOADUCODE) == DWT_ERROR)
	    {

	        while (1)
	        { };
	    }
	    port_set_dw1000_fastrate();

	    dwt_setleds(DWT_LEDS_ENABLE);
	    /* Configure DW1000. See NOTE 7 below. */
	    dwt_configure(&config);

	    /* Apply default antenna delay value. See NOTE 1 below. */
	    dwt_setrxantennadelay(RX_ANT_DLY);
	    dwt_settxantennadelay(TX_ANT_DLY);

	    /* Set expected response's delay and timeout. See NOTE 4, 5 and 6 below.
	     * As this example only handles one incoming frame with always the same delay and timeout, those values can be set here once for all. */
	    dwt_setrxaftertxdelay(POLL_TX_TO_RESP_RX_DLY_UUS);
	    dwt_setrxtimeout(RESP_RX_TIMEOUT_UUS);
	    dwt_setpreambledetecttimeout(PRE_TIMEOUT);
}

void UWB_Anchor_Get_Distance(uwb_data_t *dataPtr, uint8_t anchor)
{

    uint8_t tx_selected_poll[sizeof(tx_poll_msg)];

    switch(anchor)
    {
		case 1:
		{
			memcpy(tx_selected_poll, tx_poll_msg_1, sizeof(tx_poll_msg_1));
			break;
		}
		case 2:
		{
			memcpy(tx_selected_poll, tx_poll_msg_2, sizeof(tx_poll_msg_2));
			break;
		}
		case 3:
		{
			memcpy(tx_selected_poll, tx_poll_msg_3, sizeof(tx_poll_msg_3));
			break;
		}
		case 4:
		{
			memcpy(tx_selected_poll, tx_poll_msg_4, sizeof(tx_poll_msg_4));
			break;
		}
		default:
		{
			break;
		}
    }
    tx_selected_poll[ALL_MSG_SN_IDX] = frame_seq_nb;
    dwt_writetxdata(sizeof(tx_selected_poll), tx_selected_poll, 0); /* Zero offset in TX buffer. */
    dwt_writetxfctrl(sizeof(tx_selected_poll), 0, 1); /* Zero offset in TX buffer, ranging. */

    //tx_poll_msg[ALL_MSG_SN_IDX] = frame_seq_nb;
    //dwt_writetxdata(sizeof(tx_poll_msg), tx_poll_msg, 0); /* Zero offset in TX buffer. */
    //dwt_writetxfctrl(sizeof(tx_poll_msg), 0, 1); /* Zero offset in TX buffer, ranging. */

    /* Start transmission, indicating that a response is expected so that reception is enabled automatically after the frame is sent and the delay
     * set by dwt_setrxaftertxdelay() has elapsed. */
    dwt_starttx(DWT_START_TX_IMMEDIATE | DWT_RESPONSE_EXPECTED);

    /* We assume that the transmission is achieved correctly, poll for reception of a frame or error/timeout. See NOTE 9 below. */
    while (!((status_reg = dwt_read32bitreg(SYS_STATUS_ID)) & (SYS_STATUS_RXFCG | SYS_STATUS_ALL_RX_TO | SYS_STATUS_ALL_RX_ERR)))
    {
  	 dataPtr->debugMsg = 0x15;
    };
    dataPtr->debugMsg = 0x20;
    /* Increment frame sequence number after transmission of the poll message (modulo 256). */
    //TODO: frame_seq_nb++;

    if (status_reg & SYS_STATUS_RXFCG)
    {
        uint32 frame_len;
        dataPtr->debugMsg = 0x69;

        /* Clear good RX frame event and TX frame sent in the DW1000 status register. */
        dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_RXFCG | SYS_STATUS_TXFRS);

        /* A frame has been received, read it into the local buffer. */
        frame_len = dwt_read32bitreg(RX_FINFO_ID) & RX_FINFO_RXFLEN_MASK;
        if (frame_len <= RX_BUF_LEN)
        {
            dwt_readrxdata(rx_buffer, frame_len, 0);
        }

        /* Check that the frame is the expected response from the companion "DS TWR responder" example.
         * As the sequence number field of the frame is not relevant, it is cleared to simplify the validation of the frame. */
        rx_buffer[ALL_MSG_SN_IDX] = 0;
        if (memcmp(rx_buffer, rx_resp_msg, ALL_MSG_COMMON_LEN) == 0)
        {
            uint32 final_tx_time;
            int ret;

            /* Retrieve poll transmission and response reception timestamp. */
            poll_tx_ts = get_tx_timestamp_u64();
            resp_rx_ts = get_rx_timestamp_u64();

            testTagDist = resp_rx_ts - poll_tx_ts;

            //HAL_GPIO_TogglePin(IR_GPIO_Port, IR_Pin);
            /* Compute final message transmission time. See NOTE 10 below. */
            final_tx_time = (resp_rx_ts + (RESP_RX_TO_FINAL_TX_DLY_UUS * UUS_TO_DWT_TIME)) >> 8;
            dwt_setdelayedtrxtime(final_tx_time);

            /* Final TX timestamp is the transmission time we programmed plus the TX antenna delay. */
            final_tx_ts = (((uint64)(final_tx_time & 0xFFFFFFFEUL)) << 8) + TX_ANT_DLY;

            /* Write all timestamps in the final message. See NOTE 11 below. */
            final_msg_set_ts(&tx_final_msg[FINAL_MSG_POLL_TX_TS_IDX], poll_tx_ts);
            final_msg_set_ts(&tx_final_msg[FINAL_MSG_RESP_RX_TS_IDX], resp_rx_ts);
            final_msg_set_ts(&tx_final_msg[FINAL_MSG_FINAL_TX_TS_IDX], final_tx_ts);

            /* Write and send final message. See NOTE 8 below. */
            tx_final_msg[ALL_MSG_SN_IDX] = frame_seq_nb;
            dwt_writetxdata(sizeof(tx_final_msg), tx_final_msg, 0); /* Zero offset in TX buffer. */
            dwt_writetxfctrl(sizeof(tx_final_msg), 0, 1); /* Zero offset in TX buffer, ranging. */
            dwt_write8bitoffsetreg(PMSC_ID, PMSC_CTRL0_OFFSET, PMSC_CTRL0_TXCLKS_125M);
            ret = dwt_starttx(DWT_START_TX_DELAYED);
            //TODO: TU!
            dataPtr->debugMsg = 0x13;
            dataPtr->debugError = ret;

            /* If dwt_starttx() returns an error, abandon this ranging exchange and proceed to the next one. See NOTE 12 below. */
            if (ret == DWT_SUCCESS)
            {

                /* Poll DW1000 until TX frame sent event set. See NOTE 9 below. */
                while (!(dwt_read32bitreg(SYS_STATUS_ID) & SYS_STATUS_TXFRS))
                { };
                HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
                dataPtr->debugMsg = 0x98;
                //HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
                /* Clear TXFRS event. */
                dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_TXFRS);

                /* Increment frame sequence number after transmission of the final message (modulo 256). */
                frame_seq_nb++;
            }
        }
    }
    else
    {
        /* Clear RX error/timeout events in the DW1000 status register. */
        dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_ALL_RX_TO | SYS_STATUS_ALL_RX_ERR);
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, !LED_ACTIVE_STATE);
        dataPtr->debugMsg = 0x03;
        /* Reset RX to properly reinitialise LDE operation. */
        dwt_rxreset();
    }

    /* Execute a delay between ranging exchanges. */
    //Sleep(RNG_DELAY_MS);
}


#endif

void UWB_Send_Data(uint8_t *sourceBuffer, uint16_t size)
{
    dwt_writetxdata(size, sourceBuffer, 0); /* Zero offset in TX buffer. */
    dwt_writetxfctrl(size, 0, 0); /* Zero offset in TX buffer, no ranging. */

    /* Start transmission. */
    dwt_starttx(DWT_START_TX_IMMEDIATE);

    /* Poll DW1000 until TX frame sent event set. See NOTE 5 below.
     * STATUS register is 5 bytes long but, as the event we are looking at is in the first byte of the register, we can use this simplest API
     * function to access it.*/
    while (!(dwt_read32bitreg(SYS_STATUS_ID) & SYS_STATUS_TXFRS))
    { };

    /* Clear TX frame sent event. */
    dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_TXFRS);
}

uint8_t UWB_Get_Data(uint8_t *destBuffer)
{
	uint8_t result = 1;
	uint8_t size = sizeof(destBuffer);
	for(uint8_t cnt = 0; cnt < size; cnt++)
	{
		destBuffer[cnt] = 0;
	}
	dwt_setrxtimeout(5000);
    /* Activate reception immediately. See NOTE 3 below. */
    dwt_rxenable(DWT_START_RX_IMMEDIATE);

    /* Poll until a frame is properly received or an error/timeout occurs. See NOTE 4 below.
     * STATUS register is 5 bytes long but, as the event we are looking at is in the first byte of the register, we can use this simplest API
     * function to access it. */
    while (!((status_reg = dwt_read32bitreg(SYS_STATUS_ID)) & (SYS_STATUS_RXFCG | SYS_STATUS_ALL_RX_ERR | SYS_STATUS_ALL_RX_TO )))
    { };

    if (status_reg & SYS_STATUS_RXFCG)
    {
    	uint16_t frameLength;
        /* A frame has been received, copy it to our local buffer. */
        frameLength = dwt_read32bitreg(RX_FINFO_ID) & RX_FINFO_RXFL_MASK_1023;

        dwt_readrxdata(destBuffer, frameLength, 0);


        /* Clear good RX frame event in the DW1000 status register. */
        dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_RXFCG);
        result = 0;
    }
    else
    {
        /* Clear RX error events in the DW1000 status register. */
        dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_ALL_RX_ERR);
        result = 1;
    }
    return result;
}
#endif
