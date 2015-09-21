//--------------------------------------------------------------------
//
//  Laboratory 11, Programming Exercise 1                     ossim.cs
//
//  (Shell) Operating system task scheduling simulation
//
//--------------------------------------------------------------------

// Simulates an operating system's use of a priority queue to regulate
// access to a system resource (printer, disk, etc.).

#include <iostream>
#include <cstdlib>
#include "PriorityQueue.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declaration for the task data struct
//

struct TaskData
{
    int getPriority () const
        { return priority; }     // Returns the priority. Needed by the heap.

    int priority,                // Task's priority
        arrived;                 // Time when task was enqueued

};


//--------------------------------------------------------------------

int main ()
{
    PriorityQueue<TaskData, int, Less<int> > taskPQ;   // Priority queue of tasks
    TaskData task;               // Task
    int simLength,               // Length of simulation (minutes)
        minute,                  // Current minute
        numPtyLevels,            // Number of priority levels
        numArrivals,             // Number of new tasks arriving
        j;                       // Loop counter
	int k;

    // Seed the random number generator
    srand( (unsigned int) 7 );

    cout << endl << "Enter the number of priority levels : ";
    cin >> numPtyLevels;

    cout << "Enter the length of time to run the simulator : ";
    cin >> simLength;
	taskPQ.clear();

    for ( minute = 0 ; minute < simLength ; minute++ )
    {
        // Dequeue the first task in the queue (if any).
		if( !taskPQ.isEmpty() )
		{

			task = taskPQ.dequeue();
			cout << "At " << minute << " dequeued : ";
			cout << task.getPriority() << ' ' << task.arrived;
			cout << ( minute - task.arrived ) << endl;
		}
	
        // Determine the number of new tasks and add them to
        // the queue.
		int k = rand() % 4;
		if( k == 1 || k == 2 )
		{
			if( !taskPQ.isFull() )
			{
				for( j = 0; j < k; j++ )
				{
					task.priority = rand() % numPtyLevels;
					task.arrived = minute;
					taskPQ.enqueue( task );
				}
			}
		}

    }

    return 0;
}

