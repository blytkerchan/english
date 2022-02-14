#include "poet.hpp"
#include <sstream>
#include <ostream>
#include "details/extractor.hpp"
#include "words/adjectives.hpp"
#include "words/adverbs.hpp"
#include "words/articles.hpp"
#include "words/nouns.hpp"
#include "words/prepositions.hpp"
#include "words/verbsi.hpp"
#include "words/verbst.hpp"

using namespace std;

namespace Vlinder { namespace English {
namespace {
	bool branch(Details::Extractor& extractor)
	{
		return extractor.get(1) == 1;
	}
	template < unsigned int N >
	void word(ostream& os, Details::Extractor& extractor, char const* (&words)[N])
	{
		os << words[extractor.get(N - 1)];
	}
	void nounPhrase(ostream& os, Details::Extractor& extractor)
	{
		word(os, extractor, Words::articles__);
		if (branch(extractor))
		{
			os << " ";
			word(os, extractor, Words::adjectives__);
		}
		os << " ";
		word(os, extractor, Words::nouns__);
	}
	void sentence(ostream& os, Details::Extractor& extractor)
	{
		nounPhrase(os, extractor);
		if (branch(extractor))
		{
			os << " ";
			word(os, extractor, Words::verbs_t__);
			os << " ";
			nounPhrase(os, extractor);
		}
		else
		{
			os << " ";
			word(os, extractor, Words::verbs_i__);
		}
		if (branch(extractor))
		{
			os << " ";
			word(os, extractor, Words::adverbs__);
		}
		if (branch(extractor))
		{
			os << " ";
			word(os, extractor, Words::prepositions__);
			os << " ";
			nounPhrase(os, extractor);
		}
		os << endl;
	}
}
std::string createPoem(std::vector< unsigned char > const& data)
{
	Details::Extractor extractor(data);
	stringstream ss;
	while (!extractor.empty())
	{
		sentence(ss, extractor);
	}
	return ss.str();
}

}}

