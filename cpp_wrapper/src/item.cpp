#include <iostream>
#include "item.hpp"

cht::item::item()
{
	this->_item = createItem();
}

cht::item::item(std::string file) : _file(file), _size(0)
{
	this->_item = createItem();
	setFileLink(const_cast<char*>(file.c_str()));
}

cht::item::item(std::string file, std::string elem, std::string value) : _file(file), _elem(elem), _value(value), _size(0)
{
	this->_item = createItem();
	setFileLink(const_cast<char*>(file.c_str()));
	setItemInfo(const_cast<char*>(elem.c_str()), const_cast<char*>(value.c_str()));
}

cht::item::item(cht::item &other) : _file(other.getFile()), _elem(other.getElem()), _value(other.getSearchValue()), _size(other.getSize())
{
	this->_item = copyItem(other.getItemList());
}

cht::item::~item()
{
	freeItem(this->_item);
}

bool cht::item::get()
{
	setFileLink(const_cast<char*>(this->_file.c_str()));
	setItemInfo(const_cast<char*>(this->_elem.c_str()), const_cast<char*>(this->_value.c_str()));
	this->_item = findItem(this->_item);
	if (this->_item == NULL)
		return (false);
	return (true);
}

void cht::item::dump()
{
	promptItem(this->_item);
}

std::string cht::item::getValue(std::string elem)
{
	std::string tmp(InItem(this->_item, const_cast<char*>(elem.c_str())));

	return (tmp);
}

bool cht::item::setSearch(std::string elem, std::string value)
{
	this->_elem = elem;
	this->_value = value;
	return (true);
}

bool cht::item::setFile(std::string file)
{
	this->_file = file;
	return (true);
}

std::string	cht::item::operator[](std::string elem)
{
	return this->getValue(elem);
}

cht::item cht::item::operator=(cht::item &other)
{
	this->_file = other.getFile();
	this->_elem = other.getElem();
	this->_value = other.getSearchValue();
	this->_size = other.getSize();
	return (*this);
}

namespace cht{
	std::ostream 	&operator<<(std::ostream &stream, const cht::item &item)
	{
		int i;

		i = 0;
		stream << "file : " << item._file << "\nelem : " << item._elem;
		stream << "\nvalue searched : " << item._value;
		stream << "\ndump of item :\n";
		while (item._item[i].element && item._item[i].value){
			stream << '\t' << item._item[i].element << " | " << item._item[i].value << std::endl;
			i++;
		}
		return (stream);
	}
};

std::string cht::item::getFile()
{
	return this->_file;
}

std::string cht::item::getElem()
{
	return this->_file;
}

std::string cht::item::getSearchValue()
{
	return this->_value;
}

size_t cht::item::getSize()
{
	return this->_size;
}

const t_item	*cht::item::getItemList()
{
	return this->_item;
}