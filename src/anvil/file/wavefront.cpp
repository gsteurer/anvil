#include "anvil/file/wavefront.h"

// @@@ todo remove these
#include <fstream>
#include <string>
#include <vector>

#include "anvil/file/mesh.h"
#include "anvil/math/vec4f.h"
#include "anvil/string/stlutils.h"

namespace astl = anvil::string::stlutils;
namespace avec = anvil::math;

namespace anvil {
namespace file {
namespace wavefront {

// @@@ consider adding exception handling https://stackoverflow.com/questions/2512931/catch-multiple-custom-exceptions-c
avec::Vec4f parse_vertex(std::vector<std::string> line) {
    avec::Vec4f result = avec::Point(0.0, 0.0, 0.0);
    if (line.size() >= 1) {
        double x = std::atof(line[1].c_str());  // can throw an exception
        result.x = x;
    }
    if (line.size() >= 2) {
        double y = std::atof(line[2].c_str());
        result.y = y;
    }
    if (line.size() >= 3) {
        double z = std::atof(line[3].c_str());
        result.z = z;
    }

    return result;
}

Face parse_face_index_element(std::string line) {
    Face face;
    std::vector<std::string> indicies = astl::split(line, "/");
    if (indicies.size() >= 1) {
        int vertex = std::atoi(indicies[0].c_str()) - 1;  // can throw an exception
        face.vertex = vertex;
    }
    if (indicies.size() >= 2) {
        int texture = std::atoi(indicies[1].c_str()) - 1;  // can throw an exception
        face.texture = texture;
    }
    if (indicies.size() >= 3) {
        int normal = std::atoi(indicies[2].c_str()) - 1;  // can throw an exception
        face.normal = normal;
    }
    return face;
}

std::array<Face, 3> parse_face_indicies(std::vector<std::string> line) {
    if (line.size() != 4) {
        throw std::runtime_error("no support for more than three indicies per face");
    }

    std::array<Face, 3> faces;

    faces[0] = parse_face_index_element(line[1]);
    faces[1] = parse_face_index_element(line[2]);
    faces[2] = parse_face_index_element(line[3]);

    return faces;
}

Mesh Parse(std::string filename) {
    Mesh mesh;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("could not open file " + filename);
    }
    std::string line;
    while (std::getline(file, line)) {
        auto result = astl::split(astl::strip(line), " ");
        if (result.size() == 0) {
            throw std::runtime_error("could not parse file " + filename);
        }
        std::string element = result[0];

        if (element.compare("v") == 0) {  // vertex
            avec::Vec4f vert = parse_vertex(result);
            mesh.verts.Insert(vert);
        } else if (element.compare("vt") == 0) {  // texture coords
            avec::Vec4f vert = parse_vertex(result);
            vert.z = 0.0f;
            mesh.textures.Insert(vert);
        } else if (element.compare("vn") == 0) {  // vertex normal
            avec::Vec4f vert = parse_vertex(result);
            vert.z = 0.0f;
            mesh.normals.Insert(vert);
        } else if (element.compare("vp") == 0) {  // parameter space verts

        } else if (element.compare("f") == 0) {  // face element
            auto faces = parse_face_indicies(result);
            mesh.faces.Insert(faces);
        } else if (element.compare("l") == 0) {  // line element
        }
    }
    file.close();

    return mesh;
}

};  // namespace wavefront
};  // namespace file
};  // namespace anvil