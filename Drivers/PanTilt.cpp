#include "PanTilt.h"

bool PanTilt::Initialize (void)
{
    std::cout <<"\n\t\tSearching for Arduino Serial Port...\n\t\t\t\t\t\t";

    char mode [] = {'8','N','1',0};
    sendBuffer [0] = COMMAND_BEGIN;
    sendBuffer [1] = COMMAND_PAN;
    sendBuffer [2] = COMMAND_TILT;
    sendBuffer [3] = COMMAND_REQUEST;
    sendBuffer [4] = COMMAND_END;
    if (RS232_OpenComport(USB_PORT, BAUD_RATE, mode))
        return false;
    usleep(COM_DELAY);

    return ExecuteTransmission ();
}

bool PanTilt::ExecuteTransmission()
{
    receiveBuffer [0] = RESPONSE_FAILURE;
    RS232_cputs(USB_PORT, sendBuffer);
    usleep(COM_DELAY);
    int n = RS232_PollComport(USB_PORT, receiveBuffer, REC_BUF_SIZE);
    if (n == REC_BUF_SIZE)
    {
        if (receiveBuffer [0] == RESPONSE_SUCCESS)
            return true;
    }
    return false;
}

std::string PanTilt::RetrieveAngleHex(int angle)
{
    if (angle < 15 || angle > 180)
        return NULL;

    std::string sHex;
    std::stringstream stream;
    stream << "0x"
           << std::setfill ('0') << std::setw(sizeof(int)*2)
           << std::hex << angle;
    sHex = stream.str ();

    return sHex;
}

bool PanTilt::SendPosition(std::string angle)
{
    int n = angle.length();
    char hex[n + 1];
    strcpy (hex, angle.c_str());

    sendBuffer [2] = hex [n - 2];
    sendBuffer [3] = hex [n - 1];

    return ExecuteTransmission();
}

bool PanTilt::TiltPosition (int angle)
{
    sendBuffer [1] = COMMAND_TILT;
    return SendPosition (RetrieveAngleHex (angle));
}

bool PanTilt::PanPosition (int angle)
{
    sendBuffer [1] = COMMAND_PAN;
    return SendPosition (RetrieveAngleHex(angle));
}

int PanTilt::GetAngleFromCommand(const char command [])
{
    int angle = 0;

    angle += (command [2] - '0') * 100;
    angle += (command [3] - '0') * 10;
    angle += (command [4] - '0');

    return angle;
}

bool PanTilt::ProcessCommand (const char command [], int size)
{
    if (size == 5)
	{
        if (command [1] == 'P')
        {
            if (command [0] == 'T')
                return TiltPosition (GetAngleFromCommand(command));  // Position (Tilt)
            else if (command [0] == 'P')
                return PanPosition (GetAngleFromCommand(command));   // Position (Pan)
        }
	}

    return false;
}
