#pragma once

class RenderTarget {
public:
	static RenderTarget* mainRenderTarget;	
public:
	int OriginX;
	int OriginY;
	int Width;
	int Height;
	float displayRatio;
public:
	RenderTarget(int ox, int oy, int w, int h):
		OriginX(ox),
		OriginY(oy),
		Width(w),
		Height(h)
	{
		displayRatio = (float)Width / (float)Height;
	}
};

RenderTarget* RenderTarget::mainRenderTarget = NULL;