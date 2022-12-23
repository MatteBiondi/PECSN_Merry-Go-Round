package merrygoround;

simple MerryGoRound
{
	parameters:
		int T;	//number of seconds of one ride duration
		@signal[rideStart](type=int);
		@statistic[rideCounter](source=sumPerDuration(rideStart); record=last, vector);
	gates:
		input in;
		output out;
}
