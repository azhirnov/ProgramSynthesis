float expectedFunc (float a, float b)
{
	return 77.0f;
}

float rnd ()
{
	return Rand_FloatRange( -5.0f, 5.0f );
}

void main ()
{
	TestCasesF2 tc;
	
	tc.Add( 0.0f, 0.0f, expectedFunc( 0.0f, 0.0f ) );

	for (int i = 0; i < 10; ++i)
	{
		float a = rnd();
		float b = rnd();

		tc.Add( a, b, expectedFunc( a, b ) );
	}

	BruteforceCodeGen	bfcg;
	bfcg.SetTests( tc );
	bfcg.SetMaxAccuracy( 0.001f );
	bfcg.SetMaxCommands( 6 );
	bfcg.SetMaxConstants( 1 );
	bfcg.AddCommandSet( ECommandSet_FloatArithmetic );
	bfcg.AddConstantSet( EConstantSet_Values0to255 );
	bfcg.SetFitnessFunction( EFitnessFunction_FloatLinear );
	bfcg.Run( "test6_res.txt" );
}
