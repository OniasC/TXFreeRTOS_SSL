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

IO_Pin_STM32 Botao(IO_Pin::IO_Pin_Mode_IN, GPIOA, GPIO_Pin_0, GPIO_PuPd_NOPULL);

IO_Pin_STM32 USB_DP(IO_Pin::IO_Pin_Mode_SPECIAL, GPIOA, GPIO_Pin_12, GPIO_PuPd_NOPULL, GPIO_OType_PP, GPIO_AF_OTG_FS);
IO_Pin_STM32 USB_DM(IO_Pin::IO_Pin_Mode_SPECIAL, GPIOA, GPIO_Pin_11, GPIO_PuPd_NOPULL, GPIO_OType_PP, GPIO_AF_OTG_FS);

//USB_DEVICE_CLASS_CDC_RNDIS usb_device_class_cdc_rndis(1);

std::list<USB_DEVICE_CLASS*> USB_DEVICE_CLASS::_usb_device_classes_list;
USB_DEVICE_CLASS_CDC_VCP usb_device_class_cdc_vcp({"RoboIME Serial Port"},1);
USB_STM32 usb(0x29BC, 0x2000, "IME", "RoboIME", SerialNumberGetHexaString());

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
