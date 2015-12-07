// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include<stdio.h>
#include<iostream>


//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE
	float rd = (90.0*pi / 180.0);
	mat3 second_mat = glm::mat3(
		glm::vec3(axis.x*axis.x, axis.x*axis.y, axis.x*axis.z),
		glm::vec3(axis.x*axis.y, axis.y*axis.y, axis.y*axis.z),
		glm::vec3(axis.x*axis.z, axis.y*axis.z, axis.z*axis.z));
	mat3 third_mat = glm::mat3(
		glm::vec3(0.0f, -axis.z, axis.y),
		glm::vec3(axis.z, 0.0f, -axis.x),
		glm::vec3(-axis.y, axis.x, 0.0f));
	mat3 rts = mat3((cos(glm::radians(degrees)))*mat3(1.0) + (1 - cos(glm::radians(degrees))*second_mat) + (sin(glm::radians(degrees))*third_mat));

	/*mat4 rot=glm::rotate(,degrees, axis);
	std::cout<<rts[0][0]<<rts[0][1]<<rts[0][2]<<std::endl;
	std::cout << rts[1][0] << rts[1][1] << rts[1][2] << std::endl;
	std::cout << rts[2][0] << rts[2][1] << rts[2][2] << std::endl;*/
  // You will change this return call
  return mat3(rts);
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE

	vec3 e = eye - vec3(.001f, 0.01f, .01f);
	vec3 upv = glm::normalize(glm::cross(up, e));
		//eye=e* rotate(degrees, upv);
	up = glm::normalize(up * rotate(degrees, upv));
	printf("Left Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", 
		eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
	
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE 
	vec3 e =( eye - vec3(.001f, 0.001f, .001f));
	vec3 upv = glm::normalize(glm::cross(up, e));
	eye =eye * rotate(degrees, upv);
	up = up * rotate(degrees, upv);
	mat4 m;
	glm::rotate(m, glm::radians(degrees), upv);
	

	printf("Up Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n",
		eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	/*vec3 a = eye - vec3(.01, .01, .01);
	vec3 w = glm::normalize(a);
	vec3 b = up;
	vec3 u= glm::normalize(glm::cross(b, w));
	vec3 v = glm::cross(w, u);
	mat3 R = glm::transpose(mat3(w, u, v));
	mat4 view = mat4(R);
	view[3][3] = 1.0f;
	mat4 i = mat4(1.0f);
	i[3] = vec4(-eye, 1.0f);
	view = glm::mat4(view*i);
	return view;*/
	glm::mat4 view = glm::lookAt(
		glm::vec3(eye),
		glm::vec3(glm::normalize(eye)),
		glm::vec3(up)
		);
	return view;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
