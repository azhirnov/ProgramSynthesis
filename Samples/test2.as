float expectedFunc (float a, float b, float c, float d)
{
	return (c * -b) + (d * a);
}

float rnd ()
{
	return Rand_FloatRange( -5.0f, 5.0f );
}

void main ()
{
	TestCasesF4 tc;

	for (int i = 0; i < 10; ++i)
	{
		float a = rnd();
		float b = rnd();
		float c = rnd();
		float d = rnd();

		tc.Add( a, b, c, d, expectedFunc( a, b, c, d ) );
	}

	BruteforceCodeGen	bfcg;
	bfcg.SetTests( tc );
	bfcg.SetMaxAccuracy( 0.001f );
	bfcg.SetMaxCommands( 6 );
	bfcg.AddCommandSet( ECommandSet_FloatArithmetic );
	bfcg.SetFitnessFunction( EFitnessFunction_FloatLinear );
	bfcg.Run( "test2_res.txt" );
}
