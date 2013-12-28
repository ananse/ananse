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
    indent = 0;
    indenterEnabled = true;
}

std::string CppGenerator::indentation()
{
	std::string ret = "";
	if(indenterEnabled)
	{
		for(int i = 0; i < indent; i++)
		{
			ret += "    ";
		}
	}
	return ret;
}

void CppGenerator::addHeader(std::string header)
{
	bool insert = false;

	if(headers.size() == 0)
	{
		insert = true;
	}
	else
	{
		std::vector<std::string>::iterator it =std::find(headers.begin(), headers.end(), header);
		if(*it != header)
		{
			insert = true;
		}
	}

	if(insert)
	{
		setOutput(&includes);
		write("#include <" + header + ">\n");
		setOutput(&body);
		headers.push_back(header);
	}
}

void CppGenerator::emitEndOfStatement()
{
    write(";\n" + indentation());
	setOutput(&body);
	indenterEnabled = true;
}

void CppGenerator::emitDeclaration(std::string identifier, std::string datatype)
{
	indenterEnabled = false;
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
	addHeader("iostream");
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
    indent++;
}

void CppGenerator::emitModuleFooter()
{
	indent--;
    write("\n}");
}

void CppGenerator::emitIf(ExpressionNode * condition)
{
	write("if ");
	emitExpression(condition);
}

void CppGenerator::emitElse()
{
	write("else");
}

void CppGenerator::emitBeginCodeBlock()
{
	write("\n" + indentation() + "{\n");
	indent++;
	write(indentation());
}

void CppGenerator::emitEndCodeBlock()
{
	indent--;
	write ("\n" + indentation() + "}\n");
}

void CppGenerator::emitEndProgramme()
{
	write("exit(0)");
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


