/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_pass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:41:33 by labintei          #+#    #+#             */
/*   Updated: 2022/03/28 18:44:13 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Message.hpp"

irc::Message::Message(std::string line, Server *server, Client *sender) : _server(server), _sender(sender), _fullCommand(line)
