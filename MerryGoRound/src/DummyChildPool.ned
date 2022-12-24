//
//Project team:		Biondi, Cristofani, Guidotti
//Academic Year: 	2022/2023
//File Description: This file represents the structure of the 
//					simple module in charge of generating 
//					deterministically the arrival of new 
//					children in the merry go round queue.
//					This module is used to validate the other
//					modules in the chain 		
// 

package merrygoround;


simple DummyChildPool
{
    parameters:
        int Q;
        double interarrivalTime;	        
        int bulk;        
    gates:
        output toChildQueue;
}
