#include <stdbool.h>
#include "esp_log.h"
#include "bootloader_init.h"
#include "bootloader_utility.h"

int a =1 ;

static const char *TAG = "boot";
static int load_partition_table(bootloader_state_t *bs);

void __attribute__((noreturn)) call_start_cpu0(void)
{

  // 1. Hardware initialization
    bootloader_init();


    // 2. Load partition table
    bootloader_state_t bs = {0};
    load_partition_table(&bs);

    // 2. Select the number of boot partition
    int boot_index;
    int select_partition = 1;
    ESP_LOGI(TAG, "Select the firmware:");

    while(select_partition == 1){

    if ( a==0) {
            boot_index = 0; //for ota_0
            select_partition = 0;
        }

    if ( a==1) {
            boot_index = 1; //for ota_1
            select_partition = 0;
        }

    }

    ESP_LOGE(TAG, "Load the app image for booting\n");
    // 3. Load the app image for booting
    bootloader_utility_load_boot_image(&bs, boot_index);

}


static int load_partition_table(bootloader_state_t *bs)
{
    // Load partition table
    if (!bootloader_utility_load_partition_table(bs)) {
        ESP_LOGE(TAG, "load partition table error!");
        return INVALID_INDEX;
    }

    // Get selected boot partition
    return bootloader_utility_get_selected_boot_partition(bs);
}

// Return global reent struct if any newlib functions are linked to bootloader
struct _reent *__getreent(void)
{
    return _GLOBAL_REENT;
}
