#ifndef XML_CONFIGURATION_H_
#define XML_CONFIGURATION_H_

#include "abstract_configuration.h"
#include <string>

class TiXmlDocument;

class XMLConfiguration : public AbstractConfiguration
{
	private:
	
		TiXmlDocument* m_document;
		
		std::string get_value(const std::string& section, const std::string& object) const;
		
	//	std::string get_section(const std::string& object_path) const;
		
	//	std::string get_object_name(const std::string& object_path) const;
		
		void set_value(const std::string& section, const std::string& object, const std::string& value);
		
		bool m_initialized;
		
		std::string m_file_path;
		

	public:
	
		XMLConfiguration(const std::string& file_path, bool create_if_missing = false);
		
		~XMLConfiguration();
		
		std::string get_string(const std::string& section_name, const std::string& object_name) const;
		
		Uint32 get_int(const std::string& section_name, const std::string& object_name) const;
	
		bool get_bool(const std::string& section_name, const std::string& object_name) const;
	
	//	double get_double(const std::string& object_name) const;
	
		void save();
		
		void remove_object(const std::string& section_name, const std::string& object_name);
		
		void remove_section(const std::string& section_name);
	
		void set_string(const std::string& section_name, const std::string& object_name, const std::string& value);
	
		void set_int(const std::string& section_name, const std::string& object_name, const int& value);
	
		void set_bool(const std::string& section_name, const std::string& object_name, const bool& value);
	
	//	void set_double(const std::string& object_name, const double& value);
		
};

#endif /*XML_CONFIGURATION_H_*/
