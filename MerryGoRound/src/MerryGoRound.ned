package merrygoround;

simple MerryGoRound
{
	parameters:
		int T;	//number of seconds of one ride duration
		@signal[rideStop](type=int);
		@statistic[MGR_Utilization](source=sumPerDuration(rideStop); record=last, vector);
	gates:
		input in;
		output out;
}
