//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package merrygoround;

simple ChildQueue
{
    parameters:
        @signal[queueTotalCount](type=unsigned int);
        @signal[queueQuitCount](type=unsigned int);
        @signal[queueServedCount](type=unsigned int);
        @signal[queueLength](type=unsigned int);
        @statistic[queueTotalCountStat](source="queueTotalCount";record=sum); 
        @statistic[queueQuitCountStat](source="queueQuitCount";record=sum);     
        @statistic[queueServedCountStat](source="queueServedCount";record=sum); 
        @statistic[queueLengthStat](source="queueLength";record=mean,timeavg);     
    gates:
        input childPoolIn;
        input ownerIn;
        output ownerOut;
        
}
