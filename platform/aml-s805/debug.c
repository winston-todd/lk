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
#include <stdarg.h>
#include <reg.h>
#include <stdio.h>
#include <kernel/thread.h>
#include <platform/aml_s805.h>
#include <platform/debug.h>
#include <target/debugconfig.h>
#include <dev/uart.h>

void platform_dputc(char c)
{
    if (c == '\n') uart_putc(DEBUG_UART, '\r');
	uart_putc(DEBUG_UART, c);
}

int platform_dgetc(char *c, bool wait)
{
    *c = uart_getc(DEBUG_UART, wait);
    return 0;
}

void platform_halt(void)
{
    writel(0, WATCHDOG_RESET);
    writel((10|((1<<19)| (0xf<<24))), WATCHDOG_TC);
    for (;;);
}

void debug_set_trace_level(int trace_type, int level)
{
}

uint32_t debug_cycle_count(void)
{
    return 0;
}
