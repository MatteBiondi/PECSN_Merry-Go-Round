package merrygoround.simulations;

import merrygoround.ChildPool;
import merrygoround.ChildQueue;
import merrygoround.MerryGoRound;
import merrygoround.Owner;


network MRG_Network
{
    @display("bgb=495,186");
    submodules:
        childPool: ChildPool {
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
        childPool.toChildQueue --> childQueue.childPoolIn;
        owner.outToQueue --> childQueue.ownerIn;
        childQueue.ownerOut --> owner.inFromQueue;
        owner.outToMGR --> merryGoRound.in;
        merryGoRound.out --> owner.inFromMGR;
}
