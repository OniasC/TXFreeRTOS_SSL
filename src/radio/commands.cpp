#include <radio/commands.h>
#include <radio/bsp.h>
#include "control/Robo.h"

uint16_t cmd_idn(uint16_t argc, uint8_t *argv8[]){
	const char **argv=(const char **)argv8;
	uint16_t size=0;
	char* buffer=(char*)argv[0];

	if(argc==1){
		size+=sprintf(buffer+size, "IME,RoboIME,2016,0.1\r\n");
	} else {
		size+=sprintf(buffer+size, "Syntax: model\r\n");
	}
	return size;
}

uint16_t cmd_motv(uint16_t argc, uint8_t *argv8[]){
	const char **argv=(const char **)argv8;
	uint16_t size=0;
	char* buffer=(char*)argv[0];
	uint8_t motnr=0;
	if(argc==6){
		vel_robo* velocidades;
		velocidades = new vel_robo;
		velocidades->vel[0]=atof(argv[1]);
		velocidades->vel[1]=atof(argv[2]);
		velocidades->vel[2]=atof(argv[3]);
		velocidades->vel[3]=atof(argv[4]);
		xQueueSendToBack(fila_vel, &velocidades, portMAX_DELAY);
		size+=sprintf(buffer+size, "OK\r\n");
	} else {
		size+=sprintf(buffer+size, "        motv vel0 vel1 vel2 vel3 vel4\r\n");
	}
	return size;
}

CommandLine cmdline({"*IDN?", "motv"},
					{cmd_idn, cmd_motv});
