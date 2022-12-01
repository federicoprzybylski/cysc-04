#include "pico/stdlib.h"
#include <stdio.h>
#include "ultrasonic.h"
#include "hardware/pwm.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"


int main()
{
  stdio_init_all();
  gpio_init (22);
  gpio_set_dir (22, true);
  gpio_init (21);
  gpio_set_dir (21, true);
  gpio_init (20);
  gpio_set_dir (20, true);
  gpio_init (19);
  gpio_set_dir (19, true);
  gpio_set_function(9, GPIO_FUNC_PWM);
  gpio_set_function(8, GPIO_FUNC_PWM);
  gpio_set_function(10, GPIO_FUNC_PWM);
  gpio_set_function(11, GPIO_FUNC_PWM);
  uint8_t slice_num = pwm_gpio_to_slice_num(9);
  uint8_t slice_num1 = pwm_gpio_to_slice_num(10);
  pwm_config config = pwm_get_default_config();
  pwm_init(slice_num, &config, true);
  pwm_init(slice_num1, &config, true);
  pwm_set_gpio_level(8, 0x3fff);
  pwm_set_gpio_level(9, 0x3fff);
  pwm_set_gpio_level(10, 0x3fff);
  pwm_set_gpio_level(11, 0x03fff);
  gpio_put(19, true);
}