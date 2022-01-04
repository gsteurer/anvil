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
struct face_index {
    int vertex;
    int texture;
    int normal;
};

face_index parse_face_index_element(std::string line) {
    face_index index;
    std::vector<std::string> indicies = astl::split(line, "/");
    if (indicies.size() >= 1) {
        int vertex = std::atoi(indicies[0].c_str()) - 1;  // can throw an exception
        index.vertex = vertex;
    }
    if (indicies.size() >= 2) {
        int texture = std::atoi(indicies[1].c_str()) - 1;  // can throw an exception
        index.texture = texture;
    }
    if (indicies.size() >= 3) {
        int normal = std::atoi(indicies[2].c_str()) - 1;  // can throw an exception
        index.normal = normal;
    }
    return index;
}

std::vector<face_index> parse_face_indicies(std::vector<std::string> line) {
    if (line.size() != 4) {
        throw std::runtime_error("no support for more than three indicies per face");
    }
    std::vector<face_index> indices;

    indices.push_back(parse_face_index_element(line[1]));

    indices.push_back(parse_face_index_element(line[2]));

    indices.push_back(parse_face_index_element(line[3]));

    return indices;
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

        } else if (element.compare("vn") == 0) {  // vertex normal

        } else if (element.compare("vp") == 0) {  // parameter space verts

        } else if (element.compare("f") == 0) {  // face element
            auto indices = parse_face_indicies(result);
            std::array<uint32_t, 3> face;
            face[0] = indices[0].vertex;
            face[1] = indices[1].vertex;
            face[2] = indices[2].vertex;
            mesh.faces.Insert(face);
        } else if (element.compare("l") == 0) {  // line element
        }
    }
    file.close();

    return mesh;
}

};  // namespace wavefront
};  // namespace file
};  // namespace anvil