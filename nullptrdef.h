#ifndef NULLPTRDEF_H
#define NULLPTRDEF_H

/*
 * If the C++11 'nullptr' keyword is not defined, add it
 */

#if defined(__cplusplus) && __cplusplus < 201103L
    // it is a const object...
    const class nullptr_t
    {
    public:
        // constructor
        nullptr_t() {}
        // convertible to any type of null non-member pointer...
        template<typename _Tp> operator _Tp* () const{ return (_Tp*)0; }
        // or any type of null member pointer...
        template<typename _Cl, typename _Tp> operator _Tp _Cl::* () const { return (_Tp _Cl::*)0; }
        // support operator overloading (== and !=)
        template<typename _Tp> bool equals(_Tp const& rhs) const { return rhs == 0; }
    private:
        // can not take address of nullptr
        void operator&() const;
        // can not copy
        nullptr_t(const nullptr_t&);
        const nullptr_t& operator=(const nullptr_t&);
    } nullptr_;
    #define nullptr nullptr_

    template<typename T> inline bool operator==(const nullptr_t& lhs, T const& rhs) { return  lhs.equals(rhs); }
    template<typename T> inline bool operator==(T const& lhs, const nullptr_t& rhs) { return  rhs.equals(lhs); }
    template<typename T> inline bool operator!=(const nullptr_t& lhs, T const& rhs) { return !lhs.equals(rhs); }
    template<typename T> inline bool operator!=(T const& lhs, const nullptr_t& rhs) { return !rhs.equals(lhs); }
#endif

#endif // NULLPTRDEF_H
