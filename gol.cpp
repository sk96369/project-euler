#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iterator>
#include <istream>

class Cell
{
	bool wall;
	char c;
	bool alive;
	//Is the cell's state marked to be changed?
	bool willdie;
	bool willbeborn;

	public:
	bool isWall() const
	{
		return wall;
	}
	void kill()
	{
		willdie = true;
	}
	void unkill()
	{
		willbeborn = true;
	}
	void commitchange()
	{
		if(willdie)
		{
			alive = false;
			c = ' ';
			willdie = false;
		}
		if(willbeborn)
		{
			alive = true;
			c = 'O';
			willbeborn = false;
		}
	}

	char getCell()
	{
		return c;
	}

	bool isAlive() const
	{
		return alive;
	}

	Cell() : willdie(false), willbeborn(false), wall(true), c('#'), alive(false)
	{
	}

	Cell(char ld) : willdie(false), willbeborn(false), wall(false)
	{
		if(ld == 'o')
		{
			c = 'O';
			alive = true;
		}
		else
		{
			c = ' ';
			alive = false;
		}
	}

	Cell(bool ld) : alive(ld), willdie(false), willbeborn(false), wall(false)
	{
		if(ld == true)
			c = 'O';
		else
			c = ' ';
	}
};

class World
{
	std::vector<std::vector<Cell*>> grid;
	int s;

	public:
	int getSize() const
	{
		return s;
	}
	void showworld();
	void advance();
	int check(int i, int j);

	World(std::fstream &file)
	{
		std::string str;
		getline(file, str);
		s = str.size() + 1;
		std::vector<Cell*> front;
		std::vector<Cell*> back;
		for(int i = 0;i < s;i++)
		{
			front.push_back(new Cell);
			back.push_back(new Cell);
		}
		grid.push_back(back);
		do	
		{
			std::vector<char>charline (str.begin(),str.end());
			std::vector<Cell*> line;
			line.push_back(new Cell());
			for(auto ptr = str.begin();ptr != str.end();ptr++)
			{
				line.push_back(new Cell(*ptr));
			}
			//Pop the useless character added to the end
			line.pop_back();
			line.push_back(new Cell());
			grid.push_back(line);
		}
		while(getline(file, str));
		grid.push_back(front);
		std::cout << grid.size() << grid[0].size() << std::endl;
	}


	World(std::vector<std::vector<Cell*>> &g)
	{
		Cell* wall = new Cell();
		std::vector<Cell*> frontline;
		std::vector<Cell*> backline;
		for(int i = 0;i <= g.size() + 1;i++)
		{
			frontline.push_back(wall);
			backline.push_back(wall);
		}

		g.insert(g.begin(), frontline);
		g.push_back(backline);
		for(int i = 1;i<g.size()-1;i++)
		{
			g[i].insert(g[i].begin(), wall);
			g[i].push_back(wall);
		}

		grid = g;
		s = g.size();
	}

	World(int size, int seed) : s(size+2)
	{
		srand(seed);
		Cell* wall = new Cell();
		std::vector<Cell*> frontwall;
		std::vector<Cell*> backwall;
		for(int i = 0;i<=size;i++)
		{
			frontwall.push_back(wall);
			backwall.push_back(wall);
		}
		for(int i = 0;i < size;i++)
		{
			std::vector<Cell*> newline;
			newline.push_back(wall);
			for(int j = 0;j < size;j++)
			{
				if(rand() % 2 == 0)
					newline.push_back(new Cell(false));
				else
					newline.push_back(new Cell(true));
			}
			newline.push_back(wall);
			grid.push_back(newline);
		}
	}
};

void World::showworld()
{
	for(int i = 0;i<s;i++)
	{
		for(int j = 0;j<s;j++)
		{
			std::cout << grid[i][j]->getCell();
		}
		std::cout << std::endl;
	}
}
//Returns the number of alive cells in the neighborhood
int World::check(int i, int j)
{
	int count = 0;
	if(grid[i-1][j]->isAlive())
	{
		{
			count++;
		}
	}
	if(grid[i][j-1]->isAlive())
	{
		{
			count++;
		}
	}
	if(grid[i-1][j-1]->isAlive())
	{
		{
			count++;
		}
	}
	if(grid[i+1][j-1]->isAlive())
	{
		{
			count++;
		}
	}
	if(grid[i-1][j+1]->isAlive())
	{
		{
			count++;
		}
	}
	if(grid[i+1][j]->isAlive())
	{
		count++;
	}
	if(grid[i][j+1]->isAlive())
		{
			count++;
		}
	if(grid[i+1][j+1]->isAlive())
	{
		count++;
	}
	
	return count;
}

void World::advance()
{

	for(int i = 1;i<s-1;i++)
	{
		for(int j = 1;j<s-1;j++)
		{
			int alive = check(i, j);
			if(alive < 2)
				grid[i][j]->kill();
			if(alive > 3)
				grid[i][j]->kill();
			if(alive == 3)
				grid[i][j]->unkill();
		}
	}
	for(int i = 0;i<s;i++)
	{
		for(int j = 0;j<s;j++)
		{
			grid[i][j]->commitchange();
		}
	}
}


int main(int argc, char *argv[])
{
	World* world;
	if(argc == 3)
	{
		world = new World(atoi(argv[1]), atoi(argv[2]));
	}
	if(argc == 2)
	{
		std::fstream file;
		file.open(argv[1]);
		/*std::vector<std::vector<Cell*>> grid;
		std::string s;
		while(getline(file, s))
		{
			std::vector<char> charline (s.begin(),s.end());
			std::vector<Cell*> line;
			for(auto ptr = s.begin();ptr != s.end();ptr++)
			{
				line.push_back(new Cell(*ptr));
			}
			
			grid.push_back(line);
		}*/
		
		world = new World(file);
		file.close();
		
	}
	std::string input = "";

	do
	{
		std::cout << "TEST1\n";
		world->showworld();
		std::cout << "TEST2\n";
		world->advance();
		std::cout << "Press enter to advance, type in 'q' and press enter to exit.\n";
		std::getline(std::cin, input);
	}
	while(input != "q");


	return 0;
}
