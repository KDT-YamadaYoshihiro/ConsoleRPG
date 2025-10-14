#pragma once
#include "ScreenBase.h"

enum class MODE {
	SELECT,
	COF,
	TRANSITION,
};

class Stage : public ScreenBase {

	MODE mode;

public:
	// XVˆ—
	void Update() override;
};

