int expectedFunc (int a)
{
	return Abs(a);
	//return a & ((1 << 31)-1);
}

int rnd ()
{
	return Rand_Int();
}

void main ()
{
	TestCasesI1 tc;
	
	for (int i = 0; i < 20; ++i)
	{
		int a = Abs(rnd());

		tc.Add( a, expectedFunc( a ) );
		tc.Add( -a, expectedFunc( -a ) );
	}

	BruteforceCodeGen	bfcg;
	bfcg.SetTests( tc );
	bfcg.SetMaxAccuracy( 0.001f );
	bfcg.SetMaxCommands( 9 );
	bfcg.SetMaxConstants( 2 );
	bfcg.AddCommandSet( ECommandSet_IntBitwise );
	bfcg.AddConstantSet( EConstantSet_PrimeNumbers );
	bfcg.SetFitnessFunction( EFitnessFunction_FloatLinear );
	bfcg.Run( "test7_res.txt" );
}
