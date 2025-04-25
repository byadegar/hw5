#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool backtrackingFunction(int day, int workerIndex, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<int>& countShifts); 
//current day scheduling, current index worker on the day, availability matrix, number of workers needed for that day
//max shifts allowed for each worker, output schedulel being built, number of shifts each worker has worked 

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    //do i have to do another check for empty??
    
    //get info for number of days and workers, grab the data from the 2d matrix
    //rows represent days and columns represent workers and if true theyre free that day 
    size_t numberDays = avail.size();  //how many days are there 
    size_t numberWorkers = avail[0].size(); //how many workers are in there (cols in row)

    //initialize schedule matrix, intiially with invalid_id so all slots are unassigned for now
    sched.assign(numberDays, vector<Worker_T>(dailyNeed, INVALID_ID)); 

    //initilize countshift vector to track shifts worked per each worker
    vector<int> countShifts(numberWorkers, 0); 

    //use all info to recursively schedule (using backtracking)
    return backtrackingFunction(0, 0, avail, dailyNeed, maxShifts, sched, countShifts); 

}

bool backtrackingFunction(int day, int workerIndex, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<int>& countShifts){
  size_t numberDays = avail.size();  //how many days are there 
  size_t numberWorkers = avail[0].size(); //how many workers are in there (cols in row)

  //base case 
  //all days have been scjeduled, your done 
  if (day == int(numberDays)){ //means you have just finished scheduling the last day
    return true; 
  }

  if (workerIndex == int(dailyNeed)){ //all slots are filled for this day, so we are looking at next day
    return backtrackingFunction(day + 1, 0, avail, dailyNeed, maxShifts, sched, countShifts); 
  }

  //try assinging each worker to the current day and worker slot 
  //see if workers are a valid choice 
  for (Worker_T i = 0; i < numberWorkers; i++){
    //every worker loop so we can try to place 
    //check if worker is available on the day 
    if (avail[day][i] == true){
      if (countShifts[i] < int(maxShifts)){ //check if worker has exceeded the shift limkit
        if (find(sched[day].begin(), sched[day].end(), i) == sched[day].end()) { //is worker already scheduled for this day
          //yay able to go and assign the worker 
          sched[day][workerIndex] = i; 
          countShifts[i]++; 

          //time to fill the next slot
          //recursion 
          if(backtrackingFunction(day, workerIndex +1, avail, dailyNeed, maxShifts, sched, countShifts) == true){
            return true; //worked
          }

          //if u didn't return true, you have to backtrack to undo the assingment
          sched[day][workerIndex] = INVALID_ID; 
          countShifts[i]--; 
        }

      }
    }
  }
  //if havent returned true by now 
  return false; 
} 


