/*
 * PbParser.h
 *
 *  Created on: Feb 14, 2017
 *      Author: sk
 */

#ifndef PBPARSER_H_
#define PBPARSER_H_
#include<string>
#include<iostream>
#include <fstream>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/compiler/importer.h>
using namespace google::protobuf;
using namespace google::protobuf::compiler;
using namespace std;
#define SAFE_FREE(x)		\
		if(x != NULL) {free(x);x = NULL;}
#define SAFE_DELETE(x)		\
		if(x != NULL) {delete(x);x = NULL;}

#ifdef DEBUG
     #define Log(x)  cout<<x<<endl;
#else
	#define Log(x)  ;
#endif


class PbParser {
public:
	PbParser(string &proto_file_name,string &object_name);
	bool Init();
	bool ParseFromString(const string* data);
	bool ParseFromIstream(istream* input);
	string &DebugString();
	virtual ~PbParser();
private:
	Message* FindMessageTypeByName();
private:
	const FileDescriptor *fileDescriptor_;
	const Descriptor *descriptor_;
    Importer *importer_;
    Message* message_;
    DynamicMessageFactory *factory_;
    istream* input;
	string proto_file_name_;
	string object_name_;
	string debug_string_;
};

#endif /* PBPARSER_H_ */
