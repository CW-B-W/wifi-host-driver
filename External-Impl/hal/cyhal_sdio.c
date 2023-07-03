#include "cyhal_sdio.h"

cy_rslt_t cyhal_sdio_bulk_transfer(cyhal_sdio_t *obj, cyhal_transfer_t direction, uint32_t argument,
                                   const uint32_t *data, uint16_t length, uint32_t *response)
{
    return 0;
}

void cyhal_sdio_irq_enable(cyhal_sdio_t *obj, cyhal_sdio_irq_event_t event, bool enable)
{
    return;
}

void cyhal_sdio_register_irq(cyhal_sdio_t *obj, cyhal_sdio_irq_handler_t handler, void *handler_arg)
{
    return;
}

cy_rslt_t cyhal_sdio_send_cmd(const cyhal_sdio_t *obj, cyhal_transfer_t direction, cyhal_sdio_command_t command,
                              uint32_t argument, uint32_t *response)
{
    return 0;
}