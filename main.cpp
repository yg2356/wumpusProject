#include<iostream>

#include<vector>

#include<cstdlib>

#include<cstring>

#include<cmath>

#include<algorithm>

#include<ctime>

#include<iomanip>

#include<conio.h>

#include<string>

#include<stack>



using namespace std;



#define size 4

#define probability 0.15



string Map[6][6];

bool visited[6][6];

bool visit[6][6];

bool wdie[6][6] = { 0, };

bool pdie[6][6] = { 0, };

bool climb = false;

int shoot = 3;

int North = 0, South = 0, East = 1, West = 0;

stack<pair<int, int>>back;



void glitter(int x, int y);

void wumpus(int x, int y);

void pit(int x, int y);

void stentch(int x, int y);

void breeze(int x, int y);



void board()

{

	for (int i = 0;i < 6;i++)

	{

		for (int j = 0;j < 6;j++)

		{

			if (i == 0 || i == 5 || j == 0 || j == 5)

			{

				Map[i][j] = "#";

			}

			else

				Map[i][j] = "-";

		}

	}

}



void WumpusWorld()

{

	int x;

	int y;

	srand(time(NULL));



	x = 4, y = 1;



	glitter(x, y);

	wumpus(x, y);

	pit(x, y);

}



void glitter(int x, int y)

{

	while ((x == 4) && (y == 1))

	{

		x = (rand() % size) + 1;

		y = (rand() % size) + 1;



		if ((x == 4 && y == 1) || (x == 3 && y == 1) || (x == 4 && y == 2))

		{

			x = 4;

			y = 1;

		}

	}



	if (Map[x][y] == "-")

		Map[x][y] = "g";

	else

	{

		string s = Map[x][y];

		s += "g";

		Map[x][y] = s;

	}

}



void wumpus(int x, int y)

{
	int cnt = 0;
	for (x = 1;x <= size;x++)

	{

		for (y = 1;y <= size;y++)

		{

			if (!((x == 4 && y == 1) || (x == 3 && y == 1) || (x == 4 && y == 2)))

			{
				if (cnt >= 3)
					return;

				if ((rand() % 1000) <= (probability * 1000))

				{

					if (Map[x][y] == "-")

						Map[x][y] = "w";

					else

					{

						string s = Map[x][y];

						s += "w";

						Map[x][y] = s;

					}

					cnt++;

					stentch(x, y);

				}

			}

		}

	}

}



void pit(int x, int y)

{
	int cnt = 0;
	for (x = 1;x <= size;x++)

	{

		for (y = 1;y <= size;y++)

		{

			if (!((x == 4 && y == 1) || (x == 3 && y == 1) || (x == 4 && y == 2)))

			{
				if (cnt >= 3)
					return;

				if ((rand() % 1000) <= (probability * 1000))

				{

					if (Map[x][y] == "-")

						Map[x][y] = "p";

					else

					{

						string s = Map[x][y];

						s += "p";

						Map[x][y] = s;

					}



					breeze(x, y);

				}

			}

		}

	}

}



void travel()

