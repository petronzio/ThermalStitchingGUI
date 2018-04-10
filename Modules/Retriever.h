#ifndef RETRIEVER_H_
#define RETRIEVER_H_
#include <QFile>
#include <QDir>
#include <QString>
#include <iostream>
#include <thread>
#include "Drivers/PanTilt.h"
#include "Drivers/Imager.h"
#include "Modules/Stitcher.h"

#define STATION_COUNT 5

class Retriever
{
	public:
        enum RunningStates { running, paused, complete, failed, idle };
        RunningStates RunningState;   // Manages the state of running.

        bool Initialize (PanTilt &panTilt, Imager &imager, Stitcher &stitcher);
        bool ProcessCommand (const char command [], int size);
        void BeginCapture ();
        void PauseCapture ();
        void ResetCapture ();
    private:
        const QString CAPTURE_DIRECTORY = QString ("./Modules/Captures/");
        const QString ORIG_FILE = QString (CAPTURE_DIRECTORY + "raw_capture.png");
        PanTilt _panTilt;               // Reference to PanTilt Driver.
        Imager _imager;                 // Reference to Imager Driver.
        Stitcher _stitcher;            // Reference to Stitching Module.
        std::thread _retrievalThread;   // Manages the retrieving action.
        void RetrievalThread ();        // Executes actual retrieving
        bool CopyImage (std::string newName);
        void PurgeCaptureDirectory ();
        int _stationCount;
        int PAN_STATIONS [STATION_COUNT] =
        {20,53,73,89,116};
        //{20,25,32,36,41,48,53,57,64,68,73,80,85,89,96,100,105,112,116,121,128,133,144,148,153};


};

#endif /* Retriever_H_ */
