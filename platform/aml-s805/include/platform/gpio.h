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

#include <platform/aml_s805.h>
#include <dev/gpio.h>


#define GPIO_BANK_X_OEN              CBUS_REG(0x200C)
#define GPIO_BANK_X_OUT              CBUS_REG(0x200D)
#define GPIO_BANK_X_IN               CBUS_REG(0x200E)
#define GPIO_BANK_X_PUPD             CBUS_REG(0x203E)
#define GPIO_BANK_X_PUPD_EN          CBUS_REG(0x204C)

#define GPIO_BANK_Y_OEN              CBUS_REG(0x200F)
#define GPIO_BANK_Y_OUT              CBUS_REG(0x2010)
#define GPIO_BANK_Y_IN               CBUS_REG(0x2011)
#define GPIO_BANK_Y_PUPD             CBUS_REG(0x203D)
#define GPIO_BANK_Y_PUPD_EN          CBUS_REG(0x204B)

#define GPIO_BANK_DV_OEN             CBUS_REG(0x2012)
#define GPIO_BANK_DV_OUT             CBUS_REG(0x2013)
#define GPIO_BANK_DV_IN              CBUS_REG(0x2014)

#define GPIO_BANK_H_OEN              CBUS_REG(0x2015)
#define GPIO_BANK_H_OUT              CBUS_REG(0x2016)
#define GPIO_BANK_H_IN               CBUS_REG(0x2017)

#define GPIO_BANK_AO_OEN             AOBUS_REG(0x0024)
#define GPIO_BANK_AO_OUT             AOBUS_REG(0x0024)
#define GPIO_BANK_AO_IN              AOBUS_REG(0x0028)


enum
{
	GPIO_BANK_X,
	GPIO_BANK_Y,
	GPIO_BANK_DV,
	GPIO_BANK_H,
	GPIO_BANK_AO,
	GPIO_BANK_COUNT
};

enum
{
	GPIOX_0 = 0,
	GPIOX_1,
	GPIOX_2,
	GPIOX_3,
	GPIOX_4,
	GPIOX_5,
	GPIOX_6,
	GPIOX_7,
	GPIOX_8,
	GPIOX_9,
	GPIOX_10,
	GPIOX_11,
	GPIOX_12,
	GPIOX_13,
	GPIOX_14,
	GPIOX_15,
	GPIOX_16,
	GPIOX_17,
	GPIOX_18,
	GPIOX_19,
	GPIOX_20,
	GPIOX_21,
	GPIOX_END = GPIOX_21,

	GPIOY_0,
	GPIOY_1,
	GPIOY_2,
	GPIOY_3,
	GPIOY_4,
	GPIOY_5,
	GPIOY_6,
	GPIOY_7,
	GPIOY_8,
	GPIOY_9,
	GPIOY_10,
	GPIOY_11,
	GPIOY_12,
	GPIOY_13,
	GPIOY_14,
	GPIOY_END = GPIOY_14,

	GPIODV_9,
	GPIODV_24,
	GPIODV_25,
	GPIODV_26,
	GPIODV_27,
	GPIODV_28,
	GPIODV_29,
	GPIODV_END = GPIODV_29,

	GPIOH_0,
	GPIOH_1,
	GPIOH_2,
	GPIOH_3,
	GPIOH_4,
	GPIOH_5,
	GPIOH_6,
	GPIOH_7,
	GPIOH_8,
	GPIOH_9,
	GPIOH_END = GPIOH_9,

	GPIOAO_0,
	GPIOAO_1,
	GPIOAO_2,
	GPIOAO_3,
	GPIOAO_4,
	GPIOAO_5,
	GPIOAO_6,
	GPIOAO_7,
	GPIOAO_8,
	GPIOAO_9,
	GPIOAO_10,
	GPIOAO_11,
	GPIOAO_12,
	GPIOAO_13,
	GPIOAO_END = GPIOAO_13,

	MAX_GPIO
};
