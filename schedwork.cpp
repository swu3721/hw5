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
bool scheduleHelper(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, size_t day, size_t workersNeeded, size_t numWorkers, std::vector<int>& workerShiftsDone, std::vector<std::vector<bool>>& workerWorkedOnDay);

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

    //Number of workers
    size_t numWorkers = avail[0].size();
    //Vector with number of shifts done by each worker (index)
    std::vector<int> workerShiftsDone(numWorkers, 0);

    //2D vector to verify if worker has already worked on the day (avail.size())
    std::vector<std::vector<bool>> workerWorkedOnDay(avail.size(), std::vector<bool>(numWorkers, false));

    for (size_t i = 0; i < avail.size(); i++) { //For each day
        std::vector<unsigned int> temp; //Make a temp variable
        for (size_t j = 0; j < dailyNeed; j++) { //For dailyNeeded workers
            temp.push_back(0); //Push back 0
        }
        sched.push_back(temp); //Push back temp
    }
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0, numWorkers, workerShiftsDone, workerWorkedOnDay);




}

bool scheduleHelper(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, size_t day, size_t workersNeeded, size_t numWorkers, std::vector<int>& workerShiftsDone, std::vector<std::vector<bool>>& workerWorkedOnDay) {
    if (day == avail.size()) { //If all days observed
        return true;
    }

    for (size_t k = 0; k < numWorkers; ++k) { //For each worker
        if (avail[day][k] == true && workerWorkedOnDay[day][k] == false && workerShiftsDone[k] < maxShifts) { //If the worker can work that day and it is valid (not exceeding max shifts)
            
            sched[day][workersNeeded] = k; //Add k to the schedule (schedule k for shift on day)
            workerShiftsDone[k] += 1; //Add to k's shifts done
            workerWorkedOnDay[day][k] = true; //Set worker k on day to true

            // Recursive call for the next day
            int newDay = day;
            int newWorkersNeeded = workersNeeded;
            if (workersNeeded + 1 == dailyNeed) { //If we are at the max workers for the day, move to the next day
                newDay++;
                newWorkersNeeded = 0;
            } else { //Else move to next worker (d)
                newWorkersNeeded++;
            }

            if (scheduleHelper(avail, dailyNeed, maxShifts, sched, newDay, newWorkersNeeded, numWorkers, workerShiftsDone, workerWorkedOnDay)) {
                return true;
            }

            //Backtrack
            workerWorkedOnDay[day][k] = false; //Set worker k to false
            workerShiftsDone[k] -= 1; //Subtract from k's shift
        }
        
    }
    //if we get here, no workers possible for that day
    return false;
}