{

	int x = 4;

	int y = 1;



	Map[x][y] = "h";

	visited[x][y] = true;

	visit[x][y] = true;

	back.push(make_pair(x, y));



	//ÃÊ±â»óÅÂ

	cout << "ÇöÀçÀ§Ä¡: (" << x << ", " << y << ")" << endl;

	for (int i = 0;i < 6;i++)

	{

		for (int j = 0;j < 6;j++)

		{

			cout.setf(ios::left);

			cout << setw(6) << Map[i][j] << " ";

		}

		cout << "\n";

	}



	system("pause");





	while (climb == false)

	{



		system("cls");

		if (x > 4) x--;

		if (x < 1) x++;

		if (y > 4) y--;

		if (y < 1) y++;



		if (visit[x][y + 1] == false && East == 1)

		{

			East = 1;

			West = 0;

			North = 0;

			South = 0;



			y++;

			visit[x][y] = true;

			string grab = Map[x][y];



			if (grab.find("g") != grab.npos && grab.find("p") != grab.npos)

			{

				cout << "±ÝÀ» È¹µæÇÏ´Â °ÍÀººÒ°¡´É" << endl;

				exit(0);

			}

			if (grab.find("g") != grab.npos && grab.find("w") == grab.npos && grab.find("p") == grab.npos)

			{

				climb = true;

				cout << "±ÝÀ» È¹µæ" << endl;



			}



			if (Map[x][y] == "#")

			{

				cout << "bump" << endl;

				visited[x][y] = true;

				y--;

				East = 0;

				North = 1;

				South = 1;

				West = 1;

			}



			if (visited[x][y] == true)

			{

				string temp = Map[x][y];



				if (temp.find("v") != temp.npos && temp.find("w") == temp.npos && temp.find("p") == temp.npos)

				{

					//y++;

					replace(temp.begin(), temp.end(), 'v', 'h');

					Map[x][y] = temp;

				}



				if (temp.find("s") != temp.npos)

				{



					if (wdie[x][y + 1] == true)

					{



						cout << "shoot: " << --shoot << endl;

						cout << "scream" << endl;

						string fix = Map[x][y + 1];

						fix.erase(remove(fix.begin(), fix.end(), 'w'), fix.end());

						Map[x][y + 1] = fix;

						wdie[x][y + 1] = false;



					}

					else if (wdie[x][y - 1] == true)

					{

						cout << "shoot: " << --shoot << endl;



						cout << "scream" << endl;

						string fix = Map[x][y - 1];

						fix.erase(remove(fix.begin(), fix.end(), 'w'), fix.end());

						Map[x][y - 1] = fix;

						wdie[x][y - 1] = false;

					}

					else if (wdie[x - 1][y] == true)

					{

						cout << "shoot: " << --shoot << endl;



						cout << "scream" << endl;

						string fix = Map[x - 1][y];

						fix.erase(remove(fix.begin(), fix.end(), 'w'), fix.end());

						Map[x - 1][y] = fix;

						wdie[x - 1][y] = false;

					}

					else if (wdie[x + 1][y] == true)

					{

						cout << "shoot: " << --shoot << endl;



						cout << "scream" << endl;

						string fix = Map[x + 1][y];

						fix.erase(remove(fix.begin(), fix.end(), 'w'), fix.end());

						Map[x + 1][y] = fix;

						wdie[x + 1][y] = false;

					}



				}



				string temp2 = Map[x][y];

				if (temp2.find("b") != temp2.npos)

				{

					//¿À¸¥ÂÊ ¾Æ·¡ ¸ð¼­¸®¿¡ ÀÖÀ» ¶§

					if (pdie[x - 1][y] == true && Map[x + 1][y] == "#" && Map[x][y + 1] == "#")

					{

						visit[x - 1][y] = true;

						West = 1;

						visit[x][y - 1] = false;

					}

					//¿À¸¥ÂÊÀº °¬´Ù¿Ô°í ´ë°¢¼± À§ÂÊ°ú À§°¡ pitÀÏ ¶§

					else if (pdie[x - 1][y] == true && visit[x][y + 1] == true)

					{

						visit[x - 1][y] = true;

						West = 1;

						visit[x][y - 1] = false;

					}

					else if (pdie[x + 1][y] == true && Map[x - 1][y] == "#" && Map[x][y + 1] == "#")

					{

						visit[x + 1][y] = true;

						West = 1;

						visit[x][y - 1] = false;

					}

					//¿À¸¥ÂÊ¿¡ pitÀÌ ÀÖÀ» ¶§

					else if (pdie[x][y + 1] == true)

					{

						visit[x][y + 1] = true;

						East = 0;

						North = 1;

						South = 1;

						West = 1;

						visit[x][y - 1] = false;

					}

				}



				if (visited[x][y + 1] == true && pdie[x][y + 1] == false)

				{

					if (visit[x - 1][y] == false) North = 1;

					if (visit[x + 1][y] == false) South = 1;

				}

			}

			//(4,2)

			else if (visited[x][y] == false)

			{



				visited[x][y] = true;



				if (Map[x][y] == "-")

				{

					Map[x][y] = "h";

				}

				else

				{

					string s = Map[x][y];

					s += "h";

					Map[x][y] = s;

				}



				string F = Map[x][y];

				if (F.find("w") != F.npos && F.find("p") == F.npos)

				{

					cout << "¿úÇÁ½º¸¦ ¸¸³ª¼­ Á×À½: (" << x << ", " << y << ")" << endl;

					wdie[x][y] = true;

					visited[x][y] = true;

					for (int i = 1;i <= size;i++)

					{

						for (int j = 1;j <= size;j++)

						{

							if (visit[i][j] == true)

							{

								string s = Map[i][j];

								replace(s.begin(), s.end(), 'h', 'v');

								Map[i][j] = s;

							}

						}

					}

					memset(visit, 0, sizeof(visit));

					x = 4;

					y = 1;

					string temp = Map[x][y];

					if (temp.find("v") != temp.npos)

					{

						replace(temp.begin(), temp.end(), 'v', 'h');

						Map[x][y] = temp;

					}

					West = 0;

					East = 1;

					North = 1;

					South = 0;

					while (!back.empty()) back.pop();

				}



				string P = Map[x][y];

				if (P.find("p") != P.npos && P.find("w") == P.npos)

				{

					cout << "¿õµ¢ÀÌ¸¦ ¸¸³ª¼­ Á×À½: (" << x << ", " << y << ")" << endl;

					pdie[x][y] = true;

					visited[x][y] = true;

					for (int i = 1;i <= size;i++)

					{

						for (int j = 1;j <= size;j++)

						{

							if (visit[i][j] == true)

							{

								string s = Map[i][j];

								replace(s.begin(), s.end(), 'h', 'v');

								Map[i][j] = s;



							}

						}

					}

					memset(visit, 0, sizeof(visit));

					visit[x][y] = true;

					x = 4;

					y = 1;

					string temp = Map[x][y];

					if (temp.find("v") != temp.npos)

					{

						replace(temp.begin(), temp.end(), 'v', 'h');

						Map[x][y] = temp;

					}

					West = 0;

					East = 1;

					North = 1;

					South = 0;

					while (!back.empty()) back.pop();

				}



				string d = Map[x][y];

				if (d.find("w") != d.npos && d.find("p") != d.npos)

				{

					cout << "¿õµ¢ÀÌ¿Í ¿øÇÁ½º°¡ °°ÀÌ ÀÖ´Â °÷¿¡¼­ Á×À½" << endl;

					wdie[x][y] = true;

					pdie[x][y] = true;

					visited[x][y] = true;

					for (int i = 1;i <= size;i++)

					{

						for (int j = 1;j <= size;j++)

						{

							if (visit[i][j] == true)

							{

								string s = Map[i][j];

								replace(s.begin(), s.end(), 'h', 'v');

								Map[i][j] = s;



							}

						}

					}

					memset(visit, 0, sizeof(visit));

					visit[x][y] = true;

					x = 4;

					y = 1;

					string temp = Map[x][y];

					if (temp.find("v") != temp.npos)

					{

						replace(temp.begin(), temp.end(), 'v', 'h');

						Map[x][y] = temp;

					}

					West = 0;

					East = 1;

					North = 1;

					South = 0;

					while (!back.empty()) back.pop();

				}



				if (visited[x][y + 1] == true && pdie[x][y + 1] == false)

				{

					if (visit[x - 1][y] == false) North = 1;

					if (visit[x + 1][y] == false) South = 1;

				}

			}

		}

		else if (visit[x - 1][y] == false && North == 1)

		{

			East = 0;

			West = 0;

			North = 1;

			South = 0;



			x--;

			visit[x][y] = true;

			string grab = Map[x][y];

			if (grab.find("g") != grab.npos && grab.find("p") != grab.npos)

			{

				cout << "±ÝÀ» È¹µæÇÏ´Â °ÍÀººÒ°¡´É" << endl;

				exit(0);

			}

			if (grab.find("g") != grab.npos && grab.find("w") == grab.npos && grab.find("p") == grab.npos)

			{

				climb = true;

				cout << "±ÝÀ» È¹µæ" << endl;

			}



			if (Map[x][y] == "#")

			{

				cout << "bump" << endl;

				visited[x][y] = true;

				visit[x][y] = true;

				x++;

				North = 0;

				East = 1;

				South = 1;

				West = 1;

			}

			if (visited[x][y] == true)

			{

				string temp = Map[x][y];



				if (temp.find("v") != temp.npos && temp.find("w") == temp.npos && temp.find("p") == temp.npos)

				{

					//x--;

					replace(temp.begin(), temp.end(), 'v', 'h');

					Map[x][y] = temp;

				}



				if (temp.find("s") != temp.npos)

				{



					if (wdie[x][y + 1] == true)

					{

						cout << "shoot: " << --shoot << endl;



						cout << "scream" << endl;

						string fix = Map[x][y + 1];

						fix.erase(remove(fix.begin(), fix.end(), 'w'), fix.end());

						Map[x][y + 1] = fix;

						wdie[x][y + 1] = false;



					}

					else if (wdie[x][y - 1] == true)

					{

						cout << "shoot: " << --shoot << endl;



						cout << "scream" << endl;

						string fix = Map[x][y - 1];

						fix.erase(remove(fix.begin(), fix.end(), 'w'), fix.end());

						Map[x][y - 1] = fix;

						wdie[x][y - 1] = false;

					}

					else if (wdie[x - 1][y] == true)

					{

						cout << "shoot: " << --shoot << endl;



						cout << "scream" << endl;

						string fix = Map[x - 1][y];

						fix.erase(remove(fix.begin(), fix.end(), 'w'), fix.end());

						Map[x - 1][y] = fix;

						wdie[x - 1][y] = false;



					}

					else if (wdie[x + 1][y] == true)

					{

						cout << "shoot: " << --shoot << endl;



						cout << "scream" << endl;

						string fix = Map[x + 1][y];

						fix.erase(remove(fix.begin(), fix.end(), 'w'), fix.end());

						Map[x + 1][y] = fix;

						wdie[x + 1][y] = false;

					}

				}



				string temp2 = Map[x][y];

				if (temp2.find("b") != temp2.npos)

				{



					if (pdie[x - 1][y] == true && Map[x][y + 1] == "#")

					{

						visit[x - 1][y] = true;



						if (!visit[x][y - 1])

						{

							West = 1;

						}

						else

						{

							South = 1;

							visit[x + 1][y] = false;

						}

					}

					else if (pdie[x - 1][y] == true && pdie[x][y + 1] == true)

					{

						visit[x - 1][y] = true;

						visit[x][y + 1] = true;

						if ((visited[x][y - 1] == true && Map[x][y] != "#") || visit[x][y - 1] == false)

						{

							West = 1;

							visit[x][y - 1] = false;

						}

						else

						{

							South = 1;

							visit[x + 1][y] = false;

						}



					}

					else if (pdie[x - 1][y] == true && pdie[x][y - 1] == true)

					{

						visit[x - 1][y] = true;

						visit[x][y - 1] = true;

						if (Map[x][y + 1] == "#")

						{

							South = 1;

							visit[x + 1][y] = false;

						}

						else

						{

							East = 1;

							visit[x][y + 1] = false;

						}

					}

					else if (pdie[x][y - 1] == true && Map[x][y + 1] == "#" && Map[x - 1][y] == "#")

					{

						South = 1;

						visit[x + 1][y] = false;

					}

					else if (pdie[x - 1][y] == true)

					{

						visit[x - 1][y] = true;

						East = 1;

						West = 1;

					}



				}



				if (visited[x - 1][y] == true && pdie[x - 1][y] == false)

				{

					if (visit[x][y + 1] == false) East = 1;

					if (visit[x][y - 1] == false) West = 1;

				}

			}

			//(4,2)

			else if (visited[x][y] == false)

			{

				//cout << "GoStraight" << endl;

				visited[x][y] = true;



				if (Map[x][y] == "-")

				{

					Map[x][y] = "h";

				}

				else

				{

					string s = Map[x][y];

					s += "h";

					Map[x][y] = s;

				}





				string F = Map[x][y];

				if (F.find("w") != F.npos && F.find("p") == F.npos)

				{

					wdie[x][y] = true;

					visited[x][y] = true;

					cout << "¿úÇÁ½º¸¦ ¸¸³ª¼­ Á×À½: (" << x << ", " << y << ")" << endl;

					for (int i = 1;i <= size;i++)

					{

						for (int j = 1;j <= size;j++)

						{

							if (visit[i][j] == true)

							{

								string s = Map[i][j];

								replace(s.begin(), s.end(), 'h', 'v');

								Map[i][j] = s;



							}

						}

					}

					memset(visit, 0, sizeof(visit));

					x = 4;

					y = 1;

					string temp = Map[x][y];

					if (temp.find("v") != temp.npos)

					{

						replace(temp.begin(), temp.end(), 'v', 'h');

						Map[x][y] = temp;

					}

					West = 0;

					East = 1;

					North = 1;

					South = 0;

					while (!back.empty()) back.pop();

				}



				string P = Map[x][y];

				if (P.find("p") != P.npos && P.find("w") == P.npos)

				{

					pdie[x][y] = true;

					visited[x][y] = true;

					cout << "¿õµ¢ÀÌ¸¦ ¸¸³ª¼­ Á×À½: (" << x << ", " << y << ")" << endl;

					for (int i = 1;i <= size;i++)

					{

						for (int j = 1;j <= size;j++)

						{

							if (visit[i][j] == true)

							{

								string s = Map[i][j];

								replace(s.begin(), s.end(), 'h', 'v');

								Map[i][j] = s;



							}

						}

					}

					memset(visit, 0, sizeof(visit));

					visit[x][y] = true;

					x = 4;

					y = 1;

					string temp = Map[x][y];

					if (temp.find("v") != temp.npos)

					{

						replace(temp.begin(), temp.end(), 'v', 'h');

						Map[x][y] = temp;

					}

					West = 0;

					East = 1;

					North = 1;

					South = 0;

					while (!back.empty()) back.pop();

				}



				string d = Map[x][y];

				if (d.find("w") != d.npos && d.find("p") != d.npos)

				{

					cout << "¿õµ¢ÀÌ¿Í ¿øÇÁ½º°¡ °°ÀÌ ÀÖ´Â °÷¿¡¼­ Á×À½" << endl;

					wdie[x][y] = true;

					pdie[x][y] = true;

					visited[x][y] = true;

					for (int i = 1;i <= size;i++)

					{

						for (int j = 1;j <= size;j++)

						{

							if (visit[i][j] == true)

							{

								string s = Map[i][j];

								replace(s.begin(), s.end(), 'h', 'v');

								Map[i][j] = s;



							}

						}

					}

					memset(visit, 0, sizeof(visit));

					visit[x][y] = true;

					x = 4;

					y = 1;

					string temp = Map[x][y];

					if (temp.find("v") != temp.npos)

					{

						replace(temp.begin(), temp.end(), 'v', 'h');

						Map[x][y] = temp;

					}

					West = 0;

					East = 1;

					North = 1;

					South = 0;

					while (!back.empty()) back.pop();

				}



				if (visited[x - 1][y] == true && pdie[x - 1][y] == false)

				{

					if (visit[x][y + 1] == false) East = 1;

					if (visit[x][y - 1] == false) West = 1;

				}



			}

		}

		else if (visit[x][y - 1] == false && West == 1)

		{



			East = 0;

			West = 1;

			North = 0;

			South = 0;

			y--;

			visit[x][y] = true;



			string grab = Map[x][y];

			if (grab.find("g") != grab.npos && grab.find("p") != grab.npos)

			{

				cout << "±ÝÀ» È¹µæÇÏ´Â °ÍÀººÒ°¡´É" << endl;

				exit(0);

			}

			if (grab.find("g") != grab.npos && grab.find("w") == grab.npos && grab.find("p") == grab.npos)

			{

				climb = true;

				cout << "±ÝÀ» È¹µæ" << endl;

			}



			if (Map[x][y] == "#")

			{

				cout << "bump" << endl;

				visited[x][y] = true;

				visit[x][y] = true;

				y++;

				West = 0;

				East = 1;

				North = 1;

				South = 1;

			}

			if (visited[x][y] == true)

			{

				string temp = Map[x][y];



				if (temp.find("v") != temp.npos && temp.find("w") == temp.npos && temp.find("p") == temp.npos)

				{

					//y--;

					replace(temp.begin(), temp.end(), 'v', 'h');

					Map[x][y] = temp;

				}



				if (temp.find("s") != temp.npos)

				{



					if (wdie[x][y + 1] == true)

					{

						cout << "shoot: " << --shoot << endl;



						cout << "scream" << endl;

						string fix = Map[x][y + 1];

						fix.erase(remove(fix.begin(), fix.end(), 'w'), fix.end());

						Map[x][y + 1] = fix;

						wdie[x][y + 1] = false;

					}

					else if (wdie[x][y - 1] == true)

					{

						cout << "shoot: " << --shoot << endl;



						cout << "scream" << endl;

						string fix = Map[x][y - 1];

						fix.erase(remove(fix.begin(), fix.end(), 'w'), fix.end());

						Map[x][y - 1] = fix;

						wdie[x][y - 1] = false;

					}

					else if (wdie[x - 1][y] == true)

					{

						cout << "shoot: " << --shoot << endl;



						cout << "scream" << endl;

						string fix = Map[x - 1][y];

						fix.erase(remove(fix.begin(), fix.end(), 'w'), fix.end());

						Map[x - 1][y] = fix;

						wdie[x - 1][y] = false;

					}

					else if (wdie[x + 1][y] == true)

					{

						cout << "shoot: " << --shoot << endl;



						cout << "scream" << endl;

						string fix = Map[x + 1][y];

						fix.erase(remove(fix.begin(), fix.end(), 'w'), fix.end());

						Map[x + 1][y] = fix;

						wdie[x + 1][y] = false;

					}

				}



				string temp2 = Map[x][y];

				if (temp2.find("b") != temp2.npos)

				{

					//¿À¸¥ÂÊ ¸ÇÀ§¿¡¼­ ¿ÞÂÊ¿¡ pitÀÌ ÀÖÀ» ¶§

					if (pdie[x][y - 1] == true && Map[x - 1][y] == "#" && Map[x][y + 1] == "#")

					{

						visit[x][y - 1] = true;

						visit[x + 1][y] = false;

						South = 1;

					}

					else if (pdie[x][y - 1] == true && Map[x - 1][y] == "#")

					{

						visit[x][y - 1] = true;

						South = 1;

					}

					else if (pdie[x - 1][y] == true && Map[x][y - 1] == "#")

					{

						visit[x][y - 1] = true;

						East = 1;

						visit[x][y + 1] = false;

					}

					else if (pdie[x - 1][y] == true && visit[x][y + 1] == true)

					{

						West = 1;

						visit[x][y - 1] = false;

					}

					else if (pdie[x + 1][y] == true && Map[x][y - 1] == "#" && Map[x - 1][y] == "#")

					{

						visit[x + 1][y] = true;

						East = 1;

						visit[x][y + 1] = false;

					}

					else if (pdie[x][y - 1] == true)

					{

						visit[x][y - 1] = true;

						East = 1;

						South = 1;

						North = 1;

					}

				}



				if (visited[x][y - 1] == true && pdie[x][y - 1] == false)

				{

					if (visit[x - 1][y] == false) North = 1;

					if (visit[x + 1][y] == false) South = 1;

				}

			}

			//(4,2)

			else if (visited[x][y] == false)

			{

				//cout << "GoStraight" << endl;

				visited[x][y] = true;



				if (Map[x][y] == "-")

				{

					Map[x][y] = "h";

				}

				else

				{

					string s = Map[x][y];

					s += "h";

					Map[x][y] = s;

				}



				string F = Map[x][y];

				if (F.find("w") != F.npos && F.find("p") == F.npos)

				{

					wdie[x][y] = true;

					cout << "¿úÇÁ½º¸¦ ¸¸³ª¼­ Á×À½: (" << x << ", " << y << ")" << endl;

					for (int i = 1;i <= size;i++)

					{

						for (int j = 1;j <= size;j++)

						{

							if (visit[i][j] == true)

							{

								string s = Map[i][j];

								replace(s.begin(), s.end(), 'h', 'v');

								Map[i][j] = s;



							}

						}

					}

					memset(visit, 0, sizeof(visit));

					x = 4;

					y = 1;

					string temp = Map[x][y];

					if (temp.find("v") != temp.npos)

					{

						replace(temp.begin(), temp.end(), 'v', 'h');

						Map[x][y] = temp;

					}

					West = 0;

					East = 1;

					North = 1;

					South = 0;

					while (!back.empty()) back.pop();

				}



				string P = Map[x][y];

				if (P.find("p") != P.npos && P.find("w") == P.npos)

				{

					pdie[x][y] = true;

					cout << "¿õµ¢ÀÌ¸¦ ¸¸³ª¼­ Á×À½: (" << x << ", " << y << ")" << endl;

					for (int i = 1;i <= size;i++)

					{

						for (int j = 1;j <= size;j++)

						{

							if (visit[i][j] == true)

							{

								//Àß µÊcout << i << " " << j << endl;

								string s = Map[i][j];

								replace(s.begin(), s.end(), 'h', 'v');

								Map[i][j] = s;



							}

						}

					}

					memset(visit, 0, sizeof(visit));

					visit[x][y] = true;

					x = 4;

					y = 1;

					string temp = Map[x][y];

					if (temp.find("v") != temp.npos)

					{

						replace(temp.begin(), temp.end(), 'v', 'h');

						Map[x][y] = temp;

					}

					West = 0;

					East = 1;

					North = 1;

					South = 0;

					while (!back.empty()) back.pop();

				}



				string d = Map[x][y];

				if (d.find("w") != d.npos && d.find("p") != d.npos)

				{

					cout << "¿õµ¢ÀÌ¿Í ¿øÇÁ½º°¡ °°ÀÌ ÀÖ´Â °÷¿¡¼­ Á×À½" << endl;

					wdie[x][y] = true;

					pdie[x][y] = true;

					visited[x][y] = true;

					for (int i = 1;i <= size;i++)

					{

						for (int j = 1;j <= size;j++)

						{

							if (visit[i][j] == true)

							{

								string s = Map[i][j];

								replace(s.begin(), s.end(), 'h', 'v');

								Map[i][j] = s;



							}

						}

					}

					memset(visit, 0, sizeof(visit));

					visit[x][y] = true;

					x = 4;

					y = 1;

					string temp = Map[x][y];

					if (temp.find("v") != temp.npos)

					{

						replace(temp.begin(), temp.end(), 'v', 'h');

						Map[x][y] = temp;

					}

					West = 0;

					East = 1;

					North = 1;

					South = 0;

					while (!back.empty()) back.pop();

				}



				if (visited[x][y - 1] == true && pdie[x][y - 1] == false)

				{

					if (visit[x - 1][y] == false) North = 1;

					if (visit[x + 1][y] == false) South = 1;

				}



			}

		}

		else if (visit[x + 1][y] == false && South == 1)

		{



			East = 0;

			West = 0;

			North = 0;

			South = 1;

			x++;

			visit[x][y] = true;

			string grab = Map[x][y];

			if (grab.find("g") != grab.npos && grab.find("p") != grab.npos)

			{

				cout << "±ÝÀ» È¹µæÇÏ´Â °ÍÀººÒ°¡´É" << endl;

				exit(0);

			}

			if (grab.find("g") != grab.npos && grab.find("w") == grab.npos && grab.find("p") == grab.npos)

			{

				climb = true;

				cout << "±ÝÀ» È¹µæ" << endl;

			}



			if (Map[x][y] == "#")

			{

				cout << "bump" << endl;

				visited[x][y] = true;

				visit[x][y] = true;

				x--;

				West = 0;

				East = 1;

				North = 1;

				South = 1;

			}

			if (visited[x][y] == true)

			{

				string temp = Map[x][y];



				if (temp.find("v") != temp.npos && temp.find("w") == temp.npos && temp.find("p") == temp.npos)

				{

					//x++;

					replace(temp.begin(), temp.end(), 'v', 'h');

					Map[x][y] = temp;

				}



				if (temp.find("s") != temp.npos)

				{



					if (wdie[x][y + 1] == true)

					{

						cout << "shoot: " << --shoot << endl;



						cout << "scream" << endl;

						string fix = Map[x][y + 1];

						fix.erase(remove(fix.begin(), fix.end(), 'w'), fix.end());

						Map[x][y + 1] = fix;

						wdie[x][y + 1] = false;



					}

					else if (wdie[x][y - 1] == true)

					{

						cout << "shoot: " << --shoot << endl;



						cout << "scream" << endl;

						string fix = Map[x][y - 1];

						fix.erase(remove(fix.begin(), fix.end(), 'w'), fix.end());

						Map[x][y - 1] = fix;

						wdie[x][y - 1] = false;

					}

					else if (wdie[x - 1][y] == true)

					{

						cout << "shoot: " << --shoot << endl;



						cout << "scream" << endl;

						string fix = Map[x - 1][y];

						fix.erase(remove(fix.begin(), fix.end(), 'w'), fix.end());

						Map[x - 1][y] = fix;

						wdie[x - 1][y] = false;

					}

					else if (wdie[x + 1][y] == true)

					{

						cout << "shoot: " << --shoot << endl;



						cout << "scream" << endl;

						string fix = Map[x + 1][y];

						fix.erase(remove(fix.begin(), fix.end(), 'w'), fix.end());

						Map[x + 1][y] = fix;

						wdie[x + 1][y] = false;

					}

				}



				string temp2 = Map[x][y];

				if (temp2.find("b") != temp2.npos)

				{

					if (pdie[x + 1][y] == true && Map[x][y - 1] == "#" && Map[x - 1][y] == "#")

					{

						visit[x + 1][y] = true;

						East = 1;

						visit[x][y + 1] = false;

					}

					else if (pdie[x + 1][y] == true && Map[x][y - 1] == "#")

					{

						visit[x + 1][y] = true;

						East = 1;

						visit[x][y + 1] = false;

					}

					else if (pdie[x + 1][y] == true && Map[x][y + 1] == "#" &&visit[x-1][y]==true)

					{

						visit[x + 1][y] = true;

						West = 1;

						visit[x][y - 1] = false;

					}

					else if (pdie[x][y + 1] == true && Map[x][y - 1] == "#" && visit[x + 1][y] == true)

					{

						visit[x][y + 1] = true;

						North = 1;

						visit[x - 1][y] = false;

					}

				}



				if (visited[x + 1][y] == true && pdie[x + 1][y] == false)

				{

					if (visit[x][y + 1] == false) East = 1;

					if (visit[x][y - 1] == false) West = 1;

				}



			}

			//(4,2)

			else if (visited[x][y] == false)

			{

				//cout << "GoStraight" << endl;

				visited[x][y] = true;



				if (Map[x][y] == "-")

				{

					Map[x][y] = "h";

				}

				else

				{

					string s = Map[x][y];

					s += "h";

					Map[x][y] = s;

				}





				string F = Map[x][y];

				if (F.find("w") != F.npos && F.find("p") == F.npos)

				{

					wdie[x][y] = true;

					visited[x][y] = true;

					cout << "¿úÇÁ½º¸¦ ¸¸³ª¼­ Á×À½: (" << x << ", " << y << ")" << endl;

					for (int i = 1;i <= size;i++)

					{

						for (int j = 1;j <= size;j++)

						{

							if (visit[i][j] == true)

							{

								string s = Map[i][j];

								replace(s.begin(), s.end(), 'h', 'v');

								Map[i][j] = s;



							}

						}

					}

					memset(visit, 0, sizeof(visit));

					x = 4;

					y = 1;

					string temp = Map[x][y];

					if (temp.find("v") != temp.npos)

					{

						replace(temp.begin(), temp.end(), 'v', 'h');

						Map[x][y] = temp;

					}

					West = 0;

					East = 1;

					North = 1;

					South = 0;

					while (!back.empty()) back.pop();

				}



				string P = Map[x][y];

				if (P.find("p") != P.npos && P.find("w") == P.npos)

				{

					pdie[x][y] = true;

					visited[x][y] = true;

					cout << "¿õµ¢ÀÌ¸¦ ¸¸³ª¼­ Á×À½: (" << x << ", " << y << ")" << endl;

					for (int i = 1;i <= size;i++)

					{

						for (int j = 1;j <= size;j++)

						{

							if (visit[i][j] == true)

							{

								string s = Map[i][j];

								replace(s.begin(), s.end(), 'h', 'v');

								Map[i][j] = s;



							}

						}

					}

					memset(visit, 0, sizeof(visit));

					visit[x][y] = true;

					x = 4;

					y = 1;

					string temp = Map[x][y];

					if (temp.find("v") != temp.npos)

					{

						replace(temp.begin(), temp.end(), 'v', 'h');

						Map[x][y] = temp;

					}



					West = 0;

					East = 1;

					North = 1;

					South = 0;

					while (!back.empty()) back.pop();

				}



				string d = Map[x][y];

				if (d.find("w") != d.npos && d.find("p") != d.npos)

				{

					cout << "¿õµ¢ÀÌ¿Í ¿øÇÁ½º°¡ °°ÀÌ ÀÖ´Â °÷¿¡¼­ Á×À½" << endl;

					wdie[x][y] = true;

					pdie[x][y] = true;

					visited[x][y] = true;

					for (int i = 1;i <= size;i++)

					{

						for (int j = 1;j <= size;j++)

						{

							if (visit[i][j] == true)

							{

								string s = Map[i][j];

								replace(s.begin(), s.end(), 'h', 'v');

								Map[i][j] = s;



							}

						}

					}

					memset(visit, 0, sizeof(visit));

					visit[x][y] = true;

					x = 4;

					y = 1;

					string temp = Map[x][y];

					if (temp.find("v") != temp.npos)

					{

						replace(temp.begin(), temp.end(), 'v', 'h');

						Map[x][y] = temp;

					}

					West = 0;

					East = 1;

					North = 1;

					South = 0;

					while (!back.empty()) back.pop();

				}



				if (visited[x + 1][y] == true && pdie[x + 1][y] == false)

				{

					if (visit[x][y + 1] == false) East = 1;

					if (visit[x][y - 1] == false) West = 1;

				}

			}

		}

		cout << "ÇöÀçÀ§Ä¡: (" << x << ", " << y << ")" << endl;

		string comeback = Map[x][y];



		if (comeback.find("h") != comeback.npos)

		{

			back.push(make_pair(x, y));

		}



		for (int i = 0;i < 6;i++)

		{

			for (int j = 0;j < 6;j++)

			{

				cout.setf(ios::left);

				cout << setw(6) << Map[i][j] << " ";

			}

			cout << "\n";

		}



		system("pause");

	}

}



