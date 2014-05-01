#include <vector>

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

// Exercise: Expose these classes such that `test.py` works.
