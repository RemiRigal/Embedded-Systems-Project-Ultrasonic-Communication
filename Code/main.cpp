
#include <cstdio>
#include "miosix.h"
#include "serial.h"

using namespace std;
using namespace miosix;

int main()
{
    Serial serialIO;

    for(;;)
    {
	printf("-------------------------------------\n");
	printf("\tType a message:\n");
	printf("-------------------------------------\n");

	serialIO.readLine();

	printf("-------------------------------------\n");
	printf("\tMessage received:\n");
	printf("-------------------------------------\n");

	serialIO.write(serialIO.getBuffer());
    }
}
