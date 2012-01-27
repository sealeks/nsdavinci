/*
 * Copyright (C) 2004, 2005, 2008, 2009 Nikolas Zimmermann <zimmermann@kde.org>
 * Copyright (C) 2004, 2005 Rob Buis <buis@kde.org>
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

#ifndef SVGURIReference_h
#define SVGURIReference_h

#if ENABLE(SVG)
#include "SVGElement.h"
#include "XLinkNames.h"
#include "CachedResourceClient.h"



namespace WebCore {

class Attribute;
class CachedSVGDocument;    
class Document;

class SVGURIReference  {

	friend class CachedResourceURIClient;

        class CachedResourceURIClient : public CachedResourceClient {
        public:
            CachedResourceURIClient(SVGURIReference * const ref, Attribute* att = 0);
            ~CachedResourceURIClient();
            Document* document();
            virtual void notifyFinished(CachedResource*);
            void request(const String& href, const String& url);
            String resource() const;
        private:
            SVGURIReference * const reference;
            CachedSVGDocument* m_cachedDocument;
            Attribute* attr;
        };

public:
    
    SVGURIReference();
    SVGURIReference(SVGElement * const);
    virtual ~SVGURIReference();

    bool parseMappedAttribute(Attribute*);
    bool isKnownAttribute(const QualifiedName&);
    void addSupportedAttributes(HashSet<QualifiedName>&);

    static String getTarget(const String& url);

protected:

	virtual void setHrefBaseValue(const String&) = 0;    


 private:
	
	SVGElement * const       m_svgElement;
    CachedResourceURIClient* m_observer;
};

} // namespace WebCore

#endif // ENABLE(SVG)
#endif // SVGURIReference_h
