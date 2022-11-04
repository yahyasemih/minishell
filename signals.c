/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 03:38:20 by yez-zain          #+#    #+#             */
/*   Updated: 2022/10/24 03:38:24 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	cmd_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (!g_minishell_ctx.is_executing)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		g_minishell_ctx.exit_status = 1;
	}
}

void	install_signal_handlers(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, cmd_signal_handler);
	signal(SIGQUIT, cmd_signal_handler);
	signal(SIGSTOP, cmd_signal_handler);
}

static const char	*first_signals(int sig)
{
	if (sig == SIGHUP)
		return ("Hangup: 1\n");
	if (sig == SIGINT)
		return ("\n");
	if (sig == SIGQUIT)
		return ("Quit: 3\n");
	if (sig == SIGILL)
		return ("Illegal instruction: 4\n");
	if (sig == SIGTRAP)
		return ("Trace/BPT trap: 5\n");
	if (sig == SIGABRT)
		return ("Abort trap: 6\n");
	if (sig == SIGEMT)
		return ("EMT trap: 7\n");
	if (sig == SIGFPE)
		return ("Floating point exception: 8\n");
	if (sig == SIGKILL)
		return ("Killed: 9\n");
	if (sig == SIGBUS)
		return ("Bus error: 10\n");
	if (sig == SIGSEGV)
		return ("Segmentation fault: 11\n");
	if (sig == SIGSYS)
		return ("Bad system call: 12\n");
	return ("");
}

const char	*signal_name(int sig)
{
	if (sig <= SIGSYS)
		return (first_signals(sig));
	if (sig == SIGALRM)
		return ("Alarm clock: 14\n");
	if (sig == SIGTERM)
		return ("Terminated: 15\n");
	if (sig == SIGXCPU)
		return ("Cputime limit exceeded: 24\n");
	if (sig == SIGXFSZ)
		return ("Filesize limit exceeded: 25\n");
	if (sig == SIGVTALRM)
		return ("Virtual timer expired: 26\n");
	if (sig == SIGPROF)
		return ("Profiling timer expired: 27\n");
	if (sig == SIGUSR1)
		return ("User defined signal 1: 30\n");
	if (sig == SIGUSR2)
		return ("User defined signal 2: 31\n");
	return ("");
}
