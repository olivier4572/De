#include "SerieCLI.h"



SerieCLI::SerieCLI()
{
	// Create a new SerialPort object with default settings.
	_serialPort = gcnew SerialPort();

	// Allow the user to set the appropriate properties.
	_serialPort->PortName = "COM3";
	_serialPort->BaudRate = 115200;
	_serialPort->Parity = System::IO::Ports::Parity::None;
	_serialPort->DataBits = 7;
	_serialPort->StopBits = System::IO::Ports::StopBits::One;
	_serialPort->Handshake = System::IO::Ports::Handshake::None;

	// Set the read/write timeouts
	_serialPort->ReadTimeout = 500;
	_serialPort->WriteTimeout = 500;

}
