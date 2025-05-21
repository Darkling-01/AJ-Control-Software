#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"


// Creates the correct bitmask to tell ESP32 to configure pin 13
#define LED_GPIO (1ULL << GIPO_NUM_13);


class App
{

public:

   void setup()
      {
         // Initializes the GPIO to configure safely 
         gpio_config_t myGPIOConfig = {
	       .pin_bit_mask = (LED_GPIO);
               .pull_up_en = 0;
               .pull_down_en = 0;
               .mode = GPIO_MODE_OUTPUT;
               .intr_type = GPIO_INTR_DISABLE;
            };

         gpio_config(&myGPIOConfig);
      }

   void loop()
      {
         gpio_set_level(LED_GPIO, 1);      // ON
         vTaskDelay(pdMS_TO_TICKS(1000));  // Delay for 1 second
         gpio_set_level(LED_GPIO, 0);      // OFF
      }
};

// Entry point for ESP-IDF in C++
// Must use 'extern C' so the ESP-IDF runtime can call it
extern "C" void app_main()
{
   App app;
   app.setup();  // Run once

   while(true)
      {
         app.loop();   // Run repeatedly
      }
}


