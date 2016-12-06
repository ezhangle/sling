/*
 * Copyright (C) 2003, 2006 Apple Inc.  All rights reserved.
 * Copyright (C) 2006 Samuel Weinig <sam.weinig@gmail.com>
 * Copyright (C) 2015 NAVER Corp.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ResourceRequest_h
#define ResourceRequest_h

#include "ResourceRequestBase.h"

typedef const struct _CFURLRequest* CFURLRequestRef;

namespace WebCore {
    class ResourceRequest : public ResourceRequestBase {
    public:
        ResourceRequest(const String& url)
            : ResourceRequestBase(URL(ParsedURLString, url), UseProtocolCachePolicy)
        {
        }

        ResourceRequest(const URL& url)
            : ResourceRequestBase(url, UseProtocolCachePolicy)
        {
        }

        ResourceRequest(const URL& url, const String& referrer, ResourceRequestCachePolicy policy = UseProtocolCachePolicy)
            : ResourceRequestBase(url, policy)
        {
            setHTTPReferrer(referrer);
        }

        ResourceRequest()
            : ResourceRequestBase(URL(), UseProtocolCachePolicy)
        {
        }

        ResourceRequest(int)
            : ResourceRequestBase()
        {
        }

        void updateFromDelegatePreservingOldProperties(const ResourceRequest& delegateProvidedRequest) { *this = delegateProvidedRequest; }

#if USE(CRNET)
        const String& downloadAttribute() const { return m_downloadAttribute; }
        void setDownloadAttribute(const String& attr) { m_downloadAttribute = attr; }

        // Needed for compatibility.
        CFURLRequestRef cfURLRequest(HTTPBodyUpdatePolicy) const { return 0; }
        // The following two stubs are for compatibility with CFNetwork, and are not used.
        static bool httpPipeliningEnabled() { return false; }
        static void setHTTPPipeliningEnabled(bool) { }
#endif

    private:
        friend class ResourceRequestBase;

        void doUpdatePlatformRequest() { }
        void doUpdateResourceRequest() { }
        void doUpdatePlatformHTTPBody() { }
        void doUpdateResourceHTTPBody() { }

        //cory std::unique_ptr<CrossThreadResourceRequestData> doPlatformCopyData(std::unique_ptr<CrossThreadResourceRequestData> data) const { return data; }
        //cory void doPlatformAdopt(std::unique_ptr<CrossThreadResourceRequestData>) { }
        void doPlatformSetAsIsolatedCopy(const ResourceRequest&) { } // cory add
#if USE(CRNET)
        // Anchor element's download attribute. isNull = false if set.
        String m_downloadAttribute;
#endif
    };

} // namespace WebCore

#endif // ResourceRequest_h