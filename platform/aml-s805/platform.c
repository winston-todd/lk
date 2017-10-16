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
#include <debug.h>
#include <platform.h>
#include <platform/aml_s805.h>
#include <platform/gpio.h>
#include <kernel/vm.h>
#include <dev/interrupt/arm_gic.h>
#include <target/debugconfig.h>

/* initial memory mappings. parsed by start.S */
struct mmu_initial_mapping mmu_initial_mappings[] = {
    /* 1GB of sdram space */
    {
        .phys = MEMBASE,
        .virt = KERNEL_BASE,
		.size = MEMSIZE,
        .flags = 0,
        .name = "memory"
    },

    /* peripherals */
    {
        .phys = 0xC0000000,
        .virt = 0xC0000000,
        .size = 0x1A008000,
        .flags = MMU_INITIAL_MAPPING_FLAG_DEVICE,
        .name = "periphs"
    },

    /* identity map to let the boot code run */
    {
        .phys = 0,
        .virt = 0,
        .size = MEMSIZE,
        .flags = MMU_INITIAL_MAPPING_TEMPORARY
    },

    /* null entry to terminate the list */
    { 0 }
};

static pmm_arena_t sdram_arena = {
    .name = "sdram",
    .base = 0,
    .size = MEMSIZE,
    .flags = PMM_ARENA_FLAG_KMAP
};

extern void arm_reset(void);

void platform_init_mmu_mappings(void)
{
}

void platform_early_init(void)
{
	/* initialize the interrupt controller */
    arm_gic_init();

    for(u_int i = 32; i < MAX_INT; i++)
    {
        arm_gic_set_int_trigger(i, ARM_GIC_INT_EDGE_TRIGGERED);
        arm_gic_set_int_model(i, ARM_GIC_INT_MODEL_N_N);
    }

    platform_init_timer();

    pmm_add_arena(&sdram_arena);

    /* start the other cpus */
    uintptr_t sec_entry = (uintptr_t)&arm_reset;
    sec_entry -= (KERNEL_BASE - MEMBASE);
    for (uint cpu = 1; cpu < SMP_MAX_CPUS; cpu++)
    {
        dprintf(SPEW, "powering on cpu %u\n", cpu);
        writel(sec_entry, CPU_CONTROL_ADDR(cpu));

        RMWREG32(CPU_POWER, cpu << 3, 2, 0);
        RMWREG32(A5_ISOLATION, ((2*cpu) + 16), 2, 0);
        // reset the cpu
        RMWREG32(HHI_SYS_CPU_CLK_CNTL0, cpu + 24, 1, 1);
        RMWREG32(A5_RAM_POWER_CNTL0, 32 - (cpu * 4), 4, 0);
        RMWREG32(A5_POWER, ((cpu + 1) << 1), 2, 0);
        spin(10);

        while(!(readl(A5_POWER) & (1<<(cpu + 16))))
        {
            spin(10);
        }

        RMWREG32(A5_ISOLATION, cpu, 1, 0);
        // reset the cpu
        RMWREG32(HHI_SYS_CPU_CLK_CNTL0, cpu + 24, 1, 0);
        RMWREG32(CPU_POWER, cpu << 3, 2, 0);

        writel(sec_entry, CPU_CONTROL_ADDR(cpu));
        RMWREG32(CPU_CONTROL, cpu, 1, 1);
        RMWREG32(CPU_CONTROL, 0, 1, 1);
    }
}

void platform_init(void)
{

}


