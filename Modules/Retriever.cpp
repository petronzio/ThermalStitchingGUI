#include "Retriever.h"

void Retriever::PurgeCaptureDirectory()
{
    QDir dir(CAPTURE_DIRECTORY);
    dir.setNameFilters(QStringList() << "*.*");
    dir.setFilter(QDir::Files);
    foreach(QString dirFile, dir.entryList())
    {
        dir.remove(dirFile);
    }
}

void Retriever::RetrievalThread ()
{
    std::cout << "Beginning Retrieval\n";
    int iCurrentTilt;
    int iCurrentPan;
    bool bContinue;
    bool bForwards = true;
    int panGoal;
    bool bPanReached = false;


    for (iCurrentTilt = 0; iCurrentTilt < _stationCount; iCurrentTilt++)
    {
        bContinue = false;
        if (bForwards)
        {
            iCurrentPan = 0;
            panGoal = _stationCount - 1;
        }
        else
        {
            iCurrentPan = _stationCount - 1;
            panGoal = 0;
        }

        bPanReached = false;
        while (!bPanReached)
        {
            if (RunningState == idle)
                return;
            if (RunningState == paused)
            {
                bContinue = true;
                continue;
            }

            std::cout <<"Retrieving image at:\tP(" << iCurrentPan
                     <<")\tT(" << iCurrentTilt<<")\n";
            _panTilt.PanPosition(PAN_STATIONS[iCurrentPan]);
            _panTilt.TiltPosition(PAN_STATIONS[iCurrentTilt]);

            if (iCurrentPan == 0 && iCurrentTilt == 0)
            {
                // Sleep for a longer time while the pan tilt orients itself.
                std::this_thread::sleep_for (std::chrono::milliseconds(2000));
            }

            // Once approached, retrieve an image
            // and create a renamed copy that reflects its index.
            //# This is a test. We're only polling for test photos.
            std::this_thread::sleep_for (std::chrono::milliseconds(100));
            if (_imager.CaptureImage ())
            {
                /*
                QString newFile = QString
                    (CAPTURE_DIRECTORY + "[%1],[%2].png")
                    .arg(iCurrentTilt).arg(iCurrentPan);
                QFile::copy(ORIG_FILE, newFile);
                */
                _stitcher.UpdateFinalImage
                        (static_cast<double>(PAN_STATIONS[iCurrentPan]),
                         static_cast<double>(PAN_STATIONS[iCurrentTilt]));
            }
            else
            {
                // Bail if an error is received.
                std::cout << "Error pulling in images. Bailing";
                RunningState = failed;
                return;
            }

            if (iCurrentPan == panGoal)
            {
                bPanReached = true;
                bForwards = !bForwards;
            }
            else
            {
                if (bForwards)
                    iCurrentPan++;
                else
                    iCurrentPan--;
            }
        }

        if (bContinue)
        {
            iCurrentTilt--;
            iCurrentPan--;
        }
    }

    // Once complete, change our running state.
    std::cout << "Retrieval Complete\n";
    RunningState = complete;

    // Save the final image.
    _stitcher.SaveImage ();
}

void Retriever::BeginCapture ()
{
    if (RunningState == running)
        return;

    // Purge the capture directory before
    // beginning any new capture.
    PurgeCaptureDirectory();


    RunningState = running;
    _retrievalThread = std::thread
            (&Retriever::RetrievalThread, this);
    _retrievalThread.detach();
}

void Retriever::PauseCapture ()
{
    if (RunningState == paused)
    {
        std::cout << "Capture Resumed\n";
        RunningState = running;
    }
    else if (RunningState == running)
    {
        std::cout << "Capture Paused\n";
        RunningState = paused;
    }
    else
    {
        std::cout << "No Capture in progress\n";
    }
}

void Retriever::ResetCapture ()
{
    std::cout << "Capture Reset\n";
    RunningState = idle;
}

bool Retriever::Initialize (PanTilt &panTilt, Imager &imager, Stitcher &stitcher)
{
    try
    {
        _panTilt = panTilt;
        _imager = imager;
        _stitcher = stitcher;
        RunningState = idle;
        _stationCount = STATION_COUNT;
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool Retriever::ProcessCommand (const char command [], int size)
{
    if (size == 1)
    {
        if (command [0] == 'B')
        {
            BeginCapture ();
            return true;
        }
        else if (command [0] == 'R')
        {
            ResetCapture ();
            return true;
        }
        else if (command [0] == 'P')
        {
            PauseCapture ();
            return true;
        }
        else
            return false;
    }
    else if (size == 3 && (command[2] >= '0' && command[2] <= '3')) // SR0 - SR3
    {
        return true;
    }
    else
        return false;
}
