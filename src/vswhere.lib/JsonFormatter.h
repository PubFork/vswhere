// <copyright file="JsonFormatter.h" company="Microsoft Corporation">
// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt in the project root for license information.
// </copyright>

#pragma once

class JsonFormatter :
    public Formatter
{
public:
    static std::unique_ptr<Formatter> Create()
    {
        return std::unique_ptr<JsonFormatter>(new JsonFormatter());
    }

    JsonFormatter() :
        Formatter()
    {
    }

    JsonFormatter(_In_ const JsonFormatter& obj) :
        Formatter(obj),
        m_padding(obj.m_padding),
        m_scopes(obj.m_scopes)
    {
    }

    static std::wstring Escape(_In_ const std::wstring& value);

    bool ShowLogo() const override
    {
        return false;
    }

    bool SupportsPackages() const override
    {
        return true;
    }

protected:
    void StartArray(_In_ Console& console, _In_opt_ const std::wstring& name = empty_wstring) override;
    void StartObject(_In_ Console& console, _In_opt_ const std::wstring& name = empty_wstring) override;
    void WriteProperty(_In_ Console& console, _In_ const std::wstring& name, _In_ const std::wstring& value) override;
    void WriteProperty(_In_ Console& console, _In_ const std::wstring& name, _In_ bool value) override;
    void WriteProperty(_In_ Console& console, _In_ const std::wstring& name, _In_ long long value) override;
    void EndObject(_In_ Console& console) override;
    void EndArray(_In_ Console& console) override;
    void EndDocument(_In_ Console& console) override;
    std::wstring FormatDate(_In_ const FILETIME& value) override;

private:
    static const size_t padding_size = 2;

    void Push();
    void Pop();

    void StartScope(_In_ Console& console, _In_ JsonScope::Type type, _In_ const std::wstring& name);
    void StartProperty(_In_ Console& console, _In_ const std::wstring& name);
    void EndScope(_In_ Console& console);

    std::wstring m_padding;
    std::stack<JsonScope> m_scopes;
};
