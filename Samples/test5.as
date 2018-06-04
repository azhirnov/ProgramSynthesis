uint expectedFunc (uint a, uint b, uint c, uint d)
{
	return (a >> (b&31)) ^ ((c != 0 ? c % d : 0) | (d & c));
}

uint rnd ()
{
	return Rand_UInt();
}

void main ()
{
	TestCasesU4 tc;

	for (int i = 0; i < 20; ++i)
	{
		uint a = rnd();
		uint b = rnd();
		uint c = rnd();
		uint d = rnd();

		tc.Add( a, b, c, d, expectedFunc( a, b, c, d ) );
	}

	BruteforceCodeGen	bfcg;
	bfcg.SetTests( tc );
	bfcg.SetMaxAccuracy( 0.5f );
	bfcg.SetMaxCommands( 8 );
	bfcg.AddCommandSet( ECommandSet_IntArithmetic );
	bfcg.SetFitnessFunction( EFitnessFunction_FloatLinear );
	bfcg.Run( "test5_res.txt" );
}
