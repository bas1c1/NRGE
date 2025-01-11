#include "../include/object.h"

components::object::base_component::base_component() = default;
components::object::base_component::~base_component() = default;
void components::object::base_component::updateGameObj() {};
void components::object::base_component::update() {};
std::string components::object::base_component::toString() { return std::string("default component"); };

components::object::object(const char* name, int layer, ObjectType objType) {
	this->layer = layer;
	this->objType = objType;
	this->name = std::string(name);
}

void components::object::update() {
	for (auto component : components) {
		component.second->update();
	}
}

components::object components::object::gameObject() { return *this; }

int components::object::get_layer() {
	return this->layer;
}

void components::object::set_layer(int layer) {
	this->layer = layer;
}

std::string components::object::get_name() {
	return this->name;
}

void components::object::set_name(std::string name) {
	this->name = name;
}

std::vector<components::object::base_component*> components::object::getComponentsList() {
	std::vector<base_component*> tmp = std::vector<base_component*>();
	for (auto& it : components) {
		tmp.push_back(it.second);
	}
	return tmp;
}

/*template<typename T>
T* components::object::get_component() {
	auto it = components.find(typeid(T).name());
	if (it != components.end()) {
		return dynamic_cast<T*>(it->second);
	}
	return nullptr;
}

template<typename T>
bool components::object::has_component() {
	auto it = components.find(typeid(T).name());
	if (it != components.end()) {
		return true;
	}
	return false;
}

template<typename T, typename... Args>
T* components::object::add_component(Args&&... args) {
	T* component = new T(std::forward<Args>(args)...);
	components[typeid(T).name()] = component;
	components[typeid(T).name()]->gameObj = this;
	return component;
}*/