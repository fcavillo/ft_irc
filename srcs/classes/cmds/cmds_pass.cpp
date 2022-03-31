/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_pass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:41:33 by labintei          #+#    #+#             */
/*   Updated: 2022/03/31 21:22:28 by labintei         ###   ########.fr       */
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

bool		irc::isSpecial(char c){ return (c >= '[' && c <= ''') || (c >= '{' && c <= '}');}
bool		irc::isLetter(char c){ return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');}
bool		irc::isChiffre(char c){ return (c >= '0' && c <= '9');}



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

bool	irc::nick_check_char(std::string params)
{
	for(size_t index = 1; index < params.lenght(); ++index)
		if(!isLetter(params[index]) && !isSpecial(params[index]) && !isChiffre(params[index]))
			return(false);
	return(true);
}

void	irc::irc::Client*		irc::Server::findNick(std::string nick)

void	irc::Message::nick()
{
	if(this->_params[0] == "")
		this->Message_p(ERR_NONICKNAMEGIVEN, ERR_NONICKNAMEGIVEN_MSG());
	else if(this->_server->findNick(this->_params[0])) // Si c est deja le meme nickname
		this->Message_p(ERR_NICKNAMEINUSE, ERR_NICKNAMEINUSE_MSG(this->_params[0]));
	else if(this->_params[0].lenght() > 9 || (!isLetter(this->-params[0][0]) && !isSpecial(this->_params[0][0])))
		this->Message_p(ERR_ERRONEUSNICKNAME, ERR_ERRONEUSNICKNAME_MSG(this->_params[0]));
	else if(!(nick_check_char(this->_params[0])))
		this->Message_p(ERR_ERRONEUSNICKNAME, ERR_ERRONEUSNICKNAME_MSG(this->_params[0]));
	else
		this->_sender->setNick(this->_params[0]);
	// RETOURNER PAR UN SERVER SI LA CONNECTION EST DITE RESTRICTED user mode "+r"
//	this->Message_p(ERR_RESTRICTED, ERR_RESTRICTED_MSG());
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
		if(this->_sender->getUsername() == "labintei" || this->_sender->getUsername() == "fcavillo")
		{
			this->_sender->setOper(true);
			this->Message_p(RPL_YOUREOPER, RPL_YOUREOPER_MSG());
		}
		else
			this->Message_p(ERR_NOOPERHOST, ERR_NOOPERHOST_MSG());
	}
}
/*
void	irc::Message::parse(std::string line)
{
	int							pref = 0;
	int							j = 0;
	std::vector<std::string>	v;
	std::string					word;

	for (int i = 0; i < (int)line.size(); i++)
	{
		if (line[i] == ' ')
		{
			while (line[i] == ' ' && line[i + 1] == ' ')
				i++;
			if (word.size() > 0)
			{
				if(pref == 0 && line[i] == ':')
				{
					this->_prefix = word;
					pref++;
				}
				else if(this->_cmds == "")
					this->_cmds = word;
				else
					this->_params.push_back(word);
				pref++;
			}
			word.clear();
		}
		else if(line[i] != ' ')
		{
			word += line[i];
//			std::cout << word << std::endl;			//commenté pour y voir plus clair, déso :)
		}
	}
	if (word.size() > 0)
	{
		if(pref == 0 && line[j] == ':')
			this->_prefix = word;
		else if(this->_cmds == "")
			this->_cmds = word;
		else
			this->_params.push_back(word);
	}
	word.clear();
	return (v);
}*/

std::vector<std::string>		splitChar(std::string line, char c)
{
	std::string		word;
	std::vector<std::string>	v;

	for (int i = 0; i < (int)line.size(); i++)
	{
		if(line[i] == c)
		{
			if(word.size())
			{
				v.pushback(word);
				word.clear();
			}
		}
		else
			word += line[i];
	}
	if(word.size())
		v.push_back(word);
	return(v);
}


// Les channel se trouve au niveau du Server
void	irc::Message::join()
{
	std::vector<std::string>	names;
	std::vector<std::string>	key;

	if(this->_params[0] == "")
		this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	v = splitChar(this->_params[0], ',');
	if(this->_params[1] != "")
		key = splitChar(this->_params[1], ',');
	if()


	// PAS A GERER LES MODES
	//this->Message_p(ERR_INVITEONLYCHAN, ERR_INVITEONLYCHAN_MSG());
	// quand un server va fermer et que l acces au serveur va etre fermmee
	//this->Message_p(ERR_CHANNELISTFULL, ERR_CHANNELISTFULL_MSG());
	
	// Pour un nom de channel invalide
	this->Message_p(ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG());
	// Quand un client cherche a rejindre un channel qui a ! et qui a plusieurs short name equivalents
	this->Message_p(ERR_TOOMANYTARGETS, ERR_TOOMANYTARGETS_MSG());
	// Quand un client est ban
	this->Message_p(ERR_BANNEDFROMCHAN, ERR_BANNEDFROMCHAN_MSG());
	// Quand le client donne la mauvaise clee pour acceder au channel;
	this->Message_p(ERR_BADCHANNELKEY, ERR_BADCHANNELKEY_MSG());
	// MEME QUE CHANNELLIST IS FULL
	//this->Message_p(ERR_BADCHANMASK, ERR_BADCHANMASK_MSG());
	
	// Users join the max number of channels;
	this->Message_p(ERR_TOOMANYCHANNELS, ERR_TOOMANYCHANNELS());
	// Bloquer par le channel delay mecanism;
	this-<Message_p(ERR_UNAVAILRESOURCE, ERR_UNAVAILRESOURCE_MSG());
}

void	irc::Message::part()
{
	/*this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS(this->_cmds));
	this->Message_p(ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MSG());
	this->Message_p(ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG());
	*/
}

void	irc::Message::topic()
{/*
	this->Message_p(ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG(this->_cmds));
	this->Message_p(ERR_NOTOPIC, ERR_NOTOPIC_MSG());
	this->Message_p(ERR_CHANOPRIVSNEEDED, ERR_CHANOPRIVSNEEDED_MSG());
	this->Message_p(ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MSG());
	this->Message_p(ERR_NOCHANMODES, ERR_NOCHANMODES_MSG());*/
}

void	irc::Message::names()
{
//	this->Message_p(ERR_TOOMANYMATCHES, )
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
{/*
	this->Message_p(ERR_NOSUCHSERVER, ERR_NOSUCHSERVER_MSG());
	this->Message_p(ERR_ADMINME, ERR_ADMINME_MSG());
	this->Message_p(ERR_ADMINLOC1, ERR_ADMINLOC1_MSG());
	this->Message_p(ERR_ADMINLOC2, ERR_ADMINLOC2_MSG());
	this->Message_p(ERR_ADMINEMAIL, ERR_ADMINEMAIL_MSG());*/
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


