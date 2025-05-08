#include <math.h>

#include "vec2.h"

Vec2 vec2Add(const Vec2 a, const Vec2 b) {
	return (Vec2){.x = a.x + b.x, .y = a.y + b.y};
}

Vec2 vec2Subtract(const Vec2 a, const Vec2 b) {
	return (Vec2){.x = a.x - b.x, .y = a.y - b.y};
}

Vec2 vec2Multiply(const Vec2 v, const float scalar) {
	return (Vec2){.x = v.x * scalar, .y = v.y * scalar};
}

float vec2Length(const Vec2 v) {
	return sqrtf(powf(v.x, 2) + powf(v.y, 2));
}

Vec2 vec2Normalize(const Vec2 v) {
	const float len = vec2Length(v);

	return (Vec2){.x = v.x / len, .y = v.y / len};
}

float vec2Distance(const Vec2 a, const Vec2 b) {
	const Vec2 v = vec2Subtract(a, b);

	return vec2Length(v);
}
