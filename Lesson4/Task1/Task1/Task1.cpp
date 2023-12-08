#include <iostream>
#include <cassert>
#include <algorithm>
#include <random>

#include "shape.h"
#include "point.h"
#include "line.h"
#include "rectangle.h"
#include "parallelepiped.h"
#include "circle.h"
#include "cylinder.h"
#include "transform.h"


namespace tests
{
    using namespace point;
    using namespace shapes;

    void testPoints();
    void testLine();
    void testRectangle();
    void testParallelepiped();
    void testCircle();
    void testCylinder();
    void testTransform();
}

int main()
{
    using namespace tests;

    testPoints();
    testLine();
    testRectangle();
    testParallelepiped();
    testCircle();
    testCylinder();
    testTransform();
}


namespace tools
{
    inline bool areEqual(double a, double b)
    {
        return fabs(a - b) < 0.00001;
    }
}

void tests::testPoints()
{
    {
        Point A{ 12, 17 };
        Point B{ 12, 17 };
        Point C{ 1, 12 };
        assert(A == B);
        assert(A != C);
        assert(B != C);

        A.scaleX(2);
        assert(A.getX() == 24);

        B.scaleY(3);
        assert(B.getY() == 51);

        C.shift(1, 5);
        assert(C.getX() == 2);
        assert(C.getY() == 17);
    }

    {
        Point A{ 12, 17, 4 };
        Point B{ 12, 17, 4 };
        Point C{ 1, 12, 5 };
        assert(A == B);
        assert(A != C);
        assert(B != C);

        A.scaleX(2);
        assert(A.getX() == 24);

        B.scaleY(3);
        assert(B.getY() == 51);

        C.scaleZ(2);
        assert(C.getZ() == 10);

        C.shift(1, 5, 3);
        assert(C.getX() == 2);
        assert(C.getY() == 17);
        assert(C.getZ() == 13);
    }
}

void tests::testLine()
{
    Point A{ 12, 17 };
    Point B{ 1, 12 };

    Line l{ A, B };
    assert(l.getType() == ShapeType::LINE);
    assert(l.getArea() == 0.0);
    assert(l.getVolume() == 0.0);
}

void tests::testRectangle()
{
    Point A{ 0, 0 };
    Point B{ 12, 0 };
    Point C{ 12, 17 };
    Point D{ 0, 17 };

    Rectangle r{ {A, B, C, D} };
    assert(r.getType() == ShapeType::RECTANGLE);
    assert(r.getArea() == 204.0);
    assert(r.getVolume() == 0.0);

    Rectangle r2{ {D, C, B, A} };
    assert(r.getType() == r2.getType());
    assert(r.getArea() == r2.getArea());
    assert(r.getVolume() == r2.getVolume());
}

void tests::testParallelepiped()
{
    Point A{ 0, 0, 0 };
    Point B{ 12, 0, 0 };
    Point C{ 12, 17, 0 };
    Point D{ 0, 17, 0 };
    Point E{ 0, 0, 1 };
    Point F{ 12, 0, 1 };
    Point G{ 12, 17, 1 };
    Point H{ 0, 17, 1 };

    Parallelepiped p{ {A, B, C, D, E, F, G, H} };
    assert(p.getType() == ShapeType::PARALLELPIPED);
    assert(p.getArea() == 466.0);
    assert(p.getVolume() == 204.0);

    Parallelepiped p2{ {H, G, F, E, A, B, C, D} };
    assert(p.getType() == p2.getType());
    assert(p.getArea() == p2.getArea());
    assert(p.getVolume() == p2.getVolume());
}

void tests::testCircle()
{
    const Point center{ 0, 0 };
    const double radius = 17.0;

    Circle c{ center, radius};
    assert(c.getType() == ShapeType::CIRCLE);
    assert(tools::areEqual(c.getArea(), 907.92028));
    assert(c.getVolume() == 0.0);
}

void tests::testCylinder()
{
    const Point center{ 0, 0, 0 };
    const double radius = 17.0;
    const double height = 12.0;

    Cylinder c{ center, radius, height };
    assert(c.getType() == ShapeType::CYLINDER);
    assert(tools::areEqual(c.getArea(), 3097.61036));
    assert(tools::areEqual(c.getVolume(), 10895.04332));
}

