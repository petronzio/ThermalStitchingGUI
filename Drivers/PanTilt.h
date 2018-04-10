#ifndef PANTILT_H_
#define PANTILT_H_
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <unistd.h>
#include "Third-Party/RS-232/rs232.h"

#define SEND_BUF_SIZE 5
#define REC_BUF_SIZE 1
#define COM_DELAY 200000 // microseconds

class PanTilt
{
	public:
		bool Initialize ();
        bool ProcessCommand (const char command [], int size);
        bool PanPosition (int angle);
        bool TiltPosition (int angle);
    private:
        int  GetAngleFromCommand (const char command []);
        bool ExecuteTransmission ();
        bool SendPosition (std::string angle);
        std::string RetrieveAngleHex (int angle);
        unsigned char receiveBuffer [REC_BUF_SIZE];
        char sendBuffer [SEND_BUF_SIZE];
        int BAUD_RATE = 9600; // 9600 baud
        int USB_PORT = 24;    // ACM0 serial port #
        char COMMAND_BEGIN = '$';
        char COMMAND_END {'~'};
        char COMMAND_PAN {'P'};
        char COMMAND_TILT {'T'};
        char COMMAND_REQUEST {'?'};
        char RESPONSE_SUCCESS {'Y'};
        char RESPONSE_FAILURE {'N'};
        char COMMAND_QUERY [SEND_BUF_SIZE] = {COMMAND_BEGIN,
                                    COMMAND_PAN,
                                    COMMAND_TILT,
                                    COMMAND_REQUEST,
                                    COMMAND_END};
};

#endif /* PANTILT_H_ */
