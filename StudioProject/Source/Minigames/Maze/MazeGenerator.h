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
	void SetUp(string FileDirectory);
	void Update(double dt);
	void AddMazetoGOList(vector<PhysicsObject*>*);
private:
	vector<MazeObject*> MazeList;
	float m_worldWidth;
	float m_worldHeight;
};

#endif // !MAZEGENERATOR_H