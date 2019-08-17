#include "spritecomponent.h"
#include "actor.h"
#include "gamestage.h"
#include<DxLib.h>
#include"animdraw.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	, mImage(nullptr)
	, mDrawOrder(drawOrder)
	, mImgWidth(0)
	, mImgHeight(0)
{
	mOwner->GetGameStage()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGameStage()->RemoveSprite(this);
}

void SpriteComponent::Draw(int count)
{
	if (mImage)
	{
		Vector2 pos = mOwner->GetPosition();
		//���ƂŃA�j���[�V�����̕`�悪�ł���悤�ɂ���
		DrawGraph(pos.x, pos.y, mImage[0], TRUE);
	}
}

void SpriteComponent::SetImage(int* img)
{
	mImage = img;
	GetGraphSize(img[0], &mImgWidth, &mImgHeight);
}
