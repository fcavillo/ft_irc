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
	//Argument error handling
	if (ac != 3)
	{
		std::cout << "Please start the server with this format :\n./ircserv <port> <password>" << std::endl;		
		return (1);
	}
	else if (*(av[2]) == '\0')
	{
		std::cout << "Cannot use NULL as the password" << std::endl;		
		return (1);
	}

	
	irc::Server*	server;
	
	try
	{
		server = new irc::Server(av[1], av[2]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}
	
	
	return (0);
}