#include <vector>

#include <boost/python.hpp>

namespace bp=boost::python;

class Row
{
public:
    Row(const std::vector<int>& data,
        std::size_t row,
        std::size_t cols) : data_(data),
                            row_(row),
                            cols_(cols)
        {}

    int get(std::size_t idx) const {
        return data_[row_ * cols_ + idx];
    }

private:
    const std::vector<int>& data_;
    std::size_t row_, cols_;
};

class Matrix
{
public:
    Matrix(std::size_t rows,
           std::size_t cols) : rows_(rows),
                               cols_(cols),
                               data_(rows * cols, 0)
        {}

    Row get(std::size_t idx) const {
        return Row(data_, idx, cols_);
    }

private:
    std::size_t rows_, cols_;
    std::vector<int> data_;
};

BOOST_PYTHON_MODULE(call_policies)
{
    bp::class_<Row>("Row", bp::init<const std::vector<int>&, std::size_t, std::size_t>())
        .def("get", &Row::get)
        ;

    bp::class_<Matrix>("Matrix", bp::init<std::size_t, std::size_t>())
        .def("get", &Matrix::get, bp::with_custodian_and_ward_postcall<0, 1>())
        ;
}
