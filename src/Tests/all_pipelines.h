// This is generated file
#pragma once

#include "Engine/Platforms/Engine.Platforms.h"

#ifdef GRAPHICS_API_SOFT
#include "Engine/Platforms/Soft/ShaderLang/SWLang.h"
#endif

namespace Pipelines
{
	using namespace GX_STL;
	using namespace GX_STL::GXTypes;
	using namespace GX_STL::GXMath;

	using namespace Engine::Platforms;
}

#include "shared_types.h"

namespace Pipelines
{
// From file 'biginttest.cpp'
void Create_biginttest (PipelineTemplateDescription& descr);

// From file 'bruteforcetest.cpp'
void Create_bruteforcetest (PipelineTemplateDescription& descr);

}	// Pipelines
