#include<iostream>
#include<bitset>

using namespace std;

using byte_t = unsigned char;
using word_t = uint32_t;

int main()
{
	byte_t bytes[4] = {0x01, 0x01, 0x01, 0x01};
	word_t *word = (word_t*)bytes;

	cout << hex << (int)(*word)<<endl;
}