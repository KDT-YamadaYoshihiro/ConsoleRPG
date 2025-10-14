#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "ScreenBase.h"

class Result : public ScreenBase {
public:
	// XVˆ—
	void Update() override;
	// •`‰æˆ—
	void Draw() const override;
};

