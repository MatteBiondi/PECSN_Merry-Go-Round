package merrygoround;

simple Owner
{
    parameters:
		double v_fraction;		//minimum of children accepted to start a ride
		double c;				//number of coins earned for each child who enjoys a ride
		int N;					//number of seats of the MGR
		@signal[earnedCoins](type=double);
		@statistic[coinsPerUnitOfTime](source=sumPerDuration(earnedCoins); record=vector, last;);
		@signal[peopleOnBoard](type=int);
		@statistic[avgPeoplePerRide](source=peopleOnBoard; record=count, mean;);
	
	gates:
		input inFromQueue;
		input inFromMGR;
		output outToQueue;
		output outToMGR;
}
