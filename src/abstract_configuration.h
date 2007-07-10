#ifndef ABSTRACT_CONFIGURATION_H_
#define ABSTRACT_CONFIGURATION_H_

class AbstractConfiguration
{
	
public:
	
	virtual std::string get_string(const std::string& object_name)=0;
	
	virtual Uint32 get_int(const std::string& object_name)=0;
	
	virtual bool get_bool(const std::string& object_name)=0;
	
	virtual double get_double(const std::string& object_name)=0;
			
}

#endif /*ABSTRACT_CONFIGURATION_H_*/
