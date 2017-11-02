#include <stm32f4xx_gpio.h>
#include <stm32f4xx_usart.h>

#include <radio/bsp.h>
#include <radio/serialnumber.h>
#include <hal_stm32/interrupt_stm32.h>
#include <radio/version.h>
#include <list>
//#include <control/Robo.h>
//#include <control/Switch.h>
//#include "TimerTime.h"

extern "C"{
	#include "usb_dcd_int.h"
	#include "usb_hcd_int.h"
}
//------------setando os leds----------------//
LED led_verde(new IO_Pin_STM32 (IO_Pin::IO_Pin_Mode_OUT, GPIOD, GPIO_Pin_12)); //led verde
LED led_laranja(new IO_Pin_STM32 (IO_Pin::IO_Pin_Mode_OUT, GPIOD, GPIO_Pin_13)); //led laranja
LED led_vermelho(new IO_Pin_STM32 (IO_Pin::IO_Pin_Mode_OUT, GPIOD, GPIO_Pin_14)); //led vermelho
LED led_azul(new IO_Pin_STM32 (IO_Pin::IO_Pin_Mode_OUT, GPIOD, GPIO_Pin_15)); //led azul
//-------------setando o botão--------------//
//IO_Pin_STM32 Botao(IO_Pin::IO_Pin_Mode_IN, GPIOA, GPIO_Pin_0, GPIO_PuPd_NOPULL);

//-------------setando o usb--------------//
IO_Pin_STM32 USB_DP(IO_Pin::IO_Pin_Mode_SPECIAL, GPIOA, GPIO_Pin_12, GPIO_PuPd_NOPULL, GPIO_OType_PP, GPIO_AF_OTG_FS);
IO_Pin_STM32 USB_DM(IO_Pin::IO_Pin_Mode_SPECIAL, GPIOA, GPIO_Pin_11, GPIO_PuPd_NOPULL, GPIO_OType_PP, GPIO_AF_OTG_FS);

//USB_DEVICE_CLASS_CDC_RNDIS usb_device_class_cdc_rndis(1);

std::list<USB_DEVICE_CLASS*> USB_DEVICE_CLASS::_usb_device_classes_list;
USB_DEVICE_CLASS_CDC_VCP usb_device_class_cdc_vcp({"RoboIME Serial Port"},1);
USB_STM32 usb(0x29BC, 0x2000, "IME", "RoboIME", SerialNumberGetHexaString());

//-------------setando o nrf--------------//
IO_Pin_STM32 SPI_SCK_PIN(IO_Pin::IO_Pin_Mode_SPECIAL, GPIOA, GPIO_Pin_5, GPIO_PuPd_NOPULL, GPIO_OType_PP, GPIO_AF_SPI1);
IO_Pin_STM32 SPI_MISO_PIN(IO_Pin::IO_Pin_Mode_SPECIAL, GPIOA, GPIO_Pin_6, GPIO_PuPd_NOPULL, GPIO_OType_PP, GPIO_AF_SPI1);
IO_Pin_STM32 SPI_MOSI_PIN(IO_Pin::IO_Pin_Mode_SPECIAL, GPIOA, GPIO_Pin_7, GPIO_PuPd_NOPULL, GPIO_OType_PP, GPIO_AF_SPI1);
IO_Pin_STM32 NRF24_SS_PIN(IO_Pin::IO_Pin_Mode_OUT, GPIOA, GPIO_Pin_4, GPIO_PuPd_NOPULL, GPIO_OType_PP);
IO_Pin_STM32 NRF24_CE_PIN(IO_Pin::IO_Pin_Mode_OUT, GPIOA, GPIO_Pin_3, GPIO_PuPd_NOPULL, GPIO_OType_PP);
IO_Pin_STM32 NRF24_IRQN_PIN(IO_Pin::IO_Pin_Mode_IN, GPIOC, GPIO_Pin_5, GPIO_PuPd_UP, GPIO_OType_OD);

SPI_STM32 spi(SPI1, NRF24_SS_PIN);

NRF24L01P nrf24(spi, NRF24_SS_PIN, NRF24_CE_PIN, NRF24_IRQN_PIN);

IO_Pin_STM32 LIS3DSH_CSN(IO_Pin::IO_Pin_Mode_IN, GPIOE, GPIO_Pin_3, GPIO_PuPd_NOPULL, GPIO_OType_OD);

/*------------PARA USAR QND TIVER COM OS MOTORES---------------
//INTERRUPT_STM32 nrf24_irqn_exti_interrupt(NRF24_IRQN_PIN.GetIRQChannel(), 0x0C, 0x0C, DISABLE);
Timer_Time2 robo_timer;

//checar os minas no desenho da placa

Pwm ahpwm0(GPIOC, GPIO_Pin_9, TIM8, GPIO_PinSource9, GPIO_AF_TIM8, 4, false);
GPIO algpio0(GPIOE, GPIO_Pin_5);
Pwm bhpwm0(GPIOC, GPIO_Pin_7, TIM8, GPIO_PinSource7, GPIO_AF_TIM8, 2, false);
GPIO blgpio0(GPIOC, GPIO_Pin_13);
Encoder encoder0(GPIOB, GPIOB, GPIO_Pin_4, GPIO_Pin_5, TIM3, GPIO_PinSource4, GPIO_PinSource5, GPIO_AF_TIM3);
INA220 mina220(i2c_a, 0x80);
Motor motor0(&ahpwm0, &algpio0, &bhpwm0, &blgpio0, &encoder0, &robo_timer, &mina220);
*///------------------------/////////

CircularBuffer<uint8_t> _usbserialbuffer(0,2048);
CircularBuffer<uint8_t> _usbserialbuffer2(0,2048);

INTERRUPT_STM32 usb_otg_fs_interrupt(OTG_FS_IRQn, 0x0D, 0x0D, ENABLE);

extern USB_OTG_CORE_HANDLE USB_OTG_dev;
extern "C" void OTG_FS_IRQHandler(void){
	USBD_OTG_ISR_Handler (&USB_OTG_dev);
	USBH_OTG_ISR_Handler (&USB_OTG_dev);
}
extern "C" void OTG_FS_WKUP_IRQHandler(void){
	if(USB_OTG_dev.cfg.low_power){
		*(uint32_t *)(0xE000ED10) &= 0xFFFFFFF9 ;
		SystemInit();
		USB_OTG_UngateClock(&USB_OTG_dev);
	}
	EXTI_ClearITPendingBit(EXTI_Line18);
}
