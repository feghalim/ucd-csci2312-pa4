//
// Created by Mario on 4/11/2016.
//

#include "Exceptions.h"

namespace Gaming {
    void GamingException::setName(std::string name) {
        __name = name;
    }
    std::ostream &operator<<(std::ostream &os, const GamingException &ex) {
        os << "Exception " << ex.getName() << std::endl;
        return os;
    }

    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height) {
        setName("DimensionsEx");
        __exp_width = expWidth;
        __exp_height = expHeight;
        __width = width;
        __height = height;
    }
    unsigned DimensionEx::getExpHeight() const { return __exp_height; }
    unsigned DimensionEx::getExpWidth() const { return __exp_width; }
    unsigned DimensionEx::getWidth() const { return __width; }
    unsigned DimensionEx::getHeight() const { return __height; }
    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width, unsigned height) {
        setName("InsufficientDimensionsEx");
        __exp_height = minHeight;
        __exp_width = minWidth;
        __width = width;
        __height = height;
    }
    void InsufficientDimensionsEx::__print_args(std::ostream &os) const {
        os << getName() << ": " << getHeight() << " < " << getExpHeight() << "and/or" << getWidth() << " < " << getExpWidth();
    }
    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height) {
        setName("OutOfBoundsEx");
        __exp_width = maxWidth;
        __exp_height = maxHeight;
        __height = height;
        __width = width;
    }
    void OutOfBoundsEx::__print_args(std::ostream &os) const {
        os << getName() << ": " << getHeight() << " > " << getExpHeight() << "and/or" << getWidth() << " > " << getExpWidth();
    }

    PositionEx::PositionEx(unsigned x, unsigned y) {
        setName("PositionEx");
        __x = x;
        __y = y;
    }
}