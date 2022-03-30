/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_pass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:41:33 by labintei          #+#    #+#             */
/*   Updated: 2022/03/30 21:00:07 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Message.hpp"
#include "../numeric_replies.hpp"
//#include "cstring"

/*
std::string message_print(
std::string nameserver, 
std::string code, 
std::string nick, 
std::string msg, 
bool op)
*/

/*
std::string		message_print1(std::string nameserver, std::string code, std::string nick, std::string msg, bool op)
{
    if(op == true)
        return("*:" + nameserver + " " + code + " " + nick + " " + msg);
    else
        return(":" + nameserver + " " + code + " " + nick + " " + msg);
}
*/

void	irc::Message::Message_p(std::string code, std::string code_msg)
{
	this->_sender->sendMsg(message_print(this->_server->getServername(), code , this->_sender->getNick(), code_msg , this->_sender->getOpper()));
}

void	irc::Message::pass()
{
	if(this->_params[0] == "")
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	else if(this->_sender->getPass() != "")
		this->Message_p(ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MSG());
	else
		this->_sender->setPass(this->_params[0]);
}

void	irc::Message::nick()
{
	if(this->_params[0] == "")
		this->Message_p(ERR_NONICKNAMEGIVEN, ERR_NONICKNAMEGIVEN_MSG());
	else if(this->_server->findClient_nick(this->_params[0]))
		this->Message_p(ERR_NICKNAMEINUSE, ERR_NICKNAMEINUSE_MSG(this->_params[0]));
	else
		this->_sender->setNick(this->_params[0]);
	// ERRONEUSNICKNAME
	// UNAVAILLABLERESOURCE
	// ERRNICKCOLLISION
	// ERRRESTRICTED
}

void	irc::Message::user()
{
	if(this->_params[0] == "")
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	else if(this->_server->findClient_user(this->_params[0]))
		this->Message_p(ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MSG());
	else
	{
		this->_sender->setUsername(this->_params[0]);
		// voir pour mettre les mode et real name
	}
}

void	irc::Message::opper()
{
	if(this->_params[0] == "")
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	else if(this->_params[1] != this->_server->getPassword())
		this->Message_p(ERR_PASSWDMISMATCH, ERR_PASSWDMISMATCH_MSG());
	else
	{
		this->_sender->setOper(true);
		this->Message_p(RPL_YOUREOPER, RPL_YOUREOPER_MSG());
	}
	// MANQUE ERR_NOOPERHOST
}


// Les channel se trouve au niveau du Server
void	irc::Message::join()
{
	if(this->_params[0] == "")
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	

}

void	irc::Message::part()
{


}

void	irc::Message::topic()
{

}

void	irc::Message::names()
{

}

void	irc::Message::list()
{

}

void	irc::Message::invite()
{

}

void	irc::Message::kick()
{

}

void	irc::Message::privmsg()
{

}

void	irc::Message::notice()
{

}

void	irc::Message::admin()
{

}

//(nick name collision)
void	irc::Message::kill()
{

}

//(DIE opper)
void	irc::Message::die()
{

}

void	irc::Message::restart()
{

}


/*
void	irc::Message::pass()
{
	if(this->_params[0] == "")
		sender->sendMsg(message_print(this->_server->_servername, ERR_NEEDMOREPARAMS, this->sender->getNick(), ERR_NEEDMOREPARAMS_MSG() , this->_sender->getUsername(), this->_sender->_opper));
	else if(this->_sender->_pass != "")
		sender->sendMsg(message_print(this->_server->_servername, ERR_ALREADYREGISTERED, this->sender->getNick(), ERR_ALREADYREGISTERED_MSG() , this->_sender->getUsername(), this->_sender->_opper));
	else
		sender->setPass(this->_params[0]);
}

void	irc::Message::nick()
{
	if(this->_params[0] == "")
		sender->sendMsg(message_print(this->_server->_servername, ERR_NONICKNAMEGIVEN, this->sender->getNick(), ERR_NONICKNAMEGIVEN_MSG() , this->_sender->getUsername(), this->_sender->_opper));
	else if(this->_server->findClient_nick(this->_params[0]))
		sender->sendMsg(message_print(this->_server->_servername, ERR_NICKNAMEINUSE, this->sender->getNick(), ERR_NICKNAMEINUSE_MSG() , this->_sender->getUsername(), this->_sender->_opper));
	else
		this->_sender->setNick(this->_params[0]);
	// ERRONEUSNICKNAME
	// UNAVAILLABLERESOURCE
	// ERRNICKCOLLISION
	// ERRRESTRICTED
}

void	irc::Message::user()
{
	if(this->params[0] == "")
		sender->sendMsg(message_print(this->_server->_servername, ERR_NEEDMOREPARAMS, this->sender->getNick(), ERR_NEEDMOREPARAMS_MSG() , this->_sender->getUsername(), this->_sender->_opper));
	else if(this->_server->findClient_user(this->_params[0]))
		sender->sendMsg(message_print(this->_server->_servername, ERR_ALREADYREGISTERED, this->sender->getNick(), ERR_ALREADYREGISTERED_MSG() , this->_sender->getUsername(), this->_sender->_opper));
	else
	{
		this->_sender->setUsername(params[0]);
		// voir pour mettre les mode et real name
	}
}


// On va partir du principe que tout le monde peut devenir opper
void	irc::Message::oper()
{

}
*/


