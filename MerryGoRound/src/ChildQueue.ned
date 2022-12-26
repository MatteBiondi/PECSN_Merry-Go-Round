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
        @signal[queueTotal](type=int);
        @signal[queueQuit](type=int);
        @signal[queueServed](type=int);
        @signal[queueLength](type=unsigned int);
        @statistic[queueTotalStat](title="ChildrenInQueue";source="queueTotal";record=vector, count); 
        @statistic[queueQuitStat](title="ChildrenQuit";source="queueQuit";record=vector, count);     
        @statistic[queueServedStat](title="ChildrenServed";source="queueServed";record=vector,count); 
        @statistic[queueLengthStat](title="QueueLenght";source="queueLength";record=vector,timeavg);     
    gates:
        input childPoolIn;
        input ownerIn;
        output ownerOut;
}
