#ifndef SPIDERNETEXCEPTION_H
#define SPIDERNETEXCEPTION_H

#include <exception>
#include <string>
#include <sstream>

namespace SpiderNet {

	class Exception : public std::exception
	{
	protected:
        long                    line;
        const char *            typeName;
        const char *            file;
        std::string             description;
        std::string             source;
        mutable std::string     fullDesc;

	public:

		enum  ExceptionCodes {
			ERR_CANNOT_WRITE_TO_FILE,
			ERR_INVALID_STATE,
			ERR_INVALID_PARAMS,
			ERR_FILE_NOT_FOUND,
			ERR_INTERNAL_ERROR,
			ERR_NOT_IMPLEMENTED,
			ERR_INVALID_CALL,
            ERR_NOT_CONSTRUCTED
		};

		Exception(int number, const std::string &description, const std::string &source);
		Exception(int number, const std::string &description, const std::string &source, const char* type, const char* file, long line);

		Exception(const Exception& rhs);
		~Exception() noexcept {}

		virtual const std::string& getFullDescription() const;

		const std::string& getSource() const { return source; }

		const char* getFile() const { return file; }

		long getLine() const { return line; }

		const std::string& getDescription() const { return description; }

		const char* what() const noexcept { return getFullDescription().c_str(); }
	};

	class  UnimplementedException : public Exception
	{
	public:
		UnimplementedException(int inNumber, const std::string& inDescription, const std::string& inSource, const char* inFile, long inLine)
			: Exception(inNumber, inDescription, inSource, __FUNCTION__, inFile, inLine) {}
	};
	class  FileNotFoundException : public Exception
	{
	public:
		FileNotFoundException(int inNumber, const std::string& inDescription, const std::string& inSource, const char* inFile, long inLine)
			: Exception(inNumber, inDescription, inSource, __FUNCTION__, inFile, inLine) {}
	};
	class  IOException : public Exception
	{
	public:
		IOException(int inNumber, const std::string& inDescription, const std::string& inSource, const char* inFile, long inLine)
			: Exception(inNumber, inDescription, inSource, __FUNCTION__, inFile, inLine) {}
	};
	class  InvalidStateException : public Exception
	{
	public:
		InvalidStateException(int inNumber, const std::string& inDescription, const std::string& inSource, const char* inFile, long inLine)
			: Exception(inNumber, inDescription, inSource, __FUNCTION__, inFile, inLine) {}
	};
	class  InvalidParametersException : public Exception
	{
	public:
		InvalidParametersException(int inNumber, const std::string& inDescription, const std::string& inSource, const char* inFile, long inLine)
			: Exception(inNumber, inDescription, inSource, __FUNCTION__, inFile, inLine) {}
	};
	class  ItemIdentityException : public Exception
	{
	public:
		ItemIdentityException(int inNumber, const std::string& inDescription, const std::string& inSource, const char* inFile, long inLine)
			: Exception(inNumber, inDescription, inSource, __FUNCTION__, inFile, inLine) {}
	};
	class  InternalErrorException : public Exception
	{
	public:
		InternalErrorException(int inNumber, const std::string& inDescription, const std::string& inSource, const char* inFile, long inLine)
			: Exception(inNumber, inDescription, inSource, __FUNCTION__, inFile, inLine) {}
	};

	class  InvalidCallException : public Exception
	{
	public:
		InvalidCallException(int inNumber, const std::string& inDescription, const std::string& inSource, const char* inFile, long inLine)
			: Exception(inNumber, inDescription, inSource, __FUNCTION__, inFile, inLine) {}
	};
    class  UnconstructedException : public Exception
	{
	public:
		UnconstructedException(int inNumber, const std::string& inDescription, const std::string& inSource, const char* inFile, long inLine)
			: Exception(inNumber, inDescription, inSource, __FUNCTION__, inFile, inLine) {}
	};

	class ExceptionFactory
	{
	private:
		/// Private constructor, no construction
		ExceptionFactory() {}
		static __attribute__((noreturn)) void _throwException(
			Exception::ExceptionCodes code, int number,
			const std::string& desc,
			const std::string& src, const char* file, long line)
		{
			switch (code)
			{
			case Exception::ERR_CANNOT_WRITE_TO_FILE:   throw IOException(number, desc, src, file, line);
			case Exception::ERR_INVALID_STATE:          throw InvalidStateException(number, desc, src, file, line);
			case Exception::ERR_INVALID_PARAMS:			throw InvalidParametersException(number, desc, src, file, line);
			case Exception::ERR_FILE_NOT_FOUND:         throw FileNotFoundException(number, desc, src, file, line);
			case Exception::ERR_INTERNAL_ERROR:         throw InternalErrorException(number, desc, src, file, line);
			case Exception::ERR_NOT_IMPLEMENTED:        throw UnimplementedException(number, desc, src, file, line);
			case Exception::ERR_INVALID_CALL:           throw InvalidCallException(number, desc, src, file, line);
            case Exception::ERR_NOT_CONSTRUCTED:        throw UnconstructedException(number, desc, src, file, line);
			default:                                    throw Exception(number, desc, src, "Exception", file, line);
			}
		}
	public:
		static __attribute__((noreturn)) void throwException(
			Exception::ExceptionCodes code,
			const std::string& desc,
			const std::string& src, const char* file, long line)
		{
			_throwException(code, code, desc, src, file, line);
		}
	};


#define SPIDERNET_EXCEPT_SRC(code,desc,src)		ExceptionFactory::throwException(code,desc,src,__FILE__,__LINE__)
#define SPIDERNET_EXCEPT(code,desc)			ExceptionFactory::throwException(code, desc, __FUNCTION__, __FILE__, __LINE__)

}

#endif


