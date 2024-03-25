#include "watchdog.h"

#define IWDG_KEY_ENABLE         0x5555
#define IWDG_PRESCALER_DIV_256  0x06
#define IWDG_KEY_RELOAD         0xAAAA
#define IWDG_KEY_START          0xCCCC

#if defined(BOARD_MK_STM32F105) | defined(BOARD_MK_STM32F205)
#define IWDG_PERIPH IWDG
#elif defined(BOARD_MK_STM32H730)
#define IWDG_PERIPH IWDG1
#else
#define IWDG_PERIPH IWDG
#endif


// Hardware (IC on the board) watchdog
void reset_hw_watchdog(void){
	TOGGLE_HW_WATCHDOG;
}

void Init_IWDG(uint16_t tw){
// Для IWDG_PR=7 Tmin=6,4мс RLR=Tмс*40/256
	IWDG_PERIPH->KR=IWDG_KEY_ENABLE; // Ключ для доступа к таймеру
	IWDG_PERIPH->PR=IWDG_PRESCALER_DIV_256; // Обновление IWDG_PR
	IWDG_PERIPH->RLR= (uint32_t)(tw*40/256); // Загрузить регистр перезагрузки
	IWDG_PERIPH->KR=IWDG_KEY_RELOAD; // Перезагрузка
	IWDG_PERIPH->KR=IWDG_KEY_START; // Пуск таймера
	}

// Функция перезагрузки сторожевого таймера IWDG
void IWDG_reset(void){
	TOGGLE_HW_WATCHDOG;
	IWDG_PERIPH->KR=(uint32_t)IWDG_KEY_RELOAD; // Перезагрузка
}
