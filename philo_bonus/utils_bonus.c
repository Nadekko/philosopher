/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:31:21 by andjenna          #+#    #+#             */
/*   Updated: 2024/12/03 13:31:24 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_clean_sem(t_prog *prog)
{
	sem_close(prog->forks);
	sem_close(prog->print);
	sem_close(prog->death);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("death");
}

void	ft_usleep(int time, t_philo *philo)
{
	int	start;

	start = get_time_ms();
	while (get_time_ms() - start < time)
	{
		if (!ft_check_death(philo))
			break ;
		usleep(100);
	}
}

int	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	terminate_process(t_prog *prog)
{
	int	i;

	i = 0;
	ft_clean_sem(prog);
	while (i < prog->nb_of_philo)
	{
		kill(prog->philo[i].pid, SIGKILL);
		i++;
	}
}