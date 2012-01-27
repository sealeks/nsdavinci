/*
 * Copyright (C) 2004, 2005, 2008 Nikolas Zimmermann <zimmermann@kde.org>
 * Copyright (C) 2004, 2005, 2006 Rob Buis <buis@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "config.h"

#if ENABLE(SVG)
#include "SVGURIReference.h"

#include "Element.h"
#include "Document.h"
#include "CachedResourceLoader.h"
#include "SVGDocument.h"
#include "XMLSerializer.h"
#include "SVGDefsElement.h"
#include "SVGNames.h"
#include "CachedSVGDocument.h"
#include "SVGStyledElement.h"
#include "SVGColor.h"

namespace WebCore {

    static bool isLocalURI(const String& uri) {
        return (((uri.startsWith("#")) || (uri.startsWith("url("))) || ((uri.startsWith("#{"))));
    }
    
    
    static String normalazeURI(String uri) {
        return uri.replace("#", "z").replace(".", "d").replace("/", "s").replace("\\", "s").replace(":", "q");
    }

    
    
    static String normalizeID(const String& id, const String& url) {
        return normalazeURI(url + "#" + id);
    }
    
    

    static String reqestpartURI(const String& url) {
        return (url.find('#') == notFound) ? url : url.substring(0, url.find('#'));
    }

    
    
    static String getTargetURI(const String& url, const String& uri = "") {

        String uritmp = url;

        if (url.startsWith("url(")) {

            size_t start = url.find('(') + 1;
            size_t end = url.reverseFind(')');
            uritmp = uri + url.substring(start, end - start);

            if (url.startsWith("'")) {
                uritmp = uritmp.replace("'", "");
            }
        }

        if (uritmp.startsWith("#") && (uri == "")) {

            return SVGURIReference::getTarget(uritmp);
        }

        return normalazeURI(uri + uritmp);
    }
    
    
    

    void formatRomoteDocument(Element* el, const String& uri) {

        if (uri == "")
            return;

        const AtomicString& id = el->getIdAttribute();
        if (id != nullAtom) {
            String val = id;
            if (!val.startsWith(normalizeID("", uri))) {
                val = normalizeID(val, uri);
                if ((val != ""))
                    el->setIdAttribute(val);
            }
        }

        NamedNodeMap* attr_map = el->attributeMap();
        
        if (attr_map) {
            for (size_t i = 0; i < attr_map->length(); i++) {

                if (attr_map->attributeItem(i)) {

                    String val = el->getAttribute(attr_map->attributeItem(i)->name());

                    if ((isLocalURI(val)) && (!SVGColor::colorFromRGBColorString(val).isValid()) &&
                            (attr_map->attributeItem(i)->value() != "id")) {
                        val = getTargetURI(val);
                        String templattr = getTargetURI("", uri);

                        if (!val.startsWith(templattr)) {
                            val = "url(#" + getTargetURI(normalizeID(val, uri)) + ")";
                            el->setAttribute(attr_map->attributeItem(i)->name(), val);
                        }
                    }
                }
            }
        }

        for (Element* e = el->firstElementChild(); e; e = e->nextElementSibling()) {
            formatRomoteDocument(e, uri);
        }
    }



// Animated property definitions

    bool SVGURIReference::parseMappedAttribute(Attribute* attr) {

        if (attr->name().matches(XLinkNames::hrefAttr)) {
            setHrefBaseValue(attr->value());
            if ((m_svgElement) && (!isLocalURI(attr->value()))) {
                Document* doc = m_svgElement->document();
                if (doc) {
                    KURL url(doc->baseURI(), attr->value());
                    if (url.hasFragmentIdentifier()) {
                        String hrf = attr->value();
                        String uripart = reqestpartURI(attr->value());
                        m_svgElement->setAttribute(attr->name(), "#" + getTargetURI(attr->value()));
                        if (m_observer) {
                            if (m_observer->resource() == uripart) {
                                m_svgElement->svgAttributeChanged(attr->name());
                                return true;
                            }
                            delete m_observer;
                        }
                        m_observer = new CachedResourceURIClient(this, attr);
                        // m_svgElement->setHasPending(true);
                        m_observer->request(hrf, uripart);
                    }
                }
            }
            return true;
        }
        return false;
    };

SVGURIReference::SVGURIReference() : m_svgElement(0), m_observer(0) { }


SVGURIReference::SVGURIReference(SVGElement * const el) : m_svgElement(el), m_observer(0)
{
}

SVGURIReference::~SVGURIReference() {
if (m_observer) 
		delete m_observer;
}




bool SVGURIReference::isKnownAttribute(const QualifiedName& attrName)
{
    return attrName.matches(XLinkNames::hrefAttr);
}

String SVGURIReference::getTarget(const String& url)
{
	if (url.startsWith("#{")) return String();

    if (url.startsWith("url(")) { // URI References, ie. fill:url(#target)

        size_t start = url.find('#') + 1;
        size_t end = url.reverseFind(')');
        return url.substring(start, end - start);
    }

    if (url.find('#') != notFound) { // format is #target
        size_t start = url.find('#') + 1;
        return url.substring(start, url.length() - start);
    }

    // The url doesn't have any target.
    return String();
}

void SVGURIReference::addSupportedAttributes(HashSet<QualifiedName>& supportedAttributes)
{
    DEFINE_STATIC_LOCAL(AtomicString, xlinkPrefix, ("xlink"));
    QualifiedName hrefWithPrefix = XLinkNames::hrefAttr;
    hrefWithPrefix.setPrefix(xlinkPrefix);
    supportedAttributes.add(hrefWithPrefix);
    supportedAttributes.add(XLinkNames::hrefAttr);
}


String SVGURIReference::CachedResourceURIClient::resource() const{
	return (m_cachedDocument) ? m_cachedDocument->RequestUri() : "";
}

SVGURIReference::CachedResourceURIClient::CachedResourceURIClient(SVGURIReference * const ref, Attribute* att) : reference(ref), m_cachedDocument(0), attr(att) {
}


SVGURIReference::CachedResourceURIClient::~CachedResourceURIClient(){
	if (m_cachedDocument)
		m_cachedDocument->removeClient(this);

}


    void SVGURIReference::CachedResourceURIClient::notifyFinished(CachedResource* newdoc) {


        if ((reference) && (reference->m_svgElement)) {
            
            m_cachedDocument = static_cast<CachedSVGDocument*> (newdoc);
            Document* document = reference->m_svgElement->document();
            
            if ((document) && (m_cachedDocument->document())) {

                Document* remotedocument = m_cachedDocument->document();
                if (!document->getElementById(normalizeID("", m_cachedDocument->RequestUri()))) {


                    formatRomoteDocument(remotedocument->documentElement(), m_cachedDocument->RequestUri());
                    RefPtr<SVGDefsElement> svgdefElement = SVGDefsElement::create(SVGNames::defsTag, document);
                    
                    ExceptionCode ex;


                    svgdefElement->setIdAttribute(normalizeID("", m_cachedDocument->RequestUri()));
                    Element* source = reference->m_svgElement->viewportElement() ?
                            (Element*) reference->m_svgElement->viewportElement() : document->documentElement();


                    if (!source->firstElementChild())
                        source->appendChild(svgdefElement, ex);
                    else
                        source->insertBefore(svgdefElement, document->documentElement()->firstElementChild(), ex);

                    for (Element* e = remotedocument->documentElement()->firstElementChild(); e; e = e->nextElementSibling()) {

                        svgdefElement->appendChild(e->cloneElementWithChildren(), ex);
                    }
                }


                if (attr) {
                    reference->m_svgElement->svgAttributeChanged(attr->name());
                }

            }
        }
    }
    
    
    void SVGURIReference::CachedResourceURIClient::request(const String& href, const String& url) {
        if ((reference) && (reference->m_svgElement)) {
            Document* document = reference->m_svgElement->document();
            if (document) {
                ResourceRequest request(document->completeURL(href));
                m_cachedDocument = document->cachedResourceLoader()->requestSVGDocument(request, url);
                if (m_cachedDocument)
                    m_cachedDocument->addClient(this);
            }
        }
    }

}

#endif // ENABLE(SVG)