void tests::testTransform()
{
    using namespace transformation;

    {
        Point A{ 12, 17 };
        Point B{ 1, 12 };

        Line l{ A, B };
        Transform<Line> tr{ l };

        Line l1 = tr.scaleX(2);
        Line l1_answ{ {24, 17}, {2, 12} };
        assert(l1_answ == l1);
        assert(l1.getType() == ShapeType::LINE);

        Line l2 = tr.scaleY(2);
        Line l2_answ{ {12, 34}, {1, 24} };
        assert(l2_answ == l2);

        Line l3 = tr.scaleZ(3);
        assert(l == l3);

        Line l4 = tr.scale(4);
        Line l4_answ{ {48, 68}, {4, 48} };
        assert(l4_answ == l4);

        Line l5 = tr.shift(5, -6, 7);
        Line l5_answ{ {17, 11}, {6, 6} }; 
        assert(l5_answ == l5);
    }

    {
        Point A{ 0, 0 };
        Point B{ 12, 0 };
        Point C{ 12, 17 };
        Point D{ 0, 17 };

        Rectangle r{ {A, B, C, D} };
        Transform<Rectangle> tr{ r };

        Rectangle r1 = tr.scaleX(2);
        Rectangle r1_answ{ {{0, 0}, {24, 0}, {24, 17}, {0, 17}} };
        assert(r1_answ == r1);
        assert(r1.getType() == ShapeType::RECTANGLE);

        Rectangle r2 = tr.scaleY(2);
        Rectangle r2_answ{ {{0, 0}, {12, 0}, {12, 34}, {0, 34}} };
        assert(r2_answ == r2);

        Rectangle r3 = tr.scaleZ(3);
        assert(r == r3);

        Rectangle r4 = tr.scale(4);
        Rectangle r4_answ{ {{0, 0}, {48, 0}, {48, 68}, {0, 68}} };
        assert(r4_answ == r4);

        Rectangle r5 = tr.shift(5, -6, 7);
        Rectangle r5_answ{ {{5, -6}, {17, -6}, {17, 11}, {5, 11}} };
        assert(r5_answ == r5);
    }

    {
        Point A{ 0, 0, 0 };
        Point B{ 12, 0, 0 };
        Point C{ 12, 17, 0 };
        Point D{ 0, 17, 0 };
        Point E{ 0, 0, 1 };
        Point F{ 12, 0, 1 };
        Point G{ 12, 17, 1 };
        Point H{ 0, 17, 1 };

        Parallelepiped p{ {A, B, C, D, E, F, G, H} };
        Transform<Parallelepiped> tr{ p };

        Parallelepiped p1 = tr.scaleX(2);
        Parallelepiped p1_answ{ {{ 0, 0, 0 }, { 24, 0, 0 }, { 24, 17, 0 }, { 0, 17, 0 },
                                 { 0, 0, 1 }, { 24, 0, 1 }, { 24, 17, 1 }, { 0, 17, 1 }} };
        assert(p1_answ == p1);
        assert(p1.getType() == ShapeType::PARALLELPIPED);

        Parallelepiped p2 = tr.scaleY(2);
        Parallelepiped p2_answ{ {{ 0, 0, 0 }, { 12, 0, 0 }, { 12, 34, 0 }, { 0, 34, 0 },
                                 { 0, 0, 1 }, { 12, 0, 1 }, { 12, 34, 1 }, { 0, 34, 1 }} };
        assert(p2_answ == p2);

        Parallelepiped p3 = tr.scaleZ(3);
        Parallelepiped p3_answ{ {{ 0, 0, 0 }, { 12, 0, 0 }, { 12, 17, 0 }, { 0, 17, 0 },
                                 { 0, 0, 3 }, { 12, 0, 3 }, { 12, 17, 3 }, { 0, 17, 3 }} };
        assert(p3_answ == p3);

        Parallelepiped p4 = tr.scale(4);
        Parallelepiped p4_answ{ {{ 0, 0, 0 }, { 48, 0, 0 }, { 48, 68, 0 }, { 0, 68, 0 },
                                 { 0, 0, 4 }, { 48, 0, 4 }, { 48, 68, 4 }, { 0, 68, 4 }} };
        assert(p4_answ == p4);

        Parallelepiped p5 = tr.shift(5, -6, 7);
        Parallelepiped p5_answ{ {{ 5, -6, 7 }, { 17, -6, 7 }, { 17, 11, 7 }, { 5, 11, 7 },
                                 { 5, -6, 8 }, { 17, -6, 8 }, { 17, 11, 8 }, { 5, 11, 8 }} };
        assert(p5_answ == p5);
    }

    {
        const Point center{ 0, 0 };
        const double radius = 17.0;

        Circle c{ center, radius };
        Transform<Circle> tr{ c };

        Circle c1 = tr.scaleX(1);
        assert(c == c1);
        assert(c1.getType() == ShapeType::CIRCLE);

        Circle c2 = tr.scaleY(2);
        assert(c == c2);

        Circle c3 = tr.scaleZ(3);
        assert(c == c3);

        Circle c4 = tr.scale(4);
        assert(c == c4);

        Circle c5 = tr.shift(5, 6, 7);
        assert(c == c5);
    }

    {
        const Point center{ 0, 0, 0 };
        const double radius = 17.0;
        const double height = 12.0;

        Cylinder c{ center, radius, height };
        Transform<Cylinder> tr{ c };

        Cylinder c1 = tr.scaleX(1);
        assert(c == c1);
        assert(c1.getType() == ShapeType::CYLINDER);

        Cylinder c2 = tr.scaleY(2);
        assert(c == c2);

        Cylinder c3 = tr.scaleZ(3);
        assert(c == c3);

        Cylinder c4 = tr.scale(4);
        assert(c == c4);

        Cylinder c5 = tr.shift(5, 6, 7);
        assert(c == c5);
    }
}