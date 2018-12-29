#pragma once
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include<list>

namespace my
{
	class Object
	{
	public:
		Object(Object* parent = nullptr)
		{
			if (parent == nullptr) return;
			parent->addChild(this);
		}
		virtual ~Object()
		{
			for (Object* ptr : children_)
				delete ptr;
		}

		Object() = delete;
		Object(const Object&) = delete;
		Object(Object&&) = delete;

		Object& operator=(const Object&) = delete;
		Object& operator=(Object&&) = delete;

		virtual Object* clone() { return new Object(this); }
		void setParent(Object* parent)
		{
			if (parent == nullptr) return;
			if (std::find(std::cbegin(parent->children_),
				std::cend(parent->children_), this) != std::cend(parent->children_))
				return;

			parent->addChild(this);
		}
		int getId() const { return id; }

	private:
		static int id;
		std::list<Object*> children_;
		void addChild(Object* child)
		{
			if (child == nullptr) return;
			children_.push_back(child);
		}
	};

	int Object::id = 0;
}

#endif // !OBJECT_HPP