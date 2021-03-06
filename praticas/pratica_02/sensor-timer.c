#include "contiki.h"
#include "sys/etimer.h"
#include "button-sensor.h"
#include "batmon-sensor.h"

#include <stdio.h>

/*---------------------------------------------------------------------------*/
#define BUF_SIZE 8
static int buffer[BUF_SIZE];
static int buf_c = 0;

static struct etimer et_sensor;

/*---------------------------------------------------------------------------*/
PROCESS(sensor_process, "Sensor process");
/*---------------------------------------------------------------------------*/
AUTOSTART_PROCESSES(&sensor_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(sensor_process, ev, data)
{
  PROCESS_BEGIN();

  SENSORS_ACTIVATE(batmon_sensor);

  etimer_set(&et_sensor, 1*CLOCK_SECOND); // a cada segundo

  while(1) {
    PROCESS_WAIT_EVENT();
    if(ev == PROCESS_EVENT_TIMER)  // se passou um segundo
    {
        etimer_reset(&et_sensor); // reinicia timer

        int val = batmon_sensor.value(BATMON_SENSOR_TYPE_TEMP); // lê sensor

        //Armazenando os valores requisitados em um buffer circular
        buffer[buf_c++] = val;
        if(buf_c == BUF_SIZE)
            buf_c = 0;





        printf("Valor buf_c %d\n", buf_c);
        printf("Leu %d\n", val);
    }
  }

  PROCESS_END();
}
