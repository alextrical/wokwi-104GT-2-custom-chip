// Wokwi Custom Chip - For information and examples see:
// https://link.wokwi.com/custom-chips-alpha
//
// SPDX-License-Identifier: MIT
// Copyright (C) 2022 Alextrical
// equations based on https://forum.arduino.cc/t/steinhart-hart-reverse-equation/396226/34

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ~~~~~~ A,B,C ~~~~~~
#define A 7.97110609710217e-4 //104GT-2
#define B 2.13433144381270e-4 //104GT-2
#define C 6.5338987554e-8     //104GT-2

const long seriesResistor = 4700;

typedef struct {
  pin_t pin_sig;
  uint32_t temperature_attr;
} chip_state_t;

static void chip_timer_event(void *user_data);

void chip_init(void) {
  chip_state_t *chip = malloc(sizeof(chip_state_t));
  chip->pin_sig = pin_init("SIG", ANALOG);
  chip->temperature_attr = attr_init_float("temperature", 19.0);

  const timer_config_t timer_config = {
    .callback = chip_timer_event,
    .user_data = chip,
  };
  timer_t timer_id = timer_init(&timer_config);
  timer_start(timer_id, 1000, true);
}

void chip_timer_event(void *user_data) {
  chip_state_t *chip = (chip_state_t*)user_data;

  float T = attr_read_float(chip->temperature_attr) + 273.15;
  float x = (A - 1/T)/C;
  float B_C = B/C;
  float y = sqrt(B_C*B_C*B_C/27 + x*x/4);
  float R = exp(pow(y - x/2,1/3.) - pow(y + x/2,1/3.));

  float voltage = 5.0 * (R/(R+seriesResistor));
  pin_dac_write(chip->pin_sig, voltage);
}