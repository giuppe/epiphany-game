#include "commandline_configuration.h"
#include <map>
#include <string>
#include <cassert>
#include <cstring>
#include <vector>


CommandlineConfiguration::CommandlineConfiguration(Sint32 argc, char* argv[])
{
	std::vector<std::string> arguments;
	
	for(Sint32 i = 1; i<argc; i++)
	{
		arguments.push_back(std::string(argv[i]));
	}
	
	parse_arguments(arguments);
	
}

void CommandlineConfiguration::parse_arguments(const std::vector<std::string>& arguments)
{
	
	Uint32 it = 0;

	
	std::string curr_arg("");
	
	std::string prev_arg("");
	
	while (  it < arguments.size())
	{
    	curr_arg = arguments[it];
		if(curr_arg.substr(0, 2) == "--")
		{
			//DEBWARN("Argument: "<<curr_arg.substr(2)<<"\n");
			if(prev_arg.substr(0, 2) == "--")
			{
				m_arguments[prev_arg.substr(0, 2)] = "true";
				DEBOUT("Setting "<<prev_arg.substr(2)<<" = true\n");
			}
			
			if(it == arguments.size()-1)
			{
				m_arguments[curr_arg.substr(0, 2)] = "true";
				DEBOUT("Setting "<<curr_arg.substr(2)<<" = true\n");
			}
			prev_arg = curr_arg;
		}
		else
		{
			if(prev_arg.substr(0, 2) == "--")
			{
				m_arguments[prev_arg.substr(0, 2)] = curr_arg;
				DEBOUT("Setting "<<prev_arg.substr(2)<<" = "<<curr_arg<<"\n");
				
			}
			else if(curr_arg.substr(0, 2) == "--")
			{
				DEBWARN("Invalid option: "<<curr_arg<<"\n");
				
			}
			prev_arg = curr_arg;
			//assert(0);
		}
		it++;	    		
	}
	
	
}

bool CommandlineConfiguration::get_string(const std::string& section_name, const std::string& object_name, std::string& value) const
{
	assert(!"Function not implemented.");
}
		
bool CommandlineConfiguration::get_int(const std::string& section_name, const std::string& object_name, Uint32& value) const
{
	assert(!"Function not implemented.");
}
	
bool CommandlineConfiguration::get_bool(const std::string& section_name, const std::string& object_name, bool& value) const
{
	assert(!"Function not implemented.");
}


