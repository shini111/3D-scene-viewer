#include "OBJModel.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>




OBJModel::OBJModel() {
}

OBJModel::~OBJModel() {
}

void OBJModel::LoadFromFile(const char* fileName) {
	std::vector<Position> vertices;
	std::vector<Normal> normals;

	std::ifstream file(fileName);
	if (file)
	{
		std::string line;
		while (std::getline(file, line))
		{
			char currentMtlName[100];
			if (StartWith(line, "mtllib "))
			{
				char mtlFileName[100];
				(void)sscanf_s(line.c_str(), "mtlib %s", mtlFileName, sizeof(mtlFileName));
				LoadMaterialFile(mtlFileName);
			}
			if (StartWith(line, "v "))
			{
				Position pos;
				sscanf_s(line.c_str(), "v %f %f %f", &pos.x, &pos.y, &pos.z);
				vertices.push_back(pos);
			}
			if (StartWith(line, "vn "))
			{
				Normal n;
				sscanf_s(line.c_str(), "vn %f %f %f", &n.x, &n.y, &n.z);
				normals.push_back(n);
			}
			if (StartWith(line, "usemtl"))
			{
				(void)sscanf_s(line.c_str(), "usemtl %s", currentMtlName, sizeof(currentMtlName));
			}
			if (StartWith(line, "f "))
			{
				int v1, v2, v3;
				int n1, n2, n3;
				(void)sscanf_s(line.c_str(), "f %d//d %d//d %d//d", &v1, &n1, &v2, &n2, &v3, &n3);

				AddVertexData(v1, n1, currentMtlName, vertices, normals);
				AddVertexData(v2, n2, currentMtlName, vertices, normals);
				AddVertexData(v3, n3, currentMtlName, vertices, normals);
			}


		}
	}
}

std::vector<float> OBJModel::GetVertexData() {
	return mVertexData;
}

int OBJModel::GetVertexCount(){
	return mVertexData.size() / 9;
}

void OBJModel::LoadMaterialFile(const char* fileName) {
	std::ifstream file(fileName);
	if (file) {
		std::string line;
		while (std::getline(file,line))
		{
			char mtlName[100];
			if (StartWith(line, "newmtl "))
			{
				(void)sscanf_s(line.c_str(), "newmtl %s", mtlName, sizeof(mtlName));
				mMaterialMap[mtlName] = Color();
			}
			if (StartWith(line, "Kd "))
			{
				Color& color = mMaterialMap[mtlName];
				sscanf_s(line.c_str(), "Kd %f %f %f", &color.r, &color.g, &color.b);
			}
		}
	}
	else
	{
		std::cout << "Material file loading failed" << std::endl;
	}
}

bool OBJModel::StartWith(std::string& line, const char* text) {
	size_t textLen = strlen(text);
	if (line.size() < textLen)
	{
		return false;
	}
	for (size_t i = 0; i < textLen; i++)
	{
		if (line[i] == text[i]) continue;
		else return false;
	}
	return true;
}

void OBJModel::AddVertexData(int vIdx, int nIdx, const char* mtl,
	std::vector<Position>& vertices, std::vector<Normal>& normals){
	
	
	Color c = mMaterialMap[mtl];
	Position p = vertices[vIdx - 1];
	Normal n = normals[nIdx - 1];


	mVertexData.push_back(p.x);
	mVertexData.push_back(p.y);
	mVertexData.push_back(p.z);
	mVertexData.push_back(c.r);
	mVertexData.push_back(c.g);
	mVertexData.push_back(c.b);
	mVertexData.push_back(n.x);
	mVertexData.push_back(n.y);
	mVertexData.push_back(n.z);
}