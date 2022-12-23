package merrygoround;

simple MerryGoRound
{
	parameters:
		int T;	//number of seconds of one ride duration
		@signal[rideStart](type=double);
		@signal[rideStop](type=int);
		@statistic[MGR_Utilization](source=sumPerDuration(rideStop); record=last, vector);
		@statistic[MGR_Start](source=rideStart; record=vector);
	gates:
		input in;
		output out;
}
