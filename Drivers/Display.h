#ifndef Display_H_
#define Display_H_

class Display
{
	public:
        Display();
        virtual ~Display();
		bool Initialize ();
        bool ProcessCommand (const char command [], int size);
};

#endif /* Display_H_ */
