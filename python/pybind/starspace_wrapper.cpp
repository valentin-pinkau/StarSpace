#include <pybind11/pybind11.h>
#include "../../src/starspace.h"

int add(int i, int j) {
    return i + j;
}

namespace py = pybind11;
using namespace starspace;


PYBIND11_MODULE(starspace_wrapper, m) {
m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------
        .. currentmodule:: cmake_example
        .. autosummary::
           :toctree: _generate
           add
           subtract
    )pbdoc";

py::class_<Args>(m, "args")
    .def(py::init<>())
    .def_readwrite("lr", &Args::lr)
    .def_readwrite("termLr", &Args::termLr)
    .def_readwrite("norm", &Args::norm)
    .def_readwrite("margin", &Args::margin)
    .def_readwrite("wordWeight", &Args::wordWeight)
    .def_readwrite("initRandSd", &Args::initRandSd)
    .def_readwrite("dropoutLHS", &Args::dropoutLHS)
    .def_readwrite("dropoutRHS", &Args::dropoutRHS)
    .def_readwrite("p", &Args::p)
    .def_readwrite("dim", &Args::dim)
    .def_readwrite("epoch", &Args::epoch)
    .def_readwrite("ws", &Args::ws)
    .def_readwrite("maxTrainTime", &Args::maxTrainTime)
    .def_readwrite("thread", &Args::thread)
    .def_readwrite("maxNegSamples", &Args::maxNegSamples)
    .def_readwrite("negSearchLimit", &Args::negSearchLimit)
    .def_readwrite("minCount", &Args::minCount)
    .def_readwrite("minCountLabel", &Args::minCountLabel)
    .def_readwrite("K", &Args::K)
    .def_readwrite("verbose", &Args::verbose)
    .def_readwrite("debug", &Args::debug)
    .def_readwrite("adagrad", &Args::adagrad)
    .def_readwrite("normalizeText", &Args::normalizeText)
    .def_readwrite("trainMode", &Args::trainMode)
    .def_readwrite("fileFormat", &Args::fileFormat)
    .def_readwrite("label", &Args::label)
    .def_readwrite("bucket", &Args::bucket)
    .def_readwrite("ngrams", &Args::ngrams)
    .def_readwrite("loss", &Args::loss)
    .def_readwrite("similarity", &Args::similarity)
    .def_readwrite("isTrain", &Args::isTrain)
    .def_readwrite("shareEmb", &Args::shareEmb)
    .def_readwrite("saveEveryEpoch", &Args::saveEveryEpoch)
    .def_readwrite("saveTempModel", &Args::saveTempModel)
    .def_readwrite("useWeight", &Args::useWeight)
    .def_readwrite("trainWord", &Args::trainWord);

m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers
        Some other explanation about the subtract function.
    )pbdoc");

#ifdef VERSION_INFO
m.attr("__version__") = VERSION_INFO;
#else
m.attr("__version__") = "dev";
#endif
}