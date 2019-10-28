/*
 * PbParser.cpp
 *
 *  Created on: Feb 14, 2017
 *      Author: sk
 */

#include "PbParser.h"

PbParser::PbParser(string& proto_file_name,string& object_name)
:proto_file_name_(proto_file_name)
,object_name_(object_name)
{
	// TODO Auto-generated constructor stub
	fileDescriptor_=NULL;
	descriptor_=NULL;
	importer_=NULL;
	input=NULL;
	message_=NULL;
	factory_=NULL;
}

PbParser::~PbParser() {
	// TODO Auto-generated destructor stub
	if(importer_!=NULL){
		SAFE_DELETE(importer_);
	}
	if(message_!=NULL){
		SAFE_DELETE(message_);
	}
	if(factory_!=NULL){
		SAFE_DELETE(message_);
	}
}

bool PbParser::Init(){

	if(proto_file_name_.empty()||object_name_.empty()){
        cout<<"proto_file_name or object_name empty!!!"<<endl;
		return false;
	}
	Log("proto_file_name : "+proto_file_name_);
	Log("object_name : "+object_name_);
    google::protobuf::compiler::DiskSourceTree sourceTree;
    sourceTree.MapPath("proto", proto_file_name_);
    importer_=new Importer(&sourceTree, NULL);
    fileDescriptor_=importer_->Import("proto");
	if (fileDescriptor_ != NULL){
	   //Log("----proto fileDescriptor-----");
	   //Log(fileDescriptor_->DebugString());
	}else{
	   Log("proto fileDescriptor_is null");
	   return false;
	}
	//Log(fileDescriptor_->package());
    Log("");
	message_=FindMessageTypeByName();
	if(!message_){
		Log("FindMessageTypeByName error");
        return false;
	}
    return true;
}

Message* PbParser::FindMessageTypeByName(){
	string object;
	std::size_t found = object_name_.find(".");
	if (found!=std::string::npos){
		object=object_name_;
	}else{
		object=fileDescriptor_->package()+"."+object_name_;
	}

    descriptor_=importer_->pool()->FindMessageTypeByName(object);

    if (descriptor_ != NULL){
        Log("----------"+object_name_+"----------");
        Log(descriptor_->DebugString());
    }else{
        Log(object_name_+" descriptor_ is null");
        return NULL;
    }
    factory_=new DynamicMessageFactory();//notice
    const Message*  proto = factory_->GetPrototype(descriptor_);
    Message*  message= proto->New();
    return message;
}

bool PbParser::ParseFromString(const string *data){
	if(data->empty()){
		Log("ParseFromString data is empty")
        return false;
	}

	if(!message_){
		Log("init error");
        return false;
	}
    if(!message_->ParseFromString(*data)){
        Log(object_name_+" ParseFromIstream error");
    }else{
    	Log("Parser Result: --------------------");
        Log(object_name_);
    	Log(message_->DebugString());
    	debug_string_=message_->DebugString();
    }

    return true;
}

bool PbParser::ParseFromIstream(istream* input){
	if(input==NULL){
		Log("ParseFromIstream input is null")
        return false;
	}
	if(message_==NULL){
		Log("init error");
        return false;
	}
    if(!message_->ParseFromIstream(input)){
        Log(object_name_+" ParseFromIstream error");
    }else{
    	Log("Parser Result: --------------------");
        Log(object_name_);
    	Log(message_->DebugString());
    	debug_string_=message_->DebugString();
    }
	return true;
}

string& PbParser::DebugString(){
   return debug_string_;
}
