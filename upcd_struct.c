#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/usb.h"
#include "usblib/usblib.h"
#include "usblib/usblibpriv.h"
#include "usblib/device/usbdevice.h"
#include "upcd.h"

#define UPCD_VID		 0x1cbe
#define UPCD_PID		 0x0003	

#define DATA_IN_EP		USB_EP_1
#define DATA_OUT_EP		USB_EP_1

#define DATA_IN_EP_FIFO_SIZE	USB_FIFO_SZ_64
#define DATA_OUT_EP_FIFO_SIZE	USB_FIFO_SZ_64

#define DATA_IN_EP_MAX_SIZE	USBFIFOSizeToBytes(DATA_IN_EP_FIFO_SIZE)
#define DATA_OUT_EP_MAX_SIZE	USBFIFOSizeToBytes(DATA_OUT_EP_FIFO_SIZE)

uint8_t g_UPCDDeviceDescriptor[] = {
	18,
	USB_DTYPE_DEVICE,
	USBShort(0x110),
	USB_CLASS_VEND_SPECIFIC,
	0,
	0,
	64,
	USBShort(0),
	USBShort(0),
	USBShort(100),
	1,
	2,
	3,
	1
};

uint8_t g_UPCDDescriptor[] = {
	9,
	USB_DTYPE_CONFIGURATION,
	USBShort(32),

	1,
	1,
	5,
	USB_CONF_ATTR_SELF_PWR,
	250,

};

const uint8_t g_UPCDInterface[23] = {
	9,
	USB_DTYPE_INTERFACE,
	0,
	0,
	2,
	USB_CLASS_VEND_SPECIFIC,
	0,
	0,
	4,

	//EndPoint Descriptors

	7,
	USB_DTYPE_ENDPOINT,
	USB_EP_DESC_IN | USBEPToIndex(DATA_IN_EP),
	USB_EP_ATTR_INT,
	USBShort(DATA_IN_EP_MAX_SIZE),
	0,

	7,
	USB_DTYPE_ENDPOINT,
	USB_EP_DESC_OUT | USBEPToIndex(DATA_OUT_EP),
	USB_EP_ATTR_INT,
	USBShort(DATA_OUT_EP_MAX_SIZE),
	0,
};

const tConfigSection g_UPCDConfigSection = {
	sizeof(g_UPCDDescriptor),
	g_UPCDDescriptor,
};

const tConfigSection g_UPCDInterfaceSection = {
	sizeof(g_UPCDInterface),
	g_UPCDInterface,
};

const tConfigSection *g_UPCDSections[] = {
	&g_UPCDConfigSection,
	&g_UPCDInterfaceSection,
};

#define NUM_DEV_SECTION sizeof(g_UPCDSections)/sizeof(g_UPCDSections[0])

const tConfigHeader g_UPCDConfigHeader = {
	NUM_DEV_SECTION,
	g_UPCDSections,

};

const tConfigHeader *const g_UPCDConfigurationDescriptors[] = {
	&g_UPCDConfigHeader
};

const uint8_t g_langDescriptor[] =
{
    4,
    USB_DTYPE_STRING,
    USBShort(USB_LANG_EN_US)
};

const uint8_t g_manufacturerString[] =
{
    (10 + 1) * 2,
    USB_DTYPE_STRING,
    'C', 0, '-', 0, 'D', 0, 'A', 0, 'C', 0, ' ', 0, 'A', 0, 'C', 0,
    'T', 0, 'S', 0,
};

const uint8_t g_productString[] =
{
    (29 + 1) * 2,
    USB_DTYPE_STRING,
    'U', 0, 'S', 0, 'B', 0, ' ', 0, 'P', 0, 'e', 0, 'r', 0, 'i', 0,
    'p', 0, 'h', 0, 'e', 0, 'r', 0, 'a', 0, 'l', 0, ' ', 0, 'C', 0,
    'o', 0, 'n', 0, 't', 0, 'r', 0, 'o', 0, 'l', 0, ' ', 0, 'D', 0,
    'e', 0, 'v', 0, 'i', 0, 'c', 0, 'e', 0,
};

const uint8_t g_serialNumberString[] = 
{ 
    (7 + 1) * 2, 
    USB_DTYPE_STRING, 
    'U', 0, 'S', 0, 'B', 0, '-', 0, '0', 0, '0', 0, '1', 0, 
};

const uint8_t g_interfaceString[] = 
{ 
    (28 + 1) * 2, 
    USB_DTYPE_STRING, 
    'D', 0, 'e', 0, 'f', 0, 'a', 0, 'u', 0, 'l', 0, 't', 0, ' ', 0, 
    'P', 0, 'e', 0, 'r', 0, 'i', 0, 'p', 0, 'h', 0, 'e', 0, 'r', 0,
    'a', 0, 'l', 0, ' ', 0, 'I', 0, 'n', 0, 't', 0, 'e', 0, 'r', 0,
    'f', 0, 'a', 0, 'c', 0, 'e', 0, 
};

