#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#endif
#include <vector>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here
bool schedHelper( size_t dayRow, int numWorkers, DailySchedule& sched, 
const AvailabilityMatrix& avail,  std::vector<size_t>& shifts,
const size_t maxShifts, const size_t requiredAmt){
    // first shift of the first day 
    // recurse thru each shift in that day and go to next day
    // base case past last day and return true
    
    if (dayRow == avail.size()){
        return true;
    }
		// if reached needed amount, increment day and set workers = 0
    else if (numWorkers == requiredAmt){
        return schedHelper (dayRow + 1, 0, sched, avail, shifts, maxShifts, requiredAmt);
    }
    else{
        int newWorkers = numWorkers;
        for(size_t i = 0; i < avail[dayRow].size(); i++){   
           
            // if available and not working max shifts, put in schedule
            // if the worker is availble 
            if (avail[dayRow][i] && shifts[i] < maxShifts && std::find(sched[dayRow].begin(),sched[dayRow].end(), i) == sched[dayRow].end()){
                //increment the number of shifts
                shifts[i] += 1;
                sched[dayRow].push_back(i);
                newWorkers += 1;
								// if the amount is met, increment day and change workers to 0
                if (sched[dayRow].size() == requiredAmt){
                    dayRow += 1;
                    newWorkers = 0;
                }
								// recurse
                bool result = schedHelper(dayRow, newWorkers, sched, avail, shifts, maxShifts, requiredAmt);
								// return true if true
                if (result){
                    return true;
                }
								// if not, backtrack and reset
                else{
                    shifts[i] -= 1;
										// if u incrememnted and its false, decrement back to og day and popback
                    if (sched[dayRow].size() == 0){
                        dayRow -= 1;
                    }
                    sched[dayRow].pop_back();
                    newWorkers = numWorkers;
                }

            }
            // return false
        }
        return false;
    }
}
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0){
        return false;
    }
    sched.clear();
    
    // shifts vector
    vector<size_t> shifts;
		// initalize sched
    for (int i = 0; i < avail.size(); i++){
        sched.push_back(vector<Worker_T>());
    }
    
    // initialize shifts to all 0
    for (size_t i = 0; i < avail[0].size(); i++){
        shifts.push_back(0);
    }
		// return 
     return schedHelper(0, 0, sched, avail, shifts, maxShifts, dailyNeed);
        

}

