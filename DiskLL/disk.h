/*
 * disk.h
 *
 *  Created on: Jun 29, 2014
 *      Author: Liam
 */

#ifndef DISK_H_
#define DISK_H_
#define SIZEOFSECTOR 3
#define NUMOFSECTORS 30

#include <list>
#include <iostream>
using namespace std;

class Sector {
public:
	Sector();
	void setContents(char*);
	void printContents() const;
	char *contents;
};

class SectorListNode {
public:
	SectorListNode(int, int);
	int begin, end;
	SectorListNode *next;
};

class DiskFile {
public:
	DiskFile(const char*, streamsize, DiskFile*);
	void addSectorNode(const SectorListNode&);
	const char *name;
	int numOfChars;
	list<SectorListNode> *sectors;
	DiskFile *next;
};

SectorListNode::SectorListNode(int begin, int end){
	this->begin = begin;
	this->end = end;
	this->next = nullptr;
}

Sector::Sector(){
	this->contents = nullptr;
}

void Sector::setContents(char *s){
	for(int i = 0; i < 3; i++, s++)
		this->contents = s;
}

void Sector::printContents() const{
	cout << this->contents;
}

DiskFile::DiskFile(const char* s, streamsize numOfChars, DiskFile* file){
	this->name = s;
	this->numOfChars = numOfChars;
	this->sectors = new list<SectorListNode>();
	this->next = file;
}

void DiskFile::addSectorNode(const SectorListNode &node){
	this->sectors->push_front(node);
}
#endif /* DISK_H_ */
