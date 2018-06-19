# auto generated file
cmake_minimum_required (VERSION 3.6.0)

#==================================================================================================
# project: Projects.ProgramSynthesis
#==================================================================================================
set( SOURCES 
	"Generators/Bruteforce/Bruteforce.glsl"
	"Generators/Bruteforce/BruteforceGenerator.cpp"
	"Generators/Bruteforce/BruteforceGenerator.h"
	"Generators/Bruteforce/BruteforceGenerator_Compiler.cpp"
	"Generators/Bruteforce/sw_bruteforce.cpp"
	"Tests/all_pipelines.h"
	"Tests/biginttest.cpp"
	"Tests/BigIntTest.ppln"
	"Tests/bruteforcetest.cpp"
	"Tests/BruteforceTest.ppln"
	"Tests/resources.as"
	"Tests/shared_types.h"
	"Tests/Test_BigInteger.cpp"
	"Tests/Test_Bruteforce.cpp"
	"Tests/Test_GpuBigInt.cpp"
	"Tests/Test_GpuBruteforce.cpp"
	"Generators/Fitness/FitnessFunctions.cpp"
	"Generators/Fitness/FitnessFunctions.h"
	"Generators/Fitness/Fitness_Bitwise.glsl"
	"Generators/Fitness/Fitness_FloatLinear.glsl"
	"CMakeLists.txt"
	"CodeGenApp.cpp"
	"CodeGenApp.h"
	"CodeGenApp_Script.cpp"
	"Common.h"
	"README.md"
	"Samples/test1.as"
	"Samples/test1_res.txt"
	"Samples/test2.as"
	"Samples/test2_res.txt"
	"Samples/test3.as"
	"Samples/test3_res.txt"
	"Samples/test4.as"
	"Samples/test4_res.txt"
	"Samples/test5.as"
	"Samples/test5_res.txt"
	"Samples/test6.as"
	"Samples/test6_res.txt"
	"Samples/test7.as"
	"Samples/test7_res.txt"
	"Samples/test8.as"
	"Generators/BigInt.glsl"
	"Generators/BigInteger.h"
	"Generators/Commands.cpp"
	"Generators/Commands.h"
	"Generators/Constants.inl.h"
	"Generators/GenFunctionSerializer.cpp"
	"Generators/GenFunctionSerializer.h"
	"Generators/IGenerator.h"
	"Generators/Mixed.h"
	"Generators/ResultSearch.cpp"
	"Generators/ResultSearch.h"
	"Generators/TestCase.h"
	"Generators/Utils.h" )
if (DEFINED ANDROID)
	add_library( "Projects.ProgramSynthesis" SHARED ${SOURCES} )
else()
	add_executable( "Projects.ProgramSynthesis" ${SOURCES} )
