// Copyright (C) 2003-2015 swengLab Technologies - All rights reserved
// Siebenbürgerstrasse 16-26/26/17, A--1220 Vienna, Austria. 
// Author: Dr. SMAILI Idriz   smaili.idriz@gmail.com
//
//++
// Name
//    @file uart.h
//
// Purpose
//    @brief Implements the routine needed to handle the ADC  
//
// Author
//    @author: Dr. Dipl.-Ing. Idriz SMAILI, smaili.idriz@gmail.com
//    $Author: smaili $
//
// Revision Dates
//    2017-12-28 (smaili): Initial version
//    $Log: uart.h $
//--

#ifndef __UART__H
#define __UART__H 1

#include <avr/io.h> 

#include "r_buffer.h"

/*
 * Declarations of UART MACROS
 */
#define UART_INVALID_CHANNEL 0x30

/*
 * Declarations of UART no of channels
 */
#if defined (UART_USE_CH1)
#define UART_NO_CHANNELS 2
#define UART_CHANNEL_0   0
#define UART_CHANNEL_1   1
#else
#define UART_CHANNEL_0   0
#define UART_NO_CHANNELS 1
#endif

/*
 * Declarations of UART prescaler div factors
 */
#define FOSC           1843200

#if !defined (BAUD0)
#error "The uart baudrate for the UART channel 0 has to be specified"
#endif

#define BAUD0_PRESCALE FOSC / 16 / BAUD0 - 1

#if defined (UART_USE_CH1)
#if !defined (BAUD1)
#error "The uart baudrate for the UART channel 1 has to be specified"
#endif
#define BAUD1_PRESCALE FOSC / 16 / BAUD1 - 1
#endif

/*
 * Declarations of UART macros
 */
#define UART_INIT_CHANNEL(ubrr, ch)\
  /* Set baud rate */ \
  UBRR##ch##H = (uint8_t) (ubrr >> 8);\
  UBRR##ch##L = (uint8_t) ubrr;\
\
  /* Enable receiver and transmitter */ \
  UCSR##ch##B = (1 << RXEN##ch) | (1 << TXEN##ch); \
\
  /* Set frame format: 8data, 2stop bit */     \
  UCSR##ch##C = (1 << USBS) | (3 << UCSZ##ch); \
\
  /* Enable the uart Recieve Complete interrupt (uart_RXC) */\
  UCSR##ch##B |= (1 << RXCIE##ch);\

#define UART_ENABLE_INT(ch)                \
  do \
    { \
      UCSR##ch##B |= (1 << RXCIE##ch) | (1 << TXCIE##ch);     \
    } \
  while (0);\

#define UART_DISABLE_INT(ch)\
  UCSR##ch##B &= ~(1 << RXCIE##ch) | (1 << TXCIE##ch) \

#define UART_SEND(ch, data)\
    /* Wait for empty transmit buffer */\
    while (!(UCSR##ch##A & (1 << UDRE##ch)))\
        ;\
    /* Put data into buffer, sends the data */  \
    UDR##ch = data;\

/*
 * Declarations of ADC's members
 */
void              uart_init     (uint16_t ubrr0, uint16_t ubrr);
volatile
r_buffer_t *const uart_get_rbuf (uint8_t  chan);
uint8_t           uart_send     (uint8_t  chan, uint8_t  data);
uint8_t           uart_receive  (uint8_t  chan, uint8_t *buf, uint8_t b_len,
                                  uint8_t *const rx_len);

 /* Declaration of interrupt rx service routine for the UART#0
 */
void ISR(USART0_RX_vect);

#if defined (UART_USE_CH1)
void ISR(USART1_RX_vect);
#endif

#endif /* __UART__H */
