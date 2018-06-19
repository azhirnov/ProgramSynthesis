// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#include "Engine/Platforms/Engine.Platforms.h"

#ifdef GRAPHICS_API_SOFT
#include "Engine/Platforms/Soft/ShaderLang/SWLang.h"
#endif

#ifdef GRAPHICS_API_SOFT
namespace SWShaderLang {
namespace {

# ifdef _MSC_VER
#	pragma warning (push)
#	pragma warning (1: 4456)
# endif // _MSC_VER

#	define INOUT
#	define IN
#	define OUT

	struct BigInt
	{
		SArr<UInt,1> value;
		UInt lastBit;
	
		BigInt () {}
		BigInt (BigInt &&) = default;
		BigInt (const BigInt &) = default;
		explicit BigInt(const SArr<UInt,1> &value, const UInt &lastBit) : value{value}, lastBit{lastBit} {}
	
		BigInt& operator = (BigInt &&) = default;
		BigInt& operator = (const BigInt &) = default;
		Bool operator == (const BigInt &right) const {
			return	all( value == right.value ) &&
					all( lastBit == right.lastBit );
		}
		Bool operator != (const BigInt &right) const { return !(*this == right); }
	
	};
	
	struct CmdNode
	{
		UInt id;
		SArr<Int,3> args;
		Int argsCount;
		Int result;
	
		CmdNode () {}
		CmdNode (CmdNode &&) = default;
		CmdNode (const CmdNode &) = default;
		explicit CmdNode(const UInt &id, const SArr<Int,3> &args, const Int &argsCount, const Int &result) : id{id}, args{args}, argsCount{argsCount}, result{result} {}
	
		CmdNode& operator = (CmdNode &&) = default;
		CmdNode& operator = (const CmdNode &) = default;
		Bool operator == (const CmdNode &right) const {
			return	all( id == right.id ) &&
					all( args == right.args ) &&
					all( argsCount == right.argsCount ) &&
					all( result == right.result );
		}
		Bool operator != (const CmdNode &right) const { return !(*this == right); }
	
	};
	
	struct Bruteforce_Atomics
	{
		Atomic<UInt> results;
		Atomic<UInt> bestResults;
	};
	
	struct Bruteforce_Result
	{
		BigInt funHash;
		BigInt constHash;
		Float ticks;
		Float accuracy;
	
		Bruteforce_Result () {}
		Bruteforce_Result (Bruteforce_Result &&) = default;
		Bruteforce_Result (const Bruteforce_Result &) = default;
		explicit Bruteforce_Result(const BigInt &funHash, const BigInt &constHash, const Float &ticks, const Float &accuracy) : funHash{funHash}, constHash{constHash}, ticks{ticks}, accuracy{accuracy} {}
	
		Bruteforce_Result& operator = (Bruteforce_Result &&) = default;
		Bruteforce_Result& operator = (const Bruteforce_Result &) = default;
		Bool operator == (const Bruteforce_Result &right) const {
			return	all( funHash == right.funHash ) &&
					all( constHash == right.constHash ) &&
					all( ticks == right.ticks ) &&
					all( accuracy == right.accuracy );
		}
		Bool operator != (const Bruteforce_Result &right) const { return !(*this == right); }
	
	};
	
	struct TestCase
	{
		SArr<Int,1> inArgs;
		Int result;
	
		TestCase () {}
		TestCase (TestCase &&) = default;
		TestCase (const TestCase &) = default;
		explicit TestCase(const SArr<Int,1> &inArgs, const Int &result) : inArgs{inArgs}, result{result} {}
	
		TestCase& operator = (TestCase &&) = default;
		TestCase& operator = (const TestCase &) = default;
		Bool operator == (const TestCase &right) const {
			return	all( inArgs == right.inArgs ) &&
					all( result == right.result );
		}
		Bool operator != (const TestCase &right) const { return !(*this == right); }
	
	};
	
	struct Bruteforce_InputsSSBO
	{
		BigInt initialHash;
		BigInt constHash;
		Float maxAccuracy;
		Int numConstants;
		SArr<Int,3> constants;
		SArr<TestCase,20> tests;
	
