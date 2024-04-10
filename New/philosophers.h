/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 13:34:16 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/03/19 16:35:55 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILOSOPHERS_H_
# define _PHILOSOPHERS_H_

/* INCLUDES LIBRARIES */
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>/* For pthread Functions */
# include <sys/time.h>/* gettimeofday */
# include <limits.h>

/* DEFINED USER COLOR*/
# define DEF_COLOR "\033[0;39m"
# define GRAY "\033[0;90m"
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define PINK "\e[0;38;5;199m"
# define CYAN "\033[0;96m"

/* DEFINED USER MESSAGES */
# define TRUE 		1
# define ERROR		0
# define FALSE		0
# define DIED 		"died"
# define EATING 	"is eating"
# define THINKING 	"is thinking"
# define SLEEPING 	"is sleeping"
# define TAKE_FORKS	"has taken a fork"

struct  s_info;

typedef struct s_philosopher
{
    int             id;
	long            time_for_eat;
    long            time_current;
    int             has_eat_count;
    struct s_info   *info;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    pthread_mutex_t eating;
	
}	t_philo;

typedef struct s_info {
    struct  s_philosopher   *philo; 
    pthread_t               *threads;
    pthread_mutex_t         *forks;
    pthread_mutex_t         mutex_lock;
    pthread_mutex_t         print_lock;
    pthread_mutex_t         death_lock;
    int                     philo_num;
    int                     time_to_eat;
    int                     time_to_sleep;
    int                     time_to_die;
    int                     eating_count;
    int                     philo_dead;
    int                     philo_full;
    int                     everyone_full;
    int                     fail_thread;
    long                    start_time;
}   t_info;

/*------------FUNCTIONS---------- */

//ARGUMENT CHECK FUNCTIONS
int	initialize_struct(char **argv, t_info *info);
int	check_arguments(int argc, char **argv);

// PHILOSOPHER FUNCTIONS
int		philo_steal_fork(t_philo *philo, int id);
int		philo_eating(t_philo *philo, int id);
int		philo_sleeping(t_philo *philo, int id);
int		philo_died(t_philo *philo, int id);
int		philo_thinking(t_philo *philo, int id);

// THREAD FUNCTIONS
int		initialize_threads(t_info *info);
int		initialize_mutexes(t_info *info);
void	initialize_fork(t_info *info);
int		operations_even(t_philo *philo);
int		operations_odd(t_philo *philo);
int		one_philo_loop(t_philo *philo);
void	monitoring(t_philo *philo);
void	*thread_loop(void *data);

// ERROR-FREE FUNCTIONS
int		print_error(char *str, t_info *info);
void	free_struct(t_info *info);
void	delete_mutexes(t_info *info);

// UTILS FUNCTION
char	    *ft_strcpy(char *dest, const char *src);
void	    *ft_calloc(size_t count, size_t size);
int         ft_strlen(char *str);
void        end_threads(t_philo *philo, int index);
long        get_time(void);
int			ft_atoi(char *str);
int		    sleep_function(long time, t_philo *philo);
int         printing(t_philo *philo, int id, const char *str);

#endif