endif()
source_group( "Generators\\Bruteforce" FILES "Generators/Bruteforce/Bruteforce.glsl" "Generators/Bruteforce/BruteforceGenerator.cpp" "Generators/Bruteforce/BruteforceGenerator.h" "Generators/Bruteforce/BruteforceGenerator_Compiler.cpp" "Generators/Bruteforce/sw_bruteforce.cpp" )
source_group( "Tests" FILES "Tests/all_pipelines.h" "Tests/biginttest.cpp" "Tests/BigIntTest.ppln" "Tests/bruteforcetest.cpp" "Tests/BruteforceTest.ppln" "Tests/resources.as" "Tests/shared_types.h" "Tests/Test_BigInteger.cpp" "Tests/Test_Bruteforce.cpp" "Tests/Test_GpuBigInt.cpp" "Tests/Test_GpuBruteforce.cpp" )
source_group( "Generators\\Fitness" FILES "Generators/Fitness/FitnessFunctions.cpp" "Generators/Fitness/FitnessFunctions.h" "Generators/Fitness/Fitness_Bitwise.glsl" "Generators/Fitness/Fitness_FloatLinear.glsl" )
source_group( "" FILES "CMakeLists.txt" "CodeGenApp.cpp" "CodeGenApp.h" "CodeGenApp_Script.cpp" "Common.h" "README.md" )
source_group( "Samples" FILES "Samples/test1.as" "Samples/test1_res.txt" "Samples/test2.as" "Samples/test2_res.txt" "Samples/test3.as" "Samples/test3_res.txt" "Samples/test4.as" "Samples/test4_res.txt" "Samples/test5.as" "Samples/test5_res.txt" "Samples/test6.as" "Samples/test6_res.txt" "Samples/test7.as" "Samples/test7_res.txt" "Samples/test8.as" )
source_group( "Generators" FILES "Generators/BigInt.glsl" "Generators/BigInteger.h" "Generators/Commands.cpp" "Generators/Commands.h" "Generators/Constants.inl.h" "Generators/GenFunctionSerializer.cpp" "Generators/GenFunctionSerializer.h" "Generators/IGenerator.h" "Generators/Mixed.h" "Generators/ResultSearch.cpp" "Generators/ResultSearch.h" "Generators/TestCase.h" "Generators/Utils.h" )
set_property( TARGET "Projects.ProgramSynthesis" PROPERTY FOLDER "Projects" )
target_include_directories( "Projects.ProgramSynthesis" PUBLIC "C:/Projects/graphxgenengine/Projects/ProgramSynthesis" )
target_include_directories( "Projects.ProgramSynthesis" PUBLIC "C:/Projects/graphxgenengine/External" )
target_include_directories( "Projects.ProgramSynthesis" PUBLIC "${EXTERNALS_PATH}" )
target_include_directories( "Projects.ProgramSynthesis" PUBLIC "C:/Projects/graphxgenengine/Core/.." )
target_link_libraries( "Projects.ProgramSynthesis" "Engine.Platforms" )
target_link_libraries( "Projects.ProgramSynthesis" "Engine.PipelineCompiler" )
target_link_libraries( "Projects.ProgramSynthesis" "Core.Script" )
# compiler
set_target_properties( "Projects.ProgramSynthesis" PROPERTIES LINK_FLAGS_RELEASE ${PROJECTS_SHARED_LINKER_FLAGS_RELEASE} )
set_target_properties( "Projects.ProgramSynthesis" PROPERTIES LINK_FLAGS_PROFILE ${PROJECTS_SHARED_LINKER_FLAGS_PROFILE} )
target_compile_definitions( "Projects.ProgramSynthesis" PRIVATE $<$<CONFIG:Debug>: ${PROJECTS_SHARED_DEFINES_DEBUG}> )
set_target_properties( "Projects.ProgramSynthesis" PROPERTIES LINK_FLAGS_DEBUGANALYZE ${PROJECTS_SHARED_LINKER_FLAGS_DEBUGANALYZE} )
target_compile_definitions( "Projects.ProgramSynthesis" PRIVATE $<$<CONFIG:DebugAnalyze>: ${PROJECTS_SHARED_DEFINES_DEBUGANALYZE}> )
target_compile_options( "Projects.ProgramSynthesis" PRIVATE $<$<CONFIG:Profile>: ${PROJECTS_SHARED_CXX_FLAGS_PROFILE}> )
target_compile_options( "Projects.ProgramSynthesis" PRIVATE $<$<CONFIG:Release>: ${PROJECTS_SHARED_CXX_FLAGS_RELEASE}> )
target_compile_definitions( "Projects.ProgramSynthesis" PRIVATE $<$<CONFIG:Profile>: ${PROJECTS_SHARED_DEFINES_PROFILE}> )
target_compile_definitions( "Projects.ProgramSynthesis" PRIVATE $<$<CONFIG:Release>: ${PROJECTS_SHARED_DEFINES_RELEASE}> )
set_target_properties( "Projects.ProgramSynthesis" PROPERTIES LINK_FLAGS_DEBUG ${PROJECTS_SHARED_LINKER_FLAGS_DEBUG} )
target_compile_options( "Projects.ProgramSynthesis" PRIVATE $<$<CONFIG:DebugAnalyze>: ${PROJECTS_SHARED_CXX_FLAGS_DEBUGANALYZE}> )
target_compile_options( "Projects.ProgramSynthesis" PRIVATE $<$<CONFIG:Debug>: ${PROJECTS_SHARED_CXX_FLAGS_DEBUG}> )



