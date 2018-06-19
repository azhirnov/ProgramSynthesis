
int rnd ()
{
	return Rand_Int();
}

const int a0 = rnd();
const int a1 = rnd();
const int a2 = rnd();
const int a3 = rnd();

int expectedFunc (int a)
{
	switch ( a )
	{
		case 0 :	return a0;
		case 1 :	return a1;
		case 2 :	return a2;
		case 3 :	return a3;
	}
	return 0;
}


void main ()
{
	TestCasesI1 tc;
	
	for (int i = 0; i < 20; ++i)
	{
		int a = Abs(rnd());

		tc.Add( a, expectedFunc( a ) );
	}

	BruteforceCodeGen	bfcg;
	bfcg.SetTests( tc );
	bfcg.SetMaxAccuracy( 0.001f );
	bfcg.SetMaxCommands( 9 );
	bfcg.SetMaxConstants( 2 );
	bfcg.AddCommandSet( ECommandSet_IntBitwise );
	bfcg.AddConstantSet( EConstantSet_Values0to255 );
	bfcg.SetFitnessFunction( EFitnessFunction_FloatLinear );
	bfcg.Run( "test8_res.txt" );
}
