#include "ets_sys.h"
#include "driver/uart.h"
#include "i2c/i2c.h"
#include "i2c_hd44780/i2c_hd44780.h"
#include "osapi.h"
#include "os_type.h"
#include "user_interface.h"
#include "config.h"
#include "user_display.h"
#include "user_buttons.h"
#include "user_network.h"


os_event_t    user_procTaskQueue[user_procTaskQueueLen];

static void user_procTask(os_event_t *events);

static void ICACHE_FLASH_ATTR
user_procTask(os_event_t *events)
{
}

void user_init(void)
{
    char ssid[32] = SSID;
    char password[64] = SSID_PASSWORD;
    struct station_config stationConf;

    system_timer_reinit();
    uart_init(BIT_RATE_115200, BIT_RATE_115200);

    os_memcpy(&stationConf.ssid, ssid, 32);
    os_memcpy(&stationConf.password, password, 32);

    //Setup wifi
    wifi_set_opmode( 0x1 );
    wifi_set_phy_mode(PHY_MODE_11N);
    wifi_station_set_config(&stationConf);

    network_init();
    display_init();
    buttons_init();
    
    os_printf("\n\rStartup done\n\r");

    system_os_task(user_procTask, user_procTaskPrio,user_procTaskQueue, user_procTaskQueueLen);
}

