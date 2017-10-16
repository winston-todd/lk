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
#include <err.h>
#include <reg.h>
#include <debug.h>
#include <trace.h>
#include <platform.h>
#include <lk/init.h>
#include <sys/types.h>
#include <arch/arch_ops.h>
#include <platform/interrupts.h>
#include <platform/aml_s805.h>
#include <platform/timer.h>
#include <platform/timer_regs.h>
#include <dev/interrupt/arm_gic.h>

#define LOCAL_TRACE 0

typedef struct
{
    uint32_t mux_reg;
    uint32_t reg;
    uint32_t enable_bit;
    uint32_t mode_bit;
    uint32_t clk_bit;
    uint32_t irq;
} aml_s805_timer_t;

static void platform_timer_init_per_cpu(uint level);


static platform_timer_callback callback;
static void* callback_arg;

static const aml_s805_timer_t timer_a = {
        .mux_reg = TIMER_MUX(TIMER0_BASE),
        .reg = TIMER_A(TIMER0_BASE),
        .enable_bit = TIMER_MUX_A_ENABLE,
        .mode_bit = TIMER_MUX_A_MODE,
        .clk_bit = TIMER_MUX_A_CLK_SEL,
        .irq = TIMER_0A_INT
};

static const aml_s805_timer_t timer_b = {
        .mux_reg = TIMER_MUX(TIMER0_BASE),
        .reg = TIMER_B(TIMER0_BASE),
        .enable_bit = TIMER_MUX_B_ENABLE,
        .mode_bit = TIMER_MUX_B_MODE,
        .clk_bit = TIMER_MUX_B_CLK_SEL,
        .irq = TIMER_0B_INT
};

static const aml_s805_timer_t timer_c = {
        .mux_reg = TIMER_MUX(TIMER0_BASE),
        .reg = TIMER_C(TIMER0_BASE),
        .enable_bit = TIMER_MUX_C_ENABLE,
        .mode_bit = TIMER_MUX_C_MODE,
        .clk_bit = TIMER_MUX_C_CLK_SEL,
        .irq = TIMER_0C_INT
};

static const aml_s805_timer_t timer_d = {
        .mux_reg = TIMER_MUX(TIMER0_BASE),
        .reg = TIMER_D(TIMER0_BASE),
        .enable_bit = TIMER_MUX_D_ENABLE,
        .mode_bit = TIMER_MUX_D_MODE,
        .clk_bit = TIMER_MUX_D_CLK_SEL,
        .irq = TIMER_0D_INT
};

static const aml_s805_timer_t* cpu_timers[] = {
        &timer_a, &timer_b, &timer_c, &timer_d
};


void platform_init_timer(void)
{
    LTRACE;

    for(size_t i = 0; i < countof(cpu_timers); ++i)
    {
        RMWREG32(cpu_timers[i]->mux_reg, cpu_timers[i]->enable_bit, 1, 0);
    }

    platform_timer_init_per_cpu(0);

    // Use Timer E as the high-res clock source
    RMWREG32(TIMER_MUX(TIMER0_BASE), TIMER_MUX_E_CLK_SEL, TIEMR_MUX_E_CLK_SEL_WIDTH, TIMER_E_CLK_SEL_1US);
    writel(0, TIMER_E(TIMER0_BASE));
}

status_t platform_set_periodic_timer(platform_timer_callback cb, void *arg, lk_time_t interval)
{
    LTRACE;

    callback = cb;
    callback_arg = arg;

    for(size_t i = 0; i < countof(cpu_timers); ++i)
    {
        const aml_s805_timer_t* timer = cpu_timers[i];

        RMWREG32(timer->mux_reg, timer->enable_bit, 1, 0);
        RMWREG32(timer->mux_reg, timer->mode_bit, 1, TIMER_MODE_PERIODIC);
        RMWREG32(timer->mux_reg, timer->clk_bit, TIMER_MUX_CLK_SEL_WIDTH, TIMER_CLK_SEL_10US);
        RMWREG32(timer->reg, TIMER_LOAD, TIMER_LOAD_WIDTH, interval * 100);
        RMWREG32(timer->mux_reg, timer->enable_bit, 1, 1);
    }
    return NO_ERROR;
}

static enum handler_return platform_tick(void *arg)
{
    if (callback) {
        return callback(arg, current_time());
    } else {
        return INT_NO_RESCHEDULE;
    }
}

lk_time_t current_time(void)
{
    return readl(TIMER_E(TIMER0_BASE)) / 1000;
}

lk_bigtime_t current_time_hires(void)
{
    return readl(TIMER_E(TIMER0_BASE));
}

static void platform_timer_init_per_cpu(uint level)
{
    LTRACEF("level %u cpu %u\n", level, arch_curr_cpu_num());
    u_int cpu = arch_curr_cpu_num();
    const aml_s805_timer_t* timer = cpu_timers[cpu];

    /* route the interrupt to the current cpu */
    arm_gic_set_affinity(timer->irq, (1<<cpu), (1<<cpu));

    /* register the platform tick interrupt */
    register_int_handler(timer->irq, &platform_tick, NULL);
    unmask_interrupt(timer->irq);
}

/* secondary cpu initialize the timer just before the kernel starts with interrupts enabled */
LK_INIT_HOOK_FLAGS(platform_timer_init_per_cpu,
                   platform_timer_init_per_cpu,
                   LK_INIT_LEVEL_THREADING - 1, LK_INIT_FLAG_SECONDARY_CPUS);

