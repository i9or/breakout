#ifndef VEC2_H
#define VEC2_H

typedef struct Vec2 {
	float x;
	float y;
} Vec2;

Vec2 vec2Add(Vec2 a, Vec2 b);
Vec2 vec2Subtract(Vec2 a, Vec2 b);
Vec2 vec2Multiply(Vec2 v, float scalar);
float vec2Length(Vec2 v);
Vec2 vec2Normalize(Vec2 v);
float vec2Distance(Vec2 a, Vec2 b);

#endif // VEC2_H
