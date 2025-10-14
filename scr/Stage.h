#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
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
	// •`‰æˆ—
	void Draw() const override;
};

