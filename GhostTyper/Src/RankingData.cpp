#include<iostream>
#include "RankingData.h"
#include<sstream>
#include<time.h>
RankingData::RankingData()
{
}

RankingData::RankingData(int rank, char name[], int complete, char artname[], int correct, float time)
    :rank(rank),name(),complete(complete),artname(),correct(correct),time(time)
{
}

std::string RankingData::formatInfo()
{
	std::stringstream ss;
	ss << rank << '\t' << name << '\t' << complete<<'\t'<<artname<<'\t'<<correct<<'\t'<<time << std::endl;
	return ss.str();
}

void RankingData::display()
{
	std::cout << this->rank << '\t' << this->name << '\t' << this->complete << '\t' << this->artname << '\t' << this->correct << '\t' << this->time << '\t' << std::endl;
}

void RankingData::formatWrite(const std::string& str)
{
	std::stringstream ss(str);
	ss >> this->rank >> this->name >> this->complete >> this->artname>>this->correct>>this->time;
}
