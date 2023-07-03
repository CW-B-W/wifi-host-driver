#include "cyhal_gpio.h"

cy_rslt_t cyhal_gpio_init(cyhal_gpio_t pin, cyhal_gpio_direction_t direction, cyhal_gpio_drive_mode_t drvMode, bool initVal)
{
    return 0;
}

void cyhal_gpio_irq_enable(cyhal_gpio_t pin, cyhal_gpio_irq_event_t event, bool enable)
{
    return;
}

void cyhal_gpio_register_irq(cyhal_gpio_t pin, uint8_t intrPriority, cyhal_gpio_irq_handler_t handler,
                             void *handler_arg)
{
    return;
}