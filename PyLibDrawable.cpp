#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <math.hpp>
#include <libdrawable.hpp>
#include <drawable.hpp>
#include <skeleton.hpp>
#include <drawabledictionary.hpp>

namespace py = pybind11;

PYBIND11_MODULE(pylibdrawable, m) {
    py::class_<UVector2>(m, "UVector2")
        .def(py::init<>())
        .def_readwrite("x", &UVector2::x)
        .def_readwrite("y", &UVector2::y);
    py::class_<UVector3>(m, "UVector3")
        .def(py::init<>())
        .def_readwrite("x", &UVector3::x)
        .def_readwrite("y", &UVector3::y)
        .def_readwrite("z", &UVector3::z);
    py::class_<UVector4>(m, "UVector4")
        .def(py::init<>())
        .def_readwrite("x", &UVector4::x)
        .def_readwrite("y", &UVector4::y)
        .def_readwrite("z", &UVector4::z)
        .def_readwrite("w", &UVector4::w);
    py::class_<UMatrix4>(m, "UMatrix4")
        .def(py::init<>())
        .def_readwrite("r0", &UMatrix4::r0)
        .def_readwrite("r1", &UMatrix4::r1)
        .def_readwrite("r2", &UMatrix4::r2)
        .def_readwrite("r3", &UMatrix4::r3);

    py::class_<UShaderUniform>(m, "UShaderUniform")
        .def(py::init<>())
        .def_readwrite("Name", &UShaderUniform::Name)
        .def_readwrite("Hash", &UShaderUniform::Hash)
        .def_readwrite("Data", &UShaderUniform::Data);
    py::class_<UShader>(m, "UShader")
        .def(py::init<>())
        .def_readwrite("Name", &UShader::Name)
        .def_readwrite("Hash", &UShader::Hash)
        .def_readwrite("Uniforms", &UShader::Uniforms)
        .def("GetUniforms", [](const UShader& s) {
            std::map<std::string, std::vector<float>> uniforms;

            for (UShaderUniform* u : s.Uniforms) {
                uniforms[u->Name] = u->Data;
            }

            return uniforms;
        });

    py::class_<UJoint>(m, "UJoint")
        .def(py::init<>())
        .def_readwrite("Name", &UJoint::Name)
        .def_readwrite("Parent", &UJoint::Parent)
        .def_readwrite("Children", &UJoint::Children)
        .def("GetRotation", &UJoint::GetRotation)
        .def("GetTranslation", &UJoint::GetTranslation)
        .def("GetScale", &UJoint::GetScale)
        .def("GetInverseBindMatrix", &UJoint::GetInverseBindMatrix)
        .def("GetBindMatrix", &UJoint::GetBindMatrix);
    py::class_<USkeleton>(m, "USkeleton")
        .def(py::init<>())
        .def_readwrite("Root", &USkeleton::Root)
        .def_readwrite("FlatSkeleton", &USkeleton::FlatSkeleton);

    py::class_<UVertex>(m, "UVertex")
        .def(py::init<>())
        .def_readwrite("Position", &UVertex::Position)
        .def_readwrite("Normal", &UVertex::Normal)
        .def_readwrite("Tangent", &UVertex::Tangent)
        .def_readwrite("Binormal", &UVertex::Binormal)
        .def_readwrite("Color", &UVertex::Color)
        .def_readwrite("BlendWeight", &UVertex::BlendWeight)
        .def_readwrite("BlendIndex", &UVertex::BlendIndex)
        .def_readwrite("TexCoord", &UVertex::TexCoord);
    py::class_<UGeometry>(m, "UGeometry")
        .def(py::init<>())
        .def("GetVertexPositionArray", [](const UGeometry& g, int index = 0) {
            std::vector<std::array<float, 3>> positions;

            for (UVertex* v : g.Vertices) {
                positions.push_back({
                    v->Position[index].x,
                    v->Position[index].y,
                    v->Position[index].z
                });
            }

            return positions;
        })
        .def("GetVertexNormalArray", [](const UGeometry& g, int index = 0) {
             std::vector<std::array<float, 3>> normals;

             for (UVertex* v : g.Vertices) {
                 normals.push_back({
                     v->Normal[index].x,
                     v->Normal[index].y,
                     v->Normal[index].z
                 });
             }

             return normals;
        })
        .def("GetVertexBlendIndexArray", [](const UGeometry& g, int index = 0) {
            std::vector<std::array<uint32_t, 4>> blendIndices;

            for (UVertex* v : g.Vertices) {
                blendIndices.push_back({
                    static_cast<uint32_t>(v->BlendIndex[index].x),
                    static_cast<uint32_t>(v->BlendIndex[index].y),
                    static_cast<uint32_t>(v->BlendIndex[index].z),
                    static_cast<uint32_t>(v->BlendIndex[index].w)
                });
            }

            return blendIndices;
        })
        .def("GetVertexBlendWeightArray", [](const UGeometry& g, int index = 0) {
            std::vector<std::array<float, 4>> blendWeights;

            for (UVertex* v : g.Vertices) {
                blendWeights.push_back({
                    v->BlendIndex[index].x,
                    v->BlendIndex[index].y,
                    v->BlendIndex[index].z,
                    v->BlendIndex[index].w
                });
            }

            return blendWeights;
        })
        .def("GetVertexColorArray", [](const UGeometry& g, int index = 0) {
            std::vector<std::array<float, 4>> colors;

            for (UVertex* v : g.Vertices) {
                colors.push_back({
                    v->Color[index].x,
                    v->Color[index].y,
                    v->Color[index].z,
                    v->Color[index].w
                });
            }

            return colors;
        })
        .def("GetVertexTexCoordArray", [](const UGeometry& g, int index = 0) {
            std::vector<std::array<float, 2>> texCoords;

            for (UVertex* v : g.Vertices) {
                texCoords.push_back({
                    v->TexCoord[index].x,
                    v->TexCoord[index].y
                });
            }

            return texCoords;
        })
        .def("GetIndexArray", [](const UGeometry& g) {
            std::vector<std::array<uint32_t, 3>> indices;

            for (int i = 2; i < g.Indices.size(); i += 3) {
                indices.push_back({
                    g.Indices[i - 2],
                    g.Indices[i - 1],
                    g.Indices[i]
                });
            }

            return indices;
            })
        .def_readonly("PositionsCount", &UGeometry::PositionsCount)
        .def_readonly("NormalsCount", &UGeometry::NormalsCount)
        .def_readonly("TangentsCount", &UGeometry::TangentsCount)
        .def_readonly("BinormalsCount", &UGeometry::BinormalsCount)
        .def_readonly("BlendIndicesCount", &UGeometry::BlendIndicesCount)
        .def_readonly("BlendWeightsCount", &UGeometry::BlendWeightsCount)
        .def_readonly("ColorsCount", &UGeometry::ColorsCount)
        .def_readonly("TexCoordsCount", &UGeometry::TexCoordsCount)
        .def("GetShader", [](const UGeometry& g) {
            return g.Shader;
        }, py::return_value_policy::reference);
    py::class_<UModel>(m, "UModel")
        .def(py::init<>())
        .def_readwrite("Geometries", &UModel::Geometries);
    py::class_<ULod>(m, "ULod")
        .def(py::init<>())
        .def_readwrite("Models", &ULod::Models)
        .def_readwrite("LodDistance", &ULod::LodDistance)
        .def_readwrite("LodFlags", &ULod::LodFlags);
    py::class_<UDrawable>(m, "UDrawable")
        .def(py::init<>())
        .def_readwrite("FileName", &UDrawable::FileName)
        .def_readwrite("Lods", &UDrawable::Lods)
        .def_readwrite("Skeleton", &UDrawable::Skeleton)
        .def_readwrite("DictionaryHash", &UDrawable::DictionaryHash);

    py::class_<UDrawableDictionary>(m, "UDrawableDictionary")
        .def(py::init<>())
        .def_readwrite("Drawables", &UDrawableDictionary::Drawables);

    m.def("ImportYdr", &ImportYdr, py::return_value_policy::take_ownership);
    m.def("ImportYdd", &ImportYdd, py::return_value_policy::take_ownership);
}