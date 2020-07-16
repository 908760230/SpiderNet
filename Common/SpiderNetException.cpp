#include "SpiderNetException.h"


namespace SpiderNet {



	Exception::Exception(int number, const std::string & description, const std::string & source):
		line(0),
		description(description),
		source(source)
	{
	}

	Exception::Exception(int number, const std::string & description, const std::string & source, const char * type, const char * file, long line):
		line(line),
		typeName(type),
		description(description),
		source(source),
		file(file)
	{
	}

	Exception::Exception(const Exception & rhs):
		line(rhs.line),
		typeName(rhs.typeName),
		description(rhs.description),
		source(rhs.source),
		file(rhs.file)
	{
	}

	const std::string & Exception::getFullDescription() const
	{
		// TODO: �ڴ˴����� return ���
		if (fullDesc.empty())
		{

			std::stringstream desc;

			desc << typeName << ": "
				<< description
				<< " in " << source;

			if (line > 0)
			{
				desc << " at " << file << " (line " << line << ")";
			}

			fullDesc = desc.str();
		}

		return fullDesc;
	}




}