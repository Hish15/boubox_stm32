#pragma once
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_gpio.h>

#include <cstdint>
struct Pin {
    GPIO_TypeDef* port;
    uint16_t pin;
    void (*clkEnable)();
    GPIO_InitTypeDef GPIO_Config;
    Pin(GPIO_TypeDef* port,
        uint16_t pin,
        void (*clkEnable)(),
        const GPIO_InitTypeDef& config)
        : port(port), pin(pin), clkEnable(clkEnable), GPIO_Config(config)
    {
        HAL_Init();
        GPIO_Config.Pin = pin;
        clkEnable();
        HAL_GPIO_Init(port, &GPIO_Config);
    }

};