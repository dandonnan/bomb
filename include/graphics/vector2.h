#ifndef Vector2_H
#define Vector2_H

// A definition for a 2D vector.
class Vector2
{
    public:
        Vector2();
        Vector2(int x, int y);
        ~Vector2();
        int X();
        int Y();

    private:
        int x;
        int y;
};

#endif // Vector2_H