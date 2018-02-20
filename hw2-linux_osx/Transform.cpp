// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
  mat3 ret;
  // YOUR CODE FOR HW2 HERE
  // Please implement this.  Likely the same as in HW 1.
  float radians = (degrees / 360.0) * 2 * pi;
  mat3 cos_i = mat3(cos(radians));
  mat3 aat = outerProduct(axis, axis);
  mat3 comp_along_axis = (1 - cos(radians)) * aat;
  mat3 c_t = Transform::conjugate_transpose(axis);
  mat3 comp_perp_to_axis = sin(radians) * c_t;
  ret = cos_i + comp_along_axis + comp_perp_to_axis;

  return ret;
}

void Transform::left(float degrees, vec3& eye, vec3& up)
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.
  mat3 rotation = Transform::rotate(degrees, up);
  eye = rotation * eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up)
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.
  vec3 axis = normalize(cross(eye, up));
  mat3 rotation = Transform::rotate(degrees, axis);
  eye = rotation * eye;
  up = normalize(cross(axis, eye));
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.
  vec3 a = eye - center;
  vec3 b = up;
  vec3 w = normalize(a);
  vec3 u = normalize(cross(b, w));
  vec3 v = normalize(cross(w, u));

  mat4 r = mat4(
                u[0], v[0], w[0], 0.0,
                u[1], v[1], w[1], 0.0,
                u[2], v[2], w[2], 0.0,
                0.0,  0.0,  0.0,  1.0
              );
  mat4 t = Transform::translate(-eye.x, -eye.y, -eye.z);
  ret = r * t;
  return ret;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // New, to implement the perspective transform as well.
  float d = cos(fovy / 2) / sin(fovy / 2);
  float a = -((zFar + zNear) / (zFar - zNear));
  float b = -((2 * zFar * zNear) / (zFar - zNear));

  ret = mat4(
             d / aspect, 0.0, 0.0, 0.0,
             0.0,        d,   0.0, 0.0,
             0.0,        0.0, a,   -1.0,
             0.0,        0.0, b,   0.0
           );
  return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
  // mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // Implement scaling
  mat4 ret = mat4(
                sx,  0.0, 0.0, 0.0,
                0.0, sy,  0.0, 0.0,
                0.0, 0.0, sz,  0.0,
                0.0, 0.0, 0.0, 1.0
              );
  return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
  // mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // Implement translation
  mat4 ret = mat4(
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                tx,  ty,  tz,  1.0
              );
  return ret;
}

// To normalize the up direction and construct a coordinate frame.
// As discussed in the lecture.  May be relevant to create a properly
// orthogonal and normalized up.
// This function is provided as a helper, in case you want to use it.
// Using this function (in readfile.cpp or display.cpp) is optional.

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec)
{
  vec3 x = glm::cross(up,zvec);
  vec3 y = glm::cross(zvec,x);
  vec3 ret = glm::normalize(y);
  return ret;
}


// Privates
mat3 Transform::conjugate_transpose(const vec3& vector) {
	float x = vector[0];
	float y = vector[1];
	float z = vector[2];
	mat3 c_t = mat3(0.0, z, -y, -z, 0.0, x, y, -x, 0.0);
	return c_t;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
