#pragma once

#include <QSharedPointer>
#include <QtCore/private/qmetaobjectbuilder_p.h>

template <class T>
class QmlSharedPointer
    : public QObject
{
// Q_OBJECT macro written out
public:
    QT_WARNING_PUSH
    Q_OBJECT_NO_OVERRIDE_WARNING
    static const QMetaObject staticMetaObject;
    //virtual const QMetaObject *metaObject() const;
    //virtual void *qt_metacast(const char *);
    //virtual int qt_metacall(QMetaObject::Call, int, void **);
    QT_TR_FUNCTIONS
private:
    Q_OBJECT_NO_ATTRIBUTES_WARNING
    Q_DECL_HIDDEN_STATIC_METACALL static void qt_static_metacall(QObject *, QMetaObject::Call, int, void **);
    QT_WARNING_POP
    struct QPrivateSignal {};
    QT_ANNOTATE_CLASS(qt_qobject, "")

private:
    QMetaObject *m_metaobject;
    QSharedPointer<T> m_dptr;

// end Q_OBJECT

    void init()
    {
        QMetaObjectBuilder b;
        m_metaobject = b.toMetaObject();
    }

public:
    QmlSharedPointer()
        : m_dptr()
    {
        init();
    }

    template <typename X> explicit QmlSharedPointer(X *ptr)
        : m_dptr(ptr)
    {
        init();
    }

    template <typename X, typename Deleter> QmlSharedPointer(X *ptr, Deleter d)
        : m_dptr(ptr, d)
    {
        init();
    }

    QmlSharedPointer(std::nullptr_t)
        : m_dptr(nullptr)
    {
        init();
    }

    template <typename Deleter> QmlSharedPointer(std::nullptr_t, Deleter d)
        : m_dptr(nullptr, d)
    {
        init();
    }

    QmlSharedPointer(const QSharedPointer<T> &other)
        : m_dptr(other)
    {
        init();
    }

    QmlSharedPointer(const QWeakPointer<T> &other)
        : m_dptr(other)
    {
        init();
    }

    virtual const QMetaObject *metaObject() const
    {
        //return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
        //return &staticMetaObject;
        return m_metaobject; 
    }

    virtual void *qt_metacast(const char *)
    {
        Q_ASSERT(false);
        return nullptr;
    }

    virtual int qt_metacall(QMetaObject::Call, int, void**)
    {
        Q_ASSERT(false);
        return -1;
    }

    virtual ~QmlSharedPointer()
    {
        free(m_metaobject);
    }
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

