/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:29:24 by fcavillo          #+#    #+#             */
/*   Updated: 2022/03/15 10:23:55 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "srcs/classes/Server.hpp"

int     main(int ac, char **av)
{
	if (ac == 3)
	{
		return (0);
	}
	std::cout << "Please start the server with this format :\n./ircserv <port> <password>" << std::endl;
	(void)av;
	return (1);
}