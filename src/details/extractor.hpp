#ifndef vlinder_english_details_extractor_hpp
#define vlinder_english_details_extractor_hpp

#include <deque>
#include <vector>

namespace Vlinder { namespace English { namespace Details {
class Extractor
{
public :
	Extractor(std::vector< unsigned char > const &data);

	unsigned int get(unsigned int max);
	bool empty() const { return data_.empty(); }

private :
	unsigned char latest_byte_;
	unsigned int bits_remaining_ = 0;
	std::deque< unsigned char > data_;

	static unsigned char const mask__[9];
};
}}}

#endif
