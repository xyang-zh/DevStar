#pragma once

#include "Repeat.g.h"
#include <unordered_set>

namespace winrt::DevStar::implementation
{
    struct Repeat : RepeatT<Repeat>
    {
        Repeat();
       
        void ClearButtonClicked(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);        
        void RepeatTextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void FindBoxTextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e);
        void AutoSearch(bool v);
        bool AutoSearch(void);

        void ProcessRepeat(std::string& p, std::string& match, winrt::hstring& method);
        void HighlightMatches(winrt::hstring& p);
        void RemoveHighlightes(void);
        void RemoveStatistics(void);
        bool RecordsEmpty();
        void ClearRecords(void);
        void UpdateRecords(std::unordered_set<std::string> &v, size_t s);
        bool RepeatSame(std::unordered_set<std::string>& v, size_t s);

    private:
        std::unordered_set<std::string> _repeatSet;
        size_t _repeatNum{ 0 };
        bool _autoSearch{ true };
    };
}

namespace winrt::DevStar::factory_implementation
{
    struct Repeat : RepeatT<Repeat, implementation::Repeat>
    {
    };
}
