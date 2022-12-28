package merrygoround;

simple Owner
{
    parameters:
		double v_fraction;	//minimum of children accepted to start a ride
		int c;				//number of coins earned for each child who enjoys a ride
		int N;				//number of seats of the MGR
		@signal[earnedCoins](type=int);
		@statistic[throughput](source=sumPerDuration(earnedCoins); record=last;);
	
	gates:
		input inFromQueue;
		input inFromMGR;
		output outToQueue;
		output outToMGR;
}
