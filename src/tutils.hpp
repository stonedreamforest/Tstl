#ifndef _TUTILS_H_HPP_
#define _TUTILS_H_HPP_
#ifdef _KERNEL_TSTL
#include <ntddk.h>
#define _noexcept
#else
#define _noexcept noexcept
#endif // _KERNEL_TSTL

#if _HAS_NODISCARD
#define _NODISCARD [[nodiscard]]
#define _NODISCARD_PERF
#else /* ^^^ CAN HAZ [[nodiscard]] ^^^ // vvv NO CAN HAZ [[nodiscard]] vvv */
#define _NODISCARD
#define _NODISCARD_PERF
#endif /* _HAS_NODISCARD */

#if _HAS_CXX17
#define _INLINE_VAR inline
#else /* _HAS_CXX17 */
#define _INLINE_VAR
#endif /* _HAS_CXX17 */

#define _EMPTY_ARGUMENT
#define _CLASS_DEFINE_CV(CLASS)                                                                    \
    CLASS(_EMPTY_ARGUMENT)                                                                         \
    CLASS(const)                                                                                   \
    CLASS(volatile)                                                                                \
    CLASS(const volatile)

namespace Tstl {
    template <class _Type>
    struct remove_pointer {
        using type = _Type;
    };

    /**/ #define _REMOVE_POINTER(CV_OPT) /**/ template <class _Type>
    /**/ struct remove_pointer <_Type * CV_OPT> /**/ { /* remove pointer */
        using type = _Type;                            /**/
    };
    _CLASS_DEFINE_CV(_REMOVE_POINTER)
#undef _REMOVE_POINTER

    template <class _Type>
    using remove_pointer_t = typename remove_pointer<_Type>::type;

    template <class _Type, _Type _Val>
    struct integral_constant {
        static constexpr _Type value = _Val;

        using value_type = _Type;
        using type       = integral_constant;

        constexpr operator value_type() const noexcept {
            return (value);
        }

        _NODISCARD constexpr value_type operator()() const noexcept {
            return (value);
        }
    };

    template <bool _Val>
    using bool_constant = integral_constant<bool, _Val>;

    using true_type  = bool_constant<true>;
    using false_type = bool_constant<false>;

    template <class _Type>
    struct is_class : bool_constant<__is_class(_Type)> {};

    template <class _Type>
    struct is_lvalue_reference : false_type {};

    template <class _Type>
    struct is_lvalue_reference<_Type&> : true_type {};

    template <class _Type>
    _INLINE_VAR constexpr bool is_lvalue_reference_v = is_lvalue_reference<_Type>::value;

    template <class _Type>
    struct remove_reference {
        using type = _Type;
    };

    template <class _Type>
    struct remove_reference<_Type&> {
        using type = _Type;
    };

    template <class _Type>
    struct remove_reference<_Type&&> {
        using type = _Type;
    };

    template <class _Type>
    using remove_reference_t = typename remove_reference<_Type>::type;

    template <class _Type>
    _NODISCARD constexpr _Type&& forward(remove_reference_t<_Type>& _Arg) _noexcept {
        return (static_cast<_Type&&>(_Arg));
    }

    template <class _Type>
    _NODISCARD constexpr _Type&& forward(remove_reference_t<_Type>&& _Arg) _noexcept {
        static_assert(!is_lvalue_reference_v<_Type>, "bad forward call");
        return (static_cast<_Type&&>(_Arg));
    }

    template <class _Type>
    _NODISCARD constexpr remove_reference_t<_Type>&& move(_Type&& _Arg) _noexcept {
        return (static_cast<remove_reference_t<_Type>&&>(_Arg));
    }

    template <class _Type>
    _NODISCARD constexpr decltype(auto) new_mem() {
        void*          ptr           = nullptr;
        constexpr auto numberOfBytes = sizeof(_Type);
#ifdef _KERNEL_TSTL
        ptr = ExAllocatePoolWithTag(NonPagedPoolExecute, numberOfBytes, 'Tstl');
#else
        ptr = malloc(numberOfBytes);
#endif // _KERNEL_TSTL
        memset(ptr, 0, numberOfBytes);
        return reinterpret_cast<_Type*>(ptr);
    }

    inline decltype(auto) del_mem(void* ptr) {
        if (ptr == nullptr) {
            __debugbreak();
        }
#ifdef _KERNEL_TSTL
        ExFreePoolWithTag(ptr, 'Tstl');
#else
        free(ptr);
#endif // _KERNEL_TSTL
        ptr = nullptr;
    }

    /*
    初始化全局变量 init_global_vars
    销毁全局变量 destory_global_vars
    */
    template <typename T>
    constexpr decltype(auto) init_global_vars(T& theArg) {
        using npType = typename Tstl::remove_pointer<T>::type;
        theArg       = Tstl::new_mem<npType>();
    }

    template <typename T, typename... Args>
    constexpr decltype(auto) init_global_vars(T& theArg, Args&&... nArgs) {
        init_global_vars(theArg);
        init_global_vars(Tstl::forward<Args>(nArgs)...);
    }

    template <typename T>
    constexpr decltype(auto) destory_global_vars(T& theArg) {
        theArg->_destory();
        del_mem(theArg);
        theArg = nullptr;
    }

    template <typename T, typename... Args>
    constexpr decltype(auto) destory_global_vars(T& theArg, Args&&... nArgs) {
        destory_global_vars(theArg);
        destory_global_vars(Tstl::forward<Args>(nArgs)...);
    }

    template <typename T>
    class Constructor {
    public:
        Constructor() {
            _Object = Tstl::new_mem<T>();
        }
        ~Constructor() {
            Tstl::del_mem(_Object);
        }

    public:
        template <typename... Args>
        decltype(auto) init_args(Args&&... nArgs) {
            _Object->_init(Tstl::forward<Args>(nArgs)...);
        }

        decltype(auto) get() const {
            return *_Object;
        }

    private:
        T* _Object = nullptr;
    };

} // namespace Tstl

#undef _EMPTY_ARGUMENT
#undef _CLASS_DEFINE_CV

#endif // !_TUTILS_H_HPP_
