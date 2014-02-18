#pragma once

#include <vector>
#include <boost/algorithm/string/replace.hpp>

#include <cpdoccore/CPSharedPtr.h>
#include <cpdoccore/CPWeakPtr.h>
#include <cpdoccore/xml/xmlelement.h>
//#include <cpdoccore/common/readdocelement.h>
#include <cpdoccore/common/writedocelement.h>
#include <cpdoccore/CPAssert.h>

#include "office_elements_type.h"

//#include "visitor.h"
//#include "..\conversionelement.h"

namespace cpdoccore {
namespace odf {

class document_context;

class office_element;

typedef shared_ptr<office_element>::Type office_element_ptr;
typedef weak_ptr<office_element>::Type office_element_weak_ptr;
typedef ::std::vector<office_element_ptr> office_element_ptr_array;

class office_element : public xml::element<wchar_t>,
    public common::write_doc_element
{    
public:
    office_element() : is_root_(false), context_(NULL) {}

    virtual ElementType get_type() const = 0;
    virtual ~office_element() = 0;
    void set_root(bool isRoot) { is_root_ = isRoot; }
    bool is_root() const { return is_root_; }

    virtual void afterCreate() {};
    virtual void afterReadContent() {};
   

    void setContext(document_context * Context) { context_ = Context; }

public:
    virtual ::std::wostream & text_to_stream(::std::wostream & _Wostream) const
    {
        //_CP_LOG(info) << L"[warning] use base text_to_stream\n";
        return _Wostream;
    }

    virtual ::std::wostream & xml_to_stream(::std::wostream & _Wostream) const
    {
        //_CP_LOG(info) << L"[warning] use base xml_to_stream\n";
        return _Wostream;
    }
    document_context * getContext() { return context_; }
//
//protected:
    const document_context * getContext() const { return context_; }

private:
    bool is_root_;
    document_context * context_;
};

#define CPDOCCORE_OFFICE_DOCUMENT_IMPL_NAME_FUNCS_ public:\
    virtual const wchar_t * get_ns() const { return ns; }\
    virtual const wchar_t * get_name() const { return name; }\
    virtual xml::NodeType get_xml_type() const { return xml_type; }\
    virtual ElementType get_type() const { return type; }



inline office_element::~office_element()
{
}

/// \class  office_element_impl
template <class Element>
class office_element_impl : public virtual office_element
{
// xml::element impl
public:
    virtual const wchar_t * get_ns() const
    { 
        return Element::ns;
    }
    
    virtual const wchar_t * get_name() const
    { 
        return Element::name;
    }

    virtual xml::NodeType get_xml_type() const
    { 
        return Element::xml_type;
    }

private:
    virtual void add_text(const std::wstring & Text)
    {
        std::wstring text = Text;
        boost::algorithm::erase_all(text, L" ");
        boost::algorithm::erase_all(text, L"\t");
        boost::algorithm::erase_all(text, L"\n");
        boost::algorithm::erase_all(text, L"\r");
        //CP_ASSERT(false);
    }

// office_element impl
public:
    virtual ElementType get_type() const
    { 
        return Element::type;
    }
   
};


}
}

