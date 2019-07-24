#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#include <applibs/log.h>
#include <applibs/gpio.h>
#include <stdio.h>
#include <applibs/mt3620_rdb.h>
#include <applibs/mt3620_adc_driver.h>


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

	int sensor = GPIO_OpenAsInput(MT3620_GPIO4);
	int fd2 = GPIO_OpenAsOutput(7, GPIO_OutputMode_PushPull, GPIO_Value_Low);
	if (sensor < 0) {
		Log_Debug(
			"Error opening GPIO: %s (%d). Check that app_manifest.json includes the GPIO used.\n",
			strerror(errno), errno);
		return -1;
	 }

    const struct timespec sleepTime = {1, 0};
    while (true) {
		GPIO_Value_Type newstate1;
		GPIO_GetValue(sensor, &newstate1);
	    //Log_Debug("Valor GPIO 5 (%s) \n", newstate1);
		if (newstate1 == GPIO_Value_High )
		{
			Log_Debug("Human Touch  \n");
		  GPIO_SetValue(fd2, GPIO_Value_High);
		    
		}
		else if (newstate1 == GPIO_Value_Low)
		{
			Log_Debug("No Human Touch  \n");
			GPIO_SetValue(fd2, GPIO_Value_Low);
		}
		
		//GPIO_SetValue(fd, GPIO_Value_Low);
		//Log_Debug("Valor GPIO 5 (%s) \n", newstate1);
        nanosleep(&sleepTime, NULL);
    }
}