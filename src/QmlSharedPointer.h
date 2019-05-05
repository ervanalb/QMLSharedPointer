#pragma once

#include <QSharedPointer>
#include "StringConstant.h"

template <class T>
class QmlSharedPointer
    : private QSharedPointer<T>
{
// The following is the Q_GADGET macro but written out explicitly
public:
    static const QMetaObject staticMetaObject;
    void qt_check_for_QGADGET_macro();
    typedef void QtGadgetHelper;
private:
    QT_WARNING_PUSH
    Q_OBJECT_NO_ATTRIBUTES_WARNING
    Q_DECL_HIDDEN_STATIC_METACALL static void qt_static_metacall(QObject *, QMetaObject::Call, int, void **);
    QT_WARNING_POP
    QT_ANNOTATE_CLASS(qt_qgadget, "")
// end Q_GADGET macro

private:
    QMetaObject *m_metaobject;

    void init()
    {
    }

public:
    QmlSharedPointer()
        : QSharedPointer<T>()
    {
        init();
    }

    template <typename X> explicit QmlSharedPointer(X *ptr)
        : QSharedPointer<T>(ptr)
    {
        init();
    }

    template <typename X, typename Deleter> QmlSharedPointer(X *ptr, Deleter d)
        : QSharedPointer<T>(ptr, d)
    {
        init();
    }

    QmlSharedPointer(std::nullptr_t)
        : QSharedPointer<T>(nullptr)
    {
        init();
    }

    template <typename Deleter> QmlSharedPointer(std::nullptr_t, Deleter d)
        : QSharedPointer<T>(nullptr, d)
    {
        init();
    }

    QmlSharedPointer(const QSharedPointer<T> &other)
        : QSharedPointer<T>(other)
    {
        init();
    }

    QmlSharedPointer(const QWeakPointer<T> &other)
        : QSharedPointer<T>(other)
    {
        init();
    }

    virtual ~QmlSharedPointer()
    {
        init();
    }

    //virtual const QMetaObject *metaObject() const
    //{
    //    Q_ASSERT(false);
    //    return m_metaobject;
    //}

    //virtual void *qt_metacast(const char *)
    //{
    //    Q_ASSERT(false);
    //    return nullptr;
    //}

    //virtual int qt_metacall(QMetaObject::Call, int, void**)
    //{
    //    Q_ASSERT(false);
    //    return -1;
    //}
};

struct qt_meta_stringdata_QmlSharedPointer_t {
    QByteArrayData data[1];
    char stringdata0[];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QmlSharedPointer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
template <typename T> static const qt_meta_stringdata_QmlSharedPointer_t qt_meta_stringdata_QmlSharedPointer = {
    {
        QT_MOC_LITERAL(0, 0, 34), // "QmlSharedPointer<ExampleQmlObject>"
    },
    //"QmlSharedPointer<" + T::staticMetaObject.className() + ">\0"
    "QmlSharedPointer<"  "ExampleQmlObject"  ">\0"
    //"ExampleQmlObjectSP\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QmlSharedPointer[] = {
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       //6,   14, // methods
       //2,   62, // properties
       //0,    0, // enums/sets
       //0,    0, // constructors
       //0,       // flags
       //3,       // signalCount
};

template <typename T> void QmlSharedPointer<T>::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    return;
}

//QT_INIT_METAOBJECT template<typename T> const QMetaObject QmlSharedPointer<T>::staticMetaObject{};
QT_INIT_METAOBJECT template<typename T> const QMetaObject QmlSharedPointer<T>::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_QmlSharedPointer<T>.data,
    qt_meta_data_QmlSharedPointer,
    qt_static_metacall,
    nullptr,
    nullptr
} };
