// $Id$

#include "MSXPSG.hh"
#include "AY8910.hh"
#include "LedStatus.hh"
#include "CassettePort.hh"
#include "MSXMotherBoard.hh"
#include "JoystickPort.hh"
#include "SimpleDebuggable.hh"
#include "XMLElement.hh"
#include "RenShaTurbo.hh"
#include "serialize.hh"

namespace openmsx {

class JoyPortDebuggable : public SimpleDebuggable
{
public:
	JoyPortDebuggable(MSXMotherBoard& motherBoard, MSXPSG& psg);
	virtual byte read(unsigned address, EmuTime::param time);
	virtual void write(unsigned address, byte value);
private:
	MSXPSG& psg;
};


// MSXDevice
MSXPSG::MSXPSG(MSXMotherBoard& motherBoard, const XMLElement& config)
	: MSXDevice(motherBoard, config)
	, joyPortDebuggable(new JoyPortDebuggable(motherBoard, *this))
	, cassette(motherBoard.getCassettePort())
	, renShaTurbo(motherBoard.getRenShaTurbo())
	, prev(255)
	, keyLayoutBit(config.getChildData("keyboardlayout", "") == "JIS")
{
	selectedPort = 0;
	PluggingController& controller = motherBoard.getPluggingController();
	ports[0].reset(new JoystickPort(controller, "joyporta", "MSX Joystick port A"));
	ports[1].reset(new JoystickPort(controller, "joyportb", "MSX Joystick port B"));

	// must come after initialisation of ports
	EmuTime::param time = getCurrentTime();
	ay8910.reset(new AY8910(motherBoard, *this, config, time));
	reset(time);
}

MSXPSG::~MSXPSG()
{
	powerDown(EmuTime::dummy());
}

void MSXPSG::reset(EmuTime::param time)
{
	registerLatch = 0;
	ay8910->reset(time);
}

void MSXPSG::powerDown(EmuTime::param /*time*/)
{
	getMotherBoard().getLedStatus().setLed(LedStatus::KANA, false);
}

byte MSXPSG::readIO(word /*port*/, EmuTime::param time)
{
	byte result = ay8910->readRegister(registerLatch, time);
	//PRT_DEBUG("PSG read R#"<<(int)registerLatch<<" = "<<(int)result);
	return result;
}

byte MSXPSG::peekIO(word /*port*/, EmuTime::param time) const
{
	return ay8910->peekRegister(registerLatch, time);
}

void MSXPSG::writeIO(word port, byte value, EmuTime::param time)
{
	switch (port & 0x03) {
	case 0:
		registerLatch = value & 0x0F;
		break;
	case 1:
		//PRT_DEBUG("PSG write R#"<<(int)registerLatch<<" = "<<(int)value);
		ay8910->writeRegister(registerLatch, value, time);
		break;
	}
}


// AY8910Periphery
byte MSXPSG::readA(EmuTime::param time)
{
	byte joystick = ports[selectedPort]->read(time) |
	                ((renShaTurbo.getSignal(time)) ? 0x10 : 0x00);

	// pin 6,7 input is ANDed with pin 6,7 output
	byte pin67 = prev << (4 - 2 * selectedPort);
	joystick &= (pin67| 0xCF);

	byte cassetteInput = cassette.cassetteIn(time) ? 0x80 : 0x00;
	byte keyLayout = keyLayoutBit ? 0x40 : 0x00;
	return joystick | keyLayout | cassetteInput;
}

void MSXPSG::writeB(byte value, EmuTime::param time)
{
	byte val0 =  (value & 0x03)       | ((value & 0x10) >> 2);
	byte val1 = ((value & 0x0C) >> 2) | ((value & 0x20) >> 3);
	ports[0]->write(val0, time);
	ports[1]->write(val1, time);
	selectedPort = (value & 0x40) >> 6;

	if ((prev ^ value) & 0x80) {
		getMotherBoard().getLedStatus().setLed(LedStatus::KANA, !(value & 0x80));
	}
	prev = value;
}


// class JoyPortDebuggable

JoyPortDebuggable::JoyPortDebuggable(MSXMotherBoard& motherBoard, MSXPSG& psg_)
	: SimpleDebuggable(motherBoard, "joystickports", "MSX Joystick Ports", 2)
	, psg(psg_)
{
}

byte JoyPortDebuggable::read(unsigned address, EmuTime::param time)
{
	return psg.ports[address]->read(time);
}

void JoyPortDebuggable::write(unsigned /*address*/, byte /*value*/)
{
	// ignore
}


template<typename Archive>
void MSXPSG::serialize(Archive& ar, unsigned /*version*/)
{
	ar.template serializeBase<MSXDevice>(*this);
	ar.serialize("ay8910", *ay8910);
	ar.serialize("joystickportA", *ports[0]);
	ar.serialize("joystickportB", *ports[1]);
	ar.serialize("registerLatch", registerLatch);
	byte portB = prev;
	ar.serialize("portB", portB);
	if (ar.isLoader()) {
		writeB(portB, getCurrentTime());
	}
	// selectedPort is derived from portB
}
INSTANTIATE_SERIALIZE_METHODS(MSXPSG);
REGISTER_MSXDEVICE(MSXPSG, "PSG");

} // namespace openmsx
