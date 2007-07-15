#ifndef COMMANDLINE_CONFIGURATION_H_
#define COMMANDLINE_CONFIGURATION_H_

#include "dephine.h"
#include "abstract_configuration.h"
#include <map>
#include <string>
#include <vector>


class CommandlineConfiguration : public AbstractConfiguration
{
	private:
		std::map< std::string, std::string> m_arguments;
		
		void parse_arguments(const std::vector<std::string>& arguments);
		
	public:
	
		CommandlineConfiguration(Sint32 argc, char* argv[]);
		
		bool get_string(const std::string& section_name, const std::string& object_name, std::string& value) const;
		
		bool get_int(const std::string& section_name, const std::string& object_name, Uint32& value) const;
	
		bool get_bool(const std::string& section_name, const std::string& object_name, bool& value) const;
	
	//	bool get_double(const std::string& object_name, double& value) const;
	
		void save(){};
		
		void remove_object(const std::string& section_name, const std::string& object_name){};
		
		void remove_section(const std::string& section_name){};
	
		void set_string(const std::string& section_name, const std::string& object_name, const std::string& value){};
	
		void set_int(const std::string& section_name, const std::string& object_name, const Uint32& value){};
	
		void set_bool(const std::string& section_name, const std::string& object_name, const bool& value){};
	
	//	void set_double(const std::string& object_name, const double& value){};
		
};

#endif /*COMMANDLINE_CONFIGURATION_H_*/
