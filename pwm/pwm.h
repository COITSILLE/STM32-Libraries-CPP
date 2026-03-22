#pragma once

#include "main.h"
#include "smath.h"

#ifdef __cplusplus


template <typename PWM_i>
class PWM {
public:
    void setDuty(float duty) {static_cast<PWM_i*>(this)->setDuty(duty);}
    void setTime(float time_ms) {static_cast<PWM_i*>(this)->setTime(time_ms);}
};

#endif
