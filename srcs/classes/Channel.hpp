#include <iostream>
#include <cstring>
#include <map>
#include <pair>

#include "User.hpp"


/*	This is the main class for the Channel : it groups the main info about it, 
*	like the name, user list	*/

namespace irc
{

class   Channel
{
	public :
		Channel(std::string name);
		~Channel();

		std::string const &				getName() const;
		std::map<std::string, User*>	getUsers();

		//user management
		int								addUser(User* user);
		int								rmUser(std::string nick);
		User*							findUser(std::string nick);

	private :
		Channel();

		std::map<std::string, User*>		_users;		//list of all the users on the channel, the pair is <nick, address>
		std::string 						_name;		//name of the channel (initialized by the user command '/join *name*')
}



}   //namespace end