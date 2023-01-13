//
//Project team:		Biondi, Cristofani, Guidotti
//Academic Year: 	2022/2023
//File Description: This file represents the structure of the 
//					simple module in charge of represting the 
//					MGR rides by taking into account the ride 
//					duration
//

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
