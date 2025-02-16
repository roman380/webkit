/*
 * Copyright (C) 2020 Sony Interactive Entertainment Inc.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "JSObject.h"

namespace JSC {

class IntlLocale final : public JSNonFinalObject {
public:
    using Base = JSNonFinalObject;

    static constexpr bool needsDestruction = true;

    static void destroy(JSCell* cell)
    {
        static_cast<IntlLocale*>(cell)->IntlLocale::~IntlLocale();
    }

    template<typename CellType, SubspaceAccess mode>
    static IsoSubspace* subspaceFor(VM& vm)
    {
        return vm.intlLocaleSpace<mode>();
    }

    static IntlLocale* create(VM&, Structure*);
    static Structure* createStructure(VM&, JSGlobalObject*, JSValue);

    DECLARE_INFO;

    void initializeLocale(JSGlobalObject*, JSValue tagValue, JSValue optionsValue);
    const String& maximize();
    const String& minimize();
    const String& toString();
    const String& baseName();
    const String& language();
    const String& script();
    const String& region();
    const String& calendar();
    const String& caseFirst();
    const String& collation();
    const String& hourCycle();
    const String& numberingSystem();
    TriState numeric();

private:
    IntlLocale(VM&, Structure*);
    void finishCreation(VM&);
    static void visitChildren(JSCell*, SlotVisitor&);

    String keywordValue(ASCIILiteral, bool isBoolean = false) const;

    CString m_localeID;

    String m_maximized;
    String m_minimized;
    String m_fullString;
    String m_baseName;
    String m_language;
    String m_script;
    String m_region;
    String m_calendar;
    String m_caseFirst;
    String m_collation;
    String m_hourCycle;
    String m_numberingSystem;
    TriState m_numeric { TriState::Indeterminate };
};

} // namespace JSC
