#include <memory>
#include <DxLib.h>
#include "SceneMng.h"
#include "GameOver.h"



GameOver::GameOver()
{
}


GameOver::~GameOver()
{
}

unique_Base GameOver::Update(unique_Base own)
{
	//return std::make_unique<SelectScene>();

      return std::move(own);
}
