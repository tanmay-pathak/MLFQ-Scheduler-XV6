#include "kernel/types.h"
#include "user/user.h"

// Userspace program to test newly added instrumentation and the new syscall waitstat()
void main(int argc, char *argv[])
{
    // Argument error checks
    if (argc != 5)
    {
        printf("Invalid call.\n");
        printf("Arguments given:%d\n", argc - 1);
        exit(-1);
    }

    // Convert arguments to ints
    int k = atoi(argv[1]);
    int l = atoi(argv[2]);
    int m = atoi(argv[3]);
    int n = atoi(argv[4]);
    
    // Fork 45 times
    int pids[45];
    for (int i = 0; i < 45; i++)
    {
        pids[i] = fork();
        if (pids[i] < 0)
        {
            // Fork for p1/p2/p3 failed
            printf("Fork failed.\n");
            exit(-1);
        }
        else if (pids[i] == 0)
        {
            int j;
            // Child process
            if (i < 15)
            {
                j = n;
            }
            else if (i < 30)
            {
                j = m;
            }
            else
            {
                j = l;
            }
            // Perform an arbitrary calculation to simulate some work
            int result = 0;
            for (int n1 = 1; n1 < (k + 1); n1++)
            {
                for (int n2 = 1; n2 < (j + 1); n2++)
                {
                    result += (n1 - n2);
                }
            }
            exit(0);
        }
        else
        {
            // parent process
        }
    }

    // Wait for all children to finish
    printf("About to wait\n");
    printf("-------------\n");
    int status = 0;
    uint turnaroundTime = 0;
    uint runtime = 0;
    uint turnAroundTimeSums[3];
    uint runTimeSums[3];
    turnAroundTimeSums[0] = 0;
    turnAroundTimeSums[1] = 0;
    turnAroundTimeSums[2] = 0;
    runTimeSums[0] = 0;
    runTimeSums[1] = 0;
    runTimeSums[2] = 0;

    int procID = waitstat(&status, &turnaroundTime, &runtime);
    // Keep looping until waitstat determines there are no children left to wait for.
    while (procID > 0)
    {
        for(int c = 0; c < 45; c++ ){
            // Find the proc in the pids array, and add to its groups sums.
            if(pids[c] == procID){
                if (c < 15){
                    turnAroundTimeSums[0] += turnaroundTime;
                    runTimeSums[0] += runtime;
                }
                else if (c < 30){
                    turnAroundTimeSums[1] += turnaroundTime;
                    runTimeSums[1] += runtime;
                }
                else{
                    turnAroundTimeSums[2] += turnaroundTime;
                    runTimeSums[2] += runtime;
                }
            }
        }
        // Call waitstat to find another proc that is done.
        procID = waitstat(&status, &turnaroundTime, &runtime);
    }

    // Print results
    printf("\n P1 GROUP \n");
    printf("Turn Around Time: %d,  Run Time: %d\n", turnAroundTimeSums[0], runTimeSums[0]);

    printf("\n P2 GROUP \n");
    printf("Turn Around Time: %d,  Run Time: %d\n", turnAroundTimeSums[1], runTimeSums[1]);

    printf("\n P3 GROUP \n");
    printf("Turn Around Time: %d,  Run Time: %d\n", turnAroundTimeSums[2], runTimeSums[2]);

    printf("Test complete.\n");
    exit(0);
}