#!/bin/bash

CONFIGURATIONS=(
    "Low_Load_Throughput_Optimization" 
    "Medium_Load_Throughput_Optimization" 
    "High_Load_Throughput_Optimization"
    "Low_Load_Utilization_Optimization"
    "Medium_Load_Utilization_Optimization"
    "High_Load_Utilization_Optimization"
)

parallel='true'

print_usage() {
  echo "Usage: bash $0 [-s]"
}

while getopts 's' flag; do
  case "${flag}" in
    s) parallel='false' ;;
    *) print_usage
       exit 1 ;;
  esac
done

for config in ${CONFIGURATIONS[@]}; do
  printf "\n*** Running $config\n"
  if [ $parallel = 'true' ] ; then
     opp_runall ../src/MerryGoRound_dbg -u Cmdenv -c $config -n .:../src omnetpp.ini > simulation.out
  else
    ../src/MerryGoRound_dbg -u Cmdenv -c $config -n .:../src omnetpp.ini > simulation.out
  fi 
done

echo "Simulation complete"
