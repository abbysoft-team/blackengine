#include "blobjparser.h"

#include <exception>
#include <iostream>

namespace black {

OBJParser::OBJParser()
    : m_vertices(),
      m_normals(),
      m_uvCoords(),
      m_indices(),

      m_vVertex(),
      m_vNormal(),
      m_vTexture(),
      m_vIndex(),

      m_file()
{

}

void OBJParser::parseObj(std::string path)
{
    m_file.open(path);
    if ( !m_file.is_open() ) {
        std::cerr << "Failed to load model " << path << ": file not found!" << '\n';

        //TODO: exceptions
        throw "Bad file";
    }

    std::string line;

    getline(m_file, line);       // First header line
    getline(m_file, line);       // Second header line must be www.blender.org

    if ( line.find("www.blender.org") == std::string::npos ) {
        std::cerr << "Failed to load model " << path << ": wrong obj file!" << '\n';

        //TODO: exceptions
        throw "Bad file";
    }

    std::string type; // Type of a data (v for vertices, vn for normals and so on)

    /* Reads verices and indices data until line with starting f*/
    try {
        while (readVertex()) {}
    } catch(std::exception &e) {
        std::cerr << "Failed to load model " << path << ": " <<  e.what() << '\n';
        throw e;
    }

    // Sorting data
    m_vVertex.reserve(m_vertices.size());
    m_vNormal.reserve(m_normals.size());
    m_vTexture.reserve(m_uvCoords.size());
    m_vIndex.reserve(m_indices.size());

    while (true) {
       if ( !readFace() ) {
           break;
       }
    }

    m_file.close();
}

void OBJParser::splitString(std::string str, std::string delimiter, std::string *out, int size)
{
    int count = 0;
    size_t pos = str.find(delimiter);
    std::string token;
    do {
        if ( ++count > size ) {
            return;
        }

        token = str.substr(0, pos);

        *(out) = token;
        ++out;

        str.erase(0, pos + delimiter.length());
    } while ( (pos = str.find(delimiter)) != std::string::npos );

    *(out) = str;
}

bool OBJParser::readVertex()
{
    std::string type;
    try {
        m_file >> type;

        if ( type == "v" ) {
            readCoord();
        } else if ( type == "vt" ) {
            readTexture();
        } else if ( type == "vn" ) {
            readNormal();
        } else if ( type == "f" ) {   // End of list
            m_file.unget();
            return false;
        } else { // Skip this line
            getline(m_file, type);
            return true;
        }

        return true;
    } catch(std::exception &e) {
        throw e;
    }
}

void OBJParser::readCoord()
{
    float fnumber;

    m_file >> fnumber;
    m_vertices.push_back(fnumber);
    m_file >> fnumber;
    m_vertices.push_back(fnumber);
    m_file >> fnumber;
    m_vertices.push_back(fnumber);
}

void OBJParser::readTexture()
{
    float fnumber;

    m_file >> fnumber;
    m_uvCoords.push_back(fnumber);
    m_file >> fnumber;
    m_uvCoords.push_back(fnumber);
}

void OBJParser::readNormal()
{
    float fnumber;

    m_file >> fnumber;
    m_normals.push_back(fnumber);
    m_file >> fnumber;
    m_normals.push_back(fnumber);
    m_file >> fnumber;
    m_normals.push_back(fnumber);
}

void OBJParser::readIndex()
{
    int inumber;

    m_file >> inumber;
    m_indices.push_back(inumber);
    m_file >> inumber;
    m_indices.push_back(inumber);
}

bool OBJParser::readFace()
{
    std::string type;
    std::string group;
    std::string splited[3];

    m_file >> type;

    if ( type.empty() ) {
        return false;
    }

    if ( type != "f" ) {
        getline(m_file, type); // seek to the end of line
        return true;
    }

    for (int i = 0; i < 3; ++i) {
        m_file >> group; // x\y\z group
        splitString(group, "/", splited, 3);

        readFaceElement(splited);
    }

    return true;
}

void OBJParser::readFaceElement(const std::string splited[])
{
    int index = std::stoi(splited[0]) - 1;

    m_vVertex.push_back(m_vertices[index * 3]);
    m_vVertex.push_back(m_vertices[index * 3 + 1]);
    m_vVertex.push_back(m_vertices[index * 3 + 2]);

    index = std::stoi(splited[1]) - 1;
    m_vTexture.push_back(m_uvCoords[index * 2]);
    m_vTexture.push_back(m_uvCoords[index * 2 + 1]);
    m_vTexture.push_back(m_uvCoords[index * 2 + 2]);

    index = std::stoi(splited[2]) - 1;
    m_vNormal.push_back(m_normals[index * 3]);
    m_vNormal.push_back(m_normals[index * 3 + 1]);
    m_vNormal.push_back(m_normals[index * 3 + 2]);
}

}
