#pragma once

// This macro defines a dependency property for a WinRT class.
// Use this in your class' header file after declaring it in the idl.
// Remember to register your dependency property in the respective cpp file.
#define DEPENDENCY_PROPERTY(type, name)                                  \
public:                                                                  \
    static winrt::Windows::UI::Xaml::DependencyProperty name##Property() \
    {                                                                    \
        return _##name##Property;                                        \
    }                                                                    \
    type name() const                                                    \
    {                                                                    \
        return winrt::unbox_value<type>(GetValue(_##name##Property));    \
    }                                                                    \
    void name(const type& value)                                         \
    {                                                                    \
        SetValue(_##name##Property, winrt::box_value(value));            \
    }                                                                    \
                                                                         \
private:                                                                 \
    static winrt::Windows::UI::Xaml::DependencyProperty _##name##Property;

// This macro must be used alongside GETSET_BINDABLE_ENUM_SETTING.
// Use this in your class's constructor after Initialize_Component().
// It sorts and initializes the observable list of enum entries with the enum name
// being its localized name, and also initializes the enum to EnumEntry
// map that's required to tell XAML what enum value the currently active
// setting has.
#define INITIALIZE_BINDABLE_ENUM_SETTING(name, list, resourceProperty)                                  \
    do                                                                                                  \
    {                                                                                                   \
        std::vector<winrt::hstring> _nameList;                                                          \
                                                                                                        \
        for (auto _name : list)                                                                         \
        {                                                                                               \
            winrt::hstring bindname = LocalizedNameForResource(_name, resourceProperty);                \
            _nameList.emplace_back(bindname);                                                           \
        }                                                                                               \
        _##name##List = winrt::single_threaded_observable_vector<winrt::hstring>(std::move(_nameList)); \
                                                                                                        \
		auto curr = _##name.try_as<winrt::hstring>();                                                   \
                                                                                                        \
        winrt::hstring bindname = LocalizedNameForResource(*curr, resourceProperty);                    \
        _##name = box_value(bindname);                                                                  \
    } while (0);

// This macro must be used alongside GETSET_BINDABLE_ENUM_SETTING.
// Use this in your class's constructor after Initialize_Component().
// It sorts and initializes the observable list of enum entries with the enum name
// being its localized name, and also initializes the enum to EnumEntry
// map that's required to tell XAML what enum value the currently active
// setting has.
#define INITIALIZE_BINDABLE_CONTA_SETTING(N, T, name, list, resourceProperty)                           \
    do                                                                                                  \
    {                                                                                                   \
        std::vector<N::T> _nameList;                                                                    \
        winrt::hstring row = _Current##name.##name();                                                 \
        winrt::hstring dip;                                                                             \
                                                                                                        \
        for (auto _name : list)                                                                         \
        {                                                                                               \
            winrt::hstring bindname = LocalizedNameForResource(_name, resourceProperty);                \
            auto container{ winrt::make_self<T>() };                                                    \
                                                                                                        \
            (*container).##name(bindname);                                                              \
            _nameList.emplace_back(*container);                                                           \
        }                                                                                               \
        _##name##List = winrt::single_threaded_observable_vector<N::T>(std::move(_nameList));           \
        dip = LocalizedNameForResource(row, resourceProperty);                                          \
        _Current##name.##name(dip);                                                                      \
    } while (0);


// This macro must be used alongside INITIALIZE_BINDABLE_ENUM_SETTING.
// It declares the needed data structures, getters, and setters to make
// the given enum type bindable to XAML. It provides an observable list
// of EnumEntries so that we may display all possible values of the given
// enum type and its localized names. It also provides a getter and setter
// for the setting we wish to bind to.
#define GETSET_BINDABLE_ENUM_SETTING(name, enumType, _default)                                  \
public:                                                                                         \
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::hstring> name##List()     \
    {                                                                                           \
        return _##name##List;                                                                   \
    }                                                                                           \
                                                                                                \
    winrt::Windows::Foundation::IInspectable Current##name()                                    \
    {                                                                                           \
        return _##name##;                                                                       \
    }                                                                                           \
                                                                                                \
    void Current##name(const winrt::Windows::Foundation::IInspectable& enumEntry)               \
    {                                                                                           \
        _##name## = enumEntry;                                                                  \
    }                                                                                           \
                                                                                                \
private:                                                                                        \
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::hstring> _##name##List;   \
    winrt::Windows::Foundation::IInspectable _##name## { box_value(_default) };


// Use this macro to quick implement both the getter and setter for a property.
// This should only be used for simple types where there's no logic in the
// getter/setter beyond just accessing/updating the value.
#define WINRT_PROPERTY(type, name, ...)                        \
public:                                                        \
    type name() const noexcept { return _##name; }             \
    void name(const type& value) noexcept { _##name = value; } \
                                                               \
private:                                                       \
    type _##name{ __VA_ARGS__ };

// Use this macro to quickly implement both the getter and setter for an
// observable property. This is similar to the WINRT_PROPERTY macro above,
// except this will also raise a PropertyChanged event with the name of the
// property that has changed inside of the setter. This also implements a
// private _setName() method, that the class can internally use to change the
// value when it _knows_ it doesn't need to raise the PropertyChanged event
// (like when the class is being initialized).
#define WINRT_OBSERVABLE_PROPERTY(type, name, event, ...)                                 \
public:                                                                                   \
    type name() const noexcept { return _##name; };                                       \
    void name(const type& value)                                                          \
    {                                                                                     \
        if (_##name != value)                                                             \
        {                                                                                 \
            _##name = value;                                                              \
            event(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L## #name }); \
        }                                                                                 \
    };                                                                                    \
                                                                                          \
private:                                                                                  \
    type _##name{ __VA_ARGS__ };                                                          \
    void _set##name(const type& value)                                                    \
    {                                                                                     \
        _##name = value;                                                                  \
    };

// This is a helper macro for both declaring the signature of a callback (nee event) and
// defining the body. Winrt callbacks need a method for adding a delegate to the
// callback and removing the delegate. This macro will both declare the method
// signatures and define them both for you, because they don't really vary from
// event to event.
// Use this in a class's header if you have a "delegate" type in your IDL.
#define WINRT_CALLBACK(name, args)                                                          \
public:                                                                                     \
    winrt::event_token name(const args& handler) { return _##name##Handlers.add(handler); } \
    void name(const winrt::event_token& token) { _##name##Handlers.remove(token); }         \
                                                                                            \
protected:                                                                                  \
    winrt::event<args> _##name##Handlers;
