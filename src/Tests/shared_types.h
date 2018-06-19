// This is generated file
#pragma once

namespace Pipelines
{
// Packing: Std430
struct BigInt final
{
	uint  value[2];    // offset: 0, align: 4
	uint  lastBit;    // offset: 8, align: 4

	BigInt ()
	{
		STATIC_ASSERT( sizeof(BigInt) == 12 );
		STATIC_ASSERT( (offsetof( BigInt, value ) == 0) and (sizeof( value ) == 8) );
		STATIC_ASSERT( (offsetof( BigInt, lastBit ) == 8) and (sizeof( lastBit ) == 4) );
	}
};

// Packing: Std140
struct BigIntTest_SSBO final
{
	uint  result;    // offset: 0, align: 4
	float  _padding0;    // offset: 4, align: 4
	float  _padding1;    // offset: 8, align: 4
	float  _padding2;    // offset: 12, align: 4

	BigIntTest_SSBO ()
	{
		STATIC_ASSERT( sizeof(BigIntTest_SSBO) == 16 );
		STATIC_ASSERT( (offsetof( BigIntTest_SSBO, result ) == 0) and (sizeof( result ) == 4) );
		STATIC_ASSERT( (offsetof( BigIntTest_SSBO, _padding0 ) == 4) and (sizeof( _padding0 ) == 4) );
		STATIC_ASSERT( (offsetof( BigIntTest_SSBO, _padding1 ) == 8) and (sizeof( _padding1 ) == 4) );
		STATIC_ASSERT( (offsetof( BigIntTest_SSBO, _padding2 ) == 12) and (sizeof( _padding2 ) == 4) );
	}
};

// Packing: Std140
struct Bruteforce_SSBO final
{
	uint  result;    // offset: 0, align: 4
	float  _padding0;    // offset: 4, align: 4
	float  _padding1;    // offset: 8, align: 4
	float  _padding2;    // offset: 12, align: 4

	Bruteforce_SSBO ()
	{
		STATIC_ASSERT( sizeof(Bruteforce_SSBO) == 16 );
		STATIC_ASSERT( (offsetof( Bruteforce_SSBO, result ) == 0) and (sizeof( result ) == 4) );
		STATIC_ASSERT( (offsetof( Bruteforce_SSBO, _padding0 ) == 4) and (sizeof( _padding0 ) == 4) );
		STATIC_ASSERT( (offsetof( Bruteforce_SSBO, _padding1 ) == 8) and (sizeof( _padding1 ) == 4) );
		STATIC_ASSERT( (offsetof( Bruteforce_SSBO, _padding2 ) == 12) and (sizeof( _padding2 ) == 4) );
	}
};

// Packing: Std430
struct Bruteforce_Atomics final
{
	uint  results;    // offset: 0, align: 4
	uint  bestResults;    // offset: 4, align: 4

	Bruteforce_Atomics ()
	{
		STATIC_ASSERT( sizeof(Bruteforce_Atomics) == 8 );
		STATIC_ASSERT( (offsetof( Bruteforce_Atomics, results ) == 0) and (sizeof( results ) == 4) );
		STATIC_ASSERT( (offsetof( Bruteforce_Atomics, bestResults ) == 4) and (sizeof( bestResults ) == 4) );
	}
};

// Packing: Std430
struct Bruteforce_Result final
{
	BigInt  funHash;    // offset: 0, align: 4
	BigInt  constHash;    // offset: 12, align: 4
	float  ticks;    // offset: 24, align: 4
	float  accuracy;    // offset: 28, align: 4

