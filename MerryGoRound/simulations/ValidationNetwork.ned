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

package merrygoround.simulations;

import merrygoround.DummyChildPool;
import merrygoround.ChildQueue;
import merrygoround.MerryGoRound;
import merrygoround.Owner;

network ValidationNetwork
{
    @display("bgb=495,186");
    submodules:
        dummyChildPool: DummyChildPool {
            @display("p=59,85");
        }
        owner: Owner {
            @display("p=309,85");
        }
        merryGoRound: MerryGoRound {
            @display("p=437,85");
        }
        childQueue: ChildQueue {
            @display("p=176,85");
        }
    connections:
        dummyChildPool.toChildQueue --> childQueue.childPoolIn;
        owner.outToQueue --> childQueue.ownerIn;
        childQueue.ownerOut --> owner.inFromQueue;
        owner.outToMGR --> merryGoRound.in;
        merryGoRound.out --> owner.inFromMGR;
}
