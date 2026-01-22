/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 18:58:31 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/11 15:42:16 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_maze *maze)
{
	if (key == XK_Escape)
		close_window();
	else if (key == XK_w)
		maze->keys.w = 1;
	else if (key == XK_s)
		maze->keys.s = 1;
	else if (key == XK_a)
		maze->keys.a = 1;
	else if (key == XK_d)
		maze->keys.d = 1;
	else if (key == XK_Left)
		maze->keys.left = 1;
	else if (key == XK_Right)
		maze->keys.right = 1;
	return (0);
}

int	key_release(int key, t_maze *maze)
{
	if (key == XK_e)
		try_open_door(maze);
	else if (key == XK_w)
		maze->keys.w = 0;
	else if (key == XK_s)
		maze->keys.s = 0;
	else if (key == XK_a)
		maze->keys.a = 0;
	else if (key == XK_d)
		maze->keys.d = 0;
	else if (key == XK_Left)
		maze->keys.left = 0;
	else if (key == XK_Right)
		maze->keys.right = 0;
	return (0);
}

// static void	limit_framerate(void)
// {
// 	static long		last_us = 0;
// 	struct timeval	now;
// 	long			now_us;
// 	long			target_us;
// 	long			delta;
// 	long			rem;
// 			struct timespec ts;

// 	target_us = 1000000 / FRAME_CAP;
// 	gettimeofday(&now, NULL);
// 	now_us = now.tv_sec * 1000000L + now.tv_usec;
// 	if (last_us != 0)
// 	{
// 		delta = now_us - last_us;
// 		if (delta < target_us)
// 		{
// 			rem = target_us - delta;
// 			ts.tv_sec = rem / 1000000L;
// 			ts.tv_nsec = (rem % 1000000L) * 1000L;
// 			nanosleep(&ts, NULL);
// 		}
// 	}
// 	gettimeofday(&now, NULL);
// 	last_us = now.tv_sec * 1000000L + now.tv_usec;
// }

static void	limit_framerate(void)
{
	static long		last = 0;
	long			elapsed;
	struct timeval	now;

	gettimeofday(&now, NULL);
	elapsed = now.tv_sec * 1000000L + now.tv_usec - last;
	if (last && elapsed < 1000000L / FRAME_CAP)
		usleep((1000000L / FRAME_CAP) - elapsed);
	gettimeofday(&now, NULL);
	last = now.tv_sec * 1000000L + now.tv_usec;
}

int	render_maze(t_maze *maze)
{
	t_player	*p;

	p = &maze->map.player;
	if (maze->keys.w)
		move_forward(maze, p);
	if (maze->keys.s)
		move_backward(maze, p);
	if (maze->keys.a)
		move_left(maze, p);
	if (maze->keys.d)
		move_right(maze, p);
	if (maze->keys.right)
		rotate(p, ROT_SPEED);
	if (maze->keys.left)
		rotate(p, -ROT_SPEED);
	render_frame(maze);
	limit_framerate();
	return (0);
}
