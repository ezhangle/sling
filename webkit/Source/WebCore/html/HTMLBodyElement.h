/*
 * Copyright (C) 1999 Lars Knoll (knoll@kde.org)
 *           (C) 1999 Antti Koivisto (koivisto@kde.org)
 *           (C) 2000 Simon Hausmann <hausmann@kde.org>
 * Copyright (C) 2004, 2006, 2009, 2010, 2015 Apple Inc. All rights reserved.
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
 *
 */

#ifndef HTMLBodyElement_h
#define HTMLBodyElement_h

#include "HTMLElement.h"

namespace WebCore {

class HTMLBodyElement final : public HTMLElement {
public:
    static Ref<HTMLBodyElement> create(Document&);
    static Ref<HTMLBodyElement> create(const QualifiedName&, Document&);
    virtual ~HTMLBodyElement();

    static const AtomicString& eventNameForWindowEventHandlerAttribute(const QualifiedName& attributeName);

private:
    HTMLBodyElement(const QualifiedName&, Document&);

    bool isFirstBodyElementOfDocument() const;

    void parseAttribute(const QualifiedName&, const AtomicString&) override;
    bool isPresentationAttribute(const QualifiedName&) const override;
    void collectStyleForPresentationAttribute(const QualifiedName&, const AtomicString&, MutableStyleProperties&) override;

    InsertionNotificationRequest insertedInto(ContainerNode&) override;

    bool isURLAttribute(const Attribute&) const override;
    
    bool supportsFocus() const override;

    int scrollLeft() override;
    void setScrollLeft(int) override;
    
    int scrollTop() override;
    void setScrollTop(int) override;
    
    int scrollHeight() override;
    int scrollWidth() override;
    
    void addSubresourceAttributeURLs(ListHashSet<URL>&) const override;

    static EventHandlerNameMap createWindowEventHandlerNameMap();
};

} //namespace

#endif