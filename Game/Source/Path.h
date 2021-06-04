#ifndef __PATH_H__
#define __PATH_H__

#include "p2Point.h"

#define MAX_STEPS 25

class Animation;
struct Step
{
	uint framesDuration = 1;
	fPoint speed;
	Animation* animation = nullptr;
};

class Path
{
public:
	
	void PushBack(fPoint speed, uint frames, Animation* animation = nullptr);

	void Update();

	iPoint GetRelativePosition() const;

	Animation* GetCurrentAnimation();

	void Reset();

public:
	
	bool loop = true;

	Step steps[MAX_STEPS];

private:
	
	uint totalSteps = 0;

	uint currentStepFrame = 0;

	fPoint relativePosition = fPoint(0.0f, 0.0f);

	uint currentStep = 0;
};

#endif // __PATH_H__