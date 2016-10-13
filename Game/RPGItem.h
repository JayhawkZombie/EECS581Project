#pragma once
#include <string>
class RPGItem
{
public:
	//constructor-destructor
	RPGItem();
	~RPGItem();

	//Getters-Setters
	std::string getName() const;
	std::string getDescription() const;
	int getValue() const;
	int getId() const;

	void setName(std::string name);
	void setDescription(std::string description);
	void setValue(int value);
	void setId(int id);

	//Other Methods
	void InitializeRPGItem();
//	static int HowMany();//returns the number of items
//	static RPGItem* get();//returns a pointer to the
	//base of the array of length Num() that holds 
	//All of the RPGItem objects
private:
//	RPGItem* arrayBase;
//	static int num;
	std::string m_name;
	std::string m_description;
	int m_value;
	int m_id;
};

