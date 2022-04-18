/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:36:15 by labintei          #+#    #+#             */
/*   Updated: 2022/04/18 14:41:01 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		UTILS_HPP
#define		UTILS_HPP

#include<cstring>

namespace	irc
{
	bool		isSpecial(char c){ return (c >= '[' && c <= '\'') || (c >= '{' && c <= '}');};
	bool		isLetter(char c){ return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');};
	bool		isChiffre(char c){ return (c >= '0' && c <= '9');};

	bool		nick_check_char(std::string params)
	{
		for(size_t index = 1; index < params.length(); ++index)
			if(!isLetter(params[index]) && !isSpecial(params[index]) && !isChiffre(params[index]))
				return(false);
		return(true);
	};

	int								ftatoi(std::string s) // ft_atoi sans secu
	{
		int		n = 0;

		for(size_t y = 0; s[y] != '\0'; y++)
		{
			if(isChiffre(s[y]))
				n = (n * 10) + (s[y] - '0');
		}
		return(n);
	}

	std::vector<std::string>		splitChar(std::string line, char c)
	{
		std::string		word;
		std::vector<std::string>	v;

		if(line.size() != 0)
		{
			for (int i = 0; i < (int)line.size(); i++)
			{
				if(line[i] == c)
				{
					if(word.size())
					{
						v.push_back(word);
						word.clear();
					}
				}
				else
					word += line[i];
			}
			if(word.size())
				v.push_back(word);
		}
		return(v);
	};
	
	bool	validChannelName(std::string s)
	{
		(void)s;		//pour que ca compile, dsl
		return true;
		//for
	};

	bool	ftFind(char c, std::string s)
	{
		for(size_t e = 0; s[e] != '\0'; e++)
		{
			if(s[e] == c)
				return(true);
		}
		return(false);
	};


	bool	ftFinds(std::string find, std::string s)
	{
		for(size_t e = 0; s[e] != '\0'; e++)
		{
			for(size_t o = 0; find[o] != '\0' ; o++)
			{
				if(find[o] == s[e])
					return(true);
			}
		}
		return(false);
	};


	std::string		cutChar(std::string s, char c, int i)
	{
		std::string		u;
		int				b = 0;

		for(size_t r = 0; s[r] != '\0'; r++)
		{
			if(s[r] == c)
			{
				b = 1;
			}
			else if(i == 0 && b == 0)
			{
				u += s[r];
			}
			else if(i == 1 && b == 1)
			{
				u += s[r];
			}
		}
		return u;

	};

	std::string		convertVectortoString(std::vector<std::string> s, int c)
	{
		std::string		r;
		int				j = 0;

		for(std::vector<std::string>::iterator it = s.begin() ; it != s.end() ; it++)
		{
			if(j >= c)
			{
				r += (*it);
				if(it + 1 != s.end())
				{
					r += " ";
				}
			}
			j++;
		}
		return(r);
	};

	std::string		extensionValidPrivmsg(std::string	params)
	{
		std::string		extension;
		std::string		p;

		if(params != "")
		{
			if(params[0] != '#' || params[0] != '$')
				return(NULL);
			if(params[1] != '*')
				return(NULL);
			if(params[2] != '.')
				return(NULL);
			for(int		i = 3; params[i] != '\0'; i++)
			{
				extension += params[i];
			}
			if(ftFind('?', extension) || ftFind('#', extension))
				return(NULL);
			return(extension);
		}
		else
			return(NULL);
	};

};


#endif
