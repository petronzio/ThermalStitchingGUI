#ifndef IMAGER_H_
#define IMAGER_H_

#include <stdint.h>
#include <QImage>

#define PACKET_SIZE 164
#define PACKET_SIZE_UINT16 (PACKET_SIZE/2)
#define PACKETS_PER_FRAME 60
#define FRAME_SIZE_UINT16 (PACKET_SIZE_UINT16*PACKETS_PER_FRAME)
#define FPS 27;

class Imager
{
	public:
		bool Initialize ();
        bool ProcessCommand (const char command [], int size);
        bool CaptureImage ();
    private:
        void ReadPackets ();
        void ProcessImage ();
        QImage myImage;
        uint8_t result[PACKET_SIZE*PACKETS_PER_FRAME];
        uint16_t *frameBuffer;
};

#endif /* IMAGER_H_ */
