#ifndef POINTDDD_H
#define POINTDDD_H

class PointDDD
{
private:
    float m_x;
    float m_y;
    float m_z;
public:
    PointDDD();
    PointDDD(float x,float y ,float z);
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setPoint(float x, float y, float z);
    float getX() const;
    float getY() const;
    float getZ() const;
};

#endif // POINTDDD_H
