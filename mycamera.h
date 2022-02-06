#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class MyCamera
{
public:
	using vec3 = glm::vec3;
public:
	MyCamera() {}
	MyCamera(const vec3& _pos, const vec3& _targ, const vec3& _up);

	vec3& vpos() {
		return m_pos;
	}
	const vec3& vpos() const {
		return m_pos;
	}
	vec3& vtarg() {
		return m_target;
	}
	const vec3& vtarg() const {
		return m_target;
	}
	vec3& vup() {
		return m_up;
	}
	const vec3& vup() const {
		return m_up;
	}
	
	glm::mat4 look_at() const {
		return glm::lookAt(m_pos, m_pos + m_target, m_up);
	}

	glm::mat4 look_at2() const {
		glm::mat4 lookat;

		auto direction = glm::normalize(m_pos + m_target);

		lookat = glm::translate(lookat, m_pos);
	}

	void front(float speed) {
		m_pos += speed * m_target;
	}
	void back(float speed) {
		m_pos -= speed * m_target;
	}

	void forward(float speed) {
		m_pos += speed * glm::normalize(glm::vec3(m_target.x, 0, m_target.z));
	}
	void backward(float speed) {
		m_pos -= speed * glm::normalize(glm::vec3(m_target.x, 0, m_target.z));
	}

	void goleft(float speed) {
		m_pos -= glm::normalize(glm::cross(m_target, m_up)) * speed;
	}
	void goright(float speed) {
		m_pos += glm::normalize(glm::cross(m_target, m_up)) * speed;
	}

	void upper(float speed) {
		m_pos.y += speed;
	}
	void lower(float speed) {
		m_pos.y -= speed;
	}

private:
	vec3 m_pos;
	vec3 m_target;
	vec3 m_up;
};