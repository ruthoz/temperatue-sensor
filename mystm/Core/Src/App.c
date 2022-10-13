#include "App.h"
#include <stdio.h>


void printAppVer(const Application* app)
{
	uint8_t major = app->version ;
	uint8_t minor  = app->version >> 8  ;
	uint8_t release =  app->version >> 16 ;
	uint8_t build = app->version >> 24 ;

	printf("%d.%d.%d.%d \r\n" , major, minor, release, build );
}

