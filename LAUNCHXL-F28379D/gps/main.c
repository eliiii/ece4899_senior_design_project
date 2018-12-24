/***************************************************************************
| Project           : gps
|
| Program name      : main.c
|
| Author            : qrogers
|
| Date created      : ** *** ****
|
| Purpose           : GPS Module
|
| Revision History  :
|
| Date          Author      Ref     Revision
| ** *** ****   qrogers      1      Initial Release
|
***************************************************************************/

#include "driverlib.h"
#include "device.h"

void main(void)
{
   uint16_t receivedChar;
   
   Device_init();
   
   Device_initGPIO();
   
   // GPIO19 is the SCI RX pin.
   GPIO_setMasterCore(19, GPIO_CORE_CPU1);
   GPIO_setPinConfig(GPIO_19_SCIRXDB);
   GPIO_setDirectionMode(19, GPIO_DIR_MODE_IN);
   GPIO_setPadConfig(28, GPIO_PIN_TYPE_STD);
   GPIO_setQualificationMode(19, GPIO_QUAL_ASYNC);
   
   // GPIO18 is the SCI TX pin.
   GPIO_setMasterCore(18, GPIO_CORE_CPU1);
   GPIO_setPinConfig(GPIO_18_SCITXDB);
   GPIO_setDirectionMode(18, GPIO_DIR_MODE_OUT);
   GPIO_setPadConfig(18, GPIO_PIN_TYPE_STD);
   GPIO_setQualificationMode(18, GPIO_QUAL_ASYNC);
   
   Interrupt_initModule();
   Interrupt_initVectorTable();
   
   SCI_performSoftwareReset(SCIB_BASE);
   
   SCI_setConfig(SCIB_BASE, DEVICE_LSPCLK_FREQ, 9600, (SCI_CONFIG_WLEN_8   |
                                                       SCI_CONFIG_STOP_ONE |
                                                       SCI_CONFIG_PAR_NONE));
   SCI_resetChannels(SCIB_BASE);
   SCI_resetRxFIFO(SCIB_BASE);
   SCI_resetTxFIFO(SCIB_BASE);
   SCI_clearInterruptStatus(SCIB_BASE, SCI_INT_TXFF | SCI_INT_RXFF);
   SCI_enableFIFO(SCIB_BASE);
   SCI_enableModule(SCIB_BASE);
   SCI_performSoftwareReset(SCIB_BASE);
   
   while(1)
   {
     receivedChar = SCI_readCharBlockingFIFO(SCIB_BASE);
   }
}
