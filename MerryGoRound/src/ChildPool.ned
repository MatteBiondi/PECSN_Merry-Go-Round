//Project team:		Biondi, Cristofani, Guidotti
//Academic Year: 	2022/2023
//File Description: This file represents the structure of the 
//					simple module in charge of generating the 
//					arrival of new children in the merry go 
//					round queue 		
 

package merrygoround;


simple ChildPool
{
    parameters:
        int Q;
        double Delta;
        double Lambda;
        double P;
        @signal[arrivals](type=double);
		@statistic[interArrivalStat](source=arrivals; record=vector,stats;);
        
    gates:
        output toChildQueue;
}
