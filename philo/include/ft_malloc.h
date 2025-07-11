/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:15:09 by algultse          #+#    #+#             */
/*   Updated: 2024/03/18 16:52:12 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>

typedef struct s_malloc {
	void	**mallocs;
	size_t	len;
}				t_malloc;

void		*ft_malloc(t_malloc *m, int blocks);
void		ft_free_all(t_malloc *m);
void		**malloc_realloc(t_malloc *m);
t_malloc	*init_malloc(void);

#endif