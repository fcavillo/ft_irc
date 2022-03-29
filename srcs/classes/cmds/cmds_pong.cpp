/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_pong.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:15:01 by fcavillo          #+#    #+#             */
/*   Updated: 2022/03/29 16:17:16 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server.hpp"
#include "../Message.hpp"

// void    pong(irc::Message* message) //no server2 since interserver communication is not in the subject
// {
// 	if (message->_params.size() == 0)
// 		message->sender->sendMsg(message_print(message->server->getServername(), ERR_NOORIGIN, ERR_NOORIGIN(), false));
// 	else
//         message->sender->sendMsg("PONG : " + message->_params[0]);

// }