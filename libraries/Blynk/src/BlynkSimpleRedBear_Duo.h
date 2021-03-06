/**
 * @file       BlynkSimpleRedBear_Duo.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Dec 2015
 * @brief
 *
 */

#ifndef BlynkSimpleRedBear_Duo_h
#define BlynkSimpleRedBear_Duo_h

#include "BlynkParticle.h"

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_BLYNK)
  static BlynkTransportParticle _blynkTransport;
  BlynkParticle Blynk(_blynkTransport);
#else
  extern BlynkParticle Blynk;
#endif

#include "BlynkWidgets.h"

#endif
