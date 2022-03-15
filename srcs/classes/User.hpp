#include <iostream>
#include <cstring>


/*	This is the main class for the User : it groups the main info about it, 
*	like the username, nickname, real name, status	*/

namespace irc
{

class   User
{
	public :
		User();
		~User();

		std::string const &		getUsername() const;
		std::string const &		getNick() const;
		std::string const &		getRealName() const;
		bool const &			getOper() const;
		void					setUsername(std::string username);
		void					setNick(std::string nick);
		void					setRealName(std::string realName);
		void					setOper(bool oper);					//used in user command /oper

	private :

		bool			_oper;										//1 if user is operator, 0 by default
		std::string 	_username;
		std::string		_nick;
		std::string		_realName;
		std::string		_password;
}



}   //namespace end