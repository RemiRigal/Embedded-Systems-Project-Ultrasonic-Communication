#ifndef SERIAL_H
#define SERIAL_H

#include <string>

using namespace std;

class Serial
{
    public:
	// Read a line from stdin
	// Returns the number of read characters, or a negative value in case of error(s)
	int readLine();

	// Write a line containing the string 'msg' to stdout
	// Return the number of printed characters, or a negative value in case of errors
	int write(string msg) const;

	const string getBuffer() const;

    private:
	// maximum length of a msg readable at a time
	unsigned char const msg_length = 255;
	string buffer;
};

#endif //SERIAL_H
