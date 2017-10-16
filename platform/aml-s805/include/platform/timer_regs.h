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

#define WATCHDOG_BASE           CBUS_REG(0x2640)
#define TIMER0_BASE             CBUS_REG(0x2650)
#define TIMER1_BASE             CBUS_REG(0x2664)


#define TIMER_REG(base, x)      ((base) + ((x)<<2))

#define TIMER_MUX(base)         TIMER_REG(base, 0)
#define TIMER_A(base)           TIMER_REG(base, 1)
#define TIMER_B(base)           TIMER_REG(base, 2)
#define TIMER_C(base)           TIMER_REG(base, 3)
#define TIMER_D(base)           TIMER_REG(base, 4)
#define TIMER_E(base)           TIMER_REG(base, 5)

#define TIMER_LOAD                 0
#define TIMER_COUNT                16
#define TIMER_LOAD_WIDTH           16
#define TIMER_COUNT_WIDTH          16

#define TIMER_MUX_A_CLK_SEL        0
#define TIMER_MUX_B_CLK_SEL        2
#define TIMER_MUX_C_CLK_SEL        4
#define TIMER_MUX_D_CLK_SEL        6
#define TIMER_MUX_E_CLK_SEL        8

#define TIMER_MUX_CLK_SEL_WIDTH    2
#define TIEMR_MUX_E_CLK_SEL_WIDTH  3

#define TIMER_MUX_A_MODE           12
#define TIMER_MUX_B_MODE           13
#define TIMER_MUX_C_MODE           14
#define TIMER_MUX_D_MODE           15

#define TIMER_MUX_A_ENABLE         16
#define TIMER_MUX_B_ENABLE         17
#define TIMER_MUX_C_ENABLE         18
#define TIMER_MUX_D_ENABLE         19

#define TIMER_MODE_ONE_SHOT        0
#define TIMER_MODE_PERIODIC        1

#define TIMER_CLK_SEL_1US          0
#define TIMER_CLK_SEL_10US         1
#define TIMER_CLK_SEL_100US        2
#define TIMER_CLK_SEL_1000US       3

#define TIMER_E_CLK_SEL_SYS        0
#define TIMER_E_CLK_SEL_1US        1
#define TIMER_E_CLK_SEL_10US       2
#define TIMER_E_CLK_SEL_100US      3
#define TIMER_E_CLK_SEL_1000US     4



