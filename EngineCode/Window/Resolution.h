#pragma once
#include <TypeDefs/TypeDefs.h>
class WindowResolution
{
public:
	WindowResolution();
	WindowResolution(const engIntU32 Width,const engIntU32 Height);
	void SetResolution(const engIntU32 Width,const engIntU32 Height);
	const engIntU32 GetWidth() const;
	const engIntU32 GetHeight() const;
private:
	engIntU32 m_Width = 0;
	engIntU32 m_Height = 0;
	bool ResolutionInited = false;
};