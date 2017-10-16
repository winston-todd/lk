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
#include <reg.h>
#include <bits.h>
#include <stdio.h>
#include <trace.h>
#include <assert.h>
#include <lib/cbuf.h>
#include <kernel/thread.h>
#include <kernel/spinlock.h>
#include <platform/interrupts.h>
#include <platform/debug.h>
#include <platform/uart.h>


static uint32_t aml_uart_base[] = {
        UART0_AO_BASE,
        UART1_BASE,
        UART2_BASE
};


void uart_init_early(void)
{

}

void uart_init(void)
{

}


int uart_putc(int port, char c)
{
    DEBUG_ASSERT((size_t)port < countof(aml_uart_base));

    uint32_t base = aml_uart_base[port];

    while (readl(UART_STATUS(base)) & UART_STATUS_TX_FIFO_FULL);

    writel(c, UART_WFIFO(base));
    return 0;
}

int uart_getc(int port, bool wait)
{
    DEBUG_ASSERT((size_t)port < countof(aml_uart_base));

    uint32_t base = aml_uart_base[port];
    char c;

    while(readl(UART_STATUS(base)) & UART_STATUS_RX_FIFO_EMPTY)
    {
        if (!wait)
        {
            return -1;
        }
    }

    c = (readl(UART_RFIFO(base)) & 0xFF);

    // check for errors
    if (readl(UART_STATUS(base)) &
            (UART_STATUS_ERR_FRAME | UART_STATUS_ERR_OVERFLOW | UART_STATUS_ERR_PARITY))
    {
        // clear errors
        writel(readl(UART_STATUS(base)) | UART_CONTROL_CLEAR_ERROR, UART_STATUS(base));
        writel(readl(UART_STATUS(base)) & ~UART_CONTROL_CLEAR_ERROR, UART_STATUS(base));
    }

    return c;
}

void uart_flush_tx(int port)
{

}

void uart_flush_rx(int port)
{

}

void uart_init_port(int port, uint baud)
{

}

/* panic-time uart accessors, intended to be run with interrupts disabled */
int uart_pputc(int port, char c)
{
    return 0;
}

int uart_pgetc(int port)
{
    return 0;
}