		Bruteforce_InputsSSBO () {}
		Bruteforce_InputsSSBO (Bruteforce_InputsSSBO &&) = default;
		Bruteforce_InputsSSBO (const Bruteforce_InputsSSBO &) = default;
		explicit Bruteforce_InputsSSBO(const BigInt &initialHash, const BigInt &constHash, const Float &maxAccuracy, const Int &numConstants, const SArr<Int,3> &constants, const SArr<TestCase,20> &tests) : initialHash{initialHash}, constHash{constHash}, maxAccuracy{maxAccuracy}, numConstants{numConstants}, constants{constants}, tests{tests} {}
	
		Bruteforce_InputsSSBO& operator = (Bruteforce_InputsSSBO &&) = default;
		Bruteforce_InputsSSBO& operator = (const Bruteforce_InputsSSBO &) = default;
		Bool operator == (const Bruteforce_InputsSSBO &right) const {
			return	all( initialHash == right.initialHash ) &&
					all( constHash == right.constHash ) &&
					all( maxAccuracy == right.maxAccuracy ) &&
					all( numConstants == right.numConstants ) &&
					all( constants == right.constants ) &&
					all( tests == right.tests );
		}
		Bool operator != (const Bruteforce_InputsSSBO &right) const { return !(*this == right); }
	
	};
	
	struct NodeArray
	{
		SArr<CmdNode,12> nodes;
		Int count;
	
		NodeArray () {}
		NodeArray (NodeArray &&) = default;
		NodeArray (const NodeArray &) = default;
		explicit NodeArray(const SArr<CmdNode,12> &nodes, const Int &count) : nodes{nodes}, count{count} {}
	
		NodeArray& operator = (NodeArray &&) = default;
		NodeArray& operator = (const NodeArray &) = default;
		Bool operator == (const NodeArray &right) const {
			return	all( nodes == right.nodes ) &&
					all( count == right.count );
		}
		Bool operator != (const NodeArray &right) const { return !(*this == right); }
	
	};
	
	struct Bruteforce_OutputsSSBO
	{
		Bruteforce_Atomics stat;
		SArr<Bruteforce_Result,10000> funcs;
	};
	
	
	//---------------------------------
	
	static UInt BitScanReverse (const UInt x);
	static Int MaxValue (const Int x);
	static Int MaxValue_int ();
	static Float Fitness_FloatLinear (IN Int a, IN Int b);
	static Float ValueDifference (IN Int a, IN Int b);
	static Int CallFunction (const UInt id, const SArr<Int,3> args, const Int argsCount);
	static Int GetFunctionArgsCount (const UInt id);
	static UInt GetFunctionTicks (const UInt id);
	static void BigInt_Create (OUT BigInt &bi);
	static void BigInt_Add (INOUT BigInt &bi, IN UInt right);
	static void BigInt_Add (INOUT BigInt &bi, const BigInt right);
	static Bool BigInt_IsZero (const BigInt bi, const UInt pos);
	static UInt BigInt_Read (const BigInt bi, IN UInt pos, const UInt count);
	static UInt _BigInt_CalcBits (const BigInt bi, const UInt i);
	static void Node_Create (OUT CmdNode &n);
	static Bool BuildCommandsList (const BigInt hash, const Int maxInputs, OUT Float &outTicks, INOUT NodeArray &commands);
	static void RunCommands (INOUT NodeArray &commands, const Int maxInputs, const SArr<Int,1> inArgs, const SArr<Int,3> constants);
	static UInt ToMask (const UInt x);
	static Bool IsZero (const Float x);
	
	//---------------------------------
	
