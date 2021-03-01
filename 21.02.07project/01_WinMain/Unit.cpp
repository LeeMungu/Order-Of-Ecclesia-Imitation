#include "pch.h"
#include "Unit.h"

#include "Image.h"
void Unit::Release()
{
}

void Unit::Update()
{
}

void Unit::Render(HDC hdc)
{
	mImage->FrameRender(hdc, mRect.left, mRect.top, mIndexX, mIndexY);
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		RenderRect(hdc, mRect);
	}
}
