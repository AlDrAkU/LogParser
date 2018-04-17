#include "EverquestLog.h"
#include <iostream>
#include <algorithm>
#include <fstream>
EverquestLog::EverquestLog(const std::string & fileName)
	:m_Data{}
	, m_Enemy{}
	, m_AddedDamage{}
{
	ParseFile(fileName);
}

void EverquestLog::PrintData()
{
	PrintContainer();
	AddDamagePerSpell();
	PrintSpellSorted();
	PrintDamageSorted();
	PrintTotal();


}

void EverquestLog::ParseFile(const std::string& fileName)
{
	std::ifstream input{ fileName };
	if (!input)
	{
		throw std::runtime_error("Loading file failed: " + fileName);
	}
	std::string line{};
	while (input.good())
	{
		std::getline(input, line);
		if (line.find(" damage from ") != std::string::npos)
		{
			if (m_Enemy.size() == 0)
			{
				GetEnemy(line, m_Enemy);
			}
			int time{};
			int damage{};
			std::string spell{};
			GetTime(line, time);
			GetDamage(line, damage);
			GetSpell(line, spell);
			m_Data.insert(std::pair<int, std::pair<int, std::string>>(time, std::pair<int, std::string>(damage, spell)));
		}
	}
}

void EverquestLog::GetTime(const std::string & line, int& time) const
{
	int timePos = line.find(':');
	timePos -= 2;

	int totalTime{};
	std::string temp{};
	while (line.at(timePos) != ':')
	{
		temp += line.at(timePos);
		++timePos;
	}
	totalTime += std::stoi(temp) * 3600;
	temp.clear();
	++timePos;

	while (line.at(timePos) != ':')
	{
		temp += line.at(timePos);
		++timePos;
	}
	totalTime += std::stoi(temp) * 60;
	temp.clear();
	++timePos;


	while (line.at(timePos) != ' ')
	{
		temp += line.at(timePos);
		++timePos;
	}
	totalTime += std::stoi(temp);
	time = totalTime;
}

void EverquestLog::GetDamage(const std::string & line, int& damage) const
{
	std::string search{ " has taken " };
	int idx = line.find(search);
	idx += search.size();
	std::string temp{};
	while (line.at(idx) != ' ')
	{
		temp += line.at(idx);
		++idx;
	}
	damage = std::stoi(temp);
}

void EverquestLog::GetSpell(const std::string & line, std::string & spell) const
{
	std::string search{ " damage from your " };
	int idx = line.find(search);
	idx += search.size();
	std::string temp{};
	while (idx != line.size() - 1)
	{
		temp += line.at(idx);
		++idx;
	}
	spell = temp;
}

void EverquestLog::GetEnemy(const std::string & line, std::string & enemy) const
{
	std::string search{ " has taken " };
	int idx = line.find(']') +2;
	int endIdx = line.find(search);
	idx += search.size();
	std::string temp{};
	while (idx != endIdx)
	{
		temp += line.at(idx);
		++idx;
	}
	enemy = temp;
}

void EverquestLog::PrintContainer() const
{
	for (const std::pair<int, std::pair<int, std::string>>& i : m_Data)
	{
		std::cout << m_Enemy << " has taken " << i.second.first << " damage from " << i.second.second << " , at " << i.first << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void EverquestLog::PrintSpellSorted() const
{
	for (const std::pair<std::string,int>&i : m_AddedDamage)
	{
		std::cout << m_Enemy << " has taken " << i.second << " damage " << '\t' << " from " << i.first << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void EverquestLog::PrintDamageSorted()
{
	std::multimap<int, std::string> temp{};
	for (const std::pair<std::string,int>& i : m_AddedDamage)
	{
		temp.insert(std::pair<int, std::string>(i.second, i.first));
	}
	for (const std::pair<int,std::string>& i : temp)
	{
		std::cout << m_Enemy << " has taken " << i.first << " damage " << '\t' << "from " << i.second << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void EverquestLog::AddDamagePerSpell()
{
	std::map<std::string, int> temp{};
	for (const std::pair<int,std::pair<int,std::string>>& i : m_Data)
	{
		temp[i.second.second] += i.second.first;
	}
	m_AddedDamage = temp;
}

void EverquestLog::PrintTotal()
{
	int totD{};
	for (const std::pair<std::string,int>& i : m_AddedDamage)
	{
		totD += i.second;
	}
	std::cout << "Total damage = " << totD << std::endl;
	int totS{};
	std::multimap<int, std::pair<int, std::string>>::iterator it{ m_Data.end() };
	--it;
	totS = it->first - m_Data.begin()->first;

	float totDPS = float(totD) / float(totS);
	std::cout << "Total DPS = " << totDPS << std::endl;

}