	static Bool IsZero (const Float x)
	{
		return (abs(x) < Float(0.00001f));
	}
	
	
	static UInt ToMask (const UInt x)
	{
		return ( ((x < UInt(0u))) ? (UInt(0u)) : (( ((x < UInt(32u))) ? (((UInt(1u) << x) - UInt(1u))) : (UInt(4294967295u)) )) );
	}
	
	
	static UInt BitScanReverse (const UInt x)
	{
		return UInt(findMSB(x));
	}
	
	
	static Int MaxValue_int ()
	{
		return Int(2147483647);
	}
	
	
	static Int MaxValue (const Int x)
	{
		return MaxValue_int();
	}
	
	
	static Float Fitness_FloatLinear (IN Int a, IN Int b)
	{
		if (((((a & Int((-2147483647 - 1))) == (b & Int((-2147483647 - 1)))) && ((a & Int(1073741824)) != Int(0))) && ((b & Int(1073741824)) != Int(0))))
		{
			return Float(9.99999968e+37f);
		;
		}
		;
		if (((a - b) == Int(0)))
		{
			return Float(0.0f);
		}
		;
		Float diff = Float(glm::abs((a - b)));
		;
		Float div = Float(abs(a));
		;
		return ( ((div > Float(0.0f))) ? ((diff / div)) : (Float(9.99999968e+37f)) );
	}
	
	
	static Float ValueDifference (IN Int a, IN Int b)
	{
		return Fitness_FloatLinear(a, b);
	}
	
	
	static Int CallFunction (const UInt id, const SArr<Int,3> args, const Int argsCount)
	{
		switch( (id & UInt(15u)) )
		{
		case Int(0): return -((args[Int(0)]));
		;
		case Int(1): return ~((args[Int(0)]));
		;
		case Int(2): return (args[Int(0)]);
		;
		case Int(3): return ((args[Int(0)]) + (args[Int(1)]));
		;
		case Int(4): return ((args[Int(0)]) & (args[Int(1)]));
		;
		case Int(5): return ((args[Int(0)]) | (args[Int(1)]));
		;
		case Int(6): return ((args[Int(0)]) ^ (args[Int(1)]));
		;
		case Int(7): return ((args[Int(0)]) << ((args[Int(1)]) & Int(31)));
		;
		case Int(8): return ((args[Int(0)]) << ((args[Int(1)]) & Int(31)));
		;
		case Int(9): return findMSB((args[Int(0)]));
		;
		case Int(10): return ((args[Int(0)]) * (args[Int(1)]));
		;
		case Int(11): return ( (((args[Int(1)]) != Int(0))) ? (((args[Int(0)]) / (args[Int(1)]))) : (Int(0)) );
		;
		case Int(12): return ( (((args[Int(1)]) != Int(0))) ? (((args[Int(0)]) % (args[Int(1)]))) : (Int(0)) );
		;
		case Int(13): return ( (((args[Int(0)]) < (args[Int(1)]))) ? (Int(1)) : (Int(-1)) );
		;
		case Int(14): return ( (((args[Int(0)]) > (args[Int(1)]))) ? (Int(1)) : (Int(-1)) );
		;
		case Int(15): return ( (((args[Int(0)]) >= Int(0))) ? ((args[Int(1)])) : ((args[Int(2)])) );
		;
		}
		;
		return MaxValue(Int(0));
	}
	
	
	static Int GetFunctionArgsCount (const UInt id)
	{
		switch( (id & UInt(15u)) )
		{
		case Int(0): return Int(1);
		;
		case Int(1): return Int(1);
		;
		case Int(2): return Int(1);
		;
		case Int(3): return Int(2);
		;
		case Int(4): return Int(2);
		;
		case Int(5): return Int(2);
		;
		case Int(6): return Int(2);
		;
		case Int(7): return Int(2);
		;
		case Int(8): return Int(2);
		;
		case Int(9): return Int(2);
		;
		case Int(10): return Int(2);
		;
		case Int(11): return Int(2);
		;
		case Int(12): return Int(2);
		;
		case Int(13): return Int(2);
		;
		case Int(14): return Int(2);
		;
		case Int(15): return Int(3);
		;
		}
		;
		return Int(0);
	}
	
	
	static UInt GetFunctionTicks (const UInt id)
	{
		switch( (id & UInt(15u)) )
		{
		case Int(0): return UInt(2u);
		;
		case Int(1): return UInt(2u);
		;
		case Int(2): return UInt(1u);
		;
		case Int(3): return UInt(2u);
		;
		case Int(4): return UInt(2u);
		;
		case Int(5): return UInt(2u);
		;
		case Int(6): return UInt(2u);
		;
		case Int(7): return UInt(2u);
		;
		case Int(8): return UInt(2u);
		;
		case Int(9): return UInt(8u);
		;
		case Int(10): return UInt(4u);
		;
		case Int(11): return UInt(10u);
		;
		case Int(12): return UInt(12u);
		;
		case Int(13): return UInt(3u);
		;
		case Int(14): return UInt(3u);
		;
		case Int(15): return UInt(5u);
		;
		}
		;
		return UInt(0u);
	}
	
	
	static void BigInt_Create (OUT BigInt &bi)
	{
		for (UInt i = UInt(0u); (i < UInt(1u)); ++(i))
		{
			(bi.value[i]) = UInt(0u);
		}
		;
		bi.lastBit = UInt(0u);
	}
	
	
	static void BigInt_Add (INOUT BigInt &bi, IN UInt right)
	{
		for (UInt i = UInt(0u); (i < UInt(1u)); ++(i))
		{
			const UInt prev = (bi.value[i]);
			;
			((bi.value[i]) += right);
			if (((bi.value[i]) >= prev))
			{
				bi.lastBit = max(bi.lastBit, _BigInt_CalcBits(bi, i));
				break;
			;
			}
			;
			right = UInt(1u);
		}
		;
	}
	
	
	static void BigInt_Add (INOUT BigInt &bi, const BigInt right)
	{
		for (UInt j = UInt(0u); (j < UInt(1u)); ++(j))
		{
			UInt val = (right.value[j]);
			;
			if ((val == UInt(0u)))
			{
				continue;
			}
			;
			for (UInt i = j; (i < UInt(1u)); ++(i))
			{
				const UInt prev = (bi.value[i]);
				;
				((bi.value[i]) += val);
				if (((bi.value[i]) >= prev))
				{
					bi.lastBit = max(bi.lastBit, _BigInt_CalcBits(bi, i));
					break;
				;
				}
				;
				val = UInt(1u);
			}
			;
		}
		;
	}
	
	
	static Bool BigInt_IsZero (const BigInt bi, const UInt pos)
	{
		return (pos >= bi.lastBit);
	}
	
	
	static UInt BigInt_Read (const BigInt bi, IN UInt pos, const UInt count)
	{
		const UInt i = clamp((pos / UInt(32u)), UInt(0u), UInt(0u));
		;
		(pos -= (UInt(32u) * i));
		UInt result = (((bi.value[i]) >> pos) & ToMask(count));
		;
		UInt max_count = (UInt(32u) - pos);
		;
		if (((count > max_count) && ((i + UInt(1u)) < UInt(1u))))
		{
			(result |= (((bi.value[(i + UInt(1u))]) & ToMask((count - max_count))) << max_count));
		;
		}
		;
		return result;
	}
	
	
	static UInt _BigInt_CalcBits (const BigInt bi, const UInt i)
	{
		return ((BitScanReverse((bi.value[i])) + UInt(1u)) + (i * UInt(32u)));
	}
	
	
	static void Node_Create (OUT CmdNode &n)
	{
		n.id = UInt(4294967295u);
		n.argsCount = Int(0);
		n.result = MaxValue(Int(0));
		for (UInt i = UInt(0u); (i < UInt(3u)); ++(i))
		{
			(n.args[i]) = Int(0);
		}
		;
	}
	
	
	static Bool BuildCommandsList (const BigInt hash, const Int maxInputs, OUT Float &outTicks, INOUT NodeArray &commands)
	{
		Int pos = Int(0);
		;
		Int arg_idx = Int(0);
		;
		NodeArray tmp;
		tmp.count = Int(0);
		outTicks = Float(0.0f);
		do {
			const Int i = tmp.count;
			;
			Node_Create((tmp.nodes[i]));
			(tmp.nodes[i]).id = BigInt_Read(hash, UInt(pos), UInt(4u));
			const Int cnt = GetFunctionArgsCount((tmp.nodes[i]).id);
			;
			(outTicks += Float(GetFunctionTicks((tmp.nodes[i]).id)));
			(pos += Int(4));
			arg_idx = max(arg_idx, i);
			for (Int j = (cnt - Int(1)); (j >= Int(0)); --(j))
			{
				((tmp.nodes[i]).args[j]) = ++(arg_idx);
			}
			;
			(tmp.nodes[i]).argsCount = cnt;
			++(tmp.count);
		} while ( (!(BigInt_IsZero(hash, UInt(pos))) && (tmp.count < Int(4))));
		;
		if ((tmp.count <= Int(0)))
		{
			return Bool(false);
		}
		;
		commands.count = maxInputs;
		const Int cnt = (tmp.count - Int(1));
		;
		for (Int i = cnt; (i >= Int(0)); --(i))
		{
			for (Int j = ((tmp.nodes[i]).argsCount - Int(1)); (j >= Int(0)); --(j))
			{
				const Int idx = ((tmp.nodes[i]).args[j]);
				;
				if ((idx <= cnt))
				{
					((tmp.nodes[i]).args[j]) = ((cnt - idx) + maxInputs);
				}
				else
				{
					((tmp.nodes[i]).args[j]) = ((arg_idx - idx) % maxInputs);
				}
				;
			}
			;
			(commands.nodes[commands.count]) = (tmp.nodes[i]);
			++(commands.count);
		}
		;
		return Bool(true);
	}
	
	
	static void RunCommands (INOUT NodeArray &commands, const Int maxInputs, const SArr<Int,1> inArgs, const SArr<Int,3> constants)
	{
		SArr<Int,3> reg;
		(reg[Int(0)]) = Int(0);
		for (UInt c = UInt(0u); (c < UInt(maxInputs)); ++(c))
		{
			(commands.nodes[c]).result = ( ((c < UInt(1u))) ? ((inArgs[c])) : ((constants[(c - UInt(1u))])) );
		}
		;
		const Int cmd_cnt = commands.count;
		;
		for (Int c = maxInputs; (c < cmd_cnt); ++(c))
		{
			const Int args_cnt = (commands.nodes[c]).argsCount;
			;
			for (Int j = Int(0); (j < args_cnt); ++(j))
			{
				Int idx = ((commands.nodes[c]).args[j]);
				;
				(reg[j]) = (commands.nodes[idx]).result;
			}
			;
			(commands.nodes[c]).result = CallFunction((commands.nodes[c]).id, reg, args_cnt);
		}
		;
	}
	
}		// anonymous namespace
	