const unsigned char g_configString[] = 
{ 
    (32 + 1) * 2, 
    USB_DTYPE_STRING, 
    'D', 0, 'e', 0, 'f', 0, 'a', 0, 'u', 0, 'l', 0, 't', 0, ' ', 0,
    'P', 0, 'e', 0, 'r', 0, 'i', 0, 'p', 0, 'h', 0, 'e', 0, 'r', 0,
    'a', 0, 'l', 0, ' ', 0, 'C', 0, 'o', 0, 'n', 0, 'f', 0, 'i', 0,
    'g', 0, 'u', 0, 'r', 0, 'a', 0, 't', 0, 'i', 0, 'o', 0, 'n', 0, 
};

const unsigned char *const g_stringDescriptors[] = 
{ 
    g_langDescriptor, 
    g_manufacturerString, 
    g_productString,
    g_serialNumberString, 
    g_interfaceString, 
    g_configString 
};

#define NUM_STRING_DESCRIPTORS (sizeof(g_stringDescriptors) / sizeof(uint8_t *))

upcd_device UPCDDev = {
	UPCD_VID,
	UPCD_PID,
	500,
	USB_CONF_ATTR_SELF_PWR,
	g_stringDescriptors,
	NUM_STRING_DESCRIPTORS,	
};


static void HandleEndpoints(void *dev, uint32_t status)
{
	upcd_devInst *devInst = 0;
	upcd_device *device;
	uint32_t epStatus, size, compStatus;
	static uint8_t data[512];

	device = (upcd_device *)dev;
	devInst = &device->privInst;

	if (status & (0x10000 << USBEPToIndex(devInst->intOutEP))) {
		epStatus = USBEndpointStatus(devInst->USBBase,
						     devInst->intOutEP);

	if (epStatus & USB_DEV_RX_PKT_RDY) {
			size = USBEndpointDataAvail(devInst->USBBase,
							devInst->intOutEP);
			compStatus = size;
			USBEndpointDataGet(devInst->USBBase,
							   devInst->intOutEP,
							   data, &compStatus);

			if (size == compStatus) {
				USBDevEndpointStatusClear(devInst->
							      USBBase,
							      devInst->
							      intOutEP,
							      epStatus);

				USBDevEndpointDataAck(devInst->USBBase,
							  devInst->intOutEP,
							  true);
			}

			
			size = CmdHandler(data, size);
			

			USBEndpointDataPut(devInst->USBBase,
							   devInst->intInEP,
							   data, size);

			USBEndpointDataSend(devInst->USBBase,
							    devInst->intInEP,
							    USB_TRANS_IN);
			USBEndpointDataSend(devInst->USBBase,
							    devInst->intInEP,
							    USB_TRANS_IN_LAST);

		}

	}
}

const tCustomHandlers g_UPCDHandlers = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	HandleEndpoints,
	0,
};

void *UPCDInit(uint32_t index, upcd_device *dev)
{
	upcd_devInst *privInst;
	tConfigDescriptor *priConfigDescp;
	tDeviceDescriptor *priDeviceDescp;

	privInst = &dev->privInst;

	privInst->devInfo.psCallbacks = &g_UPCDHandlers;
	privInst->devInfo.pui8DeviceDescriptor = g_UPCDDeviceDescriptor;
	privInst->devInfo.ppsConfigDescriptors =
	    g_UPCDConfigurationDescriptors;
	privInst->devInfo.ppui8StringDescriptors = dev->stringDescp;
	privInst->devInfo.ui32NumStringDescriptors = dev->numStringDescp;
	
	USBDCDDeviceInfoInit(0, &privInst->devInfo);

	privInst->USBBase = USB0_BASE;
	privInst->deferredOpFlags = 0;
	privInst->connected = false;

	privInst->intInEP = DATA_IN_EP;
	privInst->intOutEP = DATA_OUT_EP;
	privInst->interfaceNo = 0;

	InternalUSBTickInit();

	InternalUSBRegisterTickHandler(0, (void *)dev);

	priDeviceDescp = (tDeviceDescriptor *) g_UPCDDeviceDescriptor;
	priDeviceDescp->idVendor = dev->vid;
	priDeviceDescp->idProduct = dev->pid;

	priConfigDescp = (tConfigDescriptor *) g_UPCDDescriptor;

	priConfigDescp->bmAttributes = dev->pwrAttr;
	priConfigDescp->bMaxPower = (uint8_t) (dev->maxPwr / 2);

	USBDCDInit(index, &privInst->devInfo, (void *)dev);

	return dev;
}





	

	
