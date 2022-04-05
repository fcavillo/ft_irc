/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_pong.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:15:01 by fcavillo          #+#    #+#             */
/*   Updated: 2022/04/05 12:00:55 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Message.hpp"
// #include "../numeric_replies.hpp"

//to do : 
//	team : ask about the version : is 1.0 ok ?
//	team : change IRC for localhost in servername ?
//  team : need passwords for channels ?
//	client : store messages from a client in a client-unique vector
//  server : handling signals


// void	irc::Message::pong()
// {
// 	if (_params.size() == 0)
// 		Message_p(ERR_NOORIGIN, ERR_NOORIGIN_MSG());
// 	else if (_params.size() > 1)
// 		Message_p(ERR_NOSUCHSERVER, ERR_NOSUCHSERVER_MSG(_server->getServername()));
// 	else
// 		_sender->sendMsg("PONG : " + _params[0]);
// 	std::cout << "user is a member of : " << std::endl;
// 	for (int i = 0; i < (int)_sender->getMembership().size(); i++)
// 		std::cout << _sender->getMembership()[i]->getName() << std::endl;
	
// }

// /*	A client session is terminated with a quit message.  */
// void	irc::Message::quit()
// {
// 	_sender->leaveAllChannels();
// 	_sender->leaveServer();
// 	close(_sender->getSocket());
// }

// void	irc::Message::welcome()
// {
// 	Message_p(RPL_WELCOME, RPL_WELCOME_MSG(_sender->getNick(), _sender->getUsername(), _server->getServername()));
// 	Message_p(RPL_YOURHOST, RPL_YOURHOST_MSG(_server->getServername(), "1.0"));
// 	Message_p(RPL_CREATED, RPL_CREATED_MSG(_server->getStartTimeString()));
// 	Message_p(RPL_MYINFO, RPL_MYINFO_MSG(_server->getServername(), "1.0", "aiwroOS", "c_modes"));
// }