void stentch(int x, int y)

{



	if (Map[x - 1][y] == "-")

	{

		Map[x - 1][y] = "s";

	}

	else if (Map[x - 1][y] != "#")

	{

		string s = Map[x - 1][y];

		if (s.find("s") == s.npos)

		{

			s += "s";

			Map[x - 1][y] = s;

		}

	}



	if (Map[x + 1][y] == "-")

	{

		Map[x + 1][y] = "s";

	}

	else if (Map[x + 1][y] != "#")

	{

		string s = Map[x + 1][y];

		if (s.find("s") == s.npos)

		{

			s += "s";

			Map[x + 1][y] = s;

		}

	}



	if (Map[x][y - 1] == "-")

	{

		Map[x][y - 1] = "s";

	}

	else if (Map[x][y - 1] != "#")

	{

		string s = Map[x][y - 1];

		if (s.find("s") == s.npos)

		{

			s += "s";

			Map[x][y - 1] = s;

		}

	}



	if (Map[x][y + 1] == "-")

	{

		Map[x][y + 1] = "s";

	}

	else if (Map[x][y + 1] != "#")

	{

		string s = Map[x][y + 1];

		if (s.find("s") == s.npos)

		{

			s += "s";

			Map[x][y + 1] = s;

		}

	}

}



