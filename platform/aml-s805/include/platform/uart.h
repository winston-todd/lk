/*
 * Copyright (c) 2017 Winston Todd
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once

#include <reg.h>
#include <platform/aml_s805.h>

#define UART0_BASE                 CBUS_REG(0x2130)
#define UART1_BASE                 CBUS_REG(0x2137)
#define UART2_BASE                 CBUS_REG(0x21C0)
#define UART0_AO_BASE              0xC81004C0
#define UART2_AO_BASE              0xC81004E0

#define UART_REG(base,reg)         ((base) + ((reg) << 2))

#define UART_WFIFO(base)           UART_REG((base), 0)
#define UART_RFIFO(base)           UART_REG((base), 1)
#define UART_CONTROL(base)         UART_REG((base), 2)
#define UART_STATUS(base)          UART_REG((base), 3)
#define UART_MISC(base)            UART_REG((base), 4)

#define UART_CONTROL_CLEAR_ERROR   (1<<24)

#define UART_STATUS_TX_FIFO_EMPTY  (1<<22)
#define UART_STATUS_TX_FIFO_FULL   (1<<21)
#define UART_STATUS_RX_FIFO_EMPTY  (1<<20)
#define UART_STATUS_RX_FIFO_FULL   (1<<19)
#define UART_STATUS_ERR_OVERFLOW   (1<<18)
#define UART_STATUS_ERR_FRAME      (1<<17)
#define UART_STATUS_ERR_PARITY     (1<<16)
#define UART_STATUS_TX_FIFO_COUNT_SHIFT  (8)
#define UART_STATUS_TX_FIFO_COUNT_MASK   (0x7f)
#define UART_STATUS_RX_FIFO_COUNT_SHIFT  (0)
#define UART_STATUS_RX_FIFO_COUNT_MASK   (0x7f)

#define UART_RX_FIFO_COUNT(base) \
    ((readl(UART_STATUS(base)) >> \
        UART_STATUS_RX_FIFO_COUNT_SHIFT) & \
        UART_STATUS_RX_FIFO_COUNT_MASK)

#define UART_TX_FIFO_COUNT(base) \
    ((readl(UART_STATUS(base)) >> \
        UART_STATUS_TX_FIFO_COUNT_SHIFT) & \
        UART_STATUS_TX_FIFO_COUNT_MASK)

