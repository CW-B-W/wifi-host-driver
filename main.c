#include <string.h>
#include <stdlib.h>
#include "WiFi_Host_Driver/inc/whd.h"
#include "WiFi_Host_Driver/inc/whd_wifi_api.h"
#include "WiFi_Host_Driver/inc/whd_resource_api.h"
#include "WiFi_Host_Driver/inc/whd_types.h"
#include "WiFi_Host_Driver/inc/whd_network_types.h"
#include "WiFi_Host_Driver/inc/whd_events.h"
#include "WiFi_Host_Driver/inc/whd_version.h"

int main()
{
    // Each wifi chip, will have it's own instance of whd_driver.
    // Each whd_driver may use multiple instance of whd_interface_t structs to define behavior and functionality.
    // Most of the WHD function calls take this structure as input.
    // The default primary interface is created automatically at the time of power up of wifi chip, whd_wifi_on(..).
    // Primary interface is STA/AP role neutral.
    // Call whd_init per wifi chip (in other words per bus slot, two SDIO Wifi chip requires two calls.)
    whd_driver_t whd_driver = malloc(sizeof(whd_driver_t));
    whd_init_config_t *whd_init_config = malloc(sizeof(whd_init_config_t));
    whd_resource_source_t *whd_resource_source = malloc(sizeof(whd_resource_source_t));
    whd_buffer_funcs_t *whd_buffer_funcs = malloc(sizeof(whd_buffer_funcs_t));
    whd_netif_funcs_t *whd_netif_funcs = malloc(sizeof(whd_netif_funcs_t));
    whd_init(&whd_driver, whd_init_config, whd_resource_source, whd_buffer_funcs, whd_netif_funcs);
    

    // Attach a bus SDIO or SPI
    whd_sdio_config_t *whd_sdio_cfg = malloc(sizeof(whd_sdio_config_t));
    cyhal_sdio_t *sdhc_obj = malloc(sizeof(cyhal_sdio_t));
    whd_bus_sdio_attach(whd_driver, whd_sdio_cfg, sdhc_obj);
    //or whd_bus_spi_attach(whd_driver, &whd_spi_cfg, &spi_obj);
    
    whd_interface_t ifp = malloc(sizeof(whd_interface_t));
    // Switch on Wifi, download firmware and create a primary interface, returns whd_interface_t
    whd_wifi_on(whd_driver, &ifp);
    
    //11a. Join to AP - Note that it doesn't take whd_driver, instead whd_interface_t
    whd_ssid_t *whd_ssid = malloc(sizeof(whd_ssid_t));
    whd_ssid->length = 7;
    strncpy((char*)whd_ssid->value, "AP SSID", whd_ssid->length + 1);
    uint8_t security_key[] = "AP PASS";
    whd_wifi_join(ifp , whd_ssid, WHD_SECURITY_OPEN, security_key, strlen((const char*)security_key));
    //whd_ifp will be in STA role from now on
    // or 11b. It can an start AP also here, then interface will be in AP role
    //whd_wifi_init_ap(ifp ..)
    //whd_wifi_start_ap(ifp);
    // Leave the AP
    whd_wifi_leave(ifp);
    // or Stop the AP
    //whd_wifi_stop_ap(ifp , ...);
    // Switch off Wifi
    whd_wifi_off(ifp);
    // Detach a bus SDIO or SPI
    whd_bus_sdio_detach(whd_driver);
    //or whd_bus_spi_detach(whd_driver);
    // Deletes all the interface and De-init the whd, free whd_driver memory
    whd_deinit(ifp);
}

// dummy functions to get rid of compilation error due to syscall functions
void _close(void) {}
void _lseek(void) {}
void _read(void) {}
void _write(void) {}
void _fstat_r() {}
void _getpid_r() {}
void _isatty_r() {}
void _kill_r() {}
