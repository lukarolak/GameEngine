#include <Window/Resolution.h>
#include <Debuging/Assert.h>
WindowResolution::WindowResolution()
{
}

WindowResolution::WindowResolution(const engIntU32 Width,const engIntU32 Height)
{
	SetResolution(Width, Height);
}

void WindowResolution::SetResolution(const engIntU32 Width,const engIntU32 Height)
{
	m_Width = Width;
	m_Height = Height;
	ResolutionInited = true;
}

const engIntU32 WindowResolution::GetWidth() const
{
	ENG_ASSERT(ResolutionInited);
	return m_Width;
}

const engIntU32 WindowResolution::GetHeight() const
{
	ENG_ASSERT(ResolutionInited);
	return m_Height;
}
