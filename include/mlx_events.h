/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:11:48 by lucpardo          #+#    #+#             */
/*   Updated: 2026/02/02 01:27:37 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MLX_EVENTS_H
# define MLX_EVENTS_H

// x11 event types (first parameter in mlx_hook)
# define MLX_KEYPRESS			2
# define MLX_KEYRELEASE			3
# define MLX_BUTTONPRESS		4
# define MLX_BUTTONRELEASE		5
# define MLX_MOTIONNOTIFY		6
# define MLX_EXPOSE				12
# define MLX_DESTROYNOTIFY		17

// x11 event masks (second parameter in mlx_hook)
# define MLX_NOEVENTMASK		0L
# define MLX_KEYPRESSMASK		(1L << 0)
# define MLX_KEYRELEASEMASK		(1L << 1)
# define MLX_BUTTONPRESSMASK	(1L << 2)
# define MLX_BUTTONRELEASEMASK	(1L << 3)
# define MLX_POINTERMOTIONMASK	(1L << 6)
# define MLX_EXPOSUREMASK		(1L << 15)

#endif
