#include <iostream>
#include "Imager.h"
#include "Third-Party/Lepton/SPI.h"
#include "Third-Party/Lepton/Palettes.h"

bool Imager::Initialize (void)
{
    //create the initial image
    myImage = QImage(80, 60, QImage::Format_RGB888);

    // Open the SPI port and attempt to read in an image.
    std::cout << "\t\tOpening SPI Port\n";
    SpiOpenPort (0);
    std::cout << "\t\tCapturing Test Image\n\t\t\t\t\t\t";
    return CaptureImage ();
}

void Imager::ReadPackets ()
{
    //read data packets from lepton over SPI
    int resets = 0;
    for(int j=0; j<PACKETS_PER_FRAME; j++)
    {
        //if it's a drop packet, reset j to 0, set to -1 so he'll be at 0 again loop
        read (spi_cs0_fd, result + sizeof (uint8_t) * PACKET_SIZE * j, sizeof (uint8_t)* PACKET_SIZE);
        int packetNumber = result [j*PACKET_SIZE+1];
        if(packetNumber != j)
        {
            j = -1;
            resets += 1;
            usleep(1000);
            //Note: we've selected 750 resets as an arbitrary limit, since there should never be 750 "null" packets between two valid transmissions at the current poll rate
            //By polling faster, developers may easily exceed this count, and the down period between frames may then be flagged as a loss of sync
            if(resets == 750)
            {
                SpiClosePort(0);
                usleep(750000);
                SpiOpenPort(0);
            }
        }
    }
}

void Imager::ProcessImage ()
{
    frameBuffer = (uint16_t *)result;
    int row, column;
    uint16_t value;
    uint16_t minValue = 65535;
    uint16_t maxValue = 0;
    for(int i=0;i<FRAME_SIZE_UINT16;i++)
    {
        //skip the first 2 uint16_t's of every packet, they're 4 header bytes
        if(i % PACKET_SIZE_UINT16 < 2)
            continue;

        //flip the MSB and LSB at the last second
        int temp = result[i*2];
        result[i*2] = result[i*2+1];
        result[i*2+1] = temp;

        value = frameBuffer [i];
        if (value > maxValue)
            maxValue = value;
        if (value < minValue)
            minValue = value;

        column = i % PACKET_SIZE_UINT16 - 2;
        row = i / PACKET_SIZE_UINT16 ;
    }

    float diff = maxValue - minValue;
    float scale = 255/diff;
    QRgb color;
    for(int i=0;i<FRAME_SIZE_UINT16;i++)
    {
        if(i % PACKET_SIZE_UINT16 < 2)
            continue;

        value = (frameBuffer[i] - minValue) * scale;
        const int *colormap = colormap_ironblack;
        color = qRgb(colormap[3*value], colormap[3*value+1], colormap[3*value+2]);
        column = (i % PACKET_SIZE_UINT16 ) - 2;
        row = i / PACKET_SIZE_UINT16;
        myImage.setPixel(column, row, color);
    }
}

bool Imager::CaptureImage ()
{
    ReadPackets ();
    ProcessImage ();

    return myImage.save("./Modules/Captures/raw_capture.png");
}

bool Imager::ProcessCommand (const char command [], int size)
{
	if (size == 1)
	{
		if (command [0] == 'C')
        {
            std::cout << "Imager Raw Capture\n";
            return CaptureImage ();
        }
		else
            return false;
	}

    return false;
}
