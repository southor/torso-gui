#ifndef _STATE_GUI_BASIC_CPP_
#define _STATE_GUI_BASIC_CPP_

#include "basic.h"

namespace SGui
{

	void TxtrCoord::rescale(const Vecd &rescaleVec)
	{
		double tmpS = static_cast<double>(s) * rescaleVec.x;
		double tmpT = static_cast<double>(t) * rescaleVec.y;
		s = static_cast<float>(tmpS);
		t = static_cast<float>(tmpT);
	}
};

#endif