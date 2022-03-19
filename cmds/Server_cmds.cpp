/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_cmds.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:45:14 by labintei          #+#    #+#             */
/*   Updated: 2022/03/19 15:26:23 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/classes/Server.hpp"



// <nickname>@<username>!<hostname> <COMMAND> <ARG>\r\n
int		irc::Server::PASS(std::string* pass)
{
	if(!(pass[1]))// NEED MORE PARAMS
	{
		std::cout << ERR_NEEDMOREPARAMS_MSG("PASS");
		return(ERR_NEEDMOREPARAMS)
	}
	if(this->_password)
	{
		std::cout << ERR_ALREADYREGISTRED_MSG();
		return(ERR_ALREADYREGISTRED);
	}
	else
	{
		this->_password = (pass[1]);
		return()
	}
}

int		irc::Server::user_already_exist(std::string	nick)
{
	for()
	{

	}
}


int		irc::Server::NICK(std::string* cmds)
{
	if(this->user_already_exist(cmds[1]))
	{
		std::cout << ERR_NICKCOLLISION_MSG();
		return(ERR_NICKCOLLISION);
	}
	if(!(cmds[1]))
	{
		std::cout << ERR_NONICKNAMEGIVEN_MSG();
		return(ERR_NONICKNAMEGIVEN);
	}


}


