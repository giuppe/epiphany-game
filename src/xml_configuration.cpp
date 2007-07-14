#include "dephine.h"
#include "xml_configuration.h"
#include <string>
#include <cstring>
#include <cassert>
#include "tinyxml/tinyxml.h"



/*
std::string XMLConfiguration::get_section(const std::string& object_path) const
{
	return object_path.substr(0, object_path.find("/"));
}



		
std::string XMLConfiguration::get_object_name(const std::string& object_path) const
{
	
	return object_path.substr(object_path.find("/")+1, object_path.size());
}

*/


std::string XMLConfiguration::get_value(const std::string& section, const std::string& object) const
{
	if(m_initialized == true)
	{
		TiXmlHandle docHandle( m_document );
		
		TiXmlText* object_value = docHandle.FirstChild(section.c_str()).FirstChild(object.c_str()).FirstChild().Text();
		if(object_value)
		{
		
			DEBWARN("XMLConfiguration: "<<section<<"/"<<object<<" is "<<object_value<<"\n");
			return object_value->Value();
		}	
	
		DEBWARN("XMLConfiguration: cannot load "<<section<<"/"<<object<<"\n");
		return "";
	
	}
	
	assert(!"XMLConfiguration: not initialized\n");
	return "";
	
	
}




XMLConfiguration::XMLConfiguration(const std::string& file_path, bool create_if_missing)
{
	m_document = new TiXmlDocument();
	
	m_initialized = false;
	
	if(m_document->LoadFile(file_path.c_str()))
	{	
		m_initialized = true;

		m_file_path = file_path;
	
	}
	else if(create_if_missing == true)
	{
	
		m_file_path = file_path;
		
		m_initialized= true;
	}	
}



XMLConfiguration::~XMLConfiguration()
{
	if(m_initialized==true)
		delete m_document;	
}
		



std::string XMLConfiguration::get_string(const std::string& section_name, const std::string& object_name) const
{
	
	return get_value(section_name, object_name);
}



Uint32 XMLConfiguration::get_int(const std::string& section_name, const std::string& object_name) const
{
	return atoi(get_value(section_name, object_name).c_str());
}


	
bool XMLConfiguration::get_bool(const std::string& section_name, const std::string& object_name) const
{
	if(get_value(section_name, object_name) == "true")
		return true;
		
	return false;
}

	


void XMLConfiguration::save()
{
	m_document->SaveFile(m_file_path.c_str());
}



	
void XMLConfiguration::set_string(const std::string& section_name, const std::string& object_name, const std::string& value)
{
	this->set_value(section_name, object_name, value);
}




void XMLConfiguration::set_int(const std::string& section_name, const std::string& object_name, const int& value)
{
	char string_value[255];
	sprintf(string_value, "%d", value);
	this->set_value(section_name, object_name, std::string(string_value));
}


	
	
void XMLConfiguration::set_bool(const std::string& section_name, const std::string& object_name, const bool& value)
{
	std::string string_value = "false";
	if(value == true)
	{
		string_value = "true";
	}
	this->set_value(section_name, object_name, string_value);
}
	

void XMLConfiguration::set_value(const std::string& section, const std::string& object, const std::string& value)
{
	bool section_found = false;
	bool object_found = false;
	
	TiXmlNode* child = 0;
	
	TiXmlNode* nephew = 0;
	
	if(m_document->NoChildren()==false)
	{
		
		while((!section_found) && ( child = m_document->IterateChildren( child ) ))
		{
			if(std::string(child->Value())==section)
			{
				section_found = true;
			}
		}
	}
		
	if(section_found == false)
	{
		DEBOUT("XMLConfiguration: no section "<<section<<" found, creating.\n");
		child = new TiXmlElement( section.c_str() );
		m_document->LinkEndChild( child );
	}
	
	if(child->NoChildren()==false)
	{
		
		while((!object_found) &&( nephew = child->IterateChildren( nephew ) ))
		{
			if(std::string(nephew->Value())==object)
			{
				object_found = true;
			}
		}
	}
	
	if(object_found == false)
	{
		DEBOUT("XMLConfiguration: no object "<<section<<"/"<<object<<" found, creating.\n");
		nephew = new TiXmlElement( object.c_str() );
		child->LinkEndChild( nephew );
	}
	
	nephew->Clear();
	
	TiXmlText* text_element = new TiXmlText( value.c_str() );
	nephew->LinkEndChild( text_element );
	
}


void XMLConfiguration::remove_object(const std::string& section_name, const std::string& object_name)
{
	bool section_found = false;
	bool object_found = false;
	
	TiXmlNode* child = 0;
	
	TiXmlNode* nephew = 0;
	
	if(m_document->NoChildren()==false)
	{
		
		while((!section_found) && ( child = m_document->IterateChildren( child ) ))
		{
			if(std::string(child->Value())==section_name)
			{
				section_found = true;
			}
		}
	}
		
	if(section_found == false)
	{
		return;
	}
	
	if(child->NoChildren()==false)
	{
		
		while((!object_found) && ( nephew = child->IterateChildren( nephew ) ))
		{
			if(std::string(nephew->Value())==object_name)
			{
				object_found = true;
			}
		}
	}
	
	if(object_found == false)
	{
		return;
	}
	
	child->RemoveChild(nephew);
}

void XMLConfiguration::remove_section(const std::string& section_name)
{
	bool section_found = false;

	
	TiXmlNode* child = 0;
		
	if(m_document->NoChildren()==false)
	{
		
		while((!section_found) && ( child = m_document->IterateChildren( child ) ))
		{
			if(std::string(child->Value())==section_name)
			{
				section_found = true;
			}
		}
	}
		
	if(section_found == false)
	{
		return;
	}
	
	m_document->RemoveChild(child);
}
