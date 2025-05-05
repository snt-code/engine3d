#include "object.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>


// ########################################################

Object::Object()
{

}

// ########################################################

Object::~Object()
{

}

// ########################################################

void Object::loadOBJ(const std::string& path)
{
    std::ifstream objFile(path);
    if (!objFile.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return;
    }

    std::string line;
    while (std::getline(objFile, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        } else if (type == "f") {
            Face face;
            char slash; // To ignore slashes if present
            std::string v1, v2, v3;

            iss >> v1 >> v2 >> v3;

            auto parseIndex = [](const std::string& s) {
                std::istringstream ss(s);
                std::string indexStr;
                std::getline(ss, indexStr, '/');  // Read until first '/'
                return std::stoi(indexStr) - 1;    // OBJ is 1-based
            };

            face.v1 = parseIndex(v1);
            face.v2 = parseIndex(v2);
            face.v3 = parseIndex(v3);
            faces.push_back(face);
        }
    }
    objFile.close();
}

// ########################################################

float* Object::getVertices()
{
    float* verticeArrayPtr = new float(vertices.size()*3);
    for(unsigned i = 0; i < vertices.size(); i++ )
    {
      verticeArrayPtr[i*3]   = vertices[i].x;  
      verticeArrayPtr[i*3+1] = vertices[i].y;  
      verticeArrayPtr[i*3+2] = vertices[i].z;
    }    
    return verticeArrayPtr;
}

// ########################################################

unsigned* Object::getFaces()
{
    unsigned* facesArrayPtr = new unsigned(faces.size()*3);
    for(unsigned i = 0; i < faces.size(); i++ )
    {
      facesArrayPtr[i*3]   = faces[i].v1;  
      facesArrayPtr[i*3+1] = faces[i].v2;  
      facesArrayPtr[i*3+2] = faces[i].v3;  
    }    
    return facesArrayPtr;
}

// ########################################################