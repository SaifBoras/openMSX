// $Id$

#include "DummyDevice.hh"
#include <cassert>


DummyDevice::DummyDevice()
{
	PRT_DEBUG ("Instantiating dummy device");
	deviceName = new std::string("Dummy device");
}

DummyDevice::~DummyDevice()
{
	PRT_DEBUG ("Destroying dummy device");
}

DummyDevice* DummyDevice::instance()
{
	if (oneInstance == NULL ) {
		oneInstance = new DummyDevice();
	}
	return oneInstance;
}
DummyDevice *DummyDevice::oneInstance = NULL;


// Block usage of the following methods

void DummyDevice::setConfigDevice(MSXConfig::Device *config)
{
	assert(false);
}

void DummyDevice::init()
{
	assert(false);
}

void DummyDevice::start()
{
	assert(false);
}

void DummyDevice::stop()
{
	assert(false);
}

void DummyDevice::reset()
{
	assert(false);
}

void DummyDevice::saveState(std::ofstream &writestream)
{
	assert(false);
}

void DummyDevice::restoreState(std::string &devicestring, std::ifstream &readstream)
{
	assert(false);
}


