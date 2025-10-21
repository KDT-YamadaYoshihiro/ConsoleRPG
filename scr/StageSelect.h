#pragma once
#include "ScreenBase.h"

class StageSelectScreen : public ScreenBase {
    bool endFlag = false;
public:
    void Init() override;
    void Update() override;
    bool IsEnd() const override { return endFlag; }
};
