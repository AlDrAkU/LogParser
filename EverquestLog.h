#pragma once
#include <map>
#include <string>

class EverquestLog
{
public:
	explicit EverquestLog(const std::string& fileName);
	void PrintData();

private:
	std::multimap<int, std::pair<int, std::string>>m_Data;
	std::map<std::string, int> m_AddedDamage;
	std::string m_Enemy;


	void ParseFile(const std::string& fileName);
	void GetTime(const std::string& line, int& time) const;
	void GetDamage(const std::string& line, int& damage)const;
	void GetSpell(const std::string& line, std::string& spell)const;
	void GetEnemy(const std::string& line, std::string& enemy)const;

	void PrintContainer() const;
	void PrintSpellSorted()const;
	void PrintDamageSorted();
	void AddDamagePerSpell();
	void PrintTotal();




};

