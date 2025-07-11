/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:03:10 by algultse          #+#    #+#             */
/*   Updated: 2024/04/15 14:12:37 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	**malloc_realloc(t_malloc *m)
{
	void	**new_mallocs;
	size_t	i;

	new_mallocs = malloc(sizeof(void *) * (m->len + 1));
	if (new_mallocs == NULL)
		return (NULL);
	i = 0;
	while (i < m->len && m->mallocs)
	{
		new_mallocs[i] = m->mallocs[i];
		i++;
	}
	if (m->mallocs)
		free(m->mallocs);
	return (new_mallocs);
}

void	ft_free_all(t_malloc *m)
{
	if (m == NULL)
		return ;
	if (m->mallocs == NULL)
	{
		free(m);
		return ;
	}
	while (m->len > 0)
		free(m->mallocs[--(m->len)]);
	free(m->mallocs);
	free(m);
}

void	*ft_malloc(t_malloc *m, int blocks)
{
	void	*new_block;

	if (m == NULL || blocks <= 0)
		return (NULL);
	new_block = malloc(blocks);
	if (new_block == NULL)
		return (NULL);
	m->mallocs = malloc_realloc(m);
	if (m->mallocs == NULL)
	{
		free(new_block);
		return (NULL);
	}
	m->mallocs[m->len] = new_block;
	m->len++;
	return (new_block);
}

t_malloc	*init_malloc(void)
{
	t_malloc	*m;

	m = (t_malloc *)malloc(sizeof(t_malloc));
	if (m == NULL)
		return (NULL);
	m->mallocs = NULL;
	m->len = 0;
	return (m);
}
