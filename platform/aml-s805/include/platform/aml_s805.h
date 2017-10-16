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

#define CBUS_BASE               0xC1100000
#define CBUS_REG(x)             (CBUS_BASE + ((x) << 2))

#define AOBUS_BASE              0xC8100000
#define AOBUS_REG(x)            (AOBUS_BASE + (x))

#define PERIPH_BASE             0xC4300000
#define SRAM_BASE               0xD9000000

#define HHI_SYS_CPU_CLK_CNTL0   CBUS_REG(0x1067)
#define WATCHDOG_TC             CBUS_REG(0x2640)
#define WATCHDOG_RESET          CBUS_REG(0x2641)


#define A5_ISOLATION            AOBUS_REG(0xe0)
#define A5_POWER                AOBUS_REG(0xe4)
#define A5_RAM_POWER_CNTL0      AOBUS_REG(0xf4)
#define A5_RAM_POWER_CNTL1      AOBUS_REG(0xf8)
#define AO_PWR_CNTL0            AOBUS_REG(0x10)
#define AO_PWR_CNTL1            AOBUS_REG(0x0c)


#define CPU_CONTROL             (SRAM_BASE + 0x1FF80)
#define CPU_CONTROL_ADDR(cpu)   (SRAM_BASE + 0x1FF84 + ((cpu-1)<<2))
#define CPU_STATUS(cpu)         (SRAM_BASE + 0x1FF90 + (cpu<<2))
#define CPU_POWER               (PERIPH_BASE + 0x8)



#define WATCHDOG_INT            32
#define HIU_MAILBOX_INT         33
#define HSYNC_INT               34
#define VSYNC_INT               35
#define ETH_PMT_INT             36
#define DEMUX_INT               37
#define TIMER_0C_INT            38
#define AUDIN_INT               39
#define ETH_GMAC_INT            40
#define TIMER_0A_INT            42
#define TIMER_0B_INT            43

#define TIMER_0D_INT            61
#define MAX_INT                 217

#define TIMER_CLOCK_FREQ        50000000


void platform_init_timer(void);
