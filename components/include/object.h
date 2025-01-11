#pragma once

#include "../components.h"
#include <string>
#include <unordered_map>
#include <iostream>

namespace components {
	class object {
	public:
		class base_component {
		public:
			object* gameObj;
			base_component();
			virtual void updateGameObj();
			virtual void update();
			virtual ~base_component();
			virtual std::string toString();
		};

		int layer;
		std::string name;
		ObjectType objType;

		object(const char* name = "Unnamed", int layer = 0, ObjectType objType = ObjectType::BASE);
		virtual void update();

		object gameObject();
		int get_layer();
		void set_layer(int layer);
		std::string get_name();
		void set_name(std::string name);
		std::vector<base_component*> getComponentsList();

		template<typename T>
		T* get_component() {
			auto it = components.find(typeid(T).name());
			if (it != components.end()) {
				return dynamic_cast<T*>(it->second);
			}
			return nullptr;
		}

		template<typename T>
		bool has_component() {
			auto it = components.find(typeid(T).name());
			if (it != components.end()) {
				return true;
			}
			return false;
		}

		template<typename T, typename... Args>
		T* add_component(Args&&... args) {
			T* component = new T(std::forward<Args>(args)...);
			components[typeid(T).name()] = component;
			components[typeid(T).name()]->gameObj = this;
			components[typeid(T).name()]->updateGameObj();
			return component;
		}

	private:
		std::unordered_map<std::string, base_component*> components;
	};
}