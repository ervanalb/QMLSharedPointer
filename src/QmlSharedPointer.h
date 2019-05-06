#pragma once

#include <QSharedPointer>

template <class T>
class QmlSharedPointer
    : public QObject
{
// Q_OBJECT macro written out
public:
    QT_WARNING_PUSH
    Q_OBJECT_NO_OVERRIDE_WARNING
    static const QMetaObject staticMetaObject;
    QT_TR_FUNCTIONS
private:
    Q_OBJECT_NO_ATTRIBUTES_WARNING
    Q_DECL_HIDDEN_STATIC_METACALL static void qt_static_metacall(QObject *, QMetaObject::Call, int, void **);
    QT_WARNING_POP
    struct QPrivateSignal {};
    QT_ANNOTATE_CLASS(qt_qobject, "")
// end Q_OBJECT

private:
    void init()
    {
        // Connect all signals from the encapsulated item to the QmlSharedPointer
        // Skip QObject's signals (e.g. destroyed)
        const int qObjectMethodCount = QObject::staticMetaObject.methodCount();
        for (int i = qObjectMethodCount; i < p->metaObject()->methodCount(); i++)
        {
            auto incomingSignal = p->metaObject()->method(i);
            if (incomingSignal.methodType() != QMetaMethod::Signal) continue;
            QMetaObject::connect(p.data(), i, this, i);
        }
    }

public:
    QSharedPointer<T> p;

    QmlSharedPointer()
        : p(new T())
    {
        init();
    }

    template <typename X> explicit QmlSharedPointer(X *ptr)
        : p(ptr)
    {
        init();
    }

    template <typename X, typename Deleter> QmlSharedPointer(X *ptr, Deleter d)
        : p(ptr, d)
    {
        init();
    }

    QmlSharedPointer(const QSharedPointer<T> &other)
        : p(other)
    {
        init();
    }

    QmlSharedPointer(const QWeakPointer<T> &other)
        : p(other)
    {
        init();
    }

    virtual const QMetaObject *metaObject() const
    {
        // This is sketchy but it works, and might be less sketchy than using QMetaObjectBuilder
        return p->metaObject();
    }

    virtual void *qt_metacast(const char *)
    {
        // Disable casting
        Q_ASSERT(false);
        return nullptr;
    }

    virtual int qt_metacall(QMetaObject::Call _c, int _id, void** _a)
    {
        //return p->qt_metacall(_c, _id, _a); // Dangerous??
        //Q_ASSERT(false);
        //return -1;
        if (_c == QMetaObject::InvokeMetaMethod) {
            auto method = metaObject()->method(_id);
            auto sig = QMetaObject::normalizedSignature(method.methodSignature());
            if (method.methodType() == QMetaMethod::Signal) {
                auto newId = _id - QObject::staticMetaObject.methodCount();
                QMetaObject::activate(this, metaObject(), newId, _a);
                return -1;
            } else {
                if (_id < QObject::staticMetaObject.methodCount()) {
                    // Handle things like deleteLater internally
                    return QObject::qt_metacall(_c, _id, _a);
                } else {
                    // Forward on anything else
                    return p->qt_metacall(_c, _id, _a); // This could be dangerous as _id might not be the same, but it appears to be the same so :shrug:
                }
            }
        } else if (_c == QMetaObject::IndexOfMethod ||
                   _c == QMetaObject::ReadProperty || 
                   _c == QMetaObject::WriteProperty ||
                   _c == QMetaObject::ResetProperty) {
            return p->qt_metacall(_c, _id, _a); // This could be dangerous as _id might not be the same
        } else {
            return -1;
        }
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
        QT_MOC_LITERAL(0, 0, 18), // "QmlSharedPointer<ExampleQmlObject>"
    },
    //"QmlSharedPointer<" + T::staticMetaObject.className() + ">\0"
    "QmlSharedPointer<" "ExampleQmlObject" ">\0"
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
