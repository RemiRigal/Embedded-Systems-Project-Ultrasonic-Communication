#include <cstdio>
#include "Serial.h"

int Serial::readLine()
{
    if (msg_length == 0) 
	return -1;

    unsigned char i;
    buffer = "";

    for (i=0; i<msg_length; i++)
    {	// read char
	unsigned char c = getchar();

	if (c == '\n' || c == '\r')
	{   // end of line, return # of char read
	    return i;
	} 
	else if (c >= 0 && c < 128) 
	{   // ASCII char, append it to buffer
	    buffer += c;
	} 
	else 
	{   // Unsupported char. Skip one char as UTF8 char above 127 are coded with 2*8bits char
	    // /!\ input must be in UTF8
	    getchar();
	    buffer += '_';
	}
    }
    printf("\n");

    return i;
}

int Serial::write(string msg) const
{
    return printf((msg + "\n").c_str());
}

const string Serial::getBuffer() const
{
    return buffer;
}

