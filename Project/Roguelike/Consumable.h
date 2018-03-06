#pragma once
class Consumable {
public:
	void consume();
	std::string returnType() const { return consumableType; }
private:
	std::string consumableType;
};