	Bruteforce_Result ()
	{
		STATIC_ASSERT( sizeof(Bruteforce_Result) == 32 );
		STATIC_ASSERT( (offsetof( Bruteforce_Result, funHash ) == 0) and (sizeof( funHash ) == 12) );
		STATIC_ASSERT( (offsetof( Bruteforce_Result, constHash ) == 12) and (sizeof( constHash ) == 12) );
		STATIC_ASSERT( (offsetof( Bruteforce_Result, ticks ) == 24) and (sizeof( ticks ) == 4) );
		STATIC_ASSERT( (offsetof( Bruteforce_Result, accuracy ) == 28) and (sizeof( accuracy ) == 4) );
	}
};

// Packing: Std430
struct TestCase final
{
	int  inArgs[2];    // offset: 0, align: 4
	int  result;    // offset: 8, align: 4

	TestCase ()
	{
		STATIC_ASSERT( sizeof(TestCase) == 12 );
		STATIC_ASSERT( (offsetof( TestCase, inArgs ) == 0) and (sizeof( inArgs ) == 8) );
		STATIC_ASSERT( (offsetof( TestCase, result ) == 8) and (sizeof( result ) == 4) );
	}
};

// Packing: Std430
struct Bruteforce_InputsSSBO final
{
	BigInt  initialHash;    // offset: 0, align: 4
	BigInt  constHash;    // offset: 12, align: 4
	float  maxAccuracy;    // offset: 24, align: 4
	int  numConstants;    // offset: 28, align: 4
	int  constants;    // offset: 32, align: 4
	TestCase  tests[10];    // offset: 36, align: 4

	Bruteforce_InputsSSBO ()
	{
		STATIC_ASSERT( sizeof(Bruteforce_InputsSSBO) == 156 );
		STATIC_ASSERT( (offsetof( Bruteforce_InputsSSBO, initialHash ) == 0) and (sizeof( initialHash ) == 12) );
		STATIC_ASSERT( (offsetof( Bruteforce_InputsSSBO, constHash ) == 12) and (sizeof( constHash ) == 12) );
		STATIC_ASSERT( (offsetof( Bruteforce_InputsSSBO, maxAccuracy ) == 24) and (sizeof( maxAccuracy ) == 4) );
		STATIC_ASSERT( (offsetof( Bruteforce_InputsSSBO, numConstants ) == 28) and (sizeof( numConstants ) == 4) );
		STATIC_ASSERT( (offsetof( Bruteforce_InputsSSBO, constants ) == 32) and (sizeof( constants ) == 4) );
		STATIC_ASSERT( (offsetof( Bruteforce_InputsSSBO, tests ) == 36) and (sizeof( tests ) == 120) );
	}
};

// Packing: Std430
struct Bruteforce_OutputsSSBO final
{
	Bruteforce_Atomics  stat;    // offset: 0, align: 4
	Bruteforce_Result  funcs[10000];    // offset: 8, align: 4

	Bruteforce_OutputsSSBO ()
	{
		STATIC_ASSERT( sizeof(Bruteforce_OutputsSSBO) == 320008 );
		STATIC_ASSERT( (offsetof( Bruteforce_OutputsSSBO, stat ) == 0) and (sizeof( stat ) == 8) );
		STATIC_ASSERT( (offsetof( Bruteforce_OutputsSSBO, funcs ) == 8) and (sizeof( funcs ) == 320000) );
	}
};

}	// Pipelines

namespace GX_STL::CompileTime::_ctime_hidden_ {
	template <> struct _IsPOD< Pipelines::BigInt > { static const bool value = true; };
	template <> struct _IsPOD< Pipelines::BigIntTest_SSBO > { static const bool value = true; };
	template <> struct _IsPOD< Pipelines::Bruteforce_SSBO > { static const bool value = true; };
	template <> struct _IsPOD< Pipelines::Bruteforce_Atomics > { static const bool value = true; };
	template <> struct _IsPOD< Pipelines::Bruteforce_Result > { static const bool value = true; };
	template <> struct _IsPOD< Pipelines::TestCase > { static const bool value = true; };
	template <> struct _IsPOD< Pipelines::Bruteforce_InputsSSBO > { static const bool value = true; };
	template <> struct _IsPOD< Pipelines::Bruteforce_OutputsSSBO > { static const bool value = true; };
}

