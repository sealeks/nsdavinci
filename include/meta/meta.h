/* 
 * File:   meta.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 25 Январь 2010 г., 23:04
 */

#ifndef _DVNCI_KRNL_CLIENTMETAINFO_H
#define	_DVNCI_KRNL_CLIENTMETAINFO_H


#include <pugixml/pugixml.hpp>
#include <kernel/constdef.h>
#include <kernel/error.h>
#include <kernel/mainstruct.h>

namespace dvnci{


typedef std::pair<indx,pugi::xml_node> num_xmlnode_pair;
typedef std::map<indx,pugi::xml_node,std::less<indx>, std::allocator<num_xmlnode_pair > > num_xmlnode_map;

typedef std::pair<std::string,nodetype> stdstr_nodetype_pair;
typedef std::map<std::string,nodetype,std::less<std::string>, std::allocator<stdstr_nodetype_pair > > stdstr_nodetype_map;

typedef std::pair<nodetype, std::string > nodetype_stdstr_pair;
typedef std::map<nodetype, std::string  ,std::less<nodetype>, std::allocator<nodetype_stdstr_pair > > nodetype_stdstr_map;

typedef std::pair<nodetype, num_xmlnode_map*> nodetype_xmlnodes_pair;
typedef std::map<nodetype, num_xmlnode_map* ,std::less<nodetype>, std::allocator<nodetype_xmlnodes_pair > > nodetype_xmlnodes_map;

class meta {



public:
    enum MetaState { disconnected , connected };
    meta();
    meta(const fspath&  dir_);
    virtual ~meta();
    MetaState state(){return _state;}

    bool connect(const fspath& dir_);
    bool disconnect();


    bool sign(dvnci::nodetype parenttp, indx parentid, iteminfo_map& mappack,
                       const std::string&  strcriteria = "" , num64 numcriteria= -1);
    bool sign(dvnci::nodetype ittp, indx_set& set_, iteminfo_map& mappack,
                       const std::string&  strcriteria = "" , num64 numcriteria= -1);

    pugi::xml_node* items(nodetype val, indx id_);

    std::string  getItemProperty(nodetype ittp, indx id_, std::string  property_);
    int  getItemProperty_int(nodetype ittp, indx id_, std::string  property_);
    unsigned int  getItemProperty_uint(nodetype ittp, indx id_, std::string  property_);
    double  getItemProperty_double(nodetype ittp, indx id_, std::string  property_);
    float  getItemProperty_float(nodetype ittp, indx id_, std::string  property_);
    bool  getItemProperty_bool(nodetype ittp, indx id_, std::string  property_);

    void  property(nodetype ittp, indx id, const std::string&  prop, const std::string&  val);

    template<typename T>
    void  property(nodetype ittp, indx id, const std::string&   prop,  T val){

        using namespace pugi;
        
        xml_node* tmp_node=items(ittp, id);
        if (tmp_node) return;
        xml_attribute at=tmp_node->attribute(prop.c_str());
        if (at.empty()) {
             tmp_node->append_attribute(prop.c_str());
             at=tmp_node->attribute(prop.c_str());};
        if (!at.empty()) {
           at.set_value(val);};}


    void  add(nodetype ittp, indx parentid, iteminfo_pair& pair_,  std::string  newname_ = "");
   
    ns_error remove(nodetype ittp, indx_set& keyset);

    bool merge();

    static std::string  nameAttribute(nodetype val);

protected:
    


    void init_s();
    std::string  nodeStr(nodetype val);
    nodetype nodeType(std::string val);

    num_xmlnode_map* registry(nodetype val);
    
    void clear();
    void loadSructure(pugi::xml_node& val);
    indx getNewKey(nodetype ittp);
    bool  checknodetypebyParentType(nodetype ittp, nodetype paritem_);
    nodetype getnodetypebyChildType(nodetype chitem_);
    bool deleteNode(num_xmlnode_map& regestry_, indx itid_);



private:
   pugi::xml_node meta_node;
   pugi::xml_node homeList_node;
   pugi::xml_node trendList_node;
   pugi::xml_node reportList_node;
   pugi::xml_node messageList_node;
   num_xmlnode_map* reportHeader_nodes;
   num_xmlnode_map* trendHeader_nodes;
   num_xmlnode_map* messageHeader_nodes;
   num_xmlnode_map* reportArr_nodes;
   num_xmlnode_map* trendArr_nodes;
   num_xmlnode_map* messageArr_nodes;
   num_xmlnode_map* unit_nodes;
   num_xmlnode_map* trend_nodes;
   num_xmlnode_map* message_nodes;
   MetaState _state;
   fspath       _dir;
   fspath       _path;
   pugi::xml_document doc;
   stdstr_nodetype_map convert_str_to_type;
   nodetype_stdstr_map convert_type_to_str;
   nodetype_xmlnodes_map xmlnodes_registry;


};


}

#endif	/* _CLIENTMETAINFO_H */

