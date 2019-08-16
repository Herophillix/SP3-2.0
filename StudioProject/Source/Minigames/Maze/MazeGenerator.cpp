#include "MazeGenerator.h"

MazeGenerator::MazeGenerator()
{

}

MazeGenerator::~MazeGenerator()
{

}

void MazeGenerator::SetUp(string FileDirectory)
{
	fstream File;
	File.open(FileDirectory);
	if (!File.is_open())
	{
		cout << "Error, file " << FileDirectory << " not found." << endl;
		return;
	}
	File.seekg(0, ios::beg);

	//Calculating aspect ratio
	m_worldHeight = 200.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	cout << FileDirectory << endl;
	while (!File.eof())
	{
		string temp;
		string info[9];
		int index = 0;
		getline(File, temp);
		for (int i = 0; i < static_cast<int>(temp.size()); ++i)
		{
			if (temp[i] != ' ')
			{
				info[index] += temp[i];
			}
			else
			{
				if (index == 8)
				{
					break;
				}
				else
				{
					++index;
				}
			}
		}
		MazeObject* maze = new MazeObject;
		switch (info[0][0])
		{
		case 'P':
			maze->type = PhysicsObject::GO_PILLAR;
			cout << "PILLAR, ";
			break;
		case 'W':
			maze->type = PhysicsObject::GO_WALL;
			cout << "WALL,   ";
			break;
		default:
			maze->type = PhysicsObject::GO_NONE;
			cout << "NONE,   ";
			break;
		}
		maze->angle_normal = Math::DegreeToRadian(stof(info[1]));
		maze->normal.Set(cosf(maze->angle_normal), sinf(maze->angle_normal), 0);

		maze->offset.Set(stof(info[2]), stof(info[3]), stof(info[4]));
		maze->normal_position = maze->offset.Normalized();
		maze->angle_offset = atan2(maze->normal_position.y, maze->normal_position.x);

		maze->scale.Set(stof(info[5]), stof(info[6]), stof(info[7]));

		maze->level = stoi(info[8]);

		maze->pos.x = m_worldWidth * 0.5f;
		maze->pos.y = m_worldHeight * 0.5f;
		maze->pos += maze->offset.Length() * maze->normal_position;

		maze->active = true;
		cout << "P: " << maze->pos << ", S: " << maze->scale << ", A: " << Math::RadianToDegree(maze->angle_normal) << ", O: " << Math::RadianToDegree(maze->angle_offset) << endl;
		MazeList.push_back(maze);
	}
}

void MazeGenerator::Update(double dt)
{
	//Calculating aspect ratio
	m_worldHeight = 200.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	for (int i = 0; i < (int)MazeList.size(); ++i)
	{
		float tempvel = Math::DegreeToRadian(30);
		MazeObject* go = MazeList[i];
		go->angle_normal_prev = go->angle_normal;
		if ((go->level == MazeObject::G_ZERO || go->level == MazeObject::G_TWO))
		{
			if (Application::IsKeyPressed('X'))
			{
				go->angle_normal += tempvel * static_cast<float>(dt);
				go->angle_offset += tempvel * static_cast<float>(dt);
			}
			else if (Application::IsKeyPressed(VK_OEM_PERIOD))
			{
				go->angle_normal -= tempvel * static_cast<float>(dt);
				go->angle_offset -= tempvel * static_cast<float>(dt);
			}
			else
			{
				go->angle_normal += tempvel / 3.f * static_cast<float>(dt);
				go->angle_offset += tempvel / 3.f * static_cast<float>(dt);
			}
		}
		else
		{
			if (Application::IsKeyPressed('C'))
			{
				go->angle_normal += tempvel * static_cast<float>(dt);
				go->angle_offset += tempvel * static_cast<float>(dt);
			}
			else if (Application::IsKeyPressed(VK_OEM_COMMA))
			{
				go->angle_normal -= tempvel * static_cast<float>(dt);
				go->angle_offset -= tempvel * static_cast<float>(dt);
			}
			else
			{
				go->angle_normal -= tempvel / 3.f * static_cast<float>(dt);
				go->angle_offset -= tempvel / 3.f * static_cast<float>(dt);
			}
		}
		go->normal = Vector3(cosf(go->angle_normal), sinf(go->angle_normal), 0);
		go->normal_position = Vector3(cosf(go->angle_offset), sinf(go->angle_offset), 0);
		go->pos.x = m_worldWidth * 0.5f;
		go->pos.y = m_worldHeight * 0.5f;
		go->pos += go->offset.Length() * go->normal_position;
	}
}

void MazeGenerator::AddMazetoGOList(vector<PhysicsObject*>* m_goList)
{
	for (int i = 0; i < (int)MazeList.size(); ++i)
	{
		PhysicsObject* go = MazeList[i];
		m_goList->push_back(go);
	}
}