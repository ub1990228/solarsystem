//
//  star.cpp
//  solarsystem
//
//  Created by Changkun Ou on 16/06/07.
//  Copyright © 2016 Shiyanlou.com. All rights reserved.
//
#include "stars.hpp"
#include <cmath>

#define PI 3.1415926535

Star::Star(GLfloat radius, GLfloat distance,
           GLfloat speed,  GLfloat selfSpeed,
           Star* parent) {
    this->radius = radius;
    this->selfSpeed = selfSpeed;
    this->alphaSelf = this->alpha = 0;
    this->distance = distance;

    for (int i = 0; i < 4; i++)
        this->rgbaColor[i] = 1.0f;

    this->parentStar = parent;
    if (speed > 0)
        this->speed = 360.0f / speed;
    else
        this->speed = 0.0f;
}

void Star::drawStar() {

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);

    int n = 1440;

    glPushMatrix();
    {
        // 公转

        // 如果是行星，且距离不为0，那么 且向原点平移一个半径
        // 这部分用于处理卫星
        if (parentStar != 0 && parentStar->distance > 0) {
            //将绘制的图形沿 z 轴旋转 alpha
            glRotatef(parentStar->alpha, 0, 0, 1);
            // x 轴方向上平移 distance , y,z 方向不变
            glTranslatef(parentStar->distance, 0.0, 0.0);
        }
        // 绘制运行轨道
        glBegin(GL_LINES);
        for(int i=0; i<n; ++i)
            glVertex2f(distance * cos(2 * PI * i / n),
                       distance * sin(2 * PI * i / n));
        glEnd();
        // 绕 z 轴旋转 alpha
        glRotatef(alpha, 0, 0, 1);
        // x 轴方向平移 distance, y,z 方向不变
        glTranslatef(distance, 0.0, 0.0);

        // 自转
        glRotatef(alphaSelf, 0, 0, 1);

        // 绘制行星颜色
        glColor3f(rgbaColor[0], rgbaColor[1], rgbaColor[2]);
        glutSolidSphere(radius, 40, 32);
    }
    glPopMatrix();

}

void Star::update(long timeSpan) {
    alpha += timeSpan * speed;  // 更新角度
    alphaSelf += selfSpeed;     // 更新自转角度
}


Planet::Planet(GLfloat radius, GLfloat distance,
               GLfloat speed,  GLfloat selfSpeed,
               Star* parent, GLfloat rgbColor[3]) :
Star(radius, distance, speed, selfSpeed, parent) {
    rgbaColor[0] = rgbColor[0];
    rgbaColor[1] = rgbColor[1];
    rgbaColor[2] = rgbColor[2];
    rgbaColor[3] = 1.0f;
}

void Planet::drawPlanet() {
    GLfloat mat_ambient[]  = {0.0f, 0.0f, 0.5f, 1.0f};
    GLfloat mat_diffuse[]  = {0.0f, 0.0f, 0.5f, 1.0f};
    GLfloat mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
    GLfloat mat_emission[] = {rgbaColor[0], rgbaColor[1], rgbaColor[2], rgbaColor[3]};
    GLfloat mat_shininess  = 90.0f; // 发光

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,  mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, mat_shininess);
}

LightPlanet::LightPlanet(GLfloat radius,    GLfloat distance, GLfloat speed,
                         GLfloat selfSpeed, Star* parent,   GLfloat rgbColor[3]) :
Planet(radius, distance, speed, selfSpeed, parent, rgbColor) {
    ;
}

void LightPlanet::drawLight() {

    GLfloat light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat light_ambient[]  = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat light_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); // 指定零号光源的位置
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);  // 表示各种光线照射到该材质上，经过很多次反射后追踪遗留在环境中的光线强度
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);  // 漫反射后的光照强度
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); // 镜面反射后的光照强度

}
