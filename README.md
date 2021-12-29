
# MLFQ Scheduler

A Multi Level Feedback Queue scheduler for the RISC-V port of XV6.

## Authors

- [Hamza Aziz](https://github.com/Hamza975A)
- [Tanmay Pathak](https://github.com/tanmay-pathak)

## Acknowledgements

- [MIT-PDOS](https://github.com/mit-pdos/xv6-riscv)
- [XV6-Explained](https://github.com/YehudaShapira/xv6-explained)
- [OSTEP](https://pages.cs.wisc.edu/~remzi/OSTEP/)


## Documentation

- We implemented a variant of MLFQ scheduling where each process would have an associated current priority which can be "high", "medium", or "low".
- This is done through keeping track of the current priority of a process as an integer in the proc structure.
- Every time that the scheduler is looking for a process to run it will first search for a high priority process to run. If it does not find a process then the scheduler will look for a high or medium priority process. On the third try the scheduler would search for any runnable process.
- New syscall named `waitstat` was added which works like `wait` but also returns the turnaround time and the running time of the process waited for.
- We also included a test program (`test.c`) which performs some arbitrary calculations to simulate some work and then calls waitstat. The results are printed when the test completes.

## Features

- New processes are initially given "high" priority.
- A high priority process is moved to medium priority after it has been scheduled once.
- A medium priority process is moved to lower priority after the process has been scheduled `MTIMES` (defined in `param.h`).
- All processes are moved to high priority after the scheduler has scheduled processes `MOVEUP` times (defined in `param.h`)

## Lessons Learned

Our testing to compare the default xv6 scheduler with our newly implemented MLFQ scheduler resulted in the following:

- Default scheduler is more efficient for smaller inputs for our test program because the overhead of selecting the correct process to run is high.
- If `MTIMES` and `MOVEUP` values are too close to each other then the MLFQ scheduler just ends up working the same as the default scheduler.
  
Improvements that can be made are:

- Switch to a time-slice based lowering of priority.
- Allow the user to suggest a priority for the process.
- Allow processes to move up to a higher priority if the process does not fully utilize the allotted time-slice when scheduled.

## Instructions to Run

1. Clone the project.
2. Add path of `riscv64` to the `Makefile`.
3. Run `make qemu` to boot up xv6.
4. Run `test` user program with four integer arguments to perform some arbitrary calculations.
5. After the calculations are finished the user program will print the results.

## [License](/LICENSE)
