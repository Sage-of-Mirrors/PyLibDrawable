#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <math.hpp>
#include <libdrawable.hpp>
#include <drawable.hpp>

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
        .def("GetVertexPositionArray", &UGeometry::GetVertexPositionArray)
        .def("GetIndexArray", &UGeometry::GetIndexArray)
        .def_readwrite("Vertices", &UGeometry::Vertices)
        .def_readwrite("Indices", &UGeometry::Indices);
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
        .def_readwrite("Lods", &UDrawable::Lods);

    m.def("ImportYdr", &ImportYdr, py::return_value_policy::take_ownership);
}