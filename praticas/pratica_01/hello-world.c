#include <stdio.h>

#include "contiki.h"


PROCESS(hello_world_process, "Hello world process");
AUTOSTART_PROCESSES(&hello_world_process);

PROCESS_THREAD(hello_world_process, ev, data)
{
  PROCESS_BEGIN();

  /* Insira o codigo aqui */
 printf("Figueira Maior do Estado\n");
  /************************/

  PROCESS_END();
}
