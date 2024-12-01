# Common Core 42 - Philosophers
Philosophers is a 42 school project designed around Edsger Dijkstra's famous dining philosophers problem. For this project, we must learn about concurrent programming. For the project's mandatory part, we must find a solution to the problem using only threads and mutexes.
![Dining_philosophers4-left-release](https://github.com/user-attachments/assets/03076686-044d-4aaa-87e3-c8cbaaf5f783)
### General Description

The subject describes the problem as follows:

* One or more philosophers sit at a round table.
+ There is a large bowl of spaghetti in the middle of the table.
- The spaghetti can only be eaten with two forks.
+ There are only as many forks as there are philosophers.
* Each philosopher successively eats, sleeps and thinks.
- If a philosopher hasn't eaten in a certain timeframe, he will die of starvation.
+ Philosophers cannot communicate with each other.
* In both the mandatory and bonus parts, we must create an algorithm that keeps the philosophers alive as far as possible. The programs must take several parameters:

1. number_of_philosophers: the number of philosophers around the table,
2. time_to_die: a number representing the time in milliseconds a philosopher has to live after a meal. If a philosopher hasn’t started eating time_to_die milliseconds after the beginning of his last meal or the beginning of the simulation, he will die.
3. time_to_eat: a number representing the time in milliseconds a philosopher takes to finish his meal. During that time, the philosopher keeps his two forks in hand.
4. time_to_sleep: the time in milliseconds that a philosopher spends sleeping.
5. number_of_times_each_philosopher_must_eat: an optional argument that allows the program to stop if all the philosophers have eaten at least that many times. If this argument is not specified, the simulation carries on unless a philosopher dies.
The programs outputs a message each time a philosopher takes an action, which is formatted this way:

* [timestamp_in_ms] [X] has taken a fork
+ [timestamp_in_ms] [X] is eating
+ [timestamp_in_ms] [X] is sleeping
- [timestamp_in_ms] [X] is thinking
- [timestamp_in_ms] [X] died

<img width="1280" alt="Screenshot 2024-12-01 at 18 54 02" src="https://github.com/user-attachments/assets/ee3ee35f-8e58-4433-bd15-86b36efdbab5">


<img width="912" alt="Screenshot 2024-12-01 at 18 55 36" src="https://github.com/user-attachments/assets/350511a6-6c73-43f8-a679-46f29cd86a95">


