//-----------------------------------------------------------------------------------------------//
// Created with QT Mult plaform C++ Library
// sqlservermanager dynamic library v1.0 2012
//
// Created by Wilson.Souza
//
// Owner 
// Copyright (c) 2012, 2013, 2014 Dedalus Prime
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <sql.listinstances.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace sql;
//-----------------------------------------------------------------------------------------------//
ListInstances::ListInstances()
{
	m_qListLocalDbInstanceInfo = std::shared_ptr<std::map<std::wstring, LocalDBInstanceInfo *>>(
		new std::map<std::wstring, LocalDBInstanceInfo *>());
}
//-----------------------------------------------------------------------------------------------//
ListInstances::~ListInstances()
{
}
//-----------------------------------------------------------------------------------------------//
bool const ListInstances::Build()
{
	return false;
}
//-----------------------------------------------------------------------------------------------//
std::shared_ptr<std::map<std::wstring, LocalDBInstanceInfo *>> const & ListInstances::GetResult() const
{
	return m_qListLocalDbInstanceInfo;	
}
//-----------------------------------------------------------------------------------------------//

