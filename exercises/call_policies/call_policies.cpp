#include <vector>

class Row
{
public:
    Row(std::size_t size) : data_(size, 0)
	{}

    int get(std::size_t idx) const {
	return data_[idx];
    }

private:
    std::vector<int> data_;
};

class Matrix
{
public:
    Matrix(std::size_t rows,
	   std::size_t cols) : data_(rows, Row(cols))
	{}

    const Row& get(std::size_t idx) const {
	return data_[idx];
    }

private:
    std::vector<Row> data_;
};

// Exercise: Expose these classes such that `test.py` works.
