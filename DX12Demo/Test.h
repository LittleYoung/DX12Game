#pragma once
#include "GameApp.h"

class Test :public GameApp 
{
public:
	Test(HINSTANCE hInstance);

	virtual void Update(const GameTimer& gt) override;
	virtual void Render(const GameTimer& gt) override;
};