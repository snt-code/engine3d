#ifndef GUI_OBJECT_H
#define GUI_OBJECT_H

#include <string>
#include <vector>


struct Vertex
{
  float x;
  float y;
  float z;  
};

struct Face
{
  unsigned v1;
  unsigned v2;
  unsigned v3;  
};


class Object
{
public:

    Object();

    ~Object();


public:

    void loadOBJ(const std::string& path);

    float* getVertices();

    unsigned* getFaces();

    unsigned getVerticesSize(){ return vertices.size()*3;};

    unsigned getFacesSize(){ return faces.size()*3;};

private:

    std::vector<Vertex> vertices;
    std::vector<Face>   faces;


};

#endif // GUI_SHADER_H