/*
 * File:   CppGenerator.cpp
 * Author: ekow
 * 
 * Created on 26 October 2013, 15:16
 */

#include "CppGenerator.h"
#include <iostream>
#include <algorithm>

CppGenerator::CppGenerator() 
{
    
}

CppGenerator::CppGenerator(const CppGenerator& orig) 
{
    
}

CppGenerator::~CppGenerator() 
{
    
}

void CppGenerator::emitEndOfStatement()
{
    write(";\n");
	setOutput(&body);
}

void CppGenerator::emitDeclaration(std::string identifier, std::string datatype)
{
	setOutput(&moduleGlobals);
    std::string localType;
    if(datatype == "number" || datatype == "")
    {
        localType = "int";
    }
    write(localType + " " + identifier);
}

void CppGenerator::emitPrint()
{
	if(headers.size() == 0)
	{
		setOutput(&includes);
		write("#include <iostream>\n");
		setOutput(&body);
	}
	else
	{
		std::vector<std::string>::iterator it =std::find(headers.begin(), headers.end(), "iostream");
		if(*it != "iostream")
		{
			setOutput(&includes);
			write("#include <iostream>\n");
			setOutput(&body);
		}
	}
	write("std::cout<<");
}

void CppGenerator::emitModuleHeader()
{
    std::string moduleFunction;
    if(isMainModule){
        moduleFunction = "int main(int argc, char ** argv)";
    }
    write(moduleFunction);
    write("\n{\n    ");
}

void CppGenerator::emitModuleFooter()
{
    write("\n}");
}

std::string CppGenerator::openOutput(std::string source)
{
	setOutput(&body);
	outputFile = getOutputFile(source);
	return outputFile;
}

void CppGenerator::closeOutput()
{
	std::ofstream file(outputFile.c_str(), std::fstream::out);
	includes.seekp(0);

	std::copy(std::istreambuf_iterator<char>(includes),
	     std::istreambuf_iterator<char>(),
	     std::ostreambuf_iterator<char>(file)
	);

	file<<"\n";

	std::copy(std::istreambuf_iterator<char>(moduleGlobals),
	     std::istreambuf_iterator<char>(),
	     std::ostreambuf_iterator<char>(file)
	);

	file<<"\n";

	std::copy(std::istreambuf_iterator<char>(body),
	     std::istreambuf_iterator<char>(),
	     std::ostreambuf_iterator<char>(file)
	);

	file.close();
}

std::string CppGenerator::getOutputFile(std::string output)
{
    return output + ".cpp";
}


