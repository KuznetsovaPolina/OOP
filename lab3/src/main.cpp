#include <iostream>
#include "Rectangle.h"
#include "Trapezoid.h"
#include "Rhombus.h"
#include "FigureArray.h"
#include "TotalArea.h"

int main() {
    std::cout << "Lab 3: Figures (Rectangle, Trapezoid, Rhombus)\n";
    std::cout << "Enter number of figures: ";
    std::size_t n;
    if (!(std::cin >> n)) {
        std::cerr << "Invalid number\n";
        return 1;
    }

    FigureArray arr;

    std::cout << "For each figure enter type and 4 vertex coordinates (x y).\n";
    std::cout << "Type: 1 - Rectangle, 2 - Trapezoid, 3 - Rhombus\n";

    for (std::size_t i = 0; i < n; ++i) {
        int type;
        std::cout << "Figure " << i << " type: ";
        std::cin >> type;

        if (!std::cin) {
            std::cerr << "Input error\n";
            return 1;
        }

        if (type == 1) {
            auto* r = new Rectangle();
            std::cout << "Enter 4 points (x y): ";
            std::cin >> *r;
            arr.push_back(r);
        } else if (type == 2) {
            auto* t = new Trapezoid();
            std::cout << "Enter 4 points (x y): ";
            std::cin >> *t;
            arr.push_back(t);
        } else if (type == 3) {
            auto* rh = new Rhombus();
            std::cout << "Enter 4 points (x y): ";
            std::cin >> *rh;
            arr.push_back(rh);
        } else {
            std::cerr << "Unknown type, try again\n";
            --i;
            continue;
        }
    }

    std::cout << "\nFigures info:\n";
    for (std::size_t i = 0; i < arr.size(); ++i) {
        Figure* f = arr[i];
        Point c = f->center();
        double s = f->area();
        std::cout << "Figure #" << i << ": " << *f << "\n";
        std::cout << "  Center: (" << c.x << ", " << c.y << ")\n";
        std::cout << "  Area: " << s << "\n";
    }

    std::cout << "\nTotal area: " << total_area(arr) << "\n";

    if (arr.size() > 0) {
        std::cout << "Enter index to remove (-1 to skip): ";
        int idx;
        std::cin >> idx;
        if (idx >= 0 && static_cast<std::size_t>(idx) < arr.size()) {
            arr.remove_at(static_cast<std::size_t>(idx));
            std::cout << "Figure removed. Now size = " << arr.size() << "\n";
        }
    }

    return 0;
}
