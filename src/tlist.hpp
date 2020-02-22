#ifndef _TLIST_HPP_
#define _TLIST_HPP_
#include "tutils.hpp"

namespace Tstl {
    template <typename T>
    class TList {
    private:
        typedef struct _Node {
            T      Value;
            _Node* prevNode;
            _Node* nextNode;
        } Node, *PNode;

    public:
        TList() = default;
        ~TList() {
            clear();
        }
        void _destory() {
            m_isDestory = true;
            clear();
        }

    public:
        decltype(auto) add(T&& newData) {
            _add(Tstl::move(newData));
        }
        decltype(auto) add(const T& newData) {
            _add(newData);
        }

        decltype(auto) remove(T targetData) {
            if (m_pHeadNode == nullptr) {
                return false;
            }

            auto temp = m_pHeadNode;

            if (temp->nextNode == nullptr) {
                if (temp->Value == targetData) {
                    Tstl::del_mem(temp);
                    m_pHeadNode = nullptr;
                    return true;
                } else {
                    return false;
                }
            } else {
                if (temp->Value == targetData) {
                    temp->nextNode->prevNode = nullptr;
                    m_pHeadNode              = temp->nextNode;
                    Tstl::del_mem(temp);
                    return true;
                }
            }

            while (temp->nextNode != nullptr) {
                temp = temp->nextNode;
                if (temp->nextNode == nullptr) {
                    if (temp->Value == targetData) {
                        temp->prevNode->nextNode = nullptr;
                        break;
                    } else {
                        return false;
                    }
                }

                if (temp->Value == targetData) {
                    temp->prevNode->nextNode = temp->nextNode;
                    temp->nextNode->prevNode = temp->prevNode;
                    break;
                }
            }
            Tstl::del_mem(temp);
            return true;
        }

        decltype(auto) clear() {
            if (m_pHeadNode == nullptr) {
                return;
            }
            auto temp = reinterpret_cast<PNode>(0);
            for (auto cur = m_pHeadNode; cur != nullptr; cur = temp) {
                if constexpr (Tstl::is_class<T>::value == true) {
                    cur->Value._destory();
                }
                temp = cur->nextNode;
                Tstl::del_mem(cur);
            }
            m_pHeadNode = nullptr;
        }

        template <typename... _Type>
        decltype(auto) _add(_Type&&... newValue) {
            auto pNewNode      = Tstl::new_mem<Node>();
            pNewNode->Value    = T(Tstl::forward<_Type>(newValue)...);
            pNewNode->nextNode = m_pHeadNode;
            pNewNode->prevNode = nullptr;
            if (m_pHeadNode != nullptr) {
                m_pHeadNode->prevNode = pNewNode;
            }
            m_pHeadNode = pNewNode;
        }

    private:
        bool  m_isDestory = false;
        PNode m_pHeadNode = nullptr;
    };

} // namespace Tstl

#endif // !_TLIST_HPP_