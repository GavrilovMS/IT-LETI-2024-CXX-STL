#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

struct Point {
    int x, y;

    bool operator<(const Point& other) const {
        return x < other.x;
    }

    bool operator>(const Point& other) const {
        return x > other.x;
    }
};

std::ostream& operator<<(std::ostream& out, const Point& p) {
    out << "(" << p.x << "," << p.y << ")";
    return out;
}


int main() {
    std::cout << "Standart sort" << std::endl;
    std::vector<int> vec = {4, 2, 5, 1, 3};
    std::sort(vec.begin(), vec.end());
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl << std::endl;

    std::cout << "Sort with operator< overload" << std::endl;
    std::vector<Point> points = {{4, 3}, {2, 1}, {5, 4}, {1, 2}};
    std::sort(points.begin(), points.end());
    std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(std::cout, " "));
    std::cout << std::endl << std::endl;

    std::cout << "Using std::greater" << std::endl;
    points = {{4, 3}, {2, 1}, {5, 4}, {1, 2}};
    std::sort(points.begin(), points.end(), std::greater<Point>());
    std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(std::cout, " "));
    std::cout << std::endl << std::endl;

    std::cout << "Custom comparator" << std::endl;
    points = {{4, 3}, {2, 1}, {5, 4}, {1, 2}};
    struct MyGreater {
        bool operator()(const Point& p1, const Point& p2) const {
            return p1.y > p2.y;
        }
    };
    std::sort(points.begin(), points.end(), MyGreater());
    std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(std::cout, " "));
    std::cout << std::endl << std::endl;

    std::cout << "Lambda" << std::endl;
    points = {{4, 3}, {2, 1}, {5, 4}, {1, 2}};
    std::sort(points.begin(), points.end(), [](const Point& p1, const Point& p2) { return p1.y > p2.y; });
    std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(std::cout, " "));
    std::cout << std::endl << std::endl;

    return 0;
}