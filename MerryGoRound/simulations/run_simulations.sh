#!/bin/bash

CONFIGURATIONS=(
    "Validation_deterministic_test" 
    "Validation_consistency_test" 
    "Validation_degeneracy_test_Q_and_Delta_0" 
    "Validation_degeneracy_test_N_0" 
    "Validation_degeneracy_test_Lambda_0" 
    "Validation_degeneracy_test_T_0"
    "Validation_continuity_test_N"
    "Validation_continuity_test_Delta"
    "Validation_continuity_test_Lambda"
    "Validation_continuity_test_T"
    "Validation_continuity_test_P"
)

parallel='false'

print_usage() {
  echo "Usage: bash $0 [-p]"
}

while getopts 'p' flag; do
  case "${flag}" in
    p) parallel='true' ;;
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
