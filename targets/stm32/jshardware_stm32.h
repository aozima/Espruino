/*
 * This file is part of Espruino, a JavaScript interpreter for Microcontrollers
 *
 * Copyright (C) 2013 Gordon Williams <gw@pur3.co.uk>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * ----------------------------------------------------------------------------
 * Hardware interface Layer bits that are specific to STM32
 * These are still defined in jshardware.c
 * ----------------------------------------------------------------------------
 */

#ifndef JSHARDWARE_STM32_H_
#define JSHARDWARE_STM32_H_

#include "platform_config.h"

#if defined(STM32F3)
// stupid renamed stuff
#define EXTI2_IRQn EXTI2_TS_IRQn
#define GPIO_Mode_AIN GPIO_Mode_AN
// see _gpio.h
#define GPIO_AF_USART1 GPIO_AF_7
#define GPIO_AF_USART2 GPIO_AF_7
#define GPIO_AF_USART3 GPIO_AF_7
#define GPIO_AF_UART4 GPIO_AF_5
#define GPIO_AF_UART5 GPIO_AF_5
#define GPIO_AF_USART6 GPIO_AF_0 // FIXME is this right?
#define GPIO_AF_SPI1 GPIO_AF_5
#define GPIO_AF_SPI2 GPIO_AF_5
#endif

#if !defined(STM32F3)
#define SPI_I2S_ReceiveData16 SPI_I2S_ReceiveData
#define SPI_I2S_SendData16 SPI_I2S_SendData
#endif

typedef enum {
  JSH_SPI_CONFIG_NONE = 0,
  JSH_SPI_CONFIG_RECEIVE_DATA = 1,
  JSH_SPI_CONFIG_16_BIT = 2, // 16 bit send - receive not implemented at the moment
} PACKED_FLAGS JSH_SPI_FLAGS;
extern JSH_SPI_FLAGS jshSPIFlags[SPIS];

static inline bool jshSPIGetFlag(IOEventFlags device, JSH_SPI_FLAGS flag) {
  assert(DEVICE_IS_SPI(device));
  return (jshSPIFlags[device - EV_SPI1] & flag) != 0;
}

static inline void jshSPISetFlag(IOEventFlags device, JSH_SPI_FLAGS flag, bool state) {
  assert(DEVICE_IS_SPI(device));
  JSH_SPI_FLAGS *f = &jshSPIFlags[device - EV_SPI1];
  if (state)
    *f = (JSH_SPI_FLAGS)(*f | flag);
  else
    *f = (JSH_SPI_FLAGS)(*f & ~flag);
}

#endif // JSHARDWARE_STM32_H_
