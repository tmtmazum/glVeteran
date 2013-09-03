#ifndef FRAME_EVAL_H
#define FRAME_EVAL_H

#include <map>
#include <cassert>

struct FrameEval
{
    struct FrameInst
    {
	float numPrimary;
	int evalType;
	float numSecondary;
	int durationFrames;

	int currentFrame;
    };

    enum types
    {
	INCR_TO,
	INCR_BY,
	INCR_TO_LINEAR,
	INCR_TO_QUADRATIC,
	INCR_TO_CUBIC,
	INCR_BY_LINEAR,
	INCR_BY_QUADRATIC,
	INCR_BY_CUBIC
    };
    
    std::map< char, FrameInst > FrameVars;
    
    float operator()(char label, float nPrim , int evType, float nSec, int durFrames, int curFrame = 0)
    {
	std::map<char,FrameInst>::iterator it = FrameVars.find(label);
	if(it==FrameVars.end())
	{
	    FrameInst FI;
	    FI.numPrimary = nPrim;
	    FI.evalType = evType;
	    FI.numSecondary = nSec;
	    FI.durationFrames = durFrames;
	    FI.currentFrame = curFrame;
	    
	    FrameVars[label] = ( FI );
	    return FI.numPrimary;
	}
	else
	{
	    return get(it);
	}
    }
    
    void get(char label)
    {
	std::map<char,FrameInst>::iterator it = FrameVars.find(label);
	assert(it!=FrameVars.end());
	get(it);
    }
    
    float get(std::map<char,FrameInst>::iterator it)
    {
	if(it->second.currentFrame < 0)
	{
	    it->second.currentFrame++;
	    return it->second.numPrimary;
	}
	float& numSec = it->second.numSecondary;
	float& numPrim = it->second.numPrimary;
	int& durationFrames = it->second.durationFrames;
	int& currentFrame = it->second.currentFrame;
	switch(it->second.evalType)
	{
	    case INCR_TO:
	    {	// LINEAR
		float incr_change = numSec / durationFrames;
		if(currentFrame >= durationFrames)
		    return incr_change*(durationFrames);
		else
		{
		    currentFrame++;
		    return incr_change*(currentFrame);
		}
	    break;
	    }
	    case INCR_BY:
	    {
		if(currentFrame >= durationFrames)
		    return durationFrames*numSec + numPrim;

		    currentFrame++;
		float incr_change = currentFrame*numSec;
		return incr_change + numPrim;
	    }
	    case INCR_BY_LINEAR:
	    {
		if(currentFrame >= durationFrames)
		    return durationFrames*durationFrames*numSec + numPrim;
		
		    currentFrame++;
		float frameMult = currentFrame;
		float incr_change = frameMult*numSec;
		return incr_change + numPrim;
	    }
	    case INCR_TO_QUADRATIC:
	    {
		if(currentFrame >= durationFrames)
		    return numSec;
		
		currentFrame++;
		float incr_rate = numSec / (durationFrames*durationFrames);
		return currentFrame*currentFrame*incr_rate;
	    }
	    case INCR_TO_CUBIC:
	    {
		if(currentFrame >= durationFrames)
		    return numSec;
		
		currentFrame++;
		float incr_rate = numSec / (durationFrames*durationFrames*durationFrames);
		return currentFrame*currentFrame*currentFrame*incr_rate;
	    }
	    case INCR_BY_QUADRATIC:
	    {
		if(it->second.currentFrame >= it->second.durationFrames)
		    return it->second.durationFrames*it->second.durationFrames*it->second.numSecondary + it->second.numPrimary;
		
		    it->second.currentFrame++;
		float frameMult = it->second.currentFrame;
		float incr_change = frameMult*frameMult*it->second.numSecondary;
		return incr_change + it->second.numPrimary;
	    }
	    case INCR_BY_CUBIC:
	    {
		if(it->second.currentFrame >= it->second.durationFrames)
		    return it->second.durationFrames*it->second.durationFrames*it->second.numSecondary + it->second.numPrimary;

		    it->second.currentFrame++;
		float frameMult = it->second.currentFrame;
		float incr_change = frameMult*frameMult*frameMult*it->second.numSecondary;
		return incr_change + it->second.numPrimary;
	    }
	}
    }
};

// -- Example
/*
void updateFrame()
{
    static FrameEval FE;
    PosXY pos(a,b);
    PosXY size(c,FE('d',0.1,FrameEval::INCR_TO,0.9,25));
    
}*/

#endif
