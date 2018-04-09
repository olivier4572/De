#pragma once

#using <System.dll>
using namespace System::IO::Ports;


ref class SerieCLI
{
public:
	SerieCLI();

public:
	static SerialPort^ _serialPort;

};

