#include "philo.h"

/*
• One or more philosophers are sitting at a round table doing one of three things:
eating, thinking, or sleeping.

 Each time a philosopher has finished eating, he will drop his forks and start sleeping.
 
 When a philosopher is done sleeping, he will start thinking

 The simulation stops when a philosopher dies.

 Each philosopher should be a thread.

 ARG:
 1. number_of_philosophers
 2. time_to_die
 3. time_to_eat 
 4.time_to_sleep
 5. [number_of_times_each_philosopher_must_eat]. if all
philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the
simulation will stop. If not specified, the simulation will stop only at the death
of a philosopher.

You can’t have more than 10 ms between the death of a philosopher and when it
will print its death.


typedef struct 

enum (X replaced with the philosopher number 
	timestamp_in_ms the current timestamp in milliseconds)
{
- timestamp_in_ms X has taken a fork
- timestamp_in_ms X is eating
- timestamp_in_ms X is sleeping
- timestamp_in_ms X is thinking
- timestamp_in_ms X died
} status

gettimeofday -   определяет время  int gettimeofday(struct timeval *tv, struct timezone *tz); 0 - ok, -1 - ne ok 
pthread_create - 
pthread_detach - 
pthread_join - 
pthread_mutex_init -
pthread_mutex_destroy -
pthread_mutex_lock -
pthread_mutex_unlock -

bonus:
waitpid - 
sem_open -
sem_close - 
sem_post - 
sem_wait - 
sem_unlink - 
fork - 


*/


int main (int argc, char **argv)
{
    return();
}