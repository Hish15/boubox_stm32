
#include "pin.hpp"

#include <stm32f4xx_hal.h>

const GPIO_InitTypeDef conf_out_no_pull = {
    .Mode = GPIO_MODE_OUTPUT_PP,
    .Pull = GPIO_NOPULL,
    .Speed = GPIO_SPEED_HIGH};
const GPIO_InitTypeDef conf_in={
    .Mode = GPIO_MODE_INPUT,
    .Pull = GPIO_NOPULL,
    .Speed = GPIO_SPEED_HIGH};
Pin red_led(
    GPIOG,
    GPIO_PIN_14,
    [](){__HAL_RCC_GPIOG_CLK_ENABLE();},
    conf_out_no_pull);
Pin green_led(
    GPIOG,
    GPIO_PIN_13,
    [](){__HAL_RCC_GPIOG_CLK_ENABLE();},
    conf_out_no_pull);

//This prevent name mangling for functions used in C/assembly files.
extern "C"
{
    void SysTick_Handler(void)
    {
        HAL_IncTick();

        // 1 Hz blinking
        if ((HAL_GetTick() % 500) == 0)
        {
            HAL_GPIO_TogglePin(green_led.port, green_led.pin);
            HAL_GPIO_TogglePin(red_led.port, red_led.pin);
        }
    }
}

int main(void)
{
    HAL_Init();
    // 1kHz ticks
    HAL_GPIO_WritePin(green_led.port, green_led.pin, GPIO_PIN_SET);
    HAL_SYSTICK_Config(SystemCoreClock / 1000);

    while(1);
    return 0;
}
