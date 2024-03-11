#include "driver/twai.h"
#include "freertos/task.h"


void app_main() 
{
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_4, GPIO_NUM_0, TWAI_MODE_NORMAL);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    //Install TWAI driver
    if (twai_driver_install(&g_config, &t_config, &f_config) == ESP_OK) 
    {
        printf("Driver installed\n");
    }
    else 
    {
        printf("Failed to install driver\n");
    }
    if (twai_start() == ESP_OK) 
    {
        printf("Driver started\n");
    }
    else 
    {
        printf("Failed to start driver\n");
    }

    while(1)
    {
        twai_message_t message;

        if (twai_receive(&message, pdMS_TO_TICKS(10000)) == ESP_OK) //tester avec un else message si c'est le nombre de temps qu'il attend pour recevoir avant d'aller au else
        {
            printf("\n\n Message received \n");

            if (message.extd) 
            {
                printf("Message is in Extended Format\n");
            } 
            else 
            {
                printf("Message is in Standard Format\n");
            }
            printf("ID is %ld\n", message.identifier);

            for(int i=0; i< 4; i++)
            {
                printf("%c",(char)message.data[i]);
            }
        }
        else
        {
            printf("\n\n Message wasn't received\n");
        }
    }
}