void breeze(int x, int y)

{

	if (Map[x - 1][y] == "-")

	{

		Map[x - 1][y] = "b";

	}

	else if (Map[x - 1][y] != "#")

	{

		string s = Map[x - 1][y];

		if (s.find("b") == s.npos)

		{

			s += "b";

			Map[x - 1][y] = s;

		}

	}



	if (Map[x + 1][y] == "-")

	{

		Map[x + 1][y] = "b";

	}

	else if (Map[x + 1][y] != "#")

	{

		string s = Map[x + 1][y];

		if (s.find("b") == s.npos)

		{

			s += "b";

			Map[x + 1][y] = s;

		}

	}



	if (Map[x][y - 1] == "-")

	{

		Map[x][y - 1] = "b";

	}

	else if (Map[x][y - 1] != "#")

	{

		string s = Map[x][y - 1];

		if (s.find("b") == s.npos)

		{

			s += "b";

			Map[x][y - 1] = s;

		}

	}



	if (Map[x][y + 1] == "-")

	{

		Map[x][y + 1] = "b";

	}

	else if (Map[x][y + 1] != "#")

	{

		string s = Map[x][y + 1];

		if (s.find("b") == s.npos)

		{

			s += "b";

			Map[x][y + 1] = s;

		}

	}

}



int main()

{

	board();

	WumpusWorld();

	travel();





	int x = 0;

	int y = 0;



	while (!back.empty())

	{

		system("cls");



		x = back.top().first;

		y = back.top().second;

		cout << "ÇöÀçÀ§Ä¡: (" << x << ", " << y << ")" << endl;

		back.pop();



		string temp = Map[x][y];



		if (temp.find("h") != temp.npos && Map[x][y] != "#")

		{

			replace(temp.begin(), temp.end(), 'h', 'B');

			Map[x][y] = temp;

		}

		for (int i = 0;i < 6;i++)

		{

			for (int j = 0;j < 6;j++)

			{

				cout.setf(ios::left);

				cout << setw(6) << Map[i][j] << " ";

			}

			cout << "\n";

		}



		system("pause");

	}



	cout << "Å½»ö¿Ï·á" << endl;





	return 0;

}