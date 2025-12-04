// =====================================================================
// TIMER5 = 1MHz  → 1us çözünürlük
// CCR1 compare interrupt = ateşleme olayı
// =====================================================================

void fire_ignition(void)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); // Örnek: LED
}

void schedule_event(uint32_t us)
{
    TIM5->CCR1 = us;
    TIM5->SR &= ~TIM_SR_CC1IF;
    TIM5->DIER |= TIM_DIER_CC1IE;
}

void TIM5_IRQHandler(void)
{
    if(TIM5->SR & TIM_SR_CC1IF)
    {
        TIM5->SR &= ~TIM_SR_CC1IF;
        fire_ignition();
    }
}

void main(void)
{
    HAL_Init();
    TIM5_Init();

    while(1)
    {
        uint32_t now = TIM5->CNT;
        schedule_event(now + 2000);  // 2ms sonra ateşle
        HAL_Delay(1000);
    }
}
