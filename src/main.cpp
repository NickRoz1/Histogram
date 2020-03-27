#include <experimental/filesystem>
#include <gauss.hpp>
#include <hist.hpp>
#include <iostream>
#include <numpy/arrayobject.h>
#include <python3.6m/Python.h>
#include <test.hpp>

Histogram gaussian_plot();
void plot_heatmap(Histogram hist);
void fill_gaussian_distribution(Histogram &hist, float mean, float std_dev,
                                int num_samples);

float parse_float(char *input) {
  auto str = std::string(input);
  return std::stof(str);
}

int parse_int(char *input) {
  auto str = std::string(input);
  return std::stoi(str);
}

int main(int argc, char **argv) {
  if (argc != 10) {
    std::cout << "Usage: ./Histogram (mean value) (standart deviation value) "
                 "(number of samples) (x min) (x max) (y min) (y max) (x axis "
                 "bin count) (y axis bin count)\n";
    return 0;
  }

  float mean = parse_float(argv[1]);
  float std_dev = parse_float(argv[2]);
  int num_of_samples = parse_int(argv[3]);
  float xmin = parse_float(argv[4]);
  float xmax = parse_float(argv[5]);
  float ymin = parse_float(argv[6]);
  float ymax = parse_float(argv[7]);
  int xbincount = parse_int(argv[8]);
  int ybincount = parse_int(argv[9]);

  Histogram hist = get_2d_hist(xmin, xmax, ymin, ymax, xbincount, ybincount);
  fill_gaussian_distribution(hist, mean, std_dev, num_of_samples);
  plot_heatmap(hist);

  // print_flat_2d_hist(hist);

  // test_2d_hist();
  // test_outside_the_limits();

  return 0;
}

void plot_heatmap(Histogram hist) {
  PyObject *pName, *pModule, *pFunc, *pValue, *pArgs;
  char module[] = "heatmap";
  char func[] = "plot_heatmap";
  auto module_path =
      std::experimental::filesystem::current_path().parent_path() / "plot" /
      ".";
  const int SIZE = hist.get_hist().size();
  npy_intp dims[1]{SIZE};
  const int ND = 1;

  std::cout << module_path << "\n";
  Py_Initialize();
  _import_array();
  PyObject *sys_path = PySys_GetObject("path");
  PyList_Append(sys_path, PyUnicode_FromString(module_path.c_str()));

  pName = PyUnicode_FromString(module);
  pModule = PyImport_Import(pName);
  Py_DECREF(pName);

  auto dimensions = hist.dims_bin_num();
  int height = dimensions[0];
  int width = dimensions[1];
  auto limits = hist.get_limits();
  float xmin = limits[0].first;
  float xmax = limits[0].second;
  float ymin = limits[1].first;
  float ymax = limits[1].second;
  std::vector<int> flat_hist = hist.get_hist();
  int *c_arr = flat_hist.data();

  PyObject *pArray = PyArray_SimpleNewFromData(ND, dims, NPY_INT, c_arr);

  if (!pArray) {
    Py_DECREF(pModule);
    PyErr_Print();
    fprintf(stderr, "Call failed\n");
    return;
  }

  if (pModule != NULL) {
    pFunc = PyObject_GetAttrString(pModule, func);
    if (pFunc && PyCallable_Check(pFunc)) {
      pArgs = PyTuple_New(7);
      PyTuple_SetItem(pArgs, 0, pArray);
      PyTuple_SetItem(pArgs, 1, PyLong_FromLong(height));
      PyTuple_SetItem(pArgs, 2, PyLong_FromLong(width));
      PyTuple_SetItem(pArgs, 3, PyLong_FromLong(xmin));
      PyTuple_SetItem(pArgs, 4, PyLong_FromLong(xmax));
      PyTuple_SetItem(pArgs, 5, PyLong_FromLong(ymin));
      PyTuple_SetItem(pArgs, 6, PyLong_FromLong(ymax));

      pValue = PyObject_CallObject(pFunc, pArgs);
      Py_DECREF(pArgs);
      if (pValue != NULL) {
        fprintf(stderr, "Call succeed\n");
      } else {
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        PyErr_Print();
        fprintf(stderr, "Call failed\n");
        return;
      }
    }
  }

  Py_Finalize();
}

void fill_gaussian_distribution(Histogram &hist, float mean, float std_dev,
                                int num_samples) {
  auto points = gaussian_distribution_2d(mean, std_dev, num_samples);

  for (const auto &point : points) {
    hist.fill(point);
  }
}