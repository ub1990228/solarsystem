//
//  star.hpp
//  solarsystem
//
//  Created by Changkun Ou on 16/06/07.
//  Copyright © 2016 Shiyanlou.com. All rights reserved.
//
#ifndef star_hpp
#define star_hpp

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

class Star {
public:
    GLfloat radius;
    GLfloat speed, selfSpeed;
    GLfloat distance;
    GLfloat rgbaColor[4];

    Star* parentStar;

    Star(GLfloat radius, GLfloat distance,
         GLfloat speed,  GLfloat selfSpeed,
         Star* parent);
    void drawStar();
    virtual void draw() { drawStar(); }
    virtual void update(long timeSpan);
protected:
    GLfloat alphaSelf, alpha;
};

class Planet : public Star {
public:
    Planet(GLfloat radius, GLfloat distance,
           GLfloat speed,  GLfloat selfSpeed,
           Star* parent, GLfloat rgbColor[3]);
    void drawPlanet();
    virtual void draw() { drawPlanet(); drawStar(); }
};

class LightPlanet : public Planet {
public:
    LightPlanet(GLfloat Radius, GLfloat Distance,
                GLfloat Speed,  GLfloat SelfSpeed,
                Star* Parent, GLfloat rgbColor[]);
    void drawLight();
    virtual void draw() { drawLight(); drawPlanet(); drawStar(); }
};

#endif /* star_hpp */
