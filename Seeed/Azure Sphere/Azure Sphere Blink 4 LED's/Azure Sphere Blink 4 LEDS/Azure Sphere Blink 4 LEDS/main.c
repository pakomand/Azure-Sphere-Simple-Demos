#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#include <applibs/log.h>
#include <applibs/gpio.h>
#include <stdio.h>


int main(void)
{
	// This minimal Azure Sphere app repeatedly toggles GPIO 9, which is the green channel of RGB
	// LED 1 on the MT3620 RDB.
	// Use this app to test that device and SDK installation succeeded that you can build,
	// deploy, and debug an app with Visual Studio, and that you can deploy an app over the air,
	// per the instructions here: https://docs.microsoft.com/azure-sphere/quickstarts/qs-overview
	//
	// It is NOT recommended to use this as a starting point for developing apps; instead use
	// the extensible samples here: https://github.com/Azure/azure-sphere-samples
	Log_Debug(
		"\nVisit https://github.com/Azure/azure-sphere-samples for extensible samples to use as a "
		"starting point for full applications.\n");

	int fd1 = GPIO_OpenAsOutput(9, GPIO_OutputMode_PushPull, GPIO_Value_Low);
	int fd2 = GPIO_OpenAsOutput(15, GPIO_OutputMode_PushPull, GPIO_Value_Low);
	int fd3 = GPIO_OpenAsOutput(20, GPIO_OutputMode_PushPull, GPIO_Value_Low);
	int fd4 = GPIO_OpenAsOutput(22, GPIO_OutputMode_PushPull, GPIO_Value_Low);
	if (fd1 < 0) {
		Log_Debug(
			"Error opening GPIO: %s (%d). Check that app_manifest.json includes the GPIO used.\n",
			strerror(errno), errno);
		return -1;
	}

	const struct timespec sleepTime = { 1, 0 };
	while (true) {
		GPIO_SetValue(fd1, GPIO_Value_Low);
		GPIO_SetValue(fd2, GPIO_Value_High);
		GPIO_SetValue(fd3, GPIO_Value_High);
		GPIO_SetValue(fd4, GPIO_Value_High);
		nanosleep(&sleepTime, NULL);
		GPIO_SetValue(fd1, GPIO_Value_High);
		GPIO_SetValue(fd2, GPIO_Value_Low);
		nanosleep(&sleepTime, NULL);
		GPIO_SetValue(fd2, GPIO_Value_High);
		GPIO_SetValue(fd3, GPIO_Value_Low);
		nanosleep(&sleepTime, NULL);
		GPIO_SetValue(fd3, GPIO_Value_High);
		GPIO_SetValue(fd4, GPIO_Value_Low);
		nanosleep(&sleepTime, NULL);
		//GPIO_SetValue(fd1, GPIO_Value_High);
		//nanosleep(&sleepTime, NULL);
	}
}