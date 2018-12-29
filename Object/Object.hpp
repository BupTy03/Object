#pragma once
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include<iostream>
#include<list>

namespace my
{
	class Object
	{
	public:
		Object(Object* parent = nullptr) : id_{ ++counter_ }
		{
			if (parent == nullptr) return;
			parent->addChild(this);
			parent_ = parent;
		}
		virtual ~Object()
		{
			std::cout << "Object with id: " << id_ << ": ~Object() (destructor) " << std::endl;
			for (Object* ptr : children_)
				delete ptr;
		}

		Object(const Object&) = delete;
		Object(Object&&) = delete;

		Object& operator=(const Object&) = delete;
		Object& operator=(Object&&) = delete;

		virtual Object* clone() { return new Object(parent_); }
		void setParent(Object* parent)
		{
			if (parent == nullptr) return;
			if (std::find(std::cbegin(parent->children_),
				std::cend(parent->children_), this) != std::cend(parent->children_))
				return;

			parent->addChild(this);
			parent_ = parent;
		}
		int getId() const { return id_; }

	protected:
		Object* parent_{};

	private:
		static int counter_;
		int id_{};
		std::list<Object*> children_;
		void addChild(Object* child)
		{
			if (child == nullptr) return;
			children_.push_back(child);
		}
	};

	int Object::counter_ = 0;
}

#endif // !OBJECT_HPP