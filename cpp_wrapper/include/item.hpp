#ifndef Chaussette_hpp_
	#define Chaussette_hpp_

	#include <string>
	extern "C"{
		#include <Chaussette/lipsite.h>
	}

	namespace cht{
		class item{
		public:
			item();
			item(std::string);
			item(std::string file, std::string elem, std::string value);
			item(item &);
			~item();
			void 			dump();
			bool 			get();
			std::string 		getValue(std::string);
			bool 			setSearch(std::string elem, std::string value);
			bool 			setFile(std::string);
			std::string		operator[](std::string);
			item 			operator=(item &);
			friend std::ostream 	&operator<<(std::ostream &stream, const item &item);
			std::string 		getFile();
			std::string 		getElem();
			std::string 		getSearchValue();
			size_t	 		getSize();
			const t_item		*getItemList();
		private:
			t_item 		*_item;
			std::string 	_file;
			std::string	_elem;
			std::string	_value;
			size_t		_size;
		};
	};



#endif