#include "MazeGenerator.h"

MazeGenerator::MazeGenerator()
{
	BiggestLength = 0.f;
}

MazeGenerator::~MazeGenerator()
{

}

void MazeGenerator::SetUp(string FileDirectory, vector<PhysicsObject*>* m_goList)
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
			maze->setType(PhysicsObject::GO_PILLAR);
			cout << "PILLAR, ";
			break;
		case 'W':
			maze->setType(PhysicsObject::GO_WALL);
			cout << "WALL,   ";
			break;
		default:
			maze->setType(PhysicsObject::GO_NONE);
			cout << "NONE,   ";
			break;
		}
		maze->setAngle_Normal(Math::DegreeToRadian(stof(info[1])));
		maze->normal.Set(cosf(maze->getAngle_Normal()), sinf(maze->getAngle_Normal()), 0);
		//maze->angle_normal = Math::DegreeToRadian(stof(info[1]));
		//maze->normal.Set(cosf(maze->angle_normal), sinf(maze->angle_normal), 0);

		maze->setOffset(Vector3(stof(info[2]), stof(info[3]), stof(info[4])));
		BiggestLength = (BiggestLength >= maze->getOffset().Length() ? BiggestLength : maze->getOffset().Length());
		maze->setNormal_Position(maze->getOffset().Normalized());
		maze->setAngle_Offset(atan2(maze->getNormal_Position().y, maze->getNormal_Position().x));
		//maze->offset.Set(stof(info[2]), stof(info[3]), stof(info[4]));
		//BiggestLength = (BiggestLength >= maze->offset.Length() ? BiggestLength : maze->offset.Length());
		//maze->normal_position = maze->offset.Normalized();
		//maze->angle_offset = atan2(maze->normal_position.y, maze->normal_position.x);

		maze->setScale(Vector3(stof(info[5]), stof(info[6]), stof(info[7])));

		maze->setLevel(stoi(info[8]));
		//maze->level = stoi(info[8]);

		maze->setPos(Vector3(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0));
		maze->setPos(maze->getOffset().Length() * maze->getNormal_Position(), true);
		//maze->pos += maze->offset.Length() * maze->normal_position;

		maze->setActive(true);
		cout << "P: " << maze->getPos() << ", S: " << maze->getScale() << ", A: " << Math::RadianToDegree(maze->getAngle_Normal()) << ", O: " << Math::RadianToDegree(maze->getAngle_Offset()) << endl;
		m_goList->push_back(maze);
	}
}

//void MazeGenerator::AddMazetoGOList(vector<PhysicsObject*>* m_goList)
//{
//	for (int i = 0; i < (int)MazeList.size(); ++i)
//	{
//		PhysicsObject* go = MazeList[i];
//		m_goList->push_back(go);
//	}
//}

float MazeGenerator::getBiggestLength()
{
	return BiggestLength;
}