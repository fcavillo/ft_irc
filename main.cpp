/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:29:24 by fcavillo          #+#    #+#             */
/*   Updated: 2022/03/15 10:47:21 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "srcs/classes/Server.hpp"

/*	Program is started with av[0] = ircserv, av[1] = port, av[2] = password	*/
int     main(int ac, char **av)
{
	try
	{
		//argument errors
		if (ac != 3)
			throw std::invalid_argument("Error : Please start the server with this format :\n./ircserv <port> <password>");		
		else if (*(av[2]) == '\0')
			throw std::invalid_argument("Error : Cannot use NULL as the password");		
		else if (*(av[1]) == '\0')
			throw std::invalid_argument("Error : invalid port number");	
		for (int i = 0; av[1][i]; i++)
			if (!isdigit(av[1][i]))
				throw std::invalid_argument("Error : invalid port number");
	
		irc::Server	server(av[1], av[2]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}
	
	return (0);
}