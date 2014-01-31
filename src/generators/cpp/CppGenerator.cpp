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
    selectCases = 0;
    nextCodeBlockPrefix = "";
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

void CppGenerator::emitDeclaration(std::string identifier, std::string datatype, bool global)
{
    if(global) 
    {
        setOutput(&moduleGlobals);
        indenterEnabled = false;
    }
    
    std::string localType;
    
    if(datatype == "integer") localType = "int";
    if(datatype == "long") localType = "long";
    if(datatype == "boolean") localType = "bool";
    
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

void CppGenerator::emitElseIf(ExpressionNode * condition)
{
	write("else if ");
	emitExpression(condition);
}

void CppGenerator::emitElse()
{
	write("else ");
}

void CppGenerator::emitBeginCodeBlock()
{
	write("\n" + indentation() + "{\n");
	indent++;
	write(indentation());
    if(nextCodeBlockPrefix != "") {
        write(nextCodeBlockPrefix);
        nextCodeBlockPrefix = "";
    }
}

void CppGenerator::emitEndCodeBlock()
{
	indent--;
	write ("\n" + indentation() + "}\n" + indentation());
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

void CppGenerator::emitSelect(ExpressionNode* node)
{
    std::stringstream identifier;
    identifier<<"select_case_";
    identifier<<selectCases;
    emitDeclaration(identifier.str() + "_matched", "boolean", false);
    write(" = false");
    emitEndOfStatement();
    emitDeclaration(identifier.str(), node->getDataType(), false);
    emitAssignment();
    emitExpression(node);
    emitEndOfStatement();
    caseVariables.push_back(identifier.str());
}

void CppGenerator::writeCaseExpression(std::string identifier, CaseExpression* expression)
{
    switch(expression->getType())
    {
        case CASE_EXPRESSION:
            write(identifier);
            write(" == ");
            emitExpression(expression->getPrimaryExpression());
            break;
        
        //@todo modify this to support strings sorted in ascending order in future
        case CASE_TO:
            write(identifier);
            write(" >= ");
            emitExpression(expression->getPrimaryExpression());
            write(" && ");
            write(identifier);
            write(" <= ");
            emitExpression(expression->getSecondaryExpression());
            break;
            
        case CASE_IS:
            write(identifier);
            write(getToken(expression->getComparator()));
            emitExpression(expression->getPrimaryExpression());
            break;
    }
}

void CppGenerator::emitCase(std::vector<CaseExpression*> expressions)
{
    CaseExpression * caseExpression;
    write("if(");
    caseExpression = expressions.back();
    expressions.pop_back();
    writeCaseExpression(caseVariables.back(), caseExpression);
    
    while(expressions.size() > 0)
    {
        write("||");
        caseExpression = expressions.back();
        expressions.pop_back();
        writeCaseExpression(caseVariables.back(), caseExpression);        
    }
    
    write(")");
    nextCodeBlockPrefix = caseVariables.back() + "_matched = true;\n" + indentation() + indentation();
}

void CppGenerator::emitCaseElse()
{
    write("if(" + caseVariables.back() + "_matched==false)");
}

void CppGenerator::emitEndSelect()
{
    write("\n" + caseVariables.back() + "_end:\n" + indentation() + "((void)0);\n" + indentation());
    caseVariables.pop_back();
}

void CppGenerator::emitExitSelect()
{
    write("goto " + caseVariables.back() + "_end;\n" + indentation());
}

void CppGenerator::emitFor(std::string identifier, ExpressionNode* from, ExpressionNode* to, ExpressionNode* step)
{
    write("for(" + identifier + " = ");
    emitExpression(from);
    write("; ");
    write(identifier + "<=");
    emitExpression(to);
    write("; ");
    write(identifier + "+=");
    if(step == NULL)
    {
        write("1");
    }
    else
    {
        emitExpression(step);
    }
    write(")");
}

void CppGenerator::emitExitFor()
{
    write("break");
    emitEndOfStatement();
}

void CppGenerator::emitContinueFor()
{
    write("continue");
    emitEndOfStatement();
}

void CppGenerator::emitWhile(ExpressionNode* condition)
{
    write("while(");
    emitExpression(condition);
    write(")");
}

void CppGenerator::emitEndWhile(){}

void CppGenerator::emitExitWhile()
{
    write("break");
    emitEndOfStatement();
}

void CppGenerator::emitContinueWhile()
{
    write("continue");
    emitEndOfStatement();
}

void CppGenerator::emitDo(std::string type, ExpressionNode* condition)
{
    bool doConditions;
    if(type == "")
    {
        write("do");
        doConditions = false;
    }
    else
    {
        write("while(");
        if(type == "while")
        {
            emitExpression(condition);
        }
        else if(type == "until")
        {
            write("!(");
            emitExpression(condition);
            write(")");
        }
        write(")");
        doConditions = true;
    }
    this->doConditions.push_back(doConditions);
}

void CppGenerator::emitLoop(std::string type, ExpressionNode* condition)
{
    if(doConditions.back() == false)
    {
        if(type == "")
        {
            write("while(true)");
            emitEndOfStatement();
        }
        else if(type == "while")
        {
            write("while(");
            emitExpression(condition);
            write(")");
            emitEndOfStatement();
        }
        else if(type == "until")
        {
            write("while(!(");
            emitExpression(condition);
            write("))");
            emitEndOfStatement();
        }
    }
    doConditions.pop_back();
}

