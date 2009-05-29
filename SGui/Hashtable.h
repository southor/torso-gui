#ifndef _STATE_GUI_HASHTABLE_H_
#define _STATE_GUI_HASHTABLE_H_

#include <list>

namespace SGui
{
	/**
	 * The shape of HashFunction:  int HashFunction(Key key);
	 */
	template <typename Element, Element NullElement, typename Key, class HashFunction>
	class Hashtable
	{
	private:
		typedef std::list<Element*> ElementGroup;
		ElementGroup *elements;

	public:
		
		Hashtable(int size);

		void insert(Element e, Key key);		

		Element get(Key key);

		
		

	};
};

#endif