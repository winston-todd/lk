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
#include <platform/gpio.h>
#include <dev/gpio.h>
#include <assert.h>

static const uint32_t gpio_reg_oen[GPIO_BANK_COUNT] = {
		[GPIO_BANK_X]  = GPIO_BANK_X_OEN,
		[GPIO_BANK_Y]  = GPIO_BANK_Y_OEN,
		[GPIO_BANK_DV] = GPIO_BANK_DV_OEN,
		[GPIO_BANK_H]  = GPIO_BANK_H_OEN,
		[GPIO_BANK_AO] = GPIO_BANK_AO_OEN
};

static const uint32_t gpio_reg_in[GPIO_BANK_COUNT] = {
		[GPIO_BANK_X]  = GPIO_BANK_X_IN,
		[GPIO_BANK_Y]  = GPIO_BANK_Y_IN,
		[GPIO_BANK_DV] = GPIO_BANK_DV_IN,
		[GPIO_BANK_H]  = GPIO_BANK_H_IN,
		[GPIO_BANK_AO] = GPIO_BANK_AO_IN
};

static const uint32_t gpio_reg_out[GPIO_BANK_COUNT] = {
		[GPIO_BANK_X]  = GPIO_BANK_X_OUT,
		[GPIO_BANK_Y]  = GPIO_BANK_Y_OUT,
		[GPIO_BANK_DV] = GPIO_BANK_DV_OUT,
		[GPIO_BANK_H]  = GPIO_BANK_H_OUT,
		[GPIO_BANK_AO] = GPIO_BANK_AO_OUT
};

static int gpio_map(unsigned nr, unsigned* bank, unsigned *num)
{
	if (nr <= GPIOX_END)
	{
		*bank = GPIO_BANK_X;
		*num = nr - GPIOX_0;
	}
	else if (nr <= GPIOY_END)
	{
		*bank = GPIO_BANK_Y;
		*num = nr - GPIOY_0;
	}
	else if (nr <= GPIODV_END)
	{
		*bank = GPIO_BANK_DV;

		if (nr == GPIODV_9)
		{
			*num = 9;
		}
		else
		{
			*num = 24 + (nr - GPIODV_24);
		}
	}
	else if (nr <= GPIOH_END)
	{
		*bank = GPIO_BANK_H;
		*num = nr - GPIOH_0;
	}
	else if (nr <= GPIOAO_END)
	{
		*bank = GPIO_BANK_AO;
		*num = nr - GPIOAO_0;
	}
	else
	{
		return -1;
	}

	return 0;
}

static inline uint32_t gpio_out_mask(unsigned bank, unsigned num)
{
	uint32_t mask;

	if (bank == GPIO_BANK_H)
	{
		mask = (1<<(num+19));
	}
	else if (bank == GPIO_BANK_AO)
	{
		mask = (1u<<(num+16));
	}
	else
	{
		mask = (1<<num);
	}

	return mask;
}

static inline uint32_t gpio_in_mask(unsigned bank, unsigned num)
{
	uint32_t mask;

	if (bank == GPIO_BANK_H)
	{
		mask = (1<<(num+19));
	}
	else
	{
		mask = (1<<num);
	}

	return mask;
}

static inline uint32_t gpio_oen_mask(unsigned bank, unsigned num)
{
	uint32_t mask;

	if (bank == GPIO_BANK_H)
	{
		mask = (1<<(num+19));
	}
	else
	{
		mask = (1<<num);
	}

	return mask;
}

int gpio_config(unsigned nr, unsigned flags)
{
	DEBUG_ASSERT(nr < MAX_GPIO);

	unsigned bank, num;

	if (gpio_map(nr, &bank, &num) != 0)
	{
		return -1;
	}

	if ((flags & GPIO_OUTPUT) != 0)
	{
		*REG32(gpio_reg_oen[bank]) &= ~gpio_oen_mask(bank, num);
	}
	else if ((flags & GPIO_INPUT) != 0)
	{
		*REG32(gpio_reg_oen[bank]) |= gpio_oen_mask(bank, num);
	}

	return 0;
}

void gpio_set(unsigned nr, unsigned on)
{
	DEBUG_ASSERT(nr < MAX_GPIO);

	unsigned bank, num;

	if (gpio_map(nr, &bank, &num) == 0)
	{
		if (on != 0)
		{
			*REG32(gpio_reg_out[bank]) |= gpio_out_mask(bank, num);
		}
		else
		{
			*REG32(gpio_reg_out[bank]) &= ~gpio_out_mask(bank, num);
		}
	}
}

int gpio_get(unsigned nr)
{
	DEBUG_ASSERT(nr < MAX_GPIO);

	unsigned bank, num;

	if (gpio_map(nr, &bank, &num) != 0)
	{
		return -1;
	}

	return ((*REG32(gpio_reg_in[bank])) & gpio_out_mask(bank, num));
}


