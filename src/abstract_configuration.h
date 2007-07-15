#ifndef ABSTRACT_CONFIGURATION_H_
#define ABSTRACT_CONFIGURATION_H_

#include <string>
#include <SDL/SDL.h>

class AbstractConfiguration
{
	
public:
	
	virtual bool get_string(const std::string& section_name, const std::string& object_name, std::string& value) const =0;
	
	virtual bool get_int(const std::string& section_name, const std::string& object_name, Uint32& value) const =0;
	
	virtual bool get_bool(const std::string& section_name, const std::string& object_name, bool& value) const =0;
	
//	virtual bool get_double(const std::string& object_name, double& value) const =0;
	
	virtual void save()=0;
	
	virtual void remove_object(const std::string& section_name, const std::string& object_name) = 0;
	
	virtual void remove_section(const std::string& section_name) = 0;
	
	virtual void set_string(const std::string& section_name, const std::string& object_name, const std::string& value) =0;
	
	virtual void set_int(const std::string& section_name, const std::string& object_name, const Uint32& value) =0;
	
	virtual void set_bool(const std::string& section_name, const std::string& object_name, const bool& value) =0;
	
//	virtual void set_double(const std::string& object_name, const double& value) =0;
	
	virtual ~AbstractConfiguration(){};
			
};

#endif /*ABSTRACT_CONFIGURATION_H_*/
