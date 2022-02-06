#ifndef MY_OBJECT_CONTAINER_H
#define MY_OBJECT_CONTAINER_H

#include <glad/glad.h>
#include <vector>
#include <array>
#include <utility>
#include <algorithm>

typedef void (APIENTRYP _my_gen_proc)(GLsizei n, GLuint* objects);
typedef void (APIENTRYP _my_del_proc)(GLsizei n, const GLuint* objects);


template <typename _Container = std::vector<GLuint>>
class GLObjectContainer;

using GLObjectContainerV = GLObjectContainer<>;
template <size_t N>
using GLObjectContainerArr = GLObjectContainer<std::array<GLuint, N>>;

template <typename _Container>
struct GLObjectContainerBase
{
	_Container container;

	_my_gen_proc generator;
	_my_del_proc deleter;

	void generate() {
		generator(container.size(), container.data());
	}
	void destroy() {
		deleter(container.size(), container.data());
	}
};

template <typename _Container>
class GLObjectContainer
{
public:
	using const_iterator = typename _Container::const_iterator;
	using const_reverse_iterator = typename _Container::const_reverse_iterator;
public:
	template <typename ... Types>
	GLObjectContainer(_my_gen_proc _generator, _my_del_proc _deleter, Types&& ... _args);
	GLObjectContainer(GLObjectContainer&& other);

	GLObjectContainer& operator=(GLObjectContainer&& other);

	_my_gen_proc generator() const {
		return mem.generator;
	}
	_my_del_proc deleter() const {
		return mem.deleter;
	}

	auto size() const {
		return mem.container.size();
	}

	auto data() const {
		return mem.container.data();
	}

	GLuint get_obj(size_t idx) {
		return mem.container[idx];
	}
	void set_obj(size_t idx, GLuint obj) {
		mem.deleter(1, mem.container[idx]);
		mem.container[idx] = obj;
	}

	const_iterator begin() const {
		return mem.container.begin();
	}
	const_iterator end() const {
		return mem.container.end();
	}
	const_iterator cbegin() const {
		return mem.container.cbegin();
	}
	const_iterator cend() const {
		return mem.container.cend();
	}
	const_reverse_iterator crbegin() const {
		return mem.container.rbegin();
	}
	const_reverse_iterator crend() const {
		return mem.container.rend();
	}

	~GLObjectContainer() {
		mem.destroy();
	}

private:
	GLObjectContainerBase< _Container> mem;
};

template <typename _C>
template <typename ... Types>
GLObjectContainer< _C>::GLObjectContainer(_my_gen_proc _generator, _my_del_proc _deleter, Types&& ... _args)
	: mem{_C(std::forward<Types>(_args)...), _generator, _deleter}
{
	mem.generate();
}

template <typename _Container>
GLObjectContainer< _Container>::GLObjectContainer(GLObjectContainer&& other)
	: mem(std::move(other.mem))
{
	for (GLuint& id : other.mem.container)
		id = 0;
}

template <typename _C>
GLObjectContainer< _C>& GLObjectContainer< _C>::operator=(GLObjectContainer&& other)
{
	if (this == &other) return *this;

	mem.destroy();
	mem = std::move(other.mem);

	for (GLuint& id : other.mem.container)
		id = 0;

	return *this;
}

#endif // MY_OBJECT_CONTAINER_H