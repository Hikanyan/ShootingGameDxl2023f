#pragma once
#include "Player.h"

class IPlayerController {
public:
    virtual ~IPlayerController() = default;
    virtual void Update(Player& player) = 0;
};
