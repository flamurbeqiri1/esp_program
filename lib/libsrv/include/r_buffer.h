// Copyright (C) 2003-2015 swengLab Technologies - All rights reserved
// Siebenbürgerstrasse 16-26/26/17, A--1220 Vienna, Austria. 
// Author: Dr. SMAILI Idriz   smaili.idriz@gmail.com
//
//++
// Name
//    @file r_buffer.h
//
// Purpose
//    @brief Implements the ring buffer data structure
//
// Author
//    @author: Dr. Dipl.-Ing. Idriz SMAILI, smaili.idriz@gmail.com
//    $Author: smaili $
//
// Revision Dates
//    2017-01-02 (smaili): Initial version
//    $Log: r_buffer.h $
//--

#ifndef __R_BUFFER__H
#define __R_BUFFER__H 1

#include "esp_types.h"

/*
 * Declarations of r_buffer's size
 */
#define RBUF_SIZE                30 
/*
 * Declarations of r_buffer's error codes
 */
#define RBUF_NO_ERROR            0x01
#define RBUF_EMPTY               0x02
#define RBUF_OVERFLOW            0x04

/*
 * Definition of the r_buffer data structure 
 */
typedef struct _r_buffer
{
  uint8_t n_elm;
  uint8_t pop_idx;
  uint8_t push_idx;
  uint8_t errno;

  uint8_t buf [RBUF_SIZE];
} r_buffer_t;

/*
 * Declarations of ring buffer's members
 */
void    rbuf_init (volatile r_buffer_t *const r_buf);
void    rbuf_push (volatile r_buffer_t *const r_buf, uint8_t        data);
uint8_t rbuf_pop  (volatile r_buffer_t *const r_buf, uint8_t *const data);

#endif /* __R_BUFFER__H */ 
