////////////////////////////////////////////////////////////////////////////////
// Module Name:  xipoint.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.1
// Date:         08.09.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "xipoint.h"

#include <algorithm>        // min
#include <cmath>

namespace xi {
    Point::Point(int x, int y) {
        _x = x;
        _y = y;
    }
    void Point::shift(int shf) {
        _x += shf;
        _y += shf;
    }
    void Point::shift(int xSh, int ySh){
        _x += xSh;
        _y += ySh;
    }
    void Point::shift(const xi::Point &pt){
        _x += pt.getX();
        _y += pt.getY();
    }

    double Point::dist(const xi::Point &other) const{
        return sqrt(pow(other.getX() - _x, 2) + pow(other.getY() - _y, 2));
    }


    int Point::getX() const { return _x;}
    int Point::getY() const { return _y;}

    void Point::setX(int x) {_x = x;}
    void Point::setY(int y) {_y = y;}



    PointArray::PointArray()
    {
        _size = 0;
        _arr = nullptr;
    }

    PointArray::PointArray(const xi::Point *points, xi::PointArray::Uint n) {


        _size = 0;
        _arr = nullptr;
        resize(n);

        for (Uint i = 0; i < n;i++)
        {
            _arr[i] = points[i];
        }


    }

    PointArray::PointArray(const xi::PointArray &pv) {

        _size = 0;
        _arr = nullptr;
        resize(pv.getSize());

        for(Uint i = 0; i < pv.getSize();i++)
        {
            _arr[i] = pv.getRawPtr()[i];
        }
    }
    PointArray::~PointArray() {
        clear();
    }


    void PointArray::append(const xi::Point &pt) {
        resize(_size + 1);
        _arr[_size-1] = pt;
    }


    void PointArray::insert(const xi::Point &pt, xi::PointArray::Uint pos) {

        if(pos > _size){
            pos = _size;
        }

        Point shift = pt;

        resize(_size + 1);
        for(Uint i = pos;i < _size;i++)
        {
            Point tmp = _arr[i];
            _arr[i] = shift;
            shift = tmp;
        }
    }

    void PointArray::remove(xi::PointArray::Uint pos) {
        if(pos >= _size)
            return;
        for(Uint i = pos; i < _size - 1;i++)
        {
            _arr[i] = _arr[i+1];
        }
        resize(_size - 1);
    }

    void PointArray::clear() {
        resize(0);
    }


    double PointArray::computePath() const {
        double sum = 0;
        for(Uint i = 0;i < _size - 1;i++){
            sum += _arr[i].dist(_arr[i+1]);
        }
        return sum;
    }


    PointArray::Uint PointArray::getSize() const {
        return _size;
    }

    Point* PointArray::get(xi::PointArray::Uint pos) {
        if(pos > _size){
            return nullptr;
        }
        return &_arr[pos];

    }

    const Point* PointArray::get(xi::PointArray::Uint pos) const {
        if(pos > _size){
            return nullptr;
        }
        return &_arr[pos];
    }






    void PointArray::resize(xi::PointArray::Uint n) {
        Point* tmp = new Point[n];

        for(Uint i = 0; i < _size;i++){
            tmp[i] = _arr[i];
        }

        delete[] _arr;
        _arr = tmp;
        _size = n;
    }
} // namespace xi {

