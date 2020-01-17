#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

//Ïàðñÿòñÿ int
std::vector<std::vector<int>> parse_csv(std::string csv_file)
{
	std::ifstream fin(csv_file);
	if (fin.fail())
		std::cout << "NO FILE!";

	std::vector<std::vector<int>> parsed;
	std::pair<std::vector<std::vector<int>>, int> vec_n_score;

	while (!fin.eof()) 
	{
		std::string line;
		std::getline(fin, line);

		// Óáèðàåì ïðîáåëû

		for (int i = 0; i < line.size(); ++i)
		{
			if (line[i] == ' ')
			{
				line = line.substr(0, i) + line.substr(i + 1);
				i--;
			}
		}

		unsigned last_start = 0;
		std::vector<int> line_parsed;

		for (int i = 0; i < line.size(); ++i)
		{
			if (line[i] == ',')
			{
				std::string substr = line.substr(last_start, i - last_start);
				last_start = i + 1;
				line_parsed.push_back(std::stoi(substr));
			}
		}

		parsed.push_back(line_parsed);
	}

	return parsed;
}
