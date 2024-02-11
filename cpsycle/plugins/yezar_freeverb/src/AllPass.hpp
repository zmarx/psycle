#pragma once
// #include <psycle/helpers/math/erase_denormals.hpp>

// Allpass filter declaration
//
// Written by Jezar at Dreampoint, June 2000
// http://www.dreampoint.co.uk
// This code is public domain

#include <operations.h>

class allpass
{
public:
					allpass();
	virtual			~allpass();
			void	setbuffer(int samples);
	inline  float	process(float inp);
			void	mute();
			void	setfeedback(float val);
			float	getfeedback();
private:
	void			deletebuffer();
	float			*buffer;
	float			feedback;
	int				bufsize;
	int				bufidx;
};

// Big to inline - but crucial for speed

inline float allpass::process(float input)
{
	float bufout = buffer[bufidx];
	float output = -input + bufout;
	float bufin = input + (bufout*feedback);

	dsp.erase_all_nans_infinities_and_denormals(&bufin, 1);
	// psycle::helpers::math::fast_erase_denormals_inplace(bufin);
	buffer[bufidx] = bufin;

	if(++bufidx>=bufsize) bufidx = 0;

	return output;
}
