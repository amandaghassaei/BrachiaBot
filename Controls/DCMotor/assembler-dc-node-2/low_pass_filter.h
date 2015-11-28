/*
 *  low_pass_filter.h
 *  
 *
 *  Created by William Langford on 3/29/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef low_pass_filter_h
#define low_pass_filter_h

// #include "WProgram.h"
 #include <Arduino.h>


class LPFilter
{
	public:
		LPFilter();
		void init(float fbreak, float y_init=0);
		float step(float u);
		float y;
		unsigned long dt;
		unsigned long time;
	private:
		float _w;
};

#endif
