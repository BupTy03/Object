#pragma once
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include<list>
#include<functional>
#include<utility>
#include<stdexcept>
#include<mutex>

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
			std::lock_guard<std::mutex> lock_(mutex_);
			for (std::function<void()>* handler : handlers_)
				(*handler)();

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
		void setOnDelete(std::function<void()> handler)
		{
			std::lock_guard<std::mutex> lock_(mutex_);
			std::function<void()>* func_ptr{nullptr};
			try {
				func_ptr = new std::function<void()>(std::move(handler));
				handlers_.push_back(func_ptr);
			}
			catch (...) {
				if (func_ptr != nullptr)
				{
					handlers_.remove(func_ptr);
					delete func_ptr;
				}
				throw std::runtime_error{ "setOnDelete failed" };
			}
		}
	protected:
		Object* parent_{};

	private:
		void addChild(Object* child)
		{
			if (child == nullptr) return;
			children_.push_back(child);
		}

	private:
		static int counter_;
		int id_{};
		std::list<Object*> children_;
		mutable std::mutex mutex_;
		std::list<std::function<void()>*> handlers_;
	};

	int Object::counter_ = 0;
}

#endif // !OBJECT_HPP