	extern void sw_bruteforce (const Impl::SWShaderHelper &_helper_)
	{
		// prepare externals
		Impl::StorageBuffer< Bruteforce_InputsSSBO, Impl::EStorageAccess::ReadOnly > ssb_input;	_helper_.GetStorageBuffer( 0, ssb_input );
		Impl::StorageBuffer< Bruteforce_OutputsSSBO, Impl::EStorageAccess::Coherent > ssb_output;	_helper_.GetStorageBuffer( 1, ssb_output );
		auto& gl_GlobalInvocationID = _helper_.GetComputeShaderState().inGlobalInvocationID;
	
		// shader
		{
			BigInt initial_hash = ssb_input->initialHash;
			;
			BigInt hash;
			BigInt_Create(hash);
			BigInt_Add(hash, initial_hash);
			BigInt_Add(hash, gl_GlobalInvocationID.x);
			Float ticks = Float(0.0f);
			;
			Int max_inputs = min((Int(1) + ssb_input->numConstants), Int(4));
			;
			NodeArray commands;
			if (!(BuildCommandsList(hash, max_inputs, ticks, commands)))
			{
				return;
			}
			;
			Float accuracy = Float(0.0f);
			;
			for (UInt i = UInt(0u); (i < UInt(20u)); ++(i))
			{
				RunCommands(commands, max_inputs, (ssb_input->tests[i]).inArgs, ssb_input->constants);
				const UInt idx = UInt((commands.count - Int(1)));
				;
				const Int res = (commands.nodes[idx]).result;
				;
				(accuracy += ValueDifference((ssb_input->tests[i]).result, res));
				if ((!((!(isinf(Float(res))) && !(isnan(Float(res))))) || (accuracy > (ssb_input->maxAccuracy * Float(max((i + UInt(1u)), UInt(2u)))))))
				{
					return;
				}
				;
			}
			;
			(accuracy /= Float(20.0f));
			if ((accuracy > ssb_input->maxAccuracy))
			{
				return;
			}
			;
			if (IsZero(accuracy))
			{
				atomicAdd(ssb_output->stat.bestResults, UInt(1u));
			;
			}
			;
			const UInt idx = atomicAdd(ssb_output->stat.results, UInt(1u));
			;
			if ((idx >= UInt(10000u)))
			{
				atomicExchange(ssb_output->stat.results, UInt(10000u));
				return;
			;
			}
			;
			(ssb_output->funcs[idx]).funHash = hash;
			(ssb_output->funcs[idx]).constHash = ssb_input->constHash;
			(ssb_output->funcs[idx]).ticks = ticks;
			(ssb_output->funcs[idx]).accuracy = accuracy;
		}
	}
	
# ifdef _MSC_VER
#	pragma warning (pop)
# endif // _MSC_VER

}		// SWShaderLang
#endif	// GRAPHICS_API_SOFT
