#pragma once
#include "main.h"
#include "pwm.h"
#include "motor_state.h"
#include <stdint.h>

struct TB6612GPIOParams{
    GPIO_TypeDef *Ctrl1GPIOx;
    uint16_t Ctrl1Pin;
    GPIO_TypeDef *Ctrl2GPIOx;
    uint16_t Ctrl2Pin;

    GPIO_TypeDef *StbyGPIOx;
    uint16_t StbyPin;
};

template <typename PWMType>
class TB6612_Motor{
private:
    TB6612GPIOParams gpio_params;
    PWM<PWMType>* pwm;
public:
    TB6612_Motor(PWM<PWMType>* pwm) : pwm(pwm){};
    void init(TB6612GPIOParams init_params);
    void stby(bool state);
    void setControl(MotorState state);
    void setDuty(float duty);
};

template <typename PWMType>
TB6612_Motor(PWM<PWMType>*) -> TB6612_Motor<PWMType>;

#include "tb6612.ipp"
