#ifndef _STATE_GUI_HASHTABLE_CPP_
#define _STATE_GUI_HASHTABLE_CPP_

#include "Hashtable.h"

namespace SGui
{
	template <typename Element, Element NullElement, typename Key, class HashFunction>
	Hashtable<Element, NullElement, Key, HashFunction>
		::Hashtable(int size)
	{
		dAssert(size >= 0);
		elements = new ElementGroup[size];
	}

	template <typename Element, Element NullElement, typename Key, class HashFunction>
	void Hashtable<Element, NullElement, Key, HashFunction>
		::insert(Element e, Key key)
	{
		HashFunction hashFunction;
		int i = hashFunction(key);
		dAssert(i >= 0);
		elements[i].push_back(e);
	}

	template <typename Element, Element NullElement, typename Key, class HashFunction>
	Element Hashtable<Element, NullElement, Key, HashFunction>
		::get(Key key)
	{
		// not implemented yet
	}
};

#endif