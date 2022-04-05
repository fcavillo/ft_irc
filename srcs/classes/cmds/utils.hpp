/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:36:15 by labintei          #+#    #+#             */
/*   Updated: 2022/04/05 11:25:03 by fcavillo         ###   ########.fr       */
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
					v.push_back(word);
					word.clear();
				}
			}
			else
				word += line[i];
		}
		if(word.size())
			v.push_back(word);
		return(v);
	};
	
	bool	validChannelName(std::string s)
	{
		(void)s;		//pour que ca compile, dsl
		return true;
		//for
	};



};


#endif
