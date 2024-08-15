/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:47:37 by smallem           #+#    #+#             */
/*   Updated: 2023/05/07 17:35:07 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nbelem, size_t sizelem)
{
	char	*ptr;

	if (sizelem && SIZE_MAX / sizelem < nbelem)
		return (NULL);
	ptr = (char *)malloc(nbelem * sizelem);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nbelem * sizelem);
	return (ptr);
}
