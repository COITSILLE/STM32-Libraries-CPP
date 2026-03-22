#pragma once

#ifdef __cplusplus
template <typename PWMType>
void TB6612_Motor<PWMType>::init(TB6612GPIOParams init_params){
    this->gpio_params = init_params;
}

template <typename PWMType>
void TB6612_Motor<PWMType>::stby(bool state){
    HAL_GPIO_WritePin(this->gpio_params.StbyGPIOx, this->gpio_params.StbyPin, (state ? GPIO_PIN_SET : GPIO_PIN_RESET));
}

template <typename PWMType>
void TB6612_Motor<PWMType>::setDuty(float duty){
    float _duty_;
    if (duty < 0) _duty_ = 0;
    else if (duty > 1) _duty_ = 1;
    else  _duty_ = duty;
    
    this->pwm->setDuty(_duty_);
}

template <typename PWMType>
void TB6612_Motor<PWMType>::setControl(MotorState state){
    switch (state) {
        case BRAKE:
            HAL_GPIO_WritePin(this->gpio_params.Ctrl1GPIOx, this->gpio_params.Ctrl1Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(this->gpio_params.Ctrl2GPIOx, this->gpio_params.Ctrl2Pin, GPIO_PIN_SET);
            break;
        case FORWARD:
            HAL_GPIO_WritePin(this->gpio_params.Ctrl1GPIOx, this->gpio_params.Ctrl1Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(this->gpio_params.Ctrl2GPIOx, this->gpio_params.Ctrl2Pin, GPIO_PIN_RESET);
            break;
        case BACKWARD:
            HAL_GPIO_WritePin(this->gpio_params.Ctrl1GPIOx, this->gpio_params.Ctrl1Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(this->gpio_params.Ctrl2GPIOx, this->gpio_params.Ctrl2Pin, GPIO_PIN_SET);
            break;
        case SLIDE:
            HAL_GPIO_WritePin(this->gpio_params.Ctrl1GPIOx, this->gpio_params.Ctrl1Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(this->gpio_params.Ctrl2GPIOx, this->gpio_params.Ctrl2Pin, GPIO_PIN_RESET);
            break;
    }
}

#endif