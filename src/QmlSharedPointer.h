#pragma once

#include <QSharedPointer>

template <class T>
class QmlSharedPointer
    : public QSharedPointer<T>
{
//    Q_GADGET

public:
    QmlSharedPointer();
    template <typename X> explicit QmlSharedPointer(X *ptr)
        : QSharedPointer<T>(ptr)
    {}

    template <typename X, typename Deleter> QmlSharedPointer(X *ptr, Deleter d)
        : QSharedPointer<T>(ptr, d)
    {}

    QmlSharedPointer(std::nullptr_t)
        : QSharedPointer<T>(nullptr)
    {}

    template <typename Deleter> QmlSharedPointer(std::nullptr_t, Deleter d)
        : QSharedPointer<T>(nullptr, d)
    {}

    QmlSharedPointer(const QSharedPointer<T> &other)
        : QSharedPointer<T>(other)
    {}

    QmlSharedPointer(const QWeakPointer<T> &other)
        : QSharedPointer<T>(other)
    {}

    virtual ~QmlSharedPointer()
    {}
};
