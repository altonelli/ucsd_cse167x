// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include <iostream>
#include "glm/gtx/string_cast.hpp"


//Please implement the following functions:

// Helper rotation function.
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	// YOUR CODE FOR HW1 HERE
	vec3 axis_p = axis;
	float radians = degrees_to_radians(degrees);
 	mat3 cos_i = mat3(cos(radians));
	mat3 aat = outerProduct(axis_p, axis_p);
	mat3 component_along_a = (1 - cos(radians)) * aat;
	mat3 c_t = Transform::conjugate_transpose(axis_p);
	mat3 component_perp_to_a = sin(radians) * c_t;
	mat3 rotation = cos_i + component_along_a + component_perp_to_a;
	// You will change this return call
	return rotation;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE
	vec3 axis = up;
	mat3 rotation_matrix = Transform::rotate(degrees, axis);
	eye = rotation_matrix * eye;
	// printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE
	vec3 left = vec3(1, 0, 0);
	// vec3 axis = left;
	vec3 axis = normalize(cross(eye, up));
	// printf("axis: %.2f, %.2f, %.2f; \n", axis.x, axis.y, axis.z);
	mat3 rotation_matrix = Transform::rotate(degrees, axis);
	eye = rotation_matrix * eye;
	up = normalize(cross(axis, eye));
	// printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	// YOUR CODE FOR HW1 HERE
	vec3 a = eye - vec3(0.0, 0.0, 0.0);

	vec3 b = up;
	vec3 w = normalize(a);
	vec3 u = normalize(cross(b, w));
	vec3 v = normalize(cross(w, u));

	mat4 r = mat4(u[0], v[0], w[0], 0.0,
								u[1], v[1], w[1], 0.0,
								u[2], v[2], w[2], 0.0,
								 0.0,  0.0,  0.0, 1.0);
	mat4 t = mat4(1.0, 0.0, 0.0, 0.0,
								0.0, 1.0, 0.0, 0.0,
								0.0, 0.0, 1.0, 0.0,
								-eye[0], -eye[1], -eye[2], 1.0);

	mat4 r_t = r * t;
	std::cout<<glm::to_string(r)<<std::endl;
	std::cout<<glm::to_string(t)<<std::endl;
	std::cout<<glm::to_string(r_t)<<std::endl;

	// You will change this return call
	return r_t;
}

mat3 Transform::conjugate_transpose(vec3& vector) {
	float x = vector[0];
	float y = vector[1];
	float z = vector[2];
	mat3 c_t = mat3(0.0, z, -y, -z, 0.0, x, y, -x, 0.0);
	return c_t;
}

float Transform::degrees_to_radians(float degrees) {
	float radians = (degrees / 360.0) * 2 * pi;
	return radians;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}


