// $Id$

#include <cassert>
#include "MidiOutLogger.hh"

namespace openmsx {

MidiOutLogger::MidiOutLogger()
	: logFilenameSetting("midi-out-logfilename",
		"filename of the file where the MIDI output is logged to",
		"/dev/midi"),
	  file(0)
{
}

MidiOutLogger::~MidiOutLogger()
{
	delete file;
}

void MidiOutLogger::plug(Connector *connector, const EmuTime &time)
	throw(PlugException)
{
	file = new ofstream(logFilenameSetting.getValue().c_str());
	if (file->fail()) {
		unplug(time);
		throw PlugException("Error opening log file");
	}
}

void MidiOutLogger::unplug(const EmuTime &time)
{
	delete file;
	file = 0;
}

const string& MidiOutLogger::getName() const
{
	static const string name("midi-out-logger");
	return name;
}

const string& MidiOutLogger::getDescription() const
{
	static const string desc(
		"Midi output logger. Log all data that is sent to this "
		"pluggable to a file. The filename is set with the "
		"'midi-out-logfilename' setting.");
	return desc;
}

void MidiOutLogger::recvByte(byte value, const EmuTime &time)
{
	assert(file);
	file->put(value);
	file->flush();
}

} // namespace openmsx
