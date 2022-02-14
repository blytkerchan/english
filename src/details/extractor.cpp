#include "extractor.hpp"
#include <algorithm>

using namespace std;

namespace Vlinder { namespace English { namespace Details {
/*static */unsigned char const Extractor::mask__[9] = { 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff };

Extractor::Extractor(vector< unsigned char > const &data)
	: data_(data.begin(), data.end())
{}

unsigned int Extractor::get(unsigned int max)
{
	// get the bits in max
	unsigned int bit(1);
	unsigned int count(0);
	while (bit <= max)
	{
		bit *= 2;
		++count;
	}
	
	if (count <= bits_remaining_)
	{
		unsigned int bits(bits_remaining_);
		unsigned char byte(latest_byte_);
		while (bits > count)
		{
			byte /= 2;
			--bits;
		}
		byte &= mask__[bits];
		bits_remaining_ -= count;
		return min< unsigned int >(max, byte);
	}
	unsigned int retval(latest_byte_ & mask__[bits_remaining_]);
	count -= bits_remaining_;

	unsigned int bytes_needed((count + 7) / 8);
	bits_remaining_ = count % 8;
	for (unsigned int b(0); b < bytes_needed; ++b)
	{
		if (!data_.empty())
		{
			latest_byte_ = data_.front();
			data_.pop_front();
		}
		else
		{
			latest_byte_ = 0;
		}
		if (count >= 8)
		{
			retval *= 256;
			retval |= latest_byte_;
			count -= 8;
		}
		else
		{
			unsigned char last_byte(latest_byte_);
			last_byte >>= (8 - count);
			last_byte &= mask__[count];
			retval <<= count;
			retval |= last_byte;
		}
	}

	return min(max, retval);
}

}}}
