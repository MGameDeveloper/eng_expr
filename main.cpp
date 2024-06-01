#include "Engine/masEngine.h"


s32 main(s32 argc, const char** argv)
{
	masEngine Engine(L"MasEngine", 1200, 800);

	Engine.Run();

	return 0;
}