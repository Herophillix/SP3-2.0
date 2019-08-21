#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <fstream>
#include <string>
#include "../../Scenes/MazeObject.h"
#include <vector>
#include "../../Application.h"

using namespace std;

class MazeGenerator
{
public:
	MazeGenerator();
	~MazeGenerator();
	void SetUp(string FileDirectory, vector<PhysicsObject*>* m_goList);
	//void AddMazetoGOList(vector<PhysicsObject*>*);
	float getBiggestLength();
private:
	vector<MazeObject*> MazeList;
	float m_worldWidth;
	float m_worldHeight;
	float BiggestLength;
};

#endif // !MAZEGENERATOR_H