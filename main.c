#include "pico/stdlib.h"
#include <stdio.h>
#include "ultrasonic.h"
#include "hardware/pwm.h"

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
  int x = 1;
  bool repeating_timer_callback(struct repeating_timer *t) {
    if (x % 2 == 0){
      pwm_set_gpio_level(9, 0xffff);
      pwm_set_gpio_level(11, 0xffff);
    }
    else{
      pwm_set_gpio_level(9, 0x3fff);
      pwm_set_gpio_level(11, 0x3fff);
    }
    x++;
    return true;
  }
  bool repeating_timer_callback1(struct repeating_timer *t) {
    if (x % 2 == 0){
      pwm_set_gpio_level(8, 0xffff);
      pwm_set_gpio_level(10, 0xffff);
    }
    else{
      pwm_set_gpio_level(8, 0x3fff);
      pwm_set_gpio_level(10, 0x03fff);
    }
    x++;
    return true;
  }

  while (true) {
    
    uint trigPin = 3;
    uint echoPin = 2;
    setupUltrasonicPins(trigPin, echoPin);
    int s1 = getCm(trigPin, echoPin);
    trigPin = 5;
    echoPin = 4;
    setupUltrasonicPins(trigPin, echoPin);
    int s2 = getCm(trigPin, echoPin);
    if (s1 > 10 && s2 > 10) {
      gpio_put(22, true);
      gpio_put(21, true);
    }
    if (s1 < 10) {
      gpio_put(22, false);
      gpio_put(21, false);
      pwm_set_gpio_level(10, 0xffff);
      pwm_set_gpio_level(11, 0xffff);
      sleep_ms(1000);
      struct repeating_timer timer;
      add_repeating_timer_ms(250, repeating_timer_callback1, NULL, &timer);
      pwm_set_gpio_level(10, 0x3fff);
      pwm_set_gpio_level(11, 0x3fff);
      sleep_ms(2000);
      gpio_put(22, true);
      gpio_put(19, true);
      sleep_ms(500);
      cancel_repeating_timer(&timer);
      pwm_set_gpio_level(8, 0x3fff);
      pwm_set_gpio_level(9, 0x3fff);
      pwm_set_gpio_level(10, 0x3fff);
      pwm_set_gpio_level(11, 0x3fff);
      gpio_put(22, false);
      gpio_put(19, false);
    }
    if (s2 < 10) {
      gpio_put(22, false);
      gpio_put(21, false);
      pwm_set_gpio_level(10, 0xffff);
      pwm_set_gpio_level(11, 0xffff);
      sleep_ms(1000);
      struct repeating_timer timer;
      add_repeating_timer_ms(250, repeating_timer_callback, NULL, &timer);
      pwm_set_gpio_level(10, 0x3fff);
      pwm_set_gpio_level(11, 0x3fff);
      sleep_ms(2000);
      gpio_put(21, true);
      gpio_put(20, true);
      sleep_ms(500);
      cancel_repeating_timer(&timer);
      pwm_set_gpio_level(8, 0x3fff);
      pwm_set_gpio_level(9, 0x3fff);
      pwm_set_gpio_level(10, 0x3fff);
      pwm_set_gpio_level(11, 0x3fff);
      gpio_put(21, false);
      gpio_put(20, false);
    }
    sleep_ms(1000);
  }
}