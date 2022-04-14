#include <iostream>
#include <cstring>
#include <map>
#include <utility>
#include <vector>

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

// #include "numeric_replies.hpp"
#include "Client.hpp"
#include "Server.hpp"

// ADD Lauranne
#include "Channel.hpp"


// #include "cmds/cmds_pong.cpp"

/*	This is the main class for the Message : it groups the main info about it, 
*	like the sender, receiver, command called and command map	*/

namespace irc
{

class	Client;
class	Server;
class	Channel;

class   Message
{
	public :
		Message(std::string line, Server *data, Client *user);
		~Message();

//	private :
		irc::Server*			_server;
		irc::Client*	 		_sender;	
		std::string				_fullCommand;	//full sent command, before splitting

	// AFTER PARSING
		std::string					_prefix;
		std::string					_cmds;
		std::vector<std::string>	_params;
	// retour charriot mais on s en fiche

		std::vector<std::string>	v_split(std::string line);
		Message();

	public :

		irc::Client*			getSender() const;
//		irc::Client*			getnonconstSender();
		irc::Server*			getServer()	const;
//		irc::Server*			getnonconstServer();
//		void					messageparse(std::string line, Server *server, Client *sender)
		void					parse(std::string line);

	// CMDS REGISTER

	// CMDS CHANNEL



	// CMDS OPER
	void	Message_cmds(std::string cmds, std::string facultatif, Client *a);
	void	Message_c(std::string code, std::string code_msg, Client *a);
	void	Message_p(std::string code, std::string code_msg);
	void	Messagejoin(Channel* chan);//ADD LABINTEI
	void	pass();
	void	nick();
	void	user();
	void	oper();
	void	join();
	void	part();
	void	topic();
	void	names();
	void	list();
	void	invite();
	void	kick();
	void	privmsg();
	void	notice();
	void	admin();
	void	kill();
	void	die();
	void	restart();
	void	pong();
	void	quit();
	void	welcome();
	void	userhost();
	void	mode();
	void	who();

	// ADD Lauranne
	//
	void	MessagetoChannel(std::string cdms, std::string facultatif, Channel* b);
	};

};   //namespace end

#